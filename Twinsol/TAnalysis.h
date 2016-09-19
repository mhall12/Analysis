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
	std::vector<TH1D*> dE2hists;
	std::vector<TH1D*> E1hists;
	std::vector<TH1D*> GamCalHists;

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

	TH1D *dESB;

	std::vector<TH2D*> SBvdE2;
	TH2D *SBvTotE;
	TH1D *GamTot;
	TH1D *GamTotT;
	TH1D *GamTotT64;
	TH1D *GoodGamTotT64;
