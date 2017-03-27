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
#include "utilities.h"
#include "TPaletteAxis.h"

void plotDijetEtaVsDijetMass(){
 TH1F::SetDefaultSumw2();
 TH1D::SetDefaultSumw2();
 TString algo = "ak3PF";
 int npt=6; 
 cout<<1<<endl;
 // int ptlow[]= {25,55,65,75,85,95,115,150,400}; 
 // int ptlow[]= {25,35,55,75,85,95,115,150,400}; 
 int ptlow[]= {25,55,75,95,115,150,400}; 
 float minSyspPb[]={0.08,0.08,0.04,0.04,0.01,0.01,0.01,0.01};
 float minSyspp[]={0.04,0.04,0.02,0.02,0.01,0.01,0.01,0.01};
             
 cout<<2<<endl; 
 // int netabins=16;
// int netabins=1;
 float sysByHand[] = {0.01,0.01,0.01,0.01,0.01,0.015,0.015,0.015,0.015,0.015,0.015,0.015,0.015,0.01,0.01,0.01,0.01,0.01};
 float sysByHandLowPanels[] = {0.005,0.005,0.005,0.005,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.005,0.005,0.005,0.005,0.005};
 
 int netabins = 18; 
 double etabins[19]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};

// double etabins[]= {0., 0.05, 0.1,0.15, 0.2, 0.3, 0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,3.0};
 // double etabins_double_hcalbins[]= {-2.9999,-2.500,  -2.172,-1.740, -1.392, -1.044,  -0.696,  -0.348,  0.000,  0.348,   0.696,   1.044,1.392,   1.740,   2.172,   2.500,   2.9999};
 TString dataset[]={"zs","jet40","jet60","jet80","jet100","jet100"};
 TString datasetPP[]={"jtpt1>20","jet40","jet60","jet80","jet100","jet100"};
 // TString datasetPP[]={"hcalnoise","hcalnoise && jet40","jet60 && hcalnoise","jet80 && hcalnoise","jet80 && hcalnoise","jet80 && hcalnoise"};

 int fileindex[]=  {0,1,1,2,2,2};
 int filemcindex[]=  {0,1,1,2,2,2};
 // int filemcindex[]={0,1,2,3,3,4};
 TFile *f_data[npt][2];
 double etacut=3; 
 TFile * f_mc[npt];
 /*
 f_mc[0] = new TFile(Form("../ntuples_pp_ppreco/pp_mb_shift.root",algo.Data(),(int)etacut));
 f_mc[1] = new TFile(Form("../ntuples_pp_ppreco/pp_jet40_shift.root",algo.Data(),(int)etacut));
 f_mc[2] = new TFile(Form("../ntuples_pp_ppreco/pp_jet80_shift.root",algo.Data(),(int)etacut));
 */
 /*
 f_mc[0] = new TFile(Form("../ntuples_20170225/mb_2.root",algo.Data(),(int)etacut));
 f_mc[1] = new TFile(Form("../ntuples_20170225/lowerpt_2.root",algo.Data(),(int)etacut));
 f_mc[2] = new TFile(Form("../ntuples_20170225/jet80_2.root",algo.Data(),(int)etacut));
 */
 f_mc[0] = new TFile(Form("../ntuples_20170225/minbias_official_boost_2.root",algo.Data(),(int)etacut));
 f_mc[1] = new TFile(Form("../ntuples_20170225/lowerpt_official_boost_2.root",algo.Data(),(int)etacut));
 f_mc[2] = new TFile(Form("../ntuples_20170225/jet80_official_boost_2.root",algo.Data(),(int)etacut));


 /*
 f_mc[0] = new TFile(Form("../ntuples/ppshift_minbias_ak3PF.root",algo.Data(),(int)etacut));
 f_mc[1] = new TFile(Form("../ntuples/ppshift_lowerpt_ak3PF.root",algo.Data(),(int)etacut));
 f_mc[2] = new TFile(Form("../ntuples/ppshift_jet80_ak3PF.root",algo.Data(),(int)etacut));
 
 // cout<<4<<endl;
 
 f_data[0][0] = new TFile(Form("../ntuples_20171117/ZBSingleTrack_ak3PF_pPb5.root"));
 f_data[1][0] = new TFile(Form("../ntuples_20171117/Jet40Jet60_ak3PF_pPb5.root"));
 f_data[2][0] = new TFile(Form("../ntuples_20171117/Jet80Jet100_ak3PF_pPb5.root")); 

 f_data[0][1] = new TFile(Form("../ntuples_20171117/ZBSingleTrack_ak3PF_Pbp5.root"));
 f_data[1][1] = new TFile(Form("../ntuples_20171117/Jet40Jet60_ak3PF_Pbp5.root"));
 f_data[2][1] = new TFile(Form("../ntuples_20171117/Jet80Jet100_ak3PF_Pbp5.root")); 
 */

 
 f_data[0][0] = new TFile(Form("../ntuples_20170225/pPb_zs.root"));
 f_data[1][0] = new TFile(Form("../ntuples_20170225/pPb_jet40.root"));
 f_data[2][0] = new TFile(Form("../ntuples_20170225/pPb_jet80.root")); 

 f_data[0][1] = new TFile(Form("../ntuples_20170225/Pbp_zs.root"));
 f_data[1][1] = new TFile(Form("../ntuples_20170225/Pbp_jet40.root"));
 f_data[2][1] = new TFile(Form("../ntuples_20170225/Pbp_jet80.root")); 


 /* 
 f_data[0][0] = new TFile(Form("../ntuples_reforest/R3_subAlgo_pPb5_mb_ak3PF_L2ResConst.root"));
 f_data[1][0] = new TFile(Form("../ntuples_reforest/R3_subAlgo_pPb5_jet40_ak3PF_L2ResConst.root"));
 f_data[2][0] = new TFile(Form("../ntuples_reforest/R3_subAlgo_pPb5_jet80_ak3PF_L2ResConst.root")); 

 f_data[0][1] = new TFile(Form("../ntuples_reforest/R3_subAlgo_Pbp5_mb_ak3PF_L2ResConst.root"));
 f_data[1][1] = new TFile(Form("../ntuples_reforest/R3_subAlgo_Pbp5_jet40_ak3PF_L2ResConst.root"));
 f_data[2][1] = new TFile(Form("../ntuples_reforest/R3_subAlgo_Pbp5_jet80_ak3PF_L2ResConst.root"));
 */
 // f_data[0][1] = new TFile(Form("../ntuples_05_27_2016/Pbp5_mb.root"));
 // f_data[1][1] = new TFile(Form("../ntuples_05_27_2016/Pbp5_jet40.root"));
 // f_data[2][1] = new TFile(Form("../ntuples_05_27_2016/Pbp5_jet80.root"));
 
 // f_data[0][0] = new TFile(Form("../ntuples/pPb5_mb_ak3PF.root"));
 // f_data[1][0] = new TFile(Form("../ntuples/pPb5_jet40_ak3PF.root")); 
 // f_data[2][0] = new TFile(Form("../ntuples/pPb5_jet80_ak3PF.root")); 
 
 // f_data[0][1] = new TFile(Form("../ntuples/Pbp5_mb_ak3PF.root"));
 // f_data[1][1] = new TFile(Form("../ntuples/Pbp5_jet40_ak3PF.root"));
 // f_data[2][1] = new TFile(Form("../ntuples/Pbp5_jet80_ak3PF.root"));
 cout<<1<<endl; 
 TFile *f_syst[npt]; 
 TH1F * hsyst[npt];
 TF1 *fit_binbybin[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  f_syst[ipt] = new TFile(Form("systematics/systematicsShift%d.root",ipt));
  hsyst[ipt] = (TH1F*)f_syst[ipt]->Get("histTotal");
  fit_binbybin[ipt] = (TF1*)f_syst[ipt]->Get("fit4");
 } 
 cout<<2<<endl;
 TFile *f_syst_pPb[npt]; 
 TH1F * hsyst_pPb[npt];
 TF1 *fit_binbybin_pPb[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  f_syst_pPb[ipt] = new TFile(Form("systematics/systematicspPb_rescorr2_%d.root",ipt));
  hsyst_pPb[ipt] = (TH1F*)f_syst_pPb[ipt]->Get("histTotal");
  fit_binbybin_pPb[ipt] = (TF1*)f_syst_pPb[ipt]->Get("fit4");
 } 
 cout<<3<<endl;
 TFile *f_syst_pPbpp[npt]; 
 TH1F * hsyst_pPbpp[npt];
 TH1F *hsystNeg_pPbpp[npt];
 TF1 *fit_binbybin_pPbpp[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  f_syst_pPbpp[ipt] = new TFile(Form("systematics/systematicspPbpp_rescorr_%d.root",ipt));
  hsyst_pPbpp[ipt] = (TH1F*)f_syst_pPbpp[ipt]->Get("histTotal");
  hsystNeg_pPbpp[ipt]  = (TH1F*)hsyst_pPbpp[ipt]->Clone(Form("hsystNegpPbpp%d",ipt));
  hsystNeg_pPbpp[ipt]->Scale(-1.);
  fit_binbybin_pPbpp[ipt] = (TF1*)f_syst_pPbpp[ipt]->Get("fit4");
 } 
 cout<<4<<endl;
 TTree * nt_mc[filemcindex[npt-1]+1];
 TTree *nt_data[fileindex[npt-1]+1][2];
 TH1D * hist_eta_perdir[npt][2];
 TH1D * hist_dir_syst[npt];
 TH1D * hist_eta[npt];
 TH1D * hist_eta_mc[npt];
 for(int ifile = 0; ifile < 3; ifile++){
 cout<<"ifile"<<ifile<<endl;
  // nt_mc[ifile] = (TTree*)f_mc[ifile]->Get("ntdijet_corr");
  nt_mc[ifile] = (TTree*)f_mc[ifile]->Get("ntdijet");
  nt_mc[ifile]->Print();
 }
 for(int ifile = 0; ifile < 3; ifile++){
  for(int idir = 0; idir < 2; idir++){
   // if(ifile==1 && idir==1)continue;
   cout<<"ifile"<<ifile<<"idir"<<idir<<endl;
   nt_data[ifile][idir] = (TTree*)f_data[ifile][idir]->Get("ntdijet");
   nt_data[ifile][idir]->Print();
  }
 }
 double bin_pt_min=30;
 double bin_pt_max=1000;
 cout<<5<<endl;
 const int ny=30;
 double x[ny+1];
 double inix=log(bin_pt_min)/log(10); 
 double delta=(log(bin_pt_max)-log(bin_pt_min))/(30*log(10));
 for(int ix=0; ix<ny+1;ix++){
  x[ix]=pow(10,inix); 
  inix+=delta;
 }
 
 for(int ipt = 0; ipt < npt ; ipt++){
 cout<<ipt<<endl;
  hist_eta[ipt] = new TH1D(Form("hist_eta_%d",ipt),";#eta_{dijet};Event fraction",netabins,etabins);
  hist_eta_mc[ipt] = new TH1D(Form("hist_eta_pp_%d",ipt),";#eta_{dijet};Event fraction",netabins,etabins);
  nt_mc[filemcindex[ipt]]->Draw(Form("(jteta1+jteta2)/2>>hist_eta_pp_%d",ipt),Form("jtpt1>30 && jtpt2>20 && ((jtpt1+jtpt2)/2)>=%d && ((jtpt1+jtpt2)/2)<%d && %s && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1],datasetPP[ipt].Data()));
  for(int idir=0; idir<2;idir++){ 
   // if(fileindex[ipt]==1 && idir==1)continue; 
   // if(idir==0)continue; 
   hist_eta_perdir[ipt][idir] = new TH1D(Form("hist_eta_perdir_%d%d",ipt,idir),";#eta_{dijet};Event fraction",netabins,etabins);
   if(idir==0)nt_data[fileindex[ipt]][idir]->Draw(Form("-(jteta1+jteta2)/2>>hist_eta_perdir_%d%d",ipt,idir),Form("jtpt1>30 && jtpt2>20 && ((jtpt1+jtpt2)/2)>=%d && ((jtpt1+jtpt2)/2)<%d && %s && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1], dataset[ipt].Data()));
   else nt_data[fileindex[ipt]][idir]->Draw(Form("(jteta1+jteta2)/2>>hist_eta_perdir_%d%d",ipt,idir),Form("jtpt1>30 && jtpt2>20 && ((jtpt1+jtpt2)/2)>=%d && ((jtpt1+jtpt2)/2)<%d && %s && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1], dataset[ipt].Data()));
   cout << Form("(jteta1+jteta2)/2>>hist_eta_perdir_%d%d",ipt,idir) << Form("jtpt1>30 && jtpt2>20 && ((jtpt1+jtpt2)/2)>=%d && ((jtpt1+jtpt2)/2)<%d && %s && acos(cos(jtphi1-jtphi2))>(2*TMath::Pi()/3)", ptlow[ipt], ptlow[ipt+1], dataset[ipt].Data()) << endl;
   hist_eta[ipt]->Add(hist_eta_perdir[ipt][idir]);
   cout << hist_eta[ipt]->Integral() << endl;
  }  
  hist_eta_mc[ipt]->SetMarkerStyle(21); 
  hist_eta_mc[ipt]->SetMarkerColor(kBlue+1);
  hist_eta_mc[ipt]->SetLineColor(kBlue+1);
  hist_eta[ipt]->SetMarkerColor(kRed+1);
  hist_eta[ipt]->SetLineColor(kRed+1);
  //turn off unfolding
   /*
  for(int ibin = 0; ibin < netabins; ibin++){
   hist_eta_mc[ipt]->SetBinContent(ibin+1, hist_eta_mc[ipt]->GetBinContent(ibin+1)*fit_binbybin[ipt]->Eval(hist_eta_mc[ipt]->GetBinCenter(ibin+1)));
  }
  for(int ibin = 0; ibin < netabins; ibin++){ 
   hist_eta[ipt]->SetBinContent(ibin+1, hist_eta[ipt]->GetBinContent(ibin+1)*fit_binbybin_pPb[ipt]->Eval(hist_eta[ipt]->GetBinCenter(ibin+1)));
  }

  hist_eta_mc[ipt]->Scale(1./hist_eta_mc[ipt]->Integral());
  hist_eta[ipt]->Scale(1./hist_eta[ipt]->Integral());
  */
  for(int idir = 0; idir < 2; idir++){
   hist_eta_perdir[ipt][idir]->Scale(1./hist_eta_perdir[ipt][idir]->Integral());
  } 
  hist_dir_syst[ipt] = (TH1D*)hist_eta_perdir[ipt][0]->Clone(Form("hist_dir_syst_%d",ipt));
  hist_dir_syst[ipt]->Divide(hist_eta_perdir[ipt][1]);
  

 } 
  
 TLegend *t3=new TLegend(0.45,0.8,0.9,0.93);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->SetFillStyle(0);
 t3->SetTextFont(43);
 t3->SetTextSize(25); 

 TLegend *t4=new TLegend(0.45,0.8,0.9,0.93);
 t4->SetFillColor(0);
 t4->SetBorderSize(0);
 t4->SetFillStyle(0);
 t4->SetTextFont(43);
 t4->SetTextSize(25); 

 TH1D * empty = new TH1D("empty",";#eta_{dijet};(1/N_{dijet})dN_{dijet}/d#eta_{dijet}",netabins,etabins);
 empty->Fill(0.,1000);  
 empty->Fill(0.,1000);  
 empty->SetMaximum(0.6999);
 empty->SetMinimum(0.00001); 
 makePretty(empty,2.2);
 empty->GetXaxis()->CenterTitle(); 
 empty->GetYaxis()->CenterTitle();
 TCanvas * c1 = new TCanvas("c1","",1200,800);
 makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.22,0.22,0.02);
 t3->AddEntry(hist_eta[0],"pPb 5.02 TeV","p");
 t3->AddEntry(hist_eta_mc[0],"pp 5.02 TeV","p");
 hist_eta[0]->SetFillColor(kTeal-5);
 hist_eta_mc[0]->SetFillColor(kOrange);
 t4->AddEntry(hist_eta[0],"pPb 5.02 TeV","f");
 t4->AddEntry(hist_eta_mc[0],"pp 5.02 TeV","f");
 TBox *box[npt][netabins];
 TBox *boxpPb[npt][netabins];
 for(int ipt = 0; ipt < npt; ipt++){
  c1->cd(ipt+1);
  empty->Draw();

  hist_eta[ipt]->Draw("same");
  
  for(int ibin = 0; ibin < netabins; ibin++){
   float centerx = hist_eta_mc[ipt]->GetBinCenter(ibin+1);
   float centery = hist_eta_mc[ipt]->GetBinContent(ibin+1);
   float error = hsyst[ipt]->GetBinContent(ibin+1)*hist_eta_mc[ipt]->GetBinContent(ibin+1);
   float width = hist_eta_mc[ipt]->GetBinWidth(ibin+1);
   float widthpp = width/2;
   float upy = error + centery;
   float downy = -error + centery;
   box[ipt][ibin] = new TBox(centerx-widthpp,downy,centerx+widthpp,upy);
   box[ipt][ibin]->SetFillColor(kOrange);
   box[ipt][ibin]->SetLineColor(kOrange);
   box[ipt][ibin]->Draw("same");
  }

  for(int ibin = 0; ibin < netabins; ibin++){
   float centerx = hist_eta[ipt]->GetBinCenter(ibin+1);
   float centery = hist_eta[ipt]->GetBinContent(ibin+1);
   float error = hsyst_pPb[ipt]->GetBinContent(ibin+1)*hist_eta[ipt]->GetBinContent(ibin+1);
   float width = hist_eta[ipt]->GetBinWidth(ibin+1);
   float widthpp = width/2.;
   float upy = error + centery;
   float downy = -error + centery;
   boxpPb[ipt][ibin] = new TBox(centerx-widthpp,downy,centerx+widthpp,upy);
   boxpPb[ipt][ibin]->SetFillColor(kTeal-5);
   boxpPb[ipt][ibin]->SetLineColor(kTeal-5);
   boxpPb[ipt][ibin]->Draw("same");
  }

  hist_eta_mc[ipt]->Draw("same");
  hist_eta[ipt]->Draw("same");
    c1->cd(ipt+1)->RedrawAxis();

  if(ipt==0) drawText("CMS Preliminary",0.27,0.85);
  
  if(ipt==1)    drawText("p_{T,1} > 30 GeV",0.05,0.85);
  if(ipt==2)    drawText("p_{T,2} > 20 GeV",0.05,0.85);
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.25,0.75);
  if(ipt == 1 || ipt == 2 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.05,0.75);
  if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.25,0.75);
  if(ipt == 4 || ipt ==5 ) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.05,0.75);
 }
 t4->Draw("same");
 t3->Draw("same");
 c1->SaveAs("dijetetaindijetptbinspPb.png");
 c1->SaveAs("dijetetaindijetptbinspPb.pdf"); 
 c1->SaveAs("dijetetaindijetptbinspPb.C");

 TLine *line = new TLine(-2.999,0.,2.999,0.);
 TH1D * hrat[npt];
 for(int ipt = 0; ipt < npt; ipt++){
  hrat[ipt] = (TH1D*)hist_eta[ipt]->Clone(Form("hrat%d",ipt));
  hrat[ipt]->Add(hist_eta_mc[ipt],-1);
 }
 TH1D * empty2 = new TH1D("empty2",";#eta_{dijet};pPb-pp",netabins,etabins);
 empty2->Fill(0.,1000);
 empty2->SetMaximum(0.05999);
 empty2->SetMinimum(-0.05999);
 makePretty(empty2,2.3);
 empty2->GetXaxis()->CenterTitle();
 empty2->GetYaxis()->CenterTitle();
 TCanvas * c2 = new TCanvas("c2","",1200,800);
 makeMultiPanelCanvas(c2,3,2,0.0,0.,0.2,0.2,0.02);
 for(int ipt = 0; ipt < npt; ipt++){
  c2->cd(ipt+1);
  empty2->Draw();

  hsyst_pPbpp[ipt]->SetFillColor(kOrange);
  hsyst_pPbpp[ipt]->SetLineColor(kOrange);
  hsystNeg_pPbpp[ipt]->SetFillColor(kOrange);
  hsystNeg_pPbpp[ipt]->SetLineColor(kOrange);

  hsyst_pPbpp[ipt]->Draw("same hist C");
  hsystNeg_pPbpp[ipt]->Draw("same hist C");
  hrat[ipt]->SetMarkerColor(kBlue+1);
  hrat[ipt]->SetLineColor(kBlue+1);
  hrat[ipt]->Draw("same");

  line->Draw("same");
  if(ipt==0) drawText("CMS Preliminary",0.27,0.85);
  if(ipt==1) drawText("p_{T,1} > 30 GeV",0.05,0.85);
  if(ipt==2) drawText("p_{T,2} > 20 GeV",0.05,0.85);
  if(ipt == 0 )drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.25,0.75);
  if(ipt == 1 || ipt == 2) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.05,0.75);
  if(ipt == 3) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.25,0.75);
  if(ipt == 4 || ipt ==5) drawText(Form("%d < p_{T}^{ave} < %d", ptlow[ipt], ptlow[ipt+1]),0.05,0.75);
  line->Draw("same");
  c2->cd(ipt+1)->RedrawAxis();

 }
 c2->SaveAs("ratdijetetaindijetptbinspPb.png");
 c2->SaveAs("ratdijetetaindijetptbinspPb.pdf");
 c2->SaveAs("ratdijetetaindijetptbinspPb.C");
 
 TFile * outf = new TFile("outf_pPb_pp_20170116_pPb_noL3.root","recreate");
 for(int ipt = 0; ipt < npt; ipt++){
  hist_eta[ipt]->Write();
  hist_eta_mc[ipt]->Write();
  hrat[ipt]->Write();
  hist_dir_syst[ipt]->Write();
  for(int idir = 0; idir < 2; idir++){
   hist_eta_perdir[ipt][idir]->Write();
  }
 }
 outf->Close();
}
