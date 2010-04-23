#!/usr/bin/env python

import configuration_SCBooks as conf,sys,os,readline,getpass,string,fileinput,socket,datetime

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
    commands = ['#!/usr/bin/env bash\n\n',
                'mkdir -p '+path,
                'cd '+path,
                'scram project CMSSW '+job['cmssw'],
                'cd '+job['cmssw']+'/src/',
                'eval `scram runtime -sh`',
                'cvs co -r'+job['susycaf']+' -dSUSYBSMAnalysis/SusyCAF UserCode/SusyCAF']
    commands+= ['addpkg '+pkg for pkg in job['addpkg'].split(',')] if job['addpkg']  else ['']
    commands+= ['cvs up -r '+f for f in job['cvsup'].split(',')] if job['cvsup']  else ['']
    commands+= job['cmds'].split(',') if job['cmds']  else ['']
    commands+= ['scram b -j8',
                '']    
    print '\n'.join(commands)
    os.system('\n'.join(commands))
    return


def setup_crab(job,user,path,rpath, CAF) :
    full_rpath = ('/castor/cern.ch/cms/store/caf/user/' if CAF else
                  '/castor/cern.ch/user/'+user[1]+'/')+\
                  user+'/'+rpath

    dirs = full_rpath.split('/')
    dirs.index(user)
    
    commands = ['#!/usr/bin/env bash\n\n',
                'rfmkdir -p '+full_rpath]
    commands +=['rfchmod 755 '+'/'.join(dirs[0:-i]) for i in range(len(dirs[dirs.index(user):]))]
    commands +=['rfchmod 775 '+full_rpath]
    print '\n'.join(commands)
    os.system('\n'.join(commands))    

    cfg = ['[CMSSW]',
           'get_edm_output = 1',
           '' if job['jsonls'] else 'total_number_of_events=-1',
           '' if job['jsonls'] else 'events_per_job=100000',
           'pset=SusyCAF_Tree_cfg.py',
           'datasetpath='+job['dataset'],
           '',
           '[GRID]',
           'virtual_organization=cms',
           ''
           '[USER]',
           'copy_data=1',
           'user_remote_dir=/'+(rpath if CAF else '/'.join(dirs[dirs.index('user'):])),
           'storage_element='+('T2_CH_CAF' if CAF else 'srm-cms.cern.ch'),
           '' if CAF else 'storage_path=/srm/managerv2?SFN=/castor/cern.ch',
           '',
           '[CRAB]',
           'cfg=crab.cfg',
           'scheduler='+('caf' if CAF else 'glite'),
           'use_server=1',
           'jobtype=cmssw',
           '']
    if CAF : cfg += ['[CAF]',
                     'queue=cmscaf1nd',
                     '']
    crabfile = open(path+"/crab.cfg","w")
    print '\n'.join(cfg),''
    print>>crabfile,'\n'.join(cfg)
    crabfile.close()
    return full_rpath


def setup_multicrab(job,path) :
    jsonls = string.strip(job['jsonls'])[1:-1].split('"')[1:]
    splitjsonls = [(jsonls[2*i],jsonls[2*i+1]) for i in range(len(jsonls)/2)]
    mcfg = ['[MULTICRAB]',
            'cfg=crab.cfg',
            '',
            '[COMMON]',
            'CMSSW.total_number_of_lumis=-1',
            'CMSSW.lumis_per_job=10']
    for pair in splitjsonls :
        mcfg += ['',
                 '[Run'+pair[0]+']',
                 'CMSSW.lumi_mask='+path+'/'+pair[0]+'jsonls.txt']
        jsonFile = open( path+'/'+pair[0]+'jsonls.txt',"w")
        print>>jsonFile, '{ "'+pair[0]+'"'+pair[1].rstrip(' ,\t\n')+'}'
        jsonFile.close()
        
    mcrabfile = open(path+"/multicrab.cfg","w")
    print>>mcrabfile,'\n'.join(mcfg)
    mcrabfile.close()
    return


def run_crab(job,path) :
    crab = 'multicrab' if job['jsonls'] else 'crab'
    commands = ['#!/usr/bin/env bash\n\n',
                'source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh',
                'cd '+path+'/'+job['cmssw']+"/src/",
                'eval `scram runtime -sh`',
                #'source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh ',
                'source /afs/cern.ch/cms/ccs/wm/scripts/Crab/CRAB_2_7_2_pre1/crab.sh',
                #'voms-proxy-init -voms cms',
                'cd '+path,
                ( 'python '+path+'/'+job['cmssw']+'/src/SUSYBSMAnalysis/SusyCAF/test/exampleTree_cfg.py'+
                  ' patify=1'+
                  ' fromRECO=1'+
                  ' mcInfo='+str(job['mcInfo'])+
                  ' JetCorrections='+job['jec']+
                  ' GlobalTag='+job['globalTag']+'::All'
                  ),
                crab+' -create -submit',
                crab+' -status &> crab.status',
                '']
    print '\n'.join(commands)
    os.system('\n'.join(commands))    
    return full_rpath


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
print 'Jobs will run on '+('CAF' if CAF else 'GRID')

db = conf.lockedDB()

db.connect()

job = get_jobrow( db )

setup_cmssw( job, path )

full_rpath = setup_crab( job, user, path, rpath, CAF )

if job['jsonls'] :
    setup_multicrab( job, path )

run_crab( job, path )

claim_job( db, job, user, node, path, full_rpath )

db.disconnect()
