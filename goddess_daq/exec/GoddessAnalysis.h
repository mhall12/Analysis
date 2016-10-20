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
	TDirectory *QQQ5_DA_PID_Cal;
	TDirectory *QQQ5_DC_PID;

	TDirectory *QQQ5_DA_Tritons;
	TDirectory *QQQ5_DC_Tritons;
	TDirectory *QQQ5_DA_dE_gated;

	TDirectory *Gammasphere_Hists;
	TDirectory *QQQ5_DA_TotalE;
	TDirectory *Gamma_Gated_Hists;
	TDirectory *Gamma_Intensity_Hists;
	TDirectory *Q_Gated_QQQ_DA_E1;
	TDirectory *Q_Gated_QQQ_DA_dE;

	TDirectory *Timing_Spectra;

	TH2D *QQQDAdE;
	TH2D *QQQDAE1;
	TH2D *QQQDAE2;
	TH2D *QQQDAE1sum;
	TH2D *QQQDAE1cal;
	TH2D *QQQDAdEcal;
	TH2D *QQQDATot;
	TH2D *QQQDATot2;
	TH2D *QQQDAQ;
	TH2D *QQQDAQAl;
	TH1D *QQQDATotQ;
	TH2D *QQQDAEx;
	TH1D *QQQDAExTot;

	TH1D *QQQDAExtotTiming;

	TH2D *QQQDCdE;
	TH2D *QQQDCE1;
	//TH1D *QQQDAtot;
	TH2D *QQQDAvsGam;

	TH2D *gam_DA;
	TH2D *gam_DC;
	
	TH1D *TimeHist;
	TH2D *gamTime;
	TH1D *gam511vtime;
	TH1D *gam511vtimeBACK;
	TH1D *gam238vtime;
	TH1D *gam238vtimeBACK;
	TH1D *gam1233vtime;
	TH1D *gam1233vtimeBACK;
	TH1D *gam1633vtime;
	TH1D *gam1633vtimeBACK;


	TH1D *QQQDAdE0;

	TH2D *gam_ind;
	TH1D *gam_tot;
	TH1D *Good_gam_tot;

	std::vector<TH1D*> gam_gated;
	std::vector<TH1D*> DA_TotE;

	int nEntries;
	
	std::vector<TH2D*> DA_PIDhists;
	std::vector<TH2D*> DA_PIDhists_Cal;
	std::vector<TH2D*> DC_PIDhists;

	std::vector<TH1D*> sT_Spec;
	std::vector<std::vector<TH1D*>> DA_T_Spec;
	std::vector<std::vector<TH1D*>> DC_T_Spec;
	
	std::vector<TH1D*> dE_gated;
	std::vector<std::vector<TH1D*>> DA_dE_Gated;
	std::vector<TH1D*> Q_gated_dE;
	std::vector<TH1D*> Q_gated_E1;
	std::vector<std::vector<TH1D*>> Q_DA_dE_Gated;

	TH1D *gam6048;
	TH1D *gam5555;
	TH1D *gam237;
	TH1D *gam272;
	TH1D *gam194;
	TH1D *gam1633;
	TH1D *gam1233;
	TH1D *gam4358;
	TH1D *gam1297;
	TH1D *gam1840;

	TH1D *int238;
	TH1D *back238;

	TH1D *int275;
	TH1D *back275;

	TH1D *int1232;
	TH1D *back1232;

	TH1D *int1840;
	TH1D *back1840;

	TH1D *int2556;
	TH1D *back2556;

	TH1D *int4140;
	TH1D *back4140;

	TH1D *int4362;
	TH1D *back4362;

	double AandEloss[20][6];

	//Calibrations for the DA E1 detector and DA dE detector are stored in these arrays.
	double calDAE1[32][2];
	double calDAdE[32][2];

	//normalization parameters for the DA E1 histograms. normDA0 is the slope and normDA1 is the intercept in m*x+b. The normalization parameters were found by matching dE-E strip combinations to the first useful looking dE-E strip combo.
	double normDA0[32][5];
	double normDA1[32][5];

	//Bounds for the Gamma coincidence gates. The first two columns are upper, lower bounds for Peak 0, etc. The peaks that don't have bounds for the higher strips are given a value of 1.0 in the txt file. 0 was not used in case some of the energies read 0. 
	double boundDA[32][8];

	//Q-Value bins for the gamma intensity histograms are initialized here.
	double Qbins[300];
	double Qgatearray[300][2];
	double buff;

	//Gammasphere quandratic calibration parameters stored here
	double gamcalparams[111][3];

	//QQQ DC Triton gates
	double TGateDCLow[22][5];
	double TGateDCHi[22][5];

	//PID Gates from calibrated energies
	double CalPIDGateLo[32][5];
	double CalPIDGateHi[32][5];

