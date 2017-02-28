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
#include "TPaletteAxis.h"

#include "../dijeteta/utilities.h"

void plotFake(){
 TH1F::SetDefaultSumw2();
 TString algo = "ak3PF";
 TString mode = "pp";
 int col[] = {kRed+1, kBlue-3, kAzure-9, kOrange-3, kTeal-7,kPink-4};

  int npt=6; 
 // int ptlow[]= {35,40,55,75,95,150,400}; 
 // int ptlow[]= {35,55,65,75,85,95,120,150,400};
 // int ptlow[]= {25,35,55,75,85,95,115,150,400}; 
 int ptlow[]= {25,55,75,95,115,150,400}; 


 int style[] = {20,21,34,33,22,23};
 int size[] = {1,1,2,2,2,2};
             
 // int netabins=32;
 int netabins=28;

 // double etabins_hcalbins[]= {0.0001,
                       // 0.174,    0.348,    0.522, 
                      // 0.696,   0.879,   1.044,   1.218,
                        // 1.392,   1.566,  1.740,  
                      // 1.930,   2.172,   2.500,  
                      // 2.999};

   float etabins_hcalbins[]= {-3.465,-2.999,-2.172,
                       -1.930, -1.740, -1.566, -1.392,
					   -1.218, -1.044, -0.879, -0.696,
					   -0.522, -0.348, -0.174,0.000,
                       0.174,    0.348,    0.522, 
                      0.696,   0.879,   1.044,   1.218,
                        1.392,   1.566,  1.740,  
                      1.930,   2.172,   
                      2.999,3.465}; 
   float etabins_hcalbins_pPb[]= {-2.999,-2.172,
                        -1.740, -1.392, -1.044, -0.696,
					    -0.348, 0.000,    0.348, 0.696,   1.044,   1.392,  1.740,  
                         2.172,   
                      2.999}; 
					  
 if(mode=="pPb"){
  netabins = 14;
  for(int ieta = 0; ieta < netabins+1; ieta++){
   etabins_hcalbins[ieta] = etabins_hcalbins_pPb[ieta];
  }
 }
 int filemcindex[]=  {1,2,3,3,4,5};

 double etacut=3;
 TFile * f_mc[npt];
 TFile * f_data[npt];
 if(mode == "pp"){
  f_mc[0] = new TFile(Form("../ntuples/pthat15_%s_eta4.root",algo.Data()));
  f_mc[1] = new TFile(Form("../ntuples/pthat30_%s_eta4.root",algo.Data()));
  f_mc[2] = new TFile(Form("../ntuples/pthat50_%s_eta4.root",algo.Data()));
  f_mc[3] = new TFile(Form("../ntuples/pthat80_%s_eta4.root",algo.Data()));
  f_mc[4] = new TFile(Form("../ntuples/pthat120_%s_eta4.root",algo.Data()));
  f_mc[5] = new TFile(Form("../ntuples/pthat170_%s_eta4.root",algo.Data()));
 }
 if(mode=="pPb"){
  f_mc[0] = new TFile(Form("../ntuples/ntuples_pthat15_rescorr2.root",algo.Data()));
  f_mc[1] = new TFile(Form("../ntuples/ntuples_pthat30_rescorr2.root",algo.Data()));
  f_mc[2] = new TFile(Form("../ntuples/ntuples_pthat50_rescorr2.root",algo.Data()));
  f_mc[3] = new TFile(Form("../ntuples/ntuples_pthat80_rescorr2.root",algo.Data()));
  f_mc[4] = new TFile(Form("../ntuples/ntuples_pthat120_rescorr2.root",algo.Data()));
  f_mc[5] = new TFile(Form("../ntuples/ntuples_pthat170_rescorr2.root",algo.Data()));
 }
 TLegend *t8=new TLegend(0.05,0.6,0.4,0.95); 
 t8->SetFillColor(0);
 t8->SetBorderSize(0);
 t8->SetFillStyle(0);
 t8->SetTextFont(43); 
 t8->SetTextSize(25);
 
 TTree * nt_mc[filemcindex[npt-1]+1];
 TTree * nt_data[filemcindex[npt-1]+1];
 TH1D * hist_deta[npt][2];
 TH1D * hist_dphi[npt][2];
 TH1D* histeta[npt][2][netabins];
 TH1D* histphi[npt][2][netabins];
 TF1 * gauseta[npt][2][netabins];
 TF1 * gausphi[npt][2][netabins];
 for(int ifile = 0; ifile < 6; ifile++){
  nt_mc[ifile] = (TTree*)f_mc[ifile]->Get("ntdijet");
 } 
 for(int ipt = 0; ipt < npt ; ipt++){
  for(int ijet = 0; ijet < 2; ijet++){
   hist_deta[ipt][ijet] = new TH1D(Form("hist_deta_%d_%d",ipt,ijet),";#eta;#sigma(#eta_{1})",netabins,etabins_hcalbins);
   hist_dphi[ipt][ijet] = new TH1D(Form("hist_dphi_%d_%d",ipt,ijet),";#eta;#sigma(#phi_{1})",netabins,etabins_hcalbins);
  
   for(int ieta = 0; ieta < netabins; ieta++){
    histeta[ipt][ijet][ieta] = new TH1D(Form("histeta%d%d%d",ipt,ijet,ieta),"",40,-0.1,0.1);
    histphi[ipt][ijet][ieta] = new TH1D(Form("histphi%d%d%d",ipt,ijet,ieta),"",40,-0.1,0.1);
	nt_mc[filemcindex[ipt]]->Draw(Form("jteta%d-refeta%d>>histeta%d%d%d",ijet+1,ijet+1,ipt,ijet,ieta),Form("jtpt1>30 && jtpt2>20 && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3) && ((jtpt1+jtpt2)/2) >= %d && ((jtpt1+jtpt2)/2)<%d && refeta%d>=%.3f && refeta%d<%.3f",ptlow[ipt],ptlow[ipt+1],ijet+1,etabins_hcalbins[ieta],ijet+1,etabins_hcalbins[ieta+1]));
	nt_mc[filemcindex[ipt]]->Draw(Form("jtphi%d-refphi%d>>histphi%d%d%d",ijet+1,ijet+1,ipt,ijet,ieta),Form("jtpt1>30 && jtpt2>20 && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3) && ((jtpt1+jtpt2)/2) >= %d && ((jtpt1+jtpt2)/2)<%d && refeta%d>=%.3f && refeta%d<%.3f",ptlow[ipt],ptlow[ipt+1],ijet+1,etabins_hcalbins[ieta],ijet+1,etabins_hcalbins[ieta+1]));
	gauseta[ipt][ijet][ieta] = new TF1(Form("gauseta%d%d%d",ipt,ijet,ieta),"gaus(0)",-0.1,0.1);
	gauseta[ipt][ijet][ieta]->SetParameters(1000.,0.,0.01);
	gausphi[ipt][ijet][ieta] = new TF1(Form("gauseta%d%d%d",ipt,ijet,ieta),"gaus(0)",-0.1,0.1);
	gausphi[ipt][ijet][ieta]->SetParameters(1000.,0.,0.01);
	histeta[ipt][ijet][ieta]->Fit(gauseta[ipt][ijet][ieta],"R");
	histphi[ipt][ijet][ieta]->Fit(gausphi[ipt][ijet][ieta],"R");
	
	hist_deta[ipt][ijet]->SetBinContent(ieta+1, fabs(gauseta[ipt][ijet][ieta]->GetParameter(2)));
	hist_deta[ipt][ijet]->SetBinError(ieta+1, gauseta[ipt][ijet][ieta]->GetParError(2));
	hist_dphi[ipt][ijet]->SetBinContent(ieta+1, fabs(gausphi[ipt][ijet][ieta]->GetParameter(2)));
	hist_dphi[ipt][ijet]->SetBinError(ieta+1, gausphi[ipt][ijet][ieta]->GetParError(2));
   }
   
   hist_deta[ipt][ijet]->SetMarkerColor(col[ijet]);
   hist_deta[ipt][ijet]->SetLineColor(col[ijet]);
   hist_deta[ipt][ijet]->SetMarkerStyle(style[ijet]);
   hist_deta[ipt][ijet]->SetMarkerSize(size[ijet]);
   hist_dphi[ipt][ijet]->SetMarkerColor(col[ijet]);
   hist_dphi[ipt][ijet]->SetLineColor(col[ijet]);
   hist_dphi[ipt][ijet]->SetMarkerStyle(style[ijet]);
   hist_dphi[ipt][ijet]->SetMarkerSize(size[ijet]);
  
  }
 } 
 t8->AddEntry(hist_deta[0][0],"leading jet","p");
 t8->AddEntry(hist_deta[0][1],"subleading jet","p");

 TH1D * empty = new TH1D("empty",";#eta;d#eta",netabins,etabins_hcalbins);
 empty->Fill(0.,1000);
 makePretty(empty,2.2);
 empty->SetMaximum(0.05);
 empty->SetMinimum(0.00001);
 makePretty(empty,2.2);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 TCanvas * c1 = new TCanvas("c1","",1600,1000);
  makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.22,0.22,0.02); 
 for(int ipt = 0; ipt < npt; ipt++){
  c1->cd(ipt+1);
  empty->Draw(); 
  for(int ijet=0; ijet<2;ijet++){
   hist_deta[ipt][ijet]->Draw("same");
  }
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.05);
  if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.05);
  if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.25);
  if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt ==5) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.25);
 }
 if(mode=="pp")drawText("PYTHIA", 0.25,0.9,25);
 if(mode=="pPb")drawText("PYTHIA+HIJING", 0.25,0.9,25);
 drawText("|#eta| < 3", 0.25,0.69,25);
 drawText("p_{T,1} > 30 GeV", 0.25,0.83,25);
 drawText("p_{T,2} > 20 GeV", 0.25,0.76,25);
 c1->cd(3);
 t8->Draw("same");
 c1->SaveAs(Form("deta_%s.png",mode.Data()));
 c1->SaveAs(Form("deta.pdf",mode.Data())); 

 TCanvas * c2 = new TCanvas("c2","",1600,1000);
  makeMultiPanelCanvas(c2,3,2,0.0,0.0,0.22,0.22,0.02); 
  TH1D * empty2 = (TH1D*)empty->Clone("empty2");
  empty2->GetYaxis()->SetTitle("d#phi");
 for(int ipt = 0; ipt < npt; ipt++){
  c2->cd(ipt+1);
  empty2->Draw(); 
  for(int ijet=0; ijet<2;ijet++){
   hist_dphi[ipt][ijet]->Draw("same");
  }
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.05);
  if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.05);
  if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.25);
  if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt ==5) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.25);
 }
 if(mode=="pp")drawText("PYTHIA", 0.25,0.9,25);
 if(mode=="pPb")drawText("PYTHIA+HIJING", 0.25,0.9,25);
 drawText("|#eta| < 3", 0.25,0.69,25);
 drawText("p_{T,1} > 30 GeV", 0.25,0.83,25);
 drawText("p_{T,2} > 20 GeV", 0.25,0.76,25);
 c2->cd(3);
  t8->Draw("same");

 c2->SaveAs(Form("dphi_%s.png",mode.Data()));
 c2->SaveAs(Form("dphi_%s.pdf",mode.Data())); 
 
 TFile *outf = new TFile(Form("../toyMC/pointingRes_%s.root",mode.Data()),"recreate");
 for(int ipt = 0; ipt < npt ; ipt++){
  for(int ijet = 0; ijet < 2; ijet++){
   hist_deta[ipt][ijet]->Write();
  }
 }
 outf->Close();
 
}