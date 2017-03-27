#include "../data_driven_jec/dijeteta/utilities.h"
#include "TStyle.h"

void drawCorrelations(){
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2(true);
  gStyle->SetPalette(71);
  bool doPtBinned = false;
  double histBound[19];
  int nHist = 6;
  TString Var = "";
  double max, min;
  cout << 1 << endl; 
  if(doPtBinned){
    nHist = 6; 
    double boundaries[] = {25., 55., 75., 95, 115, 150, 400};
    for(int i = 0; i < nHist+1; i++){
      histBound[i] = boundaries[i];
    }
    Var += "p_{T}^{ave}";
    max = 3.5;
    min = -3.5;
  }else{
    nHist = 18;
    double boundaries[]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};
   for(int i = 0; i < nHist+1; i++){
      histBound[i] = boundaries[i];
    }
   Var += "#eta_{dijet}";
   max = 400;
   min = 25;
  }
  cout << 2 << endl;
  //  TFile * file = new TFile("out_pearson_eta_v2.root"); //eta err fixed pt
  //TFile * file = new TFile("out_pearson_pt.root"); //pt err fixed pt
  TFile *file = new TFile("out_pearson_etafix_pterr_small.root");
  TH1D * hist[nHist];
  for(int i = 0; i < nHist; i++){
    if(doPtBinned) hist[i] = (TH1D*)file->Get(Form("histCorrCov_%d",i));
    else hist[i] = (TH1D*)file->Get(Form("histCorrPtCov_%d",i));
    hist[i]->SetMaximum(1.);
    hist[i]->SetMinimum(-1.);
  }
  cout << 3 << endl;
  TCanvas *c1;
  if(doPtBinned){
    c1 = new TCanvas("c1","",300*6, 600);
    makeMultiPanelCanvas(c1,6,1,0.0,0.0,0.22,0.22,0.15);
  }else{
    c1 = new TCanvas("c1","",300*6,1200);
    makeMultiPanelCanvas(c1,6,3,0.0,0.0,0.22,0.22,0.15);
  }
  cout << 4 << endl;
  TH1D * empty;
  if(doPtBinned) empty = new TH1D("empty","",10,-3.5, 3.5);
  else empty = new TH1D("empty","",4,25,400);
  if(doPtBinned) empty->Fill(1.,1000.);
  else empty->Fill(40.,1000.);
  empty->SetMaximum(max);
  empty->SetMinimum(min);
  if(doPtBinned){
    empty->GetXaxis()->SetTitle("#eta_{dijet}");
    empty->GetYaxis()->SetTitle("#eta_{dijet}");
    makePretty(empty,1.5,1.2);
  }
  else{
    empty->GetXaxis()->SetTitle("p_{T}^{ave}");
    empty->GetYaxis()->SetTitle("p_{T}^{ave}");
    makePretty(empty,3.0,2.2);
  }
  for(int i = 0; i < nHist; i++){
    c1->cd(i+1);
    empty->Draw();
    hist[i]->Draw("colz same");
    if(doPtBinned) drawText(Form("%.0f < %s < %.0f",histBound[i], Var.Data(),histBound[i+1]),0.05,0.9);
    else drawText(Form("%.3f < %s < %.3f",histBound[i], Var.Data(),histBound[i+1]),0.05,0.9);
  }
  c1->SaveAs("correlationsMultiPanel_FixedEta_PtErr.pdf");
}
