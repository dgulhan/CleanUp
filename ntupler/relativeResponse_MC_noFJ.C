#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>     
#include <math.h> 

#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom1.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h"
#include "TF1.h"
#include "akPu3PF_MC.C"

#include "getJEC_1st.h"
// #include "getJEC_2nd.h"
// #include "getJEC_L2L3res.h"
// #include "residualJEC.h"
//#include "DogaL2L3.h"
#include "L2L3ResidualWFits.h"
 
using namespace std; 

void relativeResponse_MC(TString dataset = "/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt15/HiForest_v77_merged01/", TString infile = "pt15_HP04_prod16_v77_merged_forest_0.root", TString outdir=".", TString fname = "out_pt15_HP04_prod16_v77_merged_forest_0.root",int radius = 3, TString subAlgo = ""){ 
  TH1D::SetDefaultSumw2();
  //cout << 1 << endl; 
  TString mode = "pPb5";//"pPb","pp","Pbp";  
  bool doMC = true;//!settings for corrections
  //cout << 2 << endl;

  // int radius = 3;
  float etacut = 3;
  // float etacutcorr = etacut;
  float etacutcorr = 3;
  float phicut=2.5;
  bool dopPb = true;

  if(mode == "pPb5" || mode == "Pbp5") dopPb = true;
  //cout << 3 << endl;

  //!boosting to match pPb CoM
  bool doShift = false;
  float shift = 0.;
  if(doShift) etacutcorr=4;

  //cout << 4 << endl;

  if(mode=="pPb5" || "Pbp5") doShift = false;

  //cout << 5 << endl;

  // TString algo = Form("ak%s%dPF",subAlgo.Data(),radius);
  TString algo = Form("ak%s%dPF",subAlgo.Data(),radius);
  // algo = "ak4PF";

  TF1 *f = new TF1("f","[0]/pow(x,[1])");
  f->SetParameters(0.937820,-0.0111559);
 
  // DogaL2L3 * L2L3 = new DogaL2L3(radius, (int)etacut);
  MCTruthResidual * MCTruth = new MCTruthResidual(mode); 

  L2ResidualJES * L2L3Corr = new L2ResidualJES(radius,((int)etacutcorr),mode);
  L3ResidualJES * L3Corr = new L3ResidualJES(radius,mode);

  L2L3Corr->test(); 
  TFile *filecentweight = new TFile("hfmweightDataOverMC.root");
  TH1D * histweight = (TH1D*)filecentweight->Get("hfmweight");
  TString dijetVars="";
  TString jetVars="";
  TString genDijetVars="";
  dijetVars += "run:evt:lumi:weight:jtpt1:jteta1:jtphi1:jtpt2:jteta2:jtphi2:jtpt3:jteta3:jtphi3:dphi"
     ":trkMax1:trkMax2"
     ":ptAverage:ptBarrel:ptProbe:etaBarrel:etaProbe:alpha:hfsum:hfp:hfm:hiBin:B:pthat:refeta1:refeta2:refpt1:refpt2:refpt3:refphi1:refphi2:hasforwardjet:random:subid1:subid2:subid3:neutralmax1:neutralmax2:centweight:rawpt1:rawpt2:recopt1:recopt2:jet40:jet60:jet80:jet100:hcalnoise:genpt1:genpt2:geneta1:geneta2:genphi1:genphi2:zs";
  genDijetVars+="ptweight:run:evt:lumi:genpt1:geneta1:genphi1:mpt1:meta1:mphi1:genpt2:geneta2:genphi2:mpt2:meta2:mphi2:pt3:eta3:phi3:mpt3:meta3:mphi3:centweight";   
  jetVars+= "weight:jtpt:jteta:jtphi:refpt:refeta:refphi:subid:rawpt:centweight";

  // TFile * fnt = new TFile(Form("%s/R%d_subAlgo%s_%s.root", outdir.Data(), radius, subAlgo.Data(), fname.Data()),"recreate");
  //cout<<"file: "<<Form("R%d_subAlgo%s_%s.root", radius, subAlgo.Data(), fname.Data())<<endl;
  TFile * fnt = new TFile(Form("R%d_subAlgo%s_%s", radius, subAlgo.Data(), fname.Data()),"recreate");

  TNtuple *ntdijet = new TNtuple("ntdijet","",dijetVars.Data());
  TNtuple *ntgendijet = new TNtuple("ntgendijet","",genDijetVars.Data());
  TNtuple *ntjet = new TNtuple("ntjet","",jetVars.Data());
  //cout << 6 << endl;

  TFile * filevspt;
  TString infname = Form("%s/%s",dataset.Data(), infile.Data());


  HiTree *fhi = new HiTree(infname.Data());
  //cout << "algo:" << algo.Data()<<endl;
  akPu3PF_MC *t = new akPu3PF_MC(infname.Data(),algo);
  //cout << "algo:" << algo.Data()<<endl;
  skimTree   *fskim = new skimTree(infname.Data()); 
  HltTree   *fhlt = new HltTree(infname.Data());
 
  //cout<<infname.Data()<<std::endl;
  float jtpu[] = {0.0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,3.,3.5,4.,5.,6.,8,10,15,20};
  TH1D * histJtPu = new TH1D("histJtPu","",19, jtpu);
  TH1D * histJtPuWeighted = new TH1D("histJtPuWeighted","",19, jtpu);

  int nentries = t->GetEntriesFast();
  //int nentries = 1;

 
  //int pthatvals[] = {15,30,50,80,120,170,220,280,370,9999};
  int pthatvals[] = {15, 30, 50, 100, 200, 9999};

  int pthatmax[] = {100,155,245,9999,9999,9999,9999,9999,9999};
  float xsecs[] = {5.335E-01, 3.378E-02, 3.778E-03, 4.412E-04, 6.147E-05, 1.018E-05, 2.477E-06, 6.160E-07, 1.088E-07};
  float weights[] = {0.171181,0.0125539,0.00106675,0.000126284,2.34739e-05,3.21927e-06,6.28969e-07,2.02126e-07,5.73344e-08};
  float weightspp[] = {0.0253735, 0.00332957, 0.000339276, 2.21469e-05, 4.81271e-06, 9.23762e-07, 1.95096e-07, 4.69381e-08, 8.84642e-09};
  float weightsHerwig[] = { 10., 0.665420658, 0.073546465, 0.002751188, 0.000104895};

  if(mode == "pp5"){
    /* for(int ipthat = 0; ipthat < 10; ipthat++){
    weights[ipthat] = weights[ipthat];
   }
   */
    for(int ipthat = 0; ipthat < 5; ipthat++){
      weights[ipthat] = weightsHerwig[ipthat]; 
    }
  }
  float ptweight = 1;

  //cout<<"nentries " << nentries <<std::endl;
  //cout <<"shift"<<shift<<endl;
  //cout << "mode"<<mode <<endl;

  // for (Long64_t jentry=15565; jentry<15566; jentry++) {
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {

    //cout << jentry << endl; 
    // if((jentry%1000)==0) //cout<< jentry << endl;
    t->GetEntry(jentry);
    fhi->GetEntry(jentry);
    fskim->GetEntry(jentry);
    fhlt->GetEntry(jentry);
    //cout << 0 << endl;

    if((mode == "pp5") && !(fskim->pHBHENoiseFilterResultProducer && fskim->pPAprimaryVertexFilter && fabs(fhi->vz)<15 && fskim->pBeamScrapingFilter)) continue;
    //cout << 1 << endl;
    if((mode == "pPb5" || mode == "Pbp5" || mode == "pPb8") && !(fskim->pHBHENoiseFilter && fskim->pVertexFilterCutGplus)) continue;// HBHENoiseFilterResult pHBHENoiseFilter
    ////cout << fhi->vz << endl;
     //cout << 2 << endl;
    if(!doMC && mode=="pPb5" && fhi->run>211256) continue;
    if(!doMC && mode=="Pbp5" && fhi->run<=211256) continue;
    if(!doMC) ptweight = -99;
    else{
      for(int ipthat = 0; ipthat < 5; ipthat++){
        if(fhi->pthat >= pthatvals[ipthat] && fhi->pthat < pthatvals[ipthat+1]){
          ptweight = weights[ipthat];
          break;
        }
      }
    }
    //cluster gen jets
  
    //cout << 3 << endl;

 
    float hfweight = histweight->GetBinContent(histweight->FindBin(0.45*fhi->hiHFminusEta4));
    float pt1=-99, pt2=-99, pt3=-99, eta1=-99, eta2=-99, eta3=-99, phi1=-99, phi2=-99, phi3=-99, dphi=-99, rawpt1=-99, jtpt1=-99, rawpt2=-99,jtpt2=-99;
    float trkmax1=-99, trkmax2=-99, neutralmax1=-99, neutralmax2=-99, subid1=-99, subid2=-99, subid3=-99;
     float  ptprobe=-99, ptbarrel=-99, etaprobe=-99, etabarrel=-99;
     float hfsum = -99;
     float c = 1;
     float hfgenp=0;
     float hfgenm=0;
     float refeta1=-99, refeta2=-99, refpt1=-99, refpt2=-99, refphi1=-99, refphi2=-99, refpt3=-99, refeta3=-99, refphi3=-99;
     float genpt1=-99, genpt2=-99, genpt3=-99, geneta1=-99, geneta2=-99, geneta3=-99, genphi1=-99, genphi2=-99, genphi3=-99;
     float mpt1=-99, mpt2=-99,  mpt3=-99;
     float meta1=-99, meta2=-99, meta3=-99, mphi1=-99, mphi2=-99, mphi3=-99;
     bool hasForwardJet=false;
     std::vector<std::pair<float, std::pair<float, std::pair<float, std::pair<float, std::pair<float, std::pair<float, std::pair<float, float > >  > > > > > >jets;
     std::vector<std::pair<float, std::pair<float, std::pair<float, std::pair<float,std::pair<float,float > > > > > > genjets;
     int njet=0;
     float random;
     //cout << 4 << endl;

    for(int ijet=0;ijet<t->nref;ijet++){
      float jteta = t->jteta[ijet];
      float jtphi = t->jtphi[ijet];
      float refpt = -99;
      float refeta = -99;
      float refphi = -99;
      float subid = -99;  
      // //cout << 4.1 << endl;

      if(fabs(jteta>etacut)) hasForwardJet=true;
      if(fabs(jteta+shift)>etacut) continue;
      if(t->rawpt[ijet] < 3.) continue;
       //cout << 4.2 << endl;

      njet++;
      float  rawpt = t->rawpt[ijet];
      float jtpt = rawpt;
      //cout << 4.3 << endl;
      if(mode == "pp5" || mode=="pPb8"){
        jtpt = t->jtpt[ijet];
      }
      float correctedpt = jtpt;
      //cout << 4.4 << endl;
      if(mode=="pPb5" || mode=="Pbp5"){
         //cout << 4.5 << endl; 
         jtpt = MCTruth->getJEC_1st(jtpt,rawpt,jteta);
         //cout << 4.6 << endl; 
	 correctedpt = jtpt; 
	 if(doMC ){
	   //cout << 4.7 << endl;
	    correctedpt = MCTruth->getExtraSmear(correctedpt,jteta);
	 }
      }
      //cout << 4.8 << endl;
      if(mode == "pp5" && correctedpt > 20) correctedpt = MCTruth->getResidualCorr(rawpt,jteta);
      else{ 
        correctedpt = MCTruth->getResidualCorr(correctedpt,jteta);
      }
     	//cout << 4.9 << " " << correctedpt << endl;
	if(!doMC){
          //cout << 4.81 <<  " " << correctedpt << endl;
          //**correctedpt = L2L3Corr->getCorrectedPt(MCTruth->unfoldPt(correctedpt), jteta);
	  if(mode=="pp5"){
             correctedpt = L2L3Corr->getCorrectedPtAlternative(correctedpt, jteta); 
             correctedpt = L2L3Corr->getCorrectedPt(correctedpt, jteta);
             correctedpt = L3Corr->getCorrectedPt(correctedpt);
          }else{
	    correctedpt = L2L3Corr->getCorrectedPt(MCTruth->unfoldPt(correctedpt), jteta);
            //correctedpt = L2L3Corr->getCorrectedPt(correctedpt, jteta); 
	  }
	  //cout << 4.82 << " " << correctedpt << endl;
          //cout << 4.83 << " " << correctedpt << endl;
        }
	if(doMC){
	 refpt = t->refpt[ijet];
	 refeta = t->refeta[ijet]; 
	 refphi = t->refphi[ijet];
        }
	// //cout << 4.3 << endl;

	float jetEntry[] = {ptweight,correctedpt,jteta,jtphi,refpt,refeta,refphi,subid,t->rawpt[ijet],hfweight};
    jets.push_back(std::make_pair(correctedpt,std::make_pair(jteta, std::make_pair(jtphi,std::make_pair(refpt,std::make_pair(refeta,std::make_pair(refphi,std::make_pair(rawpt,jtpt))))))));
    ntjet->Fill(jetEntry);
  }
  
  //    //cout << 5 << endl;

  if(njet>0){
   std::sort(jets.begin(),jets.end());
   pt1 = jets[njet-1].first;
   // //cout<<"pt1:" << pt1<<endl;
   eta1 = jets[njet-1].second.first+shift;
   phi1 = jets[njet-1].second.second.first;
   if(doMC){
    refpt1 = jets[njet-1].second.second.second.first;
    refeta1 = jets[njet-1].second.second.second.second.first+shift;
    refphi1 = jets[njet-1].second.second.second.second.second.first;
   }
   rawpt1 = jets[njet-1].second.second.second.second.second.second.first;
   jtpt1 = jets[njet-1].second.second.second.second.second.second.second;
   if(njet>1){
    pt2 = jets[njet-2].first;
    eta2 = jets[njet-2].second.first+shift;
    phi2 = jets[njet-2].second.second.first;
	if(doMC){
	 refpt2 = jets[njet-2].second.second.second.first;
     refeta2 = jets[njet-2].second.second.second.second.first+shift;
     refphi2 = jets[njet-2].second.second.second.second.second.first;
    }
    rawpt2 = jets[njet-2].second.second.second.second.second.second.first;
    jtpt2 = jets[njet-2].second.second.second.second.second.second.second;
	if(njet>2){
     pt3 = jets[njet-3].first;
     eta3 = jets[njet-3].second.first+shift;
     phi3 = jets[njet-3].second.second.first;
     if(doMC){
      refpt3 = jets[njet-3].second.second.second.first;
      refeta3 = jets[njet-3].second.second.second.second.first+shift;
      refphi3 = jets[njet-3].second.second.second.second.second.first;
     }
    }
   }
  }
  if(njet>=2) dphi = acos(cos(phi1-phi2));
  if (fabs(eta1)<1.3 || fabs(eta2)<1.3){ 
   if(fabs(eta1)<1.3 && fabs(eta2)>1.3){
    etaprobe = eta2;
    etabarrel = eta1;
    ptprobe = pt2;
    ptbarrel = pt1;
   }
   if(fabs(eta1)>1.3 && fabs(eta2)<1.3){
    etaprobe = eta1;
    etabarrel = eta2;
    ptprobe = pt1;
    ptbarrel = pt2;
   }
   if(fabs(eta1)<1.3 && fabs(eta2)<1.3){
    TRandom1 *r = new TRandom1();
    random = r->Rndm();
    if(random>0.5){
    // if(random>0.496){
     etaprobe = eta1;
     etabarrel = eta2;
     ptprobe = pt1;
     ptbarrel = pt2;
    }else{
     etaprobe = eta2; 
     etabarrel = eta1;
     ptprobe = pt2; 
     ptbarrel = pt1;
    }
   }
  }
  //cout << 6 << endl;

  int ngenjet = 0;
  if(doMC){
  for(int ijet=0;ijet<t->ngen;ijet++){
   if(fabs(t->geneta[ijet]+shift)>etacut) continue;
   float pt = t->genpt[ijet];
   float eta = t->geneta[ijet];
   float phi = t->genphi[ijet];
   float mpt = -99;
   float meta = -99;
   float mphi = -99;
   for(int ireco = 0; ireco < njet; ireco++){
    if(fabs(jets[ireco].second.first - eta)<0.4 && acos(cos(jets[ireco].second.second.first - phi))<0.4){
	 mpt = jets[ireco].first;
	 meta = jets[ireco].second.first;
	 mphi = jets[ireco].second.second.first;
 	} 
   }
   ngenjet++;
   genjets.push_back(std::make_pair(pt,std::make_pair(eta, std::make_pair(phi,std::make_pair(mpt,std::make_pair(meta,mphi))))));
   }
   
  
  //cout << 7 << endl;

  
  if(ngenjet>0){
   std::sort(genjets.begin(),genjets.end());
   genpt1 = genjets[ngenjet-1].first;
   geneta1 = genjets[ngenjet-1].second.first+shift;
   genphi1 = genjets[ngenjet-1].second.second.first;
   mpt1 = genjets[ngenjet-1].second.second.second.first;
   meta1 = genjets[ngenjet-1].second.second.second.second.first+shift;
   mphi1 = genjets[ngenjet-1].second.second.second.second.second;
   if(ngenjet>1){
    genpt2 = genjets[ngenjet-2].first;
    geneta2 = genjets[ngenjet-2].second.first+shift;
    genphi2 = genjets[ngenjet-2].second.second.first;
    mpt2 = genjets[ngenjet-2].second.second.second.first;
    meta2 = genjets[ngenjet-2].second.second.second.second.first+shift;
    mphi2 = genjets[ngenjet-2].second.second.second.second.second;
    if(ngenjet>2){
     genpt3 = genjets[ngenjet-3].first;
     geneta3 = genjets[ngenjet-3].second.first+shift;
     genphi3 = genjets[ngenjet-3].second.second.first;
     mpt3 = genjets[ngenjet-3].second.second.second.first;
     meta3 = genjets[ngenjet-3].second.second.second.second.first+shift;
     mphi3 = genjets[ngenjet-3].second.second.second.second.second;
    }
   }
  }
  }
  float jet40 = 0,  jet60 = 0, jet80 = 0, jet100 = 0, hcalnoise = 0, zs = 0;
  if(!doMC){
   if(mode=="pPb5" || mode=="Pbp5"){
    jet40 = (float)fhlt->HLT_PAJet40_NoJetID_v1;
    jet60 = (float)fhlt->HLT_PAJet60_NoJetID_v1;
    jet80 = (float)fhlt->HLT_PAJet80_NoJetID_v1;
    jet100 = (float)fhlt->HLT_PAJet100_NoJetID_v1;
    hcalnoise = (float)(fskim->pHBHENoiseFilter);
    zs = (float)fhlt->HLT_PAZeroBiasPixel_SingleTrack_v1;
   }else{
    jet40 = (float)(fhlt->HLT_AK4PFJet40_Eta5p1_v1);
    jet60 = (float)(fhlt->HLT_AK4PFJet60_Eta5p1_v1);
    jet80 = (float)(fhlt->HLT_AK4PFJet80_Eta5p1_v1);
    jet100 = (float)(fhlt->HLT_AK4PFJet100_Eta5p1_v1);
    hcalnoise = (float)(fskim->HBHENoiseFilterResultRun2Loose);
    zs = (float)(fhlt->HLT_L1MinimumBiasHF1OR_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part1_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part2_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part3_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part4_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part5_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part6_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part7_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part8_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part9_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part10_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part11_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part12_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part12_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part13_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part14_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part15_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part16_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part17_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part18_v1 || fhlt->HLT_L1MinimumBiasHF1OR_part19_v1);
   }
  }
  float  ptaverage =(ptprobe+ptbarrel)/2;
  hfsum = (fhi->hiHFplusEta4 + fhi->hiHFminusEta4);
  if(njet>0){
    float dijetEntry[]={fhi->run,fhi->evt,fhi->lumi,ptweight,pt1,eta1,phi1,pt2,eta2,phi2,pt3,eta3,phi3,dphi,trkmax1,trkmax2,ptaverage,ptbarrel,ptprobe,etabarrel,etaprobe,(pt3/ptaverage),hfsum,fhi->hiHFplusEta4,fhi->hiHFminusEta4,fhi->hiBin,((ptprobe-ptbarrel)/ptaverage),t->pthat,refeta1,refeta2,refpt1,refpt2,refpt3,refphi1,refphi2,((float)hasForwardJet),random,subid1,subid2,subid3,neutralmax1,neutralmax2,hfweight,rawpt1,rawpt2,jtpt1,jtpt2,jet40,jet60,jet80,jet100,hcalnoise,genpt1,genpt2,geneta1,geneta2,genphi1,genphi2,zs};
   ntdijet->Fill(dijetEntry);
  }
  if(ngenjet>0){
    float genDijetEntry[]={ptweight,fhi->run,fhi->evt,fhi->lumi,genpt1,geneta1,genphi1,mpt1,meta1,mphi1,genpt2,geneta2,genphi2,mpt2,meta2,mphi2,genpt3,geneta3,genphi3,mpt3,meta3,mphi3,hfweight};   
   ntgendijet->Fill(genDijetEntry);
  }
  
   //calculate jtpu w cent weight
  if(mode=="Pbp5" || mode=="pPb5"){
   for(int ijet = 0; ijet < t->nref; ijet++){
    if(t->jtpt[ijet] > 30){
	 if(fabs(t->jteta[ijet])>3) continue;
     histJtPu->Fill(t->jtpu[ijet]);
     histJtPuWeighted->Fill(t->jtpu[ijet],hfweight);
    }
   }
  }
  // if(pt1>100 && refpt1<0) //cout<< "entry="<<jentry<<" pt1="<<pt1<<" eta1="<<eta1<< " phi1"<<phi1<<endl;
}

//cout<<"write"<<endl;
fnt->cd(); 
if(doMC)ntdijet->Write();
ntdijet->Write();
ntjet->Write();
ntgendijet->Write();
if(mode=="Pbp5" || mode=="pPb5"){
 histJtPuWeighted->Write();
 histJtPu->Write();
}
fnt->Close();
//cout<<"done"<<std::endl;

fhi->Close();
t->Close();
t->Close();
}
 
int main(int argc, char *argv[])
{ 
  //cout << -1 << endl;
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),argv[6]);
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],4,"Cs");
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4]);
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4]);
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],3,"Pu");
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],3,"Cs");
  relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],3,"");
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],4,"Pu");
  // relativeResponse_MC(argv[1],argv[2],argv[3],argv[4],4,"Cs");
  return 0;
}
