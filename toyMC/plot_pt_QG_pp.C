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
#include "TComplex.h"
#include "TString.h"  
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h" 


void makeMultiPanelCanvas(TCanvas*& canv,
                          const Int_t columns,
                          const Int_t rows,
                          const Float_t leftOffset,
                          const Float_t bottomOffset,
                          const Float_t leftMargin,
                          const Float_t bottomMargin,
                          const Float_t edge) {
   if (canv==0) {
      Error("makeMultiPanelCanvas","Got null canvas.");
      return;
   }
   canv->Clear();
   
   TPad* pad[columns][rows];

   Float_t Xlow[columns];
   Float_t Xup[columns];
   Float_t Ylow[rows];
   Float_t Yup[rows];
   Float_t PadWidth = 
   (1.0-leftOffset)/((1.0/(1.0-leftMargin)) +
   (1.0/(1.0-edge))+(Float_t)columns-2.0);
   Float_t PadHeight =
   (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) +
   (1.0/(1.0-edge))+(Float_t)rows-2.0);
   Xlow[0] = leftOffset;
   Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
   Xup[columns-1] = 1;
   Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);

   Yup[0] = 1;
   Ylow[0] = 1.0-PadHeight/(1.0-edge);
   Ylow[rows-1] = bottomOffset;
   Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);

   for(Int_t i=1;i<columns-1;i++) {
      Xlow[i] = Xup[0] + (i-1)*PadWidth;
      Xup[i] = Xup[0] + (i)*PadWidth;
   }
   Int_t ct = 0;
   for(Int_t i=rows-2;i>0;i--) {
      Ylow[i] = Yup[rows-1] + ct*PadHeight;
      Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
      ct++;
   }

   TString padName;
   for(Int_t i=0;i<columns;i++) {
      for(Int_t j=0;j<rows;j++) {
         canv->cd();
         padName = Form("p_%d_%d",i,j);
         pad[i][j] = new TPad(padName.Data(),padName.Data(),
            Xlow[i],Ylow[j],Xup[i],Yup[j]);
         if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
         else pad[i][j]->SetLeftMargin(0);

         if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
         else pad[i][j]->SetRightMargin(0);

         if(j==0) pad[i][j]->SetTopMargin(edge);
         else pad[i][j]->SetTopMargin(0);

         if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
         else pad[i][j]->SetBottomMargin(0);

         pad[i][j]->Draw();
         pad[i][j]->cd();
         pad[i][j]->SetNumber(columns*j+i+1);
      }
   }
}

void drawText(const char *text, float xp, float yp, int size=24){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw("same");
}

void drawPatch(float x1, float y1, float x2, float y2){
  TLegend *t1=new TLegend(x1,y1,x2,y2);
  t1->SetFillColor(kWhite);
  t1->SetBorderSize(0);
  t1->SetFillStyle(1001);
  t1->Draw("");
}

void plot_pt_QG_pp(){
 TH1D::SetDefaultSumw2();
 bool doreco=false;
 bool dores=true;
 TString xaxis,corr_string;
 if(doreco)xaxis="jtpt";
 else xaxis="refpt";
 if(dores)corr_string="jtpt";
 else corr_string="jtpt";

 TString mode = "pPb"; 
 int nR=1;
 int nfile=9;
 // int nfile=6;
 

 int pthat[]={15,30,50,80,120,170,220,280,370};
 // int pthat[]={15,30,50,80,120,170,220,280,370,460,540};
 // int pthat[]={15,30,50,80,120};
 TFile *f_ntrk[nfile][nR];
 TFile *f_ntrk2[nfile];
 TFile *f_ntrk_pp[nfile];
 TTree * t_ntrk[nfile][nR];
 TTree * t_ntrk2[nfile];
 TTree * t_ntrk_pp[nfile];
  
 int nstep=2;
 
 // int RADIUS[]={2,3,4,5};
 int RADIUS[]={3,3,4,5};
 TString algo[nR];
 for(int iR=0;iR<nR;iR++){
  algo[iR]=Form("ak%dPF",RADIUS[iR]);
 }
 // algo[nR-1] = "ak4Calo";
 // int npt=11;
  int npt=9;

 double PFptcut=2;   

 double ntrkmax=20;  
 if(PFptcut==1)ntrkmax=40;
 if(PFptcut==2)ntrkmax=20;
 if(PFptcut==3)ntrkmax=25; 
 
 ntrkmax+=0.5;
 
 int pt[]={25,45,65,100,140,190,240,300,400,700};
 int pt_pPb[]={25,55,60,100,140,190,700};
 if(mode=="pPb"){
  int nfile = 6;
  int npt = 6;
  
  for(int ipt = 0;ipt<npt+1; ipt++){
   pt[ipt] = pt_pPb[ipt];
  }
 }
 
 int npt_histograms=19;
 double pt_histograms[]={25,30,35,40,45,50,55,65,75,85,100,120,140,165,190,240,300,400,500,700};

 TH1D *p_ntrk_corr_ntrk[npt][nfile][nR];
 TH1D *p_gauss_corr[npt][nfile][nR]; 
 TH1D *p_ntrk[npt][nfile][nR];
 TH1D *p_ntrk_higheta[npt][nfile][nR];
 
 TH1D *histbin_ntrk_corr_ntrk[npt][nfile][nR][npt_histograms];
 TH1D *histbin_ntrk[npt][nfile][nR][npt_histograms];
 TH1D *histbin_ntrk_higheta[npt][nfile][nR][npt_histograms];
 TH1D *hist_response[nR][npt_histograms];
 
 TF1 *fit_ntrk_corr_ntrk[npt][nfile][nR][npt_histograms];
 TF1 *fit_ntrk[npt][nfile][nR][npt_histograms];
 TF1 *fit_ntrk_higheta[npt][nfile][nR][npt_histograms];
 TF1 *fit_response[nR][npt_histograms];
 
 for(int ifile=0;ifile<nfile;ifile++){
  for(int iR=0;iR<nR;iR++){ 
   cout<<ifile<<endl; 
   if(mode=="pp")f_ntrk[ifile][iR] = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/pthat%d_ak3PF_eta4.root",pthat[ifile]));
   if(mode=="pPb")f_ntrk[ifile][iR] = new TFile(Form("/export/d00/scratch/dgulhan/ppDijet/data_driven_jec/ntuples/ntuples_pthat%d_rescorr2.root",pthat[ifile]));
   // t_ntrk[ifile][iR]= (TTree*)f_ntrk[ifile][iR]->Get(Form("%sJetAnalyzer/t",algo[iR].Data()));
   t_ntrk[ifile][iR]= (TTree*)f_ntrk[ifile][iR]->Get("ntjet");
   t_ntrk[ifile][iR]->Print();
  }
 }

 TH1D * h_ntrk_corr_ntrk[nR];
 TH1D * h_gauss_corr[nR];
 TF1 * fit_gauss_corr[nR];
 
 TH1D * h_ntrk[nR];
 TH1D * h_ntrk_higheta[nR];

for(int iR=0;iR<nR;iR++){ 
 h_ntrk_corr_ntrk[iR] = new TH1D(Form("h_ntrk_corr_ntrk%d",iR),"",npt_histograms,pt_histograms);
 h_gauss_corr[iR] = new TH1D(Form("h_gauss_corr%d",iR),";p_{T}^{gen};#sigma/#mu;",npt_histograms,pt_histograms);
 
 h_ntrk[iR] = new TH1D(Form("h_ntrk%d",iR),"",npt_histograms,pt_histograms);
 h_ntrk_higheta[iR] = new TH1D(Form("h_ntrk_higheta_%d",iR),"",npt_histograms,pt_histograms);

 for(int ifile=0;ifile<nfile;ifile++){
  for(int ipt=0;ipt<npt;ipt++){
   p_ntrk_corr_ntrk[ipt][ifile][iR] = new TH1D(Form("p_ntrk_corr_ntrk%d%d%d",ipt,ifile,iR),"",npt_histograms,pt_histograms);
   p_gauss_corr[ipt][ifile][iR] = new TH1D(Form("p_gauss_corr%d%d%d",ipt,ifile,iR),"",npt_histograms,pt_histograms);
   p_ntrk[ipt][ifile][iR] = new TH1D(Form("p_ntrk%d%d%d",ipt,ifile,iR),"",npt_histograms,pt_histograms);
   p_ntrk_higheta[ipt][ifile][iR] = new TH1D(Form("p_ntrk_higheta%d%d%d",ipt,ifile,iR),"",npt_histograms,pt_histograms);
    // if((ipt==0 && ifile==0) ||(ipt==1 && ifile==0)||(ipt==2 && ifile==0)||(ipt==3 && ifile==0)|| (ipt==4 && ifile==1)|| (ipt==5 && ifile==2)|| (ipt==6 && ifile==3)|| (ipt==7 && ifile==3)){
   // if((ipt==0 && ifile==0)|| (ipt==1 && ifile==1)|| (ipt==2 && ifile==2)|| (ipt==3 && ifile==3)|| (ipt==4 && ifile==3)){
   cout<<-1<<endl; 

   if(ipt==ifile){
   

    for(int ibin=0;ibin<npt_histograms;ibin++){ 
     cout<<0<<endl; 

     if(h_ntrk_corr_ntrk[iR]->GetBinCenter(ibin+1)>=pt[ipt] && h_ntrk_corr_ntrk[iR]->GetBinCenter(ibin+1)<pt[ipt+1]){
      cout<<0.5<<endl; 

      histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin] = new TH1D(Form("histbin_ntrk_corr_ntrk%d%d%d%d",ipt,ifile,iR,ibin),"",300,0,3);
      histbin_ntrk[ipt][ifile][iR][ibin] = new TH1D(Form("histbin_ntrk%d%d%d%d",ipt,ifile,iR,ibin),"",300,0,3);
      histbin_ntrk_higheta[ipt][ifile][iR][ibin] = new TH1D(Form("histbin_ntrk_higheta_%d%d%d%d",ipt,ifile,iR,ibin),"",300,0,3);
         cout<<0.6<<endl; 
     cout<<Form("%s>=%.1f && %s<%.1f && refpt>0 && abs(jteta)<3.",xaxis.Data(),pt_histograms[ibin],xaxis.Data(),pt_histograms[ibin+1])<<endl;
      cout<<Form("%s/refpt>>histbin_ntrk_corr_ntrk%d%d%d%d",corr_string.Data(),ipt,ifile,iR,ibin)<<endl;
      t_ntrk[ifile][iR]->Draw(Form("jtpt/refpt>>histbin_ntrk_corr_ntrk%d%d%d%d",ipt,ifile,iR,ibin),Form("%s>=%.1f && %s<%.1f && refpt>0 && abs(jteta)<3.",xaxis.Data(),pt_histograms[ibin],xaxis.Data(),pt_histograms[ibin+1]));

      t_ntrk[ifile][iR]->Draw(Form("jtpt/refpt>>histbin_ntrk%d%d%d%d",ipt,ifile,iR,ibin),Form("%s>=%.1f && %s<%.1f && refpt>0 && abs(jteta)<3.",xaxis.Data(),pt_histograms[ibin],xaxis.Data(),pt_histograms[ibin+1]));
      t_ntrk[ifile][iR]->Draw(Form("jtpt/refpt>>histbin_ntrk_higheta_%d%d%d%d",ipt,ifile,iR,ibin),Form("%s>=%.1f && %s<%.1f && refpt>0 && abs(jteta)>3. && abs(jteta)<3.465",xaxis.Data(),pt_histograms[ibin],xaxis.Data(),pt_histograms[ibin+1]));
      
      cout<<1<<endl;
     fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin] = new TF1(Form("fit_corr_ntrk%d%d%d%d",ipt,ifile,iR,ibin),"gaus(0)",0.7,1.3);
     fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->SetParameters(10,1,0.2);
     histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->Fit(fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin],"R");
     p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinContent(ibin+1,fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParameter(1));
     p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinError(ibin+1,fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParError(1));

	 hist_response[iR][ibin] = (TH1D*)histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->Clone(Form("hist_response%d_%d",iR,ibin));
	 fit_response[iR][ibin] = (TF1*)fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->Clone(Form("hist_response%d_%d",iR,ibin));
      cout<<2<<endl;
     fit_ntrk[ipt][ifile][iR][ibin] = new TF1(Form("fit_ntrk%d%d%d%d",ipt,ifile,iR,ibin),"gaus(0)",0.7,1.3);
     fit_ntrk[ipt][ifile][iR][ibin]->SetParameters(10,1,0.2);
     histbin_ntrk[ipt][ifile][iR][ibin]->Fit(fit_ntrk[ipt][ifile][iR][ibin],"R");
     p_ntrk[ipt][ifile][iR]->SetBinContent(ibin+1,fit_ntrk[ipt][ifile][iR][ibin]->GetParameter(1));
     p_ntrk[ipt][ifile][iR]->SetBinError(ibin+1,fit_ntrk[ipt][ifile][iR][ibin]->GetParError(1));
     
     fit_ntrk_higheta[ipt][ifile][iR][ibin] = new TF1(Form("fit_ntrk_higheta_%d%d%d%d",ipt,ifile,iR,ibin),"gaus(0)",0.7,1.3);
     fit_ntrk_higheta[ipt][ifile][iR][ibin]->SetParameters(10,1,0.2);
     histbin_ntrk_higheta[ipt][ifile][iR][ibin]->Fit(fit_ntrk_higheta[ipt][ifile][iR][ibin],"R");
	 cout << "stupid " << "ibin "<< ibin<< " " <<histbin_ntrk_higheta[ipt][ifile][iR][ibin]->GetEntries() << endl;
     p_ntrk_higheta[ipt][ifile][iR]->SetBinContent(ibin+1,fit_ntrk_higheta[ipt][ifile][iR][ibin]->GetParameter(1));
     p_ntrk_higheta[ipt][ifile][iR]->SetBinError(ibin+1,fit_ntrk_higheta[ipt][ifile][iR][ibin]->GetParError(1));
     
	  if(ibin>1){
       p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinContent(ibin+1,fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParameter(1));
       p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinError(ibin+1,fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParError(1));
       p_gauss_corr[ipt][ifile][iR]->SetBinContent(ibin+1,fabs(fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParameter(2)));
       p_gauss_corr[ipt][ifile][iR]->SetBinError(ibin+1,fit_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetParError(2));
	  }else{
       p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinContent(ibin+1,histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetMean());
       p_ntrk_corr_ntrk[ipt][ifile][iR]->SetBinError(ibin+1,histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetMeanError());
       p_gauss_corr[ipt][ifile][iR]->SetBinContent(ibin+1,histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetRMS());
       p_gauss_corr[ipt][ifile][iR]->SetBinError(ibin+1,histbin_ntrk_corr_ntrk[ipt][ifile][iR][ibin]->GetRMSError());
	  }
       
      cout<<3<<endl;
      h_ntrk_corr_ntrk[iR]->SetBinContent(ibin+1,p_ntrk_corr_ntrk[ipt][ifile][iR]->GetBinContent(ibin+1));
      h_gauss_corr[iR]->SetBinContent(ibin+1,p_gauss_corr[ipt][ifile][iR]->GetBinContent(ibin+1));
      h_ntrk[iR]->SetBinContent(ibin+1,p_ntrk[ipt][ifile][iR]->GetBinContent(ibin+1));
      h_ntrk_higheta[iR]->SetBinContent(ibin+1,p_ntrk_higheta[ipt][ifile][iR]->GetBinContent(ibin+1));
      h_ntrk_corr_ntrk[iR]->SetBinError(ibin+1,p_ntrk_corr_ntrk[ipt][ifile][iR]->GetBinError(ibin+1));
      h_gauss_corr[iR]->SetBinError(ibin+1,p_gauss_corr[ipt][ifile][iR]->GetBinError(ibin+1));
      h_ntrk[iR]->SetBinError(ibin+1,p_ntrk[ipt][ifile][iR]->GetBinError(ibin+1));
      h_ntrk_higheta[iR]->SetBinError(ibin+1,p_ntrk_higheta[ipt][ifile][iR]->GetBinError(ibin+1));

      cout<<4<<endl;
     }
    }
   }
  }
 }
}

 
 TLegend * leg4;
 if(doreco)leg4= new TLegend(0.45,0.6,0.85,0.8);
 else leg4= new TLegend(0.35,0.2,0.85,0.5);
 leg4->SetBorderSize(0); 
 leg4->SetFillStyle(0);
 leg4->SetTextFont(43);
 leg4->SetTextSize(22);
 leg4->AddEntry(h_ntrk[0],"L2+L3","p");
 leg4->AddEntry(h_ntrk_corr_ntrk[0],"L2+L3+fragmentation","p");
 
 TString axislabel;
 if(doreco) axislabel="p_{T}^{reco}";
 else axislabel="p_{T}^{gen}";
 TH1D * empty= new TH1D("empty",Form(";%s;<p_{T}^{reco}/p_{T}^{gen}>",axislabel.Data()),10,35,699.99);
 empty->Fill(30,1000);
 if(doreco)empty->SetMaximum(1.7);
 else{
  if(dores) empty->SetMaximum(1.05);
  else empty->SetMaximum(1.1);
 }
 if(doreco) empty->SetMinimum(0.8);
 else{
  if(dores) empty->SetMinimum(0.95);
  else empty->SetMinimum(0.6);
 }

 empty->GetXaxis()->SetTitleSize(28);
 empty->GetXaxis()->SetTitleFont(43); 
 empty->GetXaxis()->SetTitleOffset(1.2);
 empty->GetXaxis()->SetLabelSize(22);
 empty->GetXaxis()->SetLabelFont(43);
 empty->GetYaxis()->SetTitleSize(28);
 empty->GetYaxis()->SetTitleFont(43); 
 empty->GetYaxis()->SetTitleOffset(1.2);
 empty->GetYaxis()->SetLabelSize(22);
 empty->GetYaxis()->SetLabelFont(43);
   
 empty->GetXaxis()->SetNdivisions(505);
 empty->GetYaxis()->SetNdivisions(505);

 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();

 TH1D * empty_clone = (TH1D*)empty->Clone("empty_clone");
 cout<<"label size 0"<<endl;
 cout<<"title size 0"<<endl;
 empty_clone->GetYaxis()->SetTitleSize(0);
 empty_clone->GetYaxis()->SetLabelSize(0);
 
  TLine *l= new TLine(25,1,700,1);
  TLine *l_50= new TLine(30,1.05,30,0.95);
  l_50->SetLineStyle(2);
  TLine *l_2_up= new TLine(35,1.01,700,1.01);
  l_2_up->SetLineStyle(2);
  TLine *l_2_down= new TLine(35,0.99,700,0.99);
  l_2_down->SetLineStyle(2);
  
 // TCanvas * c2 = new TCanvas("c2","",nR*350,400); 
 TCanvas * c2 = new TCanvas("c2","",600,600); 
 // makeMultiPanelCanvas(c2,nR,1,0.0,0.0,0.2,0.2,0.02);
 for(int iR=0;iR<nR;iR++){
  c2->cd(iR+1)->SetLogx();
  if(iR==0) empty->Draw();
  else empty_clone->Draw();
  // h_ntrk_corr_ntrk[iR]->Draw("same");
  // h_ntrk_corr_ntrk_q[iR]->Draw();
  // h_ntrk[iR]->SetMarkerStyle(25);
  h_ntrk[iR]->Draw("same");
  // h_ntrk_q[iR]->Draw("same");
  // h_ntrk_g[iR]->Draw("same");
  // if(iR==0)leg4->Draw("same");
  drawText(Form("%s",algo[iR].Data()),0.55,0.85);
  if(iR==2) drawText("|#eta|<3",0.55,0.25);
  if(iR==1) drawText("PYTHIA + HIJING",0.05,0.25);
  l->Draw("same");
  // l_50->Draw("same");
  l_2_up->Draw("same");
  l_2_down->Draw("same");
 }
 c2->SaveAs(Form("plot_pt_dependence_residual/%s_dependence_%s_forallR_inclusive_%s.png",xaxis.Data(),corr_string.Data(),algo[0].Data()));
 c2->SaveAs(Form("plot_pt_dependence_residual/%s_dependence_%s_forallR_inclusive_%s.pdf",xaxis.Data(),corr_string.Data(),algo[0].Data()));
 
 
 TH1D* empty2 = (TH1D*)empty->Clone("empty2");
 empty2->SetMaximum(0.3);
 empty2->SetMinimum(0.0);
 empty2->GetYaxis()->SetTitle("#sigma/#mu");
 empty2->GetYaxis()->SetTitleOffset(0.5);
 empty2->GetXaxis()->SetTitleOffset(0.5);
 TH1D* empty2_clone = (TH1D*)empty_clone->Clone("empty2_clone");
 empty2_clone->SetMaximum(0.3);
 empty2_clone->SetMinimum(0.0);
 empty2_clone->GetYaxis()->SetTitle("#sigma/#mu");
 
 // TCanvas * c3 = new TCanvas("c3","",nR*350,400); 
 TCanvas * c3 = new TCanvas("c3","",nR*600,600); 
 // makeMultiPanelCanvas(c3,nR,1,0.0,0.0,0.2,0.2,0.02);
 for(int iR=0;iR<nR;iR++){
  c3->cd(iR+1)->SetLogx();
  if(iR==0) empty2->Draw();
  else empty2_clone->Draw();
  // h_ntrk_corr_ntrk[iR]->Draw("same");
  // h_ntrk_corr_ntrk_q[iR]->Draw();
  // h_ntrk[iR]->SetMarkerStyle(25);
  for(int ibin = 0; ibin < npt_histograms; ibin++){
   h_gauss_corr[iR]->SetBinContent(ibin+1,h_gauss_corr[iR]->GetBinContent(ibin+1)/h_ntrk[iR]->GetBinContent(ibin+1));
  }
  h_gauss_corr[iR]->Draw("same");
  
  // fit_gauss_corr[iR]= new TF1(Form("fit_gauss_corr%d",0),"sqrt([0]*[0]+[1]*[1]/x+([2]*[2]+0.5)*([2]*[2]+0.5)/pow(x,2))",40,700);
  fit_gauss_corr[iR]= new TF1(Form("fit_gauss_corr%d",0),"sqrt([0]*[0]+(TMath::Abs([1]))*(TMath::Abs([1]))/x)",40,700);
  fit_gauss_corr[iR]->SetParameters(0.2,0.5);
  h_gauss_corr[iR]->Fit(fit_gauss_corr[iR],"R");
  drawText(Form("%s",algo[iR].Data()),0.35,0.85);
  if(iR==2) drawText("|#eta|<3",0.35,0.25);
  l->Draw("same");
  l_50->Draw("same"); 
  l_2_up->Draw("same");
  l_2_down->Draw("same");
 }
 c3->SaveAs(Form("plot_pt_dependence_residual/resolution_%s_dependence_%s_forallR_inclusive_%s.png",xaxis.Data(),corr_string.Data(),algo[0].Data()));
 c3->SaveAs(Form("plot_pt_dependence_residual/resolution_%s_dependence_%s_forallR_inclusive_%s.pdf",xaxis.Data(),corr_string.Data(),algo[0].Data()));
 
  int ncent=1;
  if(1){
  TF1* fit[nR];
  TFile * outf[nR]; 
  for(int iR=0;iR<nR;iR++){ 
  cout << Form("output/residualcorr%d_%s.root",nstep,algo[iR].Data()) <<endl;
   outf[iR]=  new TFile(Form("output/residualcorr%d_%s.root",nstep,algo[iR].Data()),"recreate");
   fit[iR]= new TF1(Form("fit%d",0),"-[0]*[0]/x-[1]*[1]/pow(x,2)-[2]*[2]/pow(x,3)-[3]*[3]/pow(x,4)-[4]*[4]/pow(x,5)+1",50,300);
   // fit[iR]= new TF1(Form("fit%d",0),"[0]/x+[1]/pow(x,2)+[2]/pow(x,3)+[3]",27,700);
   // fit[iR]->SetParameters(-1.,-1.,-1.,0.);
   // fit[iR]= new TF1(Form("fit%d",iR),"[0]/x+[1]/pow(x,2)+[2]/pow(x,3)+[3]/pow(x,4)+[4]",25,300);
   fit[iR]->SetParameters(-1.,-1.,-1.,1.,1.);
  // if(!doreco){

   h_ntrk_corr_ntrk[iR]->Fit(fit[iR],"R");
   TCanvas *c2 = new TCanvas("c2","",600,600);
   // h_ntrk_corr_ntrk[iR]->SetMaximum(1.1);
   // h_ntrk_corr_ntrk[iR]->SetMinimum(0.9);
   // h_ntrk_corr_ntrk[iR]->SetMaximum(1.6);
   // h_ntrk_corr_ntrk[iR]->SetMinimum(0.6); 
   h_ntrk_corr_ntrk[iR]->Draw();
   c2->SaveAs(Form("plot_pt_dependence_residual/fit_to_nonclosure_%s_%d_step%d.png",algo[iR].Data(),iR,nstep));
   fit[iR]->Write();
   h_ntrk_corr_ntrk[iR]->Write();
   outf[iR]->Close();
  }
 } 
   
 
  TCanvas * cresponse[nR];
  for(int iR = 0; iR < nR; iR++){
   cresponse[iR] = new TCanvas(Form("cresponse%d",iR),"",1500,800);
   cresponse[iR]->Divide(5,3);
	
   for(int ibin = 0; ibin < npt_histograms; ibin++){
    cresponse[iR]->cd(ibin+1);
	hist_response[iR][ibin]->Draw();
	fit_response[iR][ibin]->Draw("same");
   }
   
   cresponse[iR]->SaveAs(Form("plot_pt_dependence_residual/response__%s.png",algo[iR].Data()));
  }
  
  TFile *outf_resolution = new TFile(Form("resolution/hists_%s.root",mode.Data()),"recreate");
  for(int iR = 0; iR < nR; iR++){
   h_ntrk[iR]->Write();
   h_ntrk_higheta[iR]->Write();
   h_gauss_corr[iR]->Write();
   fit_gauss_corr[iR]->Write();
  }
  outf_resolution->Close();
}

