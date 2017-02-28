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

void plot2D(){
 TFile * fileSingleJet = new TFile("SingleJet2D_20binsinpt.root");
 int npt = 8;
 int ptlow[]= {25,35,55,75,85,95,115,150,400}; 
 TH2F* histNumber[2][npt];
 
 for(int ipt = 0; ipt < 8; ipt++){
  for(int ijet = 0; ijet < 2; ijet++){
   histNumber[ijet][ipt] = (TH2F*)fileSingleJet->Get(Form("histJet%dPtEtaPtBin%d",ijet,ipt));
   // histXval[ijet][ipt] = (TH2F*)fileSingleJet->Get(Form("histJet%dXvalPtEtaPtBin%d",ijet,ipt));
   // histYval[ijet][ipt] = (TH2F*)fileSingleJet->Get(Form("histJet%dYvalPtEtaPtBin%d",ijet,ipt));
  }
 }
 
 TCanvas * c1 = new TCanvas("c1","",1500,800);
 c1->Divide(4,2);
 for(int ipt = 0; ipt < npt; ipt++){
  c1->cd(ipt+1);
  histNumber[0][ipt]->GetXaxis()->SetTitle("p_{T,1}");
  histNumber[0][ipt]->GetYaxis()->SetTitle("#eta_{1}");
  histNumber[0][ipt]->Draw("colz");
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 1 || ipt == 2 || ipt == 3)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 5 || ipt ==6) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt ==7) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.25);
 }
 c1->SaveAs("plots/leadingnumber2d.png");
 c1->SaveAs("plots/leadingnumber2d.pdf");
 
 TCanvas * c2 = new TCanvas("c2","",1500,800);
 c2->Divide(4,2);
 for(int ipt = 0; ipt < npt; ipt++){
  c2->cd(ipt+1);
  histNumber[1][ipt]->GetXaxis()->SetTitle("p_{T,2}");
  histNumber[1][ipt]->GetYaxis()->SetTitle("#eta_{2}");
  histNumber[1][ipt]->Draw("colz");
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 1 || ipt == 2 || ipt == 3)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt == 5 || ipt ==6) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
  if(ipt ==7) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.25);
 }
 c2->SaveAs("plots/subleadingnumber2d.png");
 c2->SaveAs("plots/subleadingnumber2d.pdf");
 
  
 
  
}