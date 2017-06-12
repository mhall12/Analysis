	int ExWidth = 6; //Width of the ex bins in MeV*10.
	int ExLoopEnd = 70-ExWidth+1;

	int BkgBins = 100;


	TDirectory *Gams_vs_Run;
	TDirectory *Silicon_Detectors;
	TDirectory *Ex_vs_Gammas_Hists;
	TDirectory *QQQ5_v_Gam;
	TDirectory *Si_v_Gam;
	TDirectory *D1_Hists;
	TDirectory *D1_Hists_Bkg1000;
	TDirectory *D1_Hists_Bkg8000;
	TDirectory *Ratio_Hists;

	int gcount1;
	int gcount2;

	double SX3Renorm[28][3];
	double SX3Norm_Ang[28][4];

	double SX3Cal[23][14];

	TH2D *SX3_Gam_Gated;
	TH2D *SX3_Gated_Back;
	TH2D *SX3_Q_Gam_Gated;
	TH2D *SX3_Q_Gated_Back;

	TH2D *E_v_Ang;
	TH2D *E_v_AngBack;

	TH1D *SX3ExTot;
	TH1D *SX3Ex;
	TH1D *SX3ExBack;

	TH2D *Ex_v_Gam;
	TH2D *gam238vEx;
	TH2D *gam275vEx;

	double gamcorr[111];

	std::vector<TH2D*> GamvRunnum;

	double GamNorm31[95];
	double GamNorm87[95];

	TH2D *DAvRunCheck;

	double GamNorm[111][3];

	std::vector<TH1D*> QQQExvGam;
	std::vector<TH1D*> QQQExvGam_Bkg;
	std::vector<TH1D*> QQQExvGam_Bkg4k1000;
	std::vector<TH1D*> QQQExvGam_Bkg8k1000;
	std::vector<TH1D*> QQQExvGam_Bkg8000;
	std::vector<TH1D*> RatioVec;
/*		
	TH1D *D5_E;
	TH1D *D5_E2;
	TH1D *D5_E3;
	TH1D *D5_E4;

	TH2D *D5vPos;
	TH2D *D5vPos2;
	
	TH2D *D5vAng;
	TH2D *D5vAng2;

	TH1D *D5posZ;
	TH1D *D5posXY;


	TH1D *SX3_0;
	TH1D *SX3_1;
	TH1D *SX3_2;
	TH1D *SX3_3;
*/
