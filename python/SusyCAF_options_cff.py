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
    options.register('scan', default = "", info = "code for CMSSM or SMS scan", mytype = VP.varType.string)
    options.register('triggers', default = -1, info = "store trigger information in the ntuple") # defaults to isData (below)
    options.register('taus', default = True, info = "store tau information in the ntuple")
    options.register('dqm', default = False, info = "store dqm information in the ntuple")
    options.register('doTauReco', default = False, info = "redo tau recostruction (needed in order to read 51X files with 52X recipe)")
    
    __hack_ListVarparsingBug__( options, 'jetCollections')
    __hack_ListVarparsingBug__( options, 'jetCorrections')
    options.parseArguments()
    options._tagOrder =[] # weird, but something to do with options.output

    #eos ls /eos/cms/store/relval/CMSSW_5_2_2/RelValTTbar/GEN-SIM-RECO/PU_START52_V4-v1/0256
    defaultGT,defaultFile = {
        "52X" : [('START52_V4::All','/store/relval/CMSSW_5_2_2/RelValTTbar/GEN-SIM-RECO/PU_START52_V4-v1/0256/1AF8A650-0B76-E111-BA3B-003048FFD76E.root'),
                 ('GR_R_52_V4::All' ,'/store/relval/CMSSW_5_2_2/DoubleMu/RECO/GR_R_52_V4_RelVal_zMu2011A-v2/0252/2A3FC019-9774-E111-87DC-002618943821.root')],
        "51X" : [('START50_V15::All','/store/relval/CMSSW_5_1_2/RelValTTbar/GEN-SIM-RECO/PU_START50_V15A-v1/0003/0AB02E79-7C61-E111-8594-002481E0D73C.root'),
                 ('GR_R_50_V12::All' ,'/store/relval/CMSSW_5_1_2/Jet/RECO/GR_R_50_V12_RelVal_jet2010B-v1/0237/326E6DA4-B460-E111-AAFA-0026189438D6.root')],
        "44X" : [('START44_V12::All','/../user/b/bbetchar//CMSSW_4_4_2_patch10/RelValProdTTbar/AODSIM/START44_V7_special_120119-v1/0088/0ECC7FA5-7A43-E111-9B36-002618943861.root'),
                 ('GR_R_44_V13::All','/../user/b/bbetchar/data/Run2011A/SingleMu/AOD/08Nov2011-v1/0001/80D61727-200D-E111-B7F4-1CC1DE0571C8.root')],
        "42X" : [('START42_V17::All','/../user/b/bbetchar/CMSSW_4_2_8/RelValProdTTbar/GEN-SIM-RECO/MC_42_V12-v1/0026/9C0E8835-9ABB-E011-95B0-0026189438BA.root'),
                 ('GR_R_42_V24::All','/store/data/Run2011B/MultiJet/AOD/PromptReco-v1/000/175/832/485ABBC8-10DC-E011-980B-BCAEC518FF8E.root')]
        }["52X"][options.isData]
    options.files = options.files if options.files else defaultFile
    options.GlobalTag = options.GlobalTag if options.GlobalTag else defaultGT

    if options.triggers < 0 : options.triggers = int(options.isData)

    if not options.isData : #remove L2L3Residual correction from simulation options
        jecs = [jc for jc in options.jetCorrections if jc!='L2L3Residual']
        options.clearList('jetCorrections')
        options.jetCorrections = jecs

    return options
