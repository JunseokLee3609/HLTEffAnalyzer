#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TF1.h>
#include <TTree.h>
#include <TTreeCache.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <TTimeStamp.h>
#include <TSystem.h>

#define DEBUG (0)
#include "PlotTools.h"

using namespace std;

void printRunTime(TStopwatch timer_)
{
  Double_t cpuTime = timer_.CpuTime();
  Double_t realTime = timer_.RealTime();

  cout << endl;
  cout << "************************************************" << endl;
  cout << "Total real time: " << realTime << " (seconds)" << endl;
  cout << "Total CPU time:  " << cpuTime << " (seconds)" << endl;
  cout << "  CPU time / real time = " << cpuTime / realTime << endl;
  cout << "************************************************" << endl;
}

void drawtnpCompEffL3wrtL1(
  // The efftag must match the L1Type in "HLTEffAnalyzer.C"
  TString efftag = "HLTOxySingleMuOpen_NotMBHF2AND", TString ver = "vRun3_01", TString SAMPLE = "Run2025", TString tag = "Muon",
  // TString efftag = "L3SingleMu12", TString ver = "vRun3_01", TString SAMPLE = "Run2023", TString tag = "Muon",
  // TString efftag2 = "L3SingleMu3_Open", TString ver2 = "vRun3_01", TString SAMPLE2 = "Run2023", TString tag2 = "Muon",
  TString L1tag = "L1SQ0", TString L1str = "L1 qual > 7, p_{T}^{L1} > 2 GeV",
  bool isLogy = false  // HERE
) {
  TStopwatch timer_total;
  timer_total.Start();

  gStyle->SetPalette(kRainBow);
  TH1::SetDefaultSumw2(kTRUE);

  TString Dir = "./plots_"+ver+"/"+tag+"/Eff_"+efftag+"/"+L1tag+"/";
  if (gSystem->mkdir(Dir,kTRUE) != -1)
    gSystem->mkdir(Dir,kTRUE);

  vector<TString> v_var = {"pt_zoom", "pt", "eta", "phi", "nvtx"};//, "pu"};
  vector< vector<double> > range = {
    {1, 0, 3},  // pt zoom
    {1, 0, 20},  // pt
    {1, -2.4, 2.4},  // eta
    {1, -TMath::Pi(), TMath::Pi()},
    {1, 1, 10}  // nvtx
    // {1, 10, 75}  // PU

  };
  if (tag == "JPsi" || tag == "Bs") {
    range.at(0) = {1, 0, 40};
    range.at(1) = {1, 0, 40};
  }

  const int n_pt_bins = 12-1;
  // double pt_bins[n_pt_bins+1] = {
  //   0,0.25,0.5,0.75, 1, 1.5, 2, 3, 
  //   4, 6, 8, 12, 16, 
  //   20
  //   /*, 22, 23, 26, 30*/
  // };
  double pt_bins[n_pt_bins+1] = {
    0,0.2,0.4,0.6,0.8, 1,1.2,1.4, 1.6,1.8, 2, 3
    /*, 22, 23, 26, 30*/
  };



  const int n_eta_bins = 22-1;
  double eta_bins[n_eta_bins+1] = {
    -2.4, -2.1, -1.9, -1.7, -1.6, 
    -1.3, -1.2, -0.9, -0.3, -0.2,  
     0.0,  0.2,  0.3,  0.9,  1.2,  
     1.3,  1.5,  1.6,  1.7,  1.9,
     2.1,  2.4
  };


  vector<TString> etas_str = {"I"};//, "BB", "BE", "EB", "EE"};
  vector<TString> etas_str_long = {"|#eta^{offline}| < 2.4"};//, "|#eta^{offline}| < 0.9", "0.9 < |#eta^{offline}| < 1.2", "1.2 < |#eta^{offline}| < 2.1", "2.1 < |#eta^{offline}| < 2.4"};

  vector<Color_t> v_color = {
    kBlack,
    kBlue,
    kRed,
    //kOrange,
    kGreen+2,
    //kCyan+2,
    //kPink+4,
    //kGray+2,
    //kMagenta,
  };
  vector<int> v_marker = {
    20,
    22,
    23,
    22,
    //25,
    //26,
    //23,
    //22,
    //26,
    //23,
    //32,
  };
  // -- input file names
  vector<TString> files = {
    // "../Analyzer/hist-v00-TEST-Eff_2023PbPb_1.4M.root",
    // "../Analyzer/hist-v00-TEST-Eff_2023PbPb_1.4M.root",
    "/home/jun502s/HLTEffAnalyzer/2024HIRun/PbPbPrep/MuonEfficiency/Analyzer/hist-v00-TEST-Eff_2025OO_Coherent.root"
  };

  vector<TString> types = {
    "Eff/"+efftag+"/num_Eff_"+L1tag+"_"+efftag+"_RunAll",
    // "Eff/"+efftag2+"/num_Eff_"+L1tag+"_"+efftag2+"_RunAll",
  };
  vector<TString> types_den = {
    "Eff/"+efftag+"/den_Eff_"+L1tag+"_"+efftag+"_RunAll",
    // "Eff/"+efftag2+"/den_Eff_"+L1tag+"_"+efftag2+"_RunAll",
  };
  vector<TString> types_str = {
     "2023 PbPb"+efftag,
    // "2023 PbPb L3SingleMu12",
    // "2023 PbPb L3SingleMu3_Open",
  };

  vector<TString> v_pts = {
    "genpt0",
    "genpt3",
    "genpt5",
    "genpt7",
    // "genpt8",
    // "genpt10",
    // "genpt12",
    // "genpt15",
    // "genpt53",
  };

  vector<TString> v_pts_str = {
    "p_{T}^{offline} > 0 GeV",
    "p_{T}^{offline} > 3 GeV",
    "p_{T}^{offline} > 5 GeV",
    "p_{T}^{offline} > 7 GeV",
    // "p_{T}^{offline} > 8 GeV",
    // "p_{T}^{offline} > 10 GeV",
    // "p_{T}^{offline} > 12 GeV",
    // "p_{T}^{offline} > 15 GeV",
    // "p_{T}^{offline} > 53 GeV",
  };

  for(unsigned i_eta=0; i_eta<etas_str.size(); i_eta++){
    for(int ipt=0; ipt<(int)v_pts.size(); ++ipt) {
      for(int ivar=0; ivar<(int)v_var.size(); ++ivar) {

        double xmin = range[ivar][1];
        double xmax = range[ivar][2];
        double ymin = 0.0;
        double ymax = 1.6;

	if(!v_var[ivar].Contains("pt") || v_var[ivar] == "pt_zoom") {
          ymin = 0.;//0.82;//0.5;//0.6;//0.85;
          ymax = 1.6;//1.1;//1.25;//1.2;//1.1;
        }

        TString canvasName = TString::Format("Eff_%s_%s_%s_%s_%s",
                                             efftag.Data(),
                                             L1tag.Data(),
                                             etas_str.at(i_eta).Data(),
                                             v_pts[ipt].Data(),
                                             v_var[ivar].Data());
        canvasName.ReplaceAll(".","p").ReplaceAll("-","_").ReplaceAll("my", "");
        TCanvas *c;
        SetCanvas_Square( c, canvasName, kFALSE, kFALSE, 900, 900 );
        c->cd();
        if(isLogy) c->SetLogy();
        if(tag == "Zprime" && v_var[ivar].Contains("pt")) c->SetLogx();

        TLegend *legend;
        SetLegend( legend, 0.17, 0.69, 0.94, 0.82, -1);

        bool isFirst = true;
        for(int i = 0; i<(int)files.size(); ++i) {
          TString fileName = files.at(i);
          cout << "fileName: "<< fileName << endl;

          TString the_type_num = types[i];
          TString the_type_den = types_den[i];
          TString the_type_str = types_str[i].ReplaceAll("my","");
          //cout<<the_type_num<<", " <<the_type_den<<endl;

          TString hist_var = v_var[ivar];
          hist_var.ReplaceAll("_zoom", "");

          TString titleX = GetTitleX(hist_var+"_reco");
          TString titleY = "HLT efficiency"; //"L3/L1 efficiency";
          if(efftag.Contains("L2Muon")) titleY.ReplaceAll("L3", "L2");
          if(efftag.Contains("PixelTracks")) titleY.ReplaceAll("L3", "PixelTrack");

          TString den_name = TString::Format("%s_%s_%s_%s", the_type_den.Data(), etas_str.at(i_eta).Data(), v_pts[ipt].Data(), hist_var.Data());
          TString num_name = TString::Format("%s_%s_%s_%s", the_type_num.Data(), etas_str.at(i_eta).Data(), v_pts[ipt].Data(), hist_var.Data());

          cout << "den_name: " << den_name << endl;
          cout << "num_name: " << num_name << endl;

          TH1F* den = Get_Hist( fileName, den_name );
          TH1F* num = Get_Hist( fileName, num_name );

          int nbins0 = den->GetNbinsX();
          // cout << nbins0<< endl;

          // if(v_var[ivar] == "eta") {
          //   for(int ip=1; ip<=nbins0; ++ip) {
          //     cout << "ip, den: " << ip << ", "<< den -> GetBinContent(ip) << endl;
          //     cout << "ip, num: " << ip << ", " << num -> GetBinContent(ip) << endl;
          //   }
          // }
          // if(v_var[ivar] == "phi") {
          //   for(int ip=1; ip<=nbins0; ++ip) {
          //     cout << "ip, den: " << ip << ", "<< den -> GetBinContent(ip) << endl;
          //     cout << "ip, num: " << ip << ", " << num -> GetBinContent(ip) << endl;
          //   }
          // }

          if(v_var[ivar].Contains("pt")) {
            den = (TH1F*)den->Rebin(n_pt_bins, den_name+"_rb", pt_bins);
            num = (TH1F*)num->Rebin(n_pt_bins, num_name+"_rb", pt_bins);
            // for(int ip=1; ip<=nbins0; ++ip) {
            //   cout << "ip, den: " << ip << ", "<< den -> GetBinContent(ip) << endl;
            //   cout << "ip, num: " << ip << ", " << num -> GetBinContent(ip) << endl;
            // }
          }
          else if(v_var[ivar] == "eta") {
            den = (TH1F*)den->Rebin(n_eta_bins, den_name+"_rb", eta_bins);
            num = (TH1F*)num->Rebin(n_eta_bins, num_name+"_rb", eta_bins);
          }
          else{
            den = (TH1F*)den->Rebin(range[ivar][0]);
            num = (TH1F*)num->Rebin(range[ivar][0]);
          }

          int nbins = den->GetNbinsX();

          // if(v_var[ivar] == "eta") {
            // for(int ip=0; ip<nbins; ++ip) {
            //   cout << "ip, den: " << ip << ", "<< den -> GetBinContent(ip+1) << endl;
            //   cout << "ip, num: " << ip << ", " << num -> GetBinContent(ip+1) << endl;
            // }
          // }

          c->cd();

          TGraphAsymmErrors* g = new TGraphAsymmErrors(nbins);
          g->Divide(num, den, "n e0");
          //g->Divide(num, den, "pois");

          for(int ip=0; ip<nbins; ++ip) {
            if(g->GetPointY(ip) == 0.)  g->SetPointEYhigh(ip, 0.0);
          }

          g->SetTitle("");
          g->SetMarkerSize(1.5);
          g->SetMarkerStyle(v_marker[i]);
          g->SetMarkerColor(v_color[i]);
          g->SetLineColor(  v_color[i]);
          g->SetLineWidth(1);

          g->GetXaxis()->SetLimits( xmin, xmax );
          g->GetXaxis()->SetRangeUser( xmin, xmax );
          g->GetYaxis()->SetRangeUser( ymin, ymax );

          SetAxis_SinglePad( g->GetXaxis(), g->GetYaxis(), titleX, titleY );

          if(isFirst) {
            g->Draw("APE");
            isFirst = false;
          }
          else {
            g->Draw("PE same");
          }

          legend->AddEntry( g, TString::Format("%s", the_type_str.Data()), "lep" );
        }

        legend->Draw();

        TString L3str = "";
        if(efftag == "L2Muon") L3str = "L2 Muon";
        else if(efftag == "hltOI") L3str = "Outside-in L3 MuonTrack";
        else if(efftag == "hltPixelTracksInRegionL2") L3str = "PixelTrack near L2";
        else if(efftag == "hltPixelTracksInRegionL1") L3str = "PixelTrack near L1";
        else if(efftag == "hltPixelTracks") L3str = "PixelTrack";
        else if(efftag == "hltIter0FromL1") L3str = "Inside-out L3 MuonTrack from L1";
        else if(efftag == "hltL3FromL2Merged") L3str = "L3 MuonTrack from L2";
        else if(efftag == "hltL3Merged") L3str = "L3 MuonTrack";
        else if(efftag.Contains("hltIterL3MuonNoID")) L3str = "L3 Muon before Trigger ID";
        else if(efftag == "hltIterL3Muon") L3str = "L3 Muon after Trigger ID";
        else if(efftag.Contains("myDoubleMu0")) L3str = "L1 Double Mu0"; 
        else if(efftag.Contains("L3SingleMu3_Open")) L3str = "";         
        else if(efftag.Contains("L3SingleMu12")) L3str = ""; 

        TLatex latex;
	      // Latex_Preliminary_13p6TeV( latex );
        Latex_Preliminary_5p36TeV( latex );
        latex.DrawLatexNDC( 0.45,0.96, "#scale[0.8]{#font[42]{"+SAMPLE+"}}");
        latex.DrawLatexNDC(0.16, 0.90, "#font[42]{#scale[0.6]{"+L3str+"}}");
        latex.DrawLatexNDC(0.16, 0.85, "#font[42]{#scale[0.6]{"+L1str+"}}");
        latex.DrawLatexNDC((i_eta==2?0.66:0.70), 0.89, "#font[42]{#scale[0.8]{"+etas_str_long.at(i_eta)+"}}");
        if(v_var[ivar] != "" ) latex.DrawLatexNDC(0.68, 0.84, "#font[42]{#scale[0.8]{"+v_pts_str.at(ipt)+"}}");

        TString logy_tag = isLogy ? "_log" : "";
        // CMS_lumi(c, 98, 11);
        c->Modified();  c->Update();  c->RedrawAxis();
        gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");
        //c->SaveAs(Dir+canvasName+logy_tag+".pdf","pdf");
        c->SaveAs(Dir+canvasName+logy_tag+".png","png");
        gROOT->ProcessLine( "gErrorIgnoreLevel = kPrint;");

        c->Close();
      }
    }
  }
  printRunTime(timer_total);
}
