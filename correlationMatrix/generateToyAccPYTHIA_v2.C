#include <iostream>
#include <vector>
#include <algorithm>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom1.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TF1.h"
  
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TComplex.h"
#include "TString.h"  
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h" 
#include "TRandom3.h" 
// #include "/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/dijeteta/utilities.h"

struct JetTree {
public :
   JetTree(){};
   
   // Declaration of leaf types
   Float_t         jtpt1;
   Float_t         jteta1;
   Float_t         jtphi1;
   Float_t         jtpt2;
   Float_t         jteta2;
   Float_t         jtphi2;
   Float_t         jtpt3;
   Float_t         jteta3;
   Float_t         jtphi3;
   // List of branches
   TBranch        *b_jtpt1;   //!
   TBranch        *b_jteta1;   //!
   TBranch        *b_jtphi1;   //!
   TBranch        *b_jtpt2;   //!
   TBranch        *b_jteta2;   //!
   TBranch        *b_jtphi2;   //!
   TBranch        *b_jtpt3;   //!
   TBranch        *b_jteta3;   //!
   TBranch        *b_jtphi3;   //!
};

struct PtSmearing {
  private:
   float etaranges[4];
   float etarangesjec[3];
   float ptranges[3];  
  public :
   TFile * filerespt, *filereseta;
   TF1 * fitrespt, * fiteta[2][3];
   TH1D * histjecvspt[2];
   TF1 * gaus;
   PtSmearing(TString mode = "pp"){
    float etarangesjec[3] = {0.0, 3.0, 3.465};
    float etaranges[4] = {-3.5, -1.5, 1.5, 3.5};
    float ptranges[3] = {20.,80.,400};
	for(int ieta = 0; ieta < 4; ieta++){
	 this->etaranges[ieta] = etaranges[ieta];
	}
	for(int ieta = 0; ieta < 3; ieta++){
	 this->ptranges[ieta] = ptranges[ieta];
	}
	for(int ieta = 0; ieta < 3; ieta++){
	 this->etarangesjec[ieta] = etarangesjec[ieta];
	}
    filerespt = new TFile(Form("hists_%s.root",mode.Data()));
    filereseta = new TFile(Form("resvseta_%s.root",mode.Data()));
    fitrespt = (TF1*)filerespt->Get("fit_gauss_corr0");
    for(int ipt = 0; ipt < 2; ipt++){
     for(int ifit = 0; ifit < 3; ifit++){
      fiteta[ipt][ifit] = (TF1*)filereseta->Get(Form("fitResol%d%d",ipt,ifit));
     } 
    }
	histjecvspt[0] = (TH1D*)filerespt->Get("h_ntrk0");
	histjecvspt[1] = (TH1D*)filerespt->Get("h_ntrk_higheta_0");
    gaus = new TF1("gaus","gaus(0)",-20,20);
    gaus->SetParameters(1,0,1);
   };
   
   int findEtaBin(float jteta){
    for(int ieta = 0; ieta < 3; ieta++){
	 if(jteta >= etaranges[ieta] && jteta < etaranges[ieta+1]){
	  return ieta;
	 }
	}
	return -1;
   };
   
   int findEtaBinJES(float jteta){
    for(int ieta = 0; ieta < 2; ieta++){
	 if(fabs(jteta) >= etarangesjec[ieta] && fabs(jteta) < etarangesjec[ieta+1]){
	  return ieta;
	 }
	}
	return -1;
   };
   
   int findPtBin(float jtpt){
    for(int ipt = 0; ipt < 2; ipt++){
	 if(jtpt >= ptranges[ipt] && jtpt < ptranges[ipt+1]){
	  return ipt;
	 }
	}
	return 0;
   };
   
   float smearedPt(float jtpt, float jteta){
    float resJtPt = fitrespt->Eval(jtpt);
    float resJtEta = 0;
    int ipt = findPtBin(jtpt);
	int ieta = findEtaBin(jteta);
    resJtEta = fiteta[ipt][ieta]->Eval(jteta);
	float res = resJtPt + resJtEta;
	
	return (1+gaus->GetRandom()*res)*jtpt;
   };  
   
   float getJESOffset(float jtpt, float jteta){
    int etaBin = findEtaBinJES(jteta);
	if(etaBin < 0) return 1;
	if(etaBin == 1 && jtpt > 215) jtpt = 215;
	return histjecvspt[etaBin]->GetBinContent(histjecvspt[etaBin]->FindBin(jtpt));
	 
   }; 
};

struct EtaSmearing {
  private:
   float ptranges[7];  
  public :
   TFile * filerespoint;
   TH1D * histeta[2][6];
   TF1 * gaus;
   EtaSmearing(TString mode = "pp"){
    float ptranges[]= {25,55,75,95,115,150,400}; 
	for(int ipt = 0; ipt < 7; ipt++){
	 this->ptranges[ipt] = ptranges[ipt];
	}
    filerespoint = new TFile(Form("pointingRes_%s.root",mode.Data()));
    for(int ipt = 0; ipt < 6; ipt++){
	 for(int ijet = 0; ijet < 2; ijet++){
      histeta[ijet][ipt] = (TH1D*)filerespoint->Get(Form("hist_deta_%d_%d",ipt,ijet));
	 }
	}
    gaus = new TF1("gaus","gaus(0)",-20,20);
    gaus->SetParameters(1,0,1);
   };
     
   int findPtBin(float jtpt){
    for(int ipt = 0; ipt < 6; ipt++){
	 if(jtpt >= ptranges[ipt] && jtpt < ptranges[ipt+1]){
	  return ipt;
	 }
	}
	return 0;
   };
   
   float SmearedEta(int ijet, float jtpt, float jteta){
    int bin = findPtBin(jtpt);
	float resEta = histeta[ijet][bin]->GetBinContent(histeta[ijet][bin]->FindBin(jteta));
  
	return (1+gaus->GetRandom()*resEta)*jteta;
   }; 
};

struct JetGenerator{
 private:
  float ptranges[7];
  int binNumInPt;
  int binNumInEta;
  TRandom3 * rand;
  float etacut;
  float maxNumber[6];
 public: 
  float jteta[2];
  float jtpt[2];
  TFile *fileSingleJet;
  TH2F *histNumber[2][6];
  TH2F *histRatNumber[2][6];
 JetGenerator(TString mode = "pp"){
  etacut = 3; 
  for(int ijet = 0; ijet < 2; ijet++){
   jteta[ijet] = -99;
   jtpt[ijet] = -99;
  }
  rand = new TRandom3();
  int ptrangesTmp[]= {25,55,75,95,115,150,400}; 

  float maxNumberTmp[]={2.5e+03,2.0e+03,3.1e+03,8.0e+02,2.8e+02,5.0e+03,2.0e+03,3.8e+03};
 
  fileSingleJet = new TFile(Form("SingleJet2DPthatComb_%s.root",mode.Data()));
  for(int ipt = 0; ipt < 6; ipt++){
   this->ptranges[ipt] = ptrangesTmp[ipt];
   this->maxNumber[ipt] = maxNumberTmp[ipt];
   for(int ijet = 0; ijet < 2; ijet++){
    histNumber[ijet][ipt] = (TH2F*)fileSingleJet->Get(Form("histJet%dPtEtaPtBin%d",ijet,ipt));
    histRatNumber[ijet][ipt] = (TH2F*)fileSingleJet->Get(Form("histRatJet%dPtEtaPtBin%d",ijet,ipt));
	histNumber[ijet][ipt]->Print("all");
   }
  }
  this->ptranges[6] = ptrangesTmp[6];
  binNumInPt = histNumber[0][0]->GetNbinsX();
  binNumInEta = histNumber[0][0]->GetNbinsY();
 };
 
 int findPtBin(float jtpt){
  for(int ipt = 0; ipt < 2; ipt++){
   if(jtpt >= ptranges[ipt]*0.7 && jtpt < ptranges[ipt+1]*1.3){
	return ipt;
   }
  }
  return 0;
 };
 
 float readValue(int ijet, int binHist, float jtpt, float jteta){
  int binPt = histNumber[ijet][binHist]->GetXaxis()->FindBin(jtpt);
  int binEta = histNumber[ijet][binHist]->GetYaxis()->FindBin(jteta);
  float number = histNumber[ijet][binHist]->GetBinContent(binPt, binEta);

  return number;
 }
 
 void generateJet(int ijet, int binHist){
  int count = 0;
  while(true){
   float randomPt;
   if(ijet == 0) randomPt = ptranges[binHist]+(2*ptranges[binHist+1]-20-ptranges[binHist])*rand->Rndm();
   else randomPt = 20+(ptranges[binHist+1]-20)*rand->Rndm();
   float randomEta = -etacut + 2*rand->Rndm()*etacut;
   float randomNumber = maxNumber[binHist]*rand->Rndm();
   float value = readValue(ijet, binHist, randomPt, randomEta);
   if(value>maxNumber[binHist]){
    std::cout << "max not sufficient for bin:" << binHist<<" value = "<< value << " maxNumber = " << maxNumber[binHist]<<std::endl;
	std::cout << "eta = " << randomEta << " pt = "<<randomPt << " bin range" << ptranges[binHist] << " - " <<ptranges[binHist+1]<<  std::endl;
   }
   if(value < 3 || value == -1){
    // std::cout<<"-1 or 0"<<std::endl;
    count++;
    continue;
   }
   if(randomNumber < value){
    // std::cout << "eta = " << randomEta << " pt=" << randomPt <<endl;
	// std::cout << count << std::endl;
    jteta[ijet] = randomEta;
    jtpt[ijet] = randomPt; 
    break;
   }
   if(count > 100000){
    cout<<value<<endl;
    std::cout << "too many dice" << std::endl;
	break;
   }
   count++;
  }
 };

 float getDataWeight(int ijet, int binHist, float jtpt, float jteta){
  int binPt = histNumber[ijet][binHist]->GetXaxis()->FindBin(jtpt);
  int binEta = histNumber[ijet][binHist]->GetYaxis()->FindBin(jteta);
  return histRatNumber[ijet][binHist]->GetBinContent(binPt, binEta);
 };
};

void generateToyAccPYTHIA(){
 TH1D::SetDefaultSumw2();
 
 cout << 1 << endl;
 TString mode = "pPb";
 TFile *outf = new TFile(Form("distsPtSmearing_test5_%s.root",mode.Data()),"recreate");
 int nbin = 6;
 TNtuple *ntdijet[nbin];
 cout << 2 << endl;

 PtSmearing * ptSmear = new PtSmearing(mode);
 EtaSmearing *etaSmear = new EtaSmearing(mode);
 cout << 3 << endl;

 JetGenerator * generator = new JetGenerator(mode); //dummy;
 int ptranges[]= {25,55,75,95,115,150,400}; 
 TString dijetVars = "jtpt1:jteta1:jtpt2:jteta2:jtpt3:jteta3:jtpt1sm:jtpt2sm:jtpt3sm:(float)thirdjetfeedup:weight1:weight2:jteta1sm: jteta2sm:jtpt1offset:jtpt2offset";
 TFile *f_mc[nbin];
 // int pthat[] = {15,15,30,30,50,80};
 int pthat[] = {15,30,50,80,80,120};
 
 TTree * nt_mc[nbin];
 
 TH1F * histGenEta1[nbin];
 TH1F * histGenEta2[nbin];
 TH1F * histGenPt1[nbin];
 TH1F * histGenPt2[nbin];
 TH1F * histGenDijetEta[nbin];
 TH1F * histGenDijetEtaNoWeight[nbin];
 TH1F * histJESOffsetDijetEta[nbin];
 TH1F * histJESOffsetDijetEtaNoWeight[nbin];
 TH1F * histEtaSmearDijetEta[nbin];
 TH1F * histEtaSmearDijetEtaNoWeight[nbin];
 TH1F * histSmearDijetEta[nbin];
 TH1F * histSmearDijetEtaNoWeight[nbin];

 int neta=28;
 float etabins[]= {-2.999, -2.500, -2.172,
                  - 1.930, -1.740,-1.566,-1.392,
				  -1.218, -1.044, -0.879, -0.696,
				  -0.522,-0.348,-0.174, 0,
                       0.174,    0.348,    0.522, 
                      0.696,   0.879,   1.044,   1.218,
                        1.392,   1.566,  1.740,  
                      1.930,   2.172,   2.500,  
                      2.999};
 

 for(int ibin = 0; ibin < nbin; ibin++){
  outf->cd();
  ntdijet[ibin] = new TNtuple(Form("ntdijet_smeared%d",ibin),"",dijetVars.Data());
  
  JetTree * fJet = new JetTree(); 
  if(mode == "pp")f_mc[ibin] = new TFile(Form("/data/dgulhan/pA2016/CMSSW_5_3_20/src/ntuples/merged_pthat%d_5020GeV.root",pthat[ibin]));
  if(mode == "pPb"){
   cout <<  Form("/data/dgulhan/pA2016/CMSSW_5_3_20/src/ntuples/merged_pthat%d_boosted_5020GeV.root",pthat[ibin]) << endl;
   f_mc[ibin] = new TFile(Form("/data/dgulhan/pA2016/CMSSW_5_3_20/src/ntuples/merged_pthat%d_boosted_5020GeV.root",pthat[ibin]));
  }
  nt_mc[ibin] = (TTree*)f_mc[ibin]->Get("dijet/nt");
  nt_mc[ibin]->SetBranchAddress("pt1", &fJet->jtpt1, &fJet->b_jtpt1);
  nt_mc[ibin]->SetBranchAddress("pt2", &fJet->jtpt2, &fJet->b_jtpt2);
  nt_mc[ibin]->SetBranchAddress("pt3", &fJet->jtpt3, &fJet->b_jtpt3);
  nt_mc[ibin]->SetBranchAddress("eta1", &fJet->jteta1, &fJet->b_jteta1);
  nt_mc[ibin]->SetBranchAddress("eta2", &fJet->jteta2, &fJet->b_jteta2);
  nt_mc[ibin]->SetBranchAddress("eta3", &fJet->jteta3, &fJet->b_jteta3);
  nt_mc[ibin]->SetBranchAddress("phi1", &fJet->jtphi1, &fJet->b_jtphi1);
  nt_mc[ibin]->SetBranchAddress("phi2", &fJet->jtphi2, &fJet->b_jtphi2);
  nt_mc[ibin]->SetBranchAddress("phi3", &fJet->jtphi3, &fJet->b_jtphi3);
 

  histGenDijetEta[ibin] = new TH1F(Form("histGenDijetEta%d",ibin),"", neta, etabins);
  histGenDijetEtaNoWeight[ibin] = new TH1F(Form("histGenDijetEtaNoWeight%d",ibin),"", neta, etabins);
  histJESOffsetDijetEta[ibin] = new TH1F(Form("histJESOffsetDijetEta%d",ibin),"", neta, etabins);
  histJESOffsetDijetEtaNoWeight[ibin] = new TH1F(Form("histJESOffsetDijetEtaNoWeight%d",ibin),"", neta, etabins);
  histSmearDijetEta[ibin] = new TH1F(Form("histSmearDijetEta%d",ibin),"", neta, etabins);
  histSmearDijetEtaNoWeight[ibin] = new TH1F(Form("histSmearDijetEtaNoWeight%d",ibin),"", neta, etabins);
  histEtaSmearDijetEta[ibin] = new TH1F(Form("histEtaSmearDijetEta%d",ibin),"", neta, etabins);
  histEtaSmearDijetEtaNoWeight[ibin] = new TH1F(Form("histEtaSmearDijetEtaNoWeight%d",ibin),"", neta, etabins);

  Int_t lastEntry = nt_mc[ibin]->GetEntries();//100;

  for(int ievt = 0; ievt < lastEntry; ievt++){
  // for(int ievt = 0; ievt < 10; ievt++){
   if(ievt%10000 == 0)std::cout<<ievt<<"/"<<lastEntry<<std::endl;
   float jteta1 = -99, jteta2 = -99, jteta3 = -99;
   float jtpt1 = -99, jtpt2 = -99, jtpt3 = -99;

   nt_mc[ibin]->GetEntry(ievt); 

   jtpt1 = fJet->jtpt1;
   jtpt2 = fJet->jtpt2;
   jtpt3 = fJet->jtpt3;
   jteta1 = -fJet->jteta1;
   jteta2 = -fJet->jteta2;
   jteta3 = -fJet->jteta3;
   float jteta1sm = etaSmear->SmearedEta(0, jtpt1, jteta1);
   float jteta2sm = etaSmear->SmearedEta(1, jtpt2, jteta2);

   if(acos(cos(fJet->jtphi1-fJet->jtphi2))<(2.*TMath::Pi()/3.)) continue;

   float ptave = (jtpt1+jtpt2)/2.;
   
   //weight to match data
   float weight1 = generator->getDataWeight(0, ibin, jtpt1, jteta1);
   float weight2 = generator->getDataWeight(1, ibin, jtpt2, jteta2);

   //fill the gen info
   if(ptave >= ptranges[ibin] && ptave < ptranges[ibin+1]){
 	 if(mode == "pp"){
	  histGenDijetEta[ibin]->Fill(fabs(jteta1+jteta2)/2.,weight1*weight2);
 	  histGenDijetEtaNoWeight[ibin]->Fill(fabs(jteta1+jteta2)/2.);
	 }
	 if(mode == "pPb"){
	  histGenDijetEta[ibin]->Fill((jteta1+jteta2)/2.,weight1*weight2);
 	  histGenDijetEtaNoWeight[ibin]->Fill((jteta1+jteta2)/2.);
	 }
   }
   
   //jes offset
   
   float jtpt1offset = ptSmear->getJESOffset(jtpt1,jteta1)*jtpt1;
   float jtpt2offset = ptSmear->getJESOffset(jtpt2,jteta2)*jtpt2;
   if(mode=="pPb"){
    jtpt1offset*=1.005;
    jtpt2offset*=1.005;
   }
   // float jtpt1offset = ptSmear->getJESOffset(jtpt1,jteta1)*jtpt1;
   // float jtpt2offset = ptSmear->getJESOffset(jtpt2,jteta2)*jtpt2;
   float ptaveoffset = (jtpt1offset+jtpt2offset)/2.;
   
   if(ptaveoffset >= ptranges[ibin] && ptaveoffset < ptranges[ibin+1]){
 	 if(mode == "pp"){
 	  histJESOffsetDijetEta[ibin]->Fill(fabs(jteta1+jteta2)/2.,weight1*weight2);
 	  histJESOffsetDijetEtaNoWeight[ibin]->Fill(fabs(jteta1+jteta2)/2.);
 	 }if(mode == "pPb"){
 	  histJESOffsetDijetEta[ibin]->Fill((jteta1+jteta2)/2.,weight1*weight2);
 	  histJESOffsetDijetEtaNoWeight[ibin]->Fill((jteta1+jteta2)/2.);
	 }
   }

   // use same event 100 times for pt and eta resolution
   // for(int idice = 0; idice < 100; idice++){   
   for(int idice = 0; idice < 10; idice++){   
    if(ptave >= ptranges[ibin] && ptave < ptranges[ibin+1]){
 	 if(fabs(jteta1sm)<3. && fabs(jteta2sm)<3.){
  	  if(mode == "pp"){
	   histEtaSmearDijetEta[ibin]->Fill(fabs(jteta1sm+jteta2sm)/2.,weight1*weight2);
	   histEtaSmearDijetEtaNoWeight[ibin]->Fill(fabs(jteta1sm+jteta2sm)/2.);
  	  }if(mode == "pPb"){
 	   histEtaSmearDijetEta[ibin]->Fill((jteta1sm+jteta2sm)/2.,weight1*weight2);
 	   histEtaSmearDijetEtaNoWeight[ibin]->Fill((jteta1sm+jteta2sm)/2.);
	  }
	 }
	}
   
    float jtpt1sm = ptSmear->smearedPt(jtpt1,jteta1);
    float jtpt2sm = ptSmear->smearedPt(jtpt2,jteta2);
    float jtpt3sm = ptSmear->smearedPt(jtpt3,jteta3);
	bool thirdjetfeedup = false;
	if(jtpt3sm > jtpt2sm || jtpt3sm > jtpt1sm){
	 thirdjetfeedup = true;
	 if(jtpt3sm > jtpt1sm){
 	  jtpt1sm = jtpt3sm;
	  jteta1 = jteta3;
	 }else if(jtpt3sm > jtpt2sm){
 	  jtpt2sm = jtpt3sm;
	  jteta2 = jteta3;
	 }
	}
    float ptavesm = (jtpt1sm + jtpt2sm)/2.;
    outf->cd();
	float entry[] = {jtpt1,jteta1,jtpt2,jteta2,jtpt3,jteta3,jtpt1sm,jtpt2sm,jtpt3sm,(float)thirdjetfeedup,weight1,weight2,jteta1sm, jteta2sm,jtpt1offset,jtpt2offset};
    ntdijet[ibin]->Fill(entry);
    if(ptavesm >= ptranges[ibin] && ptavesm < ptranges[ibin+1]){
 	 if(mode == "pp"){
	  histSmearDijetEta[ibin]->Fill(fabs(jteta1+jteta2)/2,weight1*weight2);
	  histSmearDijetEtaNoWeight[ibin]->Fill(fabs(jteta1+jteta2)/2,weight1*weight2);
 	 }if(mode == "pPb"){
	  histSmearDijetEta[ibin]->Fill((jteta1+jteta2)/2,weight1*weight2);
	  histSmearDijetEtaNoWeight[ibin]->Fill((jteta1+jteta2)/2);
	 }
	}
   }
  }
 }

 outf->cd();
 for(int ibin = 0; ibin < nbin; ibin++){
  histGenDijetEta[ibin]->Write();
  histGenDijetEtaNoWeight[ibin]->Write();
  histJESOffsetDijetEta[ibin]->Write();
  histJESOffsetDijetEtaNoWeight[ibin]->Write();
  histSmearDijetEta[ibin]->Write();
  histSmearDijetEtaNoWeight[ibin]->Write();
  histEtaSmearDijetEta[ibin]->Write();
  histEtaSmearDijetEtaNoWeight[ibin]->Write();
  ntdijet[ibin]->Write();
 }
 outf->Close();
 
}
 
