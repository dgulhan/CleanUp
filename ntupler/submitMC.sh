#!/bin/sh
version=1
#pp data

#dataset=/mnt/hadoop/cms/store/user/abaty/transferTargetDirectories//2015pp_HighPtJet80/
#dataset=/mnt/hadoop/cms/store/user/abaty/transferTargetDirectories/2015pp_HighPtLowerJets/
#dataset=/mnt/hadoop/cms/store/user/abaty/transferTargetDirectories/2015pp_MinBias6/
#dataset=/mnt/hadoop/cms/store/user/abaty/transferTargetDirectories/2015pp_MinBias_2
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias1/Minbias1/170117_115040/000${1}/
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias3/Minbias3/170117_120149/000${1}/
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias4/Minbias4/170117_120639/000${1}/
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias5/Minbias5/170118_084555/000${1}
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias7/Minbias7/170119_095502/000${1}
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias8/Minbias8/170119_095621/000${1}
#dataset=/mnt/hadoop/cms/store/user/ginnocen/2015-Data-promptReco_Minbias_allHLTMB/MinimumBias9/Minbias9/170119_101826/000${1}
#destination=/mnt/hadoop/cms/store/user/dgulhan/ppDijet/20160408/minbias2_ak4PF_eta3_corr

##pp hi reco
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD120_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164522/000${1}/
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD15_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164101/000${1}/
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD170_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164554/000${1}   
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD220_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164635/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD30_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164245/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD370_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164811/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD50_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164411/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/HiForest_PYTHIA_QCD80_TuneCUETP8M1_cfi_RECODEBUGHI_757p1_timeslew_HcalRespCorrs_v4_00_mc_v2/160705_164439/000${1}


##pp files
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet15_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_125350/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet30_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133336/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet50_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133347/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet80_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133359/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet120_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133414/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet170_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133425/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet220_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133441/000${1}/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet280_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133453/0000/
#dataset=/mnt/hadoop/cms/store/user/krajczar/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/Pythia8_Dijet370_pp_TuneCUETP8M1_5020GeV_FOREST_758_PrivMC/160119_133505/000${1}/

#pp official
#dataset=/mnt/hadoop/cms/store/user/dgulhan//Pythia8_Dijet15_pp502_TuneCUETP8M1/PYTHIA_QCD15_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/160826_084701/000${1}/
#dataset=/mnt/hadoop/cms/store/user/dgulhan//Pythia8_Dijet30_pp502_TuneCUETP8M1/PYTHIA_QCD30_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/160826_084724/000${1}/
#dataset=/mnt/hadoop/cms/store/user/dgulhan//Pythia8_Dijet50_pp502_TuneCUETP8M1/PYTHIA_QCD50_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/160826_084817/000${1}/
#dataset=/mnt/hadoop/cms/store/user/dgulhan//Pythia8_Dijet80_pp502_TuneCUETP8M1/PYTHIA_QCD80_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/160826_084841/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Pythia8_Dijet120_pp502_TuneCUETP8M1/PYTHIA_QCD120_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/170301_123835/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Pythia8_Dijet170_pp502_TuneCUETP8M1/PYTHIA_QCD170_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/170301_124033/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Pythia8_Dijet220_pp502_TuneCUETP8M1/PYTHIA_QCD220_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/170301_124118/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Pythia8_Dijet280_pp502_TuneCUETP8M1/PYTHIA_QCD280_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/170301_124202/000${1}
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Pythia8_Dijet370_pp502_TuneCUETP8M1/PYTHIA_QCD370_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_genpt0GeV/170301_124532/000${1}

#pPb
# dataset=/mnt/hadoop/cms/store/user/yjlee/QCD_Pt_15_TuneZ2_Mix_reverse_5p02TeV_pythia6/HiForest_PbpDir_QCD15_QCD_Pt_15_TuneZ2_Mix_5p02TeV_pythia6_HiWinter13/160628_153838/0000/
# dataset=/mnt/hadoop/cms/store/user/yjlee/QCD_Pt_120_TuneZ2_Mix_reverse_5p02TeV_pythia6/HiForest_PbpDir_QCD50_QCD_Pt_50_TuneZ2_Mix_5p02TeV_pythia6_HiWinter13/160628_183147/0000/
#dataset=/mnt/hadoop/cms/store/user/yjlee/QCD_Pt_120_TuneZ2_Mix_reverse_5p02TeV_pythia6/HiForest_PbpDir_QCD120_QCD_Pt_120_TuneZ2_Mix_5p02TeV_pythia6_HiWinter13/160628_182016/0000/

#pPb Data
# dataset=/mnt/hadoop/cms/store/user/dgulhan/PAHighPt/HiForest753p8_PAHighPt_Jet80Jet100_v4/160619_062629/0000
#dataset=/mnt/hadoop/cms/store/user/dgulhan/PAMinBiasUPC/HiForest753p8_PAMinBiasUPC_v4/160530_064411/000${1}
destination=/mnt/hadoop/cms/store/user/dgulhan/ppDijet/20170320/pPbMC_3/
#destination=/mnt/hadoop/cms/store/user/dgulhan/ppDijet/20170118/Herwig/

#pPb 2016
#dataset=/mnt/hadoop/cms/store/user/dgulhan/mergedForest/pPb/HiForestv2_Pythia8_TuneCUETP8M1_ReggeGribovPartonMC_EposLHC_pPb_4080_4080/
#dataset=/mnt/hadoop/cms/store/user/cfmcginn/MergedForests/
#dataset=/mnt/hadoop/cms/store/user/dgulhan/mergedForestpPb/data/
dataset=/mnt/hadoop/cms/store/user/dgulhan/mergedForestpPb/MC/
#dataset=/mnt/hadoop/cms/store/user/dgulhan/Herwig/QCD_dijet/
tar -cvzf residualMCTruth.tar.gz residualMCTruth


NAME="relativeResponse_MC_noFJ.C"
g++ $NAME $(root-config --cflags --libs) -O2 -o "${NAME/%.C/}.exe"

# g++ `root-config --cflags` relativeResponse_MC.C -o relativeResponse_MC.exe `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` `root-config --libs`

subdir=`date +%Y%m%d`
logdir=/net/hisrv0001/home/dgulhan/logsDijet/${subdir}_v3
mkdir $logdir
 
cp Corrections/L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb1_July4_Pbp_double.root .
cp Corrections/L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb1_July4_Pbp_double.root .
cp Corrections/L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb1.root .
cp Corrections/L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb0.root .
cp Corrections/L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut4_dopPb0.root

mkdir -p $destination

# tar -cvzf corr.tar.gz trkCorrections
counter=0
for file in ${dataset}/*
  do
    if [ $counter -lt 500 ]
       then

      cropped=`echo $file | sed "s/\// /g" | awk '{ print $9 }'`
	  echo $cropped
	  outfile=hltTree_${1}_HighPtLowerJets_${cropped}
      Error=`echo $outfile | sed "s/root/err/g"`
	  Output=`echo $outfile | sed "s/root/out/g"`
	  Log=`echo $outfile | sed "s/root/log/g"`        
	  	
	      echo "Output is : $outfile"
	      echo "Error is : $Error"
	      echo "LFN is : $lfn"
	      echo "----------------------"
	      
	      cat > subfile <<EOF

Universe       = vanilla

# files will be copied back to this dir
Initialdir     = .

# run my script
Executable     = runTreeMakerMC.sh

+AccountingGroup = "group_cmshi.yetkin"
#+IsMadgraph = 1

Arguments      = $dataset $cropped $destination $outfile \$(Process)
# input files. in this case, there are none.
Input          = /dev/null

# log files
Error          = $logdir/$Error
Output         = $logdir/$Output
Log            = $logdir/$Log

# get the environment (path, etc.)
Getenv         = True

# prefer to run on fast computers
Rank           = kflops


# should write all output & logs to a local directory
# and then transfer it back to Initialdir on completion
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT
# specify any extra input files (for example, an orcarc file)
transfer_input_files    = relativeResponse_MC_noFJ.exe,hists_pp5.root,hfmweightDataOverMC.root,residualMCTruth.tar.gz,hists_pPb5.root,hists_Pbp5.root,L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb1_July4_Pbp_double_const.root,L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut3_dopPb1_July4_pPb_double_const.root, L2L3VsPtEtaBinned_alphacut_high2_ak3PF_etacut4_dopPb0_July4_pp_double_const_doHerwig0_Feb2017_lessbins_step1.root,Casym_pp_10bins_algo_ak3PF_pt100_140_jet80_alphahigh_20_phicut250_etacut4.root

Queue
EOF

# submit the job
condor_submit subfile
 fi
 let counter+=1
done



