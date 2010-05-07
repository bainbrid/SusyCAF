#!/usr/bin/env python

import configuration_SCBooks as conf,sys,os,readline,getpass,string,fileinput,socket,datetime,re

def remove_multislash(inString) :
    outString=re.sub(r'//*','/',inString)
    print outString
    return outString

def print_and_execute(c) :
    print c
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
    
    row = db.execute('''select job.rowid,jsonls,cmssw,addpkg,cvsup,cmds,susycaf,dataset,mcInfo,jec,globalTag,filter
                         from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                         where state="Unclaimed" AND job.rowid='''+jobnumber).fetchone()
    return row

def claim_job(db,job,user,node,path,full_rpath) :
    dashboard = get_dashboard(path)
    c=db.cursor()
    c.execute('update job set state=?,user=?,node=?,path=?,rpath=?,dash=? where rowid=?',
                        ('Processing',user,  node,  path, full_rpath,  dashboard, job['rowid']))
    c.close()


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


def setup_crab(job,user,path,rpath, CAF, SERVER) :
    full_rpath = ('/castor/cern.ch/cms/store/caf/user/' if CAF else
                  '/castor/cern.ch/user/'+user[0]+'/')+\
                  user+'/'+rpath

    dirs = full_rpath.strip('/').split('/')

    thing='''
#!/usr/bin/env bash
rfmkdir -p %(fp)s
rfchmod 775 %(fp)s''' % {"fp":full_rpath} +''.join(['''
rfchmod 755 /'''+'/'.join(dirs[:-i]) for i in range(1,len(dirs)-dirs.index(user))])

    thing+="\nnssetacl -m d:u::7,d:g::7,d:o:5 "+full_rpath
    for run in eval(job['jsonls']) :
        subDir=full_rpath+"/Run"+run
        thing+="\nrfmkdir "+subDir
        thing+="\nrfchmod 755 "+subDir
        thing+="\nnssetacl -m u::7,g::7,o:5 "+subDir
        
    print_and_execute(thing)
    crabfile = open(path+"/crab.cfg","w")
    print>>crabfile,'''
[CMSSW]
get_edm_output = 1
%(events)s
pset=SusyCAF_Tree_cfg.py
datasetpath=%(dset)s

[GRID]
virtual_organization=cms

[USER]
copy_data=1
user_remote_dir=%(rpath)s
storage_element=%(SE)s
%(storage_path)s

[CRAB]
cfg=crab.cfg
scheduler=%(sched)s
use_server=%(server)d
%(hack)s
jobtype=cmssw

%(caf)s
'''% { "dset": job['dataset'],
       "rpath": remove_multislash('/'+(rpath if CAF else '/'.join(dirs[dirs.index('user'):]))),
       "SE": ('T2_CH_CAF' if CAF else 'srm-cms.cern.ch'),
       "server": SERVER,
       "storage_path": '' if CAF else '''
storage_path=/srm/managerv2?SFN=/castor/cern.ch''',
       "sched": 'caf' if CAF else 'glite',
       "events": '' if job['jsonls'] else '''
total_number_of_events=-1
events_per_job=100000''',
       "caf": '' if not CAF else '''
[CAF]
queue=cmscaf1nd''',
       "hack": 'server_name=preprod' if CAF and SERVER else ''
       }
    crabfile.close()
    return full_rpath


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
CMSSW.lumi_mask=%(path)s/%(run)sjsonls.txt
'''%{"run":run,"path":path} for run in jsonls.keys()])
    mcrabfile.close()
    return


def run_crab(job,path) :
    crab = 'multicrab' if job['jsonls'] else 'crab'
    print_and_execute('''
#!/usr/bin/env bash
    
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
cd %(path)s/%(cmssw)s/src/
eval `scram runtime -sh`
source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh
cd %(path)s
python %(path)s/%(cmssw)s/src/SUSYBSMAnalysis/SusyCAF/test/exampleTree_cfg.py patify=1 fromRECO=1 mcInfo=%(mc)d JetCorrections=%(jec)s GlobalTag=%(gt)s::All
%(crab)s -create -submit
%(crab)s -status &> crab.status
'''%{ "path" : path,
      "cmssw" : job['cmssw'],
      "mc" : job['mcInfo'],
      "jec" : job['jec'],
      "gt" : job['globalTag'],
      "crab" : "multicrab" if job['jsonls'] else "crab"})
    return


def get_dashboard(path) :
    dash = []
    for line in fileinput.input(path+'/crab.status') :
        if line.find("Dashboard:")>0 :
            dash.append(line[line.find(":")+1:-1])
    return '"'+', '.join(dash)+'"'

    
user = getpass.getuser()
node = socket.gethostname()
timestamp = '_'.join(['%02d'% i for i in datetime.datetime.now().timetuple()[:6]])
path = '/tmp/'+user+'/SusyCAF/'+timestamp+'/'
rpath='/SusyCAF/automated/'+timestamp+'/'

CAF = True if raw_input('Run Jobs on CAF? [y/n]  ') in ['Y','y',1] else False
print '\tJobs will run on '+('CAF' if CAF else 'GRID')
SERVER = True if raw_input('Run Jobs via Server? [y/n]  ') in ['Y','y',1] else False
print '\tServer '+('ON' if SERVER else 'OFF')

db = conf.lockedDB()
db.connect()
job = get_jobrow( db )

setup_cmssw( job, path )

full_rpath = setup_crab( job, user, path, rpath, CAF, SERVER)

if job['jsonls'] :
    setup_multicrab( job, path )

run_crab( job, path )

claim_job( db, job, user, node, path, full_rpath )

db.disconnect()
