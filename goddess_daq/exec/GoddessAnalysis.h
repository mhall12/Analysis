#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTree.h"
#include "/media/mhall12/Zeus/goddess_daq/goddess/include/GoddessStruct.h"
#include <iostream>
#include <fstream>

//Variables used in GoddessAnalysis.cxx are initialized here.	
	TTree *nt;
	TFile *data;
	TFile *hist;

	vector<GamData> *gam2;
	vector<SiData> *si2;

	TDirectory *QQQ5_DA_PID;
	TDirectory *QQQ5_DC_PID;

	TDirectory *QQQ5_DA_Tritons;
	TDirectory *QQQ5_DC_Tritons;
	TDirectory *QQQ5_DA_dE_gated;

	TDirectory *Gammasphere_Hists;
	TDirectory *QQQ5_DA_TotalE;

	TH2D *QQQDAdE;
	TH2D *QQQDAE1;
	TH2D *QQQDAE2;
	TH2D *QQQDAE1sum;
	TH2D *QQQDAE1cal;
	TH2D *QQQDATot;

	TH2D *QQQDCdE;
	TH2D *QQQDCE1;
	//TH1D *QQQDAtot;

	TH1D *QQQDAdE0;

	TH2D *gam_ind;
	TH1D *gam_tot;
	TH1D *Good_gam_tot;

	std::vector<TH1D*> gam_gated;
	std::vector<TH1D*> DA_TotE;

	int nEntries;
	
	std::vector<TH2D*> DA_PIDhists;
	std::vector<TH2D*> DC_PIDhists;

	std::vector<TH1D*> sT_Spec;
	std::vector<std::vector<TH1D*>> DA_T_Spec;
	std::vector<std::vector<TH1D*>> DC_T_Spec;
	
	std::vector<TH1D*> dE_gated;
	std::vector<std::vector<TH1D*>> DA_dE_Gated;


