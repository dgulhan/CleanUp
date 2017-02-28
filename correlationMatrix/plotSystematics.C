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

void plotSystematics(){
 TH1D::SetDefaultSumw2();
 TH1F::SetDefaultSumw2();
 
 TString mode = "pp_boost_v4_noweight_neg";  //"pPb_v3", "pp_boost" 
 // TString mode = "pPb_boost_v4";  //"pPb_v3", "pp_boost" 
 
  
 // int neta = 28;
 // float etabins[] = {-2.999, -2.500, -2.172,
                  // - 1.930, -1.740,-1.566,-1.392,
				  // -1.218, -1.044, -0.879, -0.696,
				  // -0.522,-0.348,-0.174, 0,
                       // 0.174,    0.348,    0.522, 
                      // 0.696,   0.879,   1.044,   1.218,
                        // 1.392,   1.566,  1.740,  
                      // 1.930,   2.172,   2.500,  
                      // 2.999};
 
 int neta = 18; 
 double etabins[19]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};
 
 // if(mode == "pPb_boost_v4_noweight" || mode=="pp_boost_v4_noweight_neg"){
  // neta = netabinspPb;
  // for(int ibin = 0; ibin < neta+1; ibin++){
   // etabins[ibin] = etabinspPb[ibin];
  // }
 // }
 
 int npt = 6;
 // TFile * file = new TFile(Form("distsPtSmearing_test5_%s_v3.root", mode.Data()));
 TFile * file = new TFile(Form("distsPtSmearing_test5_%s.root", mode.Data()));
 TTree * ntdijet[npt];
 TH1F * histGen[npt];
 TH1F * histGenFromTree[npt];
 TH1F * histGenNoWeight[npt];
 TH1F * histSmear[npt];
 TH1F * histEtaSmear[npt];
 TH1F * histJESOffset[npt];
 TH1F * histJESDataMCUp[npt];
 TH1F * histJESDataMCDown[npt];
 TH1F * histEtaOffset[npt];
 TH1F * histFake[npt];
 TH1F * histSmearNoWeight[npt];
 TH1F * histEtaSmearNoWeight[npt];
 TH1F * histJESOffsetNoWeight[npt];
 TH1F * histUnfolding[npt];
 TH1F * histRat[npt];
 TH1F * histRatEtaRes[npt];
 TH1F * histRatJESOffset[npt];
 TH1F * histRatNoWeight[npt];
 TH1F * histRatEtaResNoWeight[npt];
 TH1F * histRatJESOffsetNoWeight[npt];
 TH1F * histRatFake[npt];
 TH1F * histRatDataMCUp[npt];
 TH1F * histRatDataMCDown[npt];
 TH1F * histRatUnfolding[npt];
 TH1F * histRatEtaOffset[npt];
 int ptlow[]= {25,55,75,95,115,150,400}; 
 TLine * line;
 line = new TLine(-2.9999, 1., 2.9999, 1.);
 // else line = new TLine(-2.9999, 1., 2.9999, 1.);
 float slopefake = 2; //0.015;
 if(mode == "pp_boost") slopefake = 2.;
 
 for(int ipt = 0; ipt < npt; ipt++){
  // histGen[ipt] = (TH1F*)file->Get(Form("histGenDijetEtaNoWeight%d",ipt));
  histGen[ipt] = (TH1F*)file->Get(Form("histGenDijetEta%d",ipt));
  histGenNoWeight[ipt] = (TH1F*)file->Get(Form("histGenDijetEtaNoWeight%d",ipt));
  histSmearNoWeight[ipt] = (TH1F*)file->Get(Form("histSmearDijetEtaNoWeight%d",ipt));
  histEtaSmearNoWeight[ipt] = (TH1F*)file->Get(Form("histEtaSmearDijetEtaNoWeight%d",ipt));
  histJESOffsetNoWeight[ipt] = (TH1F*)file->Get(Form("histJESOffsetDijetEtaNoWeight%d",ipt));
  histSmear[ipt] = (TH1F*)file->Get(Form("histSmearDijetEta%d",ipt));
  histEtaSmear[ipt] = (TH1F*)file->Get(Form("histEtaSmearDijetEta%d",ipt));
  histJESOffset[ipt] = (TH1F*)file->Get(Form("histJESOffsetDijetEta%d",ipt));
  histFake[ipt] = new TH1F(Form("histFake%d",ipt),"",neta,etabins);
  histJESDataMCUp[ipt] = new TH1F(Form("histJESDataMCUp%d",ipt),"",neta,etabins);
  histJESDataMCDown[ipt] = new TH1F(Form("histJESDataMCDown%d",ipt),"",neta,etabins);
  histGenFromTree[ipt] = new TH1F(Form("histGenFromTree%d",ipt),"",neta,etabins);
  histUnfolding[ipt] = new TH1F(Form("histUnfolding%d",ipt),"",neta,etabins);
  histEtaOffset[ipt] = new TH1F(Form("histEtaOffset%d",ipt),"",neta,etabins);
  
  ntdijet[ipt] = (TTree*)file->Get(Form("ntdijet_smeared%d",ipt));
  ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histFake%d",ipt),Form("(fake1+fake2)*(%.2f*(jteta1+jteta2)/2./3.+1)*(jtpt1 > 30 && jtpt2 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)/2. >= %d && (jtpt1+jtpt2)/2.<%d)",slopefake,ptlow[ipt],ptlow[ipt+1]));
  ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histGenFromTree%d",ipt),Form("(jtpt1 > 30 && jtpt2 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)/2. >= %d && (jtpt1+jtpt2)/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histJESDataMCDown%d",ipt),Form("(jtpt1*0.98 > 30 && jtpt2*0.98 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)*0.98/2. >= %d && (jtpt1+jtpt2)*0.98/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histJESDataMCUp%d",ipt),Form("(jtpt1*1.02 > 30 && jtpt2*1.02 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)*1.02/2. >= %d && (jtpt1+jtpt2)*1.02/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  // ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histJESDataMCDown%d",ipt),Form("(jtpt1*0.995 > 30 && jtpt2*0.995 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)*0.995/2. >= %d && (jtpt1+jtpt2)*0.995/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  // ntdijet[ipt]->Draw(Form("-(jteta1+jteta2)/2.>>histJESDataMCUp%d",ipt),Form("(jtpt1*1.005 > 30 && jtpt2*1.005 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)*1.005/2. >= %d && (jtpt1+jtpt2)*1.005/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  ntdijet[ipt]->Draw(Form("-(jteta1sm*(1-2*(%.3f)*abs((jteta1sm+0.465)/3.))+jteta2sm*(1-2*(%.3f)*abs((jteta2sm+0.465)/3.)))/2.>>histUnfolding%d",(6-((float)ipt))*2/1000.,(6-((float)ipt))*2/1000., ipt),Form("(jtpt1sm > 30 && jtpt2sm > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1sm+jtpt2sm)/2. >= %d && (jtpt1sm+jtpt2sm)/2.<%d)",ptlow[ipt],ptlow[ipt+1]));
  ntdijet[ipt]->Draw(Form("-(jteta1sm*(1-2*(%.3f)*abs((jteta1sm+0.465)/3.))+jteta2sm*(1-2*(%.3f)*abs((jteta2sm+0.465)/3.)))/2.>>histEtaOffset%d",(6-((float)ipt))*2/1000.,(6-((float)ipt))*2/1000., ipt),Form("(jtpt1 > 30 && jtpt2 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)/2. >= %d && (jtpt1+jtpt2)/2.<%d)",ptlow[ipt],ptlow[ipt+1]));

  histFake[ipt]->Add(histGenFromTree[ipt]);
  histGen[ipt]->Scale(1./histGen[ipt]->Integral());
  histSmear[ipt]->Scale(1./histSmear[ipt]->Integral());
  histEtaSmear[ipt]->Scale(1./histEtaSmear[ipt]->Integral());
  histJESOffset[ipt]->Scale(1./histJESOffset[ipt]->Integral());
  histSmearNoWeight[ipt]->Scale(1./histSmear[ipt]->Integral());
  histEtaSmearNoWeight[ipt]->Scale(1./histEtaSmear[ipt]->Integral());
  histJESOffsetNoWeight[ipt]->Scale(1./histJESOffset[ipt]->Integral());
  histGenNoWeight[ipt]->Scale(1./histGenNoWeight[ipt]->Integral());
  histFake[ipt]->Scale(1./histFake[ipt]->Integral());
  histGenFromTree[ipt]->Scale(1./histGenFromTree[ipt]->Integral());
  histJESDataMCUp[ipt]->Scale(1./histJESDataMCUp[ipt]->Integral());
  histJESDataMCDown[ipt]->Scale(1./histJESDataMCDown[ipt]->Integral());
  histUnfolding[ipt]->Scale(1./histUnfolding[ipt]->Integral());
  histEtaOffset[ipt]->Scale(1./histEtaOffset[ipt]->Integral());

  histRat[ipt] = (TH1F*) histSmear[ipt]->Clone(Form("histRat%d",ipt));
  histRat[ipt]->Divide(histGen[ipt]);
  histRatEtaRes[ipt] = (TH1F*) histEtaSmear[ipt]->Clone(Form("histRatEtaRes%d",ipt));
  histRatEtaRes[ipt]->Divide(histGen[ipt]);
  histRatJESOffset[ipt] = (TH1F*) histJESOffset[ipt]->Clone(Form("histRatJESOffset%d",ipt));
  histRatJESOffset[ipt]->Divide(histGen[ipt]);
  histRatFake[ipt] = (TH1F*) histFake[ipt]->Clone(Form("histRatFake%d",ipt));
  histRatFake[ipt]->Divide(histGenFromTree[ipt]);
  histRatDataMCUp[ipt] = (TH1F*) histJESDataMCUp[ipt]->Clone(Form("histRatDataMCUp%d",ipt));
  histRatDataMCUp[ipt]->Divide(histGenFromTree[ipt]);
  histRatDataMCDown[ipt] = (TH1F*) histJESDataMCDown[ipt]->Clone(Form("histRatDataMCDown%d",ipt));
  histRatDataMCDown[ipt]->Divide(histGenFromTree[ipt]);
  histRatUnfolding[ipt] = (TH1F*) histUnfolding[ipt]->Clone(Form("histRatUnfolding%d",ipt));
  histRatUnfolding[ipt]->Divide(histGenFromTree[ipt]);
  histRatEtaOffset[ipt] = (TH1F*) histEtaOffset[ipt]->Clone(Form("histRatEtaOffset%d",ipt));
  histRatEtaOffset[ipt]->Divide(histGenFromTree[ipt]);
  
  histRatNoWeight[ipt] = (TH1F*) histSmearNoWeight[ipt]->Clone(Form("histRatNoWeight%d",ipt));
  histRatNoWeight[ipt]->Divide(histGenNoWeight[ipt]);
  histRatEtaResNoWeight[ipt] = (TH1F*) histEtaSmearNoWeight[ipt]->Clone(Form("histRatEtaResNoWeight%d",ipt));
  histRatEtaResNoWeight[ipt]->Divide(histGenNoWeight[ipt]);
  histRatJESOffsetNoWeight[ipt] = (TH1F*) histJESOffsetNoWeight[ipt]->Clone(Form("histRatJESOffsetNoWeight%d",ipt));
  histRatJESOffsetNoWeight[ipt]->Divide(histGenNoWeight[ipt]);
 }

 TH1D *histTotal[npt];
 TH1D *histTotalNegative[npt];
 TH1D *histTotalPositive[npt];
 
 for(int ipt = 0; ipt < npt; ipt++){
  histTotal[ipt] = (TH1D*)histRatJESOffset[ipt]->Clone(Form("histTotal%d",ipt));
  histTotalNegative[ipt] = (TH1D*)histRatJESOffset[ipt]->Clone(Form("histTotalNegative%d",ipt));
  histTotalPositive[ipt] = (TH1D*)histRatJESOffset[ipt]->Clone(Form("histTotalPositive%d",ipt));
  
  for(int ibin = 0; ibin < histRat[ipt]->GetNbinsX(); ibin++){
   float yptres = histRat[ipt]->GetBinContent(ibin+1);
   float yetares = histRatEtaRes[ipt]->GetBinContent(ibin+1);
   float yptoff = histRatJESOffset[ipt]->GetBinContent(ibin+1);
   float yfake = histRatFake[ipt]->GetBinContent(ibin+1);
   float yjesup = histRatDataMCUp[ipt]->GetBinContent(ibin+1);
   float yjesdown = histRatDataMCDown[ipt]->GetBinContent(ibin+1);
   histTotal[ipt]->SetBinContent(ibin+1, sqrt(pow(yptres-1,2.)+pow(yetares-1,2.)+pow(yptoff-1,2.)+pow(yfake-1,2))+1);
   histTotalPositive[ipt]->SetBinContent(ibin+1, sqrt(pow(TMath::Max(yptres-1,0.),2.)+pow(TMath::Max(yetares-1,0.),2.)+pow(TMath::Max(yptoff-1,0.),2.)+pow(TMath::Max(yfake-1,0.),2)+pow(TMath::Max(yjesup-1,0.),2)+pow(TMath::Max(yjesdown-1,0.),2))+1);
   histTotalNegative[ipt]->SetBinContent(ibin+1, -sqrt(pow(TMath::Min(yptres-1,0.),2.)+pow(TMath::Min(yetares-1,0.),2.)+pow(TMath::Min(yptoff-1,0.),2.)+pow(TMath::Min(yfake-1,0.),2)+pow(TMath::Min(yjesup-1,0.),2)+pow(TMath::Min(yjesdown-1,0.),2))+1);
  }
    }

 TFile * outf = new TFile(Form("systematics_%s_forrat_test3.root", mode.Data()),"recreate");
 for(int ipt = 0; ipt < npt; ipt++){
 
  histRatJESOffset[ipt]->Write();
  histRat[ipt]->Write();
  histRatEtaRes[ipt]->Write();
  histRatFake[ipt]->Write();
  histRatDataMCUp[ipt]->Write(); 
  histRatDataMCDown[ipt]->Write();
  histRatUnfolding[ipt]->Write();
  histRatEtaOffset[ipt]->Write();
  
  histTotalNegative[ipt]->Write();
  histTotalPositive[ipt]->Write();
  histTotal[ipt]->Write();

  histSmear[ipt]->Write();
  histEtaSmear[ipt]->Write();
  histGen[ipt]->Write();
  histJESDataMCUp[ipt]->Write();
  histJESDataMCDown[ipt]->Write();
  histUnfolding[ipt]->Write();
  histJESOffset[ipt]->Write();
  histEtaOffset[ipt]->Write();

 }
 outf->Close();
}
