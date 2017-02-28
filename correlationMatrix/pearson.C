//#include "plotPDFDoubleRatio.C"
//#include "plotPDFDoubleRatio_v2.C"
//#include "plotPDF.C"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "ntdijet_smeared0.C"
#include "/afs/cern.ch/user/d/dgulhan/workDir/private/thesisPlots/dijetpPb/utilities.h"

void pearson(){
  TFile * file = new TFile("../toyMC/distsPtSmearing_test5_pPb_boost_v4_noweight.root");
  int npt = 6;
  ntdijet_smeared0* tree[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    tree[ipt] = new ntdijet_smeared0(ipt,"../toyMC/distsPtSmearing_test5_pPb_boost_v4_noweight.root");
  }
  //  cout << 3 << endl;
  int netabins = 18;
  double etabinspPb[19]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};
  
  double ptlow[]= {25,55,75,95,115,150,400};
  TH2D *histCorr[npt];
  TH1D *histEtaGen[npt];
  TH1D *histEtaSm[npt];
  TH1D *histEtaGenSd[npt];
  TH1D *histEtaSmSd[npt];
  int nentries[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    histCorr[ipt] = new TH2D(Form("histCorr_%d",ipt),"",netabins,etabinspPb,netabins,etabinspPb); 
    nentries[ipt] = 10000;
  }
  TH2D *histCorrPt[netabins];
  
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPt[ieta] = new TH2D(Form("histCorrPt%d",ieta),"",npt,ptlow,npt,ptlow);
  }

  cout << 2 << endl;

  int Nevents[netabins];
  double MeanGen[netabins][npt];
  double MeanSm[netabins][npt];
  for(int ieta = 0; ieta < netabins; ieta++){
    Nevents[ieta] = 0;
    for(int ipt = 0; ipt < npt; ipt++){
      MeanGen[ieta][ipt] = 0.;
      MeanSm[ieta][ipt] = 0.;
      for(int ientry = 0; ientry < nentries[ipt]; ientry++){
        tree[ipt]->GetEntry(ientry);
        double etadijet = (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2.;
        if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue; 
        Nevents[ieta]++;
        if(tree[ipt]->jtpt1 > 30 && tree[ipt]->jtpt2 > 20){
          double ptave = (tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2.; 
          if((ptave > ptlow[ipt]) &&  (ptave < ptlow[ipt+1]))MeanGen[ieta][ipt]+=1.;
        }
        if(tree[ipt]->jtpt1sm > 30 && tree[ipt]->jtpt2sm > 20){
          double ptave = (tree[ipt]->jtpt1sm + tree[ipt]->jtpt2sm)/2.; 
          if((ptave > ptlow[ipt]) && (ptave < ptlow[ipt+1]))MeanSm[ieta][ipt]+=1.;
	  
	}
      }
    }
  }
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int ipt = 0; ipt < npt; ipt++){
      MeanSm[ieta][ipt]/=((double)Nevents[ieta]);
      MeanGen[ieta][ipt]/=((double)Nevents[ieta]);
    }
  }
  double SdGen[netabins][npt];
  double SdSm[netabins][npt];

  for(int ieta = 0; ieta < netabins; ieta++){
    for(int ipt = 0; ipt < npt; ipt++){
      SdGen[ieta][ipt] = 0.;
      SdSm[ieta][ipt] = 0.;
      for(int ientry = 0; ientry < nentries[ipt]; ientry++){
        tree[ipt]->GetEntry(ientry);
        double etadijet = (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2.;
        if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue; 
        if(tree[ipt]->jtpt1 > 30 && tree[ipt]->jtpt2 > 20){
          double ptave = (tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2.; 
          if((ptave > ptlow[ipt]) &&  (ptave < ptlow[ipt+1])) SdGen[ieta][ipt]+=pow(1.-MeanGen[ieta][ipt],2.);
	  else SdGen[ieta][ipt]+=pow(MeanGen[ieta][ipt],2.);
        }
        if(tree[ipt]->jtpt1sm > 30 && tree[ipt]->jtpt2sm > 20){
          double ptave = (tree[ipt]->jtpt1sm + tree[ipt]->jtpt2sm)/2.; 
          if((ptave > ptlow[ipt]) &&  (ptave < ptlow[ipt+1])) SdSm[ieta][ipt]+=pow(1.-MeanSm[ieta][ipt],2.);
   	  else SdSm[ieta][ipt]+= pow(MeanSm[ieta][ipt],2.);  
        }
      }
    }
  }
  
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int ipt = 0; ipt < npt; ipt++){
      SdSm[ieta][ipt]=sqrt(SdSm[ieta][ipt]/((double)Nevents[ieta]));
      SdGen[ieta][ipt]=sqrt(SdGen[ieta][ipt]/((double)Nevents[ieta]));
    }
  }

  double NXNY[netabins];
  for(int ieta = 0; ieta < netabins; ieta++){
    NXNY[ieta] = 0;
  }
  for(int ipt = 0; ipt < npt; ipt++){
    for(int ientry = 0; ientry < nentries[ipt]; ientry++){
      for(int ieta = 0; ieta < netabins; ieta++){
        tree[ipt]->GetEntry(ientry);
        if(tree[ipt]->jtpt1 < 30 || tree[ipt]->jtpt2 < 20) continue;
        if(tree[ipt]->jtpt1sm < 30 && tree[ipt]->jtpt2sm < 20) continue;
        if((tree[ipt]->jteta1 + tree[ipt]->jteta2)/2. < etabinspPb[ieta] || (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2. > etabinspPb[ieta+1]) continue;
        NXNY[ieta]++;
        histCorrPt[ieta]->Fill((tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2., (tree[ipt]->jtpt1sm + tree[ipt]->jtpt2sm)/2.);
      } 
    }
  }
  TH2D *histCorrPtCov[netabins];
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPtCov[ieta] = (TH2D*)histCorrPt[ieta]->Clone(Form("histCorrPtCov_%d",ieta));    
    for(int ipt = 0; ipt < npt; ipt++){
      for(int jpt = 0; jpt < npt; jpt++){
        //cout << ieta << " " << ipt << " " << jpt << endl;
        //int xBin = histCorrPt[ieta]->GetXaxis()->FindBin(0.5*(ptlow[ipt+1]+ptlow[ipt]));
        //int yBin = histCorrPt[ieta]->GetYaxis()->FindBin(0.5*(ptlow[jpt+1]-ptlow[jpt]));
        double EDouble = histCorrPt[ieta]->GetBinContent(ipt+1,jpt+1);
        if(ipt==jpt) cout << "ieta = " << ieta << " ipt = " << ipt << " EDouble = " << EDouble << " NXNY = " << Nevents[ieta] << " MuX = " << MeanGen[ieta][ipt] << " MuY = "<< MeanSm[ieta][ipt] << " sigmaX = " << SdGen[ieta][ipt] << " sigmaY = " << SdSm[ieta][ipt] << endl;
        histCorrPtCov[ieta]->SetBinContent(ipt+1, jpt+1, ((EDouble/Nevents[ieta])-MeanGen[ieta][ipt]*MeanSm[ieta][ipt])/(SdGen[ieta][ipt]*SdSm[ieta][ipt]));
	//        histCorrPtCov[ieta]->SetBinContent(ipt+1,jpt+1,(histCorrPt[ieta]->GetBinContent(ipt+1,jpt+1)/(ndijetGen[ipt]*ndijetSm[ipt])-histEtaGen[ipt]->GetBinContent(ieta+1)*histEtaSm[jpt]->GetBinContent(ieta+1))/(histEtaGenSd[ipt]->GetBinContent(ieta+1)*histEtaSmSd[ipt]->GetBinContent(ieta+1)));
      } 
    }
  }
  cout << 7 << endl; 
  TFile *outf = new TFile("out_pearson.root","recreate");
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPtCov[ieta]->Write();
    histCorrPt[ieta]->Write();
  }
  outf->Close();

  TCanvas *canvas[netabins];
  for(int ieta = 0; ieta < netabins; ieta++){
    canvas[ieta] = new TCanvas(Form("canvas_%d",ieta),"",600,600);
    histCorrPtCov[ieta]->Draw("colz");
    canvas[ieta]->SaveAs(Form("canvas_%d.pdf",ieta));
  }
}
