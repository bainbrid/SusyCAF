import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/511/46226E2F-AED9-DE11-AD67-001D09F248F8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/506/C65EBD2D-B3D9-DE11-BA0F-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/504/9CBA73FE-A9D9-DE11-83C4-001D09F29114.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/502/D8EDE740-A2D9-DE11-A655-001D09F27067.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/501/AADBC958-9DD9-DE11-9AD4-0019DB29C614.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/500/74CE4561-98D9-DE11-BAA9-000423D952C0.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/499/F48C8D20-67D9-DE11-AB07-001D09F2438A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/498/765B071F-67D9-DE11-94E1-001D09F23174.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/497/F06AF80C-4FD9-DE11-A8F3-001D09F291D7.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/496/7613A3F4-4CD9-DE11-8498-001D09F28E80.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/495/10DD9F6F-49D9-DE11-B132-000423D99658.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/494/12E0C86E-49D9-DE11-B73A-003048D2BE08.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/492/084C4A94-5ED9-DE11-985D-000423D94494.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/490/78C60754-47D9-DE11-802C-0030487D0D3A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/478/6C8FC69B-9CD9-DE11-BEC4-001617C3B6CE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/472/CE86888A-15D9-DE11-9F5E-000423D6CA6E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/465/6E3A22E4-0FD9-DE11-8253-000423D6BA18.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/461/048C5646-0FD9-DE11-BC62-000423D6CA72.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/458/B854C5CA-0DD9-DE11-A053-0030487A18A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/441/4A3057B3-07D9-DE11-BF40-001617C3B6CC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/413/788CF9A9-F8D8-DE11-A312-001617E30D52.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/408/606A0E49-F7D8-DE11-83F4-0030487D1BCC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/379/D8FD23E6-FCD8-DE11-9D10-001617C3B5F4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/337/F07CFC99-E3D8-DE11-8A6F-003048D3756A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/336/FA0A4DD2-E0D8-DE11-BBD8-001D09F25456.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/335/CC39AE7E-E1D8-DE11-82F5-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/334/D498C3FA-CFD8-DE11-8438-001D09F2512C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/333/347D8342-CFD8-DE11-BE6E-001617C3B70E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/E0746D05-B6D8-DE11-A01C-001D09F24DDF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/DECC1233-BAD8-DE11-873C-00304879FA4A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/A6E81BCF-B8D8-DE11-89FF-001D09F2A690.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/94079381-B9D8-DE11-8C7C-001617C3B65A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/8006E1D3-BFD8-DE11-8DBC-0030487A18A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/7C032729-B3D8-DE11-8766-001D09F248F8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/64148DBC-B1D8-DE11-8CAF-001D09F2546F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/56E36DA2-BBD8-DE11-8E57-000423D94A20.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/3225ACCB-B8D8-DE11-9F3E-001617E30F50.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/18AE5FA1-BBD8-DE11-AC62-000423D99660.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/332/14ED44E6-BAD8-DE11-AB99-0030487A18F2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/331/D413BF8D-A8D8-DE11-AB62-001D09F295FB.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/328/EC937FB4-97D8-DE11-BCB8-000423D98BC4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/328/E072940C-9ED8-DE11-8489-0019B9F72BAA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/328/3E299C5F-98D8-DE11-AD18-000423D6CA6E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/321/6A6C9919-86D8-DE11-A62D-000423D9863C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/F23EF63B-7AD8-DE11-A6AC-0019B9F72F97.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/E0E8C7BF-7DD8-DE11-93F4-001617DC1F70.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/8E6024D2-7FD8-DE11-B2FD-001D09F295A1.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/8843C649-75D8-DE11-BAED-000423D6A6F4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/24A1B63F-81D8-DE11-AFAD-003048D2C108.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/318/2222B70A-78D8-DE11-8E77-0019DB29C5FC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F62B040F-6CD8-DE11-9007-001D09F24664.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F4387297-74D8-DE11-996C-001D09F24F1F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/EE7B1AC4-6CD8-DE11-97BB-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/9264A28F-87D8-DE11-83A1-001D09F24763.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/7C7495C2-71D8-DE11-ACF2-001D09F248F8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/4CAB3B6C-6BD8-DE11-845C-000423D9890C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/02E8544C-70D8-DE11-85CF-001617C3B66C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/FEA8D781-5FD8-DE11-9FF4-001D09F2514F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/E05BA030-62D8-DE11-B188-001617C3B5F4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/DC864610-65D8-DE11-8846-003048D375AA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/D4E0C00C-65D8-DE11-9ABC-003048D37538.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/D229E872-72D8-DE11-BFA3-0019B9F704D6.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/CC1611F3-69D8-DE11-B9D3-003048D37580.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/CC007262-5FD8-DE11-B73E-001D09F24024.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/C812F841-69D8-DE11-9C8B-001D09F25401.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/C4299D9E-63D8-DE11-9C0A-000423D9863C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/C2A74F6D-66D8-DE11-8440-000423D987E0.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/BCDBAAB2-65D8-DE11-BDA0-001617E30F50.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/BC2AF296-63D8-DE11-B2D6-0030486780B8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/AC9D9BE7-5BD8-DE11-BFDC-000423D9870C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/A878CA60-5FD8-DE11-83FE-001D09F252F3.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/A695BC44-69D8-DE11-8AB9-001D09F2546F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/A637ECD0-60D8-DE11-85FB-000423D94494.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/84118396-74D8-DE11-B9A6-001D09F24FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/76AF45B2-65D8-DE11-94D4-001617C3B5F4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/70B3C10B-65D8-DE11-856C-003048D2BE12.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/6AD8F75C-5FD8-DE11-B32F-0019B9F730D2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/6A537973-5BD8-DE11-B339-001D09F2AF1E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/68B9DE5E-5BD8-DE11-AB0A-001D09F252E9.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/5465A747-5DD8-DE11-A402-001D09F2AF1E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/52CD0FB7-65D8-DE11-A00F-001D09F290BF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/4C01960D-65D8-DE11-AAB5-001D09F2960F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/3CA0854B-58D8-DE11-8BD8-001D09F25456.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/3ADF748C-68D8-DE11-9489-0030487A1990.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/2A1B6150-64D8-DE11-8B21-001D09F29321.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/280CB94F-64D8-DE11-A374-0019B9F70468.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/22110B42-5DD8-DE11-A842-001D09F2423B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/1AB4C1B0-5BD8-DE11-9259-001D09F27067.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/1A6AD76B-66D8-DE11-A1D3-000423D944FC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/301/0CEBC0A0-57D8-DE11-A764-000423D9890C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/F8137267-6BD8-DE11-B021-000423D8FA38.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/F2C61672-8CD8-DE11-918F-001D09F29321.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/EADE90F7-4FD8-DE11-A235-000423D996C8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/DC855255-4CD8-DE11-9FE0-001D09F2423B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/CA457140-8FD8-DE11-965B-000423D9863C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/C696225D-5BD8-DE11-BAEF-001D09F23944.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/C68AE910-65D8-DE11-95C7-001D09F23944.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/B84971AA-6AD8-DE11-9835-001D09F24FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/B644654E-70D8-DE11-BD66-001617C3B778.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/B2AD6AF5-4FD8-DE11-8562-001617C3B6DC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/A479F3E8-5BD8-DE11-857F-000423D9880C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/9AC15494-57D8-DE11-9AA0-000423D944F8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/8E286830-48D8-DE11-8791-001D09F2426D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/8C1CA720-86D8-DE11-AD2D-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/824DF304-57D8-DE11-92B8-003048D2BE08.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/809D7AF6-8FD8-DE11-92EF-0030487A1990.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/74073A49-75D8-DE11-9974-000423D992A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/68CC04B7-97D8-DE11-9741-000423D98834.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/6233334E-58D8-DE11-8AFD-0019B9F72BFF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/5872CB4E-58D8-DE11-AEC4-001D09F251BD.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/56043A15-52D8-DE11-B452-001D09F23A20.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/3E5BDB0C-52D8-DE11-B99D-001D09F29321.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/323DD5E8-9BD8-DE11-88FC-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/26F71EA1-82D8-DE11-8C11-001D09F2437B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/26E5DEF4-8FD8-DE11-9D10-000423D6B48C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/2068F03C-5AD8-DE11-9F9E-000423D985B0.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/2032DBC5-99D8-DE11-A353-000423D9863C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/1C1073E3-6ED8-DE11-B699-0030487A1990.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/16D8DBA2-57D8-DE11-9E29-000423D951D4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/294/0801B16D-5BD8-DE11-899E-001D09F28F0C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/293/866FE9C9-48D8-DE11-9F67-001D09F2545B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/E67D0ABE-2ED8-DE11-8EFA-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/DA174604-2ED8-DE11-BF29-000423D94A04.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/8E0102AA-33D8-DE11-B06F-000423D6006E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/7EBF14D3-30D8-DE11-9C4C-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/66EFC924-30D8-DE11-B82C-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/281/588CE495-38D8-DE11-A500-001D09F2983F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/279/E48B89F3-18D8-DE11-9971-001617DBD224.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/276/BEE4A107-14D8-DE11-9269-001D09F28EA3.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/274/5A3CE4A0-12D8-DE11-9E34-001D09F24682.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/271/DA2D06A2-19D8-DE11-AFD0-001617C3B6DC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/270/F4DACFD9-0FD8-DE11-9EE9-001617E30D52.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/270/3AEE8F9A-12D8-DE11-A7E9-001617C3B65A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/270/1C90BD84-17D8-DE11-B41B-001617E30D52.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/270/0636A826-0FD8-DE11-8724-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/EC02714F-F2D7-DE11-B94A-000423D9870C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/D8FA127F-FBD7-DE11-BFE8-001617C3B6DC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/D41FAE2D-F0D7-DE11-9E3A-000423D98DC4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/D24E0A62-00D8-DE11-BA7B-001617E30D52.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/CCE67EDE-F5D7-DE11-90AD-001617C3B6FE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/C8C61A44-EBD7-DE11-9AD7-001D09F29533.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/C4CC4EBF-F3D7-DE11-ADD3-001D09F2932B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/B67183BF-FAD7-DE11-81A1-000423D998BA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/A2C5EAB5-F8D7-DE11-A8F1-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/A06F298D-EAD7-DE11-926D-0019B9F70468.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/94578F1A-EED7-DE11-8144-001617C3B6CC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/72896F93-FDD7-DE11-AC22-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/5A482257-F9D7-DE11-9E5B-001617C3B6CE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/588598F7-F7D7-DE11-A8B0-000423D999CA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/269/04552F63-EDD7-DE11-9F7C-0019DB29C5FC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/268/C88C84E0-D8D7-DE11-8F12-001D09F26509.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/267/CE18CAF4-D3D7-DE11-946E-001D09F2527B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/266/FEE6F150-F2D7-DE11-B704-000423D9939C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/256/8A3FD20C-D6D7-DE11-BFE0-001D09F25109.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/243/DA414BB0-C1D7-DE11-B293-003048D37456.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/212/D2887D23-B0D7-DE11-995D-003048D2C108.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/195/4ABB4DCC-9BD7-DE11-A864-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/193/F6FF9993-97D7-DE11-A3EB-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/184/62DBB545-91D7-DE11-8719-0030487D0D3A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/135/3C9C2A6F-80D7-DE11-9CCD-0030487A18F2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/067/4650B03C-83D7-DE11-952D-0030487A3C9A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/056/E2C42D7B-66D7-DE11-A47B-0030487A3C9A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/054/8AE4A495-4ED7-DE11-B2B0-00304879FA4A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/048/C070B5DE-46D7-DE11-9671-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/046/E8A76FD3-38D7-DE11-B683-0030487D0D3A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/FEADB0DB-E2D6-DE11-BA79-001D09F24934.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/FE853394-10D7-DE11-8907-003048D373AE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/FC850B38-0FD7-DE11-BF09-001D09F25456.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/EEB2A4D5-31D7-DE11-A9F4-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/ECDD7758-FED6-DE11-89F4-001D09F28EA3.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/E69A8B86-32D7-DE11-81E2-001D09F2426D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/E0C990F9-22D7-DE11-A677-0019B9F72BFF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/DAB845E2-E2D6-DE11-9513-000423D6006E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/D850D767-30D7-DE11-B0BC-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/D2ED7F12-E7D6-DE11-BBEB-001D09F251D1.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/D2A08F05-36D7-DE11-98E9-0030487A18A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/CE87804F-EBD6-DE11-8974-001D09F2960F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C649727B-0ED7-DE11-836E-003048D3756A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C44C46DA-EED6-DE11-BCA3-001D09F28EC1.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C2A87639-E2D6-DE11-8FFA-001D09F2525D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C0B36C19-DBD6-DE11-B94C-000423D98834.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C053EC2C-20D7-DE11-8A1A-001D09F2437B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/C01C8A34-E9D6-DE11-96CD-001D09F24682.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/BCE21339-E9D6-DE11-A296-001D09F28E80.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/BA3415D6-31D7-DE11-AA62-0030487A3C9A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B8CAD577-0ED7-DE11-B8A1-003048D37538.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B870AB21-EED6-DE11-A10B-001D09F24682.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B62923CA-2AD7-DE11-BAB0-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B620B4BD-FFD6-DE11-8204-001D09F290BF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B4DBCB5C-FED6-DE11-A360-0019B9F704D6.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/B0DB2111-F3D6-DE11-A45E-001D09F23D1D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/AE05B1EC-E2D6-DE11-B289-000423D9989E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/A64FCF72-EDD6-DE11-B386-001D09F27003.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/A64C029B-EAD6-DE11-A4E1-001D09F2932B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/A4C4BB4E-16D7-DE11-8555-001D09F2983F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/9298B833-27D7-DE11-9D1D-001617C3B6CC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/90A1C84E-EBD6-DE11-8521-003048D3756A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/90119A76-E1D6-DE11-928F-001D09F2AD84.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/900953C2-F3D6-DE11-857E-001D09F2AD7F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/8E600D83-32D7-DE11-9F17-001617C3B66C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/8E39B5E3-E2D6-DE11-9DC9-000423D94E70.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/8CEFF6E8-0FD7-DE11-A1E4-001D09F244DE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/8AEB9339-E2D6-DE11-B437-001D09F23944.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/88F60982-E8D6-DE11-94E1-001D09F24600.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/889B2F94-E3D6-DE11-BD15-000423D98750.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/8405FA21-EED6-DE11-A4C3-001D09F26509.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/802EEA88-EFD6-DE11-8C4B-001D09F2525D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7EBD0325-EED6-DE11-BB87-001D09F2441B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7E9B6DC8-2AD7-DE11-9598-001617C3B66C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7E0DD5DA-EED6-DE11-9036-001D09F27003.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/784009C9-E0D6-DE11-A024-001D09F28F0C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/76BF0DEC-F0D6-DE11-B78D-003048D37456.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7683CBBF-FFD6-DE11-84E4-001D09F28EC1.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/760C5AC0-ECD6-DE11-8003-001D09F29533.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7602DF48-16D7-DE11-9256-001D09F25401.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/7072BC40-F0D6-DE11-BF91-000423D94494.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/706A87EA-0FD7-DE11-A93A-001D09F23C73.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/68F1E524-EED6-DE11-9146-001D09F24D8A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/665FFFDA-20D7-DE11-A94B-001D09F297EF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/64EA97C8-2AD7-DE11-A2BB-0019DB29C5FC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/5CE63BD6-EED6-DE11-9F8E-001D09F2423B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/56D5AF7C-0ED7-DE11-9499-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/563FB93A-E2D6-DE11-B8EC-001D09F25041.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/54614774-E1D6-DE11-B5CF-001D09F26C5C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/54566736-0FD7-DE11-9B85-003048D37580.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/4CBB2279-0ED7-DE11-92CC-0030487D0D3A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/44F258F2-16D7-DE11-AFA4-0030487A1990.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/44C4526F-00D7-DE11-B954-001D09F232B9.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/449F778C-15D7-DE11-B054-001D09F290BF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/442009E9-0FD7-DE11-9F3A-001D09F28F11.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/42F16603-ECD6-DE11-9B71-001D09F291D2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/402027D7-20D7-DE11-90D8-001D09F2516D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/3AC13E41-F0D6-DE11-8462-003048D2BE12.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/32B399CB-2AD7-DE11-912D-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/2EAFF771-EDD6-DE11-82CD-001D09F24600.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/2A71C93D-E2D6-DE11-AF2C-001D09F2A49C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/1C93E784-DCD6-DE11-9F63-001D09F2546F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/1C5D8BE3-E2D6-DE11-9A6F-001D09F2AD84.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/1C41CE6D-EBD6-DE11-9AFE-001D09F24FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/187DDD7C-2BD7-DE11-AC24-0019DB29C614.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/148EF6EA-0FD7-DE11-B388-001D09F252E9.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/12EF11D6-31D7-DE11-8A3B-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/124F1D22-EED6-DE11-A5EA-001D09F2546F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/10532D77-E1D6-DE11-BFD2-001D09F25393.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/0C71FEAD-23D7-DE11-82AA-001D09F29169.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/0C09EB33-0FD7-DE11-B94B-001D09F29114.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/08BC127C-0ED7-DE11-A3C6-003048D373AE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/088E5013-E0D6-DE11-8285-000423D98BE8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/062A02D5-31D7-DE11-B163-001617C3B706.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/0495D340-F0D6-DE11-BFBC-0030486730C6.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/045/02A386D1-31D7-DE11-956A-001617E30F50.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/F672C63B-DDD6-DE11-8E2F-000423D991D4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/E66E2629-D6D6-DE11-8887-001617DC1F70.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/E650B270-DAD6-DE11-B018-0030487A3232.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/E21D7E6D-DAD6-DE11-BC8E-0030487A18F2.root' ] );
readFiles.extend( [

       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/D6BC0779-DAD6-DE11-B4A0-000423D99896.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/D4AC9321-DBD6-DE11-9174-003048D2C108.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/CEF813B7-D9D6-DE11-8E48-003048D2C0F4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/C41BC370-DAD6-DE11-A374-0030487A18A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/C067AC55-A6D6-DE11-B42A-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/AE9DBFD1-D4D6-DE11-8442-000423D6CA02.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/AC17E610-D9D6-DE11-A879-001D09F251B8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/A2FCD071-DAD6-DE11-803D-0030487C6090.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/A076213D-DDD6-DE11-95F4-000423D98834.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/9A81B55D-D3D6-DE11-B49F-001D09F28755.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/9A1E6CB8-D9D6-DE11-BACE-001617C3B6CC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/7C06BEEA-D6D6-DE11-BF97-001D09F25401.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/72B4FBCF-E7D6-DE11-BE9F-001D09F2932B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/6E289E70-DAD6-DE11-8B8A-000423D99F1E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/6C3FCD72-DAD6-DE11-BBFD-0030487D1BCC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/5E841B7A-DAD6-DE11-9C87-000423D991D4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/5CA05711-D9D6-DE11-B25D-0019B9F72BFF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/5A9531C1-D4D6-DE11-AF97-001D09F290BF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/58F9F8D1-DBD6-DE11-ABC1-0019B9F72BAA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/581E4F8F-DAD6-DE11-80A3-000423D98B6C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/4E836B72-DAD6-DE11-8168-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/4AF3F211-D9D6-DE11-881E-001D09F24F1F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/4A9F94D5-DBD6-DE11-A760-001D09F28F0C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/48EE0FB5-D9D6-DE11-A065-001617C3B706.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/42E88E7D-D5D6-DE11-A478-001D09F28E80.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/40F8F9D5-DBD6-DE11-9C90-001D09F251B8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/3E792220-DBD6-DE11-94BA-001D09F24F1F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/3C4904B8-D9D6-DE11-9157-001D09F2426D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/24D79271-DAD6-DE11-BF00-001D09F2A49C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/0EADE671-DAD6-DE11-AEC1-0030487A1990.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/0C4A98C1-D4D6-DE11-9950-001D09F28755.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/0C18C7BA-D9D6-DE11-9DB4-001D09F24F65.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/0A58DE10-D9D6-DE11-8CCC-001D09F26509.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/0654C373-DAD6-DE11-B954-0016177CA778.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/04AF9872-DAD6-DE11-A35C-000423D985B0.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/023/04253F9B-EAD6-DE11-96FB-001D09F252F3.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/011/D24D4D69-9AD6-DE11-A7A9-0030487A322E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/004/B8F8CF7D-95D6-DE11-A2F5-001617E30F50.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/999/2621ACDB-88D6-DE11-903C-003048D373AE.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/998/40D3E2CD-7AD6-DE11-950D-0030487C5CFA.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/964/A0B7B34A-43D6-DE11-848D-0016177CA778.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/963/D861B18C-21D6-DE11-81C9-0016177CA778.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/962/CE062D41-2ED6-DE11-BDB2-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/960/52B35507-1ED6-DE11-A795-000423D9989E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/949/5A9671D2-19D6-DE11-A372-00304879FBB2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/943/3C83AB0D-12D6-DE11-9280-001D09F2525D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/942/64AAACE6-01D6-DE11-BCE7-001D09F28F0C.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/941/7E1B6C47-FCD5-DE11-A343-001D09F25393.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/939/76CA15D4-19D6-DE11-92A4-0030487D0D3A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/935/C22BB2F5-08D6-DE11-93FC-001D09F2546F.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/931/C8397BA3-F6D5-DE11-B1FB-001D09F25109.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/928/9C6D41C9-F3D5-DE11-9AE6-001617E30F48.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/926/82B96A37-EED5-DE11-A32E-001D09F251BD.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/925/FEF4ADCA-ECD5-DE11-851D-001D09F2525D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/921/8E809AE8-EED5-DE11-82ED-0019B9F72BFF.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/912/7E93913A-EED5-DE11-B9DC-001617DC1F70.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/877/3E999BE8-01D6-DE11-AA3D-003048D37538.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/871/2887738C-F4D5-DE11-8B59-0030487A1FEC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/861/C6998F9E-CDD7-DE11-8478-001D09F2906A.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/855/E848C19C-CED5-DE11-B3CA-000423D99A8E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/851/5A447D38-CDD5-DE11-BEC5-001D09F248F8.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/849/CEE4E4BA-F1D5-DE11-A2EB-001D09F24D4E.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/847/EC1B4166-FED5-DE11-9D0C-001D09F2437B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/844/DE6B2F28-F3D5-DE11-9A70-001D09F2545B.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/841/9852B6C8-9ED5-DE11-8004-001D09F241F0.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/837/FC25C23D-9BD5-DE11-890B-000423D99658.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/835/3CD68101-AAD5-DE11-B6CD-001D09F291D7.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/835/30603EA9-95D5-DE11-8253-000423D99AA2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/833/46B0FB61-BED5-DE11-AC4A-001D09F231C9.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/819/58E5CA0F-78D5-DE11-A1CC-001D09F29321.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/805/6A8C4088-7BD5-DE11-99CC-000423D99394.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/796/8CEE0EC0-78D5-DE11-8CC8-000423D987FC.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/740/5C3FB192-6FD5-DE11-9C77-001D09F252F3.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/718/5403BC77-5AD5-DE11-9ACB-0030487A18F2.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/713/7E82B45A-58D5-DE11-A232-001D09F295A1.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/709/D87A29E5-56D5-DE11-9290-0030487A18A4.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/677/228A1E3D-5BD5-DE11-9537-001D09F2462D.root',
       '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/121/672/E6222692-10D5-DE11-B0E4-001617C3B6CE.root' ] );


secFiles.extend( [
               ] )


