def __hack_ListVarparsingBug__(options,item) :
    val = getattr(options,item)
    if len(val) and type(val[0]) is list :
        tmp = val[0]
        options.clearList(item)
        setattr(options,item, tmp)

def options() :
    from FWCore.ParameterSet.VarParsing import VarParsing as VP
    options = VP('standard')
    options.output = "SusyCAF_Tree.root"
    options.secondaryOutput = "" #switch PAT-tuple output off by default
    options.maxEvents = 100

    options.register('GlobalTag', mytype = VP.varType.string)
    options.register('quiet', default = True )
    options.register('isData', default = True )
    options.register('dropMore', default = False , info = "drop more for a smaller event size")
    options.register('leptonPtMin', default = 0 )
    options.register('patify', default = True,  info = "run SUSYPAT on the fly")
    options.register('AllTracks', default = False, info = "include all tracks")
    options.register('SourceName', info = "'S:stream' or 'DS:dataset' to store those HLT paths", mytype = VP.varType.string,)
    options.register('jetCollections', default = ['ak5calo','ak5pf'], # + ['ak7calo','ak7pf','ak5pf2pat','ak7pf2pat']
                     info = "jet types to store", mult = VP.multiplicity.list, mytype = VP.varType.string)
    options.register('jetCorrections', default = ['L1FastJet','L2Relative','L3Absolute','L2L3Residual'], #L2L3Residual removed from options for simulation (below)
                     info = "jet correction levels to apply", mult = VP.multiplicity.list, mytype = VP.varType.string)
    options.register('hbheNoiseFilterDefaultIsoReq', default = True , info = "Configure the HBHE noise filter to use default isolation requirements")
    options.register('scan', default = "", info = "code for CMSSM or SMS scan", mytype = VP.varType.string)
    options.register('triggers', default = -1, info = "store trigger information in the ntuple") # defaults to isData (below)
    options.register('taus', default = True, info = "store tau information in the ntuple")
    
    __hack_ListVarparsingBug__( options, 'jetCollections')
    __hack_ListVarparsingBug__( options, 'jetCorrections')
    options.parseArguments()
    options._tagOrder =[] # weird, but something to do with options.output

    defaultGT,defaultFile = {
        "44X" : [('START44_V12::All','/store/mc/Fall11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/RecoTest_PU_S5_START44_V4-v1/0000/F474926B-AACF-E011-B064-0018F3D0960C.root'),
                 ('GR_R_44_V13::All','/store/data/Run2011B/MultiJet/AOD/PromptReco-v1/000/175/832/485ABBC8-10DC-E011-980B-BCAEC518FF8E.root')],
        "42X" : [('START42_V17::All','/../user/b/bbetchar/CMSSW_4_2_8/RelValProdTTbar/GEN-SIM-RECO/MC_42_V12-v1/0026/9C0E8835-9ABB-E011-95B0-0026189438BA.root'),
                 ('GR_R_42_V24::All','/store/data/Run2011B/MultiJet/AOD/PromptReco-v1/000/175/832/485ABBC8-10DC-E011-980B-BCAEC518FF8E.root')]
        }["44X"][options.isData]
    options.files = options.files if options.files else defaultFile
    options.GlobalTag = options.GlobalTag if options.GlobalTag else defaultGT

    if options.triggers < 0 : options.triggers = int(options.isData)

    if not options.isData : #remove L2L3Residual correction from simulation options
        jecs = [jc for jc in options.jetCorrections if jc!='L2L3Residual']
        options.clearList('jetCorrections')
        options.jetCorrections = jecs

    return options
