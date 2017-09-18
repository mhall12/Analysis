	int ExWidth = 10; //Width of the ex bins in MeV*10.
	int gmult = 20;
	int ExLoopEnd = 72-ExWidth+1;
	int ExLoopBegin = 37;

	int BkgBins = 100;

	int GatedGams[7] = {238,275,1233,1297,1340,2556,1840};
	int DblGatedGams[9] = {2381297,2382556,2384362,2381840,2384140,2751233,2751340,2752632,25561840};

	TStopwatch t;

	TDirectory *Gams_vs_Run;
	TDirectory *Silicon_Detectors;
	TDirectory *Ex_vs_Gammas_Hists;
	TDirectory *QQQ_v_Gam;
	TDirectory *Si_v_Gam;
	TDirectory *D1_Hists;
	TDirectory *D1_Hists_Bkg1000;
	TDirectory *D1_Hists_Bkg8000;
	TDirectory *Ratio_Hists;

	TDirectory *QQQ_SingleGammaGated;
	TDirectory *QQQ_SingleGammaGated_BkgUnScale;
	TDirectory *QQQ_SingleGammaGated_Bkg;

	TDirectory *QQQ_DoubleGammaGated;
	TDirectory *QQQ_DoubleGammaGated_BkgUnScale;
	TDirectory *QQQ_DoubleGammaGated_Bkg;

	TDirectory *Si_SingleGammaGated;
	TDirectory *Si_SingleGammaGated_BkgUnScale;
	TDirectory *Si_SingleGammaGated_Bkg;

	TDirectory *Si_DoubleGammaGated;
	TDirectory *Si_DoubleGammaGated_BkgUnScale;
	TDirectory *Si_DoubleGammaGated_Bkg;

	TDirectory *TripleGammaGated;

	TDirectory *Gams_vs_Angle;


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
	TH2D *SiAll_Ex_v_Gam;

	TH2D* SiAll_Ex_v_Gam_0;
	TH2D* SiAll_Ex_v_Gam_1;
	TH2D* SiAll_Ex_v_Gam_2;
	TH2D* SiAll_Ex_v_Gam_3;
	TH2D* SiAll_Ex_v_Gam_4;

	TH2D *Ex_v_GamOffset;

	TH2D *gam238vEx;
	TH2D *gam275vEx;

	TH2D *Sigam238vEx;
	TH2D *Sigam275vEx;
	TH2D *Sigam1840vEx;

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

	std::vector<TH1D*> QQQ_SiExvGam;

	std::vector<std::vector<TH1D*>> GamGated_QQQ;

	std::vector<TH1D*> QQQ_SiExvGam_BkgUnScale;

	std::vector<std::vector<TH1D*>> GamGated_QQQ_BkgUnScale;

	std::vector<TH1D*> QQQ_SiExvGam_Bkg;

	std::vector<std::vector<TH1D*>> GamGated_QQQ_Bkg;

	std::vector<TH1D*> SiExvGam;

	std::vector<std::vector<TH1D*>> GamGated_Si;

	std::vector<TH1D*> SiExvGam_BkgUnScale;

	std::vector<std::vector<TH1D*>> GamGated_Si_BkgUnScale;

	std::vector<TH1D*> SiExvGam_Bkg;

	std::vector<std::vector<TH1D*>> GamGated_Si_Bkg;



	std::vector<TH1D*> QQQ_SiExvDblGam;

	std::vector<std::vector<TH1D*>> DblGamGated_QQQ;

	std::vector<TH1D*> QQQ_SiExvDblGam_BkgUnScale;

	std::vector<std::vector<TH1D*>> DblGamGated_QQQ_BkgUnScale;

	std::vector<TH1D*> QQQ_SiExvDblGam_Bkg;

	std::vector<std::vector<TH1D*>> DblGamGated_QQQ_Bkg;

	std::vector<TH1D*> SiExvDblGam;

	std::vector<std::vector<TH1D*>> DblGamGated_Si;

	std::vector<TH1D*> SiExvDblGam_BkgUnScale;

	std::vector<std::vector<TH1D*>> DblGamGated_Si_BkgUnScale;

	std::vector<TH1D*> SiExvDblGam_Bkg;

	std::vector<std::vector<TH1D*>> DblGamGated_Si_Bkg;

	double DCtoTotalE[32][3];

	TH2D* TimingvRunnumDA;
	TH2D* TimingvRunnumDC;
	TH2D* TimingDA2D;
	TH2D* TimingDC2D;

	TH1D* AngDistTest;
	TH1D* AngDistTest2;
	TH1D* AngDistTest_back;

	TH1D* GamTestHistback;
	TH1D* GamTestHist;

	TH1D* GMultHist;

	TH1D* g238v2556Mult;
	TH1D* g238v1840Mult;

	double GamAng[111][2];

	TH1D* g3500_theta;
	TH1D* g3500_phi;

	TH1D* g4740_theta;
	TH1D* g4740_phi;

	long int DAGam = 0;
	long int DCGam = 0;
	long int DACount = 0;
	long int DCCount = 0;
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
