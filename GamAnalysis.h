#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTree.h"
#include "../goddess/include/GoddessStruct.h"
#include <iostream>
#include <fstream>

//Variables used in GoddessAnalysis.cxx are initialized here.	
	TTree *nt;
	TFile *data;
	TFile *hist;
	int nEntries;
	vector<GamData> *gam2;
	vector<SiDataBase> *si2;

	TDirectory *Gamma_Hists;
	TDirectory *Gammasphere_Hists;
	TDirectory *Gamma_Gated_Hists;

	TDirectory *Timing_Spectra;

	TH2D *gam_ind;
	TH1D *gam_tot;


	TH1D *gam238;
	TH1D *gam275;
	TH1D *gam1233;
	TH1D *gam1297;
	TH1D *gam1840;

	TH1D *g64cascade;
	TH1D *g238and1297;
	TH1D *g275and1233;
	TH1D *g238and2556;
	TH1D *g238and1340;
	TH1D *g2556and1840;
	TH1D *g238and2556and1584;

	TH2D *gamvgam;

	//Gammasphere quandratic calibration parameters stored here
	double gamcalparams[111][3];

	TH1D* TDiffGam238;
	TH1D* TDiffGam;

	TH1D* TDiff238vs1297;
	TH1D* TDiff275vs1233;



