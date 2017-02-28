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
#include "/afs/cern.ch/user/d/dgulhan/workDir/private/thesisPlots/dijetpPb/utilities.h"
#include "TPaletteAxis.h"

void getUnfolding(){
TH1D::SetDefaultSumw2();
 // TString mode[] = {"pp_noboost","pp_boost_v4_noweight_neg_test","pPb_boost_v4_noweight_test"};
 TString mode[] = {"pp_boost_v4_noweight_neg_test2","pPb_boost_v4_noweight_test2"};
 // TString mode[] = {"pp_boost","pPb_v3"};
 int npt = 6;
 int ptlow[]= {25,55,75,95,115,150,400}; 
 TH1F * histJER[3][npt];
 TH1F * histEtaR[3][npt];
 TH1F * histEtaS[3][npt];
 TH1F * histJES[3][npt];
 TH1F * histJESDMUp[3][npt];
 TH1F * histJESDMDown[3][npt];
 TH1F * histFake[3][npt];
 TH1F * histNeg[3][npt];
 TH1F * histPos[3][npt];
 TH1F * histUnfolding[3][npt];
 TFile *file[3];
 //cout << 1 << endl;
 // int col[] = {kRed+1, kPink+7, kViolet-1, kBlue-3, kTeal-1, kOrange-3, kYellow};
 int col[] = {TColor::GetColor("#CD0000"),TColor::GetColor("#FF7F50"),TColor::GetColor("#FFA824"),TColor::GetColor("#397D02"),TColor::GetColor("#388E8E"),TColor::GetColor("#009ACD"),TColor::GetColor("#5B59BA"),kAzure-9};

 TFile *filePU[3];
 
 filePU[0] = new TFile("outf_pileup_pp.root");
 filePU[1] = new TFile("outf_pileup_pp.root");
 filePU[2] = new TFile("outf_pileup_pPb.root");
 TH1F * histPileUp[3][npt];
 for(int imode = 0; imode < 2; imode++){
  for(int ipt = 0; ipt < npt; ipt++){
   histPileUp[imode][ipt] = (TH1F*)filePU[imode]->Get(Form("histPileUp%d",ipt));
  }
 }
 
 TFile *fileDir = new TFile("outf_pPb_pp_July12.root");
 TH1F * histDir[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  histDir[ipt] = (TH1F*)fileDir->Get(Form("hist_dir_syst_%d",ipt));
  histDir[ipt]->SetMarkerStyle(24);
  for(int ibin = 0; ibin < histDir[ipt]->GetNbinsX(); ibin++){
   histDir[ipt]->SetBinError(ibin+1,histDir[ipt]->GetBinError(ibin+1)/2.);
  }
 }
 
 for(int imode = 0; imode < 2; imode++){
  file[imode] = new TFile(Form("systematics_%s.root", mode[imode].Data()));
  // file[imode] = new TFile("systematics_pp_boost.root");
  for(int ipt = 0; ipt < 6; ipt++){ 
   //cout << imode << " " << ipt << endl;
   histJER[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRat%d",ipt));
   histEtaR[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatEtaRes%d",ipt));
   histEtaS[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatEtaOffset%d",ipt));

   histFake[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatFake%d",ipt));
   histJESDMUp[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatDataMCUp%d",ipt));
   histJESDMDown[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatDataMCDown%d",ipt));
   histJES[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatJESOffset%d",ipt));
   histUnfolding[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatUnfolding%d",ipt));
   histNeg[imode][ipt] = (TH1F*) file[imode]->Get(Form("histTotalNegative%d",ipt));
   histPos[imode][ipt] = (TH1F*) file[imode]->Get(Form("histTotalPositive%d",ipt));
   histNeg[imode][ipt]->SetName(Form("histTotalNegative%dMode%s",ipt,mode[imode].Data()));
   histPos[imode][ipt]->SetName(Form("histTotalPositive%dMode%s",ipt,mode[imode].Data()));
   
   histJER[imode][ipt]->SetMarkerColor(col[0]);
   histEtaR[imode][ipt]->SetMarkerColor(col[1]);
   histFake[imode][ipt]->SetMarkerColor(col[2]);
   histJESDMUp[imode][ipt]->SetMarkerColor(col[3]);
   histJESDMDown[imode][ipt]->SetMarkerColor(col[4]);
   histJES[imode][ipt]->SetMarkerColor(col[5]);
   histPileUp[imode][ipt]->SetMarkerColor(col[6]);
   histEtaS[imode][ipt]->SetMarkerColor(col[7]);
   histJER[imode][ipt]->SetLineColor(col[0]);
   histEtaR[imode][ipt]->SetLineColor(col[1]);
   histFake[imode][ipt]->SetLineColor(col[2]);
   histJESDMUp[imode][ipt]->SetLineColor(col[3]);
   histJESDMDown[imode][ipt]->SetLineColor(col[4]);
   histJES[imode][ipt]->SetLineColor(col[5]);
   histPileUp[imode][ipt]->SetLineColor(col[6]);
   histEtaS[imode][ipt]->SetLineColor(col[7]);
   
   // histUnfolding[imode][ipt] = (TH1F*) histJER[imode][ipt]->Clone(Form("histUnfolding_%s_%d",mode[imode].Data(),ipt));
   // histUnfolding[imode][ipt]->Add(histEtaR[imode][ipt]);
   
   int nbins = histNeg[imode][ipt]->GetNbinsX();
   
   for(int ibin = 0; ibin <  nbins; ibin++){
     float y = histNeg[imode][ipt]->GetBinContent(ibin+1);
     float x = histNeg[imode][ipt]->GetBinCenter(ibin+1);
	
	 if(imode == 2){
	  float ydir = histDir[ipt]->GetBinContent(histDir[ipt]->FindBin(x));
 	  y = -sqrt(pow(y-1,2.)+pow(ydir-1,2.)) + 1.;
	 }
	 
  	 float yetaoff = histEtaS[imode][ipt]->GetBinContent(ibin+1);
	 if(yetaoff < 1) y = -sqrt(pow(y-1,2.)+pow(yetaoff-1,2.)) + 1;

     float ypu = histPileUp[imode][ipt]->GetBinContent(histPileUp[imode][ipt]->FindBin(x));
     y = -sqrt(pow(y-1,2.)+pow(ypu-1,2.)) + 1.;
	 
	 float yfake = histFake[imode][ipt]->GetBinContent(ibin+1);
	 if(yfake > 1){
 	  y = -sqrt(pow(y-1,2)+pow(yfake-1,2))+1;
	 }
	 
	 histNeg[imode][ipt]->SetBinContent(ibin+1,y);
	 
   }
   for(int ibin = 0; ibin <  nbins; ibin++){
     float y = histPos[imode][ipt]->GetBinContent(ibin+1);
     float x = histPos[imode][ipt]->GetBinCenter(ibin+1);
     float yup = histPos[imode][ipt]->GetBinContent(ibin);
     float ydown = histPos[imode][ipt]->GetBinContent(ibin+2);
	
  	 float yfake = histFake[imode][ipt]->GetBinContent(ibin+1);
	 if(yfake < 1) y = sqrt(pow(y-1,2.)+pow(yfake-1,2.)) + 1;

  	 float yetaoff = histEtaS[imode][ipt]->GetBinContent(ibin+1);
	 cout << y << " " << yetaoff << endl;
	 if(yetaoff > 1) y = sqrt(pow(y-1,2.)+pow(yetaoff-1,2.)) + 1;
     cout << y << endl;

	 
     float ypu = histPileUp[imode][ipt]->GetBinContent(histPileUp[imode][ipt]->FindBin(x));
     y = sqrt(pow(y-1,2.)+pow(ypu-1,2.)) + 1.;
	 histPos[imode][ipt]->SetBinContent(ibin+1, y);
 

   }
  
  }
 }
 
 
 cout << 2<<endl;
 TLegend *t3_2=new TLegend(0.35,0.74,0.9,0.95);
 t3_2->SetFillColor(0);
 t3_2->SetBorderSize(0);
 t3_2->SetFillStyle(0);
 t3_2->SetTextFont(43);
 t3_2->SetTextSize(25); 
 TLegend *t3_1=new TLegend(0.35,0.74,0.9,0.95);
 t3_1->SetFillColor(0);
 t3_1->SetBorderSize(0);
 t3_1->SetFillStyle(0);
 t3_1->SetTextFont(43);
 t3_1->SetTextSize(25); 
 TLegend *t3_3=new TLegend(0.45,0.74,0.9,0.95);
 t3_3->SetFillColor(0);
 t3_3->SetBorderSize(0);
 t3_3->SetFillStyle(0);
 t3_3->SetTextFont(43);
 t3_3->SetTextSize(25); 
 
 t3_2->AddEntry(histJER[0][0],"JER","l");
 t3_2->AddEntry(histEtaR[0][0],"#eta res.","l");
 t3_2->AddEntry(histFake[0][0],"fake rate","l");
 t3_1->AddEntry(histJESDMUp[0][0],"JES D/M","l");
 t3_1->AddEntry(histJESDMDown[0][0],"JES D/M","l");
 t3_1->AddEntry(histJES[0][0],"JES MC","l");
 t3_3->AddEntry(histNeg[0][0],"Total Negative","l");
 t3_3->AddEntry(histPos[0][0],"Total Positive","l");
 t3_3->AddEntry(histPileUp[0][0],"Pile up","p");
 t3_1->AddEntry(histEtaS[0][0],"#eta offset","l");
 
 TH1D * empty;
 empty = new TH1D("empty",";|#eta_{dijet}|;Fractional uncertainty",10,-2.9999,3.0001);
 // else empty = new TH1D("empty",";|#eta_{dijet}|;JES Offset/Gen",10,0,2.9999);
 empty->Fill(0.,1000);
 empty->SetMaximum(1.49999);
 empty->SetMinimum(0.500001);
 makePretty(empty,2.7);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 TLine *line = new TLine(-2.999, 1., 2.999, 1.);
 for(int imode = 0; imode < 2; imode++){
  TCanvas * c6 = new TCanvas("c6","",1300,800);
  makeMultiPanelCanvas(c6,3,2,0.0,0.,0.27,0.25,0.02);
  for(int ipt = 0; ipt < npt; ipt++){
  
   cout << imode << " "<< ipt << endl;
   c6->cd(ipt+1);
   empty->Draw();
   // if(imode==2) histDir[ipt]->Draw("same");
   histPileUp[imode][ipt]->Draw("same");
   
   histJER[imode][ipt]->Draw("same hist");
   
   histEtaR[imode][ipt]->Draw("same hist");
   cout<<1<<endl;
   histEtaS[imode][ipt]->Draw("same hist");
   cout<<2<<endl;
   histFake[imode][ipt]->Draw("same hist");
   cout<<3<<endl;
   histJESDMUp[imode][ipt]->Draw("same hist");
   cout<<4<<endl;
   histJESDMDown[imode][ipt]->Draw("same hist");
   cout<<5<<endl;
   histJES[imode][ipt]->Draw("same hist");
   cout<<6<<endl;
   // histPileUp[imode][ipt]->Draw("same hist");
   
   
   histNeg[imode][ipt]->SetLineWidth(2);
   histPos[imode][ipt]->SetLineWidth(2);   
   // if(ipt==5) histNeg[imode][ipt]->SetBinContent(2, 0.72);

   histNeg[imode][ipt]->Draw("same hist");
   histPos[imode][ipt]->Draw("same hist"); 
   
   histPos[imode][ipt]->Draw("same hist"); 
   line->Draw("same");
   // if(imode == 2 && ipt == 0) t3_3->AddEntry(histDir[0],"Beam dir.","p");

   if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.05);
   if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.05);
   if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.27);
   if(ipt == 4 ) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.27);
   if(ipt ==5) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.27);
  }
  c6->cd(5);
  t3_2->Draw("same"); 
  c6->cd(6);
  t3_1->Draw("same");
  c6->cd(4);
  t3_3->Draw("same");
  c6->cd(1);
  // if(imode==0) drawText("Systematics for pp No boost",0.27,0.9,26);
  if(imode==0) drawText("Systematics for pp Boosted",0.27,0.9,26);
  if(imode==1) drawText("Systematics for pPb",0.27,0.9,26); 
  c6->cd(4);
  drawPatch(0.95,0.0,1.0,0.26);
  c6->cd(5);
  drawPatch(0.95,0.0,1.0,0.26);
  c6->SaveAs(Form("plots/summary_%s.png",mode[imode].Data()));
  c6->SaveAs(Form("plots/summary_%s.pdf",mode[imode].Data()));
 
 }
  cout << 3 << endl;

 TH1D * empty4;
 empty4 = new TH1D("empty4",";|#eta_{dijet}|;Bin by bin unfolding",10,-2.9999,3.0001);
 // else empty4 = new TH1D("empty4",";|#eta_{dijet}|;JES Offset/Gen",10,0,2.9999);
 empty4->Fill(0.,1000);
 empty4->SetMaximum(1.4999);
 empty4->SetMinimum(0.5001);
 makePretty(empty4,2.7);
 empty4->GetXaxis()->CenterTitle();
 empty4->GetYaxis()->CenterTitle();
 TLegend *t3_4=new TLegend(0.45,0.74,0.9,0.95);
 t3_4->SetFillColor(0);
 t3_4->SetBorderSize(0);
 t3_4->SetFillStyle(0);
 t3_4->SetTextFont(43);
 t3_4->SetTextSize(25); 
 t3_4->AddEntry(histUnfolding[0][0],"Unfolding","p");
 t3_4->AddEntry(histJER[0][0],"p_{T} resolution","l");
 t3_4->AddEntry(histEtaS[0][0],"#eta scale","l");
 TFile * outf = new TFile("outf_unfolding.root","recreate");
 for(int imode = 0; imode < 2; imode++){
  TCanvas * c5 = new TCanvas("c5","",1300,800);
  makeMultiPanelCanvas(c5,3,2,0.0,0.,0.27,0.25,0.02);
 
  for(int ipt = 0; ipt < npt; ipt++){
   c5->cd(ipt+1);
   empty4->Draw();
   histUnfolding[imode][ipt]->SetName(Form("UnfoldingPt%dMode%s",ipt,mode[imode].Data()));
   histUnfolding[imode][ipt]->Draw("same");
   histEtaS[imode][ipt]->Draw("same hist");
   histJER[imode][ipt]->Draw("same hist");

   histUnfolding[imode][ipt]->Write();
   histNeg[imode][ipt]->Write();
   histPos[imode][ipt]->Write();
   line->Draw("same");

   if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.05);
   if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.05);
   if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.27);
   if(ipt == 4 ) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.27);
   if(ipt ==5) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.27);
  }
  t3_4->Draw("same");
  c5->SaveAs(Form("plots/unfolding_%s.png",mode[imode].Data()));
  c5->SaveAs(Form("plots/unfolding_%s.pdf",mode[imode].Data()));
 }
 outf->Close();
 
}
