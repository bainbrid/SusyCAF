#!/usr/bin/env python

#Generates psets
#Uses 'lcg-ls' which requires grid to be sourced and a valid grid proxy (voms-proxy-init)
#Does not add the correct crosssections, this will need to be done by hand.

import commands

import configuration_SCBooks as conf,sys,os,readline,getpass,string,fileinput,socket,datetime,re

#Connect to database
user = getpass.getuser()
db = conf.lockedDB()
db.connect()

paths=[]
shortNames=[]
xsecs=[]

#Return users jobs
rows = db.execute('''select job.rowid,state,path,dataset,rpath,node
                     from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                     where user="'''+user+'''" order by state,path''').fetchall()
for row in rows:
    print ('\t'.join([str(item) for item in row]))[0:90]+"..."
jobnumber = raw_input("\n\n\tWhich job?  ")

#get path and short name from user's selected job
for row in rows:
	if jobnumber == str(row['rowid']):
		datasets = (row['dataset']).split(',')
		if len(datasets) > 1 :
			for dset in datasets :
				path = (row['rpath'])+'/'+string.replace(dset[1:], '/', '.')
				paths.append(path)
				shortName = (string.split(dset, '/'))[1] + "_" + (string.split(dset, '/'))[2]
				shortName = string.replace(shortName,'-','_')
				shortNames.append(shortName)
				xsecs.append(0.0)
				#Would be nice if this information was in the database.
		else :
			dset = datasets[0]
			path = (row['rpath'])
			paths.append(path)
			shortName = (string.split(dset, '/'))[1] + "_" + (string.split(dset, '/'))[2]
			shortName = string.replace(shortName,'-','_')
			shortNames.append(shortName)
			xsecs.append(0.0)
		break
		
#disconect from database
db.disconnect()

#loop over datasets in job
for path, shortName, xsec in zip(paths, shortNames, xsecs) :

	print "Generating " + shortName + '.py'

	prefix = '\n' + '\t' +  "\"dcap://gfe02.grid.hep.ph.ic.ac.uk:22128/"# + path + '/'
	suffix = '\" ,'

	#ls DCAHCE
	temp = commands.getstatusoutput("lcg-ls srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN=" + path + "/")

	#Succesful?
	if temp[0] != 0 :
		print "\tError occured:"
		print temp
		break
	
	#split up chunk of text in to array of filenames
	infile = temp[1].split('\n')
	infile.sort()

	#Remove duplicate files
	toRemove = []
	for i,line1 in enumerate(infile[:-1]) : 
		if (((line1.split('/'))[-1]).split('_'))[2] == (((infile[i+1].split('/'))[-1]).split('_'))[2] :
			toRemove.append(i)
	toRemove.sort()
	toRemove.reverse()
	for i in toRemove :
		del infile[i]

	#Write PSet
	outfile = open(shortName+'.py','w')
	
	#header
	header = '\n'.join([
		'from icf.core import PSet',
		'',
		'%s=PSet(' % shortName,
		'\tName=\"%s\",' % shortName,
		'\tFormat=(\"ICF\",2),',
		'\tFile=['
		])
	outfile.write(header)

	#body
	filenames = []
	for line in infile : 
		line = line.rstrip()
		line = prefix + line + suffix 
		filenames.append(line)
	for line in filenames :
		outfile.write(line)

	#footer
	footer = '\n'.join([
		'',
		'\t],',
		'\tCrossSection=%d,' % xsec,
		')'
		])
	outfile.write(footer)