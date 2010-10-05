#!/usr/bin/env python
import configuration_SCBooks as conf,sqlite3,readline,sys

def menu(actions) :
    s = '\n\t'
    for key in actions:
        s += '['+key+']'+actions[key][0]+'\n\t'
    s += '--> '
    actions.get(raw_input(s),('', lambda: menu(actions)))[1]()
    menu(actions)

class planner:
    def __init__(self):
        self.db = conf.lockedDB()
        self.db.connect()
        
        self.mainM = {
            "q": ("uit", self.quit),
            "s": ("ave", self.db.save),
            "t": ("ags", lambda : menu(self.tagM)),
            "d": ("atasets", lambda : menu(self.dsetM)),
            "j": ("obs", lambda : menu(self.jobM))
            }
        self.tagM = {
            "m": ("ain", lambda : menu(self.mainM)),
            "l": ("ist tags", lambda : self.list_entries('select rowid,* from tag')),
            "n": ("ew tag", lambda : self.new_entry('tag')),
            "d": ("elete", lambda : self.delete_row('tag'))
            }
        self.dsetM = {
            "m": ("ain", lambda : menu(self.mainM)),
            "l": ("ist datasets", lambda : self.list_entries('select rowid,* from dset')),
            "n": ("ew dataset", lambda : self.new_entry('dset')),
            "d": ("elete", lambda : self.delete_row('dset'))
            }
        self.jobM = {
            "m": ("ain", lambda : menu(self.mainM)),
            "l": ("ist jobs", lambda : self.list_entries('select rowid,tagid,dsetid,jsonls from job')),
            "L": ("ist jobs (resolve keys)",
                  lambda : self.list_entries('''select job.rowid,dset.dataset,tag.cmssw,dset.globalTag,tag.susycaf,dset.otherOptions
                                                       from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid''')),
            "d": ("elete", lambda : self.delete_row('job')),
            "n": ("ew job", lambda : self.new_entry('job','tagid,dsetid,jsonls'))
            }

    def run(self) :
        menu(self.mainM)
        
    def quit(self) :
        self.db.disconnect()
        sys.exit()        

    def list_entries(self,select) :
        rows = self.db.execute(select).fetchall()
        if len(rows)>0 :
            print rows[0].keys()
        for row in rows :
            print '\t\t'.join([str(item) for item in row])

    def new_entry(self,table,cols='*') :
        c = self.db.cursor()
        c.execute("select "+cols+" from "+table)
        inputs = []
        for item in c.description :
            input = raw_input(item[0]+": ")
            if item[0]=='jsonls' and len(input)>4 and input[-4:]=='.txt' :
                input = open(input).readline()
            if item[0]=='mcInfo' and input!='' :
                input = True if input in [True,'True',1,'1'] else False
            if input!='' :
                inputs.append( (item[0],input) )
        if raw_input("Enter 'y' to continue: ")=='y' :
            c.execute("insert into "+
                      table     +'('+','.join([i[0] for i in inputs])+')'+
                      " values "+'('+','.join(['?'  for i in inputs])+')',
                      tuple([item[1] for item in inputs]))
            print 'Added',table, inputs
        else :
            print "Did not add", table
        c.close()

    def delete_row(self,table) :
        rowid = raw_input("delete rowid: ")
        self.db.execute("delete from "+table+" where rowid="+rowid)
        if table!='job' :
            self.db.execute("delete from job where "+table+"id="+rowid)

planner().run()
