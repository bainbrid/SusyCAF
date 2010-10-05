import sqlite3,os,sys,getpass,time

def print_HEAD(file,name) :
    print>>file, '''
    <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
    <html>
    <head> 
    <title> %s Datasets </title>'''%name +'''
    <style type="text/css">
    <!--
    body {
    text-align:left;
    margin-left:30px;
    }
    .tagwrapper {
    text-align:left;
    margin:0 auto;
    border:1px solid #ccc;
    padding-left:30px;
    padding-right:10px;
    padding-bottom:5px;
    }
    .dsetwrapper {
    text-align:left;
    margin:0 auto;
    border:1px solid #ccc;
    padding-left:30px;
    padding-right:10px;
    padding-bottom:5px;
    }
    .jobwrapper {
    text-align:left;
    margin:0 auto;
    border:1px solid #ccc;
    padding-left:30px;
    padding-right:10px;
    padding-bottom:5px;
    }
    a {
    color:blue;
    cursor:pointer;
    }
    .Processing {
    color:black;
    background-color:yellow;
    }
    .Unclaimed {
    color:black;
    background-color:red;
    }
    .Complete {
    color:black;
    background-color:#00FF00;
    }
    -->
    </style>
    
    <script type="text/javascript">
    <!--
    function switchMenu(obj) {
    var el = document.getElementById(obj);
    if ( el.style.display != "none" ) {
         el.style.display = \'none\';
    }
    else {
         el.style.display = '';
    }
    }
    var jobSwitches = new Array();
    var dsetSwitches = new Array();
    var tagSwitches = new Array();

    function switchAll(items) {
      for( var i=0; i < items.length; i++) {
        switchMenu(items[i])
      }
    }
    //-->
    </script>

    </head>
    <body>
    '''
    return
    

def print_FOOT(file) :
    print>>file,'''<script type="text/javascript"><!--
    switchAll(jobSwitches)
    switchAll(dsetSwitches)
    switchAll(tagSwitches)
    //-->
    </script>
    </body></html>'''

def print_JOB(file,job) :
    label = 'job%d' % job['rowid']
    print>>file,'\n'.join([
        '''<script type="text/javascript"><!--
        jobSwitches.push(\'%s\');//-->
        </script>'''%label,
        '<br><a onclick="switchMenu(\'%s\');" class="%s">' % (label,job['state']),
        "%d:"%job['rowid'],
        '</a>',
        "&nbsp;%s" %((job['rpath'] if job['rpath'] else 'Unclaimed')),
        '<div id="%s" class=jobwrapper>' % label,
        ('<br>'+job['user']+'@'+job['node']+':'+job['path']) if job['user'] else '',
        ('<br>Dashboard: ' + ', '.join(['<a href="%s">Job%d</a>' % (item, index) for index,item in enumerate(job['dash'].split(',')) ])) if job['dash'] else '',
        '<br>'+job['jsonls'] if job['jsonls'] else ''
        ])
    print>>file,'</div>'
    return

def print_DSET(file,db,dset,tagid) :
    label= 'dset%d_%d' % (dset['rowid'],tagid)
    jobs = db.execute('select rowid,* from job where dsetid=? and tagid=? order by user',(dset['rowid'],tagid)).fetchall()
    if len(jobs)>0 :
        print>>file,'\n'.join([
            '''<script type="text/javascript"><!--
            dsetSwitches.push(\'%s\');//-->
            </script>'''%label,
            '<br><a onclick="switchMenu(\'%s\');">' % label,
            (10*'&nbsp;').join(['<b>%s</b>','%s','%s','%s','%s']) % (dset['dataset'].replace(",","<br>"),
                                                                     dset['globalTag'],
                                                                     dset['jec'],
                                                                     dset['filter'] if dset['filter'] else '',
                                                                     dset['otherOptions'] if dset['otherOptions'] else ''),
            '</a>',
            '<div id="%s" class=dsetwrapper>' % label,
            ])
        for job in jobs:
            print_JOB(file,job)
        print>>file,'</div>'
    return

def print_TAG(file,db,tag) :
    label = 'tag%d' % tag['rowid']
    print>>file,'\n'.join([
        '''<script type="text/javascript"><!--
        tagSwitches.push(\'%s\');//-->
        </script>'''%label,
        '<a onclick="switchMenu(\'%s\');">' % label,
        '<b>'+tag['cmssw']+':'+10*'&nbsp;'+'</b>'+tag['susycaf'],
        '</a>',
        '<div id="%s" class=tagwrapper>' % label,
        ])
    if tag['addpkg'] : print>>file, '\n'.join(['<br>addpkg '+i for i in tag['addpkg'].split(',')])
    if tag['cvsup'] : print>>file, '\n'.join(['<br>cvs up -r '+i for i in tag['cvsup'].split(',')])
    if tag['cmds'] : print>>file, '\n'.join(['<br>'+i for i in tag['cmds'].split(';')])
    print>>file,'<br><br>'
    for dset in db.execute('select rowid,* from dset order by globaltag, dataset').fetchall() :
        print_DSET(file,db,dset,tag['rowid'])
    print>>file,'</div>'
    return

def print_BODY(file,db) :
    print>>file,'''
    <div><div><a onclick="switchAll(tagSwitches);">Toggle Tags</a></div>
    <div><a onclick="switchAll(dsetSwitches);">Toggle Datasets</a></div>
    <div><a onclick="switchAll(jobSwitches);">Toggle Jobs</a></div></div>
    '''
    for tag in db.execute('select rowid,* from tag order by rowid desc').fetchall() :
        print>>file,'<p>'
        print_TAG(file,db,tag)
        print>>file,'</p>'
    return

def write_webpage(db,path,name) :
    file = open(path,"w")
    print_HEAD(file,name)
    print_BODY(file,db)
    print_FOOT(file)
    file.close()
    return
