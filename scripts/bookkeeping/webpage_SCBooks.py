import sqlite3,os,sys,getpass,time

def write_webpage(db,path) :
    c=db.cursor()
    file = open(path,"w")
    print>>file, '''
    <html>
    <head> <title> SusyCAF Datasets </title> </head>
    <body>
    '''
    tags = c.execute('select rowid,* from tag').fetchall()
    for tag in tags:
        print>>file,'<BR>',tag['cmssw']
        print>>file,'<table>'
        dsets = c.execute('select rowid,* from dset').fetchall()
        for dset in dsets:
            jobs = c.execute('select * from job where dsetid=? and tagid=?',(dset['rowid'],tag['rowid'])).fetchall()
            if len(jobs)>0 :
                print>>file,'<tr><td>'+'</td><td>'.join([str(i) for i in dset])+'</td></tr>'
            for job in jobs:
                pass
        print>>file,'</table>'
    
    print>>file,'''
    </body>
    </html>
    '''
    file.close()
    c.close()
