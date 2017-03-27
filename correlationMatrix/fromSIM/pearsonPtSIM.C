//#include "plotPDFDoubleRatio.C"
//#include "plotPDFDoubleRatio_v2.C"
//#include "plotPDF.C"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "ntdijet.C"
#include "ntgendijet.C"
#include "../data_driven_jec/dijeteta/utilities.h"

void pearsonPt(){
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2(true);
  int npt = 9;
  int nptMes = 6;
  TString infname[npt]; 
  int pthat[] = {15, 30, 50, 80, 120, 170, 220, 280, 370};
  double weight[] = {4.14330878039241224, 2.31130604917169220e-01, 2.20380344223347430e-02, 2.09726282221631667e-03, 2.29395079688884196e-04, 2.97532611808287438e-05, 5.76231321229158052e-06, 1.08115903172997635e-06, 1.20588432533271561e-07};
  for(int ipt = 0; ipt < npt; ipt++){
    infname[ipt] = Form("/mnt/hadoop/cms/store/user/dgulhan/ppDijet/Correlation2/R3_subAlgo_hltTree__HighPtLowerJets_HiForest_pPbDir_QCD%d_pythia6_HiWinter13.root",pthat[ipt]);
  }
  ntdijet* recoTree[npt];
  //  ntgendijet* genTree[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    recoTree[ipt] = new ntdijet(infname[ipt].Data());
    //genTree[ipt] = new ntgendijet(infname[ipt].Data());
  }
  //  cout << 3 << endl;
  int netabins = 18;
  double etabinspPb[19]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};
  
  double ptlow[]= {25,55,75,95,115,150,400};
  TH2D *histCorr[nptMes];
  int nentriesReco[npt];
  
  for(int iptMes = 0; iptMes < nptMes; iptMes++){
    histCorr[iptMes] = new TH2D(Form("histCorr_%d",iptMes),"",netabins,etabinspPb,netabins,etabinspPb); 
  }
  for(int ipt = 0; ipt < npt; ipt++){
    nentriesReco[ipt] = recoTree[ipt]->GetEntries();
    // nentriesGen[ipt] = genTree[ipt]->GetEntries();
    //cout <<"nentriesGen" << genTree[ipt]->GetEntries()<< endl;
    //nentriesReco[ipt] = recoTree[ipt]->GetEntries();
    //nentriesReco[ipt] = 1000;
   }
  TH2D *histCorrPt[netabins];
  
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPt[ieta] = new TH2D(Form("histCorrPt%d",ieta),"",nptMes,ptlow,nptMes,ptlow);
  }

  cout << 2 << endl;

  double NeventsGen[netabins];
  double NeventsSm[netabins];
  double MeanGen[netabins][nptMes];
  double MeanSm[netabins][nptMes];
  for(int ieta = 0; ieta < netabins; ieta++){
      NeventsGen[ieta] = 0;
      NeventsSm[ieta] = 0;
      for(int iptMes = 0; iptMes < nptMes; iptMes++){
        MeanGen[ieta][iptMes] = 0.;
        MeanSm[ieta][iptMes] = 0.;
        for(int ipt = 0; ipt < npt; ipt++){
        cout << "iptMes=" << iptMes << " ieta=" << ieta << " ipt=" << ipt<<endl;
          for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){    
	    recoTree[ipt]->GetEntry(ientry);
	    //            if(ientry%10000==0) cout << "reco" << ientry<<endl;
  	    if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
  	    if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
            if((recoTree[ipt]->genpt1 +  recoTree[ipt]->genpt2)/2. > 400) continue;
            if((recoTree[ipt]->jtpt1 +  recoTree[ipt]->jtpt2)/2. > 400) continue;
	    double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.; 
            double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
	    if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue;  
            if(etadijetsm < etabinspPb[ieta] || etadijetsm > etabinspPb[ieta+1]) continue;	 
            if(iptMes==0) NeventsSm[ieta]+=weight[ipt];
            double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
            //double ptaveGen = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
            //if((ptaveGen < ptlow[0]) && (ptaveGen > ptlow[npt])) continue;
    	    if((ptaveSm > ptlow[iptMes]) &&  (ptaveSm < ptlow[iptMes+1])) MeanSm[ieta][iptMes]+=weight[ipt];
	  }
          for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){
            //if(ientry%10000==0) cout << ientry << endl;
            recoTree[ipt]->GetEntry(ientry);
	    //            cout << recoTree[ipt]->genpt1 << " " << recoTree[ipt]->genpt2 << endl;
            if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
            if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
            if((recoTree[ipt]->genpt1 +  recoTree[ipt]->genpt2)/2. > 400) continue;
            if((recoTree[ipt]->jtpt1 +  recoTree[ipt]->jtpt2)/2. > 400) continue;
            double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
  	    double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.;
            if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue;  
            if(etadijetsm < etabinspPb[ieta] || etadijetsm > etabinspPb[ieta+1]) continue;  
            if(iptMes==0) NeventsGen[ieta]+=weight[ipt];
            //double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
            double ptaveGen = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
            //if((ptaveSm < ptlow[0]) && (ptaveSm > ptlow[npt])) continue;
    	    if((ptaveGen > ptlow[iptMes]) &&  (ptaveGen < ptlow[iptMes+1])) MeanGen[ieta][iptMes]+=weight[ipt];
    	   }
        }	  
     }
  }

  cout << 1 << endl;
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      //cout << "NeventsGen = " << NeventsGen[iptMes] << endl;
      MeanSm[ieta][iptMes]/=((double)NeventsSm[ieta]);
      MeanGen[ieta][iptMes]/=((double)NeventsGen[ieta]);
    }
  }
  cout << 2 << endl;
  double SdGen[netabins][nptMes];
  double SdSm[netabins][nptMes];

  for(int iptMes = 0; iptMes < nptMes; iptMes++){
    for(int ieta = 0; ieta < netabins; ieta++){
      SdGen[ieta][iptMes] = 0.;
      SdSm[ieta][iptMes] = 0.;
      for(int ipt = 0; ipt < npt; ipt++){
        for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){
          recoTree[ipt]->GetEntry(ientry);
          if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
          if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
          if((recoTree[ipt]->genpt1 +  recoTree[ipt]->genpt2)/2. > 400) continue;
          if((recoTree[ipt]->jtpt1 +  recoTree[ipt]->jtpt2)/2. > 400) continue;
	  double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.;
          double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.;
          if(etadijetsm < etabinspPb[ieta] || etadijetsm > etabinspPb[ieta+1]) continue; 
  	  if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue; 
  	  double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
          //double ptaveGen = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
          //if((ptaveGen < ptlow[0]) && (ptaveGen > ptlow[npt])) continue;
	  if((ptaveSm > ptlow[iptMes]) &&  (ptaveSm < ptlow[iptMes+1])) SdSm[ieta][iptMes]+=weight[ipt]*pow(1-MeanSm[ieta][iptMes],2.);
	  else SdSm[ieta][iptMes]+=weight[ipt]*pow(MeanSm[ieta][iptMes],2.); 
        }
        for(int jentry = 0; jentry < nentriesReco[ipt]; jentry++) {
          recoTree[ipt]->GetEntry(jentry);
	  if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
	  if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
          if((recoTree[ipt]->genpt1 +  recoTree[ipt]->genpt2)/2. > 400) continue;
          if((recoTree[ipt]->jtpt1 +  recoTree[ipt]->jtpt2)/2. > 400) continue;
	  double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.;
          double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
	  if(etadijet < etabinspPb[ieta] || etadijet > etabinspPb[ieta+1]) continue; 	     
	  if(etadijetsm < etabinspPb[ieta] || etadijetsm > etabinspPb[ieta+1]) continue; 
          //double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
          double ptaveGen = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;	     
          //if((ptaveSm < ptlow[0]) && (ptaveSm > ptlow[npt])) continue;
	  if((ptaveGen > ptlow[iptMes]) &&  (ptaveGen < ptlow[iptMes+1])) SdGen[ieta][iptMes]+=weight[ipt]*pow(1-MeanGen[ieta][iptMes],2.);
  	  else  SdGen[ieta][iptMes]+=weight[ipt]*pow(MeanGen[ieta][iptMes],2.); 	     
        }
      }
    }
  }
  cout << 3 << endl;
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      SdSm[ieta][iptMes]=sqrt(SdSm[ieta][iptMes]/((double)NeventsSm[ieta]));
      SdGen[ieta][iptMes]=sqrt(SdGen[ieta][iptMes]/((double)NeventsGen[ieta]));
    }
  }
  cout << 4 << endl;
  double NeventsMult[netabins];
  for(int ieta = 0; ieta < netabins; ieta++){
    NeventsMult[ieta] = 0;
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      for(int ipt = 0; ipt < npt; ipt++){
        cout << "iptMes=" << iptMes << " ieta=" << ieta << " ipt=" << ipt<<endl;

        for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){
          recoTree[ipt]->GetEntry(ientry);
          bool passed = false;
            
          if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
          if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
          if((recoTree[ipt]->genpt1 +  recoTree[ipt]->genpt2)/2. > 400) continue;
          if((recoTree[ipt]->jtpt1 +  recoTree[ipt]->jtpt2)/2. > 400) continue;
          
          double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.; 
          double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
   
   	  if((etadijetsm < etabinspPb[ieta]) ||  (etadijetsm > etabinspPb[ieta+1])) continue;
     	  if((etadijet < etabinspPb[ieta]) ||  (etadijet > etabinspPb[ieta+1])) continue;
          NeventsMult[ieta] += weight[ipt];
           
          double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
          double ptave = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
          histCorrPt[ieta]->Fill(ptave,ptaveSm,weight[ipt]);
           
        }
      } 
    }
    histCorrPt[ieta]->Scale(1./((float)nptMes));
    NeventsMult[ieta]/=((float)nptMes);
  }

  cout << 5 << endl;
  TH2D *histCorrPtCov[netabins];
  double sumEDouble[netabins];
  double sumMeanGen[netabins];
  double sumMeanSm[netabins];
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPtCov[ieta] = (TH2D*)histCorrPt[ieta]->Clone(Form("histCorrPtCov_%d",ieta));    
    sumEDouble[ieta] = 0;
    sumMeanGen[ieta] = 0;
    sumMeanSm[ieta] = 0;
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      for(int jptMes = 0; jptMes < nptMes; jptMes++){
        double EDouble = histCorrPt[ieta]->GetBinContent(iptMes+1,jptMes+1);  
        cout << "EDouble = " << EDouble << endl;
        histCorrPtCov[ieta]->SetBinContent(iptMes+1, jptMes+1, ((EDouble/NeventsMult[ieta])-MeanGen[ieta][iptMes]*MeanSm[ieta][jptMes])/(SdGen[ieta][iptMes]*SdSm[ieta][jptMes])); 
        if(iptMes==jptMes)cout << ((EDouble/NeventsMult[ieta])-MeanGen[ieta][iptMes]*MeanSm[ieta][jptMes])/(SdGen[ieta][iptMes]*SdSm[ieta][jptMes]) << endl;
        sumEDouble[ieta]+=EDouble;
       } 
      sumMeanGen[ieta]+=MeanGen[ieta][iptMes];
      sumMeanSm[ieta]+=MeanSm[ieta][iptMes];
    }
    cout << "ieta sum = " << sumEDouble[ieta] << " neventsMult" << NeventsMult[ieta] << " neventsGen" << NeventsGen[ieta]<< " neventSM" << NeventsSm[ieta]<<" sum mean gen =" << sumMeanGen[ieta] << "sum mean sm = " << sumMeanSm[ieta] << endl; 
  } 
  cout << 7 << endl; 
  TFile *outf = new TFile("out_pearson_etafix_pterr_small.root","recreate");
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPtCov[ieta]->Write();
    histCorrPt[ieta]->Write();
  }
  outf->Close();
}
