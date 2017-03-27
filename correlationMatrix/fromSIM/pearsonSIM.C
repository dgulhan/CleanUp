//#include "plotPDFDoubleRatio.C"
//#include "plotPDFDoubleRatio_v2.C"
//#include "plotPDF.C"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "ntdijet.C"
//#include "ntgendijet.C"
#include "../data_driven_jec/dijeteta/utilities.h"

void pearson(){
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2(true);
  int npt = 5;
  int nptMes = 6;
  TString infname[npt]; 
  int pthat[] = {15, 30, 50, 80, 120, 170, 220, 280, 370};
  double weight[] = {4.14330878039241224, 2.31130604917169220e-01, 2.20380344223347430e-02, 2.09726282221631667e-03, 2.29395079688884196e-04, 2.97532611808287438e-05, 5.76231321229158052e-06, 1.08115903172997635e-06, 1.20588432533271561e-07};
  for(int ipt = 0; ipt < npt; ipt++){
    infname[ipt] = Form("/mnt/hadoop/cms/store/user/dgulhan/ppDijet/Correlation2/R3_subAlgo_hltTree__HighPtLowerJets_HiForest_pPbDir_QCD%d_pythia6_HiWinter13.root",pthat[ipt]);
  }
  ntdijet* recoTree[npt];
  //ntgendijet* genTree[npt];
  for(int ipt = 0; ipt < npt; ipt++){
    recoTree[ipt] = new ntdijet(infname[ipt].Data());
    //    genTree[ipt] = new ntgendijet(infname[ipt].Data());
  }
  //  cout << 3 << endl;
  int netabins = 18;
  double etabinspPb[19]={-2.915,-2.63333333333,-2.07,-1.78833333333,-1.50666666667,-1.225,-0.94333333333,-0.66166666666,-0.38,-0.09833333333,0.18333333333,0.465,0.74666666666,1.02833333333,1.31,1.59166666667,1.87333333333,2.43666666667,3};
  
  double ptlow[]= {25,55,75,95,115,150,400};
  TH2D *histCorr[nptMes];
  int nentriesReco[npt];
  int nentriesGen[npt];
  int nentries[npt];

  for(int iptMes = 0; iptMes < nptMes; iptMes++){
    histCorr[iptMes] = new TH2D(Form("histCorr_%d",iptMes),"",netabins,etabinspPb,netabins,etabinspPb); 
  }
  for(int ipt = 0; ipt < npt; ipt++){
    nentriesReco[ipt] = recoTree[ipt]->GetEntries();
    //nentriesGen[ipt] = genTree[ipt]->GetEntries();
    //  cout <<"nentriesGen" << genTree[ipt]->GetEntries()<< endl;
    //nentries[ipt] = recoTree[ipt]->GetEntries();
    //nentriesReco[ipt] = 100;
    //nentriesGen[ipt] = 1;
    //nentries[ipt] = 1;
  }
  TH2D *histCorrPt[netabins];
  
  for(int ieta = 0; ieta < netabins; ieta++){
    histCorrPt[ieta] = new TH2D(Form("histCorrPt%d",ieta),"",nptMes,ptlow,nptMes,ptlow);
  }

  cout << 2 << endl;

  double NeventsGen[nptMes];
  double NeventsSm[nptMes];
  double MeanGen[netabins][nptMes];
  double MeanSm[netabins][nptMes];
  for(int iptMes = 0; iptMes < nptMes; iptMes++){
      NeventsGen[iptMes] = 0;
      NeventsSm[iptMes] = 0;
      for(int ieta = 0; ieta < netabins; ieta++){
        MeanGen[ieta][iptMes] = 0.;
        MeanSm[ieta][iptMes] = 0.;
        for(int ipt = 0; ipt < npt; ipt++){
        cout << "iptMes=" << iptMes << " ieta=" << ieta << " ipt=" << ipt<<endl;
          for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){    
	    recoTree[ipt]->GetEntry(ientry);
	    //            if(ientry%10000==0) cout << "reco" << ientry<<endl;
	    if(recoTree[ipt]->refpt1 < 30 || recoTree[ipt]->refpt2 < 20) continue;
            double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
    	    if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
  	    if((ptaveSm < ptlow[iptMes]) ||  (ptaveSm > ptlow[iptMes+1])) continue;
	    if(ieta==0) NeventsSm[iptMes]+=weight[ipt];
            double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.; 
            if(etadijetsm > etabinspPb[ieta] && etadijetsm < etabinspPb[ieta+1]) MeanSm[ieta][iptMes]+=weight[ipt];	 
          }
	  //          cout << nentriesGen[ipt] << endl;
          for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){
            //if(ientry%10000==0) cout << ientry << endl;
            recoTree[ipt]->GetEntry(ientry);
            //cout << genTree[ipt]->genpt1 << " " << genTree[ipt]->genpt2 << endl;
            if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
            double ptaveGen = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
    	    if((ptaveGen < ptlow[iptMes]) ||  (ptaveGen > ptlow[iptMes+1])) continue;
	    if(ieta==0) NeventsGen[iptMes]+=weight[ipt];
            double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
  	    if(etadijet > etabinspPb[ieta] && etadijet < etabinspPb[ieta+1]) MeanGen[ieta][iptMes]+=weight[ipt];  
          }
        }	  
     }
  }

  cout << 1 << endl;
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      //cout << "NeventsGen = " << NeventsGen[iptMes] << endl;
      MeanSm[ieta][iptMes]/=((double)NeventsSm[iptMes]);
      MeanGen[ieta][iptMes]/=((double)NeventsGen[iptMes]);
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
          double ptave = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
	  if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
	  if((ptave < ptlow[iptMes]) ||  (ptave > ptlow[iptMes+1])) continue;
	  //Nevents[ipt]++;
          double etadijet = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.;
          if(etadijet > etabinspPb[ieta] && etadijet < etabinspPb[ieta+1]) SdSm[ieta][iptMes]+=weight[ipt]*pow(1-MeanSm[ieta][iptMes],2.); 
  	  else SdSm[ieta][iptMes]+=weight[ipt]*pow(MeanSm[ieta][iptMes],2.); 
        }
        for(int jentry = 0; jentry < nentriesReco[ipt]; jentry++) {
          recoTree[ipt]->GetEntry(jentry);
          double ptave = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;
	  if(recoTree[ipt]->genpt1 < 30 || recoTree[ipt]->genpt2 < 20) continue;
	  if((ptave < ptlow[iptMes]) ||  (ptave > ptlow[iptMes+1])) continue;
	  double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
	  if(etadijet > etabinspPb[ieta] && etadijet < etabinspPb[ieta+1])  SdGen[ieta][iptMes]+=weight[ipt]*pow(1-MeanGen[ieta][iptMes],2.); 	     
  	  else  SdGen[ieta][iptMes]+=weight[ipt]*pow(MeanGen[ieta][iptMes],2.); 	     
        }
      }
    }
  }
  cout << 3 << endl;
  for(int ieta = 0; ieta < netabins; ieta++){
    for(int iptMes = 0; iptMes < nptMes; iptMes++){
      SdSm[ieta][iptMes]=sqrt(SdSm[ieta][iptMes]/((double)NeventsSm[iptMes]));
      SdGen[ieta][iptMes]=sqrt(SdGen[ieta][iptMes]/((double)NeventsGen[iptMes]));
    }
  }
  cout << 4 << endl;
  double NeventsMult[nptMes];
  for(int iptMes = 0; iptMes < nptMes; iptMes++){
    NeventsMult[iptMes] = 0;
    for(int ieta = 0; ieta < netabins; ieta++){
      for(int ipt = 0; ipt < npt; ipt++){
        cout << "iptMes=" << iptMes << " ieta=" << ieta << " ipt=" << ipt<<endl;

        for(int ientry = 0; ientry < nentriesReco[ipt]; ientry++){
          recoTree[ipt]->GetEntry(ientry);
          bool passed = false;
          //for(int jentry = 0; jentry < nentriesGen[ipt]; jentry++){
	  //genTree[ipt]->GetEntry(jentry);
            //cout << ientry << " " << jentry << endl;
            //cout << "evt=" << genTree[ipt]->evt << " " <<  recoTree[ipt]->evt << " run=" << genTree[ipt]->run << " "<< recoTree[ipt]->run  << " lumi"  << genTree[ipt]->lumi << " "<< recoTree[ipt]->lumi << endl;
            //if(!(genTree[ipt]->evt == recoTree[ipt]->evt && genTree[ipt]->run == recoTree[ipt]->run && genTree[ipt]->lumi == recoTree[ipt]->lumi)) continue;
            //else passed = true; 
            //cout << "passed" << passed << endl;
            if(recoTree[ipt]->jtpt1 < 30 || recoTree[ipt]->jtpt2 < 20) continue;
            if(recoTree[ipt]->genpt1 < 30 && recoTree[ipt]->genpt2 < 20) continue;

            double ptaveSm = (recoTree[ipt]->jtpt1 + recoTree[ipt]->jtpt2)/2.;
            double ptave = (recoTree[ipt]->genpt1 + recoTree[ipt]->genpt2)/2.;

     	    if((ptaveSm < ptlow[iptMes]) ||  (ptaveSm > ptlow[iptMes+1])) continue;
     	    if((ptave < ptlow[iptMes]) ||  (ptave > ptlow[iptMes+1])) continue;
            NeventsMult[iptMes] += weight[ipt];
            double etadijetsm = -(recoTree[ipt]->refeta1 + recoTree[ipt]->refeta2)/2.; 
            double etadijet = -(recoTree[ipt]->geneta1 + recoTree[ipt]->geneta2)/2.; 
            histCorr[iptMes]->Fill(etadijet,etadijetsm,weight[ipt]);
            //if(passed) break;
            //if(jentry>ientry+1000) break;
	    //}
        }
      } 
    }
    histCorr[iptMes]->Scale(1./netabins);
  }
  cout << 5 << endl;
  TH2D *histCorrCov[nptMes];
  double sumEDouble[nptMes];
  double sumMeanGen[nptMes];
  double sumMeanSm[nptMes];
  for(int iptMes = 0; iptMes < nptMes; iptMes++){
    histCorrCov[iptMes] = (TH2D*)histCorr[iptMes]->Clone(Form("histCorrCov_%d",iptMes));    
    sumEDouble[iptMes] = 0;
    sumMeanGen[iptMes] = 0;
    sumMeanSm[iptMes] = 0;
    for(int ieta = 0; ieta < netabins; ieta++){
      for(int jeta = 0; jeta < netabins; jeta++){
        //cout << ieta << " " << ipt << " " << jpt << endl;
        //int xBin = histCorrPt[ieta]->GetXaxis()->FindBin(0.5*(ptlow[ipt+1]+ptlow[ipt]));
        //int yBin = histCorrPt[ieta]->GetYaxis()->FindBin(0.5*(ptlow[jpt+1]-ptlow[jpt]));
        double EDouble = histCorr[iptMes]->GetBinContent(ieta+1,jeta+1);
        if(ieta==jeta) cout << "ieta = " << ieta << " ipt = " << iptMes << " EDouble = " << EDouble << " NXNY = " << NeventsGen[iptMes] << " Nevents SM" << NeventsSm[iptMes] << " MuX = " << MeanGen[ieta][iptMes] << " MuY = "<< MeanSm[jeta][iptMes] << " sigmaX = " << SdGen[ieta][iptMes] << " sigmaY = " << SdSm[jeta][iptMes] << endl;
        histCorrCov[iptMes]->SetBinContent(ieta+1, jeta+1, ((EDouble/NeventsGen[iptMes])-MeanGen[ieta][iptMes]*MeanSm[jeta][iptMes])/(SdGen[ieta][iptMes]*SdSm[jeta][iptMes]));
        sumEDouble[iptMes]+=EDouble;
	//        histCorrPtCov[ieta]->SetBinContent(ipt+1,jpt+1,(histCorrPt[ieta]->GetBinContent(ipt+1,jpt+1)/(ndijetGen[ipt]*ndijetSm[ipt])-histEtaGen[ipt]->GetBinContent(ieta+1)*histEtaSm[jpt]->GetBinContent(ieta+1))/(histEtaGenSd[ipt]->GetBinContent(ieta+1)*histEtaSmSd[ipt]->GetBinContent(ieta+1)));
      } 
      sumMeanGen[iptMes]+=MeanGen[ieta][iptMes];
      sumMeanSm[iptMes]+=MeanSm[ieta][iptMes];
    }
    cout << "ipt sum = " << sumEDouble[iptMes] << " nevents" << NeventsMult[iptMes]<< " "<< NeventsGen[iptMes] << " sum mean gen =" << sumMeanGen[iptMes] << "sum mean sm = " << sumMeanSm[iptMes] << endl; 
  } 
  cout << 7 << endl; 
  TFile *outf = new TFile("out_pearson_pt_small.root","recreate");
  for(int ipt = 0; ipt < nptMes; ipt++){
    histCorrCov[ipt]->Write();
    histCorr[ipt]->Write();
  }
  outf->Close();

  TCanvas *canvas[npt];
  for(int ipt = 0; ipt < nptMes; ipt++){
    canvas[ipt] = new TCanvas(Form("canvas_%d",ipt),"",600,600);
    histCorrCov[ipt]->Draw("colz");
    canvas[ipt]->SaveAs(Form("canvas_%d.pdf",ipt));
  }
}
