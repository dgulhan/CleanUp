#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TStyle.h"
#include "../dijeteta/utilities.h"
#include "TPaletteAxis.h"

void plotSingleJet2D(){
 TH1F::SetDefaultSumw2();
 TH1D::SetDefaultSumw2();
 TString algo = "ak3PF";
 int npt =8;
 float ptlow[]= {25,35,55,75,85,95,115,150,400}; 
 
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
                      
  // TString dataset[]={"hcalnoise","hcalnoise","hcalnoise && jet40","jet60 && hcalnoise","jet60 &&  hcalnoise","jet80 &&  hcalnoise","jet80 && hcalnoise","jet80 && hcalnoise"};

 
 int fileindex[]=  {0,1,1,1,1,2,2,2};
 int filemcindex[]={1,1,2,2,2,3,3,4};
 TFile *f_data[npt];
 double etacut=3;
 TFile * f_mc[npt];
 f_mc[0] = new TFile(Form("../ntuples/pthat15_%s.root",algo.Data()));
 f_mc[1] = new TFile(Form("../ntuples/pthat30_%s.root",algo.Data())); 
 f_mc[2] = new TFile(Form("../ntuples/pthat50_%s.root",algo.Data())); 
 f_mc[3] = new TFile(Form("../ntuples/pthat80_%s.root",algo.Data()));
 f_mc[4] = new TFile(Form("../ntuples/pthat120_%s.root",algo.Data()));
 f_mc[5] = new TFile(Form("../ntuples/pthat170_%s.root",algo.Data()));
 
 cout<<4<<endl;
 f_data[0] = new TFile(Form("../ntuples/minbias_%s_eta%d_corr2.root",algo.Data(),(int)etacut));
 f_data[1] = new TFile(Form("../ntuples/lowerpt_%s_eta%d_corr2.root",algo.Data(),(int)etacut));
 f_data[2] = new TFile(Form("../ntuples/jet80_%s_eta%d_corr2.root",algo.Data(),(int)etacut));
 
 TTree * nt_mc[filemcindex[npt-1]+1];
 TTree *nt_data[fileindex[npt-1]+1];
 
 for(int ifile = 0; ifile < 6; ifile++){
  nt_mc[ifile] = (TTree*)f_mc[ifile]->Get("ntgendijet");
 }
 for(int ifile = 0; ifile < 3; ifile++){
  nt_data[ifile] = (TTree*)f_data[ifile]->Get("ntdijet_corr");
 }

  
 TH2F *histNumber[2][npt];
 TH2F *histXval[2][npt];
 TH2F *histYval[2][npt];
 int nbins = 10; 
 // int nbins = 2; 

 TH1F *histDummyX[2][npt][nbins][neta];
  TH1F *histDummyY[2][npt][nbins][neta];
 for(int ijet = 0; ijet < 2; ijet++){
  for(int ipt = 0; ipt < npt; ipt++){
   cout<< ((ijet*npt)+ipt) <<"/"<<(npt*2) << endl;
   //set pt bins based on ptave selection
   float x1_min, x1_max;
   if(ijet == 0){
    x1_min = ptlow[ipt];
    x1_max = 2*ptlow[ipt+1]-20;
   }else{
    x1_min = 20;
	x1_max = ptlow[ipt+1];
   }  
   float bins[nbins+1];
   float inixx1=log(x1_min)/log(10);
   float deltax1=(log(x1_max)-log(x1_min))/(nbins*log(10));
   for(int ix=0; ix<nbins+1;ix++){
    bins[ix]=pow(10,inixx1); 
    inixx1+=deltax1;
   }
   
   
   histNumber[ijet][ipt] = new TH2F(Form("histJet%dPtEtaPtBin%d",ijet,ipt),"",nbins,bins,neta,etabins);
   histXval[ijet][ipt] =  new TH2F(Form("histJet%dXvalPtEtaPtBin%d",ijet,ipt),"",nbins,bins,neta,etabins);
   histYval[ijet][ipt] =  new TH2F(Form("histJet%dYvalPtEtaPtBin%d",ijet,ipt),"",nbins,bins,neta,etabins);
  
   nt_mc[filemcindex[ipt]]->Draw(Form("geneta%d:genpt%d>>histJet%dPtEtaPtBin%d",ijet+1,ijet+1,ijet,ipt),Form("genpt1>30 && genpt2>20 && ((genpt1+genpt2)/2)>=%.0f && ((genpt1+genpt2)/2)<%.0f && acos(cos(genphi1-genphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1]));
   // nt_data[fileindex[ipt]]->Draw(Form("%s>>hist_eta_%d_%d",var[ivar].Data(),ipt,ivar),Form("jtpt1>30 && jtpt2>20 && ((jtpt1+jtpt2)/2)>=%d && ((jtpt1+jtpt2)/2)<%d && %s", ptlow[ipt], ptlow[ipt+1], dataset[ipt].Data())); 

   for(int ibin = 0; ibin < nbins; ibin++){
    for(int ieta = 0; ieta < neta; ieta++){
     histDummyX[ijet][ipt][ibin][ieta] = new TH1F(Form("histDummyX%d%d%d%d",ijet,ipt,ibin,ieta),"",10,bins[ibin],bins[ibin+1]);
     histDummyY[ijet][ipt][ibin][ieta] = new TH1F(Form("histDummyY%d%d%d%d",ijet,ipt,ibin,ieta),"",10,etabins[ibin],etabins[ibin+1]);
	 nt_mc[filemcindex[ipt]]->Draw(Form("genpt%d>>histDummyX%d%d%d%d",ijet+1,ijet,ipt,ibin,ieta),Form("genpt1>30 && genpt2>20 && ((genpt1+genpt2)/2)>=%.0f && ((genpt1+genpt2)/2)<%.0f && acos(cos(genphi1-genphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1]));
	 nt_mc[filemcindex[ipt]]->Draw(Form("geneta%d>>histDummyY%d%d%d%d",ijet+1,ijet,ipt,ibin,ieta),Form("genpt1>30 && genpt2>20 && ((genpt1+genpt2)/2)>=%.0f && ((genpt1+genpt2)/2)<%.0f && acos(cos(genphi1-genphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1]));
	 histXval[ijet][ipt]->SetBinContent(ibin+1,ieta+1,histDummyX[ijet][ipt][ibin][ieta]->GetMean());
	 histYval[ijet][ipt]->SetBinContent(ibin+1,ieta+1,histDummyY[ijet][ipt][ibin][ieta]->GetMean());
	}
   }
   
  }
 }
 
 TFile * fileSingleJet = new TFile("SingleJet2D_20binsinpt.root","recreate");

 for(int ijet = 0; ijet < 2; ijet++){
  for(int ipt = 0; ipt < npt; ipt++){
   histNumber[ijet][ipt]->Write();
   histXval[ijet][ipt]->Write();
   histYval[ijet][ipt]->Write();
  } 
 } 
 fileSingleJet->Close();
 
}