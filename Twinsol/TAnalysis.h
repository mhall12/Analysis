#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTree.h"
#include <iostream>
#include <fstream>

	TTree *newtree;
	TFile *datafile;
	TFile *hist;
	
	int nEntries;

	int runmode;

	std::vector<TH1D*> RawData;
	std::vector<TH1D*> dE1hists;
	std::vector<TH1D*> dE2hists;
	std::vector<TH1D*> E1hists;
	std::vector<TH1D*> GamCalHists;

	std::vector<TH2D*> PIDres1;

	std::vector<std::vector<TH2D*>> PIDres;

	std::vector<TH1D*> TimeGatedGammas;

	double E1cal[5][2];
	double dE2cal[5][2];
	double dE1cal[5][2];
	double dESBcal[1][2];
	double GamCalParams[16][2];

	TDirectory *Clovers;
	TDirectory *Si_Detectors;
	TDirectory *Single_Channel_Histograms;
	TDirectory *Raw_Data;
	TDirectory *PIDs;
	TDirectory *Single_Gamma_Dets;
	TDirectory *Timing_Histograms;

	TH1D *dESB;

	std::vector<TH2D*> SBvdE2;
	TH2D *SBvTotE;
	TH1D *GamTot;
	TH1D *GamTotT;
	TH1D *GamTotT64;
	TH1D *GoodGamTotT64;
	TH1D *TimeDiff;

	TH2D *Gamma35vsTime;

	TH1D *TimeDiff1230;
	TH1D *TimeDiffback;
	TH1D *TimeDiffadd;
