//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan  9 10:43:23 2017 by ROOT version 5.32/00
// from TTree ntdijet/
// found on file: ../data_driven_jec/ntuples_MC_reforest/pPb_pthat80_yueshiL2L3_step3.root
//////////////////////////////////////////////////////////

#ifndef ntdijet_h
#define ntdijet_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ntdijet {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         genpt1;
   Float_t         geneta1;
   Float_t         genphi1;
   Float_t         genpt2;
   Float_t         geneta2;
   Float_t         genphi2;
   Float_t         run;
   Float_t         evt;
   Float_t         lumi;
   Float_t         weight;
   Float_t         jtpt1;
   Float_t         jteta1;
   Float_t         jtphi1;
   Float_t         jtpt2;
   Float_t         jteta2;
   Float_t         jtphi2;
   Float_t         jtpt3;
   Float_t         jteta3;
   Float_t         jtphi3;
   Float_t         dphi;
   Float_t         trkMax1;
   Float_t         trkMax2;
   Float_t         ptAverage;
   Float_t         ptBarrel;
   Float_t         ptProbe;
   Float_t         etaBarrel;
   Float_t         etaProbe;
   Float_t         alpha;
   Float_t         hfsum;
   Float_t         hfp;
   Float_t         hfm;
   Float_t         hiBin;
   Float_t         B;
   Float_t         pthat;
   Float_t         refeta1;
   Float_t         refeta2;
   Float_t         refpt1;
   Float_t         refpt2;
   Float_t         refpt3;
   Float_t         refphi1;
   Float_t         refphi2;
   Float_t         hasforwardjet;
   Float_t         random;
   Float_t         subid1;
   Float_t         subid2;
   Float_t         subid3;
   Float_t         neutralmax1;
   Float_t         neutralmax2;
   Float_t         centweight;
   Float_t         rawpt1;
   Float_t         rawpt2;
   Float_t         recopt1;
   Float_t         recopt2;
   Float_t         jet40;
   Float_t         jet60;
   Float_t         jet80;
   Float_t         jet100;
   Float_t         hcalnoise;

   // List of branches
   TBranch        *b_genpt1;   //!                                                                                                                                                 
   TBranch        *b_geneta1;   //!                                                                                                                                              
   TBranch        *b_genphi1;   //!                                                                                                                                                 
   TBranch        *b_genpt2;   //!                                                                                                                                                 
   TBranch        *b_geneta2;   //!                                                                                                                                              
   TBranch        *b_genphi2;   //!                                                                                                                                                

   TBranch        *b_run;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_jtpt1;   //!
   TBranch        *b_jteta1;   //!
   TBranch        *b_jtphi1;   //!
   TBranch        *b_jtpt2;   //!
   TBranch        *b_jteta2;   //!
   TBranch        *b_jtphi2;   //!
   TBranch        *b_jtpt3;   //!
   TBranch        *b_jteta3;   //!
   TBranch        *b_jtphi3;   //!
   TBranch        *b_dphi;   //!
   TBranch        *b_trkMax1;   //!
   TBranch        *b_trkMax2;   //!
   TBranch        *b_ptAverage;   //!
   TBranch        *b_ptBarrel;   //!
   TBranch        *b_ptProbe;   //!
   TBranch        *b_etaBarrel;   //!
   TBranch        *b_etaProbe;   //!
   TBranch        *b_alpha;   //!
   TBranch        *b_hfsum;   //!
   TBranch        *b_hfp;   //!
   TBranch        *b_hfm;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_B;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_refeta1;   //!
   TBranch        *b_refeta2;   //!
   TBranch        *b_refpt1;   //!
   TBranch        *b_refpt2;   //!
   TBranch        *b_refpt3;   //!
   TBranch        *b_refphi1;   //!
   TBranch        *b_refphi2;   //!
   TBranch        *b_hasforwardjet;   //!
   TBranch        *b_random;   //!
   TBranch        *b_subid1;   //!
   TBranch        *b_subid2;   //!
   TBranch        *b_subid3;   //!
   TBranch        *b_neutralmax1;   //!
   TBranch        *b_neutralmax2;   //!
   TBranch        *b_centweight;   //!
   TBranch        *b_rawpt1;   //!
   TBranch        *b_rawpt2;   //!
   TBranch        *b_recopt1;   //!
   TBranch        *b_recopt2;   //!
   TBranch        *b_jet40;   //!
   TBranch        *b_jet60;   //!
   TBranch        *b_jet80;   //!
   TBranch        *b_jet100;   //!
   TBranch        *b_hcalnoise;   //!

   ntdijet(TString infile, TTree *tree=0);
   virtual ~ntdijet();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntries();
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ntdijet_cxx
ntdijet::ntdijet(TString infile, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   TFile * f = TFile::Open(infile);
   tree = (TTree*) f->Get("ntdijet");

   Init(tree);
}

ntdijet::~ntdijet()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}
 
Int_t ntdijet::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
} 
Int_t ntdijet::GetEntries()
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntries();
}
Long64_t ntdijet::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ntdijet::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("genpt1", &genpt1, &b_genpt1);
   fChain->SetBranchAddress("geneta1", &geneta1, &b_geneta1);
   fChain->SetBranchAddress("genphi1", &genphi1, &b_genphi1);
   fChain->SetBranchAddress("genpt2", &genpt2, &b_genpt2);
   fChain->SetBranchAddress("geneta2", &geneta2, &b_geneta2);
   fChain->SetBranchAddress("genphi2", &genphi2, &b_genphi2);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("jtpt1", &jtpt1, &b_jtpt1);
   fChain->SetBranchAddress("jteta1", &jteta1, &b_jteta1);
   fChain->SetBranchAddress("jtphi1", &jtphi1, &b_jtphi1);
   fChain->SetBranchAddress("jtpt2", &jtpt2, &b_jtpt2);
   fChain->SetBranchAddress("jteta2", &jteta2, &b_jteta2);
   fChain->SetBranchAddress("jtphi2", &jtphi2, &b_jtphi2);
   fChain->SetBranchAddress("jtpt3", &jtpt3, &b_jtpt3);
   fChain->SetBranchAddress("jteta3", &jteta3, &b_jteta3);
   fChain->SetBranchAddress("jtphi3", &jtphi3, &b_jtphi3);
   fChain->SetBranchAddress("dphi", &dphi, &b_dphi);
   fChain->SetBranchAddress("trkMax1", &trkMax1, &b_trkMax1);
   fChain->SetBranchAddress("trkMax2", &trkMax2, &b_trkMax2);
   fChain->SetBranchAddress("ptAverage", &ptAverage, &b_ptAverage);
   fChain->SetBranchAddress("ptBarrel", &ptBarrel, &b_ptBarrel);
   fChain->SetBranchAddress("ptProbe", &ptProbe, &b_ptProbe);
   fChain->SetBranchAddress("etaBarrel", &etaBarrel, &b_etaBarrel);
   fChain->SetBranchAddress("etaProbe", &etaProbe, &b_etaProbe);
   fChain->SetBranchAddress("alpha", &alpha, &b_alpha);
   fChain->SetBranchAddress("hfsum", &hfsum, &b_hfsum);
   fChain->SetBranchAddress("hfp", &hfp, &b_hfp);
   fChain->SetBranchAddress("hfm", &hfm, &b_hfm);
   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   fChain->SetBranchAddress("B", &B, &b_B);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("refeta1", &refeta1, &b_refeta1);
   fChain->SetBranchAddress("refeta2", &refeta2, &b_refeta2);
   fChain->SetBranchAddress("refpt1", &refpt1, &b_refpt1);
   fChain->SetBranchAddress("refpt2", &refpt2, &b_refpt2);
   fChain->SetBranchAddress("refpt3", &refpt3, &b_refpt3);
   fChain->SetBranchAddress("refphi1", &refphi1, &b_refphi1);
   fChain->SetBranchAddress("refphi2", &refphi2, &b_refphi2);
   fChain->SetBranchAddress("hasforwardjet", &hasforwardjet, &b_hasforwardjet);
   fChain->SetBranchAddress("random", &random, &b_random);
   fChain->SetBranchAddress("subid1", &subid1, &b_subid1);
   fChain->SetBranchAddress("subid2", &subid2, &b_subid2);
   fChain->SetBranchAddress("subid3", &subid3, &b_subid3);
   fChain->SetBranchAddress("neutralmax1", &neutralmax1, &b_neutralmax1);
   fChain->SetBranchAddress("neutralmax2", &neutralmax2, &b_neutralmax2);
   fChain->SetBranchAddress("centweight", &centweight, &b_centweight);
   fChain->SetBranchAddress("rawpt1", &rawpt1, &b_rawpt1);
   fChain->SetBranchAddress("rawpt2", &rawpt2, &b_rawpt2);
   fChain->SetBranchAddress("recopt1", &recopt1, &b_recopt1);
   fChain->SetBranchAddress("recopt2", &recopt2, &b_recopt2);
   fChain->SetBranchAddress("jet40", &jet40, &b_jet40);
   fChain->SetBranchAddress("jet60", &jet60, &b_jet60);
   fChain->SetBranchAddress("jet80", &jet80, &b_jet80);
   fChain->SetBranchAddress("jet100", &jet100, &b_jet100);
   fChain->SetBranchAddress("hcalnoise", &hcalnoise, &b_hcalnoise);
   Notify();
}

Bool_t ntdijet::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ntdijet::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntdijet::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ntdijet_cxx
