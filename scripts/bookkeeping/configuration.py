import sqlite3,os,sys,getpass,time

db_location = "/afs/cern.ch/cms/CAF/CMSPHYS/PHYS_SUSY/SusyCAF/bookkeeping/"
db_file = 'sqlite.db'
db_lock = 'sqlite.lock'

def create_db(path) :
    conn = sqlite3.connect(path)
    conn.execute('''CREATE TABLE tag( cmssw   TEXT NOT NULL,
                                      susycaf TEXT NOT NULL,
                                      addpkg  TEXT,
                                      cvsup   TEXT
                                     )''')
    conn.execute('''CREATE TABLE dset( dataset   TEXT NOT NULL,
                                       globalTag TEXT NOT NULL,
                                       jec       TEXT NOT NULL,
                                       mcInfo    BOOLEAN DEFAULT 0 NOT NULL,
                                       filter    TEXT
                                      )''')
    conn.execute('''CREATE TABLE job( tagid  INT NOT NULL,
                                      dsetid INT NOT NULL,
                                      jsonls TEXT,
                                      state  TEXT DEFAULT \'Unclaimed\',
                                      user   TEXT,
                                      node   TEXT,
                                      path   TEXT,
                                      rpath  TEXT,
                                      dash   TEXT
                                     )''')
    conn.commit()
    print path, 'successfully created with tables.'

def valid_keys(connection) :
    valid_tagid = [row[0] for row in connection.execute('select rowid from tag')]
    valid_dsetid = [row[0] for row in connection.execute('select rowid from dset')]
    for row in connection.execute('select tagid,dsetid from job') :
        if row['tagid'] not in valid_tagid: return False
        if row['dsetid'] not in valid_dsetid: return False
    return True

def valid_addpkg(connection) :
    for row in connection.execute('select addpkg from tag') :
        if row[0] != None and len(row[0].split())%2 !=0 :
            print 'Incorrect addpkg format'
            return False
    return True

def duplicates(connection, table) :
    if len(['' for row in connection.execute('select * from '+table)]) >  len(['' for row in connection.execute('select distinct * from '+table)]) :
        print table,'contains duplicate rows'
        return True
    return False

def valid_json(connection) :
    return True

def valid_db(connection) :
    if not valid_keys(connection) :
        print 'Some jobs have invalid tagid or dsetid'
        return False
    if not valid_addpkg(connection) :  return False
    if not valid_json(connection) :    return False
    if duplicates(connection,'tag') :  return False
    if duplicates(connection,'dset') : return False
    if duplicates(connection,'job') :  return False
    return True


def create_db_lock(path) :
    lockfile = open(path, "w")
    print>>lockfile, getpass.getuser()
    lockfile.close()

class lockedDB:
    def __init__(self):
        self.conn = 0
        self.locktime = 0
        
    def connect(self):
        if not os.path.exists(db_location) :
            print 'Cannot find database:', db_location, 'is not a valid directory'
            sys.exit()
            
        lockpath = db_location+'/'+db_lock
        if os.path.exists(lockpath) :
            user = open(lockpath).readline()[:-1]
            print "\nDatabase locked by %s %0.1f minutes ago." % (user, (time.time()-os.path.getmtime(lockpath))/60)
            input = raw_input("Break lock? [n] ")
            if not input or input[0] != 'y' :
                sys.exit()
        create_db_lock(lockpath)
        self.locktime = os.path.getmtime(lockpath)

        path = db_location+'/'+db_file
        if not os.path.exists(path) :
            input = raw_input('Cannot find database in '+db_location+'.  Create it now? [y/n] ')
            if input and input[0] in ['y','Y']:
                create_db(path)
            else :
                print 'No action taken'
                self.disconnect()
                sys.exit()
        self.conn = sqlite3.connect(path)
        self.conn.row_factory = sqlite3.Row

    def secure(self):
        lockpath = db_location+'/'+db_lock
        if os.path.exists(lockpath) :
            user = open(lockpath).readline()[:-1]
            locktime = os.path.getmtime(lockpath)
            if locktime == self.locktime and user == getpass.getuser() : return True
        return False

    def save(self):
        secure = self.secure()
        valid = valid_db(self.conn)
        if not secure :
            print 'Database not locked : not saved'
        else :
            if not valid :
                print 'Invalid database : not saved'
            else :
                self.conn.commit()
                print 'Saved'

    def disconnect(self):
        input = raw_input("Save before disconnecting? [y]")
        if input=='' or input[0]=='y' or input[0]=='Y' :
            self.save()
        else :
            print 'Not saved'
        if self.secure() : os.remove(db_location+'/'+db_lock)
        self.conn=0
    
    def execute(self,one): return self.conn.execute(one)
    def cursor(self): return self.conn.cursor()

