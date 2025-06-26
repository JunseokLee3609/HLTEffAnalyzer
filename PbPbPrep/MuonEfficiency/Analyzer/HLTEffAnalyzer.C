#include "MuonHLTNtupleRun3.h"
#include "AnalyzerTools.h"

using namespace std;

// -- numerator and denominator histograms for efficiency calculations
class HistContainer
{
public:
    HistContainer(
      TString _Tag,
      vector<TString> _variables = { "pt", "eta", "phi", "nvtx"},//, "pu", "lumi"},
      // -- determine the bin width of the histograms
      vector<vector<double>> _ranges = {
        // { number of bins, min, max }
        { 300, 0, 30 }, // pt
        { 48, -2.4, 2.4 }, // eta
        { 10, -TMath::Pi(), TMath::Pi() }, // phi
        { 10, 0, 10 }//, // nvtx
        //{ 75, 0, 75 },
        //{ 25, 0, 2.5 }
      }
    ) {

      if(_variables.size() != _ranges.size()) {
        cout << "HistContainer: _variables.size() != _ranges.size()" << endl;
        exit(1);
      }

      this->Tag = _Tag;
      this->variables = _variables;
      this->ranges = _ranges;
      this->nVar = variables.size();

      this->Init();
    }

  void fill_den( Object obj, double Nvtx, double PU, double Lumi, double weight = 1.0 ) {
      for(int k=0; k < nVar; ++k) {
        if( variables[k] == "nvtx" ) {
          v_den[k]->Fill( Nvtx, weight );
        }
        else if( variables[k] == "pu" ) {
          v_den[k]->Fill( PU, weight );
        }
        else if( variables[k] == "lumi" ) {
          v_den[k]->Fill( Lumi, weight );
        }
        else if( variables[k] == "mva" ) {
          v_den[k]->Fill( 1./(1.+exp(-1.*obj.get(variables[k]))), weight );
        }
        else if(obj.has(variables[k])) {
          v_den[k]->Fill( obj.get(variables[k]), weight );
        }
      }
    }

  void fill_num( Object obj, double Nvtx, double PU, double Lumi, double weight = 1.0 ) {
      for(int k=0; k < nVar; ++k) {
        if( variables[k] == "nvtx" ) {
          v_num[k]->Fill( Nvtx, weight );
        }
        else if( variables[k] == "pu" ) {
          v_num[k]->Fill( PU, weight );
        }
        else if( variables[k] == "lumi" ) {
          v_num[k]->Fill( Lumi, weight );
        }
        else if( variables[k] == "mva" ) {
          v_num[k]->Fill( 1./(1.+exp(-1.*obj.get(variables[k]))), weight );
        }
        else if(obj.has(variables[k])) {
          v_num[k]->Fill( obj.get(variables[k]), weight );
        }
      }
    }

    void fill_den( TString varname, int ivar, double value, double weight = 1.0 ) {
      if( variables[ivar] == varname ) {
        v_den[ivar]->Fill( value, weight );
      }
    }

    void fill_num( TString varname, int ivar, double value, double weight = 1.0 ) {
      if( variables[ivar] == varname ) {
        v_num[ivar]->Fill( value, weight );
      }
    }

    void Save( TFile *f_output )
    {
      f_output->cd();

      for(int k=0; k < nVar; ++k) {
        v_den[k]->Write();
        v_num[k]->Write();
        delete v_den[k];
        delete v_num[k];
      }
    }

    void Save( TDirectory *dir )
    {
      dir->cd();

      for(int k=0; k < nVar; ++k) {
        v_den[k]->SetDirectory(dir);
        v_num[k]->SetDirectory(dir);
        v_den[k]->Write();
        v_num[k]->Write();
        delete v_den[k];
        delete v_num[k];
      }
    }

    ~HistContainer() {}

private:
    TString Tag;
    int nVar;
    vector<TString> variables;
    vector<vector<double>> ranges;

    vector<TH1D*> v_den;
    vector<TH1D*> v_num;

    void Init()
    {
      TH1::SetDefaultSumw2(kTRUE);
      TH2::SetDefaultSumw2(kTRUE);
      TH1::AddDirectory(kFALSE);
      TH2::AddDirectory(kFALSE);

      TString Tag_tmp = this->Tag == "" ? "" : "_"+this->Tag;

      for(int k=0; k < nVar; ++k) {
        TString name = TString::Format("%s_%s", Tag_tmp.Data(), variables[k].Data() );

        TH1D *den = new TH1D("den"+name, "", ranges[k][0], ranges[k][1], ranges[k][2]);
        TH1D *num = new TH1D("num"+name, "", ranges[k][0], ranges[k][1], ranges[k][2]);

        v_den.push_back( den );
        v_num.push_back( num );
      }
    }
};

class HistContainer2D
{
public:
    HistContainer2D(
      TString _Tag,
      vector<vector<TString>> _variables = {
        {"eta", "pt"},
        {"eta", "phi"},
      },
      vector<vector<double>> _ranges = {
        {24, -2.4, 2.4, 40, 0, 200},
        {24, -2.4, 2.4, 30, -TMath::Pi(), TMath::Pi()},
      }
    ) {

      if(_variables.size() != _ranges.size()) {
        cout << "HistContainer2D: _variables.size() != _ranges.size()" << endl;
        exit(1);
      }

      this->Tag = _Tag;
      this->variables = _variables;
      this->ranges = _ranges;
      this->nVar = variables.size();

      this->Init();
    }

  void fill_den( Object obj, double weight = 1.0 ) {
    for(int k=0; k < nVar; ++k) {
      if(obj.has(variables.at(k).at(0)) && obj.has(variables.at(k).at(1))) {
	v_den.at(k)->Fill( obj.get(variables.at(k).at(0)), obj.get(variables.at(k).at(1)), weight );
      }
    }
  }

  void fill_num( Object obj, double weight = 1.0 ) {
    for(int k=0; k < nVar; ++k) {
      if(obj.has(variables.at(k).at(0)) && obj.has(variables.at(k).at(1))) {
	v_num.at(k)->Fill( obj.get(variables.at(k).at(0)), obj.get(variables.at(k).at(1)), weight );
      }
    }
  }

  void Save( TFile *f_output )
  {
    f_output->cd();

    for(int k=0; k < nVar; ++k) {
      v_den.at(k)->Write();
      v_num.at(k)->Write();
      delete v_den.at(k);
      delete v_num.at(k);
    }
  }

  void Save( TDirectory *dir )
  {
    dir->cd();

    for(int k=0; k < nVar; ++k) {
      v_den.at(k)->SetDirectory(dir);
      v_num.at(k)->SetDirectory(dir);
      v_den.at(k)->Write();
      v_num.at(k)->Write();
      delete v_den.at(k);
      delete v_num.at(k);
    }
  }

  ~HistContainer2D() {}

private:
    TString Tag;
    int nVar;
    vector<vector<TString>> variables;
    vector<vector<double>> ranges;

    vector<TH2D*> v_den;
    vector<TH2D*> v_num;

    void Init()
    {
      TH1::SetDefaultSumw2(kTRUE);
      TH2::SetDefaultSumw2(kTRUE);
      TH1::AddDirectory(kFALSE);
      TH2::AddDirectory(kFALSE);

      TString Tag_tmp = this->Tag == "" ? "" : "_"+this->Tag;

      for(int k=0; k < nVar; ++k) {
        TString name = TString::Format("%s_%s_%s", Tag_tmp.Data(), variables.at(k).at(0).Data(), variables.at(k).at(1).Data());

        TH2D *den = new TH2D("den"+name, "", ranges.at(k)[0], ranges.at(k)[1], ranges.at(k)[2], ranges.at(k)[3], ranges.at(k)[4], ranges.at(k)[5]);
        TH2D *num = new TH2D("num"+name, "", ranges.at(k)[0], ranges.at(k)[1], ranges.at(k)[2], ranges.at(k)[3], ranges.at(k)[4], ranges.at(k)[5]);

        v_den.push_back( den );
        v_num.push_back( num );
      }
    }
};

// TnP criteria
bool offlineSel(Object obj)
{
    bool out = (
        acceptance(obj) &&
        // obj.get("isTight") && //options: isTight, isMedium, isLoose, isSoft(empty in the ntuple?)
        obj.get("isLoose") && //options: isTight, isMedium, isLoose, isSoft(empty in the ntuple?)
        //obj.get("relPFIso") < 0.15 //for pp (definition in "MuonHLTNtupleRun3.h")
        //obj.get("isHighPtNew") &&
        //obj.get("relTrkIso") < 0.10
        true
    );
    return out;
}

// echo 'gROOT->LoadMacro("HLTEffAnalyzer.C+"); gSystem->Exit(0);' | root -b -l
// root -l -b -q 'HLTEffAnalyzer.C("v00", "TEST")' >&log&

void HLTEffAnalyzer(
    TString ver = "v00", TString tag = "TEST",
    vector<TString> vec_Dataset = {}, TString JobId = "",
    TString outputDir = "./",
    const bool doDimuon = false, double ZmassWindow = -1,
    Int_t maxEv = -1, bool doMem = false, int nMem = 10001, bool doBar = true  // HERE
    // Int_t maxEv = -1, bool doMem = false, int nMem = 10001, bool doBar = false
) {
  int nthreads = 4;
  ROOT::EnableImplicitMT(nthreads);
    TH1::SetDefaultSumw2(kTRUE);
    TH2::SetDefaultSumw2(kTRUE);
    TH1::AddDirectory(kFALSE);
    TH2::AddDirectory(kFALSE);

    TStopwatch timer_total;
    timer_total.Start();

    // -- Input
    vector<TString> paths = vec_Dataset;
    if(tag == "TEST") {
      // ntuples for PbPb2023 location 
      // 8k events: /afs/cern.ch/work/s/soohwan/public/PbPb2023_MuonHLT_ntuple_8k.root
      // 730k events: /eos/cms/store/group/phys_heavyions/soohwan/Run3_2023/./PostRunHLT/TriggerStudy_Run375754_DetailedForMu_PbPb2023_CMSSW_13_2_6_patch2_soohwan_09Nov2023_v1/ntuple.root
      // 788k events: /eos/cms/store/group/phys_heavyions/soohwan/Run3_2023/PostRunHLT/MuonHLTRunBefore_21Nov2023_v4.root
      // 1.4M events: /eos/cms/store/group/phys_heavyions/soohwan/Run3_2023/PostRunHLT/MuonHLTRunAfter_20Nov2023_v4.root
    // paths = {"./ntuple_ppRef_JPsi_pThat2_PU4_140X_mcRun3_2024_realistic_ForHITracking_v1_HLTDilepton_Final.root"};
    // paths = {"/home/bayuadinp/trigger/HLT/ntuple_SmallSystem_2K.root"};
    paths = {"ntuple_coherent.root"};
    }

    // -- Output
    TString fileName = TString::Format( "hist-%s-%s", ver.Data(), tag.Data() );
    if(JobId != "")  fileName = fileName + TString::Format("--%s", JobId.Data());
    TFile *f_output = TFile::Open(outputDir+fileName+"-Eff_2025OO_Coherent.root", "RECREATE"); // output name

    // -- Event chain
    TChain *_chain_Ev          = new TChain("ntupler/ntuple");
    for(size_t f = 0; f<paths.size(); ++f) {
        _chain_Ev->Add(paths[f]);
        // cout << "Adding path: " << paths[f] << endl;
    }
    cout << endl;

    unsigned nEvent      = _chain_Ev->GetEntries();
    // unsigned nEvent      = 100000;
    if(maxEv >= 0)  nEvent = maxEv;
    cout << "\t nEvent: " << nEvent << endl;

    // -- a part of the branch names in ntuple
    // (This part is for branch activation of the tree. See line 4769 in "MuonHLTNtupleRun3.h")
    vector<TString> branch_tags = {
        "genParticle", // Br 30 - 67 v
        "vec_", // Br 68 - 77 v
        "muon", // Br 78 - 174 v
        "L1Muon", // Br 196 - 203 v
        "L2Muon", // Br 184 - 189 v
        "L3Muon", // Br 175 - 183
        "TkMuon", // Br 190 - 195

        "iterL3OI", // Br 204 - 237
        "iterL3IOFromL2", // Br 238 - 271
        "iterL3FromL2", // Br 272 - 305
        "iterL3IOFromL1", // Br 306 - 328
        "iterL3MuonNoID", // Br 329 - 369 v
        "iterL3Muon", // Br 370 - 410 v
        "TP", // Br 411 - 447

        "hltIterL3MuonTrimmedPixelVertices",  // Br 448 - 458
        "hltIterL3FromL1MuonTrimmedPixelVertices", // Br 459 -469
        "hltIterL3OIMuonTrackAssociated", // Br 470 - 504
        "tpTo", // Br 505 - 541
        
        "hltIter0IterL3MuonTrackAssociated", // Br 542 - 576 v
        "tpTo_hltIter0IterL3MuonTrackAssociated", // Br 577 - 613

        "hltIter0IterL3FromL1MuonTrackAssociated", // Br 614 - 648
        "tpTo_hltIter0IterL3FromL1MuonTrackAssociated", // Br 649 - 685

        "hltIterL3MuonMergedAssociated", // Br 686 - 720 v
        "tpTo_hltIterL3MuonMergedAssociated", // Br 721 - 757 

        "hltIterL3MuonAndMuonFromL1MergedAssociated", // Br 758 - 792 v
        "tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated", // Br 793 - 829

        "iterL3MuonNoIDTrackAssociated", // Br 830 - 864
        "tpTo_iterL3MuonNoIDTrackAssociated", // Br 865 - 901

        "iterL3MuonTrackAssociated", // Br 902 - 936
        "tpTo_iterL3MuonTrackAssociated", // Br 937 -973

        "hltPixelTracksInRegionL2Associated", // Br 974 - 1008 
        "tpTo_hltPixelTracksInRegionL2Associated", // Br 1009 - 1045

        "hltPixelTracksInRegionL1Associated", // Br 1046 - 1080
        "tpTo_hltPixelTracksInRegionL1Associated", // Br 1081 - 1117

        "hltIterL3GlbMuonTrackAssociated", // Br 1118 - 1152
        "tpTo_hltIterL3GlbMuonTrackAssociated", // Br 1153 - 1189
        // "hi_cBin"
    };

    unique_ptr<MuonHLTNtupleRun3>  nt( new MuonHLTNtupleRun3( _chain_Ev, branch_tags ) );

    // -- Histograms for gen
    TH1D *h_nEvents = new TH1D("h_nEvents",  "", 3, -1, 2);
    TH1D *h_nRuns = new TH1D("h_nRuns",  "", 100, 350000, 400000);

    TH1D *h_gen_pt  = new TH1D("h_gen_pt",  "", 40, 0, 20);
    TH1D *h_gen_eta = new TH1D("h_gen_eta", "", 60, -3, 3);
    TH1D *h_gen_phi = new TH1D("h_gen_phi", "", 64, -3.2, 3.2);

    TH1D *h_gen_acc_pt  = new TH1D("h_gen_acc_pt",  "", 40, 0, 20);
    TH1D *h_gen_acc_eta = new TH1D("h_gen_acc_eta", "", 60, -3, 3);
    TH1D *h_gen_acc_phi = new TH1D("h_gen_acc_phi", "", 64, -3.2, 3.2);

    TH1D *h_gen_hard_pt  = new TH1D("h_gen_hard_pt",  "", 40, 0, 20);
    TH1D *h_gen_hard_eta = new TH1D("h_gen_hard_eta", "", 60, -3, 3);
    TH1D *h_gen_hard_phi = new TH1D("h_gen_hard_phi", "", 64, -3.2, 3.2);

    TH1D *h_gen_hard_acc_pt  = new TH1D("h_gen_hard_acc_pt",  "", 40, 0, 20);
    TH1D *h_gen_hard_acc_eta = new TH1D("h_gen_hard_acc_eta", "", 60, -3, 3);
    TH1D *h_gen_hard_acc_phi = new TH1D("h_gen_hard_acc_phi", "", 64, -3.2, 3.2);
            
    // -- Determine L3types' names
    // (This determines the file names of the histogram when it is saved, the name could be whatever you want to call, but it should be unique)
    // (Also, these correspond one-on-one with L3MuonColls (see line 890 to 948 and 1000 to 1055), which is where the muon information is stored from the ntuple)
    vector<TString> L3types = {
        "L1Muon",
        "L2Muon",

        "hltIterL3MuonNoID",
        "hltIterL3Muon",

        "hltIter0",
        "hltIter0FromL1",

        "hltL3FromL2Merged", 
        "hltL3Merged", 
        "hltIterL3MuonNoIDTrack",
        "hltIterL3MuonTrack",

        "hltPixelTracks",
        "hltPixelTracksInRegionL2",
        "hltPixelTracksInRegionL1",
        "hltOI",

        // ***************************************
        // -- filters
        "IterL3L1sSingleMuOpen",
        "IterL3L1sSingleMu3",
        "L1sSingleMu7",

        // ***************************************
        // -- paths        
        "L3SingleMu3_Open",
        "L3SingleMu5", 
        "L3SingleMu12",
        "L1DoubleMu0SQCent40to100",
        "L1SingleMuOpenBptxAND",
        "L1SingleMu0BptxAND",
        "L1SingleMu3BptxAND",
        "L1SingleMu5BptxAND",
        "L1SingleMu7BptxAND",
        "L1SingleMu0SQCent40to100BptxAND",
        "L1SingleMuOpenSQCent40to100BptxAND",
        "HLTOxySingleMuOpen_NotMBHF2AND",
        "HLTOxyL1SingleMu0"
    };

    vector<TString> HLTpaths = {
        "L2SingleMu3_Open"
        "L3SingleMu3_Open",
        "L3SingleMu5"
        "L3SingleMu12"
        "HLT_OxySingleMuOpen_NotMBHF2AND_v1",
        "HLT_OxyL1SingleMu0_v1"
    };

        // -- a part of the filter names and HLT paths in PbPb HLT menu
        // (Using the script (PrintObject.cxx) in the Ntupler directory, we can extract the fired filter names in the ntuple)
        // (I matched the corresponding HLT path using condDB)
        // {{{ 
        // (filter name / HLT path)
        // hltL1fForIterL3L1fL1sSingleMuOpenL1Filtered0 / HLT_HIL3SingleMu3_Open_v
        // hltL1fForIterL3L1fL1sSingleMuOpenSinglejet28L1Filtered0 / HLT_HIL3SingleMu3_SinglePuAK4CaloJet40_v
        // hltL1fForIterL3L1fL1sSingleMu3L1Filtered0 / HLT_HIL3SingleMu5_v
        // hltL1fForIterL3L1fL1sSingleMu3Singlejet32L1Filtered0 / HLT_HIL3SingleMu5_SinglePuAK4CaloJet40_v
        // hltL1fForIterL3L1fL1sSingleMu5L1Filtered0
        // hltL1fForIterL3L1fL1sSingleMu7L1Filtered0 / HLT_HIL3SingleMu7L1Filtered0

        // hltL1fL1sSingleMuOpenL1Filtered0 / HLT_HIL1SingleMu0_Open_v, HLT_HIL2SingleMu3_Open_v,HLT_HIL3SingleMu3_Open_v
        // hltL1fL1sSingleMuOpenSingleJet28MuFiltered0
        // hltL1fL1sSingleMuOpenSingleJet44MuFiltered0
        // hltL1fL1sSingleMu3L1Filtered0
        // hltL1fL1sSingleMu3SingleJet32MuFiltered0
        // hltL1fL1sSingleMu3SingleJet40MuFiltered0
        // hltL1fL1sSingleMu5L1Filtered0
        // hltL1fL1sSingleMu7L1Filtered0 / HLT_HIL3SingleMu12_v

        // hltL1sSingleMuOpenBptxAND
        // hltL1sSingleMuOpenSingleJet28MidEta2p7BptxAND
        // hltL1sSingleMuOpenSingleJet44MidEta2p7BptxAND
        // hltL1sSingleMuOpenNotMBHF2AND
        // hltL1sSingleMuOpenNotMBHF2OR
        // hltL1sSingleMuOpenORSingleMuCosmicEMTFNotMBHF2AND
        // hltL1sSingleMuOpenORSingleMuCosmicEMTFNotMBHF2OR

        // hltL1sSingleMu0BptxAND
        // hltL1sSingleMu3BptxAND
        // hltL1sSingleMu3SingleJet32MidEta2p7BptxAND
        // hltL1sSingleMu3SingleJet40MidEta2p7BptxAND
        // hltL1sSingleMu5BptxAND
        // hltL1sSingleMu7BptxAND
        // hltL1sSingleMuCosmicNotMBHF2AND
        // hltL1sSingleMuCosmicNotMBHF2OR

        // hltL2fL1fL1sSingleMuOpenL2Filtered0
        // hltL2fL1fL1sSingleMuOpenL2Filtered3
        // hltL2fL1fL1sSingleMuOpenSingleJet28L2Filtered0
        // hltL2fL1fL1sSingleMu3L2Filtered3
        // hltL2fL1fL1sSingleMu3SingleJet32L2Filtered0

        // hltL1sDoubleMuOpenMaxDr3p5BptxAND
        
        // hltL2fL1fL1sDoubleMuOpenL2Filtered0

        // hltL3fL1fL1sSingleMuOpenL3Filtered3 / HLT_HIL3SingleMu3_Open_v
        // hltL3fL1fL1sSingleMuOpenSingleJet28L3Filtered3
        // }}}

    // -- Efficiency
    vector<double> Eff_genpt_mins = {
        0,
        3,
        5,
        7,
        // 8,
        // 10,
        // 12,
        // 15,
        // 20
        // 16,
        // 26,
        // 30,
        // 53,
        // 105,
    };
    vector<vector<double>> Etas_bin = {
        {0., 2.4},
        //{0.9, 2.4},
        //{0.9, 1.2},
        //{1.2, 2.4},
    };
    vector<TString> Etas_str = {
        "I",  // In
        // "BE", // Barrel Endcap
        // "O", // Out
        // "E", // Endcap
    };
    vector<vector<int>> Runs_bin = {
        {-1, 999999},
    };

    vector<vector<vector<vector<HistContainer*>>>> hc_Eff = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer*>>>> hc_Eff_L1SQ0 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer*>>>> hc_Eff_L1DQ0 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer*>>>> hc_Eff_L1SQ2 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer*>>>> hc_Eff_L1DQ2 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]

    vector<vector<vector<vector<HistContainer2D*>>>> hc2D_Eff = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer2D*>>>> hc2D_Eff_L1SQ0 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer2D*>>>> hc2D_Eff_L1DQ0 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer2D*>>>> hc2D_Eff_L1SQ2 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
    vector<vector<vector<vector<HistContainer2D*>>>> hc2D_Eff_L1DQ2 = {};  // Eff[L3 type][run bin][eta bin][gen pt min]
 
    // -- res
    vector<vector<TH1D *>> vh_L3_qbpt_pt  = {};
    vector<vector<TH1D *>> vh_L3_qbpt_eta = {};
    vector<vector<TH1D *>> vh_L3_pt_pt    = {};
    vector<vector<TH1D *>> vh_L3_pt_eta   = {};

    // -- set up the histograms
    int iL3type = 0;
    for (auto& L3type: L3types) {

        hc_Eff.push_back( {} );
        hc_Eff_L1SQ0.push_back( {} );
        hc_Eff_L1DQ0.push_back( {} );
        hc_Eff_L1SQ2.push_back( {} );
        hc_Eff_L1DQ2.push_back( {} );

        hc2D_Eff.push_back( {} );
        hc2D_Eff_L1SQ0.push_back( {} );
        hc2D_Eff_L1DQ0.push_back( {} );
        hc2D_Eff_L1SQ2.push_back( {} );
        hc2D_Eff_L1DQ2.push_back( {} );        


        for (unsigned irun = 0; irun < Runs_bin.size(); ++irun) {
            TString run_str = TString::Format("Run%d_%d", Runs_bin.at(irun).at(0), Runs_bin.at(irun).at(1));
            if (Runs_bin.at(irun).at(0) < 0 && Runs_bin.at(irun).at(1) == 999999)
                run_str = "RunAll";

            hc_Eff.at(iL3type).push_back( {} );
            hc_Eff_L1SQ0.at(iL3type).push_back( {} );
            hc_Eff_L1DQ0.at(iL3type).push_back( {} );
            hc_Eff_L1SQ2.at(iL3type).push_back( {} );
            hc_Eff_L1DQ2.at(iL3type).push_back( {} );

            hc2D_Eff.at(iL3type).push_back( {} );
            hc2D_Eff_L1SQ0.at(iL3type).push_back( {} );
            hc2D_Eff_L1DQ0.at(iL3type).push_back( {} );
            hc2D_Eff_L1SQ2.at(iL3type).push_back( {} );
            hc2D_Eff_L1DQ2.at(iL3type).push_back( {} );            


            for (unsigned ieta = 0; ieta < Etas_bin.size(); ++ieta) {
                hc_Eff.at(iL3type).at(irun).push_back( {} );
                hc_Eff_L1SQ0.at(iL3type).at(irun).push_back( {} );
                hc_Eff_L1DQ0.at(iL3type).at(irun).push_back( {} );
                hc_Eff_L1SQ2.at(iL3type).at(irun).push_back( {} );
                hc_Eff_L1DQ2.at(iL3type).at(irun).push_back( {} );                

                hc2D_Eff.at(iL3type).at(irun).push_back( {} );
                hc2D_Eff_L1SQ0.at(iL3type).at(irun).push_back( {} );
                hc2D_Eff_L1DQ0.at(iL3type).at(irun).push_back( {} );
                hc2D_Eff_L1SQ2.at(iL3type).at(irun).push_back( {} );
                hc2D_Eff_L1DQ2.at(iL3type).at(irun).push_back( {} );                


                for (auto& Eff_genpt_min: Eff_genpt_mins) {
                    HistContainer* hc_tmp0   = new HistContainer( TString::Format("Eff_%s_%s_%s_genpt%.0f",      L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer* hc_tmp1_1 = new HistContainer( TString::Format("Eff_L1SQ0_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer* hc_tmp2_1 = new HistContainer( TString::Format("Eff_L1DQ0_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer* hc_tmp1_2 = new HistContainer( TString::Format("Eff_L1SQ2_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer* hc_tmp2_2 = new HistContainer( TString::Format("Eff_L1DQ2_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );

                    HistContainer2D* hc2D_tmp0 = new HistContainer2D( TString::Format("2DEff_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer2D* hc2D_tmp1_1 = new HistContainer2D( TString::Format("2DEff_L1SQ0_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer2D* hc2D_tmp2_1 = new HistContainer2D( TString::Format("2DEff_L1DQ0_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer2D* hc2D_tmp1_2 = new HistContainer2D( TString::Format("2DEff_L1SQ2_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );
                    HistContainer2D* hc2D_tmp2_2 = new HistContainer2D( TString::Format("2DEff_L1DQ2_%s_%s_%s_genpt%.0f", L3type.Data(), run_str.Data(), Etas_str.at(ieta).Data(), Eff_genpt_min) );

                    hc_Eff.at(iL3type).at(irun).at(ieta).push_back( hc_tmp0 );
                    hc_Eff_L1SQ0.at(iL3type).at(irun).at(ieta).push_back( hc_tmp1_1 );
                    hc_Eff_L1DQ0.at(iL3type).at(irun).at(ieta).push_back( hc_tmp2_1 );
                    hc_Eff_L1SQ2.at(iL3type).at(irun).at(ieta).push_back( hc_tmp1_2 );
                    hc_Eff_L1DQ2.at(iL3type).at(irun).at(ieta).push_back( hc_tmp2_2 );

                    hc2D_Eff.at(iL3type).at(irun).at(ieta).push_back( hc2D_tmp0 );
                    hc2D_Eff_L1SQ0.at(iL3type).at(irun).at(ieta).push_back( hc2D_tmp1_1 );
                    hc2D_Eff_L1DQ0.at(iL3type).at(irun).at(ieta).push_back( hc2D_tmp2_1 );
                    hc2D_Eff_L1SQ2.at(iL3type).at(irun).at(ieta).push_back( hc2D_tmp1_2 );
                    hc2D_Eff_L1DQ2.at(iL3type).at(irun).at(ieta).push_back( hc2D_tmp2_2 );

                }
            }
        }

        // -- res
        // define vectors to store histograms
        vh_L3_qbpt_pt.push_back( {} );
        vh_L3_qbpt_eta.push_back( {} );
        vh_L3_pt_pt.push_back( {} );
        vh_L3_pt_eta.push_back( {} );

        // -- define histograms and put them in the vector
        for (int ipt=0; ipt<n_pt_bins; ++ipt) {
            TString name = TString::Format("h_%s_qbpt_pt_%d", L3types.at(iL3type).Data(), ipt);
            TH1D *h_L3_qbpt  = new TH1D(name,  "", 400, -1, 1);
            vh_L3_qbpt_pt.at(iL3type).push_back( h_L3_qbpt );

            name = TString::Format("h_%s_pt_pt_%d", L3types.at(iL3type).Data(), ipt);
            TH1D *h_L3_pt  = new TH1D(name,  "", 400, -1, 1);
            vh_L3_pt_pt.at(iL3type).push_back( h_L3_pt );
        }

        for (int ieta=0; ieta<n_eta_bins-1; ++ieta) {
            TString name = TString::Format("h_%s_qbpt_eta_%d", L3types.at(iL3type).Data(), ieta);
            TH1D *h_L3_qbpt  = new TH1D(name,  "", 400, -1, 1);
            vh_L3_qbpt_eta.at(iL3type).push_back( h_L3_qbpt );

            name = TString::Format("h_%s_pt_eta_%d", L3types.at(iL3type).Data(), ieta);
            TH1D *h_L3_pt  = new TH1D(name,  "", 400, -1, 1);
            vh_L3_pt_eta.at(iL3type).push_back( h_L3_pt );
        }

        iL3type += 1;
    }

    // -- Event loop
    cout << "start loop" << endl;
    for(unsigned i_ev=0; i_ev<nEvent; i_ev++) {

        // -- print options
        if(doBar)
            loadBar(i_ev+1, nEvent, 100, 100);
        else if( doMem && i_ev !=0 && i_ev % nMem == 0 )
            printMemory("\t");
        else
            printRunTimeShort(timer_total);
            // cout << "\nEvent: " << i_ev << endl;  // HERE

        // -- load values from the ntuple  
        nt->GetEntry( i_ev );

        double genWeight = nt->genEventWeight > 0.0 ? 1.0 : -1.0;
        // if using the real data, genWeight is 1
        if (nt->isRealData)
            genWeight = 1.;
        h_nEvents->Fill( genWeight );
        h_nRuns->Fill( nt->runNum, genWeight );

        // -- Fill Gen particles (it's empty for real data)
        vector<Object> GenParticles = nt->get_GenParticles();

        bool isDimuon = false;
        vector<Object> GenMuonsFromHardProcess = {};
        vector<Object> GenMuonsFromHPInAcc = {};
        
        // -- Dimuon skim for DY
            bool found0 = false;
            bool found1 = false;
            for(auto& genP: GenParticles) {

                if( fabs(genP.get("ID")) == 13 && genP.get("fromHardProcessFinalState") == 1 ) {
                    GenMuonsFromHardProcess.push_back( genP );

                    h_gen_hard_pt->Fill( genP.pt, genWeight );
                    h_gen_hard_eta->Fill( genP.eta, genWeight );
                    h_gen_hard_phi->Fill( genP.phi, genWeight );

                    if( acceptance( genP ) ) {
                        GenMuonsFromHPInAcc.push_back(genP);

                        h_gen_hard_acc_pt->Fill( genP.pt, genWeight );
                        h_gen_hard_acc_eta->Fill( genP.eta, genWeight );
                        h_gen_hard_acc_phi->Fill( genP.phi, genWeight );
                    }
                }
                
                if( fabs(genP.get("ID")) == 13 && genP.get("status") == 1 ) {
                    h_gen_pt->Fill( genP.pt, genWeight );
                    h_gen_eta->Fill( genP.eta, genWeight );
                    h_gen_phi->Fill( genP.phi, genWeight );

                    if( acceptance( genP ) ) {
                        h_gen_acc_pt->Fill( genP.pt, genWeight );
                        h_gen_acc_eta->Fill( genP.eta, genWeight );
                        h_gen_acc_phi->Fill( genP.phi, genWeight );
                    }
                }

                if( genP.get("ID") == 13 && genP.get("isHardProcess") == 1 )
                    found0 = true;
                if( genP.get("ID") == -13 && genP.get("isHardProcess") == 1 )
                    found1 = true;
            }
            isDimuon = (found0 && found1);
            if (doDimuon && !isDimuon) {
                continue;
            }

            std::sort(GenMuonsFromHardProcess.begin(), GenMuonsFromHardProcess.end(), sort_by_pt());
            std::sort(GenMuonsFromHPInAcc.begin(), GenMuonsFromHPInAcc.end(), sort_by_pt());

            // if(doDimuon && isDimuon && ZmassWindow > 0.) {
            //     TLorentzVector mu0, mu1;
            //     mu0.SetPtEtaPhiM(GenMuonsFromHardProcess.at(0).pt,
            //                      GenMuonsFromHardProcess.at(0).eta,
            //                      GenMuonsFromHardProcess.at(0).phi,
            //                      MU_MASS);
            //     mu1.SetPtEtaPhiM(GenMuonsFromHardProcess.at(1).pt,
            //                      GenMuonsFromHardProcess.at(1).eta,
            //                      GenMuonsFromHardProcess.at(1).phi,
            //                      MU_MASS);
            //     double Zmass = (mu0+mu1).M();
            //     if (abs(Zmass-91) > ZmassWindow) {
            //         continue;
            //     }
            // }
        

        // -- Get object collections
        vector<Object> L1Muons = nt->get_L1Muons();
        vector<Object> L2Muons = nt->get_L2Muons();

        vector<Object> iterL3OI = nt->get_iterL3OI();
        vector<Object> iterL3IOFromL2 = nt->get_iterL3IOFromL2();
        vector<Object> iterL3IOFromL1 = nt->get_iterL3IOFromL1();
        vector<Object> iterL3MuonNoID = nt->get_iterL3MuonNoID();
        vector<Object> iterL3Muon = nt->get_iterL3Muon();
        vector<Object> TP = nt->get_TP();
        
        vector<Object> hltIter0IterL3MuonTrackAssociated = nt->get_hltIter0IterL3MuonTrackAssociated();
        vector<Object> hltIter0IterL3FromL1MuonTrackAssociated = nt->get_hltIter0IterL3FromL1MuonTrackAssociated();    
        
        vector<Object> hltIterL3MuonMergedAssociated = nt->get_hltIterL3MuonMergedAssociated(); //
        vector<Object> hltIterL3MuonAndMuonFromL1MergedAssociated = nt->get_hltIterL3MuonAndMuonFromL1MergedAssociated();
        vector<Object> iterL3MuonNoIDTrackAssociated = nt->get_iterL3MuonNoIDTrackAssociated();
        vector<Object> iterL3MuonTrackAssociated = nt->get_iterL3MuonTrackAssociated();

        vector<Object> hltPixelTracksAssociated = nt->get_hltPixelTracksAssociated();
        vector<Object> hltPixelTracksInRegionL2Associated = nt->get_hltPixelTracksInRegionL2Associated();
        vector<Object> hltPixelTracksInRegionL1Associated = nt->get_hltPixelTracksInRegionL1Associated();
        vector<Object> hltIterL3OIMuonTrackAssociated = nt->get_hltIterL3OIMuonTrackAssociated();
        
        // ***************************************
        // -- Get object collections of the filters
        // nt->get_myHLTObjects("<the exact filter name in the HLT menu>")
        vector<Object> IterL3SingleMuOpen_MYHLT = nt->get_myHLTObjects("hltL1fForIterL3L1fL1sSingleMuOpenL1Filtered0");
        vector<Object> IterL3SingleMu3_MYHLT = nt->get_myHLTObjects("hltL1fForIterL3L1fL1sSingleMu3L1Filtered0"); 
        vector<Object> L1sSingleMu7_MYHLT = nt->get_myHLTObjects("hltL1fL1sSingleMu7L1Filtered0");
        vector<Object> L1sDoubleMu0SQCent40to100_MYHLT                 = nt->get_myHLTObjects("hltL1fL1sDoubleMu0SQCent40to100L1Filtered0");
        vector<Object> L1SingleMuOpenBptxAND_MYHLT                     =nt->get_myHLTObjects("hltL1fL1sSingleMuOpenL1Filtered0");
        vector<Object> L1SingleMu0BptxAND_MYHLT                        =nt->get_myHLTObjects("hltL1fL1sSingleMu0L1Filtered0");
        vector<Object> L1SingleMu3BptxAND_MYHLT                        =nt->get_myHLTObjects("hltL1fL1sSingleMu3L1Filtered0");
        vector<Object> L1SingleMu5BptxAND_MYHLT                        =nt->get_myHLTObjects("hltL1fL1sSingleMu5L1Filtered0");
                vector<Object> HLTOxySingleMuOpenNotMBHF2AND_MYHLT = nt->get_myHLTObjects("hltL1sSingleMuOpenNotMBHF2AND");
        vector<Object> HLTOxyL1SingleMu0_MYHLT = nt->get_myHLTObjects("hltL1sSingleMu0BptxAND");
        vector<Object> L1SingleMu7BptxAND_MYHLT                       =nt->get_myHLTObjects("hltL1fL1sSingleMu7L1Filtered0");
        vector<Object> L1SingleMu0SQCent40to100BptxAND_MYHLT     =nt->get_myHLTObjects("hltL1fL1sSingleMuSQCent40to10L1Filtered0");
        vector<Object> L1SingleMuOpenSQCent40to100BptxAND_MYHLT =nt->get_myHLTObjects("hltL1fL1sSingleMuSQOpenCent40to10L1Filtered0");

        // -- TnP selection
        vector<Object> muons = nt->get_offlineMuons(); //get muons' information (in the Ntuple, muon_* )
        vector<Object> probes = {};        
        // tag
        for (auto & i_mu : muons) {
            if (i_mu.pt < 0.) continue;

            if (!offlineSel(i_mu)) continue;

            // if (!i_mu.matched(IsoMu24_HLT, 0.1)) 
            //     continue;

            // probe
            for (auto & j_mu : muons) {
                if (!offlineSel(j_mu)) continue;

                if (i_mu.get("charge") * j_mu.get("charge") > 0) continue;
                
                // double pair_mass = invMass(i_mu, j_mu);
                
                // if (pair_mass < 2.7) continue;
                // if (pair_mass > 3.5) continue;

                // j_mu.addVar("pair_mass", pair_mass);

                probes.push_back(j_mu);
            }
        }

        // -- L3 Muon Collection (The size of this has to be matched with L3 Type. See line 1158)
        vector<vector<Object>*> L3MuonColls {
            &probes,  // for L1 muon eff
            &L2Muons,

            &iterL3MuonNoID,
            &iterL3Muon,

            &hltIter0IterL3MuonTrackAssociated,
            &hltIter0IterL3FromL1MuonTrackAssociated,

            &hltIterL3MuonMergedAssociated, //
            &hltIterL3MuonAndMuonFromL1MergedAssociated,
            &iterL3MuonNoIDTrackAssociated,
            &iterL3MuonTrackAssociated,

            &hltPixelTracksAssociated,
            &hltPixelTracksInRegionL2Associated,
            &hltPixelTracksInRegionL1Associated,
            &hltIterL3OIMuonTrackAssociated,

        // ***************************************
        // -- filters
            &IterL3SingleMuOpen_MYHLT,  
            &IterL3SingleMu3_MYHLT,
            &L1sSingleMu7_MYHLT,

        // ***************************************
        // -- paths (match one of the filter names that the path contains)       
            &IterL3SingleMuOpen_MYHLT,  
            &IterL3SingleMu3_MYHLT, 
            &L1sSingleMu7_MYHLT,
            &L1sDoubleMu0SQCent40to100_MYHLT,
            &L1SingleMuOpenBptxAND_MYHLT,                   
            &L1SingleMu0BptxAND_MYHLT,                      
            &L1SingleMu3BptxAND_MYHLT,                      
            &L1SingleMu5BptxAND_MYHLT,                      
            &L1SingleMu7BptxAND_MYHLT,                     
            &L1SingleMu0SQCent40to100BptxAND_MYHLT,   
            &L1SingleMuOpenSQCent40to100BptxAND_MYHLT,
            &HLTOxySingleMuOpenNotMBHF2AND_MYHLT,
            &HLTOxyL1SingleMu0_MYHLT //HLTOxyL1SingleMu0




            
        };

        if (L3types.size() != L3MuonColls.size()) {
            cout << "ERROR: L3types.size() != L3MuonColls.size()" << endl;
            return;
        }

        //### L3types loop ###
        for(unsigned i=0; i<L3types.size(); ++i) {
            vector<Object>* L3Coll = L3MuonColls.at(i);
            // cout << "L3Coll size: " << L3Coll->size() << endl;

            TString L3type = L3types.at(i);
            // cout << "L3type: " << L3type << endl;

            L3type.ReplaceAll("my","");
            bool looseMatch = L3type.Contains("L2Muon");
            
            // cout << "looseMatchBool: " << looseMatch << endl;

            // -- Efficiency
            for (unsigned irun = 0; irun < Runs_bin.size(); ++irun) {
            if(L3type.Contains("Cent")&& nt->hi_cBin < 80 ){
              continue;
            }

                if (nt->runNum < Runs_bin.at(irun).at(0)) continue;
                if (nt->runNum > Runs_bin.at(irun).at(1)) continue;
                for (unsigned ieta = 0; ieta < Etas_bin.size(); ++ieta) {
                    //### offlineMuons loop ###
                    int iprobe = -1;

                    for(auto& probemu: probes) {
                        L3Coll = L3MuonColls.at(i);

                        // --select mu in the acceptance 
                        // (isn't this repetition already done in the offline selection?)
                        if( !acceptance( probemu ) ) continue;


                        // --select eta in one bin
                        if (Etas_bin.at(ieta).at(0) > abs(probemu.eta)) continue;
                        if (Etas_bin.at(ieta).at(1) < abs(probemu.eta)) continue;

                        // --New L1s matching
                        /*
                        //if (probemu.pt < 26)
                        //    continue;
                        iprobe++;
                        if(probemu.get("l1ptByQ") < 1.0){
                          cout<<"\n\nOffline mu("<<i<<")        : pt = "<<probemu.pt<<", eta = "<<probemu.eta<<", phi = "<<probemu.phi<<", charge = "<<probemu.get("charge")<<endl;
                          cout<<"recol1MatchByQ       : pt = "<<probemu.get("l1ptByQ")<<", eta = "<<probemu.get("l1etaByQ")<<", phi = "<<probemu.get("l1phiByQ")<<", qual = "<<probemu.get("l1qByQ")<<", charge = "<<probemu.get("l1chargeByQ")<<endl;
                            for(unsigned il1=0; il1<L1Muons.size(); il1++){
                              cout<<"L1 Collection's "<<il1<<"th  : pt = "<<L1Muons.at(il1).pt<<", eta = "<<L1Muons.at(il1).eta<<", phi = "<<L1Muons.at(il1).phi<<", dR = "<<probemu.deltaR(L1Muons.at(il1))<<", charge = "<<L1Muons.at(il1).get("charge")<<", qual = "<<L1Muons.at(il1).get("quality")<<endl;
                            }
                            cout<<"nl1t = "<<probemu.get("nl1t")<<endl;
                            cout<<"l1t size = "<<probemu.getvec("l1tpt").size()<<endl;
                            for(unsigned il1t=0; il1t<probemu.get("nl1t"); il1t++){
                              cout<<"L1T Collection's "<<il1t<<"th : pt = "<<probemu.getvec("l1tpt").at(il1t)<<", eta = "<<probemu.getvec("l1teta").at(il1t)<<", phi = "<<probemu.getvec("l1tphi").at(il1t)<<", dR = "<<probemu.getvec("l1tdr").at(il1t)<<", charge = "<<probemu.getvec("l1tcharge").at(il1t)<<", qual = "<<probemu.getvec("l1tq").at(il1t)<<endl;
                            }
                        }
                        */
                        bool matched_L1SQ0 = (
                            probemu.get("l1ptByQ") > -1.0 &&
                            probemu.get("l1drByQ") < 0.3 &&
                            probemu.get("l1qByQ") > 7 // 11
                        );

                        bool matched_L1SQ2 = (
                            probemu.get("l1ptByQ") > 2 &&
                            probemu.get("l1drByQ") < 0.3 &&
                            probemu.get("l1qByQ") > 7 // 11
                        );
                        // bool matched_L1SQ8 = (
                        //     probemu.get("l1ptByQ") > 8.0 &&
                        //     probemu.get("l1drByQ") < 0.3 &&
                        //     probemu.get("l1qByQ") > 11
                        // );
                        // bool matched_L1SQ22 = (
                        //     probemu.get("l1ptByQ") > 22.0 &&
                        //     probemu.get("l1drByQ") < 0.3 &&
                        //     probemu.get("l1qByQ") > 11
                        // );

                        bool matched_L1DQ0 = (
                            probemu.get("l1ptByQ") > -1.0 &&
                            probemu.get("l1drByQ") < 0.3 &&
                            probemu.get("l1qByQ") > 7
                        );

                        bool matched_L1DQ2 = (
                            probemu.get("l1ptByQ") > 2.0 &&
                            probemu.get("l1drByQ") < 0.3 &&
                            probemu.get("l1qByQ") > 7
                        );

                        // bool matched_L1DQ8 = (
                        //     probemu.get("l1ptByQ") > 8.0 &&
                        //     probemu.get("l1drByQ") < 0.3 &&
                        //     probemu.get("l1qByQ") > 7
                        // );
                        // bool matched_L1DQ22 = (
                        //     probemu.get("l1ptByQ") > 22.0 &&
                        //     probemu.get("l1drByQ") < 0.3 &&
                        //     probemu.get("l1qByQ") > 7
                        // );

                        bool l1matched_L1SQ0 = probemu.l1matched(0., 7);
                        bool l1matched_L1SQ2 = probemu.l1matched(2., 7);
                        // bool l1matched_L1SQ0 = probemu.l1matched(0., 11);
                        // bool l1matched_L1SQ8 = probemu.l1matched(8., 11);
                        // bool l1matched_L1SQ22 = probemu.l1matched(22., 11);
                        bool l1matched_L1DQ0 = probemu.l1matched(0., 7);
                        bool l1matched_L1DQ2 = probemu.l1matched(2., 7);
                        // bool l1matched_L1DQ8 = probemu.l1matched(8., 7);
                        // bool l1matched_L1DQ22 = probemu.l1matched(22., 7);

                        //cout<<"matched = "<<(matched_L1SQ22?"true":"false")<<", l1matched = "<<(m1atched_L1SQ22?"true":"false")<<endl;
                        int matched_idx = -1e6;

                        // HERE !!! --determine matched_idx value
                        vector<int> L3map(L3Coll->size(), -1);
                        if (L3type.Contains("L1Muon")) {
                            matched_idx = -1e6;
                        }
                        else if (
                            L3type.Contains("OI") ||
                            L3type.Contains("L3") ||
                            L3type.Contains("GlbTrkMuon") ||
                            (std::find(HLTpaths.begin(), HLTpaths.end(), L3type) != HLTpaths.end())
                        ) {
                            matched_idx = probemu.matched( *L3Coll, L3map, 0.1 );
                        }
                        else if (
                            L3type.Contains("hltPixelTracks")
                        ) {
                            matched_idx = probemu.matched( *L3Coll, L3map, 0.01 );  // Pixel tracks - TRK guys are using dR 0.01 btw Offline, HLT
                            // cout << "matched_idx(hltPixelTracks): "<< matched_idx << endl;
                        }
                        else if (
                             L3type.Contains("IterL3L1sSingleMuOpen")
                        ) {
                            matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L3SingleMu3_Open")
                        ) {
                            if (nt->path_myFired("HLT_HIL3SingleMu3_Open_v3")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }                        
                        else if (
                             L3type.Contains("L3SingleMu12")
                        ) {
                          if (nt->path_myFired("HLT_HIL3SingleMu12_v3")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1DoubleMu0SQCent40to100")
                        ) {
                          if (nt->path_myFired("HLT_HIL1DoubleMu0_SQ_Centrality40to100_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMuOpenBptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu0_Open_v5")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMu0BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu0_v5")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMu3BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu3_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMu5BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu5_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMu7BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu7_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMu0SQCent40to100BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu0_SQ_Centrality40to100v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                        else if (
                             L3type.Contains("L1SingleMuOpenSQCent40to100BptxAND")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMuOpen_SQ_Centrality40to100_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }
                                                else if (
                             L3type.Contains("HIL1SingleMu0_Centrality40to100")
                        ) {
                          if (nt->path_myFired("HLT_HIL1SingleMu0_Centrality40to100_v1")) matched_idx = probemu.matched( *L3Coll, L3map, 0.3 );
                        }                        else if (
                          L3type.Contains("HLTOxyL1SingleMu0")
                        ){
                          if (nt->path_myFired("HLT_OxyL1SingleMu0_v1")) matched_idx = probemu.L1matched( *L3Coll, L3map, 0.3 );
                          // if (nt->path_myFired("HLT_OxyL1SingleMu0_v1")) matched_idx = 1;
                        }
                         else if (
                          L3type.Contains("HLTOxySingleMuOpen_NotMBHF2AND")
                        ){
                          if (nt->path_myFired("HLT_OxySingleMuOpen_NotMBHF2AND_v1")) matched_idx = probemu.L1matched( *L3Coll, L3map, 0.3 );
                          // if (nt->path_myFired("HLT_OxySingleMuOpen_NotMBHF2AND_v1")) matched_idx = 1;
                        }
                        else {
                            matched_idx = looseMatch ? probemu.matched( *L3Coll, L3map, 0.3 ) :  // L2 muon
                                                       probemu.matched( *L3Coll, L3map, 0.1, 0.5 );  // IO tracks
                        }

                        if (matched_idx < 0) {
                            probemu.addVar("dR", -1.);
                        } 
                        else {
                            probemu.addVar("dR", probemu.deltaR(L3Coll->at(matched_idx)));
                        }

                        // --
                        int matched_idx_res = -1e6;
                        vector<int> L3map2(L3Coll->size(), -1);
                        matched_idx_res = looseMatch ? probemu.matched( *L3Coll, L3map2, 0.3 ) :  // L2 muon
                                                       probemu.matched( *L3Coll, L3map2, 0.1 );
                        // cout << probemu.matched( *L3Coll, L3map2, 0.3 ) << ", " << probemu.matched( *L3Coll, L3map2, 0.1 ) << endl;
                        // cout << "matched_idx_res: " << matched_idx_res << endl;
                                
                        // --  Fill Efficiency histograms / Gen or L1
                        for(unsigned j=0; j<Eff_genpt_mins.size(); ++j) {
                            if( probemu.pt > Eff_genpt_mins.at(j) ) {
                                hc_Eff.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                hc2D_Eff.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );
                                if( matched_idx > -1 ) {
                                    hc_Eff.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                    hc2D_Eff.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                }

                                if(l1matched_L1DQ0) {
                                    hc_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                    hc2D_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                    if(L3type.Contains("L1Muon")) {                                       
                                        hc_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                        hc2D_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                    }
                                    else {
                                        if( matched_idx > -1 ) {                                            
                                            hc_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                            hc2D_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                        }
                                    }
                                }

                                if(l1matched_L1SQ0) {                                    
                                    hc_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                    hc2D_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                    if(L3type.Contains("L1Muon")) {                                        
                                        hc_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                        hc2D_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                    }
                                    else {
                                        if( matched_idx > -1 ) {                                            
                                            hc_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                            hc2D_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                        }
                                    }
                                }

                                if(l1matched_L1DQ2) {
                                    hc_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                    hc2D_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                    if(L3type.Contains("L1Muon")) {                                       
                                        hc_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                        hc2D_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                    }
                                    else {
                                        if( matched_idx > -1 ) {                                          
                                            hc_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                            hc2D_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                        }
                                    }
                                }

                                if(l1matched_L1SQ2) {                                   
                                    hc_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                    hc2D_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                    if(L3type.Contains("L1Muon")) {                                       
                                        hc_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                        hc2D_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                    }
                                    else {
                                        if( matched_idx > -1 ) {                                          
                                            hc_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->dataPU, nt->instLumi, genWeight );
                                            hc2D_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                        }
                                    }
                                }


                                // if(l1matched_L1DQ8) {
                                //     hc_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //     hc2D_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                //     if(L3type.Contains("L1Muon")) {
                                //         hc_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //         hc2D_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                //     }
                                //     else {
                                //         if( matched_idx > -1 ) {
                                //             hc_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //             hc2D_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                //         }
                                //     }
                                // }

                                // if(l1matched_L1SQ22) {
                                //     hc_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //     hc2D_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_den( probemu, genWeight );

                                //     if(L3type.Contains("L1Muon")) {
                                //         hc_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //         hc2D_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                //     }
                                //     else {
                                //         if( matched_idx > -1 ) {
                                //             hc_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, nt->nVertex, nt->DataPU, nt->InstLumi, genWeight );
                                //             hc2D_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->fill_num( probemu, genWeight );
                                //         }
                                //     }
                                // }
                            }
                        }

                        // -- res
                        if (matched_idx_res > -1 &&
                            (std::find(HLTpaths.begin(), HLTpaths.end(), L3type) == HLTpaths.end()) &&
                            Runs_bin.at(irun).at(0) < 0 &&
                            Etas_bin.at(ieta).at(0) == 0. &&
                            Etas_bin.at(ieta).at(1) == 2.4
                        ) {
                            if (L3type.Contains("L1Muon"))
                                continue;

                            if (!L3Coll->at(matched_idx_res).has("charge")) {
                                if (L3Coll->at(matched_idx_res).has("inner_charge")) {
                                    L3Coll->at(matched_idx_res).addVar("charge", L3Coll->at(matched_idx_res).get("inner_charge"));
                                }
                                else {
                                    L3Coll->at(matched_idx_res).addVar("charge", 0.);
                                }
                            }

                            double L3charge  = L3Coll->at(matched_idx_res).get("charge");
                            double gencharge = probemu.get("charge");
                            if (L3charge == 0.) {
                                L3charge = 1.;
                                gencharge = 1.;
                            }
                            double L3pt      = L3Coll->at(matched_idx_res).pt;
                            double L3qbpt    = L3charge / L3Coll->at(matched_idx_res).pt;
                            double genpt     = probemu.pt;
                            double genqbpt   = gencharge / probemu.pt;
                            double res_qbpt  = (genqbpt - L3qbpt) / genqbpt;
                            double res_pt    = (L3pt - genpt) / genpt;

                            for(int ipt=0; ipt<n_pt_bins-1; ++ipt) {
                                if( probemu.pt >= pt_bins[ipt] && probemu.pt < pt_bins[ipt+1] ) {
                                    vh_L3_qbpt_pt.at(i)[ipt]->Fill( res_qbpt, genWeight );
                                    vh_L3_pt_pt.at(i)[ipt]->Fill(   res_pt,   genWeight );
                                    break;
                                }
                            }
                            // if (probemu.pt > 26.0) {
                            // cout << "---------------------" << endl;
                            // cout << "probemu.pt: "<< probemu.pt << endl;
                            // cout << "probemu.pt: "<< probemu.pt << endl;
                            if (probemu.pt > 1.0) {
                                vh_L3_qbpt_pt.at(i)[n_pt_bins-1]->Fill( res_qbpt, genWeight );
                                vh_L3_pt_pt.at(i)[n_pt_bins-1]->Fill(   res_pt,   genWeight );
                                // cout << "res_qbpt, genWeight: "<< res_qbpt << " " << genWeight << endl;
                                // cout << "res_pt, genWeight: "<< res_pt << " " << genWeight << endl;
                            }
                            for(int ieta=0; ieta<n_eta_bins-1; ++ieta) {
                                // if( probemu.eta >= eta_bins[ieta] && probemu.eta < eta_bins[ieta+1] && probemu.pt > 26.0 ) {
                                   if( probemu.eta >= eta_bins[ieta] && probemu.eta < eta_bins[ieta+1] && probemu.pt > 1.0 ) {
                                    vh_L3_qbpt_eta.at(i)[ieta]->Fill( res_qbpt, genWeight );
                                    vh_L3_pt_eta.at(i)[ieta]->Fill(   res_pt,   genWeight );
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // -- Save output and Clear memory
    // delete _chain_Ev;

    f_output->cd();

    h_nEvents->Write();
    h_nRuns->Write();

    h_gen_pt->Write();
    h_gen_eta->Write();
    h_gen_phi->Write();

    h_gen_acc_pt->Write();
    h_gen_acc_eta->Write();
    h_gen_acc_phi->Write();

    h_gen_hard_pt->Write();
    h_gen_hard_eta->Write();
    h_gen_hard_phi->Write();

    h_gen_hard_acc_pt->Write();
    h_gen_hard_acc_eta->Write();
    h_gen_hard_acc_phi->Write();

    TDirectory* dir0 = f_output->mkdir("Eff");
    dir0->cd();

    for(unsigned i=0; i<L3types.size(); ++i) {
        TDirectory* dir1 = dir0->mkdir(L3types.at(i));
        dir1->cd();

        for (unsigned irun = 0; irun < Runs_bin.size(); ++irun) {
            for (unsigned ieta = 0; ieta < Etas_bin.size(); ++ieta) {
                for(unsigned j=0; j<Eff_genpt_mins.size(); ++j) {
                    hc_Eff.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    // hc_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    // hc_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc2D_Eff.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc2D_Eff_L1SQ0.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc2D_Eff_L1DQ0.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc2D_Eff_L1SQ2.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    hc2D_Eff_L1DQ2.at(i).at(irun).at(ieta).at(j)->Save(dir1);                    
                    // hc2D_Eff_L1SQ22.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                    // hc2D_Eff_L1DQ8.at(i).at(irun).at(ieta).at(j)->Save(dir1);
                }
            }
        }
        dir0->cd();
    }

    TDirectory* dir1 = f_output->mkdir("Res");
    dir1->cd();

    for(unsigned i=0; i<L3types.size(); ++i) {
        for(int ipt=0; ipt<n_pt_bins; ++ipt) {
            vh_L3_qbpt_pt.at(i)[ipt]->Write();
            vh_L3_pt_pt.at(i)[ipt]->Write();
        }
        for(int ieta=0; ieta<n_eta_bins-1; ++ieta) {
            vh_L3_qbpt_eta.at(i)[ieta]->Write();
            vh_L3_pt_eta.at(i)[ieta]->Write();
        }
    }

    f_output->cd();
    f_output->Close();

    printRunTime(timer_total);
}


