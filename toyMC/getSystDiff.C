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
void getSystRat(){
TH1D::SetDefaultSumw2();
 TString mode[2] = {"pPb_boost_v4_noweight_forrat_test2","pp_boost_v4_noweight_neg_forrat_test3"};
 // TString mode[] = {"pp_boost","pPb_v3"};
 int npt = 6;
  cout << 0 << endl;
 float scalefake[] = {1.10, 1.20, 1.30, 1.40, 1.50, 2.00};
 int ptlow[]= {25,55,75,95,115,150,400}; 
 TH1F * histEtaSmearDijetEta[3][npt];
 TH1F * histSmearDijetEta[3][npt];
 TH1F * histGenDijetEta[3][npt];
 TH1F * histJESDataMCUp[3][npt];
 TH1F * histJESDataMCDown[3][npt];
 TH1F * histRatFake[3][npt];
 TH1F * histJESOffset[3][npt];
 TH1F * histEtaOffset[3][npt];
 
 TH1F * histdRatEtaSmearDijetEta[npt];
 TH1F * histdRatSmearDijetEta[npt];
 TH1F * histdRatGenDijetEta[npt];
 TH1F * histdRatJESDataMCUp[npt];
 TH1F * histdRatJESDataMCDown[npt];
 TH1F * histdRatFake[npt];
 TH1F * histdRatPileUp[npt];
 TH1F * histdRatJESOffset[npt];
 TH1F * histdRatEtaOffset[npt];
 TH1F * histdRatTotalNeg[npt];
 TH1F * histdRatTotalPos[npt];
 TFile *file[3];
 int col[] = {TColor::GetColor("#CD0000"),TColor::GetColor("#FF7F50"),TColor::GetColor("#FFA824"),TColor::GetColor("#397D02"),TColor::GetColor("#388E8E"),TColor::GetColor("#009ACD"),TColor::GetColor("#5B59BA"),kAzure-9};
 cout << 1 << endl;

 cout << 2 << endl;
 
 TFile * file_dir = new TFile("outf_pPb_pp_July12.root");
 TH1D * histDir[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  histDir[ipt] = (TH1D*)file_dir->Get(Form("hist_dir_syst_%d",ipt));
  histDir[ipt]->SetMarkerStyle(25);
  for(int ibin = 0; ibin < histDir[ipt]->GetNbinsX(); ibin++){
   histDir[ipt]->SetBinError(ibin+1,histDir[ipt]->GetBinError(ibin+1)/2.);
  }
 }
 int nbins = histDir[0]->GetNbinsX();
 
 TFile *filePU[2];
 filePU[0] = new TFile("outf_pileup_pp.root");
 filePU[1] = new TFile("outf_pileup_pPb.root");
 TH1F * histPileUpTmp[3][npt];
 TH1F * histPileUp[3][npt];
 for(int imode = 0; imode < 2; imode++){
  for(int ipt = 0; ipt < npt; ipt++){
   histPileUpTmp[imode][ipt] = (TH1F*)filePU[imode]->Get(Form("histPileUp%d",ipt));
   histPileUp[imode][ipt] = (TH1F*)histDir[ipt]->Clone(Form("histPileUp%d%d",imode,ipt));
   
   for(int ibin = 0; ibin < histDir[ipt]->GetNbinsX(); ibin++){
    histPileUp[imode][ipt]->SetBinContent(ibin+1, histPileUpTmp[imode][ipt]->GetBinContent(histPileUpTmp[imode][ipt]->FindBin(histPileUp[imode][ipt]->GetBinCenter(ibin+1))));
   }
  }
 }
  cout << 4 << endl;

 for(int imode = 0; imode < 2; imode++){
  cout << "top" << "imode"<<imode <<endl;
  file[imode] = new TFile(Form("systematics_%s.root", mode[imode].Data()));
  // file[imode] = new TFile("systematics_pp_boost.root");
  for(int ipt = 0; ipt < 6; ipt++){ 
   cout << imode << " " << ipt << "imode"<<imode <<endl;
   
   histSmearDijetEta[imode][ipt] = (TH1F*) file[imode]->Get(Form("histSmearDijetEta%d",ipt));
   histEtaSmearDijetEta[imode][ipt] = (TH1F*) file[imode]->Get(Form("histEtaSmearDijetEta%d",ipt));
   histGenDijetEta[imode][ipt] = (TH1F*) file[imode]->Get(Form("histGenDijetEta%d",ipt));
   histJESDataMCUp[imode][ipt] = (TH1F*) file[imode]->Get(Form("histJESDataMCUp%d",ipt));
   histJESDataMCDown[imode][ipt] = (TH1F*) file[imode]->Get(Form("histJESDataMCDown%d",ipt));
   histRatFake[imode][ipt] = (TH1F*) file[imode]->Get(Form("histRatFake%d",ipt));
   histJESOffset[imode][ipt] = (TH1F*) file[imode]->Get(Form("histJESOffsetDijetEta%d",ipt));
   histEtaOffset[imode][ipt] = (TH1F*) file[imode]->Get(Form("histEtaOffset%d",ipt));
   
   histSmearDijetEta[imode][ipt]->SetName(Form("histSmearDijetEta%d%d",imode,ipt));
   histEtaSmearDijetEta[imode][ipt]->SetName(Form("histEtaSmearDijetEta%d%d",imode,ipt));
   histGenDijetEta[imode][ipt]->SetName(Form("histGenDijetEta%d%d",imode,ipt));
   histJESDataMCUp[imode][ipt]->SetName(Form("histJESDataMCUp%d%d",imode,ipt));
   histJESDataMCDown[imode][ipt]->SetName(Form("histJESDataMCDown%d%d",imode,ipt));
   histRatFake[imode][ipt]->SetName(Form("histRatFake%d%d",imode,ipt));
   histJESOffset[imode][ipt]->SetName(Form("histJESOffset%d%d",imode,ipt));
   histEtaOffset[imode][ipt]->SetName(Form("histEtaOffset%d%d",imode,ipt));
   for(int ibin = 0; ibin < nbins; ibin++){
    histSmearDijetEta[imode][ipt]->SetBinContent(ibin+1, histSmearDijetEta[imode][ipt]->GetBinContent(ibin+1)/histSmearDijetEta[imode][ipt]->GetBinWidth(ibin+1));
    histEtaSmearDijetEta[imode][ipt]->SetBinContent(ibin+1, histEtaSmearDijetEta[imode][ipt]->GetBinContent(ibin+1)/histEtaSmearDijetEta[imode][ipt]->GetBinWidth(ibin+1));
    histGenDijetEta[imode][ipt]->SetBinContent(ibin+1, histGenDijetEta[imode][ipt]->GetBinContent(ibin+1)/histGenDijetEta[imode][ipt]->GetBinWidth(ibin+1));
    histJESDataMCUp[imode][ipt]->SetBinContent(ibin+1, histJESDataMCUp[imode][ipt]->GetBinContent(ibin+1)/histJESDataMCUp[imode][ipt]->GetBinWidth(ibin+1));
    histJESDataMCDown[imode][ipt]->SetBinContent(ibin+1, histJESDataMCDown[imode][ipt]->GetBinContent(ibin+1)/histJESDataMCDown[imode][ipt]->GetBinWidth(ibin+1));
    histJESOffset[imode][ipt]->SetBinContent(ibin+1, histJESOffset[imode][ipt]->GetBinContent(ibin+1)/histJESOffset[imode][ipt]->GetBinWidth(ibin+1));
    histEtaOffset[imode][ipt]->SetBinContent(ibin+1, histEtaOffset[imode][ipt]->GetBinContent(ibin+1)/histEtaOffset[imode][ipt]->GetBinWidth(ibin+1));
   }   
   
   for(int ibin = 0; ibin < nbins; ibin++){
    float geny = histGenDijetEta[imode][ipt]->GetBinContent(ibin+1);
    float genyerr = histGenDijetEta[imode][ipt]->GetBinError(ibin+1);
    float fakey = histRatFake[imode][ipt]->GetBinContent(ibin+1);
    float fakeyerr = histRatFake[imode][ipt]->GetBinError(ibin+1);
    float puy = histPileUp[imode][ipt]->GetBinContent(ibin+1);
    float puyerr = histPileUp[imode][ipt]->GetBinError(ibin+1);
	float fakeerrcomb = sqrt(pow(geny*fakeyerr,2.)+pow(fakey*genyerr,2.));
	float puerrcomb = 0.3*sqrt(pow(geny*puyerr,2.)+pow(genyerr,2.));
	fakey = fakey*geny-geny;
	puy = puy*geny-geny;
    histRatFake[imode][ipt]->SetBinContent(ibin+1,fakey);
    histRatFake[imode][ipt]->SetBinError(ibin+1,fakeerrcomb);
    histPileUp[imode][ipt]->SetBinContent(ibin+1,puy);
    histPileUp[imode][ipt]->SetBinError(ibin+1,puerrcomb);
   }  
   
   // histRatFake[imode][ipt]->Multiply(histGenDijetEta[imode][ipt]);
   // histPileUp[imode][ipt]->Multiply(histGenDijetEta[imode][ipt]);
   // histRatFake[imode][ipt]->Add(histGenDijetEta[imode][ipt],-1);
   // histPileUp[imode][ipt]->Add(histGenDijetEta[imode][ipt],-1);

   histSmearDijetEta[imode][ipt]->SetMarkerColor(col[0]);
   histEtaSmearDijetEta[imode][ipt]->SetMarkerColor(col[1]);
   histRatFake[imode][ipt]->SetMarkerColor(col[2]);
   histJESDataMCUp[imode][ipt]->SetMarkerColor(col[3]);
   histJESDataMCDown[imode][ipt]->SetMarkerColor(col[4]);

   histJESOffset[imode][ipt]->SetMarkerColor(col[5]);
   histSmearDijetEta[imode][ipt]->SetLineColor(col[0]);
   histEtaSmearDijetEta[imode][ipt]->SetLineColor(col[1]);
   histRatFake[imode][ipt]->SetLineColor(col[2]);
   histJESDataMCUp[imode][ipt]->SetLineColor(col[3]);
   histJESDataMCDown[imode][ipt]->SetLineColor(col[4]);
   histJESOffset[imode][ipt]->SetLineColor(col[5]);
   histEtaOffset[imode][ipt]->SetLineColor(col[6]);
   // histSmearDijetEta[imode][ipt]->Print("all");
   // histSmearDijetEta[0][ipt]->Print("all");
   if(imode==1){
     cout << imode<<endl;
     histdRatSmearDijetEta[ipt] = (TH1F*)histSmearDijetEta[0][ipt]->Clone(Form("histdRatSmearDijetEta%d",ipt));

     histdRatEtaSmearDijetEta[ipt] = (TH1F*)histEtaSmearDijetEta[0][ipt]->Clone(Form("histdRatEtaSmearDijetEta%d",ipt));
     histdRatJESDataMCUp[ipt] = (TH1F*)histJESDataMCUp[0][ipt]->Clone(Form("histdRatJESDataMCUp%d",ipt));
     histdRatJESDataMCDown[ipt] = (TH1F*)histJESDataMCDown[0][ipt]->Clone(Form("histdRatJESDataMCDown%d",ipt));
     histdRatFake[ipt] = (TH1F*)histRatFake[0][ipt]->Clone(Form("histdRatFake%d",ipt));
     histdRatPileUp[ipt] = (TH1F*)histPileUp[0][ipt]->Clone(Form("histdRatPileUp%d",ipt));
     histdRatJESOffset[ipt] = (TH1F*)histJESOffset[0][ipt]->Clone(Form("histdRatJESOffset%d",ipt));  
     histdRatEtaOffset[ipt] = (TH1F*)histEtaOffset[0][ipt]->Clone(Form("histdRatEtaOffset%d",ipt));  
     histdRatGenDijetEta[ipt] = (TH1F*)histGenDijetEta[0][ipt]->Clone(Form("histdRatGenDijetEta%d",ipt));  

  	 cout<<8.<<endl;
	 histdRatFake[ipt]->Add(histRatFake[imode][ipt],1);
  	 cout<<8.0<<endl;
	 
	 histdRatSmearDijetEta[ipt]->Add(histSmearDijetEta[imode][ipt],-1);
       	 cout<<8.1<<endl;
     histdRatEtaSmearDijetEta[ipt]->Add(histEtaSmearDijetEta[imode][ipt],-1);
       	 cout<<8.2<<endl;
     histdRatJESDataMCUp[ipt]->Add(histGenDijetEta[imode][ipt],-1); 
       	 cout<<8.3<<endl;
     histdRatJESDataMCDown[ipt]->Add(histGenDijetEta[imode][ipt],-1);
       	 cout<<8.4<<endl;
     histdRatJESOffset[ipt]->Add(histJESOffset[imode][ipt],-1);
     histdRatEtaOffset[ipt]->Add(histEtaOffset[imode][ipt],-1);
       	 cout<<8.5<<endl;
     histdRatGenDijetEta[ipt]->Add(histGenDijetEta[imode][ipt],-1);
       	 cout<<8.6<<endl;
 	 histdRatSmearDijetEta[ipt]->Add(histdRatGenDijetEta[ipt],-1);
       	 cout<<8.7<<endl;
     histdRatEtaSmearDijetEta[ipt]->Add(histdRatGenDijetEta[ipt],-1);
       	 cout<<8.8<<endl;
     histdRatJESDataMCUp[ipt]->Add(histdRatGenDijetEta[ipt],-1);
       	 cout<<8.9<<endl;
	 histdRatJESDataMCDown[ipt]->Add(histdRatGenDijetEta[ipt],-1);
       	 cout<<8.10<<endl;
     histdRatJESOffset[ipt]->Add(histdRatGenDijetEta[ipt],-1);
     histdRatEtaOffset[ipt]->Add(histdRatGenDijetEta[ipt],-1);
       	 cout<<8.11<<endl;
	 histdRatTotalNeg[ipt] = (TH1F*)histdRatJESOffset[ipt]->Clone(Form("histdRatTotalNeg%d",ipt));
       	 cout<<8.12<<endl;
	 histdRatTotalPos[ipt] = (TH1F*)histdRatJESOffset[ipt]->Clone(Form("histdRatTotalPos%d",ipt));
  	 cout<<8.3<<endl;
     
	 // int nbins = histdRatFake[ipt]->GetNbinsX();
	 // for(int ibin = 0; ibin < nbins; ibin++){
	  // histdRatFake[ipt]->SetBinContent(ibin+1, sqrt(pow(histRatFake[0][ipt]->GetBinContent(ibin+1)-1,2)+pow(histRatFake[1][ipt]->GetBinContent(ibin+1)-1,2))+1);
	  // histdRatPileUp[ipt]->SetBinContent(ibin+1, sqrt(pow(histPileUp[0][ipt]->GetBinContent(ibin+1)-1,2)+pow(histPileUp[1][ipt]->GetBinContent(ibin+1)-1,2))+1);
	 // }
	 
	 for(int ibin = 0; ibin < nbins; ibin++){
      float y[8];
  	  y[0] = histdRatSmearDijetEta[ipt]->GetBinContent(ibin+1);
      y[1] = histdRatEtaSmearDijetEta[ipt]->GetBinContent(ibin+1);
      y[2] = histdRatJESDataMCUp[ipt]->GetBinContent(ibin+1);
	  y[3] = histdRatJESDataMCDown[ipt]->GetBinContent(ibin+1);
      y[4] = histdRatJESOffset[ipt]->GetBinContent(ibin+1);
	  y[5] = scalefake[ipt]*histdRatFake[ipt]->GetBinContent(ibin+1);
	  y[6] = histdRatEtaOffset[ipt]->GetBinContent(ibin+1);
	  y[7] = histdRatPileUp[ipt]->GetBinContent(ibin+1);
	  float totalpos = 0;
	  float totalneg = 0;
	  float total = 0;
	  for(int isource = 0; isource < 8; isource++){
	    if(isource == 5 || isource==6 || isource==7 ){
		 totalpos+=pow(y[isource],2.);
		 totalneg+=pow(y[isource],2.);
		 total+=pow(y[isource],2.);
		}
		else{
	     if(y[isource]>0) totalpos+=pow(y[isource],2.);
	     if(y[isource]<0) totalneg+=pow(y[isource],2.);
	     if(isource!=3)total+=pow(y[isource],2.);
		}
	  }
	  totalpos = sqrt(totalpos);
	  totalneg = -sqrt(totalneg);
	  total = -sqrt(total);
	  histdRatTotalPos[ipt]->SetBinContent(ibin+1, total);
	  histdRatTotalNeg[ipt]->SetBinContent(ibin+1, -total);
	 } 
   }
   // histUnfolding[imode][ipt] = (TH1F*) histJER[imode][ipt]->Clone(Form("histUnfolding_%s_%d",mode[imode].Data(),ipt));
   // histUnfolding[imode][ipt]->Add(histEtaR[imode][ipt]);
  }
 }
 
 cout << 2<<endl;
 TLegend *t3_2=new TLegend(0.35,0.7,0.9,0.98);
 t3_2->SetFillColor(0);
 t3_2->SetBorderSize(0);
 t3_2->SetFillStyle(0);
 t3_2->SetTextFont(43);
 t3_2->SetTextSize(24); 
 TLegend *t3_1=new TLegend(0.35,0.7,0.9,0.98);
 t3_1->SetFillColor(0);
 t3_1->SetBorderSize(0);
 t3_1->SetFillStyle(0);
 t3_1->SetTextFont(43);
 t3_1->SetTextSize(24); 
 TLegend *t3_3=new TLegend(0.35,0.7,0.9,0.98);
 t3_3->SetFillColor(0);
 t3_3->SetBorderSize(0);
 t3_3->SetFillStyle(0);
 t3_3->SetTextFont(43);
 t3_3->SetTextSize(24); 
 t3_2->AddEntry(histdRatSmearDijetEta[0],"JER","l");
 t3_2->AddEntry(histdRatEtaSmearDijetEta[0],"#eta res.","l");
 t3_2->AddEntry(histdRatFake[0],"fake rate","l");
 t3_1->AddEntry(histdRatJESDataMCUp[0],"JES D/M","l");
 t3_1->AddEntry(histdRatJESDataMCDown[0],"JES D/M","l");
 t3_1->AddEntry(histdRatJESOffset[0],"JES MC","l");
 t3_3->AddEntry(histdRatTotalPos[0],"Total Positive","l");
 t3_3->AddEntry(histdRatTotalNeg[0],"Total Negative","l");
 t3_3->AddEntry(histdRatEtaOffset[0],"#eta offset","l");
 t3_3->AddEntry(histdRatPileUp[0],"Pile up","p");
 
 TH1D * empty;
 empty = new TH1D("empty",";|#eta_{dijet}|;Absolute uncertainty",10,-2.9999,3.0001);
 // else empty = new TH1D("empty",";|#eta_{dijet}|;JES Offset/Gen",10,0,2.9999);
 empty->Fill(0.,1000);
 empty->SetMaximum(0.02);
 empty->SetMinimum(-0.02);
 makePretty(empty,2.7);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 TLine *line = new TLine(-2.999, 1., 2.999, 1.);
 for(int imode = 0; imode < 1; imode++){
  TCanvas * c6 = new TCanvas("c6","",1300,800);
  makeMultiPanelCanvas(c6,3,2,0.0,0.,0.27,0.22,0.02);
  for(int ipt = 0; ipt < npt; ipt++){
  
   cout << imode << " "<< ipt << "imode"<<imode <<endl;
   cout << 3 << "imode"<<imode <<endl;
   c6->cd(ipt+1);
   cout << 4 << "imode"<<imode <<endl;
   empty->Draw();
  // histGenDijetEta[0][ipt]->Draw();
  // histGenDijetEta[1][ipt]->Draw("same hist");
   histdRatSmearDijetEta[ipt]->Draw("same hist");
   histdRatEtaSmearDijetEta[ipt]->Draw("same hist");
   histdRatJESDataMCUp[ipt]->Draw("same hist");
   histdRatJESDataMCDown[ipt]->Draw("same hist");
   histdRatJESOffset[ipt]->Draw("same hist");
   histdRatFake[ipt]->Draw("same hist"); 
   histdRatTotalNeg[ipt]->SetLineColor(kBlack);
   histdRatTotalPos[ipt]->SetLineColor(kBlack);
   histdRatEtaOffset[ipt]->Draw("same hist");
   // histDir[ipt]->Draw("same");
   histdRatTotalPos[ipt]->Draw("same hist");
   histdRatTotalNeg[ipt]->Draw("same hist");
   line->Draw("same");
   histdRatPileUp[ipt]->Draw("same");
   if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.05);
   if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.05);
   if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.45,0.25);
   if(ipt == 4 ) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.2,0.25);
   if(ipt ==5) drawText(Form("p_{T}^{ave} > %d", ptlow[ipt]),0.2,0.25);
  }
  c6->cd(5);
  t3_2->Draw("same"); 
  c6->cd(6);
  t3_1->Draw("same");
  c6->cd(4);
  t3_3->Draw("same");
  c6->SaveAs(Form("plots/summary_diff_%s.png",mode[imode].Data()));
  c6->SaveAs(Form("plots/summary_diff_%s.pdf",mode[imode].Data()));
 }

 TFile * outf = new TFile("outf_syst_diff.root","recreate");
 
  for(int ipt = 0; ipt < npt; ipt++){
   histdRatJESDataMCDown[ipt]->Write();
   histJESDataMCDown[0][ipt]->Write(); 
   histJESDataMCDown[1][ipt]->Write();
   histdRatJESDataMCUp[ipt]->Write();
   histJESDataMCUp[0][ipt]->Write();
   histJESDataMCUp[1][ipt]->Write();
   histdRatTotalPos[ipt]->Write();
   histdRatTotalNeg[ipt]->Write();
   histGenDijetEta[0][ipt]->Write();
   histGenDijetEta[1][ipt]->Write();
   line->Draw("same");

  }

 outf->Close();
 
}
