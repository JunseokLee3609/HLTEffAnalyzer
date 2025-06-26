//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 14 13:24:37 2021 by ROOT version 6.24/00
// from TChain ntuple/ntuple
// found on file: ntuple_1-146.root
//////////////////////////////////////////////////////////

#ifndef MuonHLTNtupleRun3_h
#define MuonHLTNtupleRun3_h

#define ArrSize 50000

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include "vector"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Object
{
private:
    map<TString, double> vars;
    map<TString, TString> strvars;
    map<TString, vector<double>> vecs;

public:
    double pt;
    double eta;
    double phi;

    Object()
    {
        pt  = -99999.;
        eta = -99999.;
        phi = -99999.;
        vars["pt"] = -99999.;
        vars["eta"] = -99999.;
        vars["phi"] = -99999.;
    }

    Object( double _pt, double _eta, double _phi ): Object()
    {
        pt            = _pt;
        eta           = _eta;
        phi           = _phi;
        vars["pt"] = _pt;
        vars["eta"] = _eta;
        vars["phi"] = _phi;
    }

    void addVar( TString name, double value )
    {
        vars[name] = value;
    }

    void addStrVar( TString name, TString value )
    {
        strvars[name] = value;
    }

    void addVec( TString name, vector<double> value )
    {
        vecs[name] = value;
    }

    bool has( TString key )
    {
        return (vars.find(key) != vars.end());
    }

    bool hasstr( TString key )
    {
        return (strvars.find(key) != strvars.end());
    }

    bool hasvec( TString key )
    {
        return (vecs.find(key) != vecs.end());
    }

    double get( TString key )
    {
        if( vars.find(key) == vars.end() ) {
            //cout << key << " does not exist -> return -99999" << endl;
            //this->print();
            return -99999.0;
        }
        else {
            return vars[key];
        }
    }

    TString getstr( TString key )
    {
        if( strvars.find(key) == strvars.end() ) {
            //cout << key << " does not exist -> return XXXXX" << endl;
            return "XXXXX";
        }
        else {
            return strvars[key];
        }
    }

    vector<double> getvec( TString key )
    {
        if( vecs.find(key) == vecs.end() ) {
            cout << key << " does not exist -> return {}" << endl;
            this->print();
            return {};
        }
        else {
            return vecs[key];
        }
    }

    void print()
    {
        cout << endl;
        cout << (*this) << endl;
        for( auto& it: vars ) {
            cout << "\t" << it.first << ": " << it.second << endl;
        }
        for( auto& it: strvars ) {
            cout << "\t" << it.first << ": " << it.second << endl;
        }
    }

    Object clone()
    {
      Object out = Object();

      out.pt      = this->pt;
      out.eta     = this->eta;
      out.phi     = this->phi;
      out.vars    = this->vars;
      out.strvars = this->strvars;

      return out;
    }

    double reduceRange(double x) {
        double o2pi = 1. / (2. * M_PI);
        if (std::abs(x) <= double(M_PI))
            return x;
        double n = std::round(x * o2pi);
        return x - n * double(2. * M_PI);
    }

    double deltaPhi(double phi)
    {
        return reduceRange(this->phi - phi);
    }

    double deltaPhi(const Object& other)
    {
        return reduceRange(this->phi - other.phi);
    }

    double deltaR( double eta, double phi )
    {
      double dR = sqrt( (this->eta - eta)*(this->eta - eta)
                      + reduceRange(this->phi - phi)*reduceRange(this->phi - phi) );
      return dR;
    }

    double deltaR( const Object& other )
    {
      double dR = sqrt( (this->eta - other.eta)*(this->eta - other.eta)
                      + reduceRange(this->phi - other.phi)*reduceRange(this->phi - other.phi) );
      return dR;
    }

    bool matched( const Object& other, double dR_match = 0.1, double dpt_match = 1.e9 ) {
      double dR  = deltaR( other );
      double dpt = fabs( this->pt - other.pt ) / this->pt;
      return ( (dR < dR_match) && (dpt < dpt_match) );
    }

    int matched( vector<Object>& objects, vector<int>& map, double dR_match = 0.1, double dpt_match = 1.e9 ) {
      bool found     = false;
      double the_dR  = dR_match;
      int the_i = -1e9;

      unsigned n = objects.size();
      for(unsigned i=0; i<n; ++i) {
        if( map[i] > 0 )  continue;

        double dR  = deltaR( objects.at(i) );
        double dpt = fabs( this->pt - objects.at(i).pt ) / this->pt;
        if( (dR < the_dR) && (dpt < dpt_match) ) {
          found = true;
          the_dR = dR;
          the_i = i;
        }
      }
    //  int l1matched( vector<Object>& objects, vector<int>& map, double dR_match = 0.1, double dpt_match = 1.e9 ) {
    //   bool found     = false;
    //   double the_dR  = dR_match;
    //   int the_i = -1e9;

    //   unsigned n = objects.size();
    //   for(unsigned i=0; i<n; ++i) {
    //     if( map[i] > 0 )  continue;

    //     double dR  = this->getvec("l1tdr").at(i);
    //     double dpt = fabs( this->pt - objects.at(i).pt ) / this->pt;
    //     if( (dR < the_dR) && (dpt < dpt_match) ) {
    //       found = true;
    //       the_dR = dR;
    //       the_i = i;
    //     }
    //   }

      if(found) {
        map[the_i] = 1;
      }

      return the_i;
    }

    bool matched( vector<Object>& objects, double dR_match = 0.1, double dpt_match = 1.e9 ) {
      bool found     = false;

      unsigned n = objects.size();
      for(unsigned i=0; i<n; ++i) {
        double dR  = deltaR( objects.at(i) );
        double dpt = fabs( this->pt - objects.at(i).pt ) / this->pt;
        if( (dR < dR_match) && (dpt < dpt_match) ) {
          found = true;
          break;
        }
      }

      return found;
    }
    int L1matched( vector<Object>& objects, vector<int>& map, double dR_match = 0.1, double dpt_match = 1.e9 ) {//custom deft 0,1
      bool found     = false;
      double the_dR  = dR_match;
      int the_i = -1e9;

      unsigned n = objects.size();
      for(unsigned i=0; i<n; ++i) {
        if( map[i] > 0 )  continue;

        double dR  = deltaR( objects.at(i) );
        //custom
        //double dR  = this->getvec("l1tdr").at(i);
        double dpt = fabs( this->pt - objects.at(i).pt ) / this->pt;
        if(  dpt < dpt_match ) {
        //if( (dR < the_dR) && (dpt < dpt_match) ) {
          found = true;
          the_dR = dR;
          the_i = i;
        }
      }

      if(found) {
        map[the_i] = 1;
      }

      return the_i;
    }

    bool l1matched( double ptcut = 22.0, double qualcut = 11 ) {
      bool found     = false;

      int nl1t = this->get("nl1t");
      for(unsigned i=0; i<(unsigned)nl1t; ++i) {
        double pt  = this->getvec("l1tpt").at(i);
        double eta  = this->getvec("l1tpropeta").at(i);
        double phi  = this->getvec("l1tpropphi").at(i);
        double charge = this->getvec("l1tcharge").at(i);
        double qual  = this->getvec("l1tq").at(i);
        double dR  = this->getvec("l1tdr").at(i);

        if( pt > ptcut && qual > qualcut) {
          if( dR < 0.3) {
            found = true;
            break;
          }
        }
      }

      return found;
    }

    friend ostream& operator<<(ostream& os, const Object& obj) {
        os << "(" << obj.pt << ", " << obj.eta << ", " << obj.phi << ")";
        return os;
    }

    bool operator==(const Object& other) const {
      return (
        (fabs(this->pt - other.pt) / this->pt < 1.e-3) &&
        (fabs(this->eta - other.eta) < 1.e-3) &&
        (fabs(this->phi - other.phi) < 1.e-3)
      );
    }
};

class MuonHLTNtupleRun3 {
public :
    TChain          *fChain;   //!pointer to the analyzed TChain or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    MuonHLTNtupleRun3(TChain *tree=0, vector<TString> branch_tags = {});
    virtual ~MuonHLTNtupleRun3();
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TChain *tree);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);

    virtual void     PrintTemplate( TString head );

    vector<TString> branch_names;

    vector<Object> get_offlineMuons();
    vector<Object> get_GenParticles();
    vector<Object> get_TP(bool hasGen = false);
    vector<Object> get_L1Muons();
    vector<Object> get_L2Muons();
    // vector<Object> get_L3MuonsNoId();
    // vector<Object> get_L3Muons();
    vector<Object> get_iterL3OI();
    vector<Object> get_iterL3IOFromL2();
    vector<Object> get_iterL3FromL2();
    vector<Object> get_iterL3IOFromL1();
    vector<Object> get_iterL3MuonNoID();
    vector<Object> get_iterL3Muon();

    bool path_fired( TString path = "HLT_PPRefL1DoubleMu0_v2" );
    bool path_myFired( TString path = "HLT_PPRefL1DoubleMu0_v2" );
    vector<Object> get_HLTObjects( TString filter = "hltL3fL1fL1sSingleMuOpenL3Filtered3" );
    vector<Object> get_myHLTObjects( TString filter = "hltL1sDoubleMu0" );
    

    vector<Object> get_hltIterL3OIMuonTrackAssociated();
    vector<Object> get_hltIter0IterL3MuonTrackAssociated();
    vector<Object> get_hltIter2IterL3MuonTrackAssociated();
    vector<Object> get_hltIter0IterL3FromL1MuonTrackAssociated();
    vector<Object> get_hltIter2IterL3FromL1MuonTrackAssociated();
    vector<Object> get_hltIter2IterL3MuonMergedAssociated();
    vector<Object> get_hltIter2IterL3FromL1MuonMergedAssociated();
    vector<Object> get_hltIterL3MuonMergedAssociated();
    vector<Object> get_hltIterL3MuonAndMuonFromL1MergedAssociated();
    vector<Object> get_iterL3MuonNoIDTrackAssociated();
    vector<Object> get_iterL3MuonTrackAssociated();
    vector<Object> get_hltPixelTracksAssociated();
    vector<Object> get_hltPixelTracksInRegionL2Associated();
    vector<Object> get_hltPixelTracksInRegionL1Associated();
    vector<Object> get_hltPixelTracksForSeedsL3MuonAssociated();
    vector<Object> get_hltMuCtfTracksAssociated();
    vector<Object> get_hltDiMuonMergingAssociated();
    vector<Object> get_hltGlbTrkMuonTracksAssociated();
    vector<Object> get_tpTo_hltIterL3OIMuonTrackAssociated();
    vector<Object> get_tpTo_hltIter0IterL3MuonTrackAssociated();
    vector<Object> get_tpTo_hltIter2IterL3MuonTrackAssociated();
    vector<Object> get_tpTo_hltIter0IterL3FromL1MuonTrackAssociated();
    vector<Object> get_tpTo_hltIter2IterL3FromL1MuonTrackAssociated();
    vector<Object> get_tpTo_hltIter2IterL3MuonMergedAssociated();
    vector<Object> get_tpTo_hltIter2IterL3FromL1MuonMergedAssociated();
    vector<Object> get_tpTo_hltIterL3MuonMergedAssociated();
    vector<Object> get_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated();
    vector<Object> get_tpTo_iterL3MuonNoIDTrackAssociated();
    vector<Object> get_tpTo_iterL3MuonTrackAssociated();
    //vector<Object> get_tpTo_hltPixelTracksAssociated();
    vector<Object> get_tpTo_hltPixelTracksInRegionL2Associated();
    vector<Object> get_tpTo_hltPixelTracksInRegionL1Associated();
    vector<Object> get_tpTo_hltPixelTracksForSeedsL3MuonAssociated();
    vector<Object> get_tpTo_hltMuCtfTracksAssociated();
    vector<Object> get_tpTo_hltDiMuonMergingAssociated();
    vector<Object> get_tpTo_hltGlbTrkMuonTracksAssociated();

    // -- variables
        Bool_t          isRealData;
        Int_t           runNum;
        Int_t           lumiBlockNum;
        ULong64_t       eventNum;
        Int_t           nVertex;
        Double_t        bunchID;
        Double_t        instLumi;
        Double_t        dataPU;
        Double_t        dataPURMS;
        Double_t        bunchLumi;
        Double_t        offlineInstLumi;
        Double_t        offlineDataPU;
        Double_t        offlineDataPURMS;
        Double_t        offlineBunchLumi;
        Int_t           truePU;
        float           InstLumi;
        float           DataPU;
        Double_t        genEventWeight;
        Int_t           nGenParticle;
        Int_t           genParticle_ID[ArrSize];   //[nGenParticle]
        Int_t           genParticle_status[ArrSize];   //[nGenParticle]
        Int_t           genParticle_mother[ArrSize];   //[nGenParticle]
        Double_t        genParticle_pt[ArrSize];   //[nGenParticle]
        Double_t        genParticle_eta[ArrSize];   //[nGenParticle]
        Double_t        genParticle_phi[ArrSize];   //[nGenParticle]
        Double_t        genParticle_px[ArrSize];   //[nGenParticle]
        Double_t        genParticle_py[ArrSize];   //[nGenParticle]
        Double_t        genParticle_pz[ArrSize];   //[nGenParticle]
        Double_t        genParticle_energy[ArrSize];   //[nGenParticle]
        Double_t        genParticle_charge[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isPrompt[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isPromptFinalState[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isTauDecayProduct[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isPromptTauDecayProduct[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isDirectPromptTauDecayProductFinalState[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isHardProcess[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isLastCopy[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isLastCopyBeforeFSR[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isPromptDecayed[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isDecayedLeptonHadron[ArrSize];   //[nGenParticle]
        Int_t           genParticle_fromHardProcessBeforeFSR[ArrSize];   //[nGenParticle]
        Int_t           genParticle_fromHardProcessDecayed[ArrSize];   //[nGenParticle]
        Int_t           genParticle_fromHardProcessFinalState[ArrSize];   //[nGenParticle]
        Int_t           genParticle_isMostlyLikePythia6Status3[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1pt[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1eta[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1phi[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1charge[ArrSize];   //[nGenParticle]
        Int_t           genParticle_l1q[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1dr[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1ptByQ[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1etaByQ[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1phiByQ[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1chargeByQ[ArrSize];   //[nGenParticle]
        Int_t           genParticle_l1qByQ[ArrSize];   //[nGenParticle]
        Double_t        genParticle_l1drByQ[ArrSize];   //[nGenParticle]
        vector<string>  *vec_firedTrigger;
        vector<string>  *vec_filterName;
        vector<double>  *vec_HLTObj_pt;
        vector<double>  *vec_HLTObj_eta;
        vector<double>  *vec_HLTObj_phi;
        vector<string>  *vec_myFiredTrigger;
        vector<string>  *vec_myFilterName;
        vector<double>  *vec_myHLTObj_pt;
        vector<double>  *vec_myHLTObj_eta;
        vector<double>  *vec_myHLTObj_phi;
        Int_t           nMuon;
        Double_t        muon_pt[ArrSize];   //[nMuon]
        Double_t        muon_eta[ArrSize];   //[nMuon]
        Double_t        muon_phi[ArrSize];   //[nMuon]
        Double_t        muon_px[ArrSize];   //[nMuon]
        Double_t        muon_py[ArrSize];   //[nMuon]
        Double_t        muon_pz[ArrSize];   //[nMuon]
        Double_t        muon_dB[ArrSize];   //[nMuon]
        Double_t        muon_charge[ArrSize];   //[nMuon]
        Int_t           muon_isGLB[ArrSize];   //[nMuon]
        Int_t           muon_isSTA[ArrSize];   //[nMuon]
        Int_t           muon_isTRK[ArrSize];   //[nMuon]
        Int_t           muon_isPF[ArrSize];   //[nMuon]
        Int_t           muon_isTight[ArrSize];   //[nMuon]
        Int_t           muon_isMedium[ArrSize];   //[nMuon]
        Int_t           muon_isLoose[ArrSize];   //[nMuon]
        Int_t           muon_isHighPt[ArrSize];   //[nMuon]
        Int_t           muon_isHighPtNew[ArrSize];   //[nMuon]
        Int_t           muon_isSoft[ArrSize];   //[nMuon]
        Double_t        muon_iso03_sumPt[ArrSize];   //[nMuon]
        Double_t        muon_iso03_hadEt[ArrSize];   //[nMuon]
        Double_t        muon_iso03_emEt[ArrSize];   //[nMuon]
        Double_t        muon_PFIso03_charged[ArrSize];   //[nMuon]
        Double_t        muon_PFIso03_neutral[ArrSize];   //[nMuon]
        Double_t        muon_PFIso03_photon[ArrSize];   //[nMuon]
        Double_t        muon_PFIso03_sumPU[ArrSize];   //[nMuon]
        Double_t        muon_PFIso04_charged[ArrSize];   //[nMuon]
        Double_t        muon_PFIso04_neutral[ArrSize];   //[nMuon]
        Double_t        muon_PFIso04_photon[ArrSize];   //[nMuon]
        Double_t        muon_PFIso04_sumPU[ArrSize];   //[nMuon]
        Double_t        muon_PFCluster03_ECAL[ArrSize];   //[nMuon]
        Double_t        muon_PFCluster03_HCAL[ArrSize];   //[nMuon]
        Double_t        muon_PFCluster04_ECAL[ArrSize];   //[nMuon]
        Double_t        muon_PFCluster04_HCAL[ArrSize];   //[nMuon]
        Double_t        muon_inner_trkChi2[ArrSize];
        Double_t        muon_inner_validFraction[ArrSize];
        Int_t           muon_inner_trackerLayers[ArrSize];
        Int_t           muon_inner_trackerHits[ArrSize];
        Int_t           muon_inner_lostTrackerHits[ArrSize];
        Int_t           muon_inner_lostTrackerHitsIn[ArrSize];
        Int_t           muon_inner_lostTrackerHitsOut[ArrSize];
        Int_t           muon_inner_lostPixelHits[ArrSize];
        Int_t           muon_inner_lostPixelBarrelHits[ArrSize];
        Int_t           muon_inner_lostPixelEndcapHits[ArrSize];
        Int_t           muon_inner_lostStripHits[ArrSize];
        Int_t           muon_inner_lostStripTIBHits[ArrSize];
        Int_t           muon_inner_lostStripTIDHits[ArrSize];
        Int_t           muon_inner_lostStripTOBHits[ArrSize];
        Int_t           muon_inner_lostStripTECHits[ArrSize];
        Int_t           muon_inner_pixelLayers[ArrSize];
        Int_t           muon_inner_pixelHits[ArrSize];
        Int_t           muon_global_muonHits[ArrSize];
        Double_t        muon_global_trkChi2[ArrSize];
        Int_t           muon_global_trackerLayers[ArrSize];
        Int_t           muon_global_trackerHits[ArrSize];
        Double_t        muon_momentumChi2[ArrSize];
        Double_t        muon_positionChi2[ArrSize];
        Double_t        muon_glbKink[ArrSize];
        Double_t        muon_glbTrackProbability[ArrSize];
        Double_t        muon_globalDeltaEtaPhi[ArrSize];
        Double_t        muon_localDistance[ArrSize];
        Double_t        muon_staRelChi2[ArrSize];
        Int_t           muon_tightMatch[ArrSize];
        Double_t        muon_trkKink[ArrSize];
        Double_t        muon_trkRelChi2[ArrSize];
        Double_t        muon_segmentCompatibility[ArrSize];
        Double_t        muon_pt_tuneP[ArrSize];   //[nMuon]
        Double_t        muon_ptError_tuneP[ArrSize];   //[nMuon]
        Double_t        muon_dxyVTX_best[ArrSize];   //[nMuon]
        Double_t        muon_dzVTX_best[ArrSize];   //[nMuon]
        Int_t           muon_nMatchedStation[ArrSize];   //[nMuon]
        Int_t           muon_nMatchedRPCLayer[ArrSize];   //[nMuon]
        Int_t           muon_stationMask[ArrSize];   //[nMuon]
        double          muon_dxy_bs[ArrSize];   //[nMuon]
        double          muon_dxyError_bs[ArrSize];   //[nMuon]
        double          muon_dz_bs[ArrSize];   //[nMuon]
        double          muon_dzError[ArrSize];   //[nMuon]
        double          muon_IPSig[ArrSize];   //[nMuon]
        Double_t        muon_l1pt[ArrSize];   //[nMuon]
        Double_t        muon_l1eta[ArrSize];   //[nMuon]
        Double_t        muon_l1phi[ArrSize];   //[nMuon]
        Double_t        muon_l1charge[ArrSize];   //[nMuon]
        Int_t           muon_l1q[ArrSize];   //[nMuon]
        Double_t        muon_l1dr[ArrSize];   //[nMuon]
        Double_t        muon_l1ptByQ[ArrSize];   //[nMuon]
        Double_t        muon_l1etaByQ[ArrSize];   //[nMuon]
        Double_t        muon_l1phiByQ[ArrSize];   //[nMuon]
        Double_t        muon_l1chargeByQ[ArrSize];   //[nMuon]
        Int_t           muon_l1qByQ[ArrSize];   //[nMuon]
        Double_t        muon_l1drByQ[ArrSize];   //[nMuon]

        Int_t           muon_nl1t[ArrSize];   //[nMuon]
        vector<vector<double>>  *muon_l1tpt;
        vector<vector<double>>  *muon_l1teta;
        vector<vector<double>>  *muon_l1tpropeta;
        vector<vector<double>>  *muon_l1tphi;
        vector<vector<double>>  *muon_l1tpropphi;
        vector<vector<double>>  *muon_l1tcharge;
        vector<vector<double>>  *muon_l1tq;
        vector<vector<double>>  *muon_l1tdr;

        Int_t           nL3Muon;
        Double_t        L3Muon_pt[ArrSize];   //[nL3Muon]
        Double_t        L3Muon_eta[ArrSize];   //[nL3Muon]
        Double_t        L3Muon_phi[ArrSize];   //[nL3Muon]
        Double_t        L3Muon_charge[ArrSize];   //[nL3Muon]
        Double_t        L3Muon_trkPt[ArrSize];   //[nL3Muon]
        Int_t           nL2Muon;
        Double_t        L2Muon_pt[ArrSize];   //[nL2Muon]
        Double_t        L2Muon_eta[ArrSize];   //[nL2Muon]
        Double_t        L2Muon_phi[ArrSize];   //[nL2Muon]
        Double_t        L2Muon_charge[ArrSize];   //[nL2Muon]
        Double_t        L2Muon_trkPt[ArrSize];   //[nL2Muon]
        Int_t           nTkMuon;
        Double_t        TkMuon_pt[ArrSize];   //[nTkMuon]
        Double_t        TkMuon_eta[ArrSize];   //[nTkMuon]
        Double_t        TkMuon_phi[ArrSize];   //[nTkMuon]
        Double_t        TkMuon_charge[ArrSize];   //[nTkMuon]
        Double_t        TkMuon_trkPt[ArrSize];   //[nTkMuon]
        Int_t           nL1Muon;
        Double_t        L1Muon_pt[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_eta[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_phi[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_charge[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_quality[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_etaAtVtx[ArrSize];   //[nL1Muon]
        Double_t        L1Muon_phiAtVtx[ArrSize];   //[nL1Muon]
        Int_t           nIterL3OI;
        Double_t        iterL3OI_inner_pt[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_inner_eta[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_inner_phi[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_inner_charge[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_inner_trkChi2[ArrSize];
        Double_t        iterL3OI_inner_validFraction[ArrSize];
        Int_t           iterL3OI_inner_trackerLayers[ArrSize];
        Int_t           iterL3OI_inner_trackerHits[ArrSize];
        Int_t           iterL3OI_inner_lostTrackerHits[ArrSize];
        Int_t           iterL3OI_inner_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3OI_inner_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3OI_inner_lostPixelHits[ArrSize];
        Int_t           iterL3OI_inner_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3OI_inner_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3OI_inner_lostStripHits[ArrSize];
        Int_t           iterL3OI_inner_lostStripTIBHits[ArrSize];
        Int_t           iterL3OI_inner_lostStripTIDHits[ArrSize];
        Int_t           iterL3OI_inner_lostStripTOBHits[ArrSize];
        Int_t           iterL3OI_inner_lostStripTECHits[ArrSize];
        Int_t           iterL3OI_inner_pixelLayers[ArrSize];
        Int_t           iterL3OI_inner_pixelHits[ArrSize];
        Double_t        iterL3OI_outer_pt[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_outer_eta[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_outer_phi[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_outer_charge[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_global_pt[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_global_eta[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_global_phi[ArrSize];   //[nIterL3OI]
        Double_t        iterL3OI_global_charge[ArrSize];   //[nIterL3OI]
        Int_t           iterL3OI_global_muonHits[ArrSize];
        Double_t        iterL3OI_global_trkChi2[ArrSize];
        Int_t           iterL3OI_global_trackerLayers[ArrSize];
        Int_t           iterL3OI_global_trackerHits[ArrSize];
        Int_t           nIterL3IOFromL2;
        Double_t        iterL3IOFromL2_inner_pt[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_inner_eta[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_inner_phi[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_inner_charge[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_inner_trkChi2[ArrSize];
        Double_t        iterL3IOFromL2_inner_validFraction[ArrSize];
        Int_t           iterL3IOFromL2_inner_trackerLayers[ArrSize];
        Int_t           iterL3IOFromL2_inner_trackerHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostTrackerHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostPixelHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostStripHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostStripTIBHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostStripTIDHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostStripTOBHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_lostStripTECHits[ArrSize];
        Int_t           iterL3IOFromL2_inner_pixelLayers[ArrSize];
        Int_t           iterL3IOFromL2_inner_pixelHits[ArrSize];
        Double_t        iterL3IOFromL2_outer_pt[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_outer_eta[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_outer_phi[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_outer_charge[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_global_pt[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_global_eta[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_global_phi[ArrSize];   //[nIterL3IOFromL2]
        Double_t        iterL3IOFromL2_global_charge[ArrSize];   //[nIterL3IOFromL2]
        Int_t           iterL3IOFromL2_global_muonHits[ArrSize];
        Double_t        iterL3IOFromL2_global_trkChi2[ArrSize];
        Int_t           iterL3IOFromL2_global_trackerLayers[ArrSize];
        Int_t           iterL3IOFromL2_global_trackerHits[ArrSize];
        Int_t           nIterL3FromL2;
        Double_t        iterL3FromL2_inner_pt[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_inner_eta[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_inner_phi[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_inner_charge[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_inner_trkChi2[ArrSize];
        Double_t        iterL3FromL2_inner_validFraction[ArrSize];
        Int_t           iterL3FromL2_inner_trackerLayers[ArrSize];
        Int_t           iterL3FromL2_inner_trackerHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostTrackerHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3FromL2_inner_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3FromL2_inner_lostPixelHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostStripHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostStripTIBHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostStripTIDHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostStripTOBHits[ArrSize];
        Int_t           iterL3FromL2_inner_lostStripTECHits[ArrSize];
        Int_t           iterL3FromL2_inner_pixelLayers[ArrSize];
        Int_t           iterL3FromL2_inner_pixelHits[ArrSize];
        Double_t        iterL3FromL2_outer_pt[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_outer_eta[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_outer_phi[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_outer_charge[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_global_pt[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_global_eta[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_global_phi[ArrSize];   //[nIterL3FromL2]
        Double_t        iterL3FromL2_global_charge[ArrSize];   //[nIterL3FromL2]
        Int_t           iterL3FromL2_global_muonHits[ArrSize];
        Double_t        iterL3FromL2_global_trkChi2[ArrSize];
        Int_t           iterL3FromL2_global_trackerLayers[ArrSize];
        Int_t           iterL3FromL2_global_trackerHits[ArrSize];
        Int_t           nIterL3IOFromL1;
        Double_t        iterL3IOFromL1_pt[ArrSize];   //[nIterL3IOFromL1]
        Double_t        iterL3IOFromL1_eta[ArrSize];   //[nIterL3IOFromL1]
        Double_t        iterL3IOFromL1_phi[ArrSize];   //[nIterL3IOFromL1]
        Double_t        iterL3IOFromL1_charge[ArrSize];   //[nIterL3IOFromL1]
        Int_t           iterL3IOFromL1_muonHits[ArrSize];
        Double_t        iterL3IOFromL1_trkChi2[ArrSize];
        Double_t        iterL3IOFromL1_validFraction[ArrSize];
        Int_t           iterL3IOFromL1_trackerLayers[ArrSize];
        Int_t           iterL3IOFromL1_trackerHits[ArrSize];
        Int_t           iterL3IOFromL1_lostTrackerHits[ArrSize];
        Int_t           iterL3IOFromL1_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3IOFromL1_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3IOFromL1_lostPixelHits[ArrSize];
        Int_t           iterL3IOFromL1_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3IOFromL1_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3IOFromL1_lostStripHits[ArrSize];
        Int_t           iterL3IOFromL1_lostStripTIBHits[ArrSize];
        Int_t           iterL3IOFromL1_lostStripTIDHits[ArrSize];
        Int_t           iterL3IOFromL1_lostStripTOBHits[ArrSize];
        Int_t           iterL3IOFromL1_lostStripTECHits[ArrSize];
        Int_t           iterL3IOFromL1_pixelLayers[ArrSize];
        Int_t           iterL3IOFromL1_pixelHits[ArrSize];
        Int_t           nIterL3MuonNoID;
        Double_t        iterL3MuonNoID_pt[ArrSize];   //[nIterL3MuonNoID]
        Double_t        iterL3MuonNoID_innerPt[ArrSize];   //[nIterL3MuonNoID]
        Double_t        iterL3MuonNoID_eta[ArrSize];   //[nIterL3MuonNoID]
        Double_t        iterL3MuonNoID_phi[ArrSize];   //[nIterL3MuonNoID]
        Double_t        iterL3MuonNoID_charge[ArrSize];   //[nIterL3MuonNoID]
        Int_t           iterL3MuonNoID_isGLB[ArrSize];   //[nIterL3MuonNoID]
        Int_t           iterL3MuonNoID_isSTA[ArrSize];   //[nIterL3MuonNoID]
        Int_t           iterL3MuonNoID_isTRK[ArrSize];   //[nIterL3MuonNoID]
        Double_t        iterL3MuonNoID_inner_trkChi2[ArrSize];
        Double_t        iterL3MuonNoID_inner_validFraction[ArrSize];
        Int_t           iterL3MuonNoID_inner_trackerLayers[ArrSize];
        Int_t           iterL3MuonNoID_inner_trackerHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostTrackerHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostPixelHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostStripHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostStripTIBHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostStripTIDHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostStripTOBHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_lostStripTECHits[ArrSize];
        Int_t           iterL3MuonNoID_inner_pixelLayers[ArrSize];
        Int_t           iterL3MuonNoID_inner_pixelHits[ArrSize];
        Int_t           iterL3MuonNoID_global_muonHits[ArrSize];
        Double_t        iterL3MuonNoID_global_trkChi2[ArrSize];
        Int_t           iterL3MuonNoID_global_trackerLayers[ArrSize];
        Int_t           iterL3MuonNoID_global_trackerHits[ArrSize];
        Double_t        iterL3MuonNoID_momentumChi2[ArrSize];
        Double_t        iterL3MuonNoID_positionChi2[ArrSize];
        Double_t        iterL3MuonNoID_glbKink[ArrSize];
        Double_t        iterL3MuonNoID_glbTrackProbability[ArrSize];
        Double_t        iterL3MuonNoID_globalDeltaEtaPhi[ArrSize];
        Double_t        iterL3MuonNoID_localDistance[ArrSize];
        Double_t        iterL3MuonNoID_staRelChi2[ArrSize];
        Int_t           iterL3MuonNoID_tightMatch[ArrSize];
        Double_t        iterL3MuonNoID_trkKink[ArrSize];
        Double_t        iterL3MuonNoID_trkRelChi2[ArrSize];
        Double_t        iterL3MuonNoID_segmentCompatibility[ArrSize];
        Int_t           nIterL3Muon;
        Double_t        iterL3Muon_pt[ArrSize];   //[nIterL3Muon]
        Double_t        iterL3Muon_innerPt[ArrSize];   //[nIterL3Muon]
        Double_t        iterL3Muon_eta[ArrSize];   //[nIterL3Muon]
        Double_t        iterL3Muon_phi[ArrSize];   //[nIterL3Muon]
        Double_t        iterL3Muon_charge[ArrSize];   //[nIterL3Muon]
        Int_t           iterL3Muon_isGLB[ArrSize];   //[nIterL3Muon]
        Int_t           iterL3Muon_isSTA[ArrSize];   //[nIterL3Muon]
        Int_t           iterL3Muon_isTRK[ArrSize];   //[nIterL3Muon]
        Double_t        iterL3Muon_inner_trkChi2[ArrSize];
        Double_t        iterL3Muon_inner_validFraction[ArrSize];
        Int_t           iterL3Muon_inner_trackerLayers[ArrSize];
        Int_t           iterL3Muon_inner_trackerHits[ArrSize];
        Int_t           iterL3Muon_inner_lostTrackerHits[ArrSize];
        Int_t           iterL3Muon_inner_lostTrackerHitsIn[ArrSize];
        Int_t           iterL3Muon_inner_lostTrackerHitsOut[ArrSize];
        Int_t           iterL3Muon_inner_lostPixelHits[ArrSize];
        Int_t           iterL3Muon_inner_lostPixelBarrelHits[ArrSize];
        Int_t           iterL3Muon_inner_lostPixelEndcapHits[ArrSize];
        Int_t           iterL3Muon_inner_lostStripHits[ArrSize];
        Int_t           iterL3Muon_inner_lostStripTIBHits[ArrSize];
        Int_t           iterL3Muon_inner_lostStripTIDHits[ArrSize];
        Int_t           iterL3Muon_inner_lostStripTOBHits[ArrSize];
        Int_t           iterL3Muon_inner_lostStripTECHits[ArrSize];
        Int_t           iterL3Muon_inner_pixelLayers[ArrSize];
        Int_t           iterL3Muon_inner_pixelHits[ArrSize];
        Int_t           iterL3Muon_global_muonHits[ArrSize];
        Double_t        iterL3Muon_global_trkChi2[ArrSize];
        Int_t           iterL3Muon_global_trackerLayers[ArrSize];
        Int_t           iterL3Muon_global_trackerHits[ArrSize];
        Double_t        iterL3Muon_momentumChi2[ArrSize];
        Double_t        iterL3Muon_positionChi2[ArrSize];
        Double_t        iterL3Muon_glbKink[ArrSize];
        Double_t        iterL3Muon_glbTrackProbability[ArrSize];
        Double_t        iterL3Muon_globalDeltaEtaPhi[ArrSize];
        Double_t        iterL3Muon_localDistance[ArrSize];
        Double_t        iterL3Muon_staRelChi2[ArrSize];
        Int_t           iterL3Muon_tightMatch[ArrSize];
        Double_t        iterL3Muon_trkKink[ArrSize];
        Double_t        iterL3Muon_trkRelChi2[ArrSize];
        Double_t        iterL3Muon_segmentCompatibility[ArrSize];
        Int_t           nTP;
        vector<float>   *TP_charge;
        vector<int>     *TP_pdgId;
        vector<double>  *TP_energy;
        vector<double>  *TP_pt;
        vector<double>  *TP_eta;
        vector<double>  *TP_phi;
        vector<double>  *TP_parentVx;
        vector<double>  *TP_parentVy;
        vector<double>  *TP_parentVz;
        vector<int>     *TP_status;
        vector<int>     *TP_numberOfHits;
        vector<int>     *TP_numberOfTrackerHits;
        vector<int>     *TP_numberOfTrackerLayers;
        vector<float>   *TP_gen_charge;
        vector<int>     *TP_gen_pdgId;
        vector<double>  *TP_gen_pt;
        vector<double>  *TP_gen_eta;
        vector<double>  *TP_gen_phi;
        vector<double>  *TP_bestMatchTrk_pt;
        vector<double>  *TP_bestMatchTrk_eta;
        vector<double>  *TP_bestMatchTrk_phi;
        vector<int>     *TP_bestMatchTrk_charge;
        vector<double>  *TP_bestMatchTrk_quality;
        vector<int>     *TP_bestMatchTrk_NValidHits;
        Int_t           nhltIterL3MuonTrimmedPixelVertices;
        vector<int>     *hltIterL3MuonTrimmedPixelVertices_isValid;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_chi2;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_ndof;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_nTracks;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_x;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_xerr;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_y;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_yerr;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_z;
        vector<double>  *hltIterL3MuonTrimmedPixelVertices_zerr;
        Int_t           nhltIterL3FromL1MuonTrimmedPixelVertices;
        vector<int>     *hltIterL3FromL1MuonTrimmedPixelVertices_isValid;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_chi2;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_ndof;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_nTracks;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_x;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_xerr;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_y;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_yerr;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_z;
        vector<double>  *hltIterL3FromL1MuonTrimmedPixelVertices_zerr;
        Int_t           nhltIterL3OIMuonTrackAssociated;
        vector<double>  *hltIterL3OIMuonTrackAssociated_pt;
        vector<double>  *hltIterL3OIMuonTrackAssociated_eta;
        vector<double>  *hltIterL3OIMuonTrackAssociated_phi;
        vector<int>     *hltIterL3OIMuonTrackAssociated_charge;
        vector<int>     *hltIterL3OIMuonTrackAssociated_matchedL3;
        vector<int>     *hltIterL3OIMuonTrackAssociated_matchedL3NoId;
        vector<float>   *hltIterL3OIMuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIterL3OIMuonTrackAssociated_bestMatchTP_status;
        vector<int>     *hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIterL3OIMuonTrackAssociated_matchedTPsize;
        vector<float>   *hltIterL3OIMuonTrackAssociated_mva;
        Int_t           ntpTo_hltIterL3OIMuonTrackAssociated;
        vector<float>   *tpTo_hltIterL3OIMuonTrackAssociated_charge;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_pdgId;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_energy;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_pt;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_eta;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_phi;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_parentVx;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_parentVy;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_parentVz;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_status;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIterL3OIMuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIter0IterL3MuonTrackAssociated;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_pt;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_eta;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_phi;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_charge;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_matchedL3;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_matchedL3NoId;
        vector<float>   *hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_bestMatchTP_status;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIter0IterL3MuonTrackAssociated_matchedTPsize;
        vector<float>   *hltIter0IterL3MuonTrackAssociated_mva;
        Int_t           ntpTo_hltIter0IterL3MuonTrackAssociated;
        vector<float>   *tpTo_hltIter0IterL3MuonTrackAssociated_charge;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_pdgId;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_energy;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_pt;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_eta;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_phi;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_parentVx;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_parentVy;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_parentVz;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_status;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIter2IterL3MuonTrackAssociated;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_pt;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_eta;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_phi;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_charge;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_matchedL3;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_matchedL3NoId;
        vector<float>   *hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_bestMatchTP_status;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIter2IterL3MuonTrackAssociated_matchedTPsize;
        vector<float>   *hltIter2IterL3MuonTrackAssociated_mva;
        Int_t           ntpTo_hltIter2IterL3MuonTrackAssociated;
        vector<float>   *tpTo_hltIter2IterL3MuonTrackAssociated_charge;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_pdgId;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_energy;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_pt;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_eta;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_phi;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_parentVx;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_parentVy;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_parentVz;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_status;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIter0IterL3FromL1MuonTrackAssociated;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_pt;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_eta;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_phi;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_charge;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_matchedL3;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId;
        vector<float>   *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize;
        vector<float>   *hltIter0IterL3FromL1MuonTrackAssociated_mva;
        Int_t           ntpTo_hltIter0IterL3FromL1MuonTrackAssociated;
        vector<float>   *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIter2IterL3FromL1MuonTrackAssociated;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_pt;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_eta;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_phi;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_charge;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_matchedL3;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId;
        vector<float>   *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize;
        vector<float>   *hltIter2IterL3FromL1MuonTrackAssociated_mva;
        Int_t           ntpTo_hltIter2IterL3FromL1MuonTrackAssociated;
        vector<float>   *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIterL3MuonMergedAssociated;
        vector<double>  *hltIterL3MuonMergedAssociated_pt;
        vector<double>  *hltIterL3MuonMergedAssociated_eta;
        vector<double>  *hltIterL3MuonMergedAssociated_phi;
        vector<int>     *hltIterL3MuonMergedAssociated_charge;
        vector<int>     *hltIterL3MuonMergedAssociated_matchedL3;
        vector<int>     *hltIterL3MuonMergedAssociated_matchedL3NoId;
        vector<float>   *hltIterL3MuonMergedAssociated_bestMatchTP_charge;
        vector<int>     *hltIterL3MuonMergedAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_energy;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_pt;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_eta;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_phi;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIterL3MuonMergedAssociated_bestMatchTP_status;
        vector<int>     *hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIterL3MuonMergedAssociated_matchedTPsize;
        vector<float>   *hltIterL3MuonMergedAssociated_mva;
        Int_t           ntpTo_hltIterL3MuonMergedAssociated;
        vector<float>   *tpTo_hltIterL3MuonMergedAssociated_charge;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_pdgId;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_energy;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_pt;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_eta;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_phi;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_parentVx;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_parentVy;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_parentVz;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_status;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_numberOfHits;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIterL3MuonMergedAssociated_gen_charge;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_gen_pt;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_gen_eta;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_gen_phi;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits;
        Int_t           nhltIterL3MuonAndMuonFromL1MergedAssociated;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_pt;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_eta;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_phi;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_charge;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId;
        vector<float>   *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize;
        vector<float>   *hltIterL3MuonAndMuonFromL1MergedAssociated_mva;
        Int_t           ntpTo_hltIterL3MuonAndMuonFromL1MergedAssociated;
        vector<float>   *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits;
        Int_t           niterL3MuonNoIDTrackAssociated;
        vector<double>  *iterL3MuonNoIDTrackAssociated_pt;
        vector<double>  *iterL3MuonNoIDTrackAssociated_eta;
        vector<double>  *iterL3MuonNoIDTrackAssociated_phi;
        vector<int>     *iterL3MuonNoIDTrackAssociated_charge;
        vector<int>     *iterL3MuonNoIDTrackAssociated_matchedL3;
        vector<int>     *iterL3MuonNoIDTrackAssociated_matchedL3NoId;
        vector<float>   *iterL3MuonNoIDTrackAssociated_bestMatchTP_charge;
        vector<int>     *iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_energy;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_pt;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_eta;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_phi;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *iterL3MuonNoIDTrackAssociated_bestMatchTP_status;
        vector<int>     *iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *iterL3MuonNoIDTrackAssociated_matchedTPsize;
        vector<float>   *iterL3MuonNoIDTrackAssociated_mva;
        Int_t           ntpTo_iterL3MuonNoIDTrackAssociated;
        vector<float>   *tpTo_iterL3MuonNoIDTrackAssociated_charge;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_pdgId;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_energy;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_pt;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_eta;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_phi;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_parentVx;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_parentVy;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_parentVz;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_status;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_iterL3MuonNoIDTrackAssociated_gen_charge;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_gen_pt;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_gen_eta;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_gen_phi;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits;
        Int_t           niterL3MuonTrackAssociated;
        vector<double>  *iterL3MuonTrackAssociated_pt;
        vector<double>  *iterL3MuonTrackAssociated_eta;
        vector<double>  *iterL3MuonTrackAssociated_phi;
        vector<int>     *iterL3MuonTrackAssociated_charge;
        vector<int>     *iterL3MuonTrackAssociated_matchedL3;
        vector<int>     *iterL3MuonTrackAssociated_matchedL3NoId;
        vector<float>   *iterL3MuonTrackAssociated_bestMatchTP_charge;
        vector<int>     *iterL3MuonTrackAssociated_bestMatchTP_pdgId;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_energy;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_pt;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_eta;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_phi;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_parentVx;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_parentVy;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_parentVz;
        vector<int>     *iterL3MuonTrackAssociated_bestMatchTP_status;
        vector<int>     *iterL3MuonTrackAssociated_bestMatchTP_numberOfHits;
        vector<int>     *iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *iterL3MuonTrackAssociated_bestMatchTP_sharedFraction;
        vector<int>     *iterL3MuonTrackAssociated_matchedTPsize;
        vector<float>   *iterL3MuonTrackAssociated_mva;
        Int_t           ntpTo_iterL3MuonTrackAssociated;
        vector<float>   *tpTo_iterL3MuonTrackAssociated_charge;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_pdgId;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_energy;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_pt;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_eta;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_phi;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_parentVx;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_parentVy;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_parentVz;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_status;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_numberOfHits;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_iterL3MuonTrackAssociated_gen_charge;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_gen_pdgId;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_gen_pt;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_gen_eta;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_gen_phi;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits;


        Int_t           nhltPixelTracksAssociated;
        vector<double>  *hltPixelTracksAssociated_pt;
        vector<double>  *hltPixelTracksAssociated_eta;
        vector<double>  *hltPixelTracksAssociated_phi;
        vector<int>     *hltPixelTracksAssociated_charge;
        vector<int>     *hltPixelTracksAssociated_matchedL3;
        vector<int>     *hltPixelTracksAssociated_matchedL3NoId;
        vector<float>   *hltPixelTracksAssociated_bestMatchTP_charge;
        vector<int>     *hltPixelTracksAssociated_bestMatchTP_pdgId;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_energy;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_pt;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_eta;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_phi;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_parentVx;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_parentVy;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_parentVz;
        vector<int>     *hltPixelTracksAssociated_bestMatchTP_status;
        vector<int>     *hltPixelTracksAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltPixelTracksAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltPixelTracksAssociated_matchedTPsize;
        vector<float>   *hltPixelTracksAssociated_mva;


        Int_t           nhltPixelTracksInRegionL2Associated;
        vector<double>  *hltPixelTracksInRegionL2Associated_pt;
        vector<double>  *hltPixelTracksInRegionL2Associated_eta;
        vector<double>  *hltPixelTracksInRegionL2Associated_phi;
        vector<int>     *hltPixelTracksInRegionL2Associated_charge;
        vector<int>     *hltPixelTracksInRegionL2Associated_matchedL3;
        vector<int>     *hltPixelTracksInRegionL2Associated_matchedL3NoId;
        vector<float>   *hltPixelTracksInRegionL2Associated_bestMatchTP_charge;
        vector<int>     *hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_energy;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_pt;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_eta;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_phi;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz;
        vector<int>     *hltPixelTracksInRegionL2Associated_bestMatchTP_status;
        vector<int>     *hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits;
        vector<int>     *hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction;
        vector<int>     *hltPixelTracksInRegionL2Associated_matchedTPsize;
        vector<float>   *hltPixelTracksInRegionL2Associated_mva;
        Int_t           ntpTo_hltPixelTracksInRegionL2Associated;
        vector<float>   *tpTo_hltPixelTracksInRegionL2Associated_charge;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_pdgId;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_energy;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_phi;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_parentVx;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_parentVy;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_parentVz;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_status;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_numberOfHits;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltPixelTracksInRegionL2Associated_gen_charge;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_gen_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_gen_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_gen_phi;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits;


        Int_t           nhltPixelTracksInRegionL1Associated;
        vector<double>  *hltPixelTracksInRegionL1Associated_pt;
        vector<double>  *hltPixelTracksInRegionL1Associated_eta;
        vector<double>  *hltPixelTracksInRegionL1Associated_phi;
        vector<int>     *hltPixelTracksInRegionL1Associated_charge;
        vector<int>     *hltPixelTracksInRegionL1Associated_matchedL3;
        vector<int>     *hltPixelTracksInRegionL1Associated_matchedL3NoId;
        vector<float>   *hltPixelTracksInRegionL1Associated_bestMatchTP_charge;
        vector<int>     *hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_energy;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_pt;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_eta;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_phi;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz;
        vector<int>     *hltPixelTracksInRegionL1Associated_bestMatchTP_status;
        vector<int>     *hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits;
        vector<int>     *hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction;
        vector<int>     *hltPixelTracksInRegionL1Associated_matchedTPsize;
        vector<float>   *hltPixelTracksInRegionL1Associated_mva;
        Int_t           ntpTo_hltPixelTracksInRegionL1Associated;
        vector<float>   *tpTo_hltPixelTracksInRegionL1Associated_charge;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_pdgId;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_energy;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_phi;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_parentVx;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_parentVy;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_parentVz;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_status;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_numberOfHits;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltPixelTracksInRegionL1Associated_gen_charge;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_gen_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_gen_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_gen_phi;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits;


        Int_t           nhltPixelTracksForSeedsL3MuonAssociated;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_pt;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_eta;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_phi;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_charge;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_matchedL3;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId;
        vector<float>   *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize;
        vector<float>   *hltPixelTracksForSeedsL3MuonAssociated_mva;
        Int_t           ntpTo_hltPixelTracksForSeedsL3MuonAssociated;
        vector<float>   *tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_status;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits;

        Int_t           nhltGlbTrkMuonTracksAssociated;
        vector<double>  *hltGlbTrkMuonTracksAssociated_pt;
        vector<double>  *hltGlbTrkMuonTracksAssociated_eta;
        vector<double>  *hltGlbTrkMuonTracksAssociated_phi;
        vector<int>     *hltGlbTrkMuonTracksAssociated_charge;
        vector<int>     *hltGlbTrkMuonTracksAssociated_matchedL3;
        vector<int>     *hltGlbTrkMuonTracksAssociated_matchedL3NoId;
        vector<float>   *hltGlbTrkMuonTracksAssociated_bestMatchTP_charge;
        vector<int>     *hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_energy;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_pt;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_eta;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_phi;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz;
        vector<int>     *hltGlbTrkMuonTracksAssociated_bestMatchTP_status;
        vector<int>     *hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits;
        vector<int>     *hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits;
        vector<int>     *hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers;
        vector<double>  *hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction;
        vector<int>     *hltGlbTrkMuonTracksAssociated_matchedTPsize;
        vector<float>   *hltGlbTrkMuonTracksAssociated_mva;
        Int_t           ntpTo_hltGlbTrkMuonTracksAssociated;
        vector<float>   *tpTo_hltGlbTrkMuonTracksAssociated_charge;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_pdgId;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_energy;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_pt;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_eta;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_phi;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_parentVx;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_parentVy;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_parentVz;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_status;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers;
        vector<float>   *tpTo_hltGlbTrkMuonTracksAssociated_gen_charge;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_gen_pt;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_gen_eta;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_gen_phi;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2;
        vector<double>  *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality;
        vector<int>     *tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits;
        int hi_cBin;

    // -- branches
        TBranch        *b_isRealData;   //!
        TBranch        *b_runNum;   //!
        TBranch        *b_lumiBlockNum;   //!
        TBranch        *b_eventNum;   //!
        TBranch        *b_nVertex;   //!
        TBranch        *b_bunchID;   //!
        TBranch        *b_instLumi;   //!
        TBranch        *b_dataPU;   //!
        TBranch        *b_dataPURMS;   //!
        TBranch        *b_bunchLumi;   //!
        TBranch        *b_offlineInstLumi;   //!
        TBranch        *b_offlineDataPU;   //!
        TBranch        *b_offlineDataPURMS;   //!
        TBranch        *b_offlineBunchLumi;   //!
        TBranch        *b_truePU;   //!
        TBranch        *b_InstLumi;   //!
        TBranch        *b_DataPU;   //!
        TBranch        *b_genEventWeight;   //!
        TBranch        *b_nGenParticle;   //!
        TBranch        *b_genParticle_ID;   //!
        TBranch        *b_genParticle_status;   //!
        TBranch        *b_genParticle_mother;   //!
        TBranch        *b_genParticle_pt;   //!
        TBranch        *b_genParticle_eta;   //!
        TBranch        *b_genParticle_phi;   //!
        TBranch        *b_genParticle_px;   //!
        TBranch        *b_genParticle_py;   //!
        TBranch        *b_genParticle_pz;   //!
        TBranch        *b_genParticle_energy;   //!
        TBranch        *b_genParticle_charge;   //!
        TBranch        *b_genParticle_isPrompt;   //!
        TBranch        *b_genParticle_isPromptFinalState;   //!
        TBranch        *b_genParticle_isTauDecayProduct;   //!
        TBranch        *b_genParticle_isPromptTauDecayProduct;   //!
        TBranch        *b_genParticle_isDirectPromptTauDecayProductFinalState;   //!
        TBranch        *b_genParticle_isHardProcess;   //!
        TBranch        *b_genParticle_isLastCopy;   //!
        TBranch        *b_genParticle_isLastCopyBeforeFSR;   //!
        TBranch        *b_genParticle_isPromptDecayed;   //!
        TBranch        *b_genParticle_isDecayedLeptonHadron;   //!
        TBranch        *b_genParticle_fromHardProcessBeforeFSR;   //!
        TBranch        *b_genParticle_fromHardProcessDecayed;   //!
        TBranch        *b_genParticle_fromHardProcessFinalState;   //!
        TBranch        *b_genParticle_isMostlyLikePythia6Status3;   //!
        TBranch        *b_genParticle_l1pt;   //!
        TBranch        *b_genParticle_l1eta;   //!
        TBranch        *b_genParticle_l1phi;   //!
        TBranch        *b_genParticle_l1charge;   //!
        TBranch        *b_genParticle_l1q;   //!
        TBranch        *b_genParticle_l1dr;   //!
        TBranch        *b_genParticle_l1ptByQ;   //!
        TBranch        *b_genParticle_l1etaByQ;   //!
        TBranch        *b_genParticle_l1phiByQ;   //!
        TBranch        *b_genParticle_l1chargeByQ;   //!
        TBranch        *b_genParticle_l1qByQ;   //!
        TBranch        *b_genParticle_l1drByQ;   //!
        TBranch        *b_vec_firedTrigger;   //!
        TBranch        *b_vec_filterName;   //!
        TBranch        *b_vec_HLTObj_pt;   //!
        TBranch        *b_vec_HLTObj_eta;   //!
        TBranch        *b_vec_HLTObj_phi;   //!
        TBranch        *b_vec_myFiredTrigger;   //!
        TBranch        *b_vec_myFilterName;   //!
        TBranch        *b_vec_myHLTObj_pt;   //!
        TBranch        *b_vec_myHLTObj_eta;   //!
        TBranch        *b_vec_myHLTObj_phi;   //!
        TBranch        *b_nMuon;   //!
        TBranch        *b_muon_pt;   //!
        TBranch        *b_muon_eta;   //!
        TBranch        *b_muon_phi;   //!
        TBranch        *b_muon_px;   //!
        TBranch        *b_muon_py;   //!
        TBranch        *b_muon_pz;   //!
        TBranch        *b_muon_dB;   //!
        TBranch        *b_muon_charge;   //!
        TBranch        *b_muon_isGLB;   //!
        TBranch        *b_muon_isSTA;   //!
        TBranch        *b_muon_isTRK;   //!
        TBranch        *b_muon_isPF;   //!
        TBranch        *b_muon_isTight;   //!
        TBranch        *b_muon_isMedium;   //!
        TBranch        *b_muon_isLoose;   //!
        TBranch        *b_muon_isHighPt;   //!
        TBranch        *b_muon_isHighPtNew;   //!
        TBranch        *b_muon_isSoft;   //!
        TBranch        *b_muon_iso03_sumPt;   //!
        TBranch        *b_muon_iso03_hadEt;   //!
        TBranch        *b_muon_iso03_emEt;   //!
        TBranch        *b_muon_PFIso03_charged;   //!
        TBranch        *b_muon_PFIso03_neutral;   //!
        TBranch        *b_muon_PFIso03_photon;   //!
        TBranch        *b_muon_PFIso03_sumPU;   //!
        TBranch        *b_muon_PFIso04_charged;   //!
        TBranch        *b_muon_PFIso04_neutral;   //!
        TBranch        *b_muon_PFIso04_photon;   //!
        TBranch        *b_muon_PFIso04_sumPU;   //!
        TBranch        *b_muon_PFCluster03_ECAL;   //!
        TBranch        *b_muon_PFCluster03_HCAL;   //!
        TBranch        *b_muon_PFCluster04_ECAL;   //!
        TBranch        *b_muon_PFCluster04_HCAL;   //!
        TBranch        *b_muon_inner_trkChi2;
        TBranch        *b_muon_inner_validFraction;
        TBranch        *b_muon_inner_trackerLayers;
        TBranch        *b_muon_inner_trackerHits;
        TBranch        *b_muon_inner_lostTrackerHits;
        TBranch        *b_muon_inner_lostTrackerHitsIn;
        TBranch        *b_muon_inner_lostTrackerHitsOut;
        TBranch        *b_muon_inner_lostPixelHits;
        TBranch        *b_muon_inner_lostPixelBarrelHits;
        TBranch        *b_muon_inner_lostPixelEndcapHits;
        TBranch        *b_muon_inner_lostStripHits;
        TBranch        *b_muon_inner_lostStripTIBHits;
        TBranch        *b_muon_inner_lostStripTIDHits;
        TBranch        *b_muon_inner_lostStripTOBHits;
        TBranch        *b_muon_inner_lostStripTECHits;
        TBranch        *b_muon_inner_pixelLayers;
        TBranch        *b_muon_inner_pixelHits;
        TBranch        *b_muon_global_muonHits;
        TBranch        *b_muon_global_trkChi2;
        TBranch        *b_muon_global_trackerLayers;
        TBranch        *b_muon_global_trackerHits;
        TBranch        *b_muon_momentumChi2;
        TBranch        *b_muon_positionChi2;
        TBranch        *b_muon_glbKink;
        TBranch        *b_muon_glbTrackProbability;
        TBranch        *b_muon_globalDeltaEtaPhi;
        TBranch        *b_muon_localDistance;
        TBranch        *b_muon_staRelChi2;
        TBranch        *b_muon_tightMatch;
        TBranch        *b_muon_trkKink;
        TBranch        *b_muon_trkRelChi2;
        TBranch        *b_muon_segmentCompatibility;
        TBranch        *b_muon_pt_tuneP;   //!
        TBranch        *b_muon_ptError_tuneP;   //!
        TBranch        *b_muon_dxyVTX_best;   //!
        TBranch        *b_muon_dzVTX_best;   //!
        TBranch        *b_muon_nMatchedStation;   //!
        TBranch        *b_muon_nMatchedRPCLayer;   //!
        TBranch        *b_muon_stationMask;   //!
        TBranch        *b_muon_dxy_bs;
        TBranch        *b_muon_dxyError_bs;
        TBranch        *b_muon_dz_bs;
        TBranch        *b_muon_dzError;
        TBranch        *b_muon_IPSig;
        TBranch        *b_muon_l1pt;   //!
        TBranch        *b_muon_l1eta;   //!
        TBranch        *b_muon_l1phi;   //!
        TBranch        *b_muon_l1charge;   //!
        TBranch        *b_muon_l1q;   //!
        TBranch        *b_muon_l1dr;   //!
        TBranch        *b_muon_l1ptByQ;   //!
        TBranch        *b_muon_l1etaByQ;   //!
        TBranch        *b_muon_l1phiByQ;   //!
        TBranch        *b_muon_l1chargeByQ;   //!
        TBranch        *b_muon_l1qByQ;   //!
        TBranch        *b_muon_l1drByQ;   //!
        TBranch        *b_muon_nl1t;   //!
        TBranch        *b_muon_l1tpt;   //!
        TBranch        *b_muon_l1teta;   //!
        TBranch        *b_muon_l1tpropeta;   //!
        TBranch        *b_muon_l1tphi;   //!
        TBranch        *b_muon_l1tpropphi;   //!
        TBranch        *b_muon_l1tcharge;   //!
        TBranch        *b_muon_l1tq;   //!
        TBranch        *b_muon_l1tdr;   //!
        TBranch        *b_nL3Muon;   //!
        TBranch        *b_L3Muon_pt;   //!
        TBranch        *b_L3Muon_eta;   //!
        TBranch        *b_L3Muon_phi;   //!
        TBranch        *b_L3Muon_charge;   //!
        TBranch        *b_L3Muon_trkPt;   //!
        TBranch        *b_nL2Muon;   //!
        TBranch        *b_L2Muon_pt;   //!
        TBranch        *b_L2Muon_eta;   //!
        TBranch        *b_L2Muon_phi;   //!
        TBranch        *b_L2Muon_charge;   //!
        TBranch        *b_L2Muon_trkPt;   //!
        TBranch        *b_nTkMuon;   //!
        TBranch        *b_TkMuon_pt;   //!
        TBranch        *b_TkMuon_eta;   //!
        TBranch        *b_TkMuon_phi;   //!
        TBranch        *b_TkMuon_charge;   //!
        TBranch        *b_TkMuon_trkPt;   //!
        TBranch        *b_nL1Muon;   //!
        TBranch        *b_L1Muon_pt;   //!
        TBranch        *b_L1Muon_eta;   //!
        TBranch        *b_L1Muon_phi;   //!
        TBranch        *b_L1Muon_charge;   //!
        TBranch        *b_L1Muon_quality;   //!
        TBranch        *b_L1Muon_etaAtVtx;   //!
        TBranch        *b_L1Muon_phiAtVtx;   //!
        TBranch        *b_nIterL3OI;   //!
        TBranch        *b_iterL3OI_inner_pt;   //!
        TBranch        *b_iterL3OI_inner_eta;   //!
        TBranch        *b_iterL3OI_inner_phi;   //!
        TBranch        *b_iterL3OI_inner_charge;   //!
        TBranch        *b_iterL3OI_inner_trkChi2;
        TBranch        *b_iterL3OI_inner_validFraction;
        TBranch        *b_iterL3OI_inner_trackerLayers;
        TBranch        *b_iterL3OI_inner_trackerHits;
        TBranch        *b_iterL3OI_inner_lostTrackerHits;
        TBranch        *b_iterL3OI_inner_lostTrackerHitsIn;
        TBranch        *b_iterL3OI_inner_lostTrackerHitsOut;
        TBranch        *b_iterL3OI_inner_lostPixelHits;
        TBranch        *b_iterL3OI_inner_lostPixelBarrelHits;
        TBranch        *b_iterL3OI_inner_lostPixelEndcapHits;
        TBranch        *b_iterL3OI_inner_lostStripHits;
        TBranch        *b_iterL3OI_inner_lostStripTIBHits;
        TBranch        *b_iterL3OI_inner_lostStripTIDHits;
        TBranch        *b_iterL3OI_inner_lostStripTOBHits;
        TBranch        *b_iterL3OI_inner_lostStripTECHits;
        TBranch        *b_iterL3OI_inner_pixelLayers;
        TBranch        *b_iterL3OI_inner_pixelHits;
        TBranch        *b_iterL3OI_outer_pt;   //!
        TBranch        *b_iterL3OI_outer_eta;   //!
        TBranch        *b_iterL3OI_outer_phi;   //!
        TBranch        *b_iterL3OI_outer_charge;   //!
        TBranch        *b_iterL3OI_global_pt;   //!
        TBranch        *b_iterL3OI_global_eta;   //!
        TBranch        *b_iterL3OI_global_phi;   //!
        TBranch        *b_iterL3OI_global_charge;   //!
        TBranch        *b_iterL3OI_global_muonHits;
        TBranch        *b_iterL3OI_global_trkChi2;
        TBranch        *b_iterL3OI_global_trackerLayers;
        TBranch        *b_iterL3OI_global_trackerHits;
        TBranch        *b_nIterL3IOFromL2;   //!
        TBranch        *b_iterL3IOFromL2_inner_pt;   //!
        TBranch        *b_iterL3IOFromL2_inner_eta;   //!
        TBranch        *b_iterL3IOFromL2_inner_phi;   //!
        TBranch        *b_iterL3IOFromL2_inner_charge;   //!
        TBranch        *b_iterL3IOFromL2_inner_trkChi2;
        TBranch        *b_iterL3IOFromL2_inner_validFraction;
        TBranch        *b_iterL3IOFromL2_inner_trackerLayers;
        TBranch        *b_iterL3IOFromL2_inner_trackerHits;
        TBranch        *b_iterL3IOFromL2_inner_lostTrackerHits;
        TBranch        *b_iterL3IOFromL2_inner_lostTrackerHitsIn;
        TBranch        *b_iterL3IOFromL2_inner_lostTrackerHitsOut;
        TBranch        *b_iterL3IOFromL2_inner_lostPixelHits;
        TBranch        *b_iterL3IOFromL2_inner_lostPixelBarrelHits;
        TBranch        *b_iterL3IOFromL2_inner_lostPixelEndcapHits;
        TBranch        *b_iterL3IOFromL2_inner_lostStripHits;
        TBranch        *b_iterL3IOFromL2_inner_lostStripTIBHits;
        TBranch        *b_iterL3IOFromL2_inner_lostStripTIDHits;
        TBranch        *b_iterL3IOFromL2_inner_lostStripTOBHits;
        TBranch        *b_iterL3IOFromL2_inner_lostStripTECHits;
        TBranch        *b_iterL3IOFromL2_inner_pixelLayers;
        TBranch        *b_iterL3IOFromL2_inner_pixelHits;
        TBranch        *b_iterL3IOFromL2_outer_pt;   //!
        TBranch        *b_iterL3IOFromL2_outer_eta;   //!
        TBranch        *b_iterL3IOFromL2_outer_phi;   //!
        TBranch        *b_iterL3IOFromL2_outer_charge;   //!
        TBranch        *b_iterL3IOFromL2_global_pt;   //!
        TBranch        *b_iterL3IOFromL2_global_eta;   //!
        TBranch        *b_iterL3IOFromL2_global_phi;   //!
        TBranch        *b_iterL3IOFromL2_global_charge;   //!
        TBranch        *b_iterL3IOFromL2_global_muonHits;
        TBranch        *b_iterL3IOFromL2_global_trkChi2;
        TBranch        *b_iterL3IOFromL2_global_trackerLayers;
        TBranch        *b_iterL3IOFromL2_global_trackerHits;
        TBranch        *b_nIterL3FromL2;   //!
        TBranch        *b_iterL3FromL2_inner_pt;   //!
        TBranch        *b_iterL3FromL2_inner_eta;   //!
        TBranch        *b_iterL3FromL2_inner_phi;   //!
        TBranch        *b_iterL3FromL2_inner_charge;   //!
        TBranch        *b_iterL3FromL2_inner_trkChi2;
        TBranch        *b_iterL3FromL2_inner_validFraction;
        TBranch        *b_iterL3FromL2_inner_trackerLayers;
        TBranch        *b_iterL3FromL2_inner_trackerHits;
        TBranch        *b_iterL3FromL2_inner_lostTrackerHits;
        TBranch        *b_iterL3FromL2_inner_lostTrackerHitsIn;
        TBranch        *b_iterL3FromL2_inner_lostTrackerHitsOut;
        TBranch        *b_iterL3FromL2_inner_lostPixelHits;
        TBranch        *b_iterL3FromL2_inner_lostPixelBarrelHits;
        TBranch        *b_iterL3FromL2_inner_lostPixelEndcapHits;
        TBranch        *b_iterL3FromL2_inner_lostStripHits;
        TBranch        *b_iterL3FromL2_inner_lostStripTIBHits;
        TBranch        *b_iterL3FromL2_inner_lostStripTIDHits;
        TBranch        *b_iterL3FromL2_inner_lostStripTOBHits;
        TBranch        *b_iterL3FromL2_inner_lostStripTECHits;
        TBranch        *b_iterL3FromL2_inner_pixelLayers;
        TBranch        *b_iterL3FromL2_inner_pixelHits;
        TBranch        *b_iterL3FromL2_outer_pt;   //!
        TBranch        *b_iterL3FromL2_outer_eta;   //!
        TBranch        *b_iterL3FromL2_outer_phi;   //!
        TBranch        *b_iterL3FromL2_outer_charge;   //!
        TBranch        *b_iterL3FromL2_global_pt;   //!
        TBranch        *b_iterL3FromL2_global_eta;   //!
        TBranch        *b_iterL3FromL2_global_phi;   //!
        TBranch        *b_iterL3FromL2_global_charge;   //!
        TBranch        *b_iterL3FromL2_global_muonHits;
        TBranch        *b_iterL3FromL2_global_trkChi2;
        TBranch        *b_iterL3FromL2_global_trackerLayers;
        TBranch        *b_iterL3FromL2_global_trackerHits;
        TBranch        *b_nIterL3IOFromL1;   //!
        TBranch        *b_iterL3IOFromL1_pt;   //!
        TBranch        *b_iterL3IOFromL1_eta;   //!
        TBranch        *b_iterL3IOFromL1_phi;   //!
        TBranch        *b_iterL3IOFromL1_charge;   //!
        TBranch        *b_iterL3IOFromL1_muonHits;
        TBranch        *b_iterL3IOFromL1_trkChi2;
        TBranch        *b_iterL3IOFromL1_validFraction;
        TBranch        *b_iterL3IOFromL1_trackerLayers;
        TBranch        *b_iterL3IOFromL1_trackerHits;
        TBranch        *b_iterL3IOFromL1_lostTrackerHits;
        TBranch        *b_iterL3IOFromL1_lostTrackerHitsIn;
        TBranch        *b_iterL3IOFromL1_lostTrackerHitsOut;
        TBranch        *b_iterL3IOFromL1_lostPixelHits;
        TBranch        *b_iterL3IOFromL1_lostPixelBarrelHits;
        TBranch        *b_iterL3IOFromL1_lostPixelEndcapHits;
        TBranch        *b_iterL3IOFromL1_lostStripHits;
        TBranch        *b_iterL3IOFromL1_lostStripTIBHits;
        TBranch        *b_iterL3IOFromL1_lostStripTIDHits;
        TBranch        *b_iterL3IOFromL1_lostStripTOBHits;
        TBranch        *b_iterL3IOFromL1_lostStripTECHits;
        TBranch        *b_iterL3IOFromL1_pixelLayers;
        TBranch        *b_iterL3IOFromL1_pixelHits;
        TBranch        *b_nIterL3MuonNoID;   //!
        TBranch        *b_iterL3MuonNoID_pt;   //!
        TBranch        *b_iterL3MuonNoID_innerPt;   //!
        TBranch        *b_iterL3MuonNoID_eta;   //!
        TBranch        *b_iterL3MuonNoID_phi;   //!
        TBranch        *b_iterL3MuonNoID_charge;   //!
        TBranch        *b_iterL3MuonNoID_isGLB;   //!
        TBranch        *b_iterL3MuonNoID_isSTA;   //!
        TBranch        *b_iterL3MuonNoID_isTRK;   //!
        TBranch        *b_iterL3MuonNoID_inner_trkChi2;
        TBranch        *b_iterL3MuonNoID_inner_validFraction;
        TBranch        *b_iterL3MuonNoID_inner_trackerLayers;
        TBranch        *b_iterL3MuonNoID_inner_trackerHits;
        TBranch        *b_iterL3MuonNoID_inner_lostTrackerHits;
        TBranch        *b_iterL3MuonNoID_inner_lostTrackerHitsIn;
        TBranch        *b_iterL3MuonNoID_inner_lostTrackerHitsOut;
        TBranch        *b_iterL3MuonNoID_inner_lostPixelHits;
        TBranch        *b_iterL3MuonNoID_inner_lostPixelBarrelHits;
        TBranch        *b_iterL3MuonNoID_inner_lostPixelEndcapHits;
        TBranch        *b_iterL3MuonNoID_inner_lostStripHits;
        TBranch        *b_iterL3MuonNoID_inner_lostStripTIBHits;
        TBranch        *b_iterL3MuonNoID_inner_lostStripTIDHits;
        TBranch        *b_iterL3MuonNoID_inner_lostStripTOBHits;
        TBranch        *b_iterL3MuonNoID_inner_lostStripTECHits;
        TBranch        *b_iterL3MuonNoID_inner_pixelLayers;
        TBranch        *b_iterL3MuonNoID_inner_pixelHits;
        TBranch        *b_iterL3MuonNoID_global_muonHits;
        TBranch        *b_iterL3MuonNoID_global_trkChi2;
        TBranch        *b_iterL3MuonNoID_global_trackerLayers;
        TBranch        *b_iterL3MuonNoID_global_trackerHits;
        TBranch        *b_iterL3MuonNoID_momentumChi2;
        TBranch        *b_iterL3MuonNoID_positionChi2;
        TBranch        *b_iterL3MuonNoID_glbKink;
        TBranch        *b_iterL3MuonNoID_glbTrackProbability;
        TBranch        *b_iterL3MuonNoID_globalDeltaEtaPhi;
        TBranch        *b_iterL3MuonNoID_localDistance;
        TBranch        *b_iterL3MuonNoID_staRelChi2;
        TBranch        *b_iterL3MuonNoID_tightMatch;
        TBranch        *b_iterL3MuonNoID_trkKink;
        TBranch        *b_iterL3MuonNoID_trkRelChi2;
        TBranch        *b_iterL3MuonNoID_segmentCompatibility;
        TBranch        *b_nIterL3Muon;   //!
        TBranch        *b_iterL3Muon_pt;   //!
        TBranch        *b_iterL3Muon_innerPt;   //!
        TBranch        *b_iterL3Muon_eta;   //!
        TBranch        *b_iterL3Muon_phi;   //!
        TBranch        *b_iterL3Muon_charge;   //!
        TBranch        *b_iterL3Muon_isGLB;   //!
        TBranch        *b_iterL3Muon_isSTA;   //!
        TBranch        *b_iterL3Muon_isTRK;   //!
        TBranch        *b_iterL3Muon_inner_trkChi2;
        TBranch        *b_iterL3Muon_inner_validFraction;
        TBranch        *b_iterL3Muon_inner_trackerLayers;
        TBranch        *b_iterL3Muon_inner_trackerHits;
        TBranch        *b_iterL3Muon_inner_lostTrackerHits;
        TBranch        *b_iterL3Muon_inner_lostTrackerHitsIn;
        TBranch        *b_iterL3Muon_inner_lostTrackerHitsOut;
        TBranch        *b_iterL3Muon_inner_lostPixelHits;
        TBranch        *b_iterL3Muon_inner_lostPixelBarrelHits;
        TBranch        *b_iterL3Muon_inner_lostPixelEndcapHits;
        TBranch        *b_iterL3Muon_inner_lostStripHits;
        TBranch        *b_iterL3Muon_inner_lostStripTIBHits;
        TBranch        *b_iterL3Muon_inner_lostStripTIDHits;
        TBranch        *b_iterL3Muon_inner_lostStripTOBHits;
        TBranch        *b_iterL3Muon_inner_lostStripTECHits;
        TBranch        *b_iterL3Muon_inner_pixelLayers;
        TBranch        *b_iterL3Muon_inner_pixelHits;
        TBranch        *b_iterL3Muon_global_muonHits;
        TBranch        *b_iterL3Muon_global_trkChi2;
        TBranch        *b_iterL3Muon_global_trackerLayers;
        TBranch        *b_iterL3Muon_global_trackerHits;
        TBranch        *b_iterL3Muon_momentumChi2;
        TBranch        *b_iterL3Muon_positionChi2;
        TBranch        *b_iterL3Muon_glbKink;
        TBranch        *b_iterL3Muon_glbTrackProbability;
        TBranch        *b_iterL3Muon_globalDeltaEtaPhi;
        TBranch        *b_iterL3Muon_localDistance;
        TBranch        *b_iterL3Muon_staRelChi2;
        TBranch        *b_iterL3Muon_tightMatch;
        TBranch        *b_iterL3Muon_trkKink;
        TBranch        *b_iterL3Muon_trkRelChi2;
        TBranch        *b_iterL3Muon_segmentCompatibility;
        TBranch        *b_nTP;   //!
        TBranch        *b_TP_charge;   //!
        TBranch        *b_TP_pdgId;   //!
        TBranch        *b_TP_energy;   //!
        TBranch        *b_TP_pt;   //!
        TBranch        *b_TP_eta;   //!
        TBranch        *b_TP_phi;   //!
        TBranch        *b_TP_parentVx;   //!
        TBranch        *b_TP_parentVy;   //!
        TBranch        *b_TP_parentVz;   //!
        TBranch        *b_TP_status;   //!
        TBranch        *b_TP_numberOfHits;   //!
        TBranch        *b_TP_numberOfTrackerHits;   //!
        TBranch        *b_TP_numberOfTrackerLayers;   //!
        TBranch        *b_TP_gen_charge;   //!
        TBranch        *b_TP_gen_pdgId;   //!
        TBranch        *b_TP_gen_pt;   //!
        TBranch        *b_TP_gen_eta;   //!
        TBranch        *b_TP_gen_phi;   //!
        TBranch        *b_TP_bestMatchTrk_pt;   //!
        TBranch        *b_TP_bestMatchTrk_eta;   //!
        TBranch        *b_TP_bestMatchTrk_phi;   //!
        TBranch        *b_TP_bestMatchTrk_charge;   //!
        TBranch        *b_TP_bestMatchTrk_quality;   //!
        TBranch        *b_TP_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIterL3MuonTrimmedPixelVertices;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_isValid;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_chi2;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_ndof;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_nTracks;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_x;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_xerr;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_y;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_yerr;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_z;   //!
        TBranch        *b_hltIterL3MuonTrimmedPixelVertices_zerr;   //!
        TBranch        *b_nhltIterL3FromL1MuonTrimmedPixelVertices;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_isValid;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_chi2;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_ndof;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_nTracks;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_x;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_xerr;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_y;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_yerr;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_z;   //!
        TBranch        *b_hltIterL3FromL1MuonTrimmedPixelVertices_zerr;   //!
        TBranch        *b_nhltIterL3OIMuonTrackAssociated;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_pt;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_eta;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_phi;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_charge;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_matchedL3;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_hltIterL3OIMuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIterL3OIMuonTrackAssociated;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIter0IterL3MuonTrackAssociated;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_matchedL3;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_hltIter0IterL3MuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIter0IterL3MuonTrackAssociated;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIter2IterL3MuonTrackAssociated;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_matchedL3;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_hltIter2IterL3MuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIter2IterL3MuonTrackAssociated;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIter0IterL3FromL1MuonTrackAssociated;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_pt;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_eta;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_phi;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_charge;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_matchedL3;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_hltIter0IterL3FromL1MuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIter0IterL3FromL1MuonTrackAssociated;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIter2IterL3FromL1MuonTrackAssociated;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_pt;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_eta;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_phi;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_charge;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_matchedL3;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_hltIter2IterL3FromL1MuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIter2IterL3FromL1MuonTrackAssociated;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIterL3MuonMergedAssociated;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_pt;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_eta;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_phi;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_charge;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_matchedL3;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_matchedTPsize;   //!
        TBranch        *b_hltIterL3MuonMergedAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIterL3MuonMergedAssociated;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_energy;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_status;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_nhltIterL3MuonAndMuonFromL1MergedAssociated;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_pt;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_eta;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_phi;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_charge;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize;   //!
        TBranch        *b_hltIterL3MuonAndMuonFromL1MergedAssociated_mva;   //!
        TBranch        *b_ntpTo_hltIterL3MuonAndMuonFromL1MergedAssociated;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_niterL3MuonNoIDTrackAssociated;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_pt;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_eta;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_phi;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_charge;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_matchedL3;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_matchedTPsize;   //!
        TBranch        *b_iterL3MuonNoIDTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_iterL3MuonNoIDTrackAssociated;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_charge;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_energy;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_pt;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_eta;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_phi;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_status;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_niterL3MuonTrackAssociated;   //!
        TBranch        *b_iterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_iterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_iterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_iterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_iterL3MuonTrackAssociated_matchedL3;   //!
        TBranch        *b_iterL3MuonTrackAssociated_matchedL3NoId;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_charge;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_energy;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_pt;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_eta;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_phi;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_status;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_iterL3MuonTrackAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_iterL3MuonTrackAssociated_matchedTPsize;   //!
        TBranch        *b_iterL3MuonTrackAssociated_mva;   //!
        TBranch        *b_ntpTo_iterL3MuonTrackAssociated;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_charge;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_pdgId;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_energy;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_pt;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_eta;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_phi;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_parentVx;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_parentVy;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_parentVz;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_status;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_gen_charge;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_gen_pt;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_gen_eta;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_gen_phi;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits;   //!

        TBranch        *b_nhltPixelTracksAssociated;   //!
        TBranch        *b_hltPixelTracksAssociated_pt;   //!
        TBranch        *b_hltPixelTracksAssociated_eta;   //!
        TBranch        *b_hltPixelTracksAssociated_phi;   //!
        TBranch        *b_hltPixelTracksAssociated_charge;   //!
        TBranch        *b_hltPixelTracksAssociated_matchedL3;   //!
        TBranch        *b_hltPixelTracksAssociated_matchedL3NoId;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltPixelTracksAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltPixelTracksAssociated_matchedTPsize;   //!
        TBranch        *b_hltPixelTracksAssociated_mva;   //!

        TBranch        *b_nhltPixelTracksInRegionL2Associated;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_pt;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_eta;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_phi;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_charge;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_matchedL3;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_matchedL3NoId;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_charge;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_energy;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_pt;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_eta;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_phi;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_status;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_matchedTPsize;   //!
        TBranch        *b_hltPixelTracksInRegionL2Associated_mva;   //!
        TBranch        *b_ntpTo_hltPixelTracksInRegionL2Associated;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_energy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_parentVx;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_parentVy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_parentVz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_status;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_numberOfHits;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_gen_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_gen_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_gen_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_gen_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits;   //!


        TBranch        *b_nhltPixelTracksInRegionL1Associated;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_pt;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_eta;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_phi;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_charge;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_matchedL3;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_matchedL3NoId;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_charge;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_energy;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_pt;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_eta;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_phi;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_status;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_matchedTPsize;   //!
        TBranch        *b_hltPixelTracksInRegionL1Associated_mva;   //!
        TBranch        *b_ntpTo_hltPixelTracksInRegionL1Associated;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_energy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_parentVx;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_parentVy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_parentVz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_status;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_numberOfHits;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_gen_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_gen_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_gen_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_gen_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits;   //!


        TBranch        *b_nhltPixelTracksForSeedsL3MuonAssociated;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_pt;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_eta;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_phi;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_charge;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_matchedL3;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize;   //!
        TBranch        *b_hltPixelTracksForSeedsL3MuonAssociated_mva;   //!
        TBranch        *b_ntpTo_hltPixelTracksForSeedsL3MuonAssociated;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_status;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits;   //!

        TBranch        *b_nhltGlbTrkMuonTracksAssociated;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_pt;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_eta;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_phi;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_charge;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_matchedL3;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_matchedL3NoId;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_charge;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_energy;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_pt;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_eta;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_phi;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_status;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_matchedTPsize;   //!
        TBranch        *b_hltGlbTrkMuonTracksAssociated_mva;   //!
        TBranch        *b_ntpTo_hltGlbTrkMuonTracksAssociated;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_charge;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_pdgId;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_energy;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_pt;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_eta;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_phi;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_parentVx;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_parentVy;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_parentVz;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_status;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_gen_charge;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_gen_pt;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_gen_eta;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_gen_phi;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality;   //!
        TBranch        *b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits;   //!
        TBranch        *b_hi_cBin;
};

void MuonHLTNtupleRun3::PrintTemplate( TString head )
{
    cout << endl;
    cout << TString::Format("vector<Object> MuonHLTNtupleRun3::get_%s()", head.Data()) << endl;
    cout << TString::Format("{") << endl;
    cout << TString::Format("    vector<Object> out = {};" ) << endl;
    cout << TString::Format("    if(%s_pt == 0 || %s_pt == nullptr)", head.Data(), head.Data()) << endl;
    cout << TString::Format("        return out;" ) << endl;
    cout << endl;
    cout << TString::Format("    for(unsigned i=0; i<%s_pt->size(); ++i) {", head.Data()) << endl;
    cout << TString::Format("        Object obj = Object( %s_pt->at(i), %s_eta->at(i), %s_phi->at(i) );", head.Data(), head.Data(), head.Data()) << endl;
    cout << endl;

    TObjArray* listofb = fChain->GetListOfBranches();
    for(const auto b: *listofb) {
        TString brname = b->GetName();

        if(brname.BeginsWith(head+"_")) {
            TString varname = brname;
            varname = varname.ReplaceAll(head+"_", "");
            // if( varname == "pt" || varname == "eta" || varname == "phi" )
            //     continue;
            cout << TString::Format("        obj.addVar( \"%s\", %s->at(i) );", varname.Data(), brname.Data() ) << endl;
        }
    }

    cout << endl;
    cout << "        out.push_back(obj);" << endl;
    cout << "    }" << endl;
    cout << endl;
    cout << "    return out;" << endl;
    cout << "}" << endl;
}

vector<Object> MuonHLTNtupleRun3::get_offlineMuons()
{
    vector<Object> out = {};

    for(unsigned i=0; i<(unsigned)nMuon; ++i) {
        // cout << "i: " << i << endl;
        Object obj = Object( muon_pt[i], muon_eta[i], muon_phi[i] );

        obj.addVar( "pt", muon_pt[i] );
        obj.addVar( "eta", muon_eta[i] );
        obj.addVar( "phi", muon_phi[i] );
        obj.addVar( "px", muon_px[i] );
        obj.addVar( "py", muon_py[i] );
        obj.addVar( "pz", muon_pz[i] );
        obj.addVar( "dB", muon_dB[i] );
        obj.addVar( "charge", muon_charge[i] );
        obj.addVar( "isGLB", muon_isGLB[i] );
        obj.addVar( "isSTA", muon_isSTA[i] );
        obj.addVar( "isTRK", muon_isTRK[i] );
        obj.addVar( "isPF", muon_isPF[i] );
        obj.addVar( "isTight", muon_isTight[i] );
        obj.addVar( "isMedium", muon_isMedium[i] );
        obj.addVar( "isLoose", muon_isLoose[i] );
        obj.addVar( "isHighPt", muon_isHighPt[i] );
        obj.addVar( "isHighPtNew", muon_isHighPtNew[i] );
        obj.addVar( "isSoft", muon_isSoft[i] );
        obj.addVar( "iso03_sumPt", muon_iso03_sumPt[i] );
        obj.addVar( "iso03_hadEt", muon_iso03_hadEt[i] );
        obj.addVar( "iso03_emEt", muon_iso03_emEt[i] );
        obj.addVar( "PFIso03_charged", muon_PFIso03_charged[i] );
        obj.addVar( "PFIso03_neutral", muon_PFIso03_neutral[i] );
        obj.addVar( "PFIso03_photon", muon_PFIso03_photon[i] );
        obj.addVar( "PFIso03_sumPU", muon_PFIso03_sumPU[i] );
        obj.addVar( "PFIso04_charged", muon_PFIso04_charged[i] );
        obj.addVar( "PFIso04_neutral", muon_PFIso04_neutral[i] );
        obj.addVar( "PFIso04_photon", muon_PFIso04_photon[i] );
        obj.addVar( "PFIso04_sumPU", muon_PFIso04_sumPU[i] );
        obj.addVar( "PFCluster03_ECAL", muon_PFCluster03_ECAL[i] );
        obj.addVar( "PFCluster03_HCAL", muon_PFCluster03_HCAL[i] );
        obj.addVar( "PFCluster04_ECAL", muon_PFCluster04_ECAL[i] );
        obj.addVar( "PFCluster04_HCAL", muon_PFCluster04_HCAL[i] );
        obj.addVar( "inner_trkChi2",  muon_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", muon_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", muon_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", muon_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", muon_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", muon_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", muon_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", muon_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", muon_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", muon_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", muon_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", muon_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", muon_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", muon_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", muon_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", muon_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", muon_inner_pixelHits[i] );
        obj.addVar( "global_muonHits", muon_global_muonHits[i] );
        obj.addVar( "global_trkChi2", muon_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", muon_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", muon_global_trackerHits[i] );
        obj.addVar( "momentumChi2", muon_momentumChi2[i] );
        obj.addVar( "positionChi2", muon_positionChi2[i] );
        obj.addVar( "glbKink", muon_glbKink[i] );
        obj.addVar( "glbTrackProbability", muon_glbTrackProbability[i] );
        obj.addVar( "globalDeltaEtaPhi", muon_globalDeltaEtaPhi[i] );
        obj.addVar( "localDistance", muon_localDistance[i] );
        obj.addVar( "staRelChi2", muon_staRelChi2[i] );
        obj.addVar( "tightMatch", muon_tightMatch[i] );
        obj.addVar( "trkKink", muon_trkKink[i] );
        obj.addVar( "trkRelChi2", muon_trkRelChi2[i] );
        obj.addVar( "segmentCompatibility", muon_segmentCompatibility[i] );
        obj.addVar( "pt_tuneP", muon_pt_tuneP[i] );
        obj.addVar( "ptError_tuneP", muon_ptError_tuneP[i] );
        obj.addVar( "dxyVTX_best", muon_dxyVTX_best[i] );
        obj.addVar( "dzVTX_best", muon_dzVTX_best[i] );
        obj.addVar( "nMatchedStation", muon_nMatchedStation[i] );
        obj.addVar( "nMatchedRPCLayer", muon_nMatchedRPCLayer[i] );
        obj.addVar( "stationMask", muon_stationMask[i] );
        obj.addVar( "dxy_bs", muon_dxy_bs[i] );
        obj.addVar( "dxyError_bs", muon_dxyError_bs[i] );
        obj.addVar( "dz_bs", muon_dz_bs[i] );
        obj.addVar( "dzError", muon_dzError[i] );
        obj.addVar( "IPSig", muon_IPSig[i] );
        obj.addVar( "l1pt", muon_l1pt[i] );
        obj.addVar( "l1eta", muon_l1eta[i] );
        obj.addVar( "l1phi", muon_l1phi[i] );
        obj.addVar( "l1eta", muon_l1eta[i] );
        obj.addVar( "l1phi", muon_l1phi[i] );
        obj.addVar( "l1charge", muon_l1charge[i] );
        obj.addVar( "l1q", muon_l1q[i] );
        obj.addVar( "l1dr", muon_l1dr[i] );
        obj.addVar( "l1ptByQ", muon_l1ptByQ[i] );
        obj.addVar( "l1etaByQ", muon_l1etaByQ[i] );
        obj.addVar( "l1phiByQ", muon_l1phiByQ[i] );
        obj.addVar( "l1chargeByQ", muon_l1chargeByQ[i] );
        obj.addVar( "l1qByQ", muon_l1qByQ[i] );
        obj.addVar( "l1drByQ", muon_l1drByQ[i] );

        obj.addVar( "nl1t", muon_nl1t[i] );
        obj.addVec( "l1tpt", muon_l1tpt->at(i) );
        obj.addVec( "l1teta", muon_l1teta->at(i) );
        obj.addVec( "l1tpropeta", muon_l1tpropeta->at(i) );
        obj.addVec( "l1tphi", muon_l1tphi->at(i) );
        obj.addVec( "l1tpropphi", muon_l1tpropphi->at(i) );
        obj.addVec( "l1tcharge", muon_l1tcharge->at(i) );
        obj.addVec( "l1tq", muon_l1tq->at(i) );
        obj.addVec( "l1tdr", muon_l1tdr->at(i) );

        obj.addVar( "relPFIso", ((muon_PFIso04_charged[i] + max(0., muon_PFIso04_neutral[i] + muon_PFIso04_photon[i] - 0.5*muon_PFIso04_sumPU[i]))/muon_pt[i]) );
        obj.addVar( "relTrkIso", (muon_iso03_sumPt[i] / muon_pt[i]) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_GenParticles()
{
    vector<Object> out = {};

    for(int i=0; i<nGenParticle; ++i) {

        if( genParticle_status[i] != 1 && genParticle_isHardProcess[i] != 1 )
            continue;

        Object obj = Object( genParticle_pt[i], genParticle_eta[i], genParticle_phi[i] );

        obj.addVar( "ID", genParticle_ID[i] );
        obj.addVar( "status", genParticle_status[i] );
        obj.addVar( "mother", genParticle_mother[i] );
        obj.addVar( "pt", genParticle_pt[i] );
        obj.addVar( "eta", genParticle_eta[i] );
        obj.addVar( "phi", genParticle_phi[i] );
        obj.addVar( "px", genParticle_px[i] );
        obj.addVar( "py", genParticle_py[i] );
        obj.addVar( "pz", genParticle_pz[i] );
        obj.addVar( "energy", genParticle_energy[i] );
        obj.addVar( "charge", genParticle_charge[i] );
        obj.addVar( "isPrompt", genParticle_isPrompt[i] );
        obj.addVar( "isPromptFinalState", genParticle_isPromptFinalState[i] );
        obj.addVar( "isTauDecayProduct", genParticle_isTauDecayProduct[i] );
        obj.addVar( "isPromptTauDecayProduct", genParticle_isPromptTauDecayProduct[i] );
        obj.addVar( "isDirectPromptTauDecayProductFinalState", genParticle_isDirectPromptTauDecayProductFinalState[i] );
        obj.addVar( "isHardProcess", genParticle_isHardProcess[i] );
        obj.addVar( "isLastCopy", genParticle_isLastCopy[i] );
        obj.addVar( "isLastCopyBeforeFSR", genParticle_isLastCopyBeforeFSR[i] );
        obj.addVar( "isPromptDecayed", genParticle_isPromptDecayed[i] );
        obj.addVar( "isDecayedLeptonHadron", genParticle_isDecayedLeptonHadron[i] );
        obj.addVar( "fromHardProcessBeforeFSR", genParticle_fromHardProcessBeforeFSR[i] );
        obj.addVar( "fromHardProcessDecayed", genParticle_fromHardProcessDecayed[i] );
        obj.addVar( "fromHardProcessFinalState", genParticle_fromHardProcessFinalState[i] );
        obj.addVar( "isMostlyLikePythia6Status3", genParticle_isMostlyLikePythia6Status3[i] );
        obj.addVar( "l1pt", genParticle_l1pt[i] );
        obj.addVar( "l1eta", genParticle_l1eta[i] );
        obj.addVar( "l1phi", genParticle_l1phi[i] );
        obj.addVar( "l1charge", genParticle_l1charge[i] );
        obj.addVar( "l1q", genParticle_l1q[i] );
        obj.addVar( "l1dr", genParticle_l1dr[i] );
        obj.addVar( "l1ptByQ", genParticle_l1ptByQ[i] );
        obj.addVar( "l1etaByQ", genParticle_l1etaByQ[i] );
        obj.addVar( "l1phiByQ", genParticle_l1phiByQ[i] );
        obj.addVar( "l1chargeByQ", genParticle_l1chargeByQ[i] );
        obj.addVar( "l1qByQ", genParticle_l1qByQ[i] );
        obj.addVar( "l1drByQ", genParticle_l1drByQ[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_TP(bool hasGen)
{
    vector<Object> out = {};
    if(TP_pt == 0 || TP_pt == nullptr)
        return out;

    for(unsigned i=0; i<TP_pt->size(); ++i) {
        if (hasGen) {
            if (abs(TP_gen_pdgId->at(i)) != 13) {
                continue;
            }
            if (TP_gen_pt->at(i) < 0.) {
                continue;
            }
        }

        Object obj = Object( TP_pt->at(i), TP_eta->at(i), TP_phi->at(i) );

        obj.addVar( "charge", TP_charge->at(i) );
        obj.addVar( "pdgId", TP_pdgId->at(i) );
        obj.addVar( "energy", TP_energy->at(i) );
        obj.addVar( "pt", TP_pt->at(i) );
        obj.addVar( "eta", TP_eta->at(i) );
        obj.addVar( "phi", TP_phi->at(i) );
        obj.addVar( "parentVx", TP_parentVx->at(i) );
        obj.addVar( "parentVy", TP_parentVy->at(i) );
        obj.addVar( "parentVz", TP_parentVz->at(i) );
        obj.addVar( "status", TP_status->at(i) );
        obj.addVar( "numberOfHits", TP_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", TP_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", TP_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", TP_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", TP_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", TP_gen_pt->at(i) );
        obj.addVar( "gen_eta", TP_gen_eta->at(i) );
        obj.addVar( "gen_phi", TP_gen_phi->at(i) );
        // obj.addVar( "bestMatchTrk_pt", TP_bestMatchTrk_pt->at(i) );
        // obj.addVar( "bestMatchTrk_eta", TP_bestMatchTrk_eta->at(i) );
        // obj.addVar( "bestMatchTrk_phi", TP_bestMatchTrk_phi->at(i) );
        // obj.addVar( "bestMatchTrk_charge", TP_bestMatchTrk_charge->at(i) );
        // obj.addVar( "bestMatchTrk_quality", TP_bestMatchTrk_quality->at(i) );
        // obj.addVar( "bestMatchTrk_NValidHits", TP_bestMatchTrk_NValidHits->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_L1Muons()
{
    vector<Object> out = {};
    for(int i=0; i<nL1Muon; ++i) {

        // if(L1Muon_quality[i] < 12)
        //     continue;

        Object obj = Object( L1Muon_pt[i], L1Muon_eta[i], L1Muon_phi[i] );

        obj.addVar( "pt", L1Muon_pt[i] );
        obj.addVar( "eta", L1Muon_eta[i] );
        obj.addVar( "phi", L1Muon_phi[i] );
        obj.addVar( "charge", L1Muon_charge[i] );
        obj.addVar( "quality", L1Muon_quality[i] );
        obj.addVar( "etaAtVtx", L1Muon_etaAtVtx[i] );
        obj.addVar( "phiAtVtx", L1Muon_phiAtVtx[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_L2Muons()
{
    vector<Object> out = {};

    for(int i=0; i<nL2Muon; ++i) {

        Object obj = Object( L2Muon_pt[i], L2Muon_eta[i], L2Muon_phi[i] );

        obj.addVar( "pt", L2Muon_pt[i] );
        obj.addVar( "eta", L2Muon_eta[i] );
        obj.addVar( "phi", L2Muon_phi[i] );
        obj.addVar( "charge", L2Muon_charge[i] );
        obj.addVar( "trkPt", L2Muon_trkPt[i] );

        out.push_back(obj);
    }

    return out;
}

/*
vector<Object> MuonHLTNtupleRun3::get_L3MuonsNoId()
{
    vector<Object> out = {};
    if(L3MuonsNoId_pt == 0 || L3MuonsNoId_pt == nullptr)
        return out;

    for(unsigned i=0; i<L3MuonsNoId_pt->size(); ++i) {
        Object obj = Object( L3MuonsNoId_pt->at(i), L3MuonsNoId_eta->at(i), L3MuonsNoId_phi->at(i) );

        obj.addVar( "pt", L3MuonsNoId_pt->at(i) );
        obj.addVar( "inner_pt", L3MuonsNoId_inner_pt->at(i) );
        obj.addVar( "inner_ptError", L3MuonsNoId_inner_ptError->at(i) );
        obj.addVar( "eta", L3MuonsNoId_eta->at(i) );
        obj.addVar( "phi", L3MuonsNoId_phi->at(i) );
        obj.addVar( "charge", L3MuonsNoId_charge->at(i) );
        obj.addVar( "isGlobalMuon", L3MuonsNoId_isGlobalMuon->at(i) );
        obj.addVar( "isStandAloneMuon", L3MuonsNoId_isStandAloneMuon->at(i) );
        obj.addVar( "isTrackerMuon", L3MuonsNoId_isTrackerMuon->at(i) );
        obj.addVar( "isLooseTriggerMuon", L3MuonsNoId_isLooseTriggerMuon->at(i) );
        obj.addVar( "isME0Muon", L3MuonsNoId_isME0Muon->at(i) );
        obj.addVar( "isGEMMuon", L3MuonsNoId_isGEMMuon->at(i) );
        obj.addVar( "isRPCMuon", L3MuonsNoId_isRPCMuon->at(i) );
        obj.addVar( "isGoodMuon_TMOneStationTight", L3MuonsNoId_isGoodMuon_TMOneStationTight->at(i) );
        obj.addVar( "numberOfMatchedStations", L3MuonsNoId_numberOfMatchedStations->at(i) );
        obj.addVar( "numberOfMatchedRPCLayers", L3MuonsNoId_numberOfMatchedRPCLayers->at(i) );
        obj.addVar( "expectedNnumberOfMatchedStations", L3MuonsNoId_expectedNnumberOfMatchedStations->at(i) );
        obj.addVar( "inner_normalizedChi2", L3MuonsNoId_inner_normalizedChi2->at(i) );
        obj.addVar( "inner_numberOfValidTrackerHits", L3MuonsNoId_inner_numberOfValidTrackerHits->at(i) );
        obj.addVar( "inner_trackerLayersWithMeasurement", L3MuonsNoId_inner_trackerLayersWithMeasurement->at(i) );
        obj.addVar( "inner_numberOfValidPixelHits", L3MuonsNoId_inner_numberOfValidPixelHits->at(i) );
        obj.addVar( "inner_dz_l1vtx", L3MuonsNoId_inner_dz_l1vtx->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_L3Muons()
{
    vector<Object> out = {};
    if(L3Muons_pt == 0 || L3Muons_pt == nullptr)
        return out;

    for(unsigned i=0; i<L3Muons_pt->size(); ++i) {
        Object obj = Object( L3Muons_pt->at(i), L3Muons_eta->at(i), L3Muons_phi->at(i) );

        obj.addVar( "pt", L3Muons_pt->at(i) );
        obj.addVar( "inner_pt", L3Muons_inner_pt->at(i) );
        obj.addVar( "inner_ptError", L3Muons_inner_ptError->at(i) );
        obj.addVar( "eta", L3Muons_eta->at(i) );
        obj.addVar( "phi", L3Muons_phi->at(i) );
        obj.addVar( "charge", L3Muons_charge->at(i) );
        obj.addVar( "isGlobalMuon", L3Muons_isGlobalMuon->at(i) );
        obj.addVar( "isStandAloneMuon", L3Muons_isStandAloneMuon->at(i) );
        obj.addVar( "isTrackerMuon", L3Muons_isTrackerMuon->at(i) );
        obj.addVar( "isLooseTriggerMuon", L3Muons_isLooseTriggerMuon->at(i) );
        obj.addVar( "isME0Muon", L3Muons_isME0Muon->at(i) );
        obj.addVar( "isGEMMuon", L3Muons_isGEMMuon->at(i) );
        obj.addVar( "isRPCMuon", L3Muons_isRPCMuon->at(i) );
        obj.addVar( "isGoodMuon_TMOneStationTight", L3Muons_isGoodMuon_TMOneStationTight->at(i) );
        obj.addVar( "numberOfMatchedStations", L3Muons_numberOfMatchedStations->at(i) );
        obj.addVar( "numberOfMatchedRPCLayers", L3Muons_numberOfMatchedRPCLayers->at(i) );
        obj.addVar( "expectedNnumberOfMatchedStations", L3Muons_expectedNnumberOfMatchedStations->at(i) );
        obj.addVar( "inner_normalizedChi2", L3Muons_inner_normalizedChi2->at(i) );
        obj.addVar( "inner_numberOfValidTrackerHits", L3Muons_inner_numberOfValidTrackerHits->at(i) );
        obj.addVar( "inner_trackerLayersWithMeasurement", L3Muons_inner_trackerLayersWithMeasurement->at(i) );
        obj.addVar( "inner_numberOfValidPixelHits", L3Muons_inner_numberOfValidPixelHits->at(i) );
        obj.addVar( "inner_dz_l1vtx", L3Muons_inner_dz_l1vtx->at(i) );

        out.push_back(obj);
    }

    return out;
}
*/

vector<Object> MuonHLTNtupleRun3::get_iterL3OI()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3OI; ++i) {
        Object obj = Object( iterL3OI_inner_pt[i], iterL3OI_inner_eta[i], iterL3OI_inner_phi[i] );

        obj.addVar( "inner_pt", iterL3OI_inner_pt[i] );
        obj.addVar( "inner_eta", iterL3OI_inner_eta[i] );
        obj.addVar( "inner_phi", iterL3OI_inner_phi[i] );
        obj.addVar( "inner_charge", iterL3OI_inner_charge[i] );
        obj.addVar( "inner_trkChi2", iterL3OI_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", iterL3OI_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", iterL3OI_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", iterL3OI_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", iterL3OI_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", iterL3OI_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", iterL3OI_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", iterL3OI_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", iterL3OI_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", iterL3OI_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", iterL3OI_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", iterL3OI_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", iterL3OI_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", iterL3OI_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", iterL3OI_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", iterL3OI_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", iterL3OI_inner_pixelHits[i] );
        obj.addVar( "outer_pt", iterL3OI_outer_pt[i] );
        obj.addVar( "outer_eta", iterL3OI_outer_eta[i] );
        obj.addVar( "outer_phi", iterL3OI_outer_phi[i] );
        obj.addVar( "outer_charge", iterL3OI_outer_charge[i] );
        obj.addVar( "global_pt", iterL3OI_global_pt[i] );
        obj.addVar( "global_eta", iterL3OI_global_eta[i] );
        obj.addVar( "global_phi", iterL3OI_global_phi[i] );
        obj.addVar( "global_charge", iterL3OI_global_charge[i] );
        obj.addVar( "global_muonHits", iterL3OI_global_muonHits[i] );
        obj.addVar( "global_trkChi2", iterL3OI_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", iterL3OI_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", iterL3OI_global_trackerHits[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3IOFromL2()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3IOFromL2; ++i) {
        Object obj = Object( iterL3IOFromL2_inner_pt[i], iterL3IOFromL2_inner_eta[i], iterL3IOFromL2_inner_phi[i] );

        obj.addVar( "inner_pt", iterL3IOFromL2_inner_pt[i] );
        obj.addVar( "inner_eta", iterL3IOFromL2_inner_eta[i] );
        obj.addVar( "inner_phi", iterL3IOFromL2_inner_phi[i] );
        obj.addVar( "inner_charge", iterL3IOFromL2_inner_charge[i] );
        obj.addVar( "inner_trkChi2", iterL3IOFromL2_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", iterL3IOFromL2_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", iterL3IOFromL2_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", iterL3IOFromL2_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", iterL3IOFromL2_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", iterL3IOFromL2_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", iterL3IOFromL2_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", iterL3IOFromL2_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", iterL3IOFromL2_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", iterL3IOFromL2_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", iterL3IOFromL2_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", iterL3IOFromL2_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", iterL3IOFromL2_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", iterL3IOFromL2_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", iterL3IOFromL2_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", iterL3IOFromL2_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", iterL3IOFromL2_inner_pixelHits[i] );
        obj.addVar( "outer_pt", iterL3IOFromL2_outer_pt[i] );
        obj.addVar( "outer_eta", iterL3IOFromL2_outer_eta[i] );
        obj.addVar( "outer_phi", iterL3IOFromL2_outer_phi[i] );
        obj.addVar( "outer_charge", iterL3IOFromL2_outer_charge[i] );
        obj.addVar( "global_pt", iterL3IOFromL2_global_pt[i] );
        obj.addVar( "global_eta", iterL3IOFromL2_global_eta[i] );
        obj.addVar( "global_phi", iterL3IOFromL2_global_phi[i] );
        obj.addVar( "global_charge", iterL3IOFromL2_global_charge[i] );
        obj.addVar( "global_muonHits", iterL3IOFromL2_global_muonHits[i] );
        obj.addVar( "global_trkChi2", iterL3IOFromL2_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", iterL3IOFromL2_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", iterL3IOFromL2_global_trackerHits[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3FromL2()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3FromL2; ++i) {
        Object obj = Object( iterL3FromL2_inner_pt[i], iterL3FromL2_inner_eta[i], iterL3FromL2_inner_phi[i] );

        obj.addVar( "inner_pt", iterL3FromL2_inner_pt[i] );
        obj.addVar( "inner_eta", iterL3FromL2_inner_eta[i] );
        obj.addVar( "inner_phi", iterL3FromL2_inner_phi[i] );
        obj.addVar( "inner_charge", iterL3FromL2_inner_charge[i] );
        obj.addVar( "inner_trkChi2", iterL3FromL2_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", iterL3FromL2_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", iterL3FromL2_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", iterL3FromL2_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", iterL3FromL2_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", iterL3FromL2_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", iterL3FromL2_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", iterL3FromL2_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", iterL3FromL2_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", iterL3FromL2_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", iterL3FromL2_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", iterL3FromL2_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", iterL3FromL2_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", iterL3FromL2_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", iterL3FromL2_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", iterL3FromL2_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", iterL3FromL2_inner_pixelHits[i] );
        obj.addVar( "outer_pt", iterL3FromL2_outer_pt[i] );
        obj.addVar( "outer_eta", iterL3FromL2_outer_eta[i] );
        obj.addVar( "outer_phi", iterL3FromL2_outer_phi[i] );
        obj.addVar( "outer_charge", iterL3FromL2_outer_charge[i] );
        obj.addVar( "global_pt", iterL3FromL2_global_pt[i] );
        obj.addVar( "global_eta", iterL3FromL2_global_eta[i] );
        obj.addVar( "global_phi", iterL3FromL2_global_phi[i] );
        obj.addVar( "global_charge", iterL3FromL2_global_charge[i] );
        obj.addVar( "global_muonHits", iterL3FromL2_global_muonHits[i] );
        obj.addVar( "global_trkChi2", iterL3FromL2_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", iterL3FromL2_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", iterL3FromL2_global_trackerHits[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3IOFromL1()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3IOFromL1; ++i) {
        Object obj = Object( iterL3IOFromL1_pt[i], iterL3IOFromL1_eta[i], iterL3IOFromL1_phi[i] );

        obj.addVar( "pt", iterL3IOFromL1_pt[i] );
        obj.addVar( "eta", iterL3IOFromL1_eta[i] );
        obj.addVar( "phi", iterL3IOFromL1_phi[i] );
        obj.addVar( "charge", iterL3IOFromL1_charge[i] );
        obj.addVar( "muonHits", iterL3IOFromL1_muonHits[i] );
        obj.addVar( "trkChi2", iterL3IOFromL1_trkChi2[i] );
        obj.addVar( "validFraction", iterL3IOFromL1_validFraction[i] );
        obj.addVar( "trackerLayers", iterL3IOFromL1_trackerLayers[i] );
        obj.addVar( "trackerHits", iterL3IOFromL1_trackerHits[i] );
        obj.addVar( "lostTrackerHits", iterL3IOFromL1_lostTrackerHits[i] );
        obj.addVar( "lostTrackerHitsIn", iterL3IOFromL1_lostTrackerHitsIn[i] );
        obj.addVar( "lostTrackerHitsOut", iterL3IOFromL1_lostTrackerHitsOut[i] );
        obj.addVar( "lostPixelHits", iterL3IOFromL1_lostPixelHits[i] );
        obj.addVar( "lostPixelBarrelHits", iterL3IOFromL1_lostPixelBarrelHits[i] );
        obj.addVar( "lostPixelEndcapHits", iterL3IOFromL1_lostPixelEndcapHits[i] );
        obj.addVar( "lostStripHits", iterL3IOFromL1_lostStripHits[i] );
        obj.addVar( "lostStripTIBHits", iterL3IOFromL1_lostStripTIBHits[i] );
        obj.addVar( "lostStripTIDHits", iterL3IOFromL1_lostStripTIDHits[i] );
        obj.addVar( "lostStripTOBHits", iterL3IOFromL1_lostStripTOBHits[i] );
        obj.addVar( "lostStripTECHits", iterL3IOFromL1_lostStripTECHits[i] );
        obj.addVar( "pixelLayers", iterL3IOFromL1_pixelLayers[i] );
        obj.addVar( "pixelHits", iterL3IOFromL1_pixelHits[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3MuonNoID()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3MuonNoID; ++i) {
        Object obj = Object( iterL3MuonNoID_pt[i], iterL3MuonNoID_eta[i], iterL3MuonNoID_phi[i] );

        obj.addVar( "pt", iterL3MuonNoID_pt[i] );
        obj.addVar( "innerPt", iterL3MuonNoID_innerPt[i] );
        obj.addVar( "eta", iterL3MuonNoID_eta[i] );
        obj.addVar( "phi", iterL3MuonNoID_phi[i] );
        obj.addVar( "charge", iterL3MuonNoID_charge[i] );
        obj.addVar( "isGLB", iterL3MuonNoID_isGLB[i] );
        obj.addVar( "isSTA", iterL3MuonNoID_isSTA[i] );
        obj.addVar( "isTRK", iterL3MuonNoID_isTRK[i] );
        obj.addVar( "inner_trkChi2", iterL3MuonNoID_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", iterL3MuonNoID_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", iterL3MuonNoID_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", iterL3MuonNoID_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", iterL3MuonNoID_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", iterL3MuonNoID_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", iterL3MuonNoID_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", iterL3MuonNoID_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", iterL3MuonNoID_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", iterL3MuonNoID_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", iterL3MuonNoID_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", iterL3MuonNoID_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", iterL3MuonNoID_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", iterL3MuonNoID_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", iterL3MuonNoID_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", iterL3MuonNoID_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", iterL3MuonNoID_inner_pixelHits[i] );
        obj.addVar( "global_muonHits", iterL3MuonNoID_global_muonHits[i] );
        obj.addVar( "global_trkChi2", iterL3MuonNoID_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", iterL3MuonNoID_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", iterL3MuonNoID_global_trackerHits[i] );
        obj.addVar( "momentumChi2", iterL3MuonNoID_momentumChi2[i] );
        obj.addVar( "positionChi2", iterL3MuonNoID_positionChi2[i] );
        obj.addVar( "glbKink", iterL3MuonNoID_glbKink[i] );
        obj.addVar( "glbTrackProbability", iterL3MuonNoID_glbTrackProbability[i] );
        obj.addVar( "globalDeltaEtaPhi", iterL3MuonNoID_globalDeltaEtaPhi[i] );
        obj.addVar( "localDistance", iterL3MuonNoID_localDistance[i] );
        obj.addVar( "staRelChi2", iterL3MuonNoID_staRelChi2[i] );
        obj.addVar( "tightMatch", iterL3MuonNoID_tightMatch[i] );
        obj.addVar( "trkKink", iterL3MuonNoID_trkKink[i] );
        obj.addVar( "trkRelChi2", iterL3MuonNoID_trkRelChi2[i] );
        obj.addVar( "segmentCompatibility", iterL3MuonNoID_segmentCompatibility[i] );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3Muon()
{
    vector<Object> out = {};
    for(int i=0; i<nIterL3Muon; ++i) {
        Object obj = Object( iterL3Muon_pt[i], iterL3Muon_eta[i], iterL3Muon_phi[i] );

        obj.addVar( "pt", iterL3Muon_pt[i] );
        obj.addVar( "innerPt", iterL3Muon_innerPt[i] );
        obj.addVar( "eta", iterL3Muon_eta[i] );
        obj.addVar( "phi", iterL3Muon_phi[i] );
        obj.addVar( "charge", iterL3Muon_charge[i] );
        obj.addVar( "isGLB", iterL3Muon_isGLB[i] );
        obj.addVar( "isSTA", iterL3Muon_isSTA[i] );
        obj.addVar( "isTRK", iterL3Muon_isTRK[i] );
        obj.addVar( "inner_trkChi2", iterL3Muon_inner_trkChi2[i] );
        obj.addVar( "inner_validFraction", iterL3Muon_inner_validFraction[i] );
        obj.addVar( "inner_trackerLayers", iterL3Muon_inner_trackerLayers[i] );
        obj.addVar( "inner_trackerHits", iterL3Muon_inner_trackerHits[i] );
        obj.addVar( "inner_lostTrackerHits", iterL3Muon_inner_lostTrackerHits[i] );
        obj.addVar( "inner_lostTrackerHitsIn", iterL3Muon_inner_lostTrackerHitsIn[i] );
        obj.addVar( "inner_lostTrackerHitsOut", iterL3Muon_inner_lostTrackerHitsOut[i] );
        obj.addVar( "inner_lostPixelHits", iterL3Muon_inner_lostPixelHits[i] );
        obj.addVar( "inner_lostPixelBarrelHits", iterL3Muon_inner_lostPixelBarrelHits[i] );
        obj.addVar( "inner_lostPixelEndcapHits", iterL3Muon_inner_lostPixelEndcapHits[i] );
        obj.addVar( "inner_lostStripHits", iterL3Muon_inner_lostStripHits[i] );
        obj.addVar( "inner_lostStripTIBHits", iterL3Muon_inner_lostStripTIBHits[i] );
        obj.addVar( "inner_lostStripTIDHits", iterL3Muon_inner_lostStripTIDHits[i] );
        obj.addVar( "inner_lostStripTOBHits", iterL3Muon_inner_lostStripTOBHits[i] );
        obj.addVar( "inner_lostStripTECHits", iterL3Muon_inner_lostStripTECHits[i] );
        obj.addVar( "inner_pixelLayers", iterL3Muon_inner_pixelLayers[i] );
        obj.addVar( "inner_pixelHits", iterL3Muon_inner_pixelHits[i] );
        obj.addVar( "global_muonHits", iterL3Muon_global_muonHits[i] );
        obj.addVar( "global_trkChi2", iterL3Muon_global_trkChi2[i] );
        obj.addVar( "global_trackerLayers", iterL3Muon_global_trackerLayers[i] );
        obj.addVar( "global_trackerHits", iterL3Muon_global_trackerHits[i] );
        obj.addVar( "momentumChi2", iterL3Muon_momentumChi2[i] );
        obj.addVar( "positionChi2", iterL3Muon_positionChi2[i] );
        obj.addVar( "glbKink", iterL3Muon_glbKink[i] );
        obj.addVar( "glbTrackProbability", iterL3Muon_glbTrackProbability[i] );
        obj.addVar( "globalDeltaEtaPhi", iterL3Muon_globalDeltaEtaPhi[i] );
        obj.addVar( "localDistance", iterL3Muon_localDistance[i] );
        obj.addVar( "staRelChi2", iterL3Muon_staRelChi2[i] );
        obj.addVar( "tightMatch", iterL3Muon_tightMatch[i] );
        obj.addVar( "trkKink", iterL3Muon_trkKink[i] );
        obj.addVar( "trkRelChi2", iterL3Muon_trkRelChi2[i] );
        obj.addVar( "segmentCompatibility", iterL3Muon_segmentCompatibility[i] );

        out.push_back(obj);
    }

    return out;
}

bool MuonHLTNtupleRun3::path_fired( TString path )
{
  bool fired = false;

  for(unsigned i=0; i<vec_firedTrigger->size(); i++) {
    if(vec_firedTrigger->at(i).find(path) != std::string::npos) {
      fired = true;
      break;
    }
  }

  return fired;
}

bool MuonHLTNtupleRun3::path_myFired( TString path )
{
  bool myFired = false;

  for(unsigned i=0; i<vec_myFiredTrigger->size(); i++) {
    if(vec_myFiredTrigger->at(i).find(path) != std::string::npos) {
      myFired = true;
      break;
    }
  }

  return myFired;
}

vector<Object> MuonHLTNtupleRun3::get_HLTObjects( TString filter )
{
    vector<Object> out = {};
    if(vec_filterName == 0 || vec_filterName == nullptr)
        return out;

    for(unsigned i=0; i<vec_filterName->size(); ++i) {

        TString ifilter = TString(vec_filterName->at(i));
        if( !ifilter.Contains(filter) )
            continue;

        Object obj = Object( vec_HLTObj_pt->at(i), vec_HLTObj_eta->at(i), vec_HLTObj_phi->at(i) );
        obj.addStrVar( "filter", ifilter );
        obj.addVar( "pt", vec_HLTObj_pt->at(i) );
        obj.addVar( "eta", vec_HLTObj_eta->at(i) );
        obj.addVar( "phi", vec_HLTObj_phi->at(i) );
        

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_myHLTObjects( TString filter )
{
    vector<Object> out = {};
    if(vec_myFilterName == 0 || vec_myFilterName == nullptr)
        return out;

    for(unsigned i=0; i<vec_myFilterName->size(); ++i) {

        TString ifilter = TString(vec_myFilterName->at(i));
        if( !ifilter.Contains(filter) )
            continue;

        Object obj = Object( vec_myHLTObj_pt->at(i), vec_myHLTObj_eta->at(i), vec_myHLTObj_phi->at(i) );

        obj.addStrVar( "filter", ifilter );
        obj.addVar( "pt", vec_myHLTObj_pt->at(i) );
        obj.addVar( "eta", vec_myHLTObj_eta->at(i) );
        obj.addVar( "phi", vec_myHLTObj_phi->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIterL3OIMuonTrackAssociated()
{
    vector<Object> out = {};
    if(hltIterL3OIMuonTrackAssociated_pt == 0 || hltIterL3OIMuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIterL3OIMuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( hltIterL3OIMuonTrackAssociated_pt->at(i), hltIterL3OIMuonTrackAssociated_eta->at(i), hltIterL3OIMuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", hltIterL3OIMuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", hltIterL3OIMuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", hltIterL3OIMuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", hltIterL3OIMuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIterL3OIMuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIterL3OIMuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIterL3OIMuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIterL3OIMuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIterL3OIMuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIterL3OIMuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIterL3OIMuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIterL3OIMuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIterL3OIMuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIterL3OIMuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIter0IterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(hltIter0IterL3MuonTrackAssociated_pt == 0 || hltIter0IterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIter0IterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( hltIter0IterL3MuonTrackAssociated_pt->at(i), hltIter0IterL3MuonTrackAssociated_eta->at(i), hltIter0IterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", hltIter0IterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", hltIter0IterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", hltIter0IterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", hltIter0IterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIter0IterL3MuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIter0IterL3MuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIter0IterL3MuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIter0IterL3MuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIter0IterL3MuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIter2IterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(hltIter2IterL3MuonTrackAssociated_pt == 0 || hltIter2IterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIter2IterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( hltIter2IterL3MuonTrackAssociated_pt->at(i), hltIter2IterL3MuonTrackAssociated_eta->at(i), hltIter2IterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", hltIter2IterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", hltIter2IterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", hltIter2IterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", hltIter2IterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIter2IterL3MuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIter2IterL3MuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIter2IterL3MuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIter2IterL3MuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIter2IterL3MuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIter0IterL3FromL1MuonTrackAssociated()
{
    vector<Object> out = {};
    if(hltIter0IterL3FromL1MuonTrackAssociated_pt == 0 || hltIter0IterL3FromL1MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIter0IterL3FromL1MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( hltIter0IterL3FromL1MuonTrackAssociated_pt->at(i), hltIter0IterL3FromL1MuonTrackAssociated_eta->at(i), hltIter0IterL3FromL1MuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", hltIter0IterL3FromL1MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", hltIter0IterL3FromL1MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", hltIter0IterL3FromL1MuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", hltIter0IterL3FromL1MuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIter0IterL3FromL1MuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIter0IterL3FromL1MuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIter2IterL3FromL1MuonTrackAssociated()
{
    vector<Object> out = {};
    if(hltIter2IterL3FromL1MuonTrackAssociated_pt == 0 || hltIter2IterL3FromL1MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIter2IterL3FromL1MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( hltIter2IterL3FromL1MuonTrackAssociated_pt->at(i), hltIter2IterL3FromL1MuonTrackAssociated_eta->at(i), hltIter2IterL3FromL1MuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", hltIter2IterL3FromL1MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", hltIter2IterL3FromL1MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", hltIter2IterL3FromL1MuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", hltIter2IterL3FromL1MuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIter2IterL3FromL1MuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIter2IterL3FromL1MuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIterL3MuonMergedAssociated()
{
    vector<Object> out = {};
    if(hltIterL3MuonMergedAssociated_pt == 0 || hltIterL3MuonMergedAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIterL3MuonMergedAssociated_pt->size(); ++i) {
        Object obj = Object( hltIterL3MuonMergedAssociated_pt->at(i), hltIterL3MuonMergedAssociated_eta->at(i), hltIterL3MuonMergedAssociated_phi->at(i) );

        obj.addVar( "pt", hltIterL3MuonMergedAssociated_pt->at(i) );
        obj.addVar( "eta", hltIterL3MuonMergedAssociated_eta->at(i) );
        obj.addVar( "phi", hltIterL3MuonMergedAssociated_phi->at(i) );
        obj.addVar( "charge", hltIterL3MuonMergedAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIterL3MuonMergedAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIterL3MuonMergedAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIterL3MuonMergedAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIterL3MuonMergedAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIterL3MuonMergedAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIterL3MuonMergedAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIterL3MuonMergedAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIterL3MuonMergedAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIterL3MuonMergedAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIterL3MuonMergedAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIterL3MuonMergedAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIterL3MuonMergedAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIterL3MuonMergedAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIterL3MuonMergedAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltIterL3MuonAndMuonFromL1MergedAssociated()
{
    vector<Object> out = {};
    if(hltIterL3MuonAndMuonFromL1MergedAssociated_pt == 0 || hltIterL3MuonAndMuonFromL1MergedAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltIterL3MuonAndMuonFromL1MergedAssociated_pt->size(); ++i) {
        Object obj = Object( hltIterL3MuonAndMuonFromL1MergedAssociated_pt->at(i), hltIterL3MuonAndMuonFromL1MergedAssociated_eta->at(i), hltIterL3MuonAndMuonFromL1MergedAssociated_phi->at(i) );

        obj.addVar( "pt", hltIterL3MuonAndMuonFromL1MergedAssociated_pt->at(i) );
        obj.addVar( "eta", hltIterL3MuonAndMuonFromL1MergedAssociated_eta->at(i) );
        obj.addVar( "phi", hltIterL3MuonAndMuonFromL1MergedAssociated_phi->at(i) );
        obj.addVar( "charge", hltIterL3MuonAndMuonFromL1MergedAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltIterL3MuonAndMuonFromL1MergedAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3MuonNoIDTrackAssociated()
{
    vector<Object> out = {};
    if(iterL3MuonNoIDTrackAssociated_pt == 0 || iterL3MuonNoIDTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<iterL3MuonNoIDTrackAssociated_pt->size(); ++i) {
        Object obj = Object( iterL3MuonNoIDTrackAssociated_pt->at(i), iterL3MuonNoIDTrackAssociated_eta->at(i), iterL3MuonNoIDTrackAssociated_phi->at(i) );

        obj.addVar( "pt", iterL3MuonNoIDTrackAssociated_pt->at(i) );
        obj.addVar( "eta", iterL3MuonNoIDTrackAssociated_eta->at(i) );
        obj.addVar( "phi", iterL3MuonNoIDTrackAssociated_phi->at(i) );
        obj.addVar( "charge", iterL3MuonNoIDTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", iterL3MuonNoIDTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", iterL3MuonNoIDTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", iterL3MuonNoIDTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", iterL3MuonNoIDTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", iterL3MuonNoIDTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", iterL3MuonNoIDTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", iterL3MuonNoIDTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", iterL3MuonNoIDTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", iterL3MuonNoIDTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", iterL3MuonNoIDTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_iterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(iterL3MuonTrackAssociated_pt == 0 || iterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<iterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( iterL3MuonTrackAssociated_pt->at(i), iterL3MuonTrackAssociated_eta->at(i), iterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "pt", iterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", iterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", iterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "charge", iterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "matchedL3", iterL3MuonTrackAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", iterL3MuonTrackAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", iterL3MuonTrackAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", iterL3MuonTrackAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", iterL3MuonTrackAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", iterL3MuonTrackAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", iterL3MuonTrackAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", iterL3MuonTrackAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", iterL3MuonTrackAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", iterL3MuonTrackAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", iterL3MuonTrackAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", iterL3MuonTrackAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", iterL3MuonTrackAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", iterL3MuonTrackAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", iterL3MuonTrackAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", iterL3MuonTrackAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltPixelTracksAssociated()
{
  vector<Object> out = {};
  if(hltPixelTracksAssociated_pt == 0 || hltPixelTracksAssociated_pt == nullptr)
    return out;

  for(unsigned i=0; i<hltPixelTracksAssociated_pt->size(); ++i) {
    Object obj = Object( hltPixelTracksAssociated_pt->at(i), hltPixelTracksAssociated_eta->at(i), hltPixelTracksAssociated_phi->at(i) );

    obj.addVar( "pt", hltPixelTracksAssociated_pt->at(i) );
    obj.addVar( "eta", hltPixelTracksAssociated_eta->at(i) );
    obj.addVar( "phi", hltPixelTracksAssociated_phi->at(i) );
    obj.addVar( "charge", hltPixelTracksAssociated_charge->at(i) );
    obj.addVar( "matchedL3", hltPixelTracksAssociated_matchedL3->at(i) );
    obj.addVar( "matchedL3NoId", hltPixelTracksAssociated_matchedL3NoId->at(i) );
    obj.addVar( "bestMatchTP_charge", hltPixelTracksAssociated_bestMatchTP_charge->at(i) );
    obj.addVar( "bestMatchTP_pdgId", hltPixelTracksAssociated_bestMatchTP_pdgId->at(i) );
    obj.addVar( "bestMatchTP_energy", hltPixelTracksAssociated_bestMatchTP_energy->at(i) );
    obj.addVar( "bestMatchTP_pt", hltPixelTracksAssociated_bestMatchTP_pt->at(i) );
    obj.addVar( "bestMatchTP_eta", hltPixelTracksAssociated_bestMatchTP_eta->at(i) );
    obj.addVar( "bestMatchTP_phi", hltPixelTracksAssociated_bestMatchTP_phi->at(i) );
    obj.addVar( "bestMatchTP_parentVx", hltPixelTracksAssociated_bestMatchTP_parentVx->at(i) );
    obj.addVar( "bestMatchTP_parentVy", hltPixelTracksAssociated_bestMatchTP_parentVy->at(i) );
    obj.addVar( "bestMatchTP_parentVz", hltPixelTracksAssociated_bestMatchTP_parentVz->at(i) );
    obj.addVar( "bestMatchTP_status", hltPixelTracksAssociated_bestMatchTP_status->at(i) );
    obj.addVar( "bestMatchTP_numberOfHits", hltPixelTracksAssociated_bestMatchTP_numberOfHits->at(i) );
    obj.addVar( "bestMatchTP_numberOfTrackerHits", hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
    obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
    obj.addVar( "bestMatchTP_sharedFraction", hltPixelTracksAssociated_bestMatchTP_sharedFraction->at(i) );
    obj.addVar( "matchedTPsize", hltPixelTracksAssociated_matchedTPsize->at(i) );
    obj.addVar( "mva", hltPixelTracksAssociated_mva->at(i) );

    out.push_back(obj);
  }

  return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltPixelTracksInRegionL2Associated()
{
    vector<Object> out = {};
    if(hltPixelTracksInRegionL2Associated_pt == 0 || hltPixelTracksInRegionL2Associated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltPixelTracksInRegionL2Associated_pt->size(); ++i) {
        Object obj = Object( hltPixelTracksInRegionL2Associated_pt->at(i), hltPixelTracksInRegionL2Associated_eta->at(i), hltPixelTracksInRegionL2Associated_phi->at(i) );

        obj.addVar( "pt", hltPixelTracksInRegionL2Associated_pt->at(i) );
        obj.addVar( "eta", hltPixelTracksInRegionL2Associated_eta->at(i) );
        obj.addVar( "phi", hltPixelTracksInRegionL2Associated_phi->at(i) );
        obj.addVar( "charge", hltPixelTracksInRegionL2Associated_charge->at(i) );
        obj.addVar( "matchedL3", hltPixelTracksInRegionL2Associated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltPixelTracksInRegionL2Associated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltPixelTracksInRegionL2Associated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltPixelTracksInRegionL2Associated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltPixelTracksInRegionL2Associated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltPixelTracksInRegionL2Associated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltPixelTracksInRegionL2Associated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltPixelTracksInRegionL2Associated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltPixelTracksInRegionL2Associated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltPixelTracksInRegionL2Associated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltPixelTracksInRegionL1Associated()
{
    vector<Object> out = {};
    if(hltPixelTracksInRegionL1Associated_pt == 0 || hltPixelTracksInRegionL1Associated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltPixelTracksInRegionL1Associated_pt->size(); ++i) {
        Object obj = Object( hltPixelTracksInRegionL1Associated_pt->at(i), hltPixelTracksInRegionL1Associated_eta->at(i), hltPixelTracksInRegionL1Associated_phi->at(i) );

        obj.addVar( "pt", hltPixelTracksInRegionL1Associated_pt->at(i) );
        obj.addVar( "eta", hltPixelTracksInRegionL1Associated_eta->at(i) );
        obj.addVar( "phi", hltPixelTracksInRegionL1Associated_phi->at(i) );
        obj.addVar( "charge", hltPixelTracksInRegionL1Associated_charge->at(i) );
        obj.addVar( "matchedL3", hltPixelTracksInRegionL1Associated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltPixelTracksInRegionL1Associated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltPixelTracksInRegionL1Associated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltPixelTracksInRegionL1Associated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltPixelTracksInRegionL1Associated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltPixelTracksInRegionL1Associated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltPixelTracksInRegionL1Associated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltPixelTracksInRegionL1Associated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltPixelTracksInRegionL1Associated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltPixelTracksInRegionL1Associated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltPixelTracksForSeedsL3MuonAssociated()
{
    vector<Object> out = {};
    if(hltPixelTracksForSeedsL3MuonAssociated_pt == 0 || hltPixelTracksForSeedsL3MuonAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltPixelTracksForSeedsL3MuonAssociated_pt->size(); ++i) {
        Object obj = Object( hltPixelTracksForSeedsL3MuonAssociated_pt->at(i), hltPixelTracksForSeedsL3MuonAssociated_eta->at(i), hltPixelTracksForSeedsL3MuonAssociated_phi->at(i) );

        obj.addVar( "pt", hltPixelTracksForSeedsL3MuonAssociated_pt->at(i) );
        obj.addVar( "eta", hltPixelTracksForSeedsL3MuonAssociated_eta->at(i) );
        obj.addVar( "phi", hltPixelTracksForSeedsL3MuonAssociated_phi->at(i) );
        obj.addVar( "charge", hltPixelTracksForSeedsL3MuonAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltPixelTracksForSeedsL3MuonAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltPixelTracksForSeedsL3MuonAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_hltGlbTrkMuonTracksAssociated()
{
    vector<Object> out = {};
    if(hltGlbTrkMuonTracksAssociated_pt == 0 || hltGlbTrkMuonTracksAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<hltGlbTrkMuonTracksAssociated_pt->size(); ++i) {
        Object obj = Object( hltGlbTrkMuonTracksAssociated_pt->at(i), hltGlbTrkMuonTracksAssociated_eta->at(i), hltGlbTrkMuonTracksAssociated_phi->at(i) );

        obj.addVar( "pt", hltGlbTrkMuonTracksAssociated_pt->at(i) );
        obj.addVar( "eta", hltGlbTrkMuonTracksAssociated_eta->at(i) );
        obj.addVar( "phi", hltGlbTrkMuonTracksAssociated_phi->at(i) );
        obj.addVar( "charge", hltGlbTrkMuonTracksAssociated_charge->at(i) );
        obj.addVar( "matchedL3", hltGlbTrkMuonTracksAssociated_matchedL3->at(i) );
        obj.addVar( "matchedL3NoId", hltGlbTrkMuonTracksAssociated_matchedL3NoId->at(i) );
        obj.addVar( "bestMatchTP_charge", hltGlbTrkMuonTracksAssociated_bestMatchTP_charge->at(i) );
        obj.addVar( "bestMatchTP_pdgId", hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId->at(i) );
        obj.addVar( "bestMatchTP_energy", hltGlbTrkMuonTracksAssociated_bestMatchTP_energy->at(i) );
        obj.addVar( "bestMatchTP_pt", hltGlbTrkMuonTracksAssociated_bestMatchTP_pt->at(i) );
        obj.addVar( "bestMatchTP_eta", hltGlbTrkMuonTracksAssociated_bestMatchTP_eta->at(i) );
        obj.addVar( "bestMatchTP_phi", hltGlbTrkMuonTracksAssociated_bestMatchTP_phi->at(i) );
        obj.addVar( "bestMatchTP_parentVx", hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx->at(i) );
        obj.addVar( "bestMatchTP_parentVy", hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy->at(i) );
        obj.addVar( "bestMatchTP_parentVz", hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz->at(i) );
        obj.addVar( "bestMatchTP_status", hltGlbTrkMuonTracksAssociated_bestMatchTP_status->at(i) );
        obj.addVar( "bestMatchTP_numberOfHits", hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerHits", hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits->at(i) );
        obj.addVar( "bestMatchTP_numberOfTrackerLayers", hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers->at(i) );
        obj.addVar( "bestMatchTP_sharedFraction", hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction->at(i) );
        obj.addVar( "matchedTPsize", hltGlbTrkMuonTracksAssociated_matchedTPsize->at(i) );
        obj.addVar( "mva", hltGlbTrkMuonTracksAssociated_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIterL3OIMuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIterL3OIMuonTrackAssociated_pt == 0 || tpTo_hltIterL3OIMuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIterL3OIMuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIterL3OIMuonTrackAssociated_pt->at(i), tpTo_hltIterL3OIMuonTrackAssociated_eta->at(i), tpTo_hltIterL3OIMuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIterL3OIMuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIterL3OIMuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIterL3OIMuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIterL3OIMuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIterL3OIMuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIterL3OIMuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIterL3OIMuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIterL3OIMuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIterL3OIMuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIterL3OIMuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIterL3OIMuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIterL3OIMuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIterL3OIMuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIterL3OIMuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIter0IterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIter0IterL3MuonTrackAssociated_pt == 0 || tpTo_hltIter0IterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIter0IterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIter0IterL3MuonTrackAssociated_pt->at(i), tpTo_hltIter0IterL3MuonTrackAssociated_eta->at(i), tpTo_hltIter0IterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIter0IterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIter0IterL3MuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIter0IterL3MuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIter0IterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIter0IterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIter0IterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIter0IterL3MuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIter0IterL3MuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIter0IterL3MuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIter0IterL3MuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIter2IterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIter2IterL3MuonTrackAssociated_pt == 0 || tpTo_hltIter2IterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIter2IterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIter2IterL3MuonTrackAssociated_pt->at(i), tpTo_hltIter2IterL3MuonTrackAssociated_eta->at(i), tpTo_hltIter2IterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIter2IterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIter2IterL3MuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIter2IterL3MuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIter2IterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIter2IterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIter2IterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIter2IterL3MuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIter2IterL3MuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIter2IterL3MuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIter2IterL3MuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIter0IterL3FromL1MuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt == 0 || tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt->at(i), tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta->at(i), tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIter2IterL3FromL1MuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt == 0 || tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt->at(i), tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta->at(i), tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIterL3MuonMergedAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIterL3MuonMergedAssociated_pt == 0 || tpTo_hltIterL3MuonMergedAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIterL3MuonMergedAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIterL3MuonMergedAssociated_pt->at(i), tpTo_hltIterL3MuonMergedAssociated_eta->at(i), tpTo_hltIterL3MuonMergedAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIterL3MuonMergedAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIterL3MuonMergedAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIterL3MuonMergedAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIterL3MuonMergedAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIterL3MuonMergedAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIterL3MuonMergedAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIterL3MuonMergedAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIterL3MuonMergedAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIterL3MuonMergedAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIterL3MuonMergedAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIterL3MuonMergedAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIterL3MuonMergedAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIterL3MuonMergedAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIterL3MuonMergedAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIterL3MuonMergedAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIterL3MuonMergedAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt == 0 || tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt->at(i), tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta->at(i), tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_iterL3MuonNoIDTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_iterL3MuonNoIDTrackAssociated_pt == 0 || tpTo_iterL3MuonNoIDTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_iterL3MuonNoIDTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_iterL3MuonNoIDTrackAssociated_pt->at(i), tpTo_iterL3MuonNoIDTrackAssociated_eta->at(i), tpTo_iterL3MuonNoIDTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_iterL3MuonNoIDTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_iterL3MuonNoIDTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_iterL3MuonNoIDTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_iterL3MuonNoIDTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_iterL3MuonNoIDTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_iterL3MuonNoIDTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_iterL3MuonNoIDTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_iterL3MuonNoIDTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_iterL3MuonNoIDTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_iterL3MuonNoIDTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_iterL3MuonNoIDTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_iterL3MuonNoIDTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_iterL3MuonNoIDTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_iterL3MuonNoIDTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_iterL3MuonTrackAssociated()
{
    vector<Object> out = {};
    if(tpTo_iterL3MuonTrackAssociated_pt == 0 || tpTo_iterL3MuonTrackAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_iterL3MuonTrackAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_iterL3MuonTrackAssociated_pt->at(i), tpTo_iterL3MuonTrackAssociated_eta->at(i), tpTo_iterL3MuonTrackAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_iterL3MuonTrackAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_iterL3MuonTrackAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_iterL3MuonTrackAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_iterL3MuonTrackAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_iterL3MuonTrackAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_iterL3MuonTrackAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_iterL3MuonTrackAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_iterL3MuonTrackAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_iterL3MuonTrackAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_iterL3MuonTrackAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_iterL3MuonTrackAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_iterL3MuonTrackAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_iterL3MuonTrackAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_iterL3MuonTrackAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_iterL3MuonTrackAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_iterL3MuonTrackAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_iterL3MuonTrackAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltPixelTracksInRegionL2Associated()
{
    vector<Object> out = {};
    if(tpTo_hltPixelTracksInRegionL2Associated_pt == 0 || tpTo_hltPixelTracksInRegionL2Associated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltPixelTracksInRegionL2Associated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltPixelTracksInRegionL2Associated_pt->at(i), tpTo_hltPixelTracksInRegionL2Associated_eta->at(i), tpTo_hltPixelTracksInRegionL2Associated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltPixelTracksInRegionL2Associated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltPixelTracksInRegionL2Associated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltPixelTracksInRegionL2Associated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltPixelTracksInRegionL2Associated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltPixelTracksInRegionL2Associated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltPixelTracksInRegionL2Associated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltPixelTracksInRegionL2Associated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltPixelTracksInRegionL2Associated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltPixelTracksInRegionL2Associated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltPixelTracksInRegionL2Associated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltPixelTracksInRegionL2Associated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltPixelTracksInRegionL2Associated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltPixelTracksInRegionL2Associated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltPixelTracksInRegionL2Associated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltPixelTracksInRegionL2Associated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltPixelTracksInRegionL1Associated()
{
    vector<Object> out = {};
    if(tpTo_hltPixelTracksInRegionL1Associated_pt == 0 || tpTo_hltPixelTracksInRegionL1Associated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltPixelTracksInRegionL1Associated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltPixelTracksInRegionL1Associated_pt->at(i), tpTo_hltPixelTracksInRegionL1Associated_eta->at(i), tpTo_hltPixelTracksInRegionL1Associated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltPixelTracksInRegionL1Associated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltPixelTracksInRegionL1Associated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltPixelTracksInRegionL1Associated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltPixelTracksInRegionL1Associated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltPixelTracksInRegionL1Associated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltPixelTracksInRegionL1Associated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltPixelTracksInRegionL1Associated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltPixelTracksInRegionL1Associated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltPixelTracksInRegionL1Associated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltPixelTracksInRegionL1Associated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltPixelTracksInRegionL1Associated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltPixelTracksInRegionL1Associated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltPixelTracksInRegionL1Associated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltPixelTracksInRegionL1Associated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltPixelTracksInRegionL1Associated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltPixelTracksForSeedsL3MuonAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt == 0 || tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt->at(i), tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta->at(i), tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltPixelTracksForSeedsL3MuonAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}

vector<Object> MuonHLTNtupleRun3::get_tpTo_hltGlbTrkMuonTracksAssociated()
{
    vector<Object> out = {};
    if(tpTo_hltGlbTrkMuonTracksAssociated_pt == 0 || tpTo_hltGlbTrkMuonTracksAssociated_pt == nullptr)
        return out;

    for(unsigned i=0; i<tpTo_hltGlbTrkMuonTracksAssociated_pt->size(); ++i) {
        Object obj = Object( tpTo_hltGlbTrkMuonTracksAssociated_pt->at(i), tpTo_hltGlbTrkMuonTracksAssociated_eta->at(i), tpTo_hltGlbTrkMuonTracksAssociated_phi->at(i) );

        obj.addVar( "charge", tpTo_hltGlbTrkMuonTracksAssociated_charge->at(i) );
        obj.addVar( "pdgId", tpTo_hltGlbTrkMuonTracksAssociated_pdgId->at(i) );
        obj.addVar( "energy", tpTo_hltGlbTrkMuonTracksAssociated_energy->at(i) );
        obj.addVar( "pt", tpTo_hltGlbTrkMuonTracksAssociated_pt->at(i) );
        obj.addVar( "eta", tpTo_hltGlbTrkMuonTracksAssociated_eta->at(i) );
        obj.addVar( "phi", tpTo_hltGlbTrkMuonTracksAssociated_phi->at(i) );
        obj.addVar( "parentVx", tpTo_hltGlbTrkMuonTracksAssociated_parentVx->at(i) );
        obj.addVar( "parentVy", tpTo_hltGlbTrkMuonTracksAssociated_parentVy->at(i) );
        obj.addVar( "parentVz", tpTo_hltGlbTrkMuonTracksAssociated_parentVz->at(i) );
        obj.addVar( "status", tpTo_hltGlbTrkMuonTracksAssociated_status->at(i) );
        obj.addVar( "numberOfHits", tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits->at(i) );
        obj.addVar( "numberOfTrackerHits", tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits->at(i) );
        obj.addVar( "numberOfTrackerLayers", tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers->at(i) );
        obj.addVar( "gen_charge", tpTo_hltGlbTrkMuonTracksAssociated_gen_charge->at(i) );
        obj.addVar( "gen_pdgId", tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId->at(i) );
        obj.addVar( "gen_pt", tpTo_hltGlbTrkMuonTracksAssociated_gen_pt->at(i) );
        obj.addVar( "gen_eta", tpTo_hltGlbTrkMuonTracksAssociated_gen_eta->at(i) );
        obj.addVar( "gen_phi", tpTo_hltGlbTrkMuonTracksAssociated_gen_phi->at(i) );
        obj.addVar( "bestMatchTrk_pt", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt->at(i) );
        obj.addVar( "bestMatchTrk_eta", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta->at(i) );
        obj.addVar( "bestMatchTrk_phi", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi->at(i) );
        obj.addVar( "bestMatchTrk_charge", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge->at(i) );
        obj.addVar( "bestMatchTrk_px", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px->at(i) );
        obj.addVar( "bestMatchTrk_py", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py->at(i) );
        obj.addVar( "bestMatchTrk_pz", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz->at(i) );
        obj.addVar( "bestMatchTrk_vx", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx->at(i) );
        obj.addVar( "bestMatchTrk_vy", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy->at(i) );
        obj.addVar( "bestMatchTrk_vz", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz->at(i) );
        obj.addVar( "bestMatchTrk_dxy_bs", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs->at(i) );
        obj.addVar( "bestMatchTrk_dxyError_bs", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs->at(i) );
        obj.addVar( "bestMatchTrk_dz_bs", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs->at(i) );
        obj.addVar( "bestMatchTrk_dzError", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError->at(i) );
        obj.addVar( "bestMatchTrk_normalizedChi2", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2->at(i) );
        obj.addVar( "bestMatchTrk_quality", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality->at(i) );
        obj.addVar( "bestMatchTrk_NValidHits", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits->at(i) );
        // obj.addVar( "bestMatchTrk_mva", tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_mva->at(i) );

        out.push_back(obj);
    }

    return out;
}



MuonHLTNtupleRun3::MuonHLTNtupleRun3(TChain *tree, vector<TString> branch_tags) : fChain(0) 
{
    Init(tree);

    fChain->SetBranchStatus( "*", 0 );
    for( auto& tag: branch_tags) {
        fChain->SetBranchStatus( tag+"*", 1 );
    }

    fChain->SetBranchStatus( "n*", 1 );
    fChain->SetBranchStatus( "isRealData", 1 );
    fChain->SetBranchStatus( "runNum", 1 );
    fChain->SetBranchStatus( "lumiBlockNum", 1 );
    fChain->SetBranchStatus( "eventNum", 1 );
    fChain->SetBranchStatus( "nVertex", 1 );
    fChain->SetBranchStatus( "truePU", 1 );

    // fChain->SetBranchStatus( "InstLumi", 1 );
    // fChain->SetBranchStatus( "DataPU", 1 );
    // fChain->SetBranchStatus( "qScale", 1 );
    fChain->SetBranchStatus( "genEventWeight", 1 );
    // fChain->SetBranchStatus( "PU_pT_hats", 1 );

    branch_names = {};
    TObjArray* listofb = fChain->GetListOfBranches();
    for(const auto b: *listofb) {
        TString name = b->GetName();
        if(fChain->GetBranchStatus(name.Data())) {
            branch_names.push_back(name);
        }
    }
}

MuonHLTNtupleRun3::~MuonHLTNtupleRun3()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t MuonHLTNtupleRun3::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t MuonHLTNtupleRun3::LoadTree(Long64_t entry)
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

void MuonHLTNtupleRun3::Init(TChain *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    muon_l1tpt = 0;
    muon_l1teta = 0;
    muon_l1tpropeta = 0;
    muon_l1tphi = 0;
    muon_l1tpropphi = 0;
    muon_l1tcharge = 0;
    muon_l1tq = 0;
    muon_l1tdr = 0;

    vec_firedTrigger = 0;
    vec_filterName = 0;
    vec_HLTObj_pt = 0;
    vec_HLTObj_eta = 0;
    vec_HLTObj_phi = 0;
    vec_myFiredTrigger = 0;
    vec_myFilterName = 0;
    vec_myHLTObj_pt = 0;
    vec_myHLTObj_eta = 0;
    vec_myHLTObj_phi = 0;
    TP_charge = 0;
    TP_pdgId = 0;
    TP_energy = 0;
    TP_pt = 0;
    TP_eta = 0;
    TP_phi = 0;
    TP_parentVx = 0;
    TP_parentVy = 0;
    TP_parentVz = 0;
    TP_status = 0;
    TP_numberOfHits = 0;
    TP_numberOfTrackerHits = 0;
    TP_numberOfTrackerLayers = 0;
    TP_gen_charge = 0;
    TP_gen_pdgId = 0;
    TP_gen_pt = 0;
    TP_gen_eta = 0;
    TP_gen_phi = 0;
    TP_bestMatchTrk_pt = 0;
    TP_bestMatchTrk_eta = 0;
    TP_bestMatchTrk_phi = 0;
    TP_bestMatchTrk_charge = 0;
    TP_bestMatchTrk_quality = 0;
    TP_bestMatchTrk_NValidHits = 0;
    hltIterL3MuonTrimmedPixelVertices_isValid = 0;
    hltIterL3MuonTrimmedPixelVertices_chi2 = 0;
    hltIterL3MuonTrimmedPixelVertices_ndof = 0;
    hltIterL3MuonTrimmedPixelVertices_nTracks = 0;
    hltIterL3MuonTrimmedPixelVertices_x = 0;
    hltIterL3MuonTrimmedPixelVertices_xerr = 0;
    hltIterL3MuonTrimmedPixelVertices_y = 0;
    hltIterL3MuonTrimmedPixelVertices_yerr = 0;
    hltIterL3MuonTrimmedPixelVertices_z = 0;
    hltIterL3MuonTrimmedPixelVertices_zerr = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_isValid = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_chi2 = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_ndof = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_nTracks = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_x = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_xerr = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_y = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_yerr = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_z = 0;
    hltIterL3FromL1MuonTrimmedPixelVertices_zerr = 0;
    hltIterL3OIMuonTrackAssociated_pt = 0;
    hltIterL3OIMuonTrackAssociated_eta = 0;
    hltIterL3OIMuonTrackAssociated_phi = 0;
    hltIterL3OIMuonTrackAssociated_charge = 0;
    hltIterL3OIMuonTrackAssociated_matchedL3 = 0;
    hltIterL3OIMuonTrackAssociated_matchedL3NoId = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_charge = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_energy = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_pt = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_eta = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_phi = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_status = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    hltIterL3OIMuonTrackAssociated_matchedTPsize = 0;
    hltIterL3OIMuonTrackAssociated_mva = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_charge = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_pdgId = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_energy = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_pt = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_eta = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_phi = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_parentVx = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_parentVy = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_parentVz = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_status = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_gen_charge = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_gen_pt = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_gen_eta = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_gen_phi = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits = 0;
    hltIter0IterL3MuonTrackAssociated_pt = 0;
    hltIter0IterL3MuonTrackAssociated_eta = 0;
    hltIter0IterL3MuonTrackAssociated_phi = 0;
    hltIter0IterL3MuonTrackAssociated_charge = 0;
    hltIter0IterL3MuonTrackAssociated_matchedL3 = 0;
    hltIter0IterL3MuonTrackAssociated_matchedL3NoId = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_status = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    hltIter0IterL3MuonTrackAssociated_matchedTPsize = 0;
    hltIter0IterL3MuonTrackAssociated_mva = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_charge = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_pdgId = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_energy = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_pt = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_eta = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_phi = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_parentVx = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_parentVy = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_parentVz = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_status = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits = 0;
    hltIter2IterL3MuonTrackAssociated_pt = 0;
    hltIter2IterL3MuonTrackAssociated_eta = 0;
    hltIter2IterL3MuonTrackAssociated_phi = 0;
    hltIter2IterL3MuonTrackAssociated_charge = 0;
    hltIter2IterL3MuonTrackAssociated_matchedL3 = 0;
    hltIter2IterL3MuonTrackAssociated_matchedL3NoId = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_status = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    hltIter2IterL3MuonTrackAssociated_matchedTPsize = 0;
    hltIter2IterL3MuonTrackAssociated_mva = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_charge = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_pdgId = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_energy = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_pt = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_eta = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_phi = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_parentVx = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_parentVy = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_parentVz = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_status = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_pt = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_eta = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_phi = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_charge = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_matchedL3 = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize = 0;
    hltIter0IterL3FromL1MuonTrackAssociated_mva = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_pt = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_eta = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_phi = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_charge = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_matchedL3 = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize = 0;
    hltIter2IterL3FromL1MuonTrackAssociated_mva = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits = 0;
    hltIterL3MuonMergedAssociated_pt = 0;
    hltIterL3MuonMergedAssociated_eta = 0;
    hltIterL3MuonMergedAssociated_phi = 0;
    hltIterL3MuonMergedAssociated_charge = 0;
    hltIterL3MuonMergedAssociated_matchedL3 = 0;
    hltIterL3MuonMergedAssociated_matchedL3NoId = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_charge = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_pdgId = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_energy = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_pt = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_eta = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_phi = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_parentVx = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_parentVy = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_parentVz = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_status = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction = 0;
    hltIterL3MuonMergedAssociated_matchedTPsize = 0;
    hltIterL3MuonMergedAssociated_mva = 0;
    tpTo_hltIterL3MuonMergedAssociated_charge = 0;
    tpTo_hltIterL3MuonMergedAssociated_pdgId = 0;
    tpTo_hltIterL3MuonMergedAssociated_energy = 0;
    tpTo_hltIterL3MuonMergedAssociated_pt = 0;
    tpTo_hltIterL3MuonMergedAssociated_eta = 0;
    tpTo_hltIterL3MuonMergedAssociated_phi = 0;
    tpTo_hltIterL3MuonMergedAssociated_parentVx = 0;
    tpTo_hltIterL3MuonMergedAssociated_parentVy = 0;
    tpTo_hltIterL3MuonMergedAssociated_parentVz = 0;
    tpTo_hltIterL3MuonMergedAssociated_status = 0;
    tpTo_hltIterL3MuonMergedAssociated_numberOfHits = 0;
    tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits = 0;
    tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIterL3MuonMergedAssociated_gen_charge = 0;
    tpTo_hltIterL3MuonMergedAssociated_gen_pdgId = 0;
    tpTo_hltIterL3MuonMergedAssociated_gen_pt = 0;
    tpTo_hltIterL3MuonMergedAssociated_gen_eta = 0;
    tpTo_hltIterL3MuonMergedAssociated_gen_phi = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_pt = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_eta = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_phi = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_charge = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3 = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize = 0;
    hltIterL3MuonAndMuonFromL1MergedAssociated_mva = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality = 0;
    tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits = 0;
    iterL3MuonNoIDTrackAssociated_pt = 0;
    iterL3MuonNoIDTrackAssociated_eta = 0;
    iterL3MuonNoIDTrackAssociated_phi = 0;
    iterL3MuonNoIDTrackAssociated_charge = 0;
    iterL3MuonNoIDTrackAssociated_matchedL3 = 0;
    iterL3MuonNoIDTrackAssociated_matchedL3NoId = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_charge = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_energy = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_pt = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_eta = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_phi = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_status = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction = 0;
    iterL3MuonNoIDTrackAssociated_matchedTPsize = 0;
    iterL3MuonNoIDTrackAssociated_mva = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_charge = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_pdgId = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_energy = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_pt = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_eta = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_phi = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_parentVx = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_parentVy = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_parentVz = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_status = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_gen_charge = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_gen_pt = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_gen_eta = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_gen_phi = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits = 0;
    iterL3MuonTrackAssociated_pt = 0;
    iterL3MuonTrackAssociated_eta = 0;
    iterL3MuonTrackAssociated_phi = 0;
    iterL3MuonTrackAssociated_charge = 0;
    iterL3MuonTrackAssociated_matchedL3 = 0;
    iterL3MuonTrackAssociated_matchedL3NoId = 0;
    iterL3MuonTrackAssociated_bestMatchTP_charge = 0;
    iterL3MuonTrackAssociated_bestMatchTP_pdgId = 0;
    iterL3MuonTrackAssociated_bestMatchTP_energy = 0;
    iterL3MuonTrackAssociated_bestMatchTP_pt = 0;
    iterL3MuonTrackAssociated_bestMatchTP_eta = 0;
    iterL3MuonTrackAssociated_bestMatchTP_phi = 0;
    iterL3MuonTrackAssociated_bestMatchTP_parentVx = 0;
    iterL3MuonTrackAssociated_bestMatchTP_parentVy = 0;
    iterL3MuonTrackAssociated_bestMatchTP_parentVz = 0;
    iterL3MuonTrackAssociated_bestMatchTP_status = 0;
    iterL3MuonTrackAssociated_bestMatchTP_numberOfHits = 0;
    iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits = 0;
    iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    iterL3MuonTrackAssociated_bestMatchTP_sharedFraction = 0;
    iterL3MuonTrackAssociated_matchedTPsize = 0;
    iterL3MuonTrackAssociated_mva = 0;
    tpTo_iterL3MuonTrackAssociated_charge = 0;
    tpTo_iterL3MuonTrackAssociated_pdgId = 0;
    tpTo_iterL3MuonTrackAssociated_energy = 0;
    tpTo_iterL3MuonTrackAssociated_pt = 0;
    tpTo_iterL3MuonTrackAssociated_eta = 0;
    tpTo_iterL3MuonTrackAssociated_phi = 0;
    tpTo_iterL3MuonTrackAssociated_parentVx = 0;
    tpTo_iterL3MuonTrackAssociated_parentVy = 0;
    tpTo_iterL3MuonTrackAssociated_parentVz = 0;
    tpTo_iterL3MuonTrackAssociated_status = 0;
    tpTo_iterL3MuonTrackAssociated_numberOfHits = 0;
    tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits = 0;
    tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers = 0;
    tpTo_iterL3MuonTrackAssociated_gen_charge = 0;
    tpTo_iterL3MuonTrackAssociated_gen_pdgId = 0;
    tpTo_iterL3MuonTrackAssociated_gen_pt = 0;
    tpTo_iterL3MuonTrackAssociated_gen_eta = 0;
    tpTo_iterL3MuonTrackAssociated_gen_phi = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality = 0;
    tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits = 0;

    hltPixelTracksAssociated_pt = 0;
    hltPixelTracksAssociated_eta = 0;
    hltPixelTracksAssociated_phi = 0;
    hltPixelTracksAssociated_charge = 0;
    hltPixelTracksAssociated_matchedL3 = 0;
    hltPixelTracksAssociated_matchedL3NoId = 0;
    hltPixelTracksAssociated_bestMatchTP_charge = 0;
    hltPixelTracksAssociated_bestMatchTP_pdgId = 0;
    hltPixelTracksAssociated_bestMatchTP_energy = 0;
    hltPixelTracksAssociated_bestMatchTP_pt = 0;
    hltPixelTracksAssociated_bestMatchTP_eta = 0;
    hltPixelTracksAssociated_bestMatchTP_phi = 0;
    hltPixelTracksAssociated_bestMatchTP_parentVx = 0;
    hltPixelTracksAssociated_bestMatchTP_parentVy = 0;
    hltPixelTracksAssociated_bestMatchTP_parentVz = 0;
    hltPixelTracksAssociated_bestMatchTP_status = 0;
    hltPixelTracksAssociated_bestMatchTP_numberOfHits = 0;
    hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltPixelTracksAssociated_bestMatchTP_sharedFraction = 0;
    hltPixelTracksAssociated_matchedTPsize = 0;
    hltPixelTracksAssociated_mva = 0;

    hltPixelTracksInRegionL2Associated_pt = 0;
    hltPixelTracksInRegionL2Associated_eta = 0;
    hltPixelTracksInRegionL2Associated_phi = 0;
    hltPixelTracksInRegionL2Associated_charge = 0;
    hltPixelTracksInRegionL2Associated_matchedL3 = 0;
    hltPixelTracksInRegionL2Associated_matchedL3NoId = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_charge = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_energy = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_pt = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_eta = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_phi = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_status = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers = 0;
    hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction = 0;
    hltPixelTracksInRegionL2Associated_matchedTPsize = 0;
    hltPixelTracksInRegionL2Associated_mva = 0;
    tpTo_hltPixelTracksInRegionL2Associated_charge = 0;
    tpTo_hltPixelTracksInRegionL2Associated_pdgId = 0;
    tpTo_hltPixelTracksInRegionL2Associated_energy = 0;
    tpTo_hltPixelTracksInRegionL2Associated_pt = 0;
    tpTo_hltPixelTracksInRegionL2Associated_eta = 0;
    tpTo_hltPixelTracksInRegionL2Associated_phi = 0;
    tpTo_hltPixelTracksInRegionL2Associated_parentVx = 0;
    tpTo_hltPixelTracksInRegionL2Associated_parentVy = 0;
    tpTo_hltPixelTracksInRegionL2Associated_parentVz = 0;
    tpTo_hltPixelTracksInRegionL2Associated_status = 0;
    tpTo_hltPixelTracksInRegionL2Associated_numberOfHits = 0;
    tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits = 0;
    tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers = 0;
    tpTo_hltPixelTracksInRegionL2Associated_gen_charge = 0;
    tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId = 0;
    tpTo_hltPixelTracksInRegionL2Associated_gen_pt = 0;
    tpTo_hltPixelTracksInRegionL2Associated_gen_eta = 0;
    tpTo_hltPixelTracksInRegionL2Associated_gen_phi = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality = 0;
    tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits = 0;


    hltPixelTracksInRegionL1Associated_pt = 0;
    hltPixelTracksInRegionL1Associated_eta = 0;
    hltPixelTracksInRegionL1Associated_phi = 0;
    hltPixelTracksInRegionL1Associated_charge = 0;
    hltPixelTracksInRegionL1Associated_matchedL3 = 0;
    hltPixelTracksInRegionL1Associated_matchedL3NoId = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_charge = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_energy = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_pt = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_eta = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_phi = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_status = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers = 0;
    hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction = 0;
    hltPixelTracksInRegionL1Associated_matchedTPsize = 0;
    hltPixelTracksInRegionL1Associated_mva = 0;
    tpTo_hltPixelTracksInRegionL1Associated_charge = 0;
    tpTo_hltPixelTracksInRegionL1Associated_pdgId = 0;
    tpTo_hltPixelTracksInRegionL1Associated_energy = 0;
    tpTo_hltPixelTracksInRegionL1Associated_pt = 0;
    tpTo_hltPixelTracksInRegionL1Associated_eta = 0;
    tpTo_hltPixelTracksInRegionL1Associated_phi = 0;
    tpTo_hltPixelTracksInRegionL1Associated_parentVx = 0;
    tpTo_hltPixelTracksInRegionL1Associated_parentVy = 0;
    tpTo_hltPixelTracksInRegionL1Associated_parentVz = 0;
    tpTo_hltPixelTracksInRegionL1Associated_status = 0;
    tpTo_hltPixelTracksInRegionL1Associated_numberOfHits = 0;
    tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits = 0;
    tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers = 0;
    tpTo_hltPixelTracksInRegionL1Associated_gen_charge = 0;
    tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId = 0;
    tpTo_hltPixelTracksInRegionL1Associated_gen_pt = 0;
    tpTo_hltPixelTracksInRegionL1Associated_gen_eta = 0;
    tpTo_hltPixelTracksInRegionL1Associated_gen_phi = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality = 0;
    tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits = 0;


    hltPixelTracksForSeedsL3MuonAssociated_pt = 0;
    hltPixelTracksForSeedsL3MuonAssociated_eta = 0;
    hltPixelTracksForSeedsL3MuonAssociated_phi = 0;
    hltPixelTracksForSeedsL3MuonAssociated_charge = 0;
    hltPixelTracksForSeedsL3MuonAssociated_matchedL3 = 0;
    hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction = 0;
    hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize = 0;
    hltPixelTracksForSeedsL3MuonAssociated_mva = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_status = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality = 0;
    tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits = 0;

    hltGlbTrkMuonTracksAssociated_pt = 0;
    hltGlbTrkMuonTracksAssociated_eta = 0;
    hltGlbTrkMuonTracksAssociated_phi = 0;
    hltGlbTrkMuonTracksAssociated_charge = 0;
    hltGlbTrkMuonTracksAssociated_matchedL3 = 0;
    hltGlbTrkMuonTracksAssociated_matchedL3NoId = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_charge = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_energy = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_pt = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_eta = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_phi = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_status = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers = 0;
    hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction = 0;
    hltGlbTrkMuonTracksAssociated_matchedTPsize = 0;
    hltGlbTrkMuonTracksAssociated_mva = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_charge = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_pdgId = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_energy = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_pt = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_eta = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_phi = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_parentVx = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_parentVy = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_parentVz = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_status = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_gen_charge = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_gen_pt = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_gen_eta = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_gen_phi = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2 = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality = 0;
    tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits = 0;
    hi_cBin=0;

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
    fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
    fChain->SetBranchAddress("lumiBlockNum", &lumiBlockNum, &b_lumiBlockNum);
    fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
    fChain->SetBranchAddress("nVertex", &nVertex, &b_nVertex);
    fChain->SetBranchAddress("bunchID", &bunchID, &b_bunchID);
    fChain->SetBranchAddress("instLumi", &instLumi, &b_instLumi);
    fChain->SetBranchAddress("dataPU", &dataPU, &b_dataPU);
    fChain->SetBranchAddress("dataPURMS", &dataPURMS, &b_dataPURMS);
    fChain->SetBranchAddress("bunchLumi", &bunchLumi, &b_bunchLumi);
    fChain->SetBranchAddress("offlineInstLumi", &offlineInstLumi, &b_offlineInstLumi);
    fChain->SetBranchAddress("offlineDataPU", &offlineDataPU, &b_offlineDataPU);
    fChain->SetBranchAddress("offlineDataPURMS", &offlineDataPURMS, &b_offlineDataPURMS);
    fChain->SetBranchAddress("offlineBunchLumi", &offlineBunchLumi, &b_offlineBunchLumi);
    fChain->SetBranchAddress("truePU", &truePU, &b_truePU);
    // fChain->SetBranchAddress("InstLumi", &InstLumi, &b_InstLumi);
    // fChain->SetBranchAddress("DataPU", &DataPU, &b_DataPU);
    fChain->SetBranchAddress("genEventWeight", &genEventWeight, &b_genEventWeight);
    fChain->SetBranchAddress("nGenParticle", &nGenParticle, &b_nGenParticle);
    fChain->SetBranchAddress("genParticle_ID", genParticle_ID, &b_genParticle_ID);
    fChain->SetBranchAddress("genParticle_status", genParticle_status, &b_genParticle_status);
    fChain->SetBranchAddress("genParticle_mother", genParticle_mother, &b_genParticle_mother);
    fChain->SetBranchAddress("genParticle_pt", genParticle_pt, &b_genParticle_pt);
    fChain->SetBranchAddress("genParticle_eta", genParticle_eta, &b_genParticle_eta);
    fChain->SetBranchAddress("genParticle_phi", genParticle_phi, &b_genParticle_phi);
    fChain->SetBranchAddress("genParticle_px", genParticle_px, &b_genParticle_px);
    fChain->SetBranchAddress("genParticle_py", genParticle_py, &b_genParticle_py);
    fChain->SetBranchAddress("genParticle_pz", genParticle_pz, &b_genParticle_pz);
    fChain->SetBranchAddress("genParticle_energy", genParticle_energy, &b_genParticle_energy);
    fChain->SetBranchAddress("genParticle_charge", genParticle_charge, &b_genParticle_charge);
    fChain->SetBranchAddress("genParticle_isPrompt", genParticle_isPrompt, &b_genParticle_isPrompt);
    fChain->SetBranchAddress("genParticle_isPromptFinalState", genParticle_isPromptFinalState, &b_genParticle_isPromptFinalState);
    fChain->SetBranchAddress("genParticle_isTauDecayProduct", genParticle_isTauDecayProduct, &b_genParticle_isTauDecayProduct);
    fChain->SetBranchAddress("genParticle_isPromptTauDecayProduct", genParticle_isPromptTauDecayProduct, &b_genParticle_isPromptTauDecayProduct);
    fChain->SetBranchAddress("genParticle_isDirectPromptTauDecayProductFinalState", genParticle_isDirectPromptTauDecayProductFinalState, &b_genParticle_isDirectPromptTauDecayProductFinalState);
    fChain->SetBranchAddress("genParticle_isHardProcess", genParticle_isHardProcess, &b_genParticle_isHardProcess);
    fChain->SetBranchAddress("genParticle_isLastCopy", genParticle_isLastCopy, &b_genParticle_isLastCopy);
    fChain->SetBranchAddress("genParticle_isLastCopyBeforeFSR", genParticle_isLastCopyBeforeFSR, &b_genParticle_isLastCopyBeforeFSR);
    fChain->SetBranchAddress("genParticle_isPromptDecayed", genParticle_isPromptDecayed, &b_genParticle_isPromptDecayed);
    fChain->SetBranchAddress("genParticle_isDecayedLeptonHadron", genParticle_isDecayedLeptonHadron, &b_genParticle_isDecayedLeptonHadron);
    fChain->SetBranchAddress("genParticle_fromHardProcessBeforeFSR", genParticle_fromHardProcessBeforeFSR, &b_genParticle_fromHardProcessBeforeFSR);
    fChain->SetBranchAddress("genParticle_fromHardProcessDecayed", genParticle_fromHardProcessDecayed, &b_genParticle_fromHardProcessDecayed);
    fChain->SetBranchAddress("genParticle_fromHardProcessFinalState", genParticle_fromHardProcessFinalState, &b_genParticle_fromHardProcessFinalState);
    fChain->SetBranchAddress("genParticle_isMostlyLikePythia6Status3", genParticle_isMostlyLikePythia6Status3, &b_genParticle_isMostlyLikePythia6Status3);
    fChain->SetBranchAddress("genParticle_l1pt", genParticle_l1pt, &b_genParticle_l1pt);
    fChain->SetBranchAddress("genParticle_l1eta", genParticle_l1eta, &b_genParticle_l1eta);
    fChain->SetBranchAddress("genParticle_l1phi", genParticle_l1phi, &b_genParticle_l1phi);
    fChain->SetBranchAddress("genParticle_l1charge", genParticle_l1charge, &b_genParticle_l1charge);
    fChain->SetBranchAddress("genParticle_l1q", genParticle_l1q, &b_genParticle_l1q);
    fChain->SetBranchAddress("genParticle_l1dr", genParticle_l1dr, &b_genParticle_l1dr);
    fChain->SetBranchAddress("genParticle_l1ptByQ", genParticle_l1ptByQ, &b_genParticle_l1ptByQ);
    fChain->SetBranchAddress("genParticle_l1etaByQ", genParticle_l1etaByQ, &b_genParticle_l1etaByQ);
    fChain->SetBranchAddress("genParticle_l1phiByQ", genParticle_l1phiByQ, &b_genParticle_l1phiByQ);
    fChain->SetBranchAddress("genParticle_l1chargeByQ", genParticle_l1chargeByQ, &b_genParticle_l1chargeByQ);
    fChain->SetBranchAddress("genParticle_l1qByQ", genParticle_l1qByQ, &b_genParticle_l1qByQ);
    fChain->SetBranchAddress("genParticle_l1drByQ", genParticle_l1drByQ, &b_genParticle_l1drByQ);
    fChain->SetBranchAddress("vec_firedTrigger", &vec_firedTrigger, &b_vec_firedTrigger);
    fChain->SetBranchAddress("vec_filterName", &vec_filterName, &b_vec_filterName);
    fChain->SetBranchAddress("vec_HLTObj_pt", &vec_HLTObj_pt, &b_vec_HLTObj_pt);
    fChain->SetBranchAddress("vec_HLTObj_eta", &vec_HLTObj_eta, &b_vec_HLTObj_eta);
    fChain->SetBranchAddress("vec_HLTObj_phi", &vec_HLTObj_phi, &b_vec_HLTObj_phi);
    fChain->SetBranchAddress("vec_myFiredTrigger", &vec_myFiredTrigger, &b_vec_myFiredTrigger);
    fChain->SetBranchAddress("vec_myFilterName", &vec_myFilterName, &b_vec_myFilterName);
    fChain->SetBranchAddress("vec_myHLTObj_pt", &vec_myHLTObj_pt, &b_vec_myHLTObj_pt);
    fChain->SetBranchAddress("vec_myHLTObj_eta", &vec_myHLTObj_eta, &b_vec_myHLTObj_eta);
    fChain->SetBranchAddress("vec_myHLTObj_phi", &vec_myHLTObj_phi, &b_vec_myHLTObj_phi);
    fChain->SetBranchAddress("nMuon", &nMuon, &b_nMuon);
    fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
    fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
    fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
    fChain->SetBranchAddress("muon_px", &muon_px, &b_muon_px);
    fChain->SetBranchAddress("muon_py", &muon_py, &b_muon_py);
    fChain->SetBranchAddress("muon_pz", &muon_pz, &b_muon_pz);
    fChain->SetBranchAddress("muon_dB", &muon_dB, &b_muon_dB);
    fChain->SetBranchAddress("muon_charge", &muon_charge, &b_muon_charge);
    fChain->SetBranchAddress("muon_isGLB", &muon_isGLB, &b_muon_isGLB);
    fChain->SetBranchAddress("muon_isSTA", &muon_isSTA, &b_muon_isSTA);
    fChain->SetBranchAddress("muon_isTRK", &muon_isTRK, &b_muon_isTRK);
    fChain->SetBranchAddress("muon_isPF", &muon_isPF, &b_muon_isPF);
    fChain->SetBranchAddress("muon_isTight", &muon_isTight, &b_muon_isTight);
    fChain->SetBranchAddress("muon_isMedium", &muon_isMedium, &b_muon_isMedium);
    fChain->SetBranchAddress("muon_isLoose", &muon_isLoose, &b_muon_isLoose);
    fChain->SetBranchAddress("muon_isHighPt", &muon_isHighPt, &b_muon_isHighPt);
    fChain->SetBranchAddress("muon_isHighPtNew", &muon_isHighPtNew, &b_muon_isHighPtNew);
    fChain->SetBranchAddress("muon_isSoft", &muon_isSoft, &b_muon_isSoft);
    fChain->SetBranchAddress("muon_iso03_sumPt", &muon_iso03_sumPt, &b_muon_iso03_sumPt);
    fChain->SetBranchAddress("muon_iso03_hadEt", &muon_iso03_hadEt, &b_muon_iso03_hadEt);
    fChain->SetBranchAddress("muon_iso03_emEt", &muon_iso03_emEt, &b_muon_iso03_emEt);
    fChain->SetBranchAddress("muon_PFIso03_charged", &muon_PFIso03_charged, &b_muon_PFIso03_charged);
    fChain->SetBranchAddress("muon_PFIso03_neutral", &muon_PFIso03_neutral, &b_muon_PFIso03_neutral);
    fChain->SetBranchAddress("muon_PFIso03_photon", &muon_PFIso03_photon, &b_muon_PFIso03_photon);
    fChain->SetBranchAddress("muon_PFIso03_sumPU", &muon_PFIso03_sumPU, &b_muon_PFIso03_sumPU);
    fChain->SetBranchAddress("muon_PFIso04_charged", &muon_PFIso04_charged, &b_muon_PFIso04_charged);
    fChain->SetBranchAddress("muon_PFIso04_neutral", &muon_PFIso04_neutral, &b_muon_PFIso04_neutral);
    fChain->SetBranchAddress("muon_PFIso04_photon", &muon_PFIso04_photon, &b_muon_PFIso04_photon);
    fChain->SetBranchAddress("muon_PFIso04_sumPU", &muon_PFIso04_sumPU, &b_muon_PFIso04_sumPU);
    fChain->SetBranchAddress("muon_PFCluster03_ECAL", &muon_PFCluster03_ECAL, &b_muon_PFCluster03_ECAL);
    fChain->SetBranchAddress("muon_PFCluster03_HCAL", &muon_PFCluster03_HCAL, &b_muon_PFCluster03_HCAL);
    fChain->SetBranchAddress("muon_PFCluster04_ECAL", &muon_PFCluster04_ECAL, &b_muon_PFCluster04_ECAL);
    fChain->SetBranchAddress("muon_PFCluster04_HCAL", &muon_PFCluster04_HCAL, &b_muon_PFCluster04_HCAL);
    fChain->SetBranchAddress("muon_inner_trkChi2", &muon_inner_trkChi2, &b_muon_inner_trkChi2);
    fChain->SetBranchAddress("muon_inner_validFraction", &muon_inner_validFraction, &b_muon_inner_validFraction);
    fChain->SetBranchAddress("muon_inner_trackerLayers", &muon_inner_trackerLayers, &b_muon_inner_trackerLayers);
    fChain->SetBranchAddress("muon_inner_trackerHits", &muon_inner_trackerHits, &b_muon_inner_trackerHits);
    fChain->SetBranchAddress("muon_inner_lostTrackerHits", &muon_inner_lostTrackerHits, &b_muon_inner_lostTrackerHits);
    fChain->SetBranchAddress("muon_inner_lostTrackerHitsIn", &muon_inner_lostTrackerHitsIn, &b_muon_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("muon_inner_lostTrackerHitsOut", &muon_inner_lostTrackerHitsOut, &b_muon_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("muon_inner_lostPixelHits", &muon_inner_lostPixelHits, &b_muon_inner_lostPixelHits);
    fChain->SetBranchAddress("muon_inner_lostPixelBarrelHits", &muon_inner_lostPixelBarrelHits, &b_muon_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("muon_inner_lostPixelEndcapHits", &muon_inner_lostPixelEndcapHits, &b_muon_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("muon_inner_lostStripHits", &muon_inner_lostStripHits, &b_muon_inner_lostStripHits);
    fChain->SetBranchAddress("muon_inner_lostStripTIBHits", &muon_inner_lostStripTIBHits, &b_muon_inner_lostStripTIBHits);
    fChain->SetBranchAddress("muon_inner_lostStripTIDHits", &muon_inner_lostStripTIDHits, &b_muon_inner_lostStripTIDHits);
    fChain->SetBranchAddress("muon_inner_lostStripTOBHits", &muon_inner_lostStripTOBHits, &b_muon_inner_lostStripTOBHits);
    fChain->SetBranchAddress("muon_inner_lostStripTECHits", &muon_inner_lostStripTECHits, &b_muon_inner_lostStripTECHits);
    fChain->SetBranchAddress("muon_inner_pixelLayers", &muon_inner_pixelLayers, &b_muon_inner_pixelLayers);
    fChain->SetBranchAddress("muon_inner_pixelHits", &muon_inner_pixelHits, &b_muon_inner_pixelHits);
    fChain->SetBranchAddress("muon_global_muonHits", &muon_global_muonHits, &b_muon_global_muonHits);
    fChain->SetBranchAddress("muon_global_trkChi2", &muon_global_trkChi2, &b_muon_global_trkChi2);
    fChain->SetBranchAddress("muon_global_trackerLayers", &muon_global_trackerLayers, &b_muon_global_trackerLayers);
    fChain->SetBranchAddress("muon_global_trackerHits", &muon_global_trackerHits, &b_muon_global_trackerHits);
    fChain->SetBranchAddress("muon_momentumChi2", &muon_momentumChi2, &b_muon_momentumChi2);
    fChain->SetBranchAddress("muon_positionChi2", &muon_positionChi2, &b_muon_positionChi2);
    fChain->SetBranchAddress("muon_glbKink", &muon_glbKink, &b_muon_glbKink);
    fChain->SetBranchAddress("muon_glbTrackProbability", &muon_glbTrackProbability, &b_muon_glbTrackProbability);
    fChain->SetBranchAddress("muon_globalDeltaEtaPhi", &muon_globalDeltaEtaPhi, &b_muon_globalDeltaEtaPhi);
    fChain->SetBranchAddress("muon_localDistance", &muon_localDistance, &b_muon_localDistance);
    fChain->SetBranchAddress("muon_staRelChi2", &muon_staRelChi2, &b_muon_staRelChi2);
    fChain->SetBranchAddress("muon_tightMatch", &muon_tightMatch, &b_muon_tightMatch);
    fChain->SetBranchAddress("muon_trkKink", &muon_trkKink, &b_muon_trkKink);
    fChain->SetBranchAddress("muon_trkRelChi2", &muon_trkRelChi2, &b_muon_trkRelChi2);
    fChain->SetBranchAddress("muon_segmentCompatibility", &muon_segmentCompatibility, &b_muon_segmentCompatibility);
    fChain->SetBranchAddress("muon_pt_tuneP", &muon_pt_tuneP, &b_muon_pt_tuneP);
    fChain->SetBranchAddress("muon_ptError_tuneP", &muon_ptError_tuneP, &b_muon_ptError_tuneP);
    fChain->SetBranchAddress("muon_dxyVTX_best", &muon_dxyVTX_best, &b_muon_dxyVTX_best);
    fChain->SetBranchAddress("muon_dzVTX_best", &muon_dzVTX_best, &b_muon_dzVTX_best);
    fChain->SetBranchAddress("muon_nMatchedStation", &muon_nMatchedStation, &b_muon_nMatchedStation);
    fChain->SetBranchAddress("muon_nMatchedRPCLayer", &muon_nMatchedRPCLayer, &b_muon_nMatchedRPCLayer);
    fChain->SetBranchAddress("muon_stationMask", &muon_stationMask, &b_muon_stationMask);
    fChain->SetBranchAddress("muon_dxy_bs", &muon_dxy_bs, &b_muon_dxy_bs);
    fChain->SetBranchAddress("muon_dxyError_bs", &muon_dxyError_bs, &b_muon_dxyError_bs);
    fChain->SetBranchAddress("muon_dz_bs", &muon_dz_bs, &b_muon_dz_bs);
    fChain->SetBranchAddress("muon_dzError", &muon_dzError, &b_muon_dzError);
    fChain->SetBranchAddress("muon_IPSig", &muon_IPSig, &b_muon_IPSig);
    fChain->SetBranchAddress("muon_l1pt", muon_l1pt, &b_muon_l1pt);
    fChain->SetBranchAddress("muon_l1eta", muon_l1eta, &b_muon_l1eta);
    fChain->SetBranchAddress("muon_l1phi", muon_l1phi, &b_muon_l1phi);
    fChain->SetBranchAddress("muon_l1charge", muon_l1charge, &b_muon_l1charge);
    fChain->SetBranchAddress("muon_l1q", muon_l1q, &b_muon_l1q);
    fChain->SetBranchAddress("muon_l1dr", muon_l1dr, &b_muon_l1dr);
    fChain->SetBranchAddress("muon_l1ptByQ", muon_l1ptByQ, &b_muon_l1ptByQ);
    fChain->SetBranchAddress("muon_l1etaByQ", muon_l1etaByQ, &b_muon_l1etaByQ);
    fChain->SetBranchAddress("muon_l1phiByQ", muon_l1phiByQ, &b_muon_l1phiByQ);
    fChain->SetBranchAddress("muon_l1chargeByQ", muon_l1chargeByQ, &b_muon_l1chargeByQ);
    fChain->SetBranchAddress("muon_l1qByQ", muon_l1qByQ, &b_muon_l1qByQ);
    fChain->SetBranchAddress("muon_l1drByQ", muon_l1drByQ, &b_muon_l1drByQ);
    fChain->SetBranchAddress("muon_nl1t", muon_nl1t, &b_muon_nl1t);
    fChain->SetBranchAddress("muon_l1tpt", &muon_l1tpt, &b_muon_l1tpt);
    fChain->SetBranchAddress("muon_l1teta", &muon_l1teta, &b_muon_l1teta);
    fChain->SetBranchAddress("muon_l1tpropeta", &muon_l1tpropeta, &b_muon_l1tpropeta);
    fChain->SetBranchAddress("muon_l1tphi", &muon_l1tphi, &b_muon_l1tphi);
    fChain->SetBranchAddress("muon_l1tpropphi", &muon_l1tpropphi, &b_muon_l1tpropphi);
    fChain->SetBranchAddress("muon_l1tcharge", &muon_l1tcharge, &b_muon_l1tcharge);
    fChain->SetBranchAddress("muon_l1tq", &muon_l1tq, &b_muon_l1tq);
    fChain->SetBranchAddress("muon_l1tdr", &muon_l1tdr, &b_muon_l1tdr);
    fChain->SetBranchAddress("nL3Muon", &nL3Muon, &b_nL3Muon);
    fChain->SetBranchAddress("L3Muon_pt", L3Muon_pt, &b_L3Muon_pt);
    fChain->SetBranchAddress("L3Muon_eta", L3Muon_eta, &b_L3Muon_eta);
    fChain->SetBranchAddress("L3Muon_phi", L3Muon_phi, &b_L3Muon_phi);
    fChain->SetBranchAddress("L3Muon_charge", L3Muon_charge, &b_L3Muon_charge);
    fChain->SetBranchAddress("L3Muon_trkPt", L3Muon_trkPt, &b_L3Muon_trkPt);
    fChain->SetBranchAddress("nL2Muon", &nL2Muon, &b_nL2Muon);
    fChain->SetBranchAddress("L2Muon_pt", L2Muon_pt, &b_L2Muon_pt);
    fChain->SetBranchAddress("L2Muon_eta", L2Muon_eta, &b_L2Muon_eta);
    fChain->SetBranchAddress("L2Muon_phi", L2Muon_phi, &b_L2Muon_phi);
    fChain->SetBranchAddress("L2Muon_charge", L2Muon_charge, &b_L2Muon_charge);
    fChain->SetBranchAddress("L2Muon_trkPt", L2Muon_trkPt, &b_L2Muon_trkPt);
    fChain->SetBranchAddress("nTkMuon", &nTkMuon, &b_nTkMuon);
    fChain->SetBranchAddress("TkMuon_pt", &TkMuon_pt, &b_TkMuon_pt);
    fChain->SetBranchAddress("TkMuon_eta", &TkMuon_eta, &b_TkMuon_eta);
    fChain->SetBranchAddress("TkMuon_phi", &TkMuon_phi, &b_TkMuon_phi);
    fChain->SetBranchAddress("TkMuon_charge", &TkMuon_charge, &b_TkMuon_charge);
    fChain->SetBranchAddress("TkMuon_trkPt", &TkMuon_trkPt, &b_TkMuon_trkPt);
    fChain->SetBranchAddress("nL1Muon", &nL1Muon, &b_nL1Muon);
    fChain->SetBranchAddress("L1Muon_pt", L1Muon_pt, &b_L1Muon_pt);
    fChain->SetBranchAddress("L1Muon_eta", L1Muon_eta, &b_L1Muon_eta);
    fChain->SetBranchAddress("L1Muon_phi", L1Muon_phi, &b_L1Muon_phi);
    fChain->SetBranchAddress("L1Muon_charge", L1Muon_charge, &b_L1Muon_charge);
    fChain->SetBranchAddress("L1Muon_quality", L1Muon_quality, &b_L1Muon_quality);
    fChain->SetBranchAddress("L1Muon_etaAtVtx", L1Muon_etaAtVtx, &b_L1Muon_etaAtVtx);
    fChain->SetBranchAddress("L1Muon_phiAtVtx", L1Muon_phiAtVtx, &b_L1Muon_phiAtVtx);
    fChain->SetBranchAddress("nIterL3OI", &nIterL3OI, &b_nIterL3OI);
    fChain->SetBranchAddress("iterL3OI_inner_pt", iterL3OI_inner_pt, &b_iterL3OI_inner_pt);
    fChain->SetBranchAddress("iterL3OI_inner_eta", iterL3OI_inner_eta, &b_iterL3OI_inner_eta);
    fChain->SetBranchAddress("iterL3OI_inner_phi", iterL3OI_inner_phi, &b_iterL3OI_inner_phi);
    fChain->SetBranchAddress("iterL3OI_inner_charge", iterL3OI_inner_charge, &b_iterL3OI_inner_charge);
    fChain->SetBranchAddress("iterL3OI_inner_trkChi2", iterL3OI_inner_trkChi2, &b_iterL3OI_inner_trkChi2);
    fChain->SetBranchAddress("iterL3OI_inner_validFraction", iterL3OI_inner_validFraction, &b_iterL3OI_inner_validFraction);
    fChain->SetBranchAddress("iterL3OI_inner_trackerLayers", iterL3OI_inner_trackerLayers, &b_iterL3OI_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3OI_inner_trackerHits", iterL3OI_inner_trackerHits, &b_iterL3OI_inner_trackerHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostTrackerHits", &iterL3OI_inner_lostTrackerHits, &b_iterL3OI_inner_lostTrackerHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostTrackerHitsIn", &iterL3OI_inner_lostTrackerHitsIn, &b_iterL3OI_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3OI_inner_lostTrackerHitsOut", &iterL3OI_inner_lostTrackerHitsOut, &b_iterL3OI_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3OI_inner_lostPixelHits", &iterL3OI_inner_lostPixelHits, &b_iterL3OI_inner_lostPixelHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostPixelBarrelHits", &iterL3OI_inner_lostPixelBarrelHits, &b_iterL3OI_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostPixelEndcapHits", &iterL3OI_inner_lostPixelEndcapHits, &b_iterL3OI_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostStripHits", &iterL3OI_inner_lostStripHits, &b_iterL3OI_inner_lostStripHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostStripTIBHits", &iterL3OI_inner_lostStripTIBHits, &b_iterL3OI_inner_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostStripTIDHits", &iterL3OI_inner_lostStripTIDHits, &b_iterL3OI_inner_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostStripTOBHits", &iterL3OI_inner_lostStripTOBHits, &b_iterL3OI_inner_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3OI_inner_lostStripTECHits", &iterL3OI_inner_lostStripTECHits, &b_iterL3OI_inner_lostStripTECHits);
    fChain->SetBranchAddress("iterL3OI_inner_pixelLayers", iterL3OI_inner_pixelLayers, &b_iterL3OI_inner_pixelLayers);
    fChain->SetBranchAddress("iterL3OI_inner_pixelHits", iterL3OI_inner_pixelHits, &b_iterL3OI_inner_pixelHits);
    fChain->SetBranchAddress("iterL3OI_outer_pt", iterL3OI_outer_pt, &b_iterL3OI_outer_pt);
    fChain->SetBranchAddress("iterL3OI_outer_eta", iterL3OI_outer_eta, &b_iterL3OI_outer_eta);
    fChain->SetBranchAddress("iterL3OI_outer_phi", iterL3OI_outer_phi, &b_iterL3OI_outer_phi);
    fChain->SetBranchAddress("iterL3OI_outer_charge", iterL3OI_outer_charge, &b_iterL3OI_outer_charge);
    fChain->SetBranchAddress("iterL3OI_global_pt", iterL3OI_global_pt, &b_iterL3OI_global_pt);
    fChain->SetBranchAddress("iterL3OI_global_eta", iterL3OI_global_eta, &b_iterL3OI_global_eta);
    fChain->SetBranchAddress("iterL3OI_global_phi", iterL3OI_global_phi, &b_iterL3OI_global_phi);
    fChain->SetBranchAddress("iterL3OI_global_charge", iterL3OI_global_charge, &b_iterL3OI_global_charge);
    fChain->SetBranchAddress("iterL3OI_global_muonHits", iterL3OI_global_muonHits, &b_iterL3OI_global_muonHits);
    fChain->SetBranchAddress("iterL3OI_global_trkChi2", iterL3OI_global_trkChi2, &b_iterL3OI_global_trkChi2);
    fChain->SetBranchAddress("iterL3OI_global_trackerLayers", iterL3OI_global_trackerLayers, &b_iterL3OI_global_trackerLayers);
    fChain->SetBranchAddress("iterL3OI_global_trackerHits", iterL3OI_global_trackerHits, &b_iterL3OI_global_trackerHits);
    fChain->SetBranchAddress("nIterL3IOFromL2", &nIterL3IOFromL2, &b_nIterL3IOFromL2);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_pt", iterL3IOFromL2_inner_pt, &b_iterL3IOFromL2_inner_pt);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_eta", iterL3IOFromL2_inner_eta, &b_iterL3IOFromL2_inner_eta);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_phi", iterL3IOFromL2_inner_phi, &b_iterL3IOFromL2_inner_phi);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_charge", iterL3IOFromL2_inner_charge, &b_iterL3IOFromL2_inner_charge);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_trkChi2", iterL3IOFromL2_inner_trkChi2, &b_iterL3IOFromL2_inner_trkChi2);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_validFraction", iterL3IOFromL2_inner_validFraction, &b_iterL3IOFromL2_inner_validFraction);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_trackerLayers", iterL3IOFromL2_inner_trackerLayers, &b_iterL3IOFromL2_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_trackerHits", iterL3IOFromL2_inner_trackerHits, &b_iterL3IOFromL2_inner_trackerHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostTrackerHits", &iterL3IOFromL2_inner_lostTrackerHits, &b_iterL3IOFromL2_inner_lostTrackerHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostTrackerHitsIn", &iterL3IOFromL2_inner_lostTrackerHitsIn, &b_iterL3IOFromL2_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostTrackerHitsOut", &iterL3IOFromL2_inner_lostTrackerHitsOut, &b_iterL3IOFromL2_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostPixelHits", &iterL3IOFromL2_inner_lostPixelHits, &b_iterL3IOFromL2_inner_lostPixelHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostPixelBarrelHits", &iterL3IOFromL2_inner_lostPixelBarrelHits, &b_iterL3IOFromL2_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostPixelEndcapHits", &iterL3IOFromL2_inner_lostPixelEndcapHits, &b_iterL3IOFromL2_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostStripHits", &iterL3IOFromL2_inner_lostStripHits, &b_iterL3IOFromL2_inner_lostStripHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostStripTIBHits", &iterL3IOFromL2_inner_lostStripTIBHits, &b_iterL3IOFromL2_inner_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostStripTIDHits", &iterL3IOFromL2_inner_lostStripTIDHits, &b_iterL3IOFromL2_inner_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostStripTOBHits", &iterL3IOFromL2_inner_lostStripTOBHits, &b_iterL3IOFromL2_inner_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_lostStripTECHits", &iterL3IOFromL2_inner_lostStripTECHits, &b_iterL3IOFromL2_inner_lostStripTECHits);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_pixelLayers", iterL3IOFromL2_inner_pixelLayers, &b_iterL3IOFromL2_inner_pixelLayers);
    fChain->SetBranchAddress("iterL3IOFromL2_inner_pixelHits", iterL3IOFromL2_inner_pixelHits, &b_iterL3IOFromL2_inner_pixelHits);
    fChain->SetBranchAddress("iterL3IOFromL2_outer_pt", iterL3IOFromL2_outer_pt, &b_iterL3IOFromL2_outer_pt);
    fChain->SetBranchAddress("iterL3IOFromL2_outer_eta", iterL3IOFromL2_outer_eta, &b_iterL3IOFromL2_outer_eta);
    fChain->SetBranchAddress("iterL3IOFromL2_outer_phi", iterL3IOFromL2_outer_phi, &b_iterL3IOFromL2_outer_phi);
    fChain->SetBranchAddress("iterL3IOFromL2_outer_charge", iterL3IOFromL2_outer_charge, &b_iterL3IOFromL2_outer_charge);
    fChain->SetBranchAddress("iterL3IOFromL2_global_pt", iterL3IOFromL2_global_pt, &b_iterL3IOFromL2_global_pt);
    fChain->SetBranchAddress("iterL3IOFromL2_global_eta", iterL3IOFromL2_global_eta, &b_iterL3IOFromL2_global_eta);
    fChain->SetBranchAddress("iterL3IOFromL2_global_phi", iterL3IOFromL2_global_phi, &b_iterL3IOFromL2_global_phi);
    fChain->SetBranchAddress("iterL3IOFromL2_global_charge", iterL3IOFromL2_global_charge, &b_iterL3IOFromL2_global_charge);
    fChain->SetBranchAddress("iterL3IOFromL2_global_muonHits", iterL3IOFromL2_global_muonHits, &b_iterL3IOFromL2_global_muonHits);
    fChain->SetBranchAddress("iterL3IOFromL2_global_trkChi2", iterL3IOFromL2_global_trkChi2, &b_iterL3IOFromL2_global_trkChi2);
    fChain->SetBranchAddress("iterL3IOFromL2_global_trackerLayers", iterL3IOFromL2_global_trackerLayers, &b_iterL3IOFromL2_global_trackerLayers);
    fChain->SetBranchAddress("iterL3IOFromL2_global_trackerHits", iterL3IOFromL2_global_trackerHits, &b_iterL3IOFromL2_global_trackerHits);
    fChain->SetBranchAddress("nIterL3FromL2", &nIterL3FromL2, &b_nIterL3FromL2);
    fChain->SetBranchAddress("iterL3FromL2_inner_pt", iterL3FromL2_inner_pt, &b_iterL3FromL2_inner_pt);
    fChain->SetBranchAddress("iterL3FromL2_inner_eta", iterL3FromL2_inner_eta, &b_iterL3FromL2_inner_eta);
    fChain->SetBranchAddress("iterL3FromL2_inner_phi", iterL3FromL2_inner_phi, &b_iterL3FromL2_inner_phi);
    fChain->SetBranchAddress("iterL3FromL2_inner_charge", iterL3FromL2_inner_charge, &b_iterL3FromL2_inner_charge);
    fChain->SetBranchAddress("iterL3FromL2_inner_trkChi2", iterL3FromL2_inner_trkChi2, &b_iterL3FromL2_inner_trkChi2);
    fChain->SetBranchAddress("iterL3FromL2_inner_validFraction", iterL3FromL2_inner_validFraction, &b_iterL3FromL2_inner_validFraction);
    fChain->SetBranchAddress("iterL3FromL2_inner_trackerLayers", iterL3FromL2_inner_trackerLayers, &b_iterL3FromL2_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3FromL2_inner_trackerHits", iterL3FromL2_inner_trackerHits, &b_iterL3FromL2_inner_trackerHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostTrackerHits", &iterL3FromL2_inner_lostTrackerHits, &b_iterL3FromL2_inner_lostTrackerHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostTrackerHitsIn", &iterL3FromL2_inner_lostTrackerHitsIn, &b_iterL3FromL2_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostTrackerHitsOut", &iterL3FromL2_inner_lostTrackerHitsOut, &b_iterL3FromL2_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostPixelHits", &iterL3FromL2_inner_lostPixelHits, &b_iterL3FromL2_inner_lostPixelHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostPixelBarrelHits", &iterL3FromL2_inner_lostPixelBarrelHits, &b_iterL3FromL2_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostPixelEndcapHits", &iterL3FromL2_inner_lostPixelEndcapHits, &b_iterL3FromL2_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostStripHits", &iterL3FromL2_inner_lostStripHits, &b_iterL3FromL2_inner_lostStripHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostStripTIBHits", &iterL3FromL2_inner_lostStripTIBHits, &b_iterL3FromL2_inner_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostStripTIDHits", &iterL3FromL2_inner_lostStripTIDHits, &b_iterL3FromL2_inner_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostStripTOBHits", &iterL3FromL2_inner_lostStripTOBHits, &b_iterL3FromL2_inner_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_lostStripTECHits", &iterL3FromL2_inner_lostStripTECHits, &b_iterL3FromL2_inner_lostStripTECHits);
    fChain->SetBranchAddress("iterL3FromL2_inner_pixelLayers", iterL3FromL2_inner_pixelLayers, &b_iterL3FromL2_inner_pixelLayers);
    fChain->SetBranchAddress("iterL3FromL2_inner_pixelHits", iterL3FromL2_inner_pixelHits, &b_iterL3FromL2_inner_pixelHits);
    fChain->SetBranchAddress("iterL3FromL2_outer_pt", iterL3FromL2_outer_pt, &b_iterL3FromL2_outer_pt);
    fChain->SetBranchAddress("iterL3FromL2_outer_eta", iterL3FromL2_outer_eta, &b_iterL3FromL2_outer_eta);
    fChain->SetBranchAddress("iterL3FromL2_outer_phi", iterL3FromL2_outer_phi, &b_iterL3FromL2_outer_phi);
    fChain->SetBranchAddress("iterL3FromL2_outer_charge", iterL3FromL2_outer_charge, &b_iterL3FromL2_outer_charge);
    fChain->SetBranchAddress("iterL3FromL2_global_pt", iterL3FromL2_global_pt, &b_iterL3FromL2_global_pt);
    fChain->SetBranchAddress("iterL3FromL2_global_eta", iterL3FromL2_global_eta, &b_iterL3FromL2_global_eta);
    fChain->SetBranchAddress("iterL3FromL2_global_phi", iterL3FromL2_global_phi, &b_iterL3FromL2_global_phi);
    fChain->SetBranchAddress("iterL3FromL2_global_charge", iterL3FromL2_global_charge, &b_iterL3FromL2_global_charge);
    fChain->SetBranchAddress("iterL3FromL2_global_muonHits", iterL3FromL2_global_muonHits, &b_iterL3FromL2_global_muonHits);
    fChain->SetBranchAddress("iterL3FromL2_global_trkChi2", iterL3FromL2_global_trkChi2, &b_iterL3FromL2_global_trkChi2);
    fChain->SetBranchAddress("iterL3FromL2_global_trackerLayers", iterL3FromL2_global_trackerLayers, &b_iterL3FromL2_global_trackerLayers);
    fChain->SetBranchAddress("iterL3FromL2_global_trackerHits", iterL3FromL2_global_trackerHits, &b_iterL3FromL2_global_trackerHits);
    fChain->SetBranchAddress("nIterL3IOFromL1", &nIterL3IOFromL1, &b_nIterL3IOFromL1);
    fChain->SetBranchAddress("iterL3IOFromL1_pt", iterL3IOFromL1_pt, &b_iterL3IOFromL1_pt);
    fChain->SetBranchAddress("iterL3IOFromL1_eta", iterL3IOFromL1_eta, &b_iterL3IOFromL1_eta);
    fChain->SetBranchAddress("iterL3IOFromL1_phi", iterL3IOFromL1_phi, &b_iterL3IOFromL1_phi);
    fChain->SetBranchAddress("iterL3IOFromL1_charge", iterL3IOFromL1_charge, &b_iterL3IOFromL1_charge);
    fChain->SetBranchAddress("iterL3IOFromL1_muonHits", iterL3IOFromL1_muonHits, &b_iterL3IOFromL1_muonHits);
    fChain->SetBranchAddress("iterL3IOFromL1_trkChi2", iterL3IOFromL1_trkChi2, &b_iterL3IOFromL1_trkChi2);
    fChain->SetBranchAddress("iterL3IOFromL1_validFraction", iterL3IOFromL1_validFraction, &b_iterL3IOFromL1_validFraction);
    fChain->SetBranchAddress("iterL3IOFromL1_trackerLayers", iterL3IOFromL1_trackerLayers, &b_iterL3IOFromL1_trackerLayers);
    fChain->SetBranchAddress("iterL3IOFromL1_trackerHits", iterL3IOFromL1_trackerHits, &b_iterL3IOFromL1_trackerHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostTrackerHits", &iterL3IOFromL1_lostTrackerHits, &b_iterL3IOFromL1_lostTrackerHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostTrackerHitsIn", &iterL3IOFromL1_lostTrackerHitsIn, &b_iterL3IOFromL1_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3IOFromL1_lostTrackerHitsOut", &iterL3IOFromL1_lostTrackerHitsOut, &b_iterL3IOFromL1_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3IOFromL1_lostPixelHits", &iterL3IOFromL1_lostPixelHits, &b_iterL3IOFromL1_lostPixelHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostPixelBarrelHits", &iterL3IOFromL1_lostPixelBarrelHits, &b_iterL3IOFromL1_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostPixelEndcapHits", &iterL3IOFromL1_lostPixelEndcapHits, &b_iterL3IOFromL1_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostStripHits", &iterL3IOFromL1_lostStripHits, &b_iterL3IOFromL1_lostStripHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostStripTIBHits", &iterL3IOFromL1_lostStripTIBHits, &b_iterL3IOFromL1_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostStripTIDHits", &iterL3IOFromL1_lostStripTIDHits, &b_iterL3IOFromL1_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostStripTOBHits", &iterL3IOFromL1_lostStripTOBHits, &b_iterL3IOFromL1_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3IOFromL1_lostStripTECHits", &iterL3IOFromL1_lostStripTECHits, &b_iterL3IOFromL1_lostStripTECHits);
    fChain->SetBranchAddress("iterL3IOFromL1_pixelLayers", iterL3IOFromL1_pixelLayers, &b_iterL3IOFromL1_pixelLayers);
    fChain->SetBranchAddress("iterL3IOFromL1_pixelHits", iterL3IOFromL1_pixelHits, &b_iterL3IOFromL1_pixelHits);
    fChain->SetBranchAddress("nIterL3MuonNoID", &nIterL3MuonNoID, &b_nIterL3MuonNoID);
    fChain->SetBranchAddress("iterL3MuonNoID_pt", iterL3MuonNoID_pt, &b_iterL3MuonNoID_pt);
    fChain->SetBranchAddress("iterL3MuonNoID_innerPt", iterL3MuonNoID_innerPt, &b_iterL3MuonNoID_innerPt);
    fChain->SetBranchAddress("iterL3MuonNoID_eta", iterL3MuonNoID_eta, &b_iterL3MuonNoID_eta);
    fChain->SetBranchAddress("iterL3MuonNoID_phi", iterL3MuonNoID_phi, &b_iterL3MuonNoID_phi);
    fChain->SetBranchAddress("iterL3MuonNoID_charge", iterL3MuonNoID_charge, &b_iterL3MuonNoID_charge);
    fChain->SetBranchAddress("iterL3MuonNoID_isGLB", iterL3MuonNoID_isGLB, &b_iterL3MuonNoID_isGLB);
    fChain->SetBranchAddress("iterL3MuonNoID_isSTA", iterL3MuonNoID_isSTA, &b_iterL3MuonNoID_isSTA);
    fChain->SetBranchAddress("iterL3MuonNoID_isTRK", iterL3MuonNoID_isTRK, &b_iterL3MuonNoID_isTRK);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_trkChi2", iterL3MuonNoID_inner_trkChi2, &b_iterL3MuonNoID_inner_trkChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_validFraction", iterL3MuonNoID_inner_validFraction, &b_iterL3MuonNoID_inner_validFraction);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_trackerLayers", iterL3MuonNoID_inner_trackerLayers, &b_iterL3MuonNoID_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_trackerHits", iterL3MuonNoID_inner_trackerHits, &b_iterL3MuonNoID_inner_trackerHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostTrackerHits", &iterL3MuonNoID_inner_lostTrackerHits, &b_iterL3MuonNoID_inner_lostTrackerHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostTrackerHitsIn", &iterL3MuonNoID_inner_lostTrackerHitsIn, &b_iterL3MuonNoID_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostTrackerHitsOut", &iterL3MuonNoID_inner_lostTrackerHitsOut, &b_iterL3MuonNoID_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostPixelHits", &iterL3MuonNoID_inner_lostPixelHits, &b_iterL3MuonNoID_inner_lostPixelHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostPixelBarrelHits", &iterL3MuonNoID_inner_lostPixelBarrelHits, &b_iterL3MuonNoID_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostPixelEndcapHits", &iterL3MuonNoID_inner_lostPixelEndcapHits, &b_iterL3MuonNoID_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostStripHits", &iterL3MuonNoID_inner_lostStripHits, &b_iterL3MuonNoID_inner_lostStripHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostStripTIBHits", &iterL3MuonNoID_inner_lostStripTIBHits, &b_iterL3MuonNoID_inner_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostStripTIDHits", &iterL3MuonNoID_inner_lostStripTIDHits, &b_iterL3MuonNoID_inner_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostStripTOBHits", &iterL3MuonNoID_inner_lostStripTOBHits, &b_iterL3MuonNoID_inner_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_lostStripTECHits", &iterL3MuonNoID_inner_lostStripTECHits, &b_iterL3MuonNoID_inner_lostStripTECHits);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_pixelLayers", iterL3MuonNoID_inner_pixelLayers, &b_iterL3MuonNoID_inner_pixelLayers);
    fChain->SetBranchAddress("iterL3MuonNoID_inner_pixelHits", iterL3MuonNoID_inner_pixelHits, &b_iterL3MuonNoID_inner_pixelHits);
    fChain->SetBranchAddress("iterL3MuonNoID_global_muonHits", iterL3MuonNoID_global_muonHits, &b_iterL3MuonNoID_global_muonHits);
    fChain->SetBranchAddress("iterL3MuonNoID_global_trkChi2", iterL3MuonNoID_global_trkChi2, &b_iterL3MuonNoID_global_trkChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_global_trackerLayers", iterL3MuonNoID_global_trackerLayers, &b_iterL3MuonNoID_global_trackerLayers);
    fChain->SetBranchAddress("iterL3MuonNoID_global_trackerHits", iterL3MuonNoID_global_trackerHits, &b_iterL3MuonNoID_global_trackerHits);
    fChain->SetBranchAddress("iterL3MuonNoID_momentumChi2", iterL3MuonNoID_momentumChi2, &b_iterL3MuonNoID_momentumChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_positionChi2", iterL3MuonNoID_positionChi2, &b_iterL3MuonNoID_positionChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_glbKink", iterL3MuonNoID_glbKink, &b_iterL3MuonNoID_glbKink);
    fChain->SetBranchAddress("iterL3MuonNoID_glbTrackProbability", iterL3MuonNoID_glbTrackProbability, &b_iterL3MuonNoID_glbTrackProbability);
    fChain->SetBranchAddress("iterL3MuonNoID_globalDeltaEtaPhi", iterL3MuonNoID_globalDeltaEtaPhi, &b_iterL3MuonNoID_globalDeltaEtaPhi);
    fChain->SetBranchAddress("iterL3MuonNoID_localDistance", iterL3MuonNoID_localDistance, &b_iterL3MuonNoID_localDistance);
    fChain->SetBranchAddress("iterL3MuonNoID_staRelChi2", iterL3MuonNoID_staRelChi2, &b_iterL3MuonNoID_staRelChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_tightMatch", iterL3MuonNoID_tightMatch, &b_iterL3MuonNoID_tightMatch);
    fChain->SetBranchAddress("iterL3MuonNoID_trkKink", iterL3MuonNoID_trkKink, &b_iterL3MuonNoID_trkKink);
    fChain->SetBranchAddress("iterL3MuonNoID_trkRelChi2", iterL3MuonNoID_trkRelChi2, &b_iterL3MuonNoID_trkRelChi2);
    fChain->SetBranchAddress("iterL3MuonNoID_segmentCompatibility", iterL3MuonNoID_segmentCompatibility, &b_iterL3MuonNoID_segmentCompatibility);
    fChain->SetBranchAddress("nIterL3Muon", &nIterL3Muon, &b_nIterL3Muon);
    fChain->SetBranchAddress("iterL3Muon_pt", iterL3Muon_pt, &b_iterL3Muon_pt);
    fChain->SetBranchAddress("iterL3Muon_innerPt", iterL3Muon_innerPt, &b_iterL3Muon_innerPt);
    fChain->SetBranchAddress("iterL3Muon_eta", iterL3Muon_eta, &b_iterL3Muon_eta);
    fChain->SetBranchAddress("iterL3Muon_phi", iterL3Muon_phi, &b_iterL3Muon_phi);
    fChain->SetBranchAddress("iterL3Muon_charge", iterL3Muon_charge, &b_iterL3Muon_charge);
    fChain->SetBranchAddress("iterL3Muon_isGLB", iterL3Muon_isGLB, &b_iterL3Muon_isGLB);
    fChain->SetBranchAddress("iterL3Muon_isSTA", iterL3Muon_isSTA, &b_iterL3Muon_isSTA);
    fChain->SetBranchAddress("iterL3Muon_isTRK", iterL3Muon_isTRK, &b_iterL3Muon_isTRK);
    fChain->SetBranchAddress("iterL3Muon_inner_trkChi2", iterL3Muon_inner_trkChi2, &b_iterL3Muon_inner_trkChi2);
    fChain->SetBranchAddress("iterL3Muon_inner_validFraction", iterL3Muon_inner_validFraction, &b_iterL3Muon_inner_validFraction);
    fChain->SetBranchAddress("iterL3Muon_inner_trackerLayers", iterL3Muon_inner_trackerLayers, &b_iterL3Muon_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3Muon_inner_trackerHits", iterL3Muon_inner_trackerHits, &b_iterL3Muon_inner_trackerHits);
    fChain->SetBranchAddress("iterL3Muon_inner_trackerLayers", iterL3Muon_inner_trackerLayers, &b_iterL3Muon_inner_trackerLayers);
    fChain->SetBranchAddress("iterL3Muon_inner_lostTrackerHits", &iterL3Muon_inner_lostTrackerHits, &b_iterL3Muon_inner_lostTrackerHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostTrackerHitsIn", &iterL3Muon_inner_lostTrackerHitsIn, &b_iterL3Muon_inner_lostTrackerHitsIn);
    fChain->SetBranchAddress("iterL3Muon_inner_lostTrackerHitsOut", &iterL3Muon_inner_lostTrackerHitsOut, &b_iterL3Muon_inner_lostTrackerHitsOut);
    fChain->SetBranchAddress("iterL3Muon_inner_lostPixelHits", &iterL3Muon_inner_lostPixelHits, &b_iterL3Muon_inner_lostPixelHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostPixelBarrelHits", &iterL3Muon_inner_lostPixelBarrelHits, &b_iterL3Muon_inner_lostPixelBarrelHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostPixelEndcapHits", &iterL3Muon_inner_lostPixelEndcapHits, &b_iterL3Muon_inner_lostPixelEndcapHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostStripHits", &iterL3Muon_inner_lostStripHits, &b_iterL3Muon_inner_lostStripHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostStripTIBHits", &iterL3Muon_inner_lostStripTIBHits, &b_iterL3Muon_inner_lostStripTIBHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostStripTIDHits", &iterL3Muon_inner_lostStripTIDHits, &b_iterL3Muon_inner_lostStripTIDHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostStripTOBHits", &iterL3Muon_inner_lostStripTOBHits, &b_iterL3Muon_inner_lostStripTOBHits);
    fChain->SetBranchAddress("iterL3Muon_inner_lostStripTECHits", &iterL3Muon_inner_lostStripTECHits, &b_iterL3Muon_inner_lostStripTECHits);
    fChain->SetBranchAddress("iterL3Muon_inner_pixelLayers", iterL3Muon_inner_pixelLayers, &b_iterL3Muon_inner_pixelLayers);
    fChain->SetBranchAddress("iterL3Muon_inner_pixelHits", iterL3Muon_inner_pixelHits, &b_iterL3Muon_inner_pixelHits);
    fChain->SetBranchAddress("iterL3Muon_global_muonHits", iterL3Muon_global_muonHits, &b_iterL3Muon_global_muonHits);
    fChain->SetBranchAddress("iterL3Muon_global_trkChi2", iterL3Muon_global_trkChi2, &b_iterL3Muon_global_trkChi2);
    fChain->SetBranchAddress("iterL3Muon_global_trackerLayers", iterL3Muon_global_trackerLayers, &b_iterL3Muon_global_trackerLayers);
    fChain->SetBranchAddress("iterL3Muon_global_trackerHits", iterL3Muon_global_trackerHits, &b_iterL3Muon_global_trackerHits);
    fChain->SetBranchAddress("iterL3Muon_momentumChi2", iterL3Muon_momentumChi2, &b_iterL3Muon_momentumChi2);
    fChain->SetBranchAddress("iterL3Muon_positionChi2", iterL3Muon_positionChi2, &b_iterL3Muon_positionChi2);
    fChain->SetBranchAddress("iterL3Muon_glbKink", iterL3Muon_glbKink, &b_iterL3Muon_glbKink);
    fChain->SetBranchAddress("iterL3Muon_glbTrackProbability", iterL3Muon_glbTrackProbability, &b_iterL3Muon_glbTrackProbability);
    fChain->SetBranchAddress("iterL3Muon_globalDeltaEtaPhi", iterL3Muon_globalDeltaEtaPhi, &b_iterL3Muon_globalDeltaEtaPhi);
    fChain->SetBranchAddress("iterL3Muon_localDistance", iterL3Muon_localDistance, &b_iterL3Muon_localDistance);
    fChain->SetBranchAddress("iterL3Muon_staRelChi2", iterL3Muon_staRelChi2, &b_iterL3Muon_staRelChi2);
    fChain->SetBranchAddress("iterL3Muon_tightMatch", iterL3Muon_tightMatch, &b_iterL3Muon_tightMatch);
    fChain->SetBranchAddress("iterL3Muon_trkKink", iterL3Muon_trkKink, &b_iterL3Muon_trkKink);
    fChain->SetBranchAddress("iterL3Muon_trkRelChi2", iterL3Muon_trkRelChi2, &b_iterL3Muon_trkRelChi2);
    fChain->SetBranchAddress("iterL3Muon_segmentCompatibility", iterL3Muon_segmentCompatibility, &b_iterL3Muon_segmentCompatibility);
    fChain->SetBranchAddress("nTP", &nTP, &b_nTP);
    fChain->SetBranchAddress("TP_charge", &TP_charge, &b_TP_charge);
    fChain->SetBranchAddress("TP_pdgId", &TP_pdgId, &b_TP_pdgId);
    fChain->SetBranchAddress("TP_energy", &TP_energy, &b_TP_energy);
    fChain->SetBranchAddress("TP_pt", &TP_pt, &b_TP_pt);
    fChain->SetBranchAddress("TP_eta", &TP_eta, &b_TP_eta);
    fChain->SetBranchAddress("TP_phi", &TP_phi, &b_TP_phi);
    fChain->SetBranchAddress("TP_parentVx", &TP_parentVx, &b_TP_parentVx);
    fChain->SetBranchAddress("TP_parentVy", &TP_parentVy, &b_TP_parentVy);
    fChain->SetBranchAddress("TP_parentVz", &TP_parentVz, &b_TP_parentVz);
    fChain->SetBranchAddress("TP_status", &TP_status, &b_TP_status);
    fChain->SetBranchAddress("TP_numberOfHits", &TP_numberOfHits, &b_TP_numberOfHits);
    fChain->SetBranchAddress("TP_numberOfTrackerHits", &TP_numberOfTrackerHits, &b_TP_numberOfTrackerHits);
    fChain->SetBranchAddress("TP_numberOfTrackerLayers", &TP_numberOfTrackerLayers, &b_TP_numberOfTrackerLayers);
    fChain->SetBranchAddress("TP_gen_charge", &TP_gen_charge, &b_TP_gen_charge);
    fChain->SetBranchAddress("TP_gen_pdgId", &TP_gen_pdgId, &b_TP_gen_pdgId);
    fChain->SetBranchAddress("TP_gen_pt", &TP_gen_pt, &b_TP_gen_pt);
    fChain->SetBranchAddress("TP_gen_eta", &TP_gen_eta, &b_TP_gen_eta);
    fChain->SetBranchAddress("TP_gen_phi", &TP_gen_phi, &b_TP_gen_phi);
    fChain->SetBranchAddress("TP_bestMatchTrk_pt", &TP_bestMatchTrk_pt, &b_TP_bestMatchTrk_pt);
    fChain->SetBranchAddress("TP_bestMatchTrk_eta", &TP_bestMatchTrk_eta, &b_TP_bestMatchTrk_eta);
    fChain->SetBranchAddress("TP_bestMatchTrk_phi", &TP_bestMatchTrk_phi, &b_TP_bestMatchTrk_phi);
    fChain->SetBranchAddress("TP_bestMatchTrk_charge", &TP_bestMatchTrk_charge, &b_TP_bestMatchTrk_charge);
    fChain->SetBranchAddress("TP_bestMatchTrk_quality", &TP_bestMatchTrk_quality, &b_TP_bestMatchTrk_quality);
    fChain->SetBranchAddress("TP_bestMatchTrk_NValidHits", &TP_bestMatchTrk_NValidHits, &b_TP_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("nhltIterL3MuonTrimmedPixelVertices", &nhltIterL3MuonTrimmedPixelVertices, &b_nhltIterL3MuonTrimmedPixelVertices);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_isValid", &hltIterL3MuonTrimmedPixelVertices_isValid, &b_hltIterL3MuonTrimmedPixelVertices_isValid);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_chi2", &hltIterL3MuonTrimmedPixelVertices_chi2, &b_hltIterL3MuonTrimmedPixelVertices_chi2);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_ndof", &hltIterL3MuonTrimmedPixelVertices_ndof, &b_hltIterL3MuonTrimmedPixelVertices_ndof);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_nTracks", &hltIterL3MuonTrimmedPixelVertices_nTracks, &b_hltIterL3MuonTrimmedPixelVertices_nTracks);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_x", &hltIterL3MuonTrimmedPixelVertices_x, &b_hltIterL3MuonTrimmedPixelVertices_x);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_xerr", &hltIterL3MuonTrimmedPixelVertices_xerr, &b_hltIterL3MuonTrimmedPixelVertices_xerr);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_y", &hltIterL3MuonTrimmedPixelVertices_y, &b_hltIterL3MuonTrimmedPixelVertices_y);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_yerr", &hltIterL3MuonTrimmedPixelVertices_yerr, &b_hltIterL3MuonTrimmedPixelVertices_yerr);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_z", &hltIterL3MuonTrimmedPixelVertices_z, &b_hltIterL3MuonTrimmedPixelVertices_z);
    fChain->SetBranchAddress("hltIterL3MuonTrimmedPixelVertices_zerr", &hltIterL3MuonTrimmedPixelVertices_zerr, &b_hltIterL3MuonTrimmedPixelVertices_zerr);
    fChain->SetBranchAddress("nhltIterL3FromL1MuonTrimmedPixelVertices", &nhltIterL3FromL1MuonTrimmedPixelVertices, &b_nhltIterL3FromL1MuonTrimmedPixelVertices);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_isValid", &hltIterL3FromL1MuonTrimmedPixelVertices_isValid, &b_hltIterL3FromL1MuonTrimmedPixelVertices_isValid);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_chi2", &hltIterL3FromL1MuonTrimmedPixelVertices_chi2, &b_hltIterL3FromL1MuonTrimmedPixelVertices_chi2);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_ndof", &hltIterL3FromL1MuonTrimmedPixelVertices_ndof, &b_hltIterL3FromL1MuonTrimmedPixelVertices_ndof);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_nTracks", &hltIterL3FromL1MuonTrimmedPixelVertices_nTracks, &b_hltIterL3FromL1MuonTrimmedPixelVertices_nTracks);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_x", &hltIterL3FromL1MuonTrimmedPixelVertices_x, &b_hltIterL3FromL1MuonTrimmedPixelVertices_x);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_xerr", &hltIterL3FromL1MuonTrimmedPixelVertices_xerr, &b_hltIterL3FromL1MuonTrimmedPixelVertices_xerr);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_y", &hltIterL3FromL1MuonTrimmedPixelVertices_y, &b_hltIterL3FromL1MuonTrimmedPixelVertices_y);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_yerr", &hltIterL3FromL1MuonTrimmedPixelVertices_yerr, &b_hltIterL3FromL1MuonTrimmedPixelVertices_yerr);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_z", &hltIterL3FromL1MuonTrimmedPixelVertices_z, &b_hltIterL3FromL1MuonTrimmedPixelVertices_z);
    fChain->SetBranchAddress("hltIterL3FromL1MuonTrimmedPixelVertices_zerr", &hltIterL3FromL1MuonTrimmedPixelVertices_zerr, &b_hltIterL3FromL1MuonTrimmedPixelVertices_zerr);
    fChain->SetBranchAddress("nhltIterL3OIMuonTrackAssociated", &nhltIterL3OIMuonTrackAssociated, &b_nhltIterL3OIMuonTrackAssociated);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_pt", &hltIterL3OIMuonTrackAssociated_pt, &b_hltIterL3OIMuonTrackAssociated_pt);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_eta", &hltIterL3OIMuonTrackAssociated_eta, &b_hltIterL3OIMuonTrackAssociated_eta);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_phi", &hltIterL3OIMuonTrackAssociated_phi, &b_hltIterL3OIMuonTrackAssociated_phi);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_charge", &hltIterL3OIMuonTrackAssociated_charge, &b_hltIterL3OIMuonTrackAssociated_charge);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_matchedL3", &hltIterL3OIMuonTrackAssociated_matchedL3, &b_hltIterL3OIMuonTrackAssociated_matchedL3);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_matchedL3NoId", &hltIterL3OIMuonTrackAssociated_matchedL3NoId, &b_hltIterL3OIMuonTrackAssociated_matchedL3NoId);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_charge", &hltIterL3OIMuonTrackAssociated_bestMatchTP_charge, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId", &hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_energy", &hltIterL3OIMuonTrackAssociated_bestMatchTP_energy, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_pt", &hltIterL3OIMuonTrackAssociated_bestMatchTP_pt, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_eta", &hltIterL3OIMuonTrackAssociated_bestMatchTP_eta, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_phi", &hltIterL3OIMuonTrackAssociated_bestMatchTP_phi, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx", &hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy", &hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz", &hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_status", &hltIterL3OIMuonTrackAssociated_bestMatchTP_status, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits", &hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction", &hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction, &b_hltIterL3OIMuonTrackAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_matchedTPsize", &hltIterL3OIMuonTrackAssociated_matchedTPsize, &b_hltIterL3OIMuonTrackAssociated_matchedTPsize);
    fChain->SetBranchAddress("hltIterL3OIMuonTrackAssociated_mva", &hltIterL3OIMuonTrackAssociated_mva, &b_hltIterL3OIMuonTrackAssociated_mva);
    fChain->SetBranchAddress("ntpTo_hltIterL3OIMuonTrackAssociated", &ntpTo_hltIterL3OIMuonTrackAssociated, &b_ntpTo_hltIterL3OIMuonTrackAssociated);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_charge", &tpTo_hltIterL3OIMuonTrackAssociated_charge, &b_tpTo_hltIterL3OIMuonTrackAssociated_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_pdgId", &tpTo_hltIterL3OIMuonTrackAssociated_pdgId, &b_tpTo_hltIterL3OIMuonTrackAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_energy", &tpTo_hltIterL3OIMuonTrackAssociated_energy, &b_tpTo_hltIterL3OIMuonTrackAssociated_energy);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_pt", &tpTo_hltIterL3OIMuonTrackAssociated_pt, &b_tpTo_hltIterL3OIMuonTrackAssociated_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_eta", &tpTo_hltIterL3OIMuonTrackAssociated_eta, &b_tpTo_hltIterL3OIMuonTrackAssociated_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_phi", &tpTo_hltIterL3OIMuonTrackAssociated_phi, &b_tpTo_hltIterL3OIMuonTrackAssociated_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_parentVx", &tpTo_hltIterL3OIMuonTrackAssociated_parentVx, &b_tpTo_hltIterL3OIMuonTrackAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_parentVy", &tpTo_hltIterL3OIMuonTrackAssociated_parentVy, &b_tpTo_hltIterL3OIMuonTrackAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_parentVz", &tpTo_hltIterL3OIMuonTrackAssociated_parentVz, &b_tpTo_hltIterL3OIMuonTrackAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_status", &tpTo_hltIterL3OIMuonTrackAssociated_status, &b_tpTo_hltIterL3OIMuonTrackAssociated_status);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits", &tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits, &b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits", &tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits, &b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers", &tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_hltIterL3OIMuonTrackAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_gen_charge", &tpTo_hltIterL3OIMuonTrackAssociated_gen_charge, &b_tpTo_hltIterL3OIMuonTrackAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId", &tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId, &b_tpTo_hltIterL3OIMuonTrackAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_gen_pt", &tpTo_hltIterL3OIMuonTrackAssociated_gen_pt, &b_tpTo_hltIterL3OIMuonTrackAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_gen_eta", &tpTo_hltIterL3OIMuonTrackAssociated_gen_eta, &b_tpTo_hltIterL3OIMuonTrackAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_gen_phi", &tpTo_hltIterL3OIMuonTrackAssociated_gen_phi, &b_tpTo_hltIterL3OIMuonTrackAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_normalizedChi2);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIterL3OIMuonTrackAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("nhltIter0IterL3MuonTrackAssociated", &nhltIter0IterL3MuonTrackAssociated, &b_nhltIter0IterL3MuonTrackAssociated);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_pt", &hltIter0IterL3MuonTrackAssociated_pt, &b_hltIter0IterL3MuonTrackAssociated_pt);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_eta", &hltIter0IterL3MuonTrackAssociated_eta, &b_hltIter0IterL3MuonTrackAssociated_eta);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_phi", &hltIter0IterL3MuonTrackAssociated_phi, &b_hltIter0IterL3MuonTrackAssociated_phi);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_charge", &hltIter0IterL3MuonTrackAssociated_charge, &b_hltIter0IterL3MuonTrackAssociated_charge);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_matchedL3", &hltIter0IterL3MuonTrackAssociated_matchedL3, &b_hltIter0IterL3MuonTrackAssociated_matchedL3);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_matchedL3NoId", &hltIter0IterL3MuonTrackAssociated_matchedL3NoId, &b_hltIter0IterL3MuonTrackAssociated_matchedL3NoId);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_status", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_status, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction", &hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction, &b_hltIter0IterL3MuonTrackAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_matchedTPsize", &hltIter0IterL3MuonTrackAssociated_matchedTPsize, &b_hltIter0IterL3MuonTrackAssociated_matchedTPsize);
    fChain->SetBranchAddress("hltIter0IterL3MuonTrackAssociated_mva", &hltIter0IterL3MuonTrackAssociated_mva, &b_hltIter0IterL3MuonTrackAssociated_mva);
    fChain->SetBranchAddress("ntpTo_hltIter0IterL3MuonTrackAssociated", &ntpTo_hltIter0IterL3MuonTrackAssociated, &b_ntpTo_hltIter0IterL3MuonTrackAssociated);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_charge", &tpTo_hltIter0IterL3MuonTrackAssociated_charge, &b_tpTo_hltIter0IterL3MuonTrackAssociated_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_pdgId", &tpTo_hltIter0IterL3MuonTrackAssociated_pdgId, &b_tpTo_hltIter0IterL3MuonTrackAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_energy", &tpTo_hltIter0IterL3MuonTrackAssociated_energy, &b_tpTo_hltIter0IterL3MuonTrackAssociated_energy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_pt", &tpTo_hltIter0IterL3MuonTrackAssociated_pt, &b_tpTo_hltIter0IterL3MuonTrackAssociated_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_eta", &tpTo_hltIter0IterL3MuonTrackAssociated_eta, &b_tpTo_hltIter0IterL3MuonTrackAssociated_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_phi", &tpTo_hltIter0IterL3MuonTrackAssociated_phi, &b_tpTo_hltIter0IterL3MuonTrackAssociated_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_parentVx", &tpTo_hltIter0IterL3MuonTrackAssociated_parentVx, &b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_parentVy", &tpTo_hltIter0IterL3MuonTrackAssociated_parentVy, &b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_parentVz", &tpTo_hltIter0IterL3MuonTrackAssociated_parentVz, &b_tpTo_hltIter0IterL3MuonTrackAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_status", &tpTo_hltIter0IterL3MuonTrackAssociated_status, &b_tpTo_hltIter0IterL3MuonTrackAssociated_status);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits", &tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits, &b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits", &tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits, &b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers", &tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_hltIter0IterL3MuonTrackAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge", &tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge, &b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId", &tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId, &b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt", &tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt, &b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta", &tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta, &b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi", &tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi, &b_tpTo_hltIter0IterL3MuonTrackAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2);

    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIter0IterL3MuonTrackAssociated_bestMatchTrk_NValidHits);
    // fChain->SetBranchAddress("nhltIter2IterL3MuonTrackAssociated", &nhltIter2IterL3MuonTrackAssociated, &b_nhltIter2IterL3MuonTrackAssociated);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_pt", &hltIter2IterL3MuonTrackAssociated_pt, &b_hltIter2IterL3MuonTrackAssociated_pt);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_eta", &hltIter2IterL3MuonTrackAssociated_eta, &b_hltIter2IterL3MuonTrackAssociated_eta);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_phi", &hltIter2IterL3MuonTrackAssociated_phi, &b_hltIter2IterL3MuonTrackAssociated_phi);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_charge", &hltIter2IterL3MuonTrackAssociated_charge, &b_hltIter2IterL3MuonTrackAssociated_charge);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_matchedL3", &hltIter2IterL3MuonTrackAssociated_matchedL3, &b_hltIter2IterL3MuonTrackAssociated_matchedL3);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_matchedL3NoId", &hltIter2IterL3MuonTrackAssociated_matchedL3NoId, &b_hltIter2IterL3MuonTrackAssociated_matchedL3NoId);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_charge);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_pdgId);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_energy);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_pt);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_eta);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_phi);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVx);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVy);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_parentVz);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_status", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_status, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_status);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfHits);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction", &hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction, &b_hltIter2IterL3MuonTrackAssociated_bestMatchTP_sharedFraction);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_matchedTPsize", &hltIter2IterL3MuonTrackAssociated_matchedTPsize, &b_hltIter2IterL3MuonTrackAssociated_matchedTPsize);
    // fChain->SetBranchAddress("hltIter2IterL3MuonTrackAssociated_mva", &hltIter2IterL3MuonTrackAssociated_mva, &b_hltIter2IterL3MuonTrackAssociated_mva);
    // fChain->SetBranchAddress("ntpTo_hltIter2IterL3MuonTrackAssociated", &ntpTo_hltIter2IterL3MuonTrackAssociated, &b_ntpTo_hltIter2IterL3MuonTrackAssociated);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_charge", &tpTo_hltIter2IterL3MuonTrackAssociated_charge, &b_tpTo_hltIter2IterL3MuonTrackAssociated_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_pdgId", &tpTo_hltIter2IterL3MuonTrackAssociated_pdgId, &b_tpTo_hltIter2IterL3MuonTrackAssociated_pdgId);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_energy", &tpTo_hltIter2IterL3MuonTrackAssociated_energy, &b_tpTo_hltIter2IterL3MuonTrackAssociated_energy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_pt", &tpTo_hltIter2IterL3MuonTrackAssociated_pt, &b_tpTo_hltIter2IterL3MuonTrackAssociated_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_eta", &tpTo_hltIter2IterL3MuonTrackAssociated_eta, &b_tpTo_hltIter2IterL3MuonTrackAssociated_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_phi", &tpTo_hltIter2IterL3MuonTrackAssociated_phi, &b_tpTo_hltIter2IterL3MuonTrackAssociated_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_parentVx", &tpTo_hltIter2IterL3MuonTrackAssociated_parentVx, &b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVx);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_parentVy", &tpTo_hltIter2IterL3MuonTrackAssociated_parentVy, &b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_parentVz", &tpTo_hltIter2IterL3MuonTrackAssociated_parentVz, &b_tpTo_hltIter2IterL3MuonTrackAssociated_parentVz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_status", &tpTo_hltIter2IterL3MuonTrackAssociated_status, &b_tpTo_hltIter2IterL3MuonTrackAssociated_status);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits", &tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits, &b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfHits);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits", &tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits, &b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerHits);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers", &tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_hltIter2IterL3MuonTrackAssociated_numberOfTrackerLayers);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge", &tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge, &b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId", &tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId, &b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_pdgId);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt", &tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt, &b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta", &tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta, &b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi", &tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi, &b_tpTo_hltIter2IterL3MuonTrackAssociated_gen_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_px);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_py);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_pz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vx);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_vz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxy_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dz_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_dzError);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2);

    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_quality);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIter2IterL3MuonTrackAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("nhltIter0IterL3FromL1MuonTrackAssociated", &nhltIter0IterL3FromL1MuonTrackAssociated, &b_nhltIter0IterL3FromL1MuonTrackAssociated);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_pt", &hltIter0IterL3FromL1MuonTrackAssociated_pt, &b_hltIter0IterL3FromL1MuonTrackAssociated_pt);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_eta", &hltIter0IterL3FromL1MuonTrackAssociated_eta, &b_hltIter0IterL3FromL1MuonTrackAssociated_eta);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_phi", &hltIter0IterL3FromL1MuonTrackAssociated_phi, &b_hltIter0IterL3FromL1MuonTrackAssociated_phi);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_charge", &hltIter0IterL3FromL1MuonTrackAssociated_charge, &b_hltIter0IterL3FromL1MuonTrackAssociated_charge);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_matchedL3", &hltIter0IterL3FromL1MuonTrackAssociated_matchedL3, &b_hltIter0IterL3FromL1MuonTrackAssociated_matchedL3);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId", &hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId, &b_hltIter0IterL3FromL1MuonTrackAssociated_matchedL3NoId);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction", &hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction, &b_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize", &hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize, &b_hltIter0IterL3FromL1MuonTrackAssociated_matchedTPsize);
    fChain->SetBranchAddress("hltIter0IterL3FromL1MuonTrackAssociated_mva", &hltIter0IterL3FromL1MuonTrackAssociated_mva, &b_hltIter0IterL3FromL1MuonTrackAssociated_mva);
    fChain->SetBranchAddress("ntpTo_hltIter0IterL3FromL1MuonTrackAssociated", &ntpTo_hltIter0IterL3FromL1MuonTrackAssociated, &b_ntpTo_hltIter0IterL3FromL1MuonTrackAssociated);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_energy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_status);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2);

    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIter0IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits);
    // fChain->SetBranchAddress("nhltIter2IterL3FromL1MuonTrackAssociated", &nhltIter2IterL3FromL1MuonTrackAssociated, &b_nhltIter2IterL3FromL1MuonTrackAssociated);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_pt", &hltIter2IterL3FromL1MuonTrackAssociated_pt, &b_hltIter2IterL3FromL1MuonTrackAssociated_pt);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_eta", &hltIter2IterL3FromL1MuonTrackAssociated_eta, &b_hltIter2IterL3FromL1MuonTrackAssociated_eta);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_phi", &hltIter2IterL3FromL1MuonTrackAssociated_phi, &b_hltIter2IterL3FromL1MuonTrackAssociated_phi);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_charge", &hltIter2IterL3FromL1MuonTrackAssociated_charge, &b_hltIter2IterL3FromL1MuonTrackAssociated_charge);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_matchedL3", &hltIter2IterL3FromL1MuonTrackAssociated_matchedL3, &b_hltIter2IterL3FromL1MuonTrackAssociated_matchedL3);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId", &hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId, &b_hltIter2IterL3FromL1MuonTrackAssociated_matchedL3NoId);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_charge);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pdgId);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_energy);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_pt);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_eta);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_phi);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVx);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVy);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_parentVz);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_status);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfHits);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction", &hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction, &b_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTP_sharedFraction);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize", &hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize, &b_hltIter2IterL3FromL1MuonTrackAssociated_matchedTPsize);
    // fChain->SetBranchAddress("hltIter2IterL3FromL1MuonTrackAssociated_mva", &hltIter2IterL3FromL1MuonTrackAssociated_mva, &b_hltIter2IterL3FromL1MuonTrackAssociated_mva);
    // fChain->SetBranchAddress("ntpTo_hltIter2IterL3FromL1MuonTrackAssociated", &ntpTo_hltIter2IterL3FromL1MuonTrackAssociated, &b_ntpTo_hltIter2IterL3FromL1MuonTrackAssociated);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pdgId);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_energy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVx);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_parentVz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_status);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfHits);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerHits);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_numberOfTrackerLayers);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pdgId);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_gen_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pt);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_eta);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_phi);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_charge);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_px);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_py);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_pz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vx);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vy);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_vz);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxy_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dxyError_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dz_bs);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_dzError);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_normalizedChi2);

    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_quality);
    // fChain->SetBranchAddress("tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIter2IterL3FromL1MuonTrackAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("nhltIterL3MuonMergedAssociated", &nhltIterL3MuonMergedAssociated, &b_nhltIterL3MuonMergedAssociated);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_pt", &hltIterL3MuonMergedAssociated_pt, &b_hltIterL3MuonMergedAssociated_pt);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_eta", &hltIterL3MuonMergedAssociated_eta, &b_hltIterL3MuonMergedAssociated_eta);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_phi", &hltIterL3MuonMergedAssociated_phi, &b_hltIterL3MuonMergedAssociated_phi);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_charge", &hltIterL3MuonMergedAssociated_charge, &b_hltIterL3MuonMergedAssociated_charge);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_matchedL3", &hltIterL3MuonMergedAssociated_matchedL3, &b_hltIterL3MuonMergedAssociated_matchedL3);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_matchedL3NoId", &hltIterL3MuonMergedAssociated_matchedL3NoId, &b_hltIterL3MuonMergedAssociated_matchedL3NoId);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_charge", &hltIterL3MuonMergedAssociated_bestMatchTP_charge, &b_hltIterL3MuonMergedAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_pdgId", &hltIterL3MuonMergedAssociated_bestMatchTP_pdgId, &b_hltIterL3MuonMergedAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_energy", &hltIterL3MuonMergedAssociated_bestMatchTP_energy, &b_hltIterL3MuonMergedAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_pt", &hltIterL3MuonMergedAssociated_bestMatchTP_pt, &b_hltIterL3MuonMergedAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_eta", &hltIterL3MuonMergedAssociated_bestMatchTP_eta, &b_hltIterL3MuonMergedAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_phi", &hltIterL3MuonMergedAssociated_bestMatchTP_phi, &b_hltIterL3MuonMergedAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_parentVx", &hltIterL3MuonMergedAssociated_bestMatchTP_parentVx, &b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_parentVy", &hltIterL3MuonMergedAssociated_bestMatchTP_parentVy, &b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_parentVz", &hltIterL3MuonMergedAssociated_bestMatchTP_parentVz, &b_hltIterL3MuonMergedAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_status", &hltIterL3MuonMergedAssociated_bestMatchTP_status, &b_hltIterL3MuonMergedAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits", &hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits, &b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits", &hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers", &hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIterL3MuonMergedAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction", &hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction, &b_hltIterL3MuonMergedAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_matchedTPsize", &hltIterL3MuonMergedAssociated_matchedTPsize, &b_hltIterL3MuonMergedAssociated_matchedTPsize);
    fChain->SetBranchAddress("hltIterL3MuonMergedAssociated_mva", &hltIterL3MuonMergedAssociated_mva, &b_hltIterL3MuonMergedAssociated_mva);
    fChain->SetBranchAddress("ntpTo_hltIterL3MuonMergedAssociated", &ntpTo_hltIterL3MuonMergedAssociated, &b_ntpTo_hltIterL3MuonMergedAssociated);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_charge", &tpTo_hltIterL3MuonMergedAssociated_charge, &b_tpTo_hltIterL3MuonMergedAssociated_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_pdgId", &tpTo_hltIterL3MuonMergedAssociated_pdgId, &b_tpTo_hltIterL3MuonMergedAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_energy", &tpTo_hltIterL3MuonMergedAssociated_energy, &b_tpTo_hltIterL3MuonMergedAssociated_energy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_pt", &tpTo_hltIterL3MuonMergedAssociated_pt, &b_tpTo_hltIterL3MuonMergedAssociated_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_eta", &tpTo_hltIterL3MuonMergedAssociated_eta, &b_tpTo_hltIterL3MuonMergedAssociated_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_phi", &tpTo_hltIterL3MuonMergedAssociated_phi, &b_tpTo_hltIterL3MuonMergedAssociated_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_parentVx", &tpTo_hltIterL3MuonMergedAssociated_parentVx, &b_tpTo_hltIterL3MuonMergedAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_parentVy", &tpTo_hltIterL3MuonMergedAssociated_parentVy, &b_tpTo_hltIterL3MuonMergedAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_parentVz", &tpTo_hltIterL3MuonMergedAssociated_parentVz, &b_tpTo_hltIterL3MuonMergedAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_status", &tpTo_hltIterL3MuonMergedAssociated_status, &b_tpTo_hltIterL3MuonMergedAssociated_status);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_numberOfHits", &tpTo_hltIterL3MuonMergedAssociated_numberOfHits, &b_tpTo_hltIterL3MuonMergedAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits", &tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits, &b_tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers", &tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers, &b_tpTo_hltIterL3MuonMergedAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_gen_charge", &tpTo_hltIterL3MuonMergedAssociated_gen_charge, &b_tpTo_hltIterL3MuonMergedAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_gen_pdgId", &tpTo_hltIterL3MuonMergedAssociated_gen_pdgId, &b_tpTo_hltIterL3MuonMergedAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_gen_pt", &tpTo_hltIterL3MuonMergedAssociated_gen_pt, &b_tpTo_hltIterL3MuonMergedAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_gen_eta", &tpTo_hltIterL3MuonMergedAssociated_gen_eta, &b_tpTo_hltIterL3MuonMergedAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_gen_phi", &tpTo_hltIterL3MuonMergedAssociated_gen_phi, &b_tpTo_hltIterL3MuonMergedAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_normalizedChi2);

    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits", &tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIterL3MuonMergedAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("nhltIterL3MuonAndMuonFromL1MergedAssociated", &nhltIterL3MuonAndMuonFromL1MergedAssociated, &b_nhltIterL3MuonAndMuonFromL1MergedAssociated);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_pt", &hltIterL3MuonAndMuonFromL1MergedAssociated_pt, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_pt);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_eta", &hltIterL3MuonAndMuonFromL1MergedAssociated_eta, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_eta);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_phi", &hltIterL3MuonAndMuonFromL1MergedAssociated_phi, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_phi);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_charge", &hltIterL3MuonAndMuonFromL1MergedAssociated_charge, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_charge);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3", &hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId", &hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedL3NoId);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction", &hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize", &hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_matchedTPsize);
    fChain->SetBranchAddress("hltIterL3MuonAndMuonFromL1MergedAssociated_mva", &hltIterL3MuonAndMuonFromL1MergedAssociated_mva, &b_hltIterL3MuonAndMuonFromL1MergedAssociated_mva);
    fChain->SetBranchAddress("ntpTo_hltIterL3MuonAndMuonFromL1MergedAssociated", &ntpTo_hltIterL3MuonAndMuonFromL1MergedAssociated, &b_ntpTo_hltIterL3MuonAndMuonFromL1MergedAssociated);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_energy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_status);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_normalizedChi2);

    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits", &tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltIterL3MuonAndMuonFromL1MergedAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("niterL3MuonNoIDTrackAssociated", &niterL3MuonNoIDTrackAssociated, &b_niterL3MuonNoIDTrackAssociated);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_pt", &iterL3MuonNoIDTrackAssociated_pt, &b_iterL3MuonNoIDTrackAssociated_pt);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_eta", &iterL3MuonNoIDTrackAssociated_eta, &b_iterL3MuonNoIDTrackAssociated_eta);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_phi", &iterL3MuonNoIDTrackAssociated_phi, &b_iterL3MuonNoIDTrackAssociated_phi);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_charge", &iterL3MuonNoIDTrackAssociated_charge, &b_iterL3MuonNoIDTrackAssociated_charge);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_matchedL3", &iterL3MuonNoIDTrackAssociated_matchedL3, &b_iterL3MuonNoIDTrackAssociated_matchedL3);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_matchedL3NoId", &iterL3MuonNoIDTrackAssociated_matchedL3NoId, &b_iterL3MuonNoIDTrackAssociated_matchedL3NoId);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_charge", &iterL3MuonNoIDTrackAssociated_bestMatchTP_charge, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId", &iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_energy", &iterL3MuonNoIDTrackAssociated_bestMatchTP_energy, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_pt", &iterL3MuonNoIDTrackAssociated_bestMatchTP_pt, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_eta", &iterL3MuonNoIDTrackAssociated_bestMatchTP_eta, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_phi", &iterL3MuonNoIDTrackAssociated_bestMatchTP_phi, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx", &iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy", &iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz", &iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_status", &iterL3MuonNoIDTrackAssociated_bestMatchTP_status, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits", &iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits", &iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers", &iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction", &iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction, &b_iterL3MuonNoIDTrackAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_matchedTPsize", &iterL3MuonNoIDTrackAssociated_matchedTPsize, &b_iterL3MuonNoIDTrackAssociated_matchedTPsize);
    fChain->SetBranchAddress("iterL3MuonNoIDTrackAssociated_mva", &iterL3MuonNoIDTrackAssociated_mva, &b_iterL3MuonNoIDTrackAssociated_mva);
    fChain->SetBranchAddress("ntpTo_iterL3MuonNoIDTrackAssociated", &ntpTo_iterL3MuonNoIDTrackAssociated, &b_ntpTo_iterL3MuonNoIDTrackAssociated);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_charge", &tpTo_iterL3MuonNoIDTrackAssociated_charge, &b_tpTo_iterL3MuonNoIDTrackAssociated_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_pdgId", &tpTo_iterL3MuonNoIDTrackAssociated_pdgId, &b_tpTo_iterL3MuonNoIDTrackAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_energy", &tpTo_iterL3MuonNoIDTrackAssociated_energy, &b_tpTo_iterL3MuonNoIDTrackAssociated_energy);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_pt", &tpTo_iterL3MuonNoIDTrackAssociated_pt, &b_tpTo_iterL3MuonNoIDTrackAssociated_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_eta", &tpTo_iterL3MuonNoIDTrackAssociated_eta, &b_tpTo_iterL3MuonNoIDTrackAssociated_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_phi", &tpTo_iterL3MuonNoIDTrackAssociated_phi, &b_tpTo_iterL3MuonNoIDTrackAssociated_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_parentVx", &tpTo_iterL3MuonNoIDTrackAssociated_parentVx, &b_tpTo_iterL3MuonNoIDTrackAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_parentVy", &tpTo_iterL3MuonNoIDTrackAssociated_parentVy, &b_tpTo_iterL3MuonNoIDTrackAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_parentVz", &tpTo_iterL3MuonNoIDTrackAssociated_parentVz, &b_tpTo_iterL3MuonNoIDTrackAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_status", &tpTo_iterL3MuonNoIDTrackAssociated_status, &b_tpTo_iterL3MuonNoIDTrackAssociated_status);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits", &tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits, &b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits", &tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits, &b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers", &tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers, &b_tpTo_iterL3MuonNoIDTrackAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_gen_charge", &tpTo_iterL3MuonNoIDTrackAssociated_gen_charge, &b_tpTo_iterL3MuonNoIDTrackAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId", &tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId, &b_tpTo_iterL3MuonNoIDTrackAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_gen_pt", &tpTo_iterL3MuonNoIDTrackAssociated_gen_pt, &b_tpTo_iterL3MuonNoIDTrackAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_gen_eta", &tpTo_iterL3MuonNoIDTrackAssociated_gen_eta, &b_tpTo_iterL3MuonNoIDTrackAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_gen_phi", &tpTo_iterL3MuonNoIDTrackAssociated_gen_phi, &b_tpTo_iterL3MuonNoIDTrackAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_normalizedChi2);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits", &tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_iterL3MuonNoIDTrackAssociated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("niterL3MuonTrackAssociated", &niterL3MuonTrackAssociated, &b_niterL3MuonTrackAssociated);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_pt", &iterL3MuonTrackAssociated_pt, &b_iterL3MuonTrackAssociated_pt);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_eta", &iterL3MuonTrackAssociated_eta, &b_iterL3MuonTrackAssociated_eta);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_phi", &iterL3MuonTrackAssociated_phi, &b_iterL3MuonTrackAssociated_phi);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_charge", &iterL3MuonTrackAssociated_charge, &b_iterL3MuonTrackAssociated_charge);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_matchedL3", &iterL3MuonTrackAssociated_matchedL3, &b_iterL3MuonTrackAssociated_matchedL3);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_matchedL3NoId", &iterL3MuonTrackAssociated_matchedL3NoId, &b_iterL3MuonTrackAssociated_matchedL3NoId);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_charge", &iterL3MuonTrackAssociated_bestMatchTP_charge, &b_iterL3MuonTrackAssociated_bestMatchTP_charge);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_pdgId", &iterL3MuonTrackAssociated_bestMatchTP_pdgId, &b_iterL3MuonTrackAssociated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_energy", &iterL3MuonTrackAssociated_bestMatchTP_energy, &b_iterL3MuonTrackAssociated_bestMatchTP_energy);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_pt", &iterL3MuonTrackAssociated_bestMatchTP_pt, &b_iterL3MuonTrackAssociated_bestMatchTP_pt);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_eta", &iterL3MuonTrackAssociated_bestMatchTP_eta, &b_iterL3MuonTrackAssociated_bestMatchTP_eta);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_phi", &iterL3MuonTrackAssociated_bestMatchTP_phi, &b_iterL3MuonTrackAssociated_bestMatchTP_phi);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_parentVx", &iterL3MuonTrackAssociated_bestMatchTP_parentVx, &b_iterL3MuonTrackAssociated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_parentVy", &iterL3MuonTrackAssociated_bestMatchTP_parentVy, &b_iterL3MuonTrackAssociated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_parentVz", &iterL3MuonTrackAssociated_bestMatchTP_parentVz, &b_iterL3MuonTrackAssociated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_status", &iterL3MuonTrackAssociated_bestMatchTP_status, &b_iterL3MuonTrackAssociated_bestMatchTP_status);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_numberOfHits", &iterL3MuonTrackAssociated_bestMatchTP_numberOfHits, &b_iterL3MuonTrackAssociated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits", &iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits, &b_iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers", &iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers, &b_iterL3MuonTrackAssociated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_bestMatchTP_sharedFraction", &iterL3MuonTrackAssociated_bestMatchTP_sharedFraction, &b_iterL3MuonTrackAssociated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_matchedTPsize", &iterL3MuonTrackAssociated_matchedTPsize, &b_iterL3MuonTrackAssociated_matchedTPsize);
    fChain->SetBranchAddress("iterL3MuonTrackAssociated_mva", &iterL3MuonTrackAssociated_mva, &b_iterL3MuonTrackAssociated_mva);
    fChain->SetBranchAddress("ntpTo_iterL3MuonTrackAssociated", &ntpTo_iterL3MuonTrackAssociated, &b_ntpTo_iterL3MuonTrackAssociated);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_charge", &tpTo_iterL3MuonTrackAssociated_charge, &b_tpTo_iterL3MuonTrackAssociated_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_pdgId", &tpTo_iterL3MuonTrackAssociated_pdgId, &b_tpTo_iterL3MuonTrackAssociated_pdgId);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_energy", &tpTo_iterL3MuonTrackAssociated_energy, &b_tpTo_iterL3MuonTrackAssociated_energy);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_pt", &tpTo_iterL3MuonTrackAssociated_pt, &b_tpTo_iterL3MuonTrackAssociated_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_eta", &tpTo_iterL3MuonTrackAssociated_eta, &b_tpTo_iterL3MuonTrackAssociated_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_phi", &tpTo_iterL3MuonTrackAssociated_phi, &b_tpTo_iterL3MuonTrackAssociated_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_parentVx", &tpTo_iterL3MuonTrackAssociated_parentVx, &b_tpTo_iterL3MuonTrackAssociated_parentVx);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_parentVy", &tpTo_iterL3MuonTrackAssociated_parentVy, &b_tpTo_iterL3MuonTrackAssociated_parentVy);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_parentVz", &tpTo_iterL3MuonTrackAssociated_parentVz, &b_tpTo_iterL3MuonTrackAssociated_parentVz);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_status", &tpTo_iterL3MuonTrackAssociated_status, &b_tpTo_iterL3MuonTrackAssociated_status);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_numberOfHits", &tpTo_iterL3MuonTrackAssociated_numberOfHits, &b_tpTo_iterL3MuonTrackAssociated_numberOfHits);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits", &tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits, &b_tpTo_iterL3MuonTrackAssociated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers", &tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers, &b_tpTo_iterL3MuonTrackAssociated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_gen_charge", &tpTo_iterL3MuonTrackAssociated_gen_charge, &b_tpTo_iterL3MuonTrackAssociated_gen_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_gen_pdgId", &tpTo_iterL3MuonTrackAssociated_gen_pdgId, &b_tpTo_iterL3MuonTrackAssociated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_gen_pt", &tpTo_iterL3MuonTrackAssociated_gen_pt, &b_tpTo_iterL3MuonTrackAssociated_gen_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_gen_eta", &tpTo_iterL3MuonTrackAssociated_gen_eta, &b_tpTo_iterL3MuonTrackAssociated_gen_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_gen_phi", &tpTo_iterL3MuonTrackAssociated_gen_phi, &b_tpTo_iterL3MuonTrackAssociated_gen_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_normalizedChi2);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits", &tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits, &b_tpTo_iterL3MuonTrackAssociated_bestMatchTrk_NValidHits);


    // fChain->SetBranchAddress("nhltPixelTracksAssociated", &nhltPixelTracksAssociated, &b_nhltPixelTracksAssociated);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_pt", &hltPixelTracksAssociated_pt, &b_hltPixelTracksAssociated_pt);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_eta", &hltPixelTracksAssociated_eta, &b_hltPixelTracksAssociated_eta);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_phi", &hltPixelTracksAssociated_phi, &b_hltPixelTracksAssociated_phi);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_charge", &hltPixelTracksAssociated_charge, &b_hltPixelTracksAssociated_charge);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_matchedL3", &hltPixelTracksAssociated_matchedL3, &b_hltPixelTracksAssociated_matchedL3);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_matchedL3NoId", &hltPixelTracksAssociated_matchedL3NoId, &b_hltPixelTracksAssociated_matchedL3NoId);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_charge", &hltPixelTracksAssociated_bestMatchTP_charge, &b_hltPixelTracksAssociated_bestMatchTP_charge);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_pdgId", &hltPixelTracksAssociated_bestMatchTP_pdgId, &b_hltPixelTracksAssociated_bestMatchTP_pdgId);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_energy", &hltPixelTracksAssociated_bestMatchTP_energy, &b_hltPixelTracksAssociated_bestMatchTP_energy);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_pt", &hltPixelTracksAssociated_bestMatchTP_pt, &b_hltPixelTracksAssociated_bestMatchTP_pt);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_eta", &hltPixelTracksAssociated_bestMatchTP_eta, &b_hltPixelTracksAssociated_bestMatchTP_eta);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_phi", &hltPixelTracksAssociated_bestMatchTP_phi, &b_hltPixelTracksAssociated_bestMatchTP_phi);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_parentVx", &hltPixelTracksAssociated_bestMatchTP_parentVx, &b_hltPixelTracksAssociated_bestMatchTP_parentVx);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_parentVy", &hltPixelTracksAssociated_bestMatchTP_parentVy, &b_hltPixelTracksAssociated_bestMatchTP_parentVy);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_parentVz", &hltPixelTracksAssociated_bestMatchTP_parentVz, &b_hltPixelTracksAssociated_bestMatchTP_parentVz);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_status", &hltPixelTracksAssociated_bestMatchTP_status, &b_hltPixelTracksAssociated_bestMatchTP_status);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_numberOfHits", &hltPixelTracksAssociated_bestMatchTP_numberOfHits, &b_hltPixelTracksAssociated_bestMatchTP_numberOfHits);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits", &hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits, &b_hltPixelTracksAssociated_bestMatchTP_numberOfTrackerHits);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers", &hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltPixelTracksAssociated_bestMatchTP_numberOfTrackerLayers);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_bestMatchTP_sharedFraction", &hltPixelTracksAssociated_bestMatchTP_sharedFraction, &b_hltPixelTracksAssociated_bestMatchTP_sharedFraction);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_matchedTPsize", &hltPixelTracksAssociated_matchedTPsize, &b_hltPixelTracksAssociated_matchedTPsize);
    // fChain->SetBranchAddress("hltPixelTracksAssociated_mva", &hltPixelTracksAssociated_mva, &b_hltPixelTracksAssociated_mva);


    fChain->SetBranchAddress("nhltPixelTracksInRegionL2Associated", &nhltPixelTracksInRegionL2Associated, &b_nhltPixelTracksInRegionL2Associated);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_pt", &hltPixelTracksInRegionL2Associated_pt, &b_hltPixelTracksInRegionL2Associated_pt);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_eta", &hltPixelTracksInRegionL2Associated_eta, &b_hltPixelTracksInRegionL2Associated_eta);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_phi", &hltPixelTracksInRegionL2Associated_phi, &b_hltPixelTracksInRegionL2Associated_phi);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_charge", &hltPixelTracksInRegionL2Associated_charge, &b_hltPixelTracksInRegionL2Associated_charge);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_matchedL3", &hltPixelTracksInRegionL2Associated_matchedL3, &b_hltPixelTracksInRegionL2Associated_matchedL3);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_matchedL3NoId", &hltPixelTracksInRegionL2Associated_matchedL3NoId, &b_hltPixelTracksInRegionL2Associated_matchedL3NoId);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_charge", &hltPixelTracksInRegionL2Associated_bestMatchTP_charge, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId", &hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_energy", &hltPixelTracksInRegionL2Associated_bestMatchTP_energy, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_pt", &hltPixelTracksInRegionL2Associated_bestMatchTP_pt, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_eta", &hltPixelTracksInRegionL2Associated_bestMatchTP_eta, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_phi", &hltPixelTracksInRegionL2Associated_bestMatchTP_phi, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx", &hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy", &hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz", &hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_status", &hltPixelTracksInRegionL2Associated_bestMatchTP_status, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_status);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits", &hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits", &hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers", &hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction", &hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction, &b_hltPixelTracksInRegionL2Associated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_matchedTPsize", &hltPixelTracksInRegionL2Associated_matchedTPsize, &b_hltPixelTracksInRegionL2Associated_matchedTPsize);
    fChain->SetBranchAddress("hltPixelTracksInRegionL2Associated_mva", &hltPixelTracksInRegionL2Associated_mva, &b_hltPixelTracksInRegionL2Associated_mva);
    fChain->SetBranchAddress("ntpTo_hltPixelTracksInRegionL2Associated", &ntpTo_hltPixelTracksInRegionL2Associated, &b_ntpTo_hltPixelTracksInRegionL2Associated);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_charge", &tpTo_hltPixelTracksInRegionL2Associated_charge, &b_tpTo_hltPixelTracksInRegionL2Associated_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_pdgId", &tpTo_hltPixelTracksInRegionL2Associated_pdgId, &b_tpTo_hltPixelTracksInRegionL2Associated_pdgId);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_energy", &tpTo_hltPixelTracksInRegionL2Associated_energy, &b_tpTo_hltPixelTracksInRegionL2Associated_energy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_pt", &tpTo_hltPixelTracksInRegionL2Associated_pt, &b_tpTo_hltPixelTracksInRegionL2Associated_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_eta", &tpTo_hltPixelTracksInRegionL2Associated_eta, &b_tpTo_hltPixelTracksInRegionL2Associated_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_phi", &tpTo_hltPixelTracksInRegionL2Associated_phi, &b_tpTo_hltPixelTracksInRegionL2Associated_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_parentVx", &tpTo_hltPixelTracksInRegionL2Associated_parentVx, &b_tpTo_hltPixelTracksInRegionL2Associated_parentVx);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_parentVy", &tpTo_hltPixelTracksInRegionL2Associated_parentVy, &b_tpTo_hltPixelTracksInRegionL2Associated_parentVy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_parentVz", &tpTo_hltPixelTracksInRegionL2Associated_parentVz, &b_tpTo_hltPixelTracksInRegionL2Associated_parentVz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_status", &tpTo_hltPixelTracksInRegionL2Associated_status, &b_tpTo_hltPixelTracksInRegionL2Associated_status);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_numberOfHits", &tpTo_hltPixelTracksInRegionL2Associated_numberOfHits, &b_tpTo_hltPixelTracksInRegionL2Associated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits", &tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits, &b_tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers", &tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers, &b_tpTo_hltPixelTracksInRegionL2Associated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_gen_charge", &tpTo_hltPixelTracksInRegionL2Associated_gen_charge, &b_tpTo_hltPixelTracksInRegionL2Associated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId", &tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId, &b_tpTo_hltPixelTracksInRegionL2Associated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_gen_pt", &tpTo_hltPixelTracksInRegionL2Associated_gen_pt, &b_tpTo_hltPixelTracksInRegionL2Associated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_gen_eta", &tpTo_hltPixelTracksInRegionL2Associated_gen_eta, &b_tpTo_hltPixelTracksInRegionL2Associated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_gen_phi", &tpTo_hltPixelTracksInRegionL2Associated_gen_phi, &b_tpTo_hltPixelTracksInRegionL2Associated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_normalizedChi2);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits", &tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits, &b_tpTo_hltPixelTracksInRegionL2Associated_bestMatchTrk_NValidHits);


    fChain->SetBranchAddress("nhltPixelTracksInRegionL1Associated", &nhltPixelTracksInRegionL1Associated, &b_nhltPixelTracksInRegionL1Associated);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_pt", &hltPixelTracksInRegionL1Associated_pt, &b_hltPixelTracksInRegionL1Associated_pt);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_eta", &hltPixelTracksInRegionL1Associated_eta, &b_hltPixelTracksInRegionL1Associated_eta);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_phi", &hltPixelTracksInRegionL1Associated_phi, &b_hltPixelTracksInRegionL1Associated_phi);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_charge", &hltPixelTracksInRegionL1Associated_charge, &b_hltPixelTracksInRegionL1Associated_charge);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_matchedL3", &hltPixelTracksInRegionL1Associated_matchedL3, &b_hltPixelTracksInRegionL1Associated_matchedL3);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_matchedL3NoId", &hltPixelTracksInRegionL1Associated_matchedL3NoId, &b_hltPixelTracksInRegionL1Associated_matchedL3NoId);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_charge", &hltPixelTracksInRegionL1Associated_bestMatchTP_charge, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_charge);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId", &hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_pdgId);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_energy", &hltPixelTracksInRegionL1Associated_bestMatchTP_energy, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_energy);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_pt", &hltPixelTracksInRegionL1Associated_bestMatchTP_pt, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_pt);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_eta", &hltPixelTracksInRegionL1Associated_bestMatchTP_eta, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_eta);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_phi", &hltPixelTracksInRegionL1Associated_bestMatchTP_phi, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_phi);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx", &hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVx);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy", &hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVy);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz", &hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_parentVz);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_status", &hltPixelTracksInRegionL1Associated_bestMatchTP_status, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_status);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits", &hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfHits);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits", &hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerHits);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers", &hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_numberOfTrackerLayers);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction", &hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction, &b_hltPixelTracksInRegionL1Associated_bestMatchTP_sharedFraction);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_matchedTPsize", &hltPixelTracksInRegionL1Associated_matchedTPsize, &b_hltPixelTracksInRegionL1Associated_matchedTPsize);
    fChain->SetBranchAddress("hltPixelTracksInRegionL1Associated_mva", &hltPixelTracksInRegionL1Associated_mva, &b_hltPixelTracksInRegionL1Associated_mva);
    fChain->SetBranchAddress("ntpTo_hltPixelTracksInRegionL1Associated", &ntpTo_hltPixelTracksInRegionL1Associated, &b_ntpTo_hltPixelTracksInRegionL1Associated);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_charge", &tpTo_hltPixelTracksInRegionL1Associated_charge, &b_tpTo_hltPixelTracksInRegionL1Associated_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_pdgId", &tpTo_hltPixelTracksInRegionL1Associated_pdgId, &b_tpTo_hltPixelTracksInRegionL1Associated_pdgId);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_energy", &tpTo_hltPixelTracksInRegionL1Associated_energy, &b_tpTo_hltPixelTracksInRegionL1Associated_energy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_pt", &tpTo_hltPixelTracksInRegionL1Associated_pt, &b_tpTo_hltPixelTracksInRegionL1Associated_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_eta", &tpTo_hltPixelTracksInRegionL1Associated_eta, &b_tpTo_hltPixelTracksInRegionL1Associated_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_phi", &tpTo_hltPixelTracksInRegionL1Associated_phi, &b_tpTo_hltPixelTracksInRegionL1Associated_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_parentVx", &tpTo_hltPixelTracksInRegionL1Associated_parentVx, &b_tpTo_hltPixelTracksInRegionL1Associated_parentVx);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_parentVy", &tpTo_hltPixelTracksInRegionL1Associated_parentVy, &b_tpTo_hltPixelTracksInRegionL1Associated_parentVy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_parentVz", &tpTo_hltPixelTracksInRegionL1Associated_parentVz, &b_tpTo_hltPixelTracksInRegionL1Associated_parentVz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_status", &tpTo_hltPixelTracksInRegionL1Associated_status, &b_tpTo_hltPixelTracksInRegionL1Associated_status);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_numberOfHits", &tpTo_hltPixelTracksInRegionL1Associated_numberOfHits, &b_tpTo_hltPixelTracksInRegionL1Associated_numberOfHits);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits", &tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits, &b_tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerHits);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers", &tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers, &b_tpTo_hltPixelTracksInRegionL1Associated_numberOfTrackerLayers);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_gen_charge", &tpTo_hltPixelTracksInRegionL1Associated_gen_charge, &b_tpTo_hltPixelTracksInRegionL1Associated_gen_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId", &tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId, &b_tpTo_hltPixelTracksInRegionL1Associated_gen_pdgId);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_gen_pt", &tpTo_hltPixelTracksInRegionL1Associated_gen_pt, &b_tpTo_hltPixelTracksInRegionL1Associated_gen_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_gen_eta", &tpTo_hltPixelTracksInRegionL1Associated_gen_eta, &b_tpTo_hltPixelTracksInRegionL1Associated_gen_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_gen_phi", &tpTo_hltPixelTracksInRegionL1Associated_gen_phi, &b_tpTo_hltPixelTracksInRegionL1Associated_gen_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pt);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_eta);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_phi);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_charge);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_px);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_py);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_pz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vx);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vy);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_vz);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxy_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dxyError_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dz_bs);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_dzError);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_normalizedChi2);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_quality);
    fChain->SetBranchAddress("tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits", &tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits, &b_tpTo_hltPixelTracksInRegionL1Associated_bestMatchTrk_NValidHits);
    fChain->SetBranchAddress("hi_cBin", &hi_cBin, &b_hi_cBin);


    // fChain->SetBranchAddress("nhltPixelTracksForSeedsL3MuonAssociated", &nhltPixelTracksForSeedsL3MuonAssociated, &b_nhltPixelTracksForSeedsL3MuonAssociated);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_pt", &hltPixelTracksForSeedsL3MuonAssociated_pt, &b_hltPixelTracksForSeedsL3MuonAssociated_pt);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_eta", &hltPixelTracksForSeedsL3MuonAssociated_eta, &b_hltPixelTracksForSeedsL3MuonAssociated_eta);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_phi", &hltPixelTracksForSeedsL3MuonAssociated_phi, &b_hltPixelTracksForSeedsL3MuonAssociated_phi);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_charge", &hltPixelTracksForSeedsL3MuonAssociated_charge, &b_hltPixelTracksForSeedsL3MuonAssociated_charge);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_matchedL3", &hltPixelTracksForSeedsL3MuonAssociated_matchedL3, &b_hltPixelTracksForSeedsL3MuonAssociated_matchedL3);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId", &hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId, &b_hltPixelTracksForSeedsL3MuonAssociated_matchedL3NoId);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_charge);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pdgId);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_energy);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_pt);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_eta);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_phi);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVx);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVy);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_parentVz);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_status);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfHits);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerHits);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_numberOfTrackerLayers);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction", &hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction, &b_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTP_sharedFraction);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize", &hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize, &b_hltPixelTracksForSeedsL3MuonAssociated_matchedTPsize);
    // fChain->SetBranchAddress("hltPixelTracksForSeedsL3MuonAssociated_mva", &hltPixelTracksForSeedsL3MuonAssociated_mva, &b_hltPixelTracksForSeedsL3MuonAssociated_mva);
    // fChain->SetBranchAddress("ntpTo_hltPixelTracksForSeedsL3MuonAssociated", &ntpTo_hltPixelTracksForSeedsL3MuonAssociated, &b_ntpTo_hltPixelTracksForSeedsL3MuonAssociated);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_charge);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_pdgId);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_energy);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_pt);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_eta);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_phi);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVx);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVy);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_parentVz);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_status", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_status, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_status);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfHits);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerHits);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_numberOfTrackerLayers);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_charge);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pdgId);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_pt);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_eta);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_gen_phi);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pt);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_eta);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_phi);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_charge);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_px);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_py);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_pz);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vx);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vy);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_vz);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxy_bs);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dxyError_bs);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dz_bs);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_dzError);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_normalizedChi2);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_quality);
    // fChain->SetBranchAddress("tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits", &tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltPixelTracksForSeedsL3MuonAssociated_bestMatchTrk_NValidHits);

    // fChain->SetBranchAddress("nhltGlbTrkMuonTracksAssociated", &nhltGlbTrkMuonTracksAssociated, &b_nhltGlbTrkMuonTracksAssociated);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_pt", &hltGlbTrkMuonTracksAssociated_pt, &b_hltGlbTrkMuonTracksAssociated_pt);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_eta", &hltGlbTrkMuonTracksAssociated_eta, &b_hltGlbTrkMuonTracksAssociated_eta);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_phi", &hltGlbTrkMuonTracksAssociated_phi, &b_hltGlbTrkMuonTracksAssociated_phi);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_charge", &hltGlbTrkMuonTracksAssociated_charge, &b_hltGlbTrkMuonTracksAssociated_charge);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_matchedL3", &hltGlbTrkMuonTracksAssociated_matchedL3, &b_hltGlbTrkMuonTracksAssociated_matchedL3);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_matchedL3NoId", &hltGlbTrkMuonTracksAssociated_matchedL3NoId, &b_hltGlbTrkMuonTracksAssociated_matchedL3NoId);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_charge", &hltGlbTrkMuonTracksAssociated_bestMatchTP_charge, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_charge);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId", &hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_pdgId);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_energy", &hltGlbTrkMuonTracksAssociated_bestMatchTP_energy, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_energy);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_pt", &hltGlbTrkMuonTracksAssociated_bestMatchTP_pt, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_pt);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_eta", &hltGlbTrkMuonTracksAssociated_bestMatchTP_eta, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_eta);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_phi", &hltGlbTrkMuonTracksAssociated_bestMatchTP_phi, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_phi);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx", &hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVx);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy", &hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVy);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz", &hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_parentVz);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_status", &hltGlbTrkMuonTracksAssociated_bestMatchTP_status, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_status);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits", &hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfHits);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits", &hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerHits);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers", &hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_numberOfTrackerLayers);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction", &hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction, &b_hltGlbTrkMuonTracksAssociated_bestMatchTP_sharedFraction);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_matchedTPsize", &hltGlbTrkMuonTracksAssociated_matchedTPsize, &b_hltGlbTrkMuonTracksAssociated_matchedTPsize);
    // fChain->SetBranchAddress("hltGlbTrkMuonTracksAssociated_mva", &hltGlbTrkMuonTracksAssociated_mva, &b_hltGlbTrkMuonTracksAssociated_mva);
    // fChain->SetBranchAddress("ntpTo_hltGlbTrkMuonTracksAssociated", &ntpTo_hltGlbTrkMuonTracksAssociated, &b_ntpTo_hltGlbTrkMuonTracksAssociated);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_charge", &tpTo_hltGlbTrkMuonTracksAssociated_charge, &b_tpTo_hltGlbTrkMuonTracksAssociated_charge);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_pdgId", &tpTo_hltGlbTrkMuonTracksAssociated_pdgId, &b_tpTo_hltGlbTrkMuonTracksAssociated_pdgId);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_energy", &tpTo_hltGlbTrkMuonTracksAssociated_energy, &b_tpTo_hltGlbTrkMuonTracksAssociated_energy);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_pt", &tpTo_hltGlbTrkMuonTracksAssociated_pt, &b_tpTo_hltGlbTrkMuonTracksAssociated_pt);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_eta", &tpTo_hltGlbTrkMuonTracksAssociated_eta, &b_tpTo_hltGlbTrkMuonTracksAssociated_eta);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_phi", &tpTo_hltGlbTrkMuonTracksAssociated_phi, &b_tpTo_hltGlbTrkMuonTracksAssociated_phi);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_parentVx", &tpTo_hltGlbTrkMuonTracksAssociated_parentVx, &b_tpTo_hltGlbTrkMuonTracksAssociated_parentVx);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_parentVy", &tpTo_hltGlbTrkMuonTracksAssociated_parentVy, &b_tpTo_hltGlbTrkMuonTracksAssociated_parentVy);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_parentVz", &tpTo_hltGlbTrkMuonTracksAssociated_parentVz, &b_tpTo_hltGlbTrkMuonTracksAssociated_parentVz);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_status", &tpTo_hltGlbTrkMuonTracksAssociated_status, &b_tpTo_hltGlbTrkMuonTracksAssociated_status);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits", &tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits, &b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfHits);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits", &tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits, &b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerHits);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers", &tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers, &b_tpTo_hltGlbTrkMuonTracksAssociated_numberOfTrackerLayers);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_gen_charge", &tpTo_hltGlbTrkMuonTracksAssociated_gen_charge, &b_tpTo_hltGlbTrkMuonTracksAssociated_gen_charge);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId", &tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId, &b_tpTo_hltGlbTrkMuonTracksAssociated_gen_pdgId);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_gen_pt", &tpTo_hltGlbTrkMuonTracksAssociated_gen_pt, &b_tpTo_hltGlbTrkMuonTracksAssociated_gen_pt);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_gen_eta", &tpTo_hltGlbTrkMuonTracksAssociated_gen_eta, &b_tpTo_hltGlbTrkMuonTracksAssociated_gen_eta);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_gen_phi", &tpTo_hltGlbTrkMuonTracksAssociated_gen_phi, &b_tpTo_hltGlbTrkMuonTracksAssociated_gen_phi);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pt);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_eta);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_phi);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_charge);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_px);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_py);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_pz);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vx);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vy);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_vz);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxy_bs);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dxyError_bs);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dz_bs);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_dzError);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_normalizedChi2);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_quality);
    // fChain->SetBranchAddress("tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits", &tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits, &b_tpTo_hltGlbTrkMuonTracksAssociated_bestMatchTrk_NValidHits);
    

    Notify();
}

Bool_t MuonHLTNtupleRun3::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TChain in a TChain or when when a new TChain
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void MuonHLTNtupleRun3::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

#endif
