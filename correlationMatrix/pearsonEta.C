//#include "plotPDFDoubleRatio.C"
//#include "plotPDFDoubleRatio_v2.C"
//#include "plotPDF.C"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "ntdijet_smeared0.C"
#include "../plot/utilities.h"

void pearson(){
  //  ntdijet[ipt]->Draw(Form("-(jteta1sm*(1-2*(%.3f)*abs((jteta1sm+0.465)/3.))+jteta2sm*(1-2*(%.3f)*abs((jteta2sm+0.465)/3.)))/2.>>histEtaOffset%d",(6-((float)ipt))*2/1000.,(6-((float)ipt))*2/1000., ipt),Form("(jtpt1 > 30 && jtpt2 > 20 && acos(cos(jtphi1-jtphi2)) > (2*TMath::Pi()/3.) && (jtpt1+jtpt2)/2. >= %d && (jtpt1+jtpt2)/2.<%d)",ptlow[ipt],ptlow[ipt+1]));


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

  int Nevents[npt];
  double MeanGen[netabins][npt];
  double MeanSm[netabins][npt];
  for(int ipt = 0; ipt < npt; ipt++){
    Nevents[ipt] = 0;
    for(int ieta = 0; ieta < netabins; ieta++){
      MeanGen[ieta][ipt] = 0.;
      MeanSm[ieta][ipt] = 0.;
      for(int ientry = 0; ientry < nentries[ipt]; ientry++){
        tree[ipt]->GetEntry(ientry);
        double ptave = (tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2.;
	if(tree[ipt]->jtpt1 < 30 || tree[ipt]->jtpt2 < 20) continue;
	if((ptave < ptlow[ipt]) ||  (ptave > ptlow[ipt+1])) continue;
	if(ieta==0) Nevents[ipt]++;
        double etadijet = (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2.; 
        double etadijetsm = (tree[ipt]->jteta1sm + tree[ipt]->jteta2sm)/2.; 
	if(etadijet > etabinspPb[ieta] && etadijet < etabinspPb[ieta+1]) MeanGen[ieta][ipt]++; 
	if(etadijetsm > etabinspPb[ieta] && etadijetsm < etabinspPb[ieta+1]) MeanSm[ieta][ipt]++; 	 
      }	  
    }
  }
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int ipt = 0; ipt < npt; ipt++){
      MeanSm[ieta][ipt]/=((double)Nevents[ipt]);
      MeanGen[ieta][ipt]/=((double)Nevents[ipt]);
    }
  }
  
  double SdGen[netabins][npt];
  double SdSm[netabins][npt];

  for(int ipt = 0; ipt < npt; ipt++){
    for(int ieta = 0; ieta < netabins; ieta++){
      SdGen[ieta][ipt] = 0.;
      SdSm[ieta][ipt] = 0.;
      for(int ientry = 0; ientry < nentries[ipt]; ientry++){
        tree[ipt]->GetEntry(ientry);

        double ptave = (tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2.;
	if(tree[ipt]->jtpt1 < 30 || tree[ipt]->jtpt2 < 20) continue;
	if((ptave < ptlow[ipt]) ||  (ptave > ptlow[ipt+1])) continue;
	//Nevents[ipt]++;
        double etadijet = (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2.; 
        double etadijetsm = (tree[ipt]->jteta1sm + tree[ipt]->jteta2sm)/2.; 
	if(etadijet > etabinspPb[ieta] && etadijet < etabinspPb[ieta+1]) SdGen[ieta][ipt]+=pow(1-MeanGen[ieta][ipt],2.); 
	else SdGen[ieta][ipt]+=pow(MeanGen[ieta][ipt],2.); 
	if(etadijetsm > etabinspPb[ieta] && etadijetsm < etabinspPb[ieta+1])  SdSm[ieta][ipt]+=pow(1-MeanSm[ieta][ipt],2.); 	     
	else  SdSm[ieta][ipt]+=pow(MeanSm[ieta][ipt],2.); 	     
      }
    }
  }
  
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int ipt = 0; ipt < npt; ipt++){
      SdSm[ieta][ipt]=sqrt(SdSm[ieta][ipt]/((double)Nevents[ipt]));
      SdGen[ieta][ipt]=sqrt(SdGen[ieta][ipt]/((double)Nevents[ipt]));
    }
  }

  for(int ipt = 0; ipt < npt; ipt++){
    for(int ientry = 0; ientry < nentries[ipt]; ientry++){
      for(int ieta = 0; ieta < netabins; ieta++){
        tree[ipt]->GetEntry(ientry);
        if(tree[ipt]->jtpt1 < 30 || tree[ipt]->jtpt2 < 20) continue;
        if(tree[ipt]->jtpt1sm < 30 && tree[ipt]->jtpt2sm < 20) continue;

        double ptave = (tree[ipt]->jtpt1 + tree[ipt]->jtpt2)/2.;
	if((ptave < ptlow[ipt]) ||  (ptave > ptlow[ipt+1])) continue;
        double etadijet = (tree[ipt]->jteta1 + tree[ipt]->jteta2)/2.; 
        double etadijetsm = (tree[ipt]->jteta1sm + tree[ipt]->jteta2sm)/2.; 
        histCorr[ipt]->Fill(etadijet,etadijetsm);
      } 
    }
    histCorr[ipt]->Scale(1./netabins);
  }
  TH2D *histCorrCov[npt];
  double sumEDouble[npt];
  double sumMeanGen[npt];
  double sumMeanSm[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    histCorrCov[ipt] = (TH2D*)histCorr[ipt]->Clone(Form("histCorrCov_%d",ipt));    
    sumEDouble[ipt] = 0;
    sumMeanGen[ipt] = 0;
    sumMeanSm[ipt] = 0;
    for(int ieta = 0; ieta < netabins; ieta++){
      for(int jeta = 0; jeta < netabins; jeta++){
        //cout << ieta << " " << ipt << " " << jpt << endl;
        //int xBin = histCorrPt[ieta]->GetXaxis()->FindBin(0.5*(ptlow[ipt+1]+ptlow[ipt]));
        //int yBin = histCorrPt[ieta]->GetYaxis()->FindBin(0.5*(ptlow[jpt+1]-ptlow[jpt]));
        double EDouble = histCorr[ipt]->GetBinContent(ieta+1,jeta+1);
        if(ieta==jeta) cout << "ieta = " << ieta << " ipt = " << ipt << " EDouble = " << EDouble << " NXNY = " << Nevents[ipt] << " MuX = " << MeanGen[ieta][ipt] << " MuY = "<< MeanSm[jeta][ipt] << " sigmaX = " << SdGen[ieta][ipt] << " sigmaY = " << SdSm[jeta][ipt] << endl;
        histCorrCov[ipt]->SetBinContent(ieta+1, jeta+1, ((EDouble/Nevents[ipt])-MeanGen[ieta][ipt]*MeanSm[jeta][ipt])/(SdGen[ieta][ipt]*SdSm[jeta][ipt]));
        sumEDouble[ipt]+=EDouble;
	//        histCorrPtCov[ieta]->SetBinContent(ipt+1,jpt+1,(histCorrPt[ieta]->GetBinContent(ipt+1,jpt+1)/(ndijetGen[ipt]*ndijetSm[ipt])-histEtaGen[ipt]->GetBinContent(ieta+1)*histEtaSm[jpt]->GetBinContent(ieta+1))/(histEtaGenSd[ipt]->GetBinContent(ieta+1)*histEtaSmSd[ipt]->GetBinContent(ieta+1)));
      } 
      sumMeanGen[ipt]+=MeanGen[ieta][ipt];
      sumMeanSm[ipt]+=MeanSm[ieta][ipt];
    }
    cout << "ipt sum = " << sumEDouble[ipt] << " nevents" << Nevents[ipt]<< " sum mean gen =" << sumMeanGen[ipt] << "sum mean sm = " << sumMeanSm[ipt] << endl; 
  } 
  cout << 7 << endl; 
  TFile *outf = new TFile("out_pearson_eta.root","recreate");
  for(int ipt = 0; ipt < npt; ipt++){
    histCorrCov[ipt]->Write();
    histCorr[ipt]->Write();
  }
  outf->Close();

  TCanvas *canvas[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    canvas[ipt] = new TCanvas(Form("canvas_%d",ipt),"",600,600);
    histCorrCov[ipt]->Draw("colz");
    canvas[ipt]->SaveAs(Form("canvas_%d.pdf",ipt));
  }
}
