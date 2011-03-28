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
    options.register('jetCollections', default = ['ak5calo','ak5pf','ak5pf2pat','ak7calo','ak7pf','ak7pf2pat'],
                     info = "jet types to store", mult = VP.multiplicity.list, mytype = VP.varType.string)
    options.register('jetCorrections', default = ['L2Relative','L3Absolute'],
                     info = "jet correction levels to apply", mult = VP.multiplicity.list, mytype = VP.varType.string)

    __hack_ListVarparsingBug__( options, 'jetCollections')
    __hack_ListVarparsingBug__( options, 'jetCorrections')
    options.parseArguments()
    options._tagOrder =[] # weird, but something to do with options.output

    defaultGT,defaultFile = (
        [('START311_V2::All','/store/relval/CMSSW_4_1_2/RelValTTbar_Tauola/GEN-SIM-RECO/START311_V2_PU_E7TeV_AVE_2_BX156-v1/0028/104008AF-9846-E011-A794-0026189438EB.root'),
         ('GR_R_311_V2::All','/store/data/Run2011A/MultiJet/AOD/PromptReco-v1/000/160/943/06FEF977-FD54-E011-B367-001D09F2438A.root')]
        )[options.isData]
    options.files = options.files if options.files else defaultFile
    options.GlobalTag = options.GlobalTag if options.GlobalTag else defaultGT
    return options


