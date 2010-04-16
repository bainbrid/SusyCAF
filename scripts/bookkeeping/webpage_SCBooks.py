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
        print>>file,'<b>'+(10*'&nbsp;').join([str(i) for i in tag])+'</b><br>'
        dsets = c.execute('select rowid,* from dset order by globaltag').fetchall()
        for dset in dsets:
            jobs = c.execute('select * from job where dsetid=? and tagid=?',(dset['rowid'],tag['rowid'])).fetchall()
            if len(jobs)>0 :
                print>>file,'<br>'+(10*'&nbsp;').join([str(i) for i in dset])
            for job in jobs:
                print>>file,'\n<br><a href='+'>Job</a>\n<br><a href='.join(job['dash'][1:-1].split(','))+'>Job</a>'
    
    print>>file,'''
    </body>
    </html>
    '''
    file.close()
    c.close()
