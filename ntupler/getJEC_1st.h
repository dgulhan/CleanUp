#include <cmath>
#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"

using namespace std;
class MCTruthResidual
{
 private:
  TH1D * hist;
  TF1 *fitUnf[4][60];
  TF1 *fitVsPt[4][60];
  TF1 *fitVsEta[5];
  TString fmode;
  TFile *fileUnf[3];
  TFile *fileResMC[3];
  TF1 * fitSmear[2];
  TF1 * fitResidualPt;
  TF1 * fitGaus;
  int nstep;
 public:
 MCTruthResidual(TString mode): fmode(mode){
  int nEta=32;
  float etabins[]= {-4,-3.465,-2.999, -2.500, -2.172,
		    -1.930, -1.740,-1.566,-1.392,
		    -1.218, -1.044, -0.879, -0.696,
		    -0.522,-0.348,-0.174, 0,
		    0.174,    0.348,    0.522,
                    0.696,   0.879,   1.044,   1.218,
		    1.392,   1.566,  1.740,
                    1.930,   2.172,   2.500,
		    2.999,3.465,4};//add -4 and 4
 
  float etabinspPb[]= {-3., -2.500, -2.172,
		    -1.930, -1.740,-1.566,-1.392,
		    -1.218, -1.044, -0.879, -0.696,
		    -0.522,-0.348,-0.174, 0,
		    0.174,    0.348,    0.522,
                    0.696,   0.879,   1.044,   1.218,
		    1.392,   1.566,  1.740,
                    1.930,   2.172,   2.500,
		    3.};//add -4 and 4
 
  if(fmode=="pPb5" || fmode=="Pbp5"){
    nEta = 28; 
    for(int iEta = 0; iEta < nEta+1; iEta++){
       etabins[iEta] = etabinspPb[iEta];
    }
  }
  hist = new TH1D("hist","",nEta,etabins);
  nstep = 1;

  if(fmode=="pPb5"){
   nstep = 2;
   fileUnf[0] = new TFile("residualMCTruth/hists_pPb.root");
   fitUnf[0][0] = (TF1*)fileUnf[0]->Get("fit_jtpt_dep0");

   for(int istep = 0; istep < nstep; istep++){ 

    
     fileResMC[istep] = new TFile(Form("residualMCTruth/responseInEtaBinspPb_yueshiL2L3_20170122_step%d.root",istep));
     
    for(int ieta = 0; ieta < nEta; ieta++){
     fitVsPt[istep][ieta] = (TF1*)fileResMC[istep]->Get(Form("fit2%d",ieta));
    } 
   }
   fitVsEta[0] = new TF1("fitvseta0","(-8.66933e-04)*x*x*x+(-3.43026e-03)*x*x+1.00985e+00",-3,3);
   fitVsEta[1] = new TF1("fitvseta1","( 7.47059e-04)*x*x*x+(3.25265e-03)*x*x+9.93123e-01",-3,3);
   fitVsEta[2] = new TF1("fitvseta2","(-3.48461e-04)*x*x*x+(1.73609e-03)*x*x+1.00252e+00",-3,3);
   fitVsEta[3] = new TF1("fitvseta3","(-3.57022e-04)*x*x*x+(1.35455e-03)*x*x+1.00280e+00",-3,3);
   fitVsEta[4] = new TF1("fitvseta4","(-2.49294e-04)*x*x*x+(1.39031e-03)*x*x+1.00320e+00",-3,3);
   fitResidualPt = new TF1("fitResidualPt","(-7.46377e-01)/x+1.00276e+00");
  }
  else if(fmode=="Pbp5"){
   nstep = 1;
   fileUnf[0] = new TFile("residualMCTruth/hists_Pbp.root");
   fitUnf[0][0] = (TF1*)fileUnf[0]->Get("fit_jtpt_dep0");
   for(int istep = 0; istep < nstep; istep++){
    fileResMC[istep] = new TFile(Form("residualMCTruth/responseInEtaBinsPbp_yueshiL2L3_20170128_step%d.root",istep));
    for(int ieta = 0; ieta < nEta; ieta++){
     fitVsPt[istep][ieta] = (TF1*)fileResMC[istep]->Get(Form("fit2%d",ieta));
    }
   }
   fitVsEta[0] = new TF1("fitvseta0","(-7.98069e-04)*x*x*x+(-1.28720e-03)*x*x+(2.92503e-03)*x+(1.00243e+00 )");
   fitVsEta[1] = new TF1("fitvseta1","(-2.30576e-04)*x*x*x+(5.03643e-03)*x*x+(2.30545e-03)*x+(9.87635e-01)");
   fitVsEta[2] = new TF1("fitvseta2","(2.52492e-04)*x*x*x+(-7.56608e-04)*x*x+(-1.37451e-03)*x+(1.00309e+00)");
   fitVsEta[3] = new TF1("fitvseta3","(-1.05427e-03)*x*x*x+(3.46250e-04)*x*x+(5.30411e-04)*x+(9.99666e-01)");
   fitVsEta[4] = new TF1("fitvseta4","(-3.12681e-04)*x*x*x+(8.44498e-05)*x*x+(2.33284e-05)*x+(1.00136e+00)");

   fitResidualPt = new TF1("fitResidualPt","(-6.45411e-01)/x+1.00520e+00");
  }
  else{ 
   nstep = 2;
   for(int istep = 0; istep < nstep; istep++){
     fileUnf[istep] = new TFile(Form("residualMCTruth/recotoref_pp_20170128_step%d.root",istep));
     for(int ieta = 0; ieta < nEta; ieta++){
       fitUnf[istep][ieta] = (TF1*)fileUnf[istep]->Get(Form("fit2%d",ieta)); 
     }
   }
   for(int istep = 0; istep < nstep; istep++){
    fileResMC[istep] = new TFile(Form("residualMCTruth/responseInEtaBinspp_yueshiL2L3_20170128_step%d.root",istep));
    for(int ieta = 0; ieta < nEta; ieta++){
     fitVsPt[istep][ieta] = (TF1*)fileResMC[istep]->Get(Form("fit2%d",ieta));
    }
   }
  }
  fitSmear[0] = new TF1("fitSmear0","(-1.75377e-05)*x+7.06741e-02",40.,200.);
  fitSmear[1] = new TF1("fitSmear1","(-3.10860e-04)*x+9.77457e-02",40.,200.);  
  fitGaus = new TF1("fitGaus","gaus(0)",-20,20);
  fitGaus->SetParameters(1,0,1);

 }
 
  double unfoldPt(double pt, double eta = 0, int istep = 0){
   double unfolding = 1;
   if(fmode == "pPb5" || fmode == "Pbp5") unfolding = fitUnf[0][0]->Eval(pt);
   else{
     int ieta = hist->FindBin(eta)-1;
     unfolding = 1./fitUnf[istep][ieta]->Eval(pt);
   }
   return pt/unfolding;
 }
 
 double getExtraSmear(double pt, double eta){
  double extraSmear = 1.;
  if(fabs(eta) < 1.3){
	extraSmear = fitSmear[0]->Eval(pt);
  }else{
	extraSmear = fitSmear[1]->Eval(pt);
  }
  if(extraSmear < 0) extraSmear = 0;
  return pt*(1+extraSmear*fitGaus->GetRandom());
 }
 
 double getResidualCorr(double pt, double eta){
  float corrpt = pt;
  if(pt < 10) corrpt = pt;
  if((fmode == "pPb5" || fmode == "Pbp5" ) && fabs(eta) > 3) return pt;
  //if(fmode=="pPb5")eta*=-1.;
  int ieta = hist->FindBin(eta)-1;
  for(int istep = 0; istep < nstep; istep++){
    if(istep==0 || pt < 100){//**
      double unfoldedPt = unfoldPt(corrpt, eta, istep);
      if(istep == 1) unfoldedPt = corrpt; //**
      double correction = fitVsPt[istep][ieta]->Eval(unfoldedPt);
      pt*=correction;
    }
  }
  if(fmode == "pPb5" || fmode == "Pbp5"){
    pt/=fitResidualPt->Eval(pt);
    if (pt >= 150) return pt;
    int ipt = 0;
    if(pt < 45 ) ipt = 0;
    if(pt >= 45 && pt < 65) ipt = 1;
    if(pt >= 65 && pt < 95) ipt = 2;
    if(pt >= 95 && pt < 135) ipt = 3;
    if(pt >= 135 && pt < 150) ipt = 4;
    pt/=fitVsEta[ipt]->Eval(eta);
  }
  return pt;
 }
 
 double getJEC_1st(double rawPt, double jetPt, double eta){
  double correction = 1;
  double rawPtOrig = rawPt;
  if(rawPt < 10) rawPt = 10;
  if(fmode=="pPb5" && rawPt < 15) rawPt = 15;
  //JEC derived by Yaxian, v08 for pPb direction
  if(fmode=="pPb5")
  {
    static const double l2_data[][11] = {
    {-5, -3, 8, 7.29453, 199.44, 0.494839, 0.276511, -0.792857, 0.448071, 0.0123351, 0.137177},
    {-3, -2.5, 8, 11.5588, 310.821, 0.440008, 0.638357, 0.893406, 0.44229, 0.00247189, -0.143698},
    {-2.5, -2.043, 8, 10.029, 505.368, 0.467457, 0.520936, 1.11645, 0.472458, 0.00263514, -0.207679},
    {-2.043, -1.93, 8, 13.7701, 509.688, 0.469552, 0.498823, 1.14783, 0.469665, 0.000155723, -0.158303},
    {-1.93, -1.74, 8, 12.8794, 515.139, 0.471104, 0.460732, 1.18737, 0.476502, 0.000402041, -0.221769},
    {-1.74, -1.653, 8, 14.8682, 522.526, 0.456514, 0.486116, 1.10437, 0.454001, -0.00806557, -0.11941},
    {-1.653, -1.566, 8, 15.1293, 525.531, 0.473442, 0.399486, 1.25624, 0.470044, -0.0018738, -0.142698},
    {-1.566, -1.392, 8, 13.9055, 523.446, 0.501994, 0.205984, 1.52002, 0.496017, 0.000818876, -0.159213},
    {-1.392, -1.218, 8, 12.3865, 515.391, 0.474566, 0.407612, 1.25494, 0.465946, -0.013683, -0.0839901},
    {-1.218, -1.131, 8, 13.1405, 519.768, 0.47858, 0.383164, 1.2956, 0.469138, -0.0115013, -0.0852108},
    {-1.131, -0.957, 8, 13.0604, 525.934, 0.46597, 0.352694, 1.24776, 0.456691, -0.0164066, -0.0742335},
    {-0.957, -0.879, 8, 14.3084, 531.606, 0.466896, 0.312609, 1.27841, 0.457132, -0.0147493, -0.0756452},
    {-0.879, -0.783, 8, 14.1959, 530.075, 0.477799, 0.159985, 1.40549, 0.466966, -0.0131053, -0.0826476},
    {-0.783, -0.609, 8, 13.7843, 541.39, 0.488929, 0.0685645, 1.52071, 0.481177, -0.0054031, -0.129421},
    {-0.609, -0.522, 8, 13.3437, 539.557, 0.450359, 0.277844, 1.20149, 0.446158, -0.0178408, -0.102329},
    {-0.522, -0.435, 8, 14.5444, 541.079, 0.474432, 0.107487, 1.41959, 0.471165, -0.00974263, -0.147399},
    {-0.435, -0.348, 8, 13.5976, 542.438, 0.477241, 0.0721407, 1.43613, 0.474038, -0.0090166, -0.148653},
    {-0.348, -0.261, 8, 14.8324, 546.451, 0.506946, -0.146872, 1.70983, 0.501821, -0.000435964, -0.170627},
    {-0.261, -0.087, 8, 13.829, 540.936, 0.477215, 0.0950669, 1.43355, 0.474513, -0.00812045, -0.15635},
    {-0.087, 0, 8, 14.7221, 544.903, 0.464125, 0.174525, 1.32229, 0.463064, -0.0107499, -0.152861},
    {0, 0.087, 8, 14.1465, 546.558, 0.478855, 0.0721429, 1.45124, 0.476884, -0.00534718, -0.1677},
    {0.087, 0.261, 8, 14.7086, 546.053, 0.480804, 0.0571601, 1.47145, 0.478541, -0.00489973, -0.168299},
    {0.261, 0.348, 8, 14.109, 544.74, 0.47235, 0.113624, 1.38971, 0.472365, -0.0066212, -0.175276},
    {0.348, 0.435, 8, 13.5225, 542.137, 0.481527, 0.0639313, 1.46645, 0.480771, -0.0040829, -0.181345},
    {0.435, 0.522, 8, 13.6836, 530.358, 0.460224, 0.205546, 1.29808, 0.456101, -0.0126815, -0.119764},
    {0.522, 0.609, 8, 16.0573, 537.119, 0.469883, 0.13113, 1.37569, 0.468712, -0.00878941, -0.160895},
    {0.609, 0.783, 8, 14.4276, 528.332, 0.483635, 0.070158, 1.4753, 0.484458, -0.00358609, -0.198548},
    {0.783, 0.879, 8, 13.2065, 518.277, 0.461956, 0.259693, 1.27985, 0.455809, -0.0142577, -0.100542},
    {0.879, 0.957, 8, 13.4033, 510.526, 0.44849, 0.394049, 1.14544, 0.441721, -0.0199149, -0.0769729},
    {0.957, 1.131, 8, 12.8019, 504.388, 0.473818, 0.296703, 1.32144, 0.466881, -0.0116215, -0.107867},
    {1.131, 1.218, 8, 14.8397, 474.369, 0.478343, 0.367147, 1.31484, 0.471962, -0.0100558, -0.117245},
    {1.218, 1.392, 8, 12.3264, 482.578, 0.472902, 0.389902, 1.25652, 0.467402, -0.0119355, -0.113864},
    {1.392, 1.566, 8, 14.3366, 452.374, 0.472389, 0.388226, 1.24421, 0.471403, -0.00446652, -0.161732},
    {1.566, 1.653, 8, 11.8416, 302.442, 0.449406, 0.456842, 1.07749, 0.442758, -0.0157467, -0.0838603},
    {1.653, 1.74, 8, 13.9266, 299.711, 0.481703, 0.299692, 1.33695, 0.474303, -0.00391539, -0.124872},
    {1.74, 1.93, 8, 15.0453, 296.772, 0.437488, 0.553883, 0.942183, 0.432433, -0.0205602, -0.0742533},
    {1.93, 2.043, 8, 12.99, 290.476, 0.427948, 0.566345, 0.877226, 0.423518, -0.0242982, -0.0662429},
    {2.043, 2.5, 8, 10.4275, 318.176, 0.482521, 0.410412, 1.21586, 0.488536, 0.0166088, -0.239731},
    {2.5, 3, 8, 13.8058, 152.136, 0.34743, 0.793517, 0.328186, 0.343375, -0.0832196, 0.0379197},
    {3, 5, 8, 9.38857, 85.1421, 0.253474, 0.907463, -0.243946, 0.256755, -0.231361, 0.113664}
	};

    static const double l3_data[][12] = {
    {-5.191, 5.191, 9, 4, 5000, 1.05368, 0.0418261, -1.31229, 0.010568, -0.179949, 2.84977, -0.782686}
	};

  //correction derived by Yue Shi
    static const double l2_2nd_data[][11] = {
    {-5.191, -4.889, 7, 40.0, 400.0, 0.519478, 0.168066, 0.040381, 0.001857, -0.005957},
    {-4.889, -4.716, 7, 40.0, 400.0, 0.523709, 0.170492, 0.040759, 0.001615, -0.006166},
    {-4.716, -4.538, 7, 40.0, 400.0, 0.527217, 0.172203, 0.040972, 0.001424, -0.006310},
    {-4.538, -4.363, 7, 40.0, 400.0, 0.531892, 0.173680, 0.040967, 0.001189, -0.006417},
    {-4.363, -4.191, 7, 40.0, 400.0, 0.538839, 0.174609, 0.040508, 0.000870, -0.006442},
    {-4.191, -4.013, 7, 40.0, 400.0, 0.557322, 0.172088, 0.037791, 0.000265, -0.006058},
    {-4.013, -3.839, 7, 40.0, 400.0, 0.563479, 0.173565, 0.037850, 0.000052, -0.006236},
    {-3.839, -3.664, 7, 40.0, 400.0, 0.593649, 0.169391, 0.032501, -0.001302, -0.005328},
    {-3.664, -3.489, 7, 40.0, 400.0, 0.628026, 0.164380, 0.026419, -0.002798, -0.004304},
    {-3.489, -3.314, 7, 40.0, 400.0, 0.668477, 0.157102, 0.019331, -0.004297, -0.003130},
    {-3.314, -3.139, 7, 40.0, 400.0, 0.707480, 0.149964, 0.012440, -0.005745, -0.001981},
    {-3.139, -2.964, 7, 40.0, 400.0, 0.735871, 0.144960, 0.007467, -0.006813, -0.001157},
    {-2.964, -2.853, 7, 40.0, 400.0, 0.737850, 0.144834, 0.007204, -0.006889, -0.001121},
    {-2.853, -2.65, 7, 40.0, 400.0, 0.720524, 0.148532, 0.010487, -0.006242, -0.001690},
    {-2.65, -2.5, 7, 40.0, 400.0, 0.688341, 0.155275, 0.016548, -0.005036, -0.002744},
    {-2.5, -2.322, 7, 40.0, 400.0, 0.659047, 0.160771, 0.021828, -0.003928, -0.003634},
    {-2.322, -2.172, 7, 40.0, 400.0, 0.636546, 0.164424, 0.025728, -0.003041, -0.004271},
    {-2.172, -2.043, 7, 40.0, 400.0, 0.629813, 0.164681, 0.026634, -0.002742, -0.004389},
    {-2.043, -1.93, 7, 40.0, 400.0, 0.633398, 0.162840, 0.025611, -0.002838, -0.004178},
    {-1.93, -1.83, 7, 40.0, 400.0, 0.641550, 0.160194, 0.023752, -0.003123, -0.003828},
    {-1.83, -1.74, 7, 40.0, 400.0, 0.651208, 0.157422, 0.021649, -0.003483, -0.003441},
    {-1.74, -1.653, 7, 40.0, 400.0, 0.660778, 0.154848, 0.019611, -0.003849, -0.003069},
    {-1.653, -1.566, 7, 40.0, 400.0, 0.669490, 0.152564, 0.017773, -0.004186, -0.002734},
    {-1.566, -1.479, 7, 40.0, 400.0, 0.676849, 0.150630, 0.016224, -0.004465, -0.002448},
    {-1.479, -1.392, 7, 40.0, 400.0, 0.682690, 0.149056, 0.015003, -0.004672, -0.002215},
    {-1.392, -1.305, 7, 40.0, 400.0, 0.686781, 0.148010, 0.014189, -0.004810, -0.002064},
    {-1.305, -1.218, 7, 40.0, 400.0, 0.690706, 0.147114, 0.013471, -0.004934, -0.001938},
    {-1.218, -1.131, 7, 40.0, 400.0, 0.695424, 0.146134, 0.012636, -0.005089, -0.001796},
    {-1.131, -1.044, 7, 40.0, 400.0, 0.701381, 0.144937, 0.011576, -0.005295, -0.001618},
    {-1.044, -0.957, 7, 40.0, 400.0, 0.708926, 0.143370, 0.010192, -0.005567, -0.001383},
    {-0.957, -0.879, 7, 40.0, 400.0, 0.717420, 0.141571, 0.008616, -0.005874, -0.001112},
    {-0.879, -0.783, 7, 40.0, 400.0, 0.726509, 0.139643, 0.006937, -0.006197, -0.000822},
    {-0.783, -0.696, 7, 40.0, 400.0, 0.734021, 0.138106, 0.005583, -0.006461, -0.000594},
    {-0.696, -0.609, 7, 40.0, 400.0, 0.738433, 0.137331, 0.004855, -0.006612, -0.000483},
    {-0.609, -0.522, 7, 40.0, 400.0, 0.740833, 0.137053, 0.004540, -0.006686, -0.000447},
    {-0.522, -0.435, 7, 40.0, 400.0, 0.742533, 0.136911, 0.004354, -0.006732, -0.000433},
    {-0.435, -0.348, 7, 40.0, 400.0, 0.743734, 0.136826, 0.004238, -0.006762, -0.000428},
    {-0.348, -0.261, 7, 40.0, 400.0, 0.744010, 0.136875, 0.004252, -0.006764, -0.000440},
    {-0.261, -0.174, 7, 40.0, 400.0, 0.743379, 0.137030, 0.004394, -0.006733, -0.000467},
    {-0.174, -0.087, 7, 40.0, 400.0, 0.742585, 0.137183, 0.004541, -0.006699, -0.000489},
    {-0.087, 0.0, 7, 40.0, 400.0, 0.742387, 0.137185, 0.004557, -0.006690, -0.000484},
    {0.0, 0.087, 7, 40.0, 400.0, 0.742865, 0.137054, 0.004429, -0.006715, -0.000452},
    {0.087, 0.174, 7, 40.0, 400.0, 0.743024, 0.137026, 0.004364, -0.006734, -0.000433},
    {0.174, 0.261, 7, 40.0, 400.0, 0.742527, 0.137143, 0.004439, -0.006723, -0.000440},
    {0.261, 0.348, 7, 40.0, 400.0, 0.741565, 0.137328, 0.004602, -0.006690, -0.000462},
    {0.348, 0.435, 7, 40.0, 400.0, 0.740132, 0.137595, 0.004846, -0.006639, -0.000497},
    {0.435, 0.522, 7, 40.0, 400.0, 0.738417, 0.137917, 0.005130, -0.006582, -0.000538},
    {0.522, 0.609, 7, 40.0, 400.0, 0.736805, 0.138192, 0.005369, -0.006537, -0.000569},
    {0.609, 0.696, 7, 40.0, 400.0, 0.734369, 0.138679, 0.005759, -0.006468, -0.000627},
    {0.696, 0.783, 7, 40.0, 400.0, 0.730396, 0.139567, 0.006464, -0.006346, -0.000743},
    {0.783, 0.879, 7, 40.0, 400.0, 0.724235, 0.140983, 0.007595, -0.006149, -0.000937},
    {0.879, 0.957, 7, 40.0, 400.0, 0.716999, 0.142667, 0.008946, -0.005912, -0.001172},
    {0.957, 1.044, 7, 40.0, 400.0, 0.709697, 0.144355, 0.010332, -0.005661, -0.001415},
    {1.044, 1.131, 7, 40.0, 400.0, 0.701670, 0.146196, 0.011885, -0.005370, -0.001690},
    {1.131, 1.218, 7, 40.0, 400.0, 0.693788, 0.147952, 0.013417, -0.005071, -0.001962},
    {1.218, 1.305, 7, 40.0, 400.0, 0.686538, 0.149544, 0.014841, -0.004785, -0.002215},
    {1.305, 1.392, 7, 40.0, 400.0, 0.680046, 0.151009, 0.016147, -0.004521, -0.002449},
    {1.392, 1.479, 7, 40.0, 400.0, 0.674146, 0.152481, 0.017391, -0.004281, -0.002677},
    {1.479, 1.566, 7, 40.0, 400.0, 0.669180, 0.153900, 0.018501, -0.004084, -0.002888},
    {1.566, 1.653, 7, 40.0, 400.0, 0.664971, 0.155285, 0.019517, -0.003917, -0.003089},
    {1.653, 1.74, 7, 40.0, 400.0, 0.660641, 0.156772, 0.020584, -0.003748, -0.003302},
    {1.74, 1.83, 7, 40.0, 400.0, 0.655528, 0.158519, 0.021823, -0.003556, -0.003549},
    {1.83, 1.93, 7, 40.0, 400.0, 0.649732, 0.160505, 0.023214, -0.003347, -0.003825},
    {1.93, 2.043, 7, 40.0, 400.0, 0.643475, 0.162701, 0.024720, -0.003127, -0.004124},
    {2.043, 2.172, 7, 40.0, 400.0, 0.638398, 0.164684, 0.026015, -0.002953, -0.004387},
    {2.172, 2.322, 7, 40.0, 400.0, 0.637369, 0.165782, 0.026542, -0.002925, -0.004515},
    {2.322, 2.5, 7, 40.0, 400.0, 0.642519, 0.165537, 0.025909, -0.003117, -0.004439},
    {2.5, 2.65, 7, 40.0, 400.0, 0.651240, 0.164347, 0.024553, -0.003430, -0.004231},
    {2.65, 2.853, 7, 40.0, 400.0, 0.662284, 0.162507, 0.022735, -0.003813, -0.003939},
    {2.853, 2.964, 7, 40.0, 400.0, 0.672691, 0.160589, 0.020974, -0.004162, -0.003649},
    {2.964, 3.139, 7, 40.0, 400.0, 0.682575, 0.158657, 0.019266, -0.004490, -0.003363},
    {3.139, 3.314, 7, 40.0, 400.0, 0.694620, 0.156240, 0.017160, -0.004888, -0.003007},
    {3.314, 3.489, 7, 40.0, 400.0, 0.708541, 0.153315, 0.014676, -0.005347, -0.002583},
    {3.489, 3.664, 7, 40.0, 400.0, 0.724324, 0.149920, 0.011824, -0.005869, -0.002092},
    {3.664, 3.839, 7, 40.0, 400.0, 0.741477, 0.146206, 0.008704, -0.006442, -0.001553},
    {3.839, 4.013, 7, 40.0, 400.0, 0.759389, 0.142339, 0.005437, -0.007045, -0.000989},
    {4.013, 4.191, 7, 40.0, 400.0, 0.777833, 0.138388, 0.002071, -0.007672, -0.000407},
    {4.191, 4.363, 7, 40.0, 400.0, 0.796387, 0.134359, -0.001285, -0.008281, 0.000167},
    {4.363, 4.538, 7, 40.0, 400.0, 0.814537, 0.130594, -0.004606, -0.008924, 0.000741},
    {4.538, 4.716, 7, 40.0, 400.0, 0.832892, 0.126810, -0.007958, -0.009575, 0.001321},
    {4.716, 4.889, 7, 40.0, 400.0, 0.851044, 0.123082, -0.011270, -0.010220, 0.001892},
    {4.889, 5.191, 7, 40.0, 400.0, 0.875533, 0.118064, -0.015735, -0.011091, 0.002663}
    };

    for (unsigned int i = 0; i < 40; i++)
    {
      if (eta >= l2_data[i][0] && eta < l2_data[i][1]) 
      {
        correction = 1;
        const double *p = &l2_data[i][5];
        const double x = rawPt;
        correction *= ((x>=20)*((p[0]+(p[1]/(pow(log10(x),2)+p[2])))+(p[3]*exp(-(p[4]*((log10(x)-p[5])*(log10(x)-p[5])))))))+((x<20)*1);;
        p = &l3_data[0][5];
        correction *= p[0]+p[1]/(pow(log10(x),2)+p[2])+p[3]*exp((-p[4]*(log10(x)-p[5])*(log10(x)-p[5]))+(p[6]*(log10(x)-p[5])));
        break;
      }
    }

    for(unsigned int i = 0; i < 82; i++) 
    {
      if (eta >= l2_2nd_data[i][0] && eta < l2_2nd_data[i][1]) 
      {
        const double *p = &l2_2nd_data[i][5];
        const double x = rawPt * correction;

        correction *= p[0]+p[1]*log10(x)+p[2]*pow(log10(x),2)+p[3]*pow(log10(x),3)+p[4]*pow(log10(x),4);
        break;
      }
    }    
    double correctedPt = rawPtOrig*correction;
	
	// correctedPt = getResidualCorr( correctedPt, eta);
	return correctedPt;
  } 
    
  //    JEC derived by Yaxian, v17 for Pbp direction
  else if(fmode=="Pbp5")
  {     
        static const double l2_data_1[][11] = {
        {-5, -3, 8, 20.9494, 142.562, 0.397055, 0.621114, 0.606799, 0.38662, -0.0887771, 0.0460021},
    {-3, -2.5, 8, 15.4947, 158.637, 0.121365, -0.422885, 3.30823, 1.02671, 0.194477, 1.383},
    {-2.5, -2.243, 8, 16.0786, 206.34, 0.576557, -0.435602, 0.767615, 0.750493, 0.0813181, -0.00265938},
    {-2.243, -1.93, 8, 17.8047, 297.859, 0.626572, -0.612674, 3.27614, 0.622391, 0.039351, -0.476973},
    {-1.93, -1.74, 8, 16.9472, 299.687, 0.500762, 0.240909, 1.65515, 0.488171, 0.00427765, -0.111224},
    {-1.74, -1.553, 8, 19.4427, 516.889, 0.475285, 0.275516, 1.46987, 0.459348, -0.0236147, -0.00829985},
    {-1.553, -1.392, 8, 18.815, 499.087, 0.525765, -0.0141155, 1.99741, 0.508772, 0.00487632, -0.100551},
    {-1.392, -1.131, 8, 17.6791, 456.35, 0.541308, -0.0345176, 2.16323, 0.52305, 0.00957549, -0.114932},
    {-1.131, -0.879, 8, 17.1671, 516.163, 0.59016, -0.549979, 2.83937, 0.583839, 0.023846, -0.360665},
    {-0.879, -0.609, 8, 17.7765, 525.119, 0.516859, -0.0525546, 1.97725, 0.501015, 0.00687127, -0.102051},
    {-0.609, -0.522, 8, 17.1145, 509.782, 0.46658, 0.174402, 1.52013, 0.450884, -0.0184007, -0.0149639},
    {-0.522, -0.435, 8, 18.055, 533.637, 0.665321, -1.35247, 3.01336, 0.663477, 0.0508586, -0.176136},
    {-0.435, -0.348, 8, 18.9764, 524.666, 0.65259, -1.24649, 3.58731, 0.61218, 0.039421, -0.151576},
    {-0.348, -0.261, 8, 18.7267, 505.638, 0.549697, -0.376181, 2.3728, 0.527632, 0.00996702, -0.0926022},
    {-0.261, -0.087, 8, 17.9307, 529.947, 0.477424, 0.115184, 1.60203, 0.461564, -0.0127118, -0.0332461},
    {-0.087, 0, 8, 18.3132, 539.987, 0.525164, -0.151212, 2.07113, 0.507833, 0.00906075, -0.104707},
    {0, 0.087, 8, 18.5845, 550.553, 0.46183, 0.201631, 1.44671, 0.448233, -0.0170974, -0.0320008},
    {0.087, 0.261, 8, 17.9564, 565.123, 0.458134, 0.219033, 1.41524, 0.446321, -0.0140534, -0.046613},
    {0.261, 0.348, 8, 18.6754, 544.04, 0.48739, 0.0895345, 1.67164, 0.468042, -0.0048837, -0.0297221},
    {0.348, 0.435, 8, 18.3028, 545.735, 0.553397, -0.334837, 2.36972, 0.53417, 0.0175732, -0.133825},
    {0.435, 0.522, 8, 18.1073, 516.688, 0.506145, -0.0523548, 1.89123, 0.486999, -0.0032065, -0.0476872},
    {0.522, 0.609, 8, 18.7352, 538.735, 0.533178, -0.237506, 2.16338, 0.513586, 0.00822483, -0.0914904},
    {0.609, 0.879, 8, 18.3687, 568.972, 0.556382, -0.322974, 2.38514, 0.538208, 0.0167073, -0.144766},
    {0.879, 1.131, 8, 17.8637, 515.13, 0.492424, 0.159862, 1.67279, 0.476868, -0.00969435, -0.0515374},
    {1.131, 1.392, 8, 18.5599, 516.65, 0.664873, -0.864739, 1.46247, 0.756289, 0.0574531, -0.323984},
    {1.392, 1.553, 8, 18.0191, 519.413, 0.660889, -1.11176, 3.77063, 0.656929, 0.0335571, -0.568288},
    {1.553, 1.74, 8, 16.2636, 524.989, 0.625011, -0.62645, 3.22383, 0.581068, 0.0392119, -0.040577},
    {1.74, 1.93, 8, 17.747, 509.352, 0.655161, -0.823391, 3.60988, 0.617062, 0.0452533, -0.190398},
    {1.93, 2.243, 8, 15.6122, 503.1, 0.632406, -0.63156, 3.388, 0.598343, 0.0418872, -0.176055},
    {2.243, 2.5, 8, 15.4238, 508.321, 0.649389, -0.734386, 3.0006, 0.634106, 0.0591195, -0.116671},
    {2.5, 3, 8, 17.4344, 492.834, 0.660892, -0.109437, -0.537924, 0.581253, 0.0889376, 0.00742166},
    {3, 5, 8, 8.74526, 285.872, 0.486494, -1.17782, 4.12418, 0.868344, 0.135141, 0.641498}
	};

    static const double l3_data_1[][12] = {
    {-5.191, 5.191, 9, 4, 5000, 1.05475, 0.0361301, 0.0225288, 0.00417097, 4.98344, 1.70233, -1.80036}
	};

    static const double l2_2nd_data_1[][11] = {
    {-5.191, -4.889, 7, 40.0, 400.0, 0.911028, 0.098031, -0.028214, -0.012986, 0.005049},
    {-4.889, -4.716, 7, 40.0, 400.0, 0.910038, 0.099136, -0.027648, -0.012931, 0.004926},
    {-4.716, -4.538, 7, 40.0, 400.0, 0.909273, 0.099961, -0.027222, -0.012889, 0.004834},
    {-4.538, -4.363, 7, 40.0, 400.0, 0.908422, 0.100813, -0.026777, -0.012845, 0.004737},
    {-4.363, -4.191, 7, 40.0, 400.0, 0.907434, 0.101691, -0.026309, -0.012796, 0.004637},
    {-4.191, -4.013, 7, 40.0, 400.0, 0.906197, 0.102639, -0.025787, -0.012738, 0.004527},
    {-4.013, -3.839, 7, 40.0, 400.0, 0.904602, 0.103683, -0.025192, -0.012668, 0.004403},
    {-3.839, -3.664, 7, 40.0, 400.0, 0.902549, 0.104838, -0.024508, -0.012583, 0.004263},
    {-3.664, -3.489, 7, 40.0, 400.0, 0.899890, 0.106147, -0.023702, -0.012476, 0.004101},
    {-3.489, -3.314, 7, 40.0, 400.0, 0.896512, 0.107633, -0.022757, -0.012346, 0.003913},
    {-3.314, -3.139, 7, 40.0, 400.0, 0.892335, 0.109313, -0.021657, -0.012188, 0.003699},
    {-3.139, -2.964, 7, 40.0, 400.0, 0.887403, 0.111172, -0.020415, -0.012006, 0.003460},
    {-2.964, -2.853, 7, 40.0, 400.0, 0.882933, 0.112792, -0.019323, -0.011844, 0.003253},
    {-2.853, -2.65, 7, 40.0, 400.0, 0.878965, 0.114323, -0.018322, -0.011701, 0.003064},
    {-2.65, -2.5, 7, 40.0, 400.0, 0.877586, 0.115262, -0.017824, -0.011649, 0.002968},
    {-2.5, -2.322, 7, 40.0, 400.0, 0.880060, 0.115106, -0.018145, -0.011730, 0.003029},
    {-2.322, -2.172, 7, 40.0, 400.0, 0.885776, 0.113965, -0.019177, -0.011918, 0.003231},
    {-2.172, -2.043, 7, 40.0, 400.0, 0.894078, 0.111957, -0.020806, -0.012193, 0.003550},
    {-2.043, -1.93, 7, 40.0, 400.0, 0.902394, 0.109773, -0.022497, -0.012462, 0.003888},
    {-1.93, -1.83, 7, 40.0, 400.0, 0.909367, 0.107799, -0.023956, -0.012677, 0.004189},
    {-1.83, -1.74, 7, 40.0, 400.0, 0.914136, 0.106278, -0.024997, -0.012806, 0.004416},
    {-1.74, -1.653, 7, 40.0, 400.0, 0.916431, 0.105352, -0.025531, -0.012838, 0.004551},
    {-1.653, -1.566, 7, 40.0, 400.0, 0.915715, 0.105246, -0.025406, -0.012750, 0.004562},
    {-1.566, -1.479, 7, 40.0, 400.0, 0.912491, 0.105854, -0.024714, -0.012560, 0.004464},
    {-1.479, -1.392, 7, 40.0, 400.0, 0.908405, 0.106697, -0.023831, -0.012334, 0.004331},
    {-1.392, -1.305, 7, 40.0, 400.0, 0.904564, 0.107442, -0.023025, -0.012123, 0.004213},
    {-1.305, -1.218, 7, 40.0, 400.0, 0.901146, 0.108075, -0.022332, -0.011940, 0.004115},
    {-1.218, -1.131, 7, 40.0, 400.0, 0.898558, 0.108464, -0.021845, -0.011799, 0.004055},
    {-1.131, -1.044, 7, 40.0, 400.0, 0.897269, 0.108509, -0.021648, -0.011717, 0.004047},
    {-1.044, -0.957, 7, 40.0, 400.0, 0.897004, 0.108307, -0.021674, -0.011683, 0.004076},
    {-0.957, -0.879, 7, 40.0, 400.0, 0.896876, 0.108202, -0.021685, -0.011664, 0.004091},
    {-0.879, -0.783, 7, 40.0, 400.0, 0.896839, 0.108238, -0.021656, -0.011657, 0.004086},
    {-0.783, -0.696, 7, 40.0, 400.0, 0.897878, 0.108051, -0.021851, -0.011705, 0.004114},
    {-0.696, -0.609, 7, 40.0, 400.0, 0.899356, 0.107778, -0.022142, -0.011781, 0.004154},
    {-0.609, -0.522, 7, 40.0, 400.0, 0.900849, 0.107536, -0.022422, -0.011860, 0.004187},
    {-0.522, -0.435, 7, 40.0, 400.0, 0.901429, 0.107515, -0.022503, -0.011897, 0.004184},
    {-0.435, -0.348, 7, 40.0, 400.0, 0.899646, 0.108283, -0.022007, -0.011842, 0.004064},
    {-0.348, -0.261, 7, 40.0, 400.0, 0.894707, 0.110121, -0.020737, -0.011660, 0.003791},
    {-0.261, -0.174, 7, 40.0, 400.0, 0.886896, 0.112873, -0.018790, -0.011362, 0.003393},
    {-0.174, -0.087, 7, 40.0, 400.0, 0.878549, 0.115774, -0.016726, -0.011036, 0.002983},
    {-0.087, 0.0, 7, 40.0, 400.0, 0.871205, 0.118311, -0.014921, -0.010746, 0.002633},
    {0.0, 0.087, 7, 40.0, 400.0, 0.865485, 0.120279, -0.013525, -0.010519, 0.002369},
    {0.087, 0.174, 7, 40.0, 400.0, 0.862650, 0.121222, -0.012858, -0.010407, 0.002253},
    {0.174, 0.261, 7, 40.0, 400.0, 0.863555, 0.120861, -0.013129, -0.010450, 0.002318},
    {0.261, 0.348, 7, 40.0, 400.0, 0.867644, 0.119357, -0.014216, -0.010628, 0.002540},
    {0.348, 0.435, 7, 40.0, 400.0, 0.873512, 0.117236, -0.015743, -0.010879, 0.002844},
    {0.435, 0.522, 7, 40.0, 400.0, 0.879620, 0.115061, -0.017304, -0.011133, 0.003154},
    {0.522, 0.609, 7, 40.0, 400.0, 0.884864, 0.113168, -0.018640, -0.011340, 0.003426},
    {0.609, 0.696, 7, 40.0, 400.0, 0.888939, 0.111741, -0.019639, -0.011486, 0.003635},
    {0.696, 0.783, 7, 40.0, 400.0, 0.892120, 0.110792, -0.020318, -0.011580, 0.003777},
    {0.783, 0.879, 7, 40.0, 400.0, 0.895245, 0.110041, -0.020881, -0.011656, 0.003893},
    {0.879, 0.957, 7, 40.0, 400.0, 0.899191, 0.109061, -0.021620, -0.011763, 0.004041},
    {0.957, 1.044, 7, 40.0, 400.0, 0.904244, 0.107613, -0.022661, -0.011909, 0.004254},
    {1.044, 1.131, 7, 40.0, 400.0, 0.911348, 0.105286, -0.024276, -0.012133, 0.004588},
    {1.131, 1.218, 7, 40.0, 400.0, 0.919574, 0.102397, -0.026263, -0.012417, 0.004996},
    {1.218, 1.305, 7, 40.0, 400.0, 0.926506, 0.099956, -0.027952, -0.012667, 0.005336},
    {1.305, 1.392, 7, 40.0, 400.0, 0.930462, 0.098602, -0.028910, -0.012820, 0.005518},
    {1.392, 1.479, 7, 40.0, 400.0, 0.930465, 0.098716, -0.028873, -0.012839, 0.005486},
    {1.479, 1.566, 7, 40.0, 400.0, 0.927572, 0.099910, -0.028108, -0.012756, 0.005302},
    {1.566, 1.653, 7, 40.0, 400.0, 0.922863, 0.101736, -0.026891, -0.012601, 0.005028},
    {1.653, 1.74, 7, 40.0, 400.0, 0.917337, 0.103829, -0.025484, -0.012416, 0.004718},
    {1.74, 1.83, 7, 40.0, 400.0, 0.911640, 0.105932, -0.024070, -0.012232, 0.004406},
    {1.83, 1.93, 7, 40.0, 400.0, 0.906007, 0.107999, -0.022689, -0.012058, 0.004099},
    {1.93, 2.043, 7, 40.0, 400.0, 0.901855, 0.109654, -0.021638, -0.011945, 0.003856},
    {2.043, 2.172, 7, 40.0, 400.0, 0.901690, 0.110148, -0.021468, -0.011978, 0.003782},
    {2.172, 2.322, 7, 40.0, 400.0, 0.909001, 0.108550, -0.022894, -0.012278, 0.004012},
    {2.322, 2.5, 7, 40.0, 400.0, 0.926815, 0.104096, -0.026535, -0.012953, 0.004660},
    {2.5, 2.65, 7, 40.0, 400.0, 0.950815, 0.097754, -0.031572, -0.013852, 0.005585},
    {2.65, 2.853, 7, 40.0, 400.0, 0.980479, 0.090200, -0.037686, -0.014964, 0.006697},
    {2.853, 2.964, 7, 40.0, 400.0, 1.002269, 0.085090, -0.042008, -0.015792, 0.007458},
    {2.964, 3.139, 7, 40.0, 400.0, 1.010724, 0.082876, -0.043792, -0.016124, 0.007775},
    {3.139, 3.314, 7, 40.0, 400.0, 1.000025, 0.084097, -0.042236, -0.015750, 0.007543},
    {3.314, 3.489, 7, 40.0, 400.0, 0.976124, 0.088300, -0.038183, -0.014913, 0.006872},
    {3.489, 3.664, 7, 40.0, 400.0, 0.946523, 0.093820, -0.033049, -0.013880, 0.006012},
    {3.664, 3.839, 7, 40.0, 400.0, 0.916445, 0.099419, -0.027842, -0.012833, 0.005142},
    {3.839, 4.013, 7, 40.0, 400.0, 0.889799, 0.104155, -0.023316, -0.011903, 0.004396},
    {4.013, 4.191, 7, 40.0, 400.0, 0.866424, 0.108048, -0.019446, -0.011084, 0.003769},
    {4.191, 4.363, 7, 40.0, 400.0, 0.845830, 0.111248, -0.016124, -0.010361, 0.003243},
    {4.363, 4.538, 7, 40.0, 400.0, 0.827127, 0.113989, -0.013172, -0.009702, 0.002783},
    {4.538, 4.716, 7, 40.0, 400.0, 0.809121, 0.116522, -0.010371, -0.009068, 0.002352},
    {4.716, 4.889, 7, 40.0, 400.0, 0.791722, 0.118914, -0.007687, -0.008455, 0.001942},
    {4.889, 5.191, 7, 40.0, 400.0, 0.768437, 0.122087, -0.004107, -0.007634, 0.001397}
	};

    for (unsigned int i = 0; i < 40; i++)
    {
      if (eta >= l2_data_1[i][0] && eta < l2_data_1[i][1]) 
      {   
        correction = 1;
        const double *q = &l2_data_1[i][5];
        const double x = rawPt;
        correction *= (q[0]+(q[1]/(pow(log10(x),2)+q[2])))+(q[3]*exp(-(q[4]*((log10(x)-q[5])*(log10(x)-q[5])))));
        q = &l3_data_1[0][5];
        correction *= q[0]+q[1]/(pow(log10(x),2)+q[2])+q[3]*exp((-q[4]*(log10(x)-q[5])*(log10(x)-q[5]))+(q[6]*(log10(x)-q[5])));
        break;
      }
    }  
  
    for(unsigned int i = 0; i < 82; i++)
    {
      if (eta >= l2_2nd_data_1[i][0] && eta < l2_2nd_data_1[i][1]) {
      const double *q = &l2_2nd_data_1[i][5];
      const double x = rawPt * correction;

      correction *= q[0]+q[1]*log10(x)+q[2]*pow(log10(x),2)+q[3]*pow(log10(x),3)+q[4]*pow(log10(x),4);
      break;
      }
    }
    double correctedPt = rawPtOrig*correction;
	// correctedPt = getResidualCorr( correctedPt, eta);
	return correctedPt;
  }
  //just use JEC in forest for non-Pb systems
  // else return jetPt;
  else return -1;
 }
};

