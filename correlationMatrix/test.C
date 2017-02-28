#include "generateToyAccPYTHIA.C"

void test(){
 TH1D::SetDefaultSumw2();
 EtaSmearing *etaSmear = new EtaSmearing("pPb");
 TH2D * histeta = new TH2D("histeta","",20,-3,3,50,-0.5,0.5);
 TRandom3* rand = new TRandom3();
 TH1D * hist = new TH1D("hist","",20,-2,2);
 for(int ibin = 0; ibin < 20; ibin++){
 float bin = histeta->GetBinCenter(ibin+1);
 for(int ijet = 0; ijet < 100; ijet++){
   // float jteta1sm = etaSmear->SmearedEta(0, 50, random);
   float jteta1sm = etaSmear->SmearedEta(0, 50, bin);
   cout << random << " "<<jteta1sm << endl;
   histeta->Fill(bin,jteta1sm-bin);
  }
  }
  TCanvas * c1 = new TCanvas("c1","",600,600);
  histeta->Draw("colz");
  c1->SaveAs("test.png");
}