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
#include "/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/dijeteta/utilities.h"


void plotVsEta(){
 TH1D::SetDefaultSumw2();
 
 TString mode = "pPb";
 bool dopp = true;
 TTree *tjet1;
 TTree *tjet2;
 TH1D * hist[60];
 TH1D * hist2[60];
 TH1D * histptave[60];
 TH1D * histptave2[60];
 TF1 * fit[60];
 TF1 * fit2[60];
 // int neta = 22;
 // int neta = 60;
 int neta = 20;
 
 
 double etabins_hcalbins[]= {-3.465,   -2.853,
                      -2.500,  -2.172,  -1.930,
                     -1.740,  -1.566, -1.392,
                      -1.044,   -0.696,
                      -0.435,  -0.261,-0.087,  
                      0.087,   0.261,  0.435,  
                      0.696,    1.044,
                      1.392,  1.566,  1.740,
                      1.930,   2.172,  2.500,  2.853,
                      3.465};
					  

 double etabins_hcalbins_pPb[]= {-2.999,  
                      -2.500,  -2.172,  -1.930,
                     -1.740,  -1.566, -1.392,
                      -1.044,   -0.696,
                        -0.261,0.  ,
                        0.261,  
                      0.696,    1.044,
                      1.392,  1.566,  1.740,
                      1.930,   2.172,  2.500,  2.999
                      };
				
					  
  if(mode=="pPb"){
   neta = 21;
   for(int ieta = 0; ieta < neta; ieta++){
    etabins_hcalbins[ieta] = etabins_hcalbins_pPb[ieta];
   }
  }
  
  TFile*   file1;
  TFile*   file2;
  if(mode == "pp"){
   file1 = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/pthat%d_ak3PF_eta4.root",30));
   file2 = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/pthat%d_ak3PF_eta4.root",80));
  }
  if(mode=="pPb"){
   file1 = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/pPb_pthat%d.root",30));
   file2 = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/pPb_pthat%d.root",80));
  }
  tjet1 = (TTree*)file1->Get("ntjet"); 
  tjet2 = (TTree*)file2->Get("ntjet"); 
  tjet1->Print();
  tjet2->Print();
  // TFile * file1 = new TFile("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt50/HiForest_v77_merged01/pt50_HP04_prod16_v77_merged_forest_0.root");
  // TFile * file2 = new TFile("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt80/HiForest_v77_merged01/pt80_HP04_prod16_v77_merged_forest_0.root");
  // tjet1 = (TTree*)file1->Get("akPu3PFJetAnalyzer/t");
  // tjet2 = (TTree*)file2->Get("akPu3PFJetAnalyzer/t");

  for(int ieta=0;ieta<neta;ieta++){
   hist[ieta] = new TH1D(Form("hist%d",ieta),"",30,0,3);
   hist2[ieta] = new TH1D(Form("hist2%d",ieta),"",30,0,3);
   histptave[ieta] = new TH1D(Form("histptave%d",ieta),"",30,0,3);
   histptave2[ieta] = new TH1D(Form("histptave2%d",ieta),"",30,0,3);
   // cout<<Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>30",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1])<<endl;
   // tjet1->Draw(Form("jtpt/refpt>>hist%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>30",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
   // tjet2->Draw(Form("jtpt/refpt>>hist2%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>80",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
  // }
   tjet1->Draw(Form("jtpt/refpt>>hist%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>30",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
   tjet2->Draw(Form("jtpt/refpt>>hist2%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>100",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
   tjet1->Draw(Form("resol>>histptave%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>30",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
   tjet2->Draw(Form("resol>>histptave2%d",ieta),Form(" (jteta)>=%.3f && (jteta)<%.3f && refpt>100",etabins_hcalbins[ieta],etabins_hcalbins[ieta+1]));
  }
   
 
 TH1D *histvseta;
 TH1D *histvseta2;
 double mean[neta];
 double meanerr[neta];
 double eta[neta];
 double etaerr[neta];
 double mean2[neta];
 double meanerr2[neta];
 double eta2[neta];
 double etaerr2[neta];
 TGraphErrors* graph;
 TGraphErrors* graph2;
  TH1D * resvseta = new TH1D(Form("resvseta"),";#eta;#mu",neta,etabins_hcalbins);
  TH1D* resvseta2 = new TH1D(Form("resvseta2"),";#eta;#mu",neta,etabins_hcalbins);
 TH1D* resvsetafit[3];
 TH1D* resvsetafit2[3];

  histvseta = new TH1D(Form("histvseta"),";#eta;#mu",neta,etabins_hcalbins);
  histvseta2 = new TH1D(Form("histvseta2"),";#eta;#mu",neta,etabins_hcalbins);
  for(int ieta = 0; ieta<neta;ieta++){
   fit[ieta] = new TF1(Form("fit%d",ieta),"gaus(0)",0.6,2.0);
   fit[ieta]->SetParameters(100,1.,0.4);
   hist[ieta]->Fit(fit[ieta],"R");
   fit2[ieta] = new TF1(Form("fit2%d",ieta),"gaus(0)",0.6,2.0);
   fit2[ieta]->SetParameters(100,1.,0.4);
   hist2[ieta]->Fit(fit2[ieta],"R");
   histvseta->SetBinContent(ieta+1,fit[ieta]->GetParameter(1));
   histvseta->SetBinError(ieta+1,fit[ieta]->GetParError(1));
   histvseta2->SetBinContent(ieta+1,fit2[ieta]->GetParameter(1));
   histvseta2->SetBinError(ieta+1,fit2[ieta]->GetParError(1));
   resvseta->SetBinContent(ieta+1,fabs(fit[ieta]->GetParameter(2))-histptave[ieta]->GetMean());
   resvseta->SetBinError(ieta+1,fit[ieta]->GetParError(2));
   resvseta2->SetBinContent(ieta+1,fabs(fit2[ieta]->GetParameter(2))-histptave2[ieta]->GetMean());
   resvseta2->SetBinError(ieta+1,fit2[ieta]->GetParError(2));
   mean[ieta] = fit[ieta]->GetParameter(1);
   meanerr[ieta] = fit[ieta]->GetParError(1);
   eta[ieta] = (etabins_hcalbins[ieta]+etabins_hcalbins[ieta+1])/2.;
   etaerr[ieta] = 0;
   mean2[ieta] = fit2[ieta]->GetParameter(1);
   meanerr2[ieta] = fit2[ieta]->GetParError(1);
   eta2[ieta] = (etabins_hcalbins[ieta]+etabins_hcalbins[ieta+1])/2.;
   etaerr2[ieta] = 0;
  }
  graph = new TGraphErrors(neta,eta,mean,etaerr,meanerr);
  graph2 = new TGraphErrors(neta,eta2,mean2,etaerr2,meanerr2);
  
   TF1 * fitResol[2][3];
   float meanfit[] = {-2,0,2};
 for(int ifile = 0; ifile < 2; ifile++){
  // fitResol[ifile][0] = new TF1(Form("fitResol%d%d",ifile,0),"[0]+[1]*x+[2]*x*x",-3.5,-1.4);
  // fitResol[ifile][1] = new TF1(Form("fitResol%d%d",ifile,1),"[0]+[1]*x+[2]*x*x",-1.2,1.2);
  // fitResol[ifile][2] = new TF1(Form("fitResol%d%d",ifile,2),"[0]+[1]*x+[2]*x*x",1.4,3.5);
  if(mode == "pp"){
   fitResol[ifile][0] = new TF1(Form("fitResol%d%d",ifile,0),"[0]+[1]*pow(x-[2],2.)",-3.5,-1.6);
   fitResol[ifile][1] = new TF1(Form("fitResol%d%d",ifile,1),"[0]+[1]*pow(x-[2],2.)*pow(x-[3],2.)",-1.5,1.5);
   fitResol[ifile][2] = new TF1(Form("fitResol%d%d",ifile,2),"[0]+[1]*pow(x-[2],2.)",1.6,3.5);
  }if(mode == "pPb"){
   fitResol[ifile][0] = new TF1(Form("fitResol%d%d",ifile,0),"[0]+[1]*pow(x-[2],2.)",-3.,-1.6);
   fitResol[ifile][1] = new TF1(Form("fitResol%d%d",ifile,1),"[0]+[1]*pow(x-[2],2.)*pow(x-[3],2.)",-1.5,1.5);
   fitResol[ifile][2] = new TF1(Form("fitResol%d%d",ifile,2),"[0]+[1]*pow(x-[2],2.)",1.6,3.);
  }
  for(int ifit = 0; ifit<3; ifit++){
   if(ifit != 1)fitResol[ifile][ifit]->SetParameters(0.2,1.,meanfit[ifit]);
   else fitResol[ifile][ifit]->SetParameters(0.2,1.,-0.5,0.5);
  } 
 }
 for(int ifitResol = 0; ifitResol < 3; ifitResol++){
  resvsetafit[ifitResol] = (TH1D*)resvseta->Clone(Form("resvsetafit%d",ifitResol));
  resvsetafit2[ifitResol] = (TH1D*)resvseta2->Clone(Form("resvsetafit2%d",ifitResol));
  resvsetafit[ifitResol]->Fit(fitResol[0][ifitResol],"R");
  resvsetafit2[ifitResol]->Fit(fitResol[1][ifitResol],"R");
 }
 histvseta2->SetMarkerStyle(24);
 TLegend *t3=new TLegend(0.45,0.8,0.9,0.93);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->SetFillStyle(0);
 t3->SetTextFont(43);
 t3->SetTextSize(25); 
 t3->AddEntry(histvseta, "p_{T}^{gen} > 30 GeV", "p" );
 t3->AddEntry(histvseta2, "p_{T}^{gen} > 100 GeV", "p" );
 // TCanvas * c1 =new TCanvas("c1","",1200,400);
 TCanvas * c1 =new TCanvas("c1","",600,600);
 TH1D * empty = new TH1D("empty",";#eta;#mu",30,-3.465,3.465);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 empty->Fill(0.,1000.);
 empty->SetMaximum(1.05);
 empty->SetMinimum(0.95);
 TLine line(-3.465,1.,3.465,1.); 
 empty->Draw();
 histvseta->Draw("same p");
 histvseta2->Draw("same p");
 line.Draw("same");
 drawText("R = 0.3 PF Jet",0.25,0.75);
 drawText("PYTHIA + HIJING",0.25,0.65);
 t3->Draw("same");
 // drawText("p_{T}^{gen} > 30 GeV",0.25,0.25);
 c1->SaveAs(Form("ppVsEta_ak3PF_%s.png",mode.Data()));
 c1->SaveAs(Form("ppVsEta_ak3PF_%s.pdf",mode.Data()));
 
 TCanvas * c2 =new TCanvas("c2","",600,600);
 TH1D * empty2 = new TH1D("empty2",";#eta;#sigma",30,-3.465,3.465);
 empty2->GetXaxis()->CenterTitle();
 empty2->GetYaxis()->CenterTitle();
 empty2->Fill(0.,1000.);
 empty2->SetMaximum(0.3);
 empty2->SetMinimum(-0.3);
 empty2->Draw();
 resvseta->Draw("same p");
 resvseta2->SetMarkerStyle(24);
 resvseta2->Draw("same p");
 drawText("R = 0.3 PF Jet",0.25,0.25);
 drawText("PYTHIA",0.6,0.25);
 for(int ifile = 0; ifile < 2; ifile++){
  for(int ifit = 0; ifit < 3; ifit++){
   fitResol[ifile][ifit]->Draw("same");
  }
 }
 t3->Draw("same");
 // drawText("p_{T}^{gen} > 30 GeV",0.25,0.25);
 c2->SaveAs(Form("resppVsEta_ak3PF_%s.png",mode.Data()));
 c2->SaveAs(Form("resppVsEta_ak3PF_%s.pdf",mode.Data()));

 
 TFile *outf = new TFile("resolution/resvseta.root","recreate");
 for(int ifile = 0; ifile < 2; ifile++){
  for(int ifit = 0; ifit < 3; ifit++){
   fitResol[ifile][ifit]->Write();
  }
 }
 resvseta->Write();
 resvseta2->Write();
 histvseta->Write();
 histvseta2->Write();
 outf->Close();
}
