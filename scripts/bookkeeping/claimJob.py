#!/usr/bin/env python

import configuration_SCBooks as conf,sys,os,readline,getpass,string,fileinput,socket,datetime,re

def remove_multislash(inString) :
    return re.sub(r'//*','/',inString)

def print_and_execute(c) :
    print '',c,''
    os.system(c)
    return

def get_jobrow(db) :
    rows = db.execute('''select job.rowid,dataset,cmssw,susycaf,jec,globalTag,filter
                             from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                             where state="Unclaimed"''').fetchall()
    for row in rows:
        print row.keys()
        print '\t'.join([str(item) for item in row])
    jobnumber = raw_input("\n\n\tWhich job?  ")
    if not jobnumber in [str(row['rowid']) for row in rows] :
        print jobnumber+' is not and `Unclaimed` job'
        db.disconnect()
        sys.exit()
    
    row = db.execute('''select job.rowid,jsonls,cmssw,addpkg,cvsup,cmds,susycaf,dataset,mcInfo,NoiseCleaning,jec,globalTag,filter
                         from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                         where state="Unclaimed" AND job.rowid='''+jobnumber).fetchone()
    return row

def setup_cmssw(job,path) :
    print_and_execute(
'''
#!/usr/bin/env bash
mkdir -p %(path)s
cd %(path)s
scram project CMSSW %(cmssw)s
cd %(cmssw)s/src/
eval `scram runtime -sh`
cvs co -r %(susycaf)s -dSUSYBSMAnalysis/SusyCAF UserCode/SusyCAF
'''%{ "path":path, "cmssw":job['cmssw'], "susycaf":job['susycaf'] }            +''.join(['''
addpkg '''+pkg for pkg in job['addpkg'].split(',')] if job['addpkg'] else [''])+''.join(['''
cvs up -r '''+f for f in job['cvsup'].split(',')] if job['cvsup'] else [''])   +'''
'''+'\n'.join( job['cmds'].split(';') if job['cmds'] else [''])+'''
scram b -j 8
''')
    return


def setup_output_dirs(option) :
    dirs = option["FULL_RPATH"].strip('/').split('/')
    print_and_execute('''
#!/usr/bin/env bash
rfmkdir -p %(FULL_RPATH)s
rfchmod 775 %(FULL_RPATH)s''' % option +''.join(['''
rfchmod 755 /'''+'/'.join(dirs[:-i]) for i in range(1,len(dirs)-dirs.index(option["USER"]))]))


def setup_crab(job,option) :

    SITE = { "CASTOR" : {"SE":"srm-cms.cern.ch",
                         "FULL_RPATH":"/castor/cern.ch/user/%(INITIAL)s/%(USER)s/%(RPATH)s",
                         "USER_REMOTE": "user/%(INITIAL)s/%(USER)s/%(RPATH)s",
                         "SCHEDULER":"glite",
                         "EXTRA": "\n[USER]\nstorage_path=/srm/managerv2?SFN=/castor/cern.ch"
                         },
             "CAF"    : {"SE":"T2_CH_CAF",
                         "FULL_RPATH":"/castor/cern.ch/cms/store/caf/user/%(USER)s/%(RPATH)s" % option,
                         "USER_REMOTE":"%(RPATH)s",
                         "SCHEDULER":"caf",
                         "EXTRA":"\n[CAF]\nqueue=cmscaf1nd\n%s" % "" if job['dataset'].find('ExpressPhysics')<0 else \
                         "[CMSSW]\ndbs_url = http://cmsdbsprod.cern.ch/cms_dbs_caf_analysis_01/servlet/DBSServlet"},
             "LONDON" : {"SE":"T2_UK_London_IC",
                         "FULL_RPATH":"/pnfs/hep.ph.ic.ac.uk/data/cms/%(USER)s/%(RPATH)s" % option,
                         "USER_REMOTE":"%(RPATH)s",
                         "SCHEDULER":"glite",
                         "EXTRA": ""}
              }
    option["INITIAL"] = option["USER"][0]
    for key,val in SITE[option["SITE"]].items() :
        option[key] = eval('\'\'\''+val+'\'\'\'%option')

    option["EVENTS"] = '' if option["SPLIT"] else '''
lumi_mask=%(PATH)s/jsonls.txt
total_number_of_lumis=-1
lumis_per_job=10'''%option if job['jsonls'] else '''
total_number_of_events=-1
events_per_job=100000'''
    option['DATASET'] = job['dataset']

    if option["SITE"] != "LONDON" :
        setup_output_dirs(option)
    if not option["SPLIT"] and job['jsonls'] :
        file = open("%(PATH)s/jsonls.txt"%option,"w")
        print>>file,str(job['jsonls']).replace("'",'"')
        file.close()
    
    crabfile = open("%(PATH)s/crab.cfg"%option,"w")
    print>>crabfile,'''
[CMSSW]
get_edm_output = 1
%(EVENTS)s
pset=SusyCAF_Tree_cfg.py
datasetpath=%(DATASET)s

[GRID]
virtual_organization=cms

[USER]
copy_data=1
user_remote_dir=%(USER_REMOTE)s
storage_element=%(SE)s

[CRAB]
cfg=crab.cfg
scheduler=%(SCHEDULER)s
use_server=%(SERVER)d
jobtype=cmssw

%(EXTRA)s
'''% option
    crabfile.close()
    return


def setup_multicrab(job,path) :
    jsonls = eval(job['jsonls'])
    for run in jsonls.keys() :
        jsonFile = open( '%s/%sjsonls.txt' % (path,run),"w")
        print>>jsonFile, '{ "%s":%s }'%(run,jsonls[run])
        jsonFile.close()

    mcrabfile = open(path+"/multicrab.cfg","w")
    print>>mcrabfile,'''
[MULTICRAB]
cfg=crab.cfg

[COMMON]
CMSSW.total_number_of_lumis=-1
CMSSW.lumis_per_job=10'''+''.join(['''

[Run%(run)s]
CMSSW.runselection=%(run)s
CMSSW.lumi_mask=%(path)s/%(run)sjsonls.txt
'''%{"run":run,"path":path} for run in jsonls.keys()])
    mcrabfile.close()
    return


def run_crab(job,path,SPLIT) :
    print_and_execute('''
#!/usr/bin/env bash
    
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
cd %(path)s/%(cmssw)s/src/
eval `scram runtime -sh`
source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh
cd %(path)s
python %(path)s/%(cmssw)s/src/SUSYBSMAnalysis/SusyCAF/test/exampleTree_cfg.py patify=1 fromRECO=1 mcInfo=%(mc)d %(noise)s JetCorrections=%(jec)s GlobalTag=%(gt)s::All
%(crab)s -create -submit
%(crab)s -status &> crab.status
'''%{ "path" : path,
      "cmssw" : job['cmssw'],
      "mc" : job['mcInfo'],
      "noise": "" if job['NoiseCleaning'] < 0 else "NoiseCleaning=%d"%job['NoiseCleaning'],
      "jec" : job['jec'],
      "gt" : job['globalTag'],
      "crab" : "multicrab" if SPLIT else "crab"})
    return


def get_dashboard(path) :
    dash = []
    for line in fileinput.input(path+'/crab.status') :
        if line.find("Dashboard:")>0 :
            dash.append((line[line.find(":")+1:]).strip())
    return '"'+', '.join(dash)+'"'


def get_options(name) :
    option = {}
    timestamp = '_'.join(['%02d'% i for i in datetime.datetime.now().timetuple()[:6]])
    print "Choose output site:"
    for site in ["CASTOR","CAF","LONDON"] : print '\t'+site
    option["SITE"] = raw_input("\t> ")
    option["SERVER"] = True if raw_input('Run Jobs via Server? [y/n]  ') in ['Y','y',1] else False
    option["SPLIT"] = True if job['jsonls'] and raw_input('Split by run with multicrab? [y/n]') in  ['Y','y',1] else False
    print 'You have specified:'
    for key,val in option.items() :
        print key+": "+str(val)
    option["USER"] = getpass.getuser()
    option["NODE"] = socket.gethostname()
    option["PATH"] = '/'.join(['','tmp',option['USER'],name,timestamp,''])
    option["RPATH"] = '/'.join(['',name,'automated',timestamp,''])
    option["JOBID"] = job['rowid']
    return option


db = conf.lockedDB()
db.connect()
job = get_jobrow( db )
option = get_options(db.name)
if(raw_input('\nDo it? [y/n] : ') in ['Y','y',1]) :
    setup_cmssw( job, option["PATH"] )
    setup_crab( job, option)
    if option["SPLIT"] : setup_multicrab( job, option["PATH"] )
    run_crab( job, option["PATH"], option["SPLIT"] )
    option["DASH"] = get_dashboard(option["PATH"])
    
    db.execute('''update job set
    state="Processing",
    user="%(USER)s",
    node="%(NODE)s",
    path="%(PATH)s",
    rpath="%(FULL_RPATH)s",
    dash=%(DASH)s where rowid=%(JOBID)d''' % option )
db.disconnect()
