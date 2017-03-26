#include "plotPDFDoubleRatio.C"
#include "plotPDFDoubleRatio_v2.C"
#include "plotPDF.C"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "utilities.h"

void prettyLegend(TLegend *legpp){
  legpp->SetFillColor(0);
  legpp->SetBorderSize(0);
  legpp->SetFillStyle(0);
  legpp->SetTextFont(43);
  legpp->SetTextSize(25); 
}

void plotsPAS(){

 TString tag = "ppjecv1";
 gStyle->SetCanvasPreferGL(1);
 TH1D::SetDefaultSumw2();
   // int colpp[] = {TColor::GetColor("#FFE303"),TColor::GetColor("#397D02")};
   int colpp[] = {kBlack,TColor::GetColor("#388E8E")};
   int colpPb[] = {TColor::GetColor("#388E8E"),kBlack,TColor::GetColor("#0276FD")};
   int colpPbdata = TColor::GetColor("#CD0000");
   int colppdata = TColor::GetColor("#0000CD");
  // int col[] = {TColor::GetColor("#CD0000"),TColor::GetColor("#FF7F50"),TColor::GetColor("#FFA824"),TColor::GetColor("#BCED91"),TColor::GetColor("#397D02"),TColor::GetColor("#388E8E"),TColor::GetColor("#009ACD"),TColor::GetColor("#5B59BA")};
  TFile *file_data = new TFile("outf_pPb_pp_20170116_2.root");

  TFile *file_data_pPb = new TFile("outf_pPb_pp_raw.root");
  
  //TFile *file_data = new TFile("outf_pPb_pp_7pi8.root");
  //TFile *file_data = new TFile("outf_pPb_pp_newppMC.root");
  TFile *file_data_NB = new TFile("outf_pp_pythia_raw.root");
  
  TString modePP = "pp_boost_v4_noweight_neg_test2";
  TString modepPb = "pPb_boost_v4_noweight_test2";
  TString modePPNB = "pp_noboost";
  TString stringppNLO[]={"MMHT14","CT14"};
  int npt = 6;
  int nPDFpp = 2; 
  int nPDFpPb = 3;
  int ptlow[] = {25, 55, 75, 95, 115, 150, 400};
  //!read data and NLO
  TH1D *hData[npt];
  TH1D *hDataPP[npt];
  TH1D *hDataRat[npt];
  TH1D *hDataDiff[npt];
  
  //!noboost
  TH1D *hMCNB[npt];
  TH1D *hDataPPNB[npt];
  TH1D *hDataRatNB[npt];
  TH1D *hDataDiffNB[npt];
  
  TGraphAsymmErrors *NLOpp[nPDFpp][npt];
  TGraphAsymmErrors *NLOpPb[nPDFpPb][nPDFpp][npt];
  TGraphAsymmErrors *NLOpPbpp[nPDFpPb][nPDFpp][npt];
  TGraphAsymmErrors *NLOdiff[nPDFpPb][nPDFpp][npt];

  for(int ipt = 0; ipt < 6; ipt++){
    //hData[ipt] = (TH1D*)file_data->Get(Form("hist_eta_%d",ipt));
    hData[ipt] = (TH1D*)file_data_pPb->Get(Form("hist_eta_%d",ipt));
    hDataPPNB[ipt] = (TH1D*)file_data_NB->Get(Form("hist_eta_%d",ipt));
    hMCNB[ipt] = (TH1D*)file_data_NB->Get(Form("hist_eta_mc_%d",ipt));
    hDataPP[ipt] = (TH1D*)file_data->Get(Form("hist_eta_pp_%d",ipt));
	for(int ipp = 0; ipp < nPDFpp; ipp++){
	  NLOpp[ipp][ipt] = plotPDF(ptlow[ipt], ptlow[ipt+1], 0, 1, ipp);
	  for(int ipPb = 0; ipPb < nPDFpPb; ipPb++){
	    cout << ipt << " " << ipp << " " << " "<< ipPb << " " << endl;
	    NLOpPb[ipPb][ipp][ipt] = plotPDF(ptlow[ipt], ptlow[ipt+1], 1, ipPb+1, ipp);
		cout << "pPb/pp" << endl; 
	    NLOpPbpp[ipPb][ipp][ipt] = plotPDFDoubleRatio(ptlow[ipt], ptlow[ipt+1], 1, ipPb+1, ipp);
	    NLOdiff[ipPb][ipp][ipt] = plotPDFDiff(ptlow[ipt], ptlow[ipt+1], 1, ipPb+1, ipp);
	  } 
	}
  }
  cout<<"read syst"<<endl;
  //!read systematics and unfolding
  TFile *file_systematics = new TFile("outf_unfolding_v2.root");
  TFile *file_systematics_NB = new TFile("outf_unfolding.root");
  TFile *file_systematics_rat = new TFile("outf_syst_rat_v2.root");
  TFile *file_systematics_diff = new TFile("outf_syst_diff_v2.root");
  TH1D *histTotalPos[npt];
  TH1D *histTotalNeg[npt];
  TH1D *histTotalPosPP[npt];
  TH1D *histTotalNegPP[npt];
  TH1D *histTotalPosRat[npt];
  TH1D *histTotalNegRat[npt];
  TH1D *histTotalPosDiff[npt];
  TH1D *histTotalNegDiff[npt];
  TH1D *histTotalPosNB[npt];
  TH1D *histTotalNegNB[npt];
  TH1D *histUnfolding[npt];
  TH1D *histUnfoldingPP[npt];
  
  for(int ipt = 0; ipt < npt; ipt++){
   cout << ipt<<endl;
    histTotalPos[ipt] = (TH1D*)file_systematics->Get(Form("histTotalPositive%dMode%s",ipt,modepPb.Data()));
    histTotalPosPP[ipt] = (TH1D*)file_systematics->Get(Form("histTotalPositive%dMode%s",ipt,modePP.Data()));
    histTotalPosRat[ipt] = (TH1D*)file_systematics_rat->Get(Form("histdRatTotalPos%d",ipt));
    histTotalPosDiff[ipt] = (TH1D*)file_systematics_diff->Get(Form("histdRatTotalPos%d",ipt));
    histTotalPosNB[ipt] = (TH1D*)file_systematics_NB->Get(Form("histTotalPositive%dMode%s",ipt,modePPNB.Data()));
    histTotalNeg[ipt] = (TH1D*)file_systematics->Get(Form("histTotalNegative%dMode%s",ipt,modepPb.Data()));
    histTotalNegPP[ipt] = (TH1D*)file_systematics->Get(Form("histTotalNegative%dMode%s",ipt,modePP.Data()));
    histTotalNegRat[ipt] = (TH1D*)file_systematics_rat->Get(Form("histdRatTotalNeg%d",ipt));
    histTotalNegNB[ipt] = (TH1D*)file_systematics_NB->Get(Form("histTotalNegative%dMode%s",ipt,modePPNB.Data()));
    histTotalNegDiff[ipt] = (TH1D*)file_systematics_diff->Get(Form("histdRatTotalNeg%d",ipt));
	histUnfolding[ipt] = (TH1D*)file_systematics->Get(Form("UnfoldingPt%dMode%s",ipt,modepPb.Data()));
	histUnfoldingPP[ipt] = (TH1D*)file_systematics->Get(Form("UnfoldingPt%dMode%s",ipt,modePP.Data()));
  }
  
  //!apply unfolding
  int nbins = hDataPP[0]->GetNbinsX();
  for(int ipt = 0; ipt < npt; ipt++){
    /*
	for(int ibin = 0; ibin < nbins; ibin++){
	  cout << ipt << " "<< ibin << endl;
      if(histUnfoldingPP[ipt]->GetBinContent(ibin+1)>0) hDataPP[ipt]->SetBinContent(ibin+1, hDataPP[ipt]->GetBinContent(ibin+1)/histUnfoldingPP[ipt]->GetBinContent(ibin+1));
      cout << 1.1 << endl;
	  if(histUnfolding[ipt]->GetBinContent(ibin+1)>0) hData[ipt]->SetBinContent(ibin+1, hData[ipt]->GetBinContent(ibin+1)/histUnfolding[ipt]->GetBinContent(ibin+1));
	  // hData[ipt]->SetBinContent(ibin+1, hData[ipt]->GetBinContent(ibin+1));
      cout << 1.2 << endl;	  
	  cout << 1.3 << endl;

	 
    }
	*/
	hDataPP[ipt]->Scale(1./hDataPP[ipt]->Integral());
	hData[ipt]->Scale(1./hData[ipt]->Integral());
	hDataPPNB[ipt]->Scale(1./hDataPPNB[ipt]->Integral());
	hMCNB[ipt]->Scale(1./hMCNB[ipt]->Integral());
	for(int ibin = 0; ibin < nbins; ibin++){
	 hDataPP[ipt]->SetBinContent(ibin+1, hDataPP[ipt]->GetBinContent(ibin+1)/hDataPP[ipt]->GetBinWidth(ibin+1));
	 hData[ipt]->SetBinContent(ibin+1, hData[ipt]->GetBinContent(ibin+1)/hData[ipt]->GetBinWidth(ibin+1));
	 hDataPP[ipt]->SetBinError(ibin+1, hDataPP[ipt]->GetBinError(ibin+1)/hDataPP[ipt]->GetBinWidth(ibin+1));
	 hData[ipt]->SetBinError(ibin+1, hData[ipt]->GetBinError(ibin+1)/hData[ipt]->GetBinWidth(ibin+1));
	}
	for(int ibin = 0; ibin < hMCNB[ipt]->GetNbinsX(); ibin++){
     hDataPPNB[ipt]->SetBinContent(ibin+1, hDataPPNB[ipt]->GetBinContent(ibin+1)/hDataPPNB[ipt]->GetBinWidth(ibin+1));
     hDataPPNB[ipt]->SetBinError(ibin+1, hDataPPNB[ipt]->GetBinError(ibin+1)/hDataPPNB[ipt]->GetBinWidth(ibin+1));
     hMCNB[ipt]->SetBinContent(ibin+1, hMCNB[ipt]->GetBinContent(ibin+1)/hMCNB[ipt]->GetBinWidth(ibin+1));
     hMCNB[ipt]->SetBinError(ibin+1, hMCNB[ipt]->GetBinError(ibin+1)/hMCNB[ipt]->GetBinWidth(ibin+1));
	}
	hDataRat[ipt] = (TH1D*)hData[ipt]->Clone(Form("hist_eta_rat_%d",ipt));
	hDataDiff[ipt] = (TH1D*)hData[ipt]->Clone(Form("hist_eta_diff_%d",ipt));
	hDataDiffNB[ipt] = (TH1D*)hDataPPNB[ipt]->Clone(Form("hist_nb_diff_%d",ipt));
	hDataRatNB[ipt] = (TH1D*)hDataPPNB[ipt]->Clone(Form("hist_nb_rat_%d",ipt));
	hDataRat[ipt]->Divide(hDataPP[ipt]);
	hDataDiff[ipt]->Add(hDataPP[ipt],-1);
	hDataRatNB[ipt]->Divide(hMCNB[ipt]);
	hDataDiffNB[ipt]->Add(hMCNB[ipt],-1);
  }
  
  cout << "bla" << endl;
  //!scale systematics according to points
  TGraphErrors *histTotalPPScaled[npt];
  TGraphErrors *histTotalScaled[npt];
  TGraphErrors *histTotalRatScaled[npt];
  TGraphErrors *histTotalDiffScaled[npt];
  TGraphErrors *histTotalNBScaled[npt];
  for(int ipt = 0; ipt < npt; ipt++){
	float centerPP[nbins]; 
	float errPP[nbins]; 
	float errPPb[nbins]; 
	float centerPPb[nbins];
	float errRat[nbins]; 
	float centerRat[nbins];
	float errDiff[nbins]; 
	float centerDiff[nbins];
	float centerx[nbins];
	float centererrx[nbins];
	float errNB[histTotalPosNB[ipt]->GetNbinsX()]; 
	float centerNB[histTotalPosNB[ipt]->GetNbinsX()];
	float centerxNB[histTotalPosNB[ipt]->GetNbinsX()]; 
	float centererrxNB[histTotalPosNB[ipt]->GetNbinsX()];
	
	
    for(int ibin = 0; ibin < histTotalPosNB[ipt]->GetNbinsX(); ibin++){
	
	  centerxNB[ibin] = histTotalNegNB[ipt]->GetBinCenter(ibin+1);
	  centererrxNB[ibin] = histTotalNegNB[ipt]->GetBinWidth(ibin+1)/2./1.3;
	  float errupNB = 1-(histTotalPosNB[ipt]->GetBinContent(ibin+1)-1);
	  float errdownNB = 1-(histTotalNegNB[ipt]->GetBinContent(ibin+1)-1);
	  float yNB = hDataPPNB[ipt]->GetBinContent(hDataPPNB[ipt]->FindBin(fabs(histTotalPosNB[ipt]->GetBinCenter(ibin+1))));
	  centerNB[ibin] = yNB*(errupNB + errdownNB)/2;
	  errNB[ibin] = yNB*(errupNB - errdownNB)/2;
	  cout << 2 << endl;
	  
	  // float errupDiffMB = histTotalPosDiffMB[ipt]->GetBinContent(ibin+1);
	  // float errdownDiffMB = histTotalNegDiffMB[ipt]->GetBinContent(ibin+1);
	  // float yDiff = hDataDiff[ipt]->GetBinContent(ibin+1);
	  // centerDiff[ibin] = yDiff+(errupDiff+errdownDiff)/2.;
	  // cout << "up diff" << errupDiff << " "<< "down diff" << errdownDiff <<endl;
	  // errDiff[ibin] = (errupDiff - errdownDiff)/2;
	}
    for(int ibin = 0; ibin < nbins; ibin++){
	 cout << 1 << endl;
	  centerx[ibin] = histTotalPosPP[ipt]->GetBinCenter(ibin+1);
	  centererrx[ibin] = histTotalPosPP[ipt]->GetBinWidth(ibin+1)/2./1.3;
	  cout << ipt << " " << ibin << endl;
	  float errupPP = 1-(histTotalPosPP[ipt]->GetBinContent(ibin+1)-1);
	  float errdownPP = 1-(histTotalNegPP[ipt]->GetBinContent(ibin+1)-1);
	  float yPP = hDataPP[ipt]->GetBinContent(ibin+1);
	  centerPP[ibin] = yPP*(errupPP + errdownPP)/2;
	  errPP[ibin] = yPP*(errupPP - errdownPP)/2;
	 cout << 2 << endl;
	 
	  
	  float errupPPb = 1-(histTotalPos[ipt]->GetBinContent(ibin+1)-1);
	  float errdownPPb = 1-(histTotalNeg[ipt]->GetBinContent(ibin+1)-1);
	  float yPPb = hData[ipt]->GetBinContent(ibin+1);
	  centerPPb[ibin] = yPPb*(errupPPb + errdownPPb)/2;
	  errPPb[ibin] = yPPb*(errupPPb - errdownPPb)/2;
	 cout << 3 << endl;
	  
	  float errupRat = 1-(histTotalPosRat[ipt]->GetBinContent(ibin+1)-1);
	  cout << 3.1<<endl;
	  float errdownRat = 1-(histTotalNegRat[ipt]->GetBinContent(ibin+1)-1);
	  // if(ibin < 2 || ibin > nbins-2){
	   // errupRat*=2;
	   // errdownRat*=2;
	  // }
	  float yRat = hDataRat[ipt]->GetBinContent(ibin+1);
	  centerRat[ibin] = yRat*(errupRat + errdownRat)/2;
	  errRat[ibin] = yRat*(errupRat - errdownRat)/2;
	 cout << 4 << endl;

	  float errupDiff = histTotalPosDiff[ipt]->GetBinContent(ibin+1);
	  float errdownDiff = histTotalNegDiff[ipt]->GetBinContent(ibin+1);
	  // if(ibin < 2 || ibin > nbins-2){
	   // errupDiff*=0.05;
	   // errdownDiff*=0.05;
	  // }
	  float yDiff = hDataDiff[ipt]->GetBinContent(ibin+1);
	  centerDiff[ibin] = yDiff+(errupDiff+errdownDiff)/2.;
	  cout << "up diff" << errupDiff << " "<< "down diff" << errdownDiff <<endl;
	  errDiff[ibin] = (errupDiff - errdownDiff)/2;
	  
	}
	histTotalPPScaled[ipt] = new TGraphErrors(nbins, centerx, centerPP, centererrx, errPP);
	histTotalScaled[ipt] = new TGraphErrors(nbins, centerx, centerPPb, centererrx, errPPb);
	histTotalRatScaled[ipt] = new TGraphErrors(nbins, centerx, centerRat, centererrx, errRat);
	histTotalDiffScaled[ipt] = new TGraphErrors(nbins, centerx, centerDiff, centererrx, errDiff);
	histTotalNBScaled[ipt] = new TGraphErrors(histTotalPosNB[ipt]->GetNbinsX(), centerxNB, centerNB, centererrxNB, errNB);
  }
  
  //!plot pp
  TH1D * emptyDist = new TH1D("emptyDist",";#eta_{dijet};#frac{1}{N_{dijet}} #frac{N_{dijet}}{#eta_{dijet}} ",10,-2.999,2.999);
  emptyDist->Fill(1.,1000.);
  makePretty(emptyDist,2.5);
  emptyDist->SetMaximum(0.4999);
  emptyDist->SetMinimum(0.0001);
  emptyDist->GetXaxis()->CenterTitle();
  emptyDist->GetYaxis()->CenterTitle();
  
  TCanvas * cpp = new TCanvas("cpp","",1300,800);
  makeMultiPanelCanvas(cpp,3,2,0.0,0.0,0.24,0.24,0.11);
  for(int ipt = 0; ipt < npt; ipt++){
    cpp->cd(ipt+1);
	emptyDist->Draw();
	histTotalPPScaled[ipt]->SetFillColorAlpha(colppdata,0.35);
	histTotalPPScaled[ipt]->SetLineColor(0);
	histTotalPPScaled[ipt]->Draw("same 2");
	double *EY = histTotalPPScaled[ipt]->GetEY();
	double *EX = histTotalPPScaled[ipt]->GetEX();
	double *centY = histTotalPPScaled[ipt]->GetY();
	double *centX = histTotalPPScaled[ipt]->GetX();
	for(int ibin = 0; ibin < nbins; ibin++){
	 TBox box(centX[ibin]-EX[ibin],centY[ibin]-EY[ibin],centX[ibin]+EX[ibin],centY[ibin]+EY[ibin]);
	 box.SetLineColor(colppdata);
	 box.Draw("same");
	}
	NLOpp[0][ipt]->SetLineColor(0);
	NLOpp[1][ipt]->SetLineColor(0);
	NLOpp[0][ipt]->SetFillColorAlpha(colpp[0],0.30);
	NLOpp[1][ipt]->SetFillColorAlpha(colpp[1],0.30);
    NLOpp[0][ipt]->Draw("same 2");
    NLOpp[1][ipt]->Draw("same 2");
	hDataPP[ipt]->SetMarkerColor(colppdata);
	hDataPP[ipt]->SetLineColor(colppdata);
	hDataPP[ipt]->Draw("same");
	hDataPP[ipt]->Print("all");
    if(ipt == 0){
 	 drawText("#bf{CMS}",0.32,0.8);
 	 drawText("#it{Preliminary}",0.32,0.73);
     drawText("#sqrt{s_{NN}} = 5.02 TeV",0.22,0.93,26);
    }
	if(ipt == 2){
	 drawText("pp 25.8 pb^{-1}",0.65,0.93,26);
    }
	if(ipt == 1){	
	 drawText("p_{T,1} > 20, p_{T,2} > 30 GeV, #Delta#phi_{1,2} > 2#pi/3",0.05,0.93,24);
	}
	if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.08,26);
    if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.30,0.08,26);
    if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.29,26);
    if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.28,0.29,26);
    if(ipt ==5) drawText(Form("p_{T}^{ave} > %d GeV", ptlow[ipt]),0.35,0.29,26);
  }
  
  TLegend *legpp = new TLegend(0.05,0.55,0.4,0.85);
  prettyLegend(legpp);
  legpp->AddEntry(hDataPP[0], "pp", "p");
  legpp->AddEntry(histTotalPPScaled[0], "Exp. Uncer.", "f");
  legpp->AddEntry(NLOpp[0][0], "MMHT14", "f");
  legpp->AddEntry(NLOpp[1][0], "CT14", "f");
  cpp->cd(3);
  legpp->Draw("same");
  cpp->SaveAs(Form("ppDists%s.png",tag.Data()));
  cpp->SaveAs(Form("ppDists%s.pdf",tag.Data()));
  cpp->SaveAs(Form("ppDists%s.C",tag.Data()));
  
  //!plot pp noboost
  
  TH1D * emptyNB = new TH1D("emptyNB",";#eta_{dijet};#frac{1}{N_{dijet}} #frac{N_{dijet}}{#eta_{dijet}} ",10,0.001,2.999);
  emptyNB->Fill(1.,1000.);
  makePretty(emptyNB,2.5);
  emptyNB->SetMaximum(0.9999);
  emptyNB->SetMinimum(0.0001);
  emptyNB->GetXaxis()->CenterTitle();
  emptyNB->GetYaxis()->CenterTitle();
  
  TCanvas * cppNB = new TCanvas("cppNB","",1300,800);
  makeMultiPanelCanvas(cppNB,3,2,0.0,0.0,0.24,0.24,0.11);
  for(int ipt = 0; ipt < npt; ipt++){
    cppNB->cd(ipt+1);
	emptyNB->Draw();

	histTotalNBScaled[ipt]->SetFillColorAlpha(colppdata,0.35);
	histTotalNBScaled[ipt]->SetLineColor(0);
	histTotalNBScaled[ipt]->Draw("same 2");
	hMCNB[ipt]->SetLineColor(colpPbdata);
	hMCNB[ipt]->SetMarkerSize(0);
	hMCNB[ipt]->SetFillColor(0);
	hMCNB[ipt]->Draw("same");
	hMCNB[ipt]->Draw("same hist");
	hDataPPNB[ipt]->SetMarkerColor(colppdata);
	hDataPPNB[ipt]->SetLineColor(colppdata);
	hDataPPNB[ipt]->SetFillColor(0);
	hDataPPNB[ipt]->Draw("same");
	hDataPPNB[ipt]->Print("all");
    if(ipt == 0){
 	 drawText("#bf{CMS}",0.32,0.8);
 	 drawText("#it{Preliminary}",0.32,0.73);
     drawText("#sqrt{s_{NN}} = 5.02 TeV",0.22,0.93,26);
    }
	if(ipt == 2){
	 drawText("pp 25.8 pb^{-1}",0.65,0.93,26);
    }
	if(ipt == 1){	
	 drawText("p_{T,1} > 20, p_{T,2} > 30 GeV, #Delta#phi_{1,2} > 2#pi/3",0.05,0.93,24);
	}
	if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.25,0.08,26);
    if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.10,0.08,26);
    if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.25,0.29,26);
    if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.08,0.29,26);
    if(ipt ==5) drawText(Form("p_{T}^{ave} > %d GeV", ptlow[ipt]),0.15,0.29,26);
  }
  
  TLegend *legppNB = new TLegend(0.05,0.65,0.4,0.85);
  prettyLegend(legppNB);
  legppNB->AddEntry(hDataPPNB[0], "pp", "p");
  legppNB->AddEntry(hMCNB[0], "PYTHIA 8", "l");
  cppNB->cd(3);
  legppNB->Draw("same");
  cppNB->SaveAs(Form("ppDistsNB%s.png",tag.Data()));
  cppNB->SaveAs(Form("ppDistsNB%s.pdf",tag.Data()));
  cppNB->SaveAs(Form("ppDistsNB%s.C",tag.Data()));
  
  //!plot pPb
  cout << 1 << endl;
  TCanvas * cpPb[2];
  for(int ipp = 0; ipp < 2; ipp++){
    cout << "ipp=" << ipp << endl;
  cpPb[ipp] = new TCanvas("cpPb","",1300,800);
  makeMultiPanelCanvas(cpPb[ipp],3,2,0.0,0.0,0.24,0.24,0.11);
  for(int ipt = 0; ipt < npt; ipt++){
    cout <<"ipt = " << ipt << endl;
       cpPb[ipp]->cd(ipt+1);
	emptyDist->Draw();
	histTotalScaled[ipt]->SetFillColorAlpha(colpPbdata,0.35);
	histTotalScaled[ipt]->SetLineColor(colpPbdata);
	histTotalScaled[ipt]->Draw("same 2");
    double *EY = histTotalScaled[ipt]->GetEY();
	double *EX = histTotalScaled[ipt]->GetEX();
	double *centY = histTotalScaled[ipt]->GetY();
        cout << "a"<<endl;
       double *centX = histTotalScaled[ipt]->GetX();
       cout << "a.1"<<endl;
        for(int ibin = 0; ibin < nbins; ibin++){
	  cout << "ibin = " << ibin << endl;
         TBox box(centX[ibin]-EX[ibin],centY[ibin]-EY[ibin],centX[ibin]+EX[ibin],centY[ibin]+EY[ibin]);
	 box.SetLineColor(colpPbdata);
	 box.Draw("same");
	}
        cout << "a.2"<<endl;
	NLOpPb[0][ipp][ipt]->SetLineColor(0);
	NLOpPb[1][ipp][ipt]->SetLineColor(0);
	NLOpPb[2][ipp][ipt]->SetLineColor(0);
	NLOpPb[0][ipp][ipt]->SetFillColorAlpha(colpPb[0],0.35);
	NLOpPb[1][ipp][ipt]->SetFillColorAlpha(colpPb[1],0.35);
	NLOpPb[2][ipp][ipt]->SetFillColorAlpha(colpPb[2],0.35);
        cout << "b"<<endl;
        NLOpPb[0][ipp][ipt]->Draw("same 2");
        //NLOpPb[1][ipp][ipt]->Draw("same 2");
	// NLOpPb[2][ipp][ipt]->Draw("same 2");
	hData[ipt]->SetMarkerColor(colpPbdata);
	hData[ipt]->SetLineColor(colpPbdata);
	hData[ipt]->Draw("same");
	hData[ipt]->Print("all");
    if(ipt == 0){
 	 drawText("#bf{CMS}",0.32,0.8);
 	 drawText("#it{Preliminary}",0.32,0.73);
     drawText("#sqrt{s_{NN}} = 5.02 TeV",0.22,0.93,26);
    }
	if(ipt == 2){
	 drawText("pPb 35 nb^{-1}",0.65,0.93,26);
    }
	if(ipt == 1){	
	 drawText("p_{T,1} > 20, p_{T,2} > 30 GeV, #Delta#phi_{1,2} > 2#pi/3",0.05,0.93,24);
	}
	if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.08,26);
    if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.30,0.08,26);
    if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.29,26);
    if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.28,0.29,26);
    if(ipt ==5) drawText(Form("p_{T}^{ave} > %d GeV", ptlow[ipt]),0.35,0.29,26);
  }
  
  
  //TLegend *legpPb = new TLegend(0.05,0.55,0.4,0.85);
  TLegend *legpPb = new TLegend(0.05,0.65,0.4,0.85);
  prettyLegend(legpPb);
  legpPb->AddEntry(hData[0], "pPb", "p");
  legpPb->AddEntry(histTotalScaled[0], "Exp. Uncer.", "f");
  legpPb->AddEntry(NLOpPb[0][0][0], "DSSz", "f");
  //legpPb->AddEntry(NLOpPb[1][0][0], "EPS09", "f");
  //legpPb->AddEntry(NLOpPb[2][0][0], "nCTEQ15", "f");
  cpPb[ipp]->cd(2);
  drawText(Form("pp NLO: %s",stringppNLO[ipp].Data()),0.05,0.8,26);
  cpPb[ipp]->cd(3);
  legpPb->Draw("same");
  if(ipp==0){
   cpPb[ipp]->SaveAs(Form("pPbDistsMM%s.png",tag.Data()));
   cpPb[ipp]->SaveAs(Form("pPbDistsMM%s.pdf",tag.Data()));
   cpPb[ipp]->SaveAs(Form("pPbDistsMM%s.C",tag.Data()));
  }else{
   cpPb[ipp]->SaveAs(Form("pPbDistsCT%s.png",tag.Data()));
   cpPb[ipp]->SaveAs(Form("pPbDistsCT%s.pdf",tag.Data()));
   cpPb[ipp]->SaveAs(Form("pPbDistsCT%s.C",tag.Data()));
  }
  }
  
  //!plot ratio

  TH1D * emptyRat = new TH1D("emptyRat",";#eta_{dijet};pPb/pp ",10,-2.999,2.999);
  emptyRat->Fill(1.,1000.);
  makePretty(emptyRat,2.5);
  emptyRat->SetMaximum(1.5);
  emptyRat->SetMinimum(0.5);
  emptyRat->GetXaxis()->CenterTitle();
  emptyRat->GetYaxis()->CenterTitle();  
  TLine *line = new TLine(-2.999,1.,2.999,1.);

   
  TCanvas * cRat[2];
  for(int ipp = 0; ipp < 2; ipp++){
  cRat[ipp] = new TCanvas(Form("cRat%d",ipp),"",1300,800);
  makeMultiPanelCanvas(cRat[ipp],3,2,0.0,0.0,0.24,0.24,0.11);
  for(int ipt = 0; ipt < npt; ipt++){
    cRat[ipp]->cd(ipt+1);
	emptyRat->Draw();
	histTotalRatScaled[ipt]->SetFillColorAlpha(colpPbdata,0.35);
	histTotalRatScaled[ipt]->SetFillColorAlpha(colpPbdata,0.35);
	histTotalRatScaled[ipt]->SetLineColor(colpPbdata);
	histTotalRatScaled[ipt]->Draw("same 2");
	double *y[3];
	for(int ipdf = 0; ipdf < 3; ipdf++){
		y[ipdf] = NLOpPbpp[ipdf][ipp][ipt]->GetY();
	}
	if(ipt > 1){
		hDataRat[ipt]->SetBinContent(1,1000.);
	   	for(int ipdf = 0; ipdf < 3; ipdf++){
		    y[ipdf][0] = 1000.;
		}
	}
	if(ipt > 3){
		hDataRat[ipt]->SetBinContent(2,1000.);
		for(int ipdf = 0; ipdf < 3; ipdf++){
		    y[ipdf][1] = 1000.;
		}
	}
	NLOpPbpp[0][ipp][ipt]->SetLineColor(0);
	NLOpPbpp[1][ipp][ipt]->SetLineColor(0);
	NLOpPbpp[2][ipp][ipt]->SetLineColor(0);
	NLOpPbpp[0][ipp][ipt]->SetFillColorAlpha(colpPb[0],0.35);
	NLOpPbpp[1][ipp][ipt]->SetFillColorAlpha(colpPb[1],0.35);
	NLOpPbpp[2][ipp][ipt]->SetFillColorAlpha(colpPb[2],0.35);
        NLOpPbpp[0][ipp][ipt]->Draw("same 2");
        //NLOpPbpp[1][ipp][ipt]->Draw("same 2");
        //NLOpPbpp[2][ipp][ipt]->Draw("same 2");	

	hDataRat[ipt]->SetMarkerColor(colpPbdata);
	hDataRat[ipt]->SetLineColor(colpPbdata);
	hDataRat[ipt]->Draw("same");
	hDataRat[ipt]->Print("all");
	line->Draw("same");
    if(ipt == 0){
 	 drawText("#bf{CMS}",0.32,0.8);
 	 drawText("#it{Preliminary}",0.32,0.73);
     drawText("#sqrt{s_{NN}} = 5.02 TeV",0.22,0.93,26);
    }
	if(ipt == 2){
	 drawText("pp 25.8 pb^{-1} pPb 35 nb^{-1}",0.35,0.93,26);
    }
	if(ipt == 1){	
	 drawText("p_{T,1} > 20, p_{T,2} > 30 GeV, #Delta#phi_{1,2} > 2#pi/3",0.05,0.93,24);
	}
	if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.08,26);
    if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.30,0.08,26);
    if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.29,26);
    if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.28,0.29,26);
    if(ipt ==5) drawText(Form("p_{T}^{ave} > %d GeV", ptlow[ipt]),0.35,0.29,26);
  }
  
  TLegend *legRat = new TLegend(0.45,0.65,0.9,0.85);
  prettyLegend(legRat);
  TLegend *legRat2 = new TLegend(0.1,0.65,0.4,0.85);
  prettyLegend(legRat2);
  legRat->AddEntry(hDataRat[0], "pPb", "p");
  legRat->AddEntry(histTotalRatScaled[0], "Exp. Uncer.", "f");
  legRat->AddEntry(NLOpPbpp[0][0][0], "DSSz", "f");
  //legRat->AddEntry(NLOpPbpp[1][0][0], "EPS09", "f");
  //legRat2->AddEntry(NLOpPbpp[2][0][0], "nCTEQ15", "f");
  // legRat->AddEntry(NLOpPbpp[2][0][0], "nCTEQ15", "f");
  cRat[ipp]->cd(2);
  drawText(Form("pp NLO: %s",stringppNLO[ipp].Data()),0.05,0.8,26);
  cRat[ipp]->cd(3);
  legRat->Draw("same");
  legRat2->Draw("same");
  if(ipp==0){
   cRat[ipp]->SaveAs("pPbppRatMM.png");
   cRat[ipp]->SaveAs("pPbppRatMM.pdf");
   cRat[ipp]->SaveAs("pPbppRatMM.C");
  }else{
   cRat[ipp]->SaveAs(Form("pPbppRatCT%s.png",tag.Data()));
   cRat[ipp]->SaveAs(Form("pPbppRatCT%s.pdf",tag.Data()));
   cRat[ipp]->SaveAs(Form("pPbppRatCT%s.C",tag.Data()));
  }
  }
  //!plot difference

  
  TH1D * emptyDiff = new TH1D("emptyDiff",";#eta_{dijet};pPb-pp ",10,-2.999,2.999);
  emptyDiff->Fill(1.,1000.);
  makePretty(emptyDiff,2.5);
  emptyDiff->SetMaximum(0.04);
  emptyDiff->SetMinimum(-0.04);
  emptyDiff->GetXaxis()->CenterTitle();
  emptyDiff->GetYaxis()->CenterTitle();  
  TLine *line0 = new TLine(-2.999,0.,2.999,0.);

  TFile *difffile = new TFile("difffile.root","recreate");
  for(int ipp = 0; ipp < 2; ipp++){
   for(int ipt = 0; ipt < npt; ipt++){ 
    if(ipp==0){
	histTotalDiffScaled[ipt]->SetName(Form("syst%d",ipt));
	histTotalDiffScaled[ipt]->Write();
    }
	NLOdiff[0][ipp][ipt]->SetName(Form("NLOdiff%d%d",ipp,ipt));
	NLOdiff[0][ipp][ipt]->Write();
   }
  }
  difffile->Close();
  
  TCanvas * cDiff[2];
  for(int ipp = 0; ipp < 2; ipp++){
  cDiff[ipp] = new TCanvas(Form("cDiff%d",ipp),"",1300,800);
  makeMultiPanelCanvas(cDiff[ipp],3,2,0.0,0.0,0.24,0.24,0.11);
  for(int ipt = 0; ipt < npt; ipt++){
    cDiff[ipp]->cd(ipt+1);
	emptyDiff->Draw();
	histTotalDiffScaled[ipt]->SetFillColorAlpha(colpPbdata,0.35);
	histTotalDiffScaled[ipt]->SetFillColorAlpha(colpPbdata,0.35);
	histTotalDiffScaled[ipt]->SetLineColor(colpPbdata);
	histTotalDiffScaled[ipt]->Draw("same 2");
	double *y[3];
	for(int ipdf = 0; ipdf < 3; ipdf++){
		y[ipdf] = NLOdiff[ipdf][ipp][ipt]->GetY();
	}
	if(ipt > 1){
		hDataDiff[ipt]->SetBinContent(1,1000.);
	   	for(int ipdf = 0; ipdf < 3; ipdf++){
		    y[ipdf][0] = 1000.;
		}
	}
	if(ipt > 3){
		hDataDiff[ipt]->SetBinContent(2,1000.);
		for(int ipdf = 0; ipdf < 3; ipdf++){
		    y[ipdf][1] = 1000.;
		}
	}
	NLOdiff[0][ipp][ipt]->SetLineColor(0);
	NLOdiff[1][ipp][ipt]->SetLineColor(0);
	NLOdiff[2][ipp][ipt]->SetLineColor(0);
	NLOdiff[0][ipp][ipt]->SetFillColorAlpha(colpPb[0],0.35);
	NLOdiff[1][ipp][ipt]->SetFillColorAlpha(colpPb[1],0.35);
	NLOdiff[2][ipp][ipt]->SetFillColorAlpha(colpPb[2],0.35);
        NLOdiff[0][ipp][ipt]->Draw("same 2");
	// NLOdiff[1][ipp][ipt]->Draw("same 2");
	// NLOdiff[2][ipp][ipt]->Draw("same 2");
	hDataDiff[ipt]->SetMarkerColor(colpPbdata);
	hDataDiff[ipt]->SetLineColor(colpPbdata);
	hDataDiff[ipt]->Draw("same");
	hDataDiff[ipt]->Print("all");

	line0->Draw("same");
    if(ipt == 0){
 	 drawText("#bf{CMS}",0.32,0.8);
 	 drawText("#it{Preliminary}",0.32,0.73);
     drawText("#sqrt{s_{NN}} = 5.02 TeV",0.22,0.93,26);
    }
	if(ipt == 2){
	 drawText("pp 25.8 pb^{-1} pPb 35 nb^{-1}",0.35,0.93,26);
    }
	if(ipt == 1){	
	 drawText("p_{T,1} > 20, p_{T,2} > 30 GeV, #Delta#phi_{1,2} > 2#pi/3",0.05,0.93,24);
	}
	if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.08,26);
    if(ipt == 1 || ipt == 2)drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.30,0.08,26);
    if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.45,0.29,26);
    if(ipt == 4) drawText(Form("%d < p_{T}^{ave} < %d GeV", ptlow[ipt], ptlow[ipt+1]),0.28,0.29,26);
    if(ipt ==5) drawText(Form("p_{T}^{ave} > %d GeV", ptlow[ipt]),0.35,0.29,26);
  }
  
  TLegend *legDiff = new TLegend(0.05,0.65,0.5,0.9);
  prettyLegend(legDiff);
  TLegend *legDiff2 = new TLegend(0.05,0.65,0.5,0.85);
  prettyLegend(legDiff2);
  legDiff->AddEntry(hDataRat[0], "pPb", "p");
  legDiff->AddEntry(histTotalRatScaled[0], "Exp. Uncer.", "f");
  legDiff->AddEntry(NLOpPbpp[0][0][0], "DSSz", "f");
  //legDiff->AddEntry(NLOpPbpp[1][0][0], "EPS09", "f");
  //legDiff->AddEntry(NLOpPbpp[2][0][0], "nCTEQ15", "f");
  cDiff[ipp]->cd(2); 
  drawText(Form("pp NLO: %s",stringppNLO[ipp].Data()),0.05,0.8,26);
  cDiff[ipp]->cd(6);
  legDiff->Draw("same");
  legDiff2->Draw("same");
  if(ipp==0){
   cDiff[ipp]->SaveAs(Form("pPbppDiffMM%s.png",tag.Data()));
   cDiff[ipp]->SaveAs(Form("pPbppDiffMM%s.pdf",tag.Data()));
   cDiff[ipp]->SaveAs(Form("pPbppDiffMM%s.C",tag.Data()));
  }else{
   cDiff[ipp]->SaveAs(Form("pPbppDiffCT%s.png",tag.Data()));
   cDiff[ipp]->SaveAs(Form("pPbppDiffCT%s.pdf",tag.Data()));
   cDiff[ipp]->SaveAs(Form("pPbppDiffCT%s.C",tag.Data()));
  }
  }
}
