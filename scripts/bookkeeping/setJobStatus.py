#!/usr/bin/env python

import configuration_SCBooks as conf,sys,os,readline,getpass

user = getpass.getuser()
db = conf.lockedDB()
db.connect()

rows = db.execute('''select job.rowid,state,dataset,cmssw,susycaf,jec,globalTag,filter
                     from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                     where user="'''+user+'''" order by state,job.rowid''').fetchall()
for row in rows:
    print '\t'.join([str(item) for item in row])
jobnumber = raw_input("\n\n\tWhich job?  ")
if not jobnumber in [str(row['rowid']) for row in rows] :
    print jobnumber+' is not and `Unclaimed` job'
    db.disconnect()
    sys.exit()


state = ["Unclaimed","Processing","Complete"]
print '\n'.join([str(i)+' : '+state[i] for i in range(len(state))])
i = input("\n\nWhich state?  ")
if not i in range(len(state)) :
    print str(i)+' is not a valid state'
    db.disconnect()
    sys.exit()


db.execute('update job set state="'+state[i]+'" where rowid='+jobnumber)
db.disconnect()

