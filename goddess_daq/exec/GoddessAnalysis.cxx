//Matthew Hall
//Analysis code for 19F(3He,t)19Ne performed at Argonne National Lab 9/2015.

#include "GoddessAnalysis.h"

void histfill(int runnum){
	std::cout << "Run " << runnum << " is now being analyzed." << std::endl; 	
	std::cout << "rootfiles/run" + TString(std::to_string(runnum)) + ".root" << endl;
	//the code opens the file here
	data = TFile::Open("rootfiles/run" + TString(std::to_string(runnum)) + ".root");
	//trees->cd();
	
	//the data from trees/god is placed into a container gam2 and si2.
	nt = (TTree*)data->Get("trees/god");
	gam2={};
	si2={};

	nt->SetBranchAddress("gam",&gam2);
	nt->SetBranchAddress("si",&si2);
	
	nEntries = nt->GetEntries();
	//A generic gate to use whenever I need a quick one. May be commented out much of the time.
	int gate = 0;
	int gamgate = 0;
	int Qgate = 0;
	int g6048 = 0; //Unknown
	int g5555 = 0; //Unknown
	int g237 = 0; //238 keV in 19Ne
	int g272 = 0; //275 keV in 19Ne
	int g194 = 0; //Unknown
	int g1633 = 0; //1633 keV in 20Ne
	int g1233 = 0; //1232 keV in 19Ne
	int g4358 = 0; //Possible 4362 keV peak in 19Ne
	int g1297 = 0;

	//Gates for each of the peaks in the triton spectra. Gate 0 refers to the Right most peak, Gate 0 refers to the one to the left and so on...
	int pkgate[4] = {0};

	//Tighter triton gates are defined here for each strip and implemented below. The Gates are drawn for the RAW DATA
	int multhiDA[32] = {36869,43521,53842,61624,49340,40212,71464,51217,95073,87486,56305,56484,52242,50244,60521,58477,1,76951,55477,1,74043,70876,77413,94147,81916,55746,101339,44402,1,1,1,1};
	double exphiDA[32] = {-.582,-.600,-.628,-.652,-.620,-.588,-.674,-.620,-.706,-.700,-.633,-.623,-.617,-.610,-.631,-.625,0,-.676,-.613,0,-.646,-.646,-.6525,-.692,-.6574,-.5995,-.6998,-.5656,0,0,0,0};

	int multloDA[32] = {48465,48904,67376,79593,57971,46821,90206,60449,168350,77873,66289,66867,59435,65073,63094,67867,1,85541,64814,1,61649,89429,1,117354,55882,64826,106899,60760,1,1,1,1};
	double exploDA[32] = {-.646,-.651,-.685,-.715,-.667,-.633,-.730,-.664,-.825,-.706,-.679,-.669,-.657,-.674,-.660,-.669,0,-.715,-.660,0,-.639,-.704,0,-.753,-.604,-.643,-.73,-.641,0,0,0,0};

	//normalization parameters for the DA E1 histograms. normDA0 is the slope and normDA1 is the intercept in m*x+b. The normalization parameters were found by matching dE-E strip combinations to the first useful looking dE-E strip combo.
	double normDA0[32][5] = {};
	double normDA1[32][5] = {};

	//Bounds for the Gamma coincidence gates. The first two columns are upper, lower bounds for Peak 0, etc. The peaks that don't have bounds for the higher strips are given a value of 1.0 in the txt file. 0 was not used in case some of the energies read 0. 
	double boundDA[32][8] = {};

	//Calibrations for the DA E1 detector and DA dE detector are stored in these arrays.
	double calDAE1[32][2] = {};
	double calDAdE[32][2] = {};

	//Gammasphere quandratic calibration parameters stored here
	double gamcalparams[111][3] = {};

	//strip number angle assignments.
	double stripangle[20][2];
	
	//cubic energy loss parameters through the Al blocker. In the file, Column 1: Angle in Deg, Column 2: Angle in Rad, Column 3,4,5,6 are the parameters Ax^3+Bx^2+Cx+D in that order.
	double energyloss[12][6];

	//The files for the normalization parameters and gates are opened here.
	ifstream inFile1("E1normmultDA.txt");
	ifstream inFile2("E1normaddDA.txt");
	ifstream inFile3("gates.txt");
	ifstream inFile4("E1cal.txt");
	ifstream inFile5("dEcal.txt");
	ifstream inFile6("GamCalParamsQuad.txt");
	ifstream inFile7("angleassign.txt");
	ifstream inFile8("energyloss.txt");

	//build the arrays for the gates and normalization parameters:

	for (int i=0; i<32; i++){

		inFile4 >> calDAE1[i][0] >> calDAE1[i][1];
		inFile5 >> calDAdE[i][0] >> calDAdE[i][1];
		
		for (int k = 0; k<8; k++){

			inFile3 >> boundDA[i][k];

		}

		for (int j=0; j<5; j++){

			inFile1 >> normDA0[i][j];
			inFile2 >> normDA1[i][j];
		}

		if (i<20) inFile7 >> stripangle[i][0] >> stripangle[i][1];

		if (i<12) inFile8 >> energyloss[i][0] >> energyloss[i][1] >> energyloss[i][2] >> energyloss[i][3] >> energyloss[i][4] >> energyloss[i][5];

	}

	for (int i=0; i<111; i++){

		inFile6 >> gamcalparams[i][0] >> gamcalparams[i][1] >> gamcalparams[i][2];

	}

	//close the files here
	inFile1.close();
	inFile2.close();
	inFile3.close();
	inFile4.close();
	inFile5.close();
	inFile6.close();
	inFile7.close();
	inFile8.close();

	//E1 norm is defined below. It is the E1 energy multiplied by the normalization that makes all of the E1 energies lie on top of each other for all of the dE,E1 combos.
	double E1norm;
	//E1cal is the calibrated E1 energy (strips 0 through 19)
	double E1cal;
	//dEcal is the calibrated dE energy (strips 0 through 19)
	double dEcal;
	//Total Calibrated energy.
	double Ecaltot;
	//Einit is the initial triton Energy from the reaction
	double Einit;

	int angle;

	double PIDGateHi;
	double PIDGateLo;

	double gamEn;

	int Match;

	int BadGams[19] = {7,21,26,27,28,31,35,39,47,48,50,56,62,63,68,87,98,105,110};

	double m3H = 3.016049;
	double m3He = 3.016029;
	double m19Ne = 19.001880;

	//Q-value of the reaction
	double Q;

	//fill the parameters from the two text files located in exec called E1normmult.txt and E1normadd.txt

	for (int evt=0;evt<nEntries;evt++){
		//Reset the gates to 0 for each entry of the tree.
		gate = 0;
		gamgate = 0;
		Qgate = 0;
		g6048 = 0; //Unknown
		g5555 = 0; //Unknown
		g237 = 0; //238 keV in 19Ne
		g272 = 0; //275 keV in 19Ne
		g194 = 0; //Unknown
		g1633 = 0; //1633 keV in 20Ne
		g1233 = 0; //1232 keV in 19Ne
		g4358 = 0;
		g1297 = 0;
			
		for (int g = 0; g<4; g++) pkgate[g] = 0;

		nt->GetEntry(evt);
		if(evt % 100000 == 0) cout << "Run " << runnum << ": Processing event number "<<evt << " of " << nEntries << endl;

		//We'll use the for loop here to draw gamma gates.
		for (int i = 0; i < gam2->size();i++){
			//if (gam2->at(i).en*.81 > 236 && gam2->at(i).en*.81 < 242) gamgate++;
			gamEn = pow(gam2->at(i).en,2)*gamcalparams[gam2->at(i).num][0] + gam2->at(i).en*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 

			if (gamEn >= 6039 && gamEn <= 6060) g6048++;
			if (gamEn >= 5546 && gamEn <= 5566) g5555++;
			if (gamEn >= 234 && gamEn <= 238) g237++;
			if (gamEn >= 271 && gamEn <= 275) g272++;
			if (gamEn >= 192 && gamEn <= 197) g194++;
			if (gamEn >= 1630 && gamEn <= 1638) g1633++;
			if (gamEn >= 1231 && gamEn <= 1239) g1233++;
			if (gamEn >= 4331 && gamEn <= 4373) g4358++;
			if (gamEn >= 1276 && gamEn <= 1314) g1297++;
		}

		//Fill the Si histograms here:
		for(int i = 0; i < si2->size();i++){

			//rstrip is the difference between the E1 strip number and the dE strip number
			int rstrip = si2->at(i).PstripE1-si2->at(i).PstripdE;			

			//if (si2->at(i).E1 < 620 && si2->at(i).E1 > 577 && si2->at(i).PstripE1 == 1) gate++;
			if (si2->at(i).sectorStr == "DA"){

				//Variables for the high and low triton PID gates for use in the below if statement are defined here.
				PIDGateHi = multhiDA[si2->at(i).PstripdE]*pow(si2->at(i).E1,exphiDA[si2->at(i).PstripdE]);
				PIDGateLo = multloDA[si2->at(i).PstripdE]*pow(si2->at(i).E1,exploDA[si2->at(i).PstripdE]);

				//Here we take only the events within the restricted gates.
				if (si2->at(i).dE < PIDGateHi && si2->at(i).dE > PIDGateLo){

					//DA_PIDhists is the gated triton PIDs. 
					DA_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(i).E1,si2->at(i).dE);
					//These 3 histograms are the energy vs strip number histograms.
					if (si2->at(i).dE != 0) QQQDAdE->Fill(si2->at(i).dE,si2->at(i).PstripdE);
					if (si2->at(i).E1 != 0) QQQDAE1->Fill(si2->at(i).E1,si2->at(i).PstripE1);
					if (si2->at(i).E2 != 0) QQQDAE2->Fill(si2->at(i).E2,si2->at(i).PstripE2);

					//The following histogram was to gate on the gamma lines and try to see what tritons were in coincidence. It didn't work because there were too few counts.
					//if (si2->at(i).PstripdE == 0 && (si2->at(i).PstripE1 == 0 || si2->at(i).PstripE1 == 1) && gamgate>0) QQQDAdE0->Fill(si2->at(i).E1);

					//Now we only consider the events that have strip(E1)-strip(dE) between 0 and 4. 
					if (rstrip >= 0 && rstrip <= 4){
						
						//This vector puts the E1 energy spectra for each strip(dE) into individual histograms. They are stored in the DA_Triton_Spectra folder.
						DA_T_Spec[si2->at(i).PstripdE][rstrip]->Fill(si2->at(i).E1);	
						
						//normDA0 and normDA1 are the m and b to the mx+b normalization, respectively. The normalization takes the E1 histograms and adds them to the rstrip=0 histogram for each strip(dE).
						if (normDA0[si2->at(i).PstripdE][rstrip] != 0 ){

							//E1 is the normalized x (uncalibrated Energy) E1 value. They are normalized to the rstrip=0 histogram. E1 norm is the normalized E1 energy for each dE strip (i.e. dE strip 0, E strip 0, 1, 2, 3)
							E1norm = si2->at(i).E1*normDA0[si2->at(i).PstripdE][rstrip]+normDA1[si2->at(i).PstripdE][rstrip];
							//QQQDAE1sum are the summed normalized E1 histograms. 
							QQQDAE1sum->Fill(E1norm, si2->at(i).PstripdE);
							
							//E1cal is the calibrated E1 energy, assuming a linear calibration for the 3 highest E peaks. 
							E1cal = E1norm*calDAE1[si2->at(i).PstripdE][0]+calDAE1[si2->at(i).PstripdE][1];
							//QQQDAE1cal are the calibrated DAE1 histograms.
							QQQDAE1cal->Fill(E1cal, si2->at(i).PstripdE);

							//dEcal is the calibrated dE energy. 
							dEcal = calDAdE[si2->at(i).PstripdE][0]*si2->at(i).dE + calDAdE[si2->at(i).PstripdE][1];

							Ecaltot = E1cal + dEcal;
					
							//DA_TotE stores the total energy histograms in the DA_Total_E folder.
							DA_TotE[si2->at(i).PstripdE]->Fill(Ecaltot);
							//QQQDATot stores the calibrated energy in a strip # vs calibrated energy histogram. 
							QQQDATot->Fill(Ecaltot, si2->at(i).PstripdE);
							
							if (si2->at(i).PstripdE < 20){
								//QQQDATot2 stores the calibrated energy BEFORE the Al blocker in strip # vs energy.
								angle = stripangle[si2->at(i).PstripdE][1];
								Einit = pow(Ecaltot,3)*energyloss[angle-15][2]+pow(Ecaltot,2)*energyloss[angle-15][3]+Ecaltot*energyloss[angle-15][4]+energyloss[angle-15][5];

								QQQDATot2->Fill(Einit, si2->at(i).PstripdE);

								//Q-Value Spectrum, calculation of Q-value below. Assume 30MeV for beam energy. Equation 11.10 in Krane.
								Q = Einit*(1+m3H/m19Ne)-30*(1-m3He/m19Ne)-2*sqrt(m3He*m3H/pow(m19Ne,2)*Einit*30)*cos(energyloss[angle-15][1]);

								QQQDAQ->Fill(Q, si2->at(i).PstripdE);
									
								//Q-value gate
								if (Q < -10 && Q > -10.1) Qgate++;


							}//closes if strip(dE)<20 

							//The gates are set here. If the gate for each peak is greater than 0, the gamma histogram corresponding to that peak is filled later in the program.
							//There are 4 peaks that were gated on, and each peak has two bounds (hence the p<8). The for loop is incremented by 2 because the 2nd bound is used by doing p+1.
							for (int p = 0; p<8; p+=2){
		
								//if E1norm is less than the first bound and greater than the 2nd bound...
								if (E1norm < boundDA[si2->at(i).PstripdE][p] && E1norm > boundDA[si2->at(i).PstripdE][p+1]){
									//...increase the gate of that peak (0,1,2,3) by 1.
									pkgate[p/2]++;
	
									//DA_dE_Gated is the gated dE for each of the four peaks in E1. p/2 because there is 4 peaks
									DA_dE_Gated[si2->at(i).PstripdE][p/2]->Fill(si2->at(i).dE);

								} //closes the gating if statement

							} //closes the gating for loop

						} //closes the if the normalization parameter !=0 if statement.

					} //closes the rstrip condition if statement

				} //closes the restricted gates if statement

			} //closes the DA if statement

			if (si2->at(i).sectorStr == "DC"){
				DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(i).E1,si2->at(i).dE);
				if (si2->at(i).dE != 0) QQQDCdE->Fill(si2->at(i).dE,si2->at(i).PstripdE);
				if (si2->at(i).E1 != 0) QQQDCE1->Fill(si2->at(i).E1,si2->at(i).PstripE1);
				
				if (rstrip >= 0 && rstrip <= 4) DC_T_Spec[si2->at(i).PstripdE][rstrip]->Fill(si2->at(i).E1);

			}

		}
		for (int i = 0; i < gam2->size();i++){

			gamEn = pow(gam2->at(i).en,2)*gamcalparams[gam2->at(i).num][0] + gam2->at(i).en*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 

			if (gamEn != 0){
				gam_ind->Fill(gamEn,gam2->at(i).num); //Gamma histogram filled by energy and detector number
				//gam_cal->Fill(gam2->at(i).en,gam2->at(i).num);

				gam_tot->Fill(gamEn);

				//Fill the gated gammasphere histograms here:
				for (int z=0; z<4; z++){
					if (pkgate[z] > 0) gam_gated[z]->Fill(gamEn);

				}

				if (Qgate > 0){
					gam_gated[4]->Fill(gamEn);
					if (gamEn > 1835 && gamEn < 1847) sum1840+=1;
				}

				Match = 0;
				for (int k=0; k<19; k++){
					if (gam2->at(i).num == BadGams[k]) Match+=1;
				}

				if (Match == 0) Good_gam_tot->Fill(gamEn);

				if (g6048 > 0) gam6048->Fill(gamEn);
				if (g5555 > 0) gam5555->Fill(gamEn);
				if (g237 > 0) gam237->Fill(gamEn);
				if (g272 > 0) gam272->Fill(gamEn);
				if (g194 > 0) gam194->Fill(gamEn);
				if (g1633 > 0) gam1633->Fill(gamEn);
				if (g1233 > 0) gam1233->Fill(gamEn);
				if (g4358 > 0) gam4358->Fill(gamEn);
				if (g1297 > 0) gam1297->Fill(gamEn);
			}

		}

	}

	
	std::cout << "Run " << runnum << " will now be closed." << std::endl; 
	gam2->clear();
	si2->clear();
	data->Close();
}

//********************************************************************************************************//


void MakeMyHists(){

	sum1840=0;
	int stripnum = 32;
	//the hist file is opened here for writing
	hist = TFile::Open("TotalData.root","RECREATE");
	//directories for the PID histograms are created. Directories for the other QQQ histograms are not created because they are put in 2D histograms.
	QQQ5_DA_PID = hist->mkdir("DA_PID");
	QQQ5_DC_PID = hist->mkdir("DC_PID");
	QQQ5_DA_Tritons = hist->mkdir("DA_Triton_Spectra");
	QQQ5_DC_Tritons = hist->mkdir("DC_Triton_Spectra");
	QQQ5_DA_dE_gated = hist->mkdir("DA_dE_gated");
	Gammasphere_Hists = hist->mkdir("Gammasphere_Histograms");
	Gamma_Gated_Hists = hist->mkdir("Gamma_Gated_Histograms");
	QQQ5_DA_TotalE = hist->mkdir("DA_Total_E");

	//QQQ energy histograms are created here.
	QQQDAdE = new TH2D("QQQDAdE","QQQ5 DA dE",4096,0,4096,32,0,32);
	QQQDAE1 = new TH2D("QQQDAE1","QQQ5 DA E1",4096,0,4096,32,0,32);
	QQQDAE2 = new TH2D("QQQDAE2","QQQ5 DA E2",4096,0,4096,32,0,32);

	QQQDCdE = new TH2D("QQQDCdE","QQQ5 DC dE",5000,0,50000,32,0,32);
	QQQDCE1 = new TH2D("QQQDCE1","QQQ5 DC E1",5000,0,50000,32,0,32);

	QQQDAE1sum = new TH2D("QQQDAE1sum","QQQ5 DA E1 Summed Histograms",1024,0,1024,32,0,32);
	QQQDAE1cal = new TH2D("QQQDAE1cal","QQQ5 DA E1 Calibrated Histograms",512,0,32,32,0,32);

	QQQ5_DA_TotalE->cd();
	QQQDATot = new TH2D("QQQDATot","QQQ5 DA Total Energy",2048,0,32,32,0,32);
	QQQDATot2 = new TH2D("QQQDATot2","QQQ5 DA Total Energy Before Degradation",2048,15,32,19,0,19);
	QQQDAQ = new TH2D("QQQDAQ","Strip Number vs Reaction Q-Value Spectrum",2048,-15,0,19,0,19);

	std::string gambase = "gam_pk";

	Gammasphere_Hists->cd();
	gam_ind = new TH2D("gam_ind","Individual Gammasphere Detectors",8000,0,8000,111,0,111);
	gam_tot = new TH1D("gam_tot","Summed Gammasphere Spectrum",8000,0,8000);
	Good_gam_tot = new TH1D("Good_gam_tot","Summed Gammasphere Spectrum (Good Resolutions)",8000,0,8000);

	gam_ind->GetXaxis()->SetTitle("Channel Number");
	gam_ind->GetYaxis()->SetTitle("Gammasphere Detector Number");
	gam_ind->GetXaxis()->CenterTitle();
	gam_ind->GetYaxis()->CenterTitle();

	gam_tot->GetXaxis()->SetTitle("Energy (keV)");
	gam_tot->GetYaxis()->SetTitle("Counts");
	gam_tot->GetXaxis()->CenterTitle();
	gam_tot->GetYaxis()->CenterTitle();

	Good_gam_tot->GetXaxis()->SetTitle("Energy (keV)");
	Good_gam_tot->GetYaxis()->SetTitle("Counts");
	Good_gam_tot->GetXaxis()->CenterTitle();
	Good_gam_tot->GetYaxis()->CenterTitle();

	for (int i=0; i<5; i++){
		string namegam = gambase + std::to_string(i);
		TH1D *h = new TH1D(TString(namegam),"Gated Gammasphere Spectrum Triton Peak " + TString(std::to_string(i)),4000,0,8000);

		gam_gated.push_back(h);

		gam_gated.back()->GetXaxis()->SetTitle("Energy (keV)");
		gam_gated.back()->GetYaxis()->SetTitle("Counts");
		gam_gated.back()->GetXaxis()->CenterTitle();
		gam_gated.back()->GetYaxis()->CenterTitle();
	}
	QQQDAdE0 = new TH1D("QQQDAdE0","Summed QQQ DA dE Strip 0 gated on 6125 keV gamma peak",4096,0,4096);

	//Total summed energy from both dE and E detectors
	//QQQDAtot = new TH1D("QQQDAtot","Total Energy Strip 0",8000,0,16);
	
	//base histogram names for histogram vectors
	std::string PIDbaseDA = "pid_DA_";
	std::string PIDbaseDC = "pid_DC_";
	std::string TSpecBasedE = "triton_dE_";
	std::string TSpecBaseE = "_E_";
	std::string dEgatebase = "dE_";
	std::string baseDAtot = "E_tot_";
		
	for (int i=0; i<stripnum; i++){
		QQQ5_DA_PID->cd();
		//Creates the summed DA PID plots (with coincidences of PstripE-PstripdE <=4)
		string nameDA = PIDbaseDA + std::to_string(i);
		TH2D *h0 = new TH2D(TString(nameDA),"QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),1024,0,1024,4096,0,4096);					

		DA_PIDhists.push_back(h0);

		DA_PIDhists.back()->GetXaxis()->SetTitle("Channel Number in E1");
		DA_PIDhists.back()->GetYaxis()->SetTitle("Channel Number in dE");
		DA_PIDhists.back()->GetXaxis()->CenterTitle();
		DA_PIDhists.back()->GetYaxis()->CenterTitle();

		QQQ5_DC_PID->cd();
		//Creates the summed DC PID plots (with coincidences of PstripE-PstripdE <=4)
		string nameDC = PIDbaseDC + std::to_string(i);
		TH2D *h1 = new TH2D(TString(nameDC),"QQQ5 DC dE vs E1 Strip " + TString(std::to_string(i)),5000,0,50000,5000,0,50000);

		DC_PIDhists.push_back(h1);

		DC_PIDhists.back()->GetXaxis()->SetTitle("Channel Number in E1");
		DC_PIDhists.back()->GetYaxis()->SetTitle("Channel number in dE");
		DC_PIDhists.back()->GetXaxis()->CenterTitle();
		DC_PIDhists.back()->GetYaxis()->CenterTitle();

		QQQ5_DA_Tritons->cd();
		//Creates the individual trition energy spectrum for each DA PstripdE and PstripE combination. Therefore, the vector created will be of dimension 32x5.
		for (int j=0; j<5; j++){
			int k = i+j;

			string TnameDA = TSpecBasedE + std::to_string(i) + TSpecBaseE + std::to_string(k);
			TH1D *h2 = new TH1D(TString(TnameDA),"Triton Energy dE Strip " + TString(std::to_string(i)) + " E Strip " + TString(std::to_string(k)),4096,0,4096);
			sT_Spec.push_back(h2);

			sT_Spec.back()->GetXaxis()->SetTitle("Channel Number");
			sT_Spec.back()->GetYaxis()->SetTitle("Counts");
			sT_Spec.back()->GetXaxis()->CenterTitle();
			sT_Spec.back()->GetYaxis()->CenterTitle();
		}

		DA_T_Spec.push_back(sT_Spec);
		sT_Spec.clear();

		QQQ5_DC_Tritons->cd();
		//Creates the individual trition energy spectrum for each DC PstripdE and PstripE combination. Therefore, the vector created will be of dimension 32x5.
		for (int j=0; j<5; j++){
			int k = i+j;

			string TnameDC = TSpecBasedE + std::to_string(i) + TSpecBaseE + std::to_string(k);
			TH1D *h3 = new TH1D(TString(TnameDC),"Triton Energy dE Strip " + TString(std::to_string(i)) + " E Strip " + TString(std::to_string(k)), 5000,0,50000);
			sT_Spec.push_back(h3);

			sT_Spec.back()->GetXaxis()->SetTitle("Channel Number");
			sT_Spec.back()->GetYaxis()->SetTitle("Counts");
			sT_Spec.back()->GetXaxis()->CenterTitle();
			sT_Spec.back()->GetYaxis()->CenterTitle();

		}
		
		DC_T_Spec.push_back(sT_Spec);
		sT_Spec.clear();


		QQQ5_DA_dE_gated->cd();

		for (int j=0; j<4; j++){
			
			string dEgatename = dEgatebase + std::to_string(i) + std::to_string(j);
			TH1D *h4 = new TH1D(TString(dEgatename),"DA dE " + TString(std::to_string(i)) + " gated on peak " + TString(std::to_string(j)),4096,0,4096);
			dE_gated.push_back(h4);

		}

		DA_dE_Gated.push_back(dE_gated);
		dE_gated.clear();

		QQQ5_DA_TotalE->cd();

		string nametotDA = baseDAtot + std::to_string(i);
		TH1D *h5 = new TH1D(TString(nametotDA),"QQQ5 DA Total Energy Strip " + TString(std::to_string(i)),512,0,32);					

		DA_TotE.push_back(h5);
		DA_TotE.back()->GetXaxis()->SetTitle("Energy (MeV)");
		DA_TotE.back()->GetYaxis()->SetTitle("Counts");
		DA_TotE.back()->GetXaxis()->CenterTitle();
		DA_TotE.back()->GetYaxis()->CenterTitle();
		

		
	}

	Gamma_Gated_Hists->cd();
	gam6048 = new TH1D("gam6048","Gammas Gated on 6048 keV Peak",8000,0,8000);
	gam5555 = new TH1D("gam5555","Gammas Gated on 5555 keV Peak",8000,0,8000);
	gam237 = new TH1D("gam237","Gammas Gated on 237 keV Peak",8000,0,8000);
	gam272 = new TH1D("gam272","Gammas Gated on 272 keV Peak",8000,0,8000);
	gam194 = new TH1D("gam194","Gammas Gated on 194 keV Peak",8000,0,8000);
	gam1633 = new TH1D("gam1633","Gammas Gated on 1633 keV Peak",8000,0,8000);
	gam1233 = new TH1D("gam1233","Gammas Gated on 1233 keV Peak",8000,0,8000);
	gam4358 = new TH1D("gam4358","Gammas Gated on 4358 keV Peak",8000,0,8000);
	gam1297 = new TH1D("gam1297","Gammas Gated on 1297 keV Peak",8000,0,8000);

	int numruns = 0;
	for (int run = 400; run < 495; run++){
		//Only some runs actually have data and will be made into histograms using this code.
		if ((run > 400 && run < 409 && run != 405) || (run > 409 && run < 424) || (run > 431 && run < 447) || (run > 448 && run < 455) || (run > 455 && run < 458) || (run > 459 && run < 465) || (run > 468 && run < 484) || (run > 484 && run < 495)){
			histfill(run);
			numruns++;
		}
	}
	
	
	std::cout << "The Integral of the 1840 peak is: " << sum1840 << std::endl;
	std::cout << "The number of runs analyzed was: " << numruns << std::endl;
	std::cout << "Writing data to TotalData.root" << std::endl;
	hist->Write();
	hist->Close();


}



//Old code that works and has been taken out of the program is dumped here at the end.







	//Creates the summed DA PID plots (with coincidences of PstripE-PstripdE <=4)
/*	QQQ5_DA_PID->cd();
	for (int i=0; i<stripnum; i++){
		string name = PIDbaseDA + std::to_string(i);
		TH2D *h = new TH2D(TString(name),"QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),4096,0,4096,4096,0,4096);

		name->GetXaxis()->SetTitle("Channel Number");
		name->GetYaxis()->SetTitle("Counts");
		name->GetXaxis()->CenterTitle();
		name->GetYaxis()->CenterTitle();						

		DA_PIDhists.push_back(h);
	}

*/
/*
	//Creates the summed DC PID plots (with coincidences of PstripE-PstripdE <=4)
	QQQ5_DC_PID->cd();
	for (int i=0; i<stripnum; i++){
		string name = PIDbaseDC + std::to_string(i);
		TH2D *h = new TH2D(TString(name),"QQQ5 DC dE vs E1 Strip " + TString(std::to_string(i)),5000,0,50000,5000,0,50000);
		DC_PIDhists.push_back(h);
	}

*/
/*
	//Creates the individual trition energy spectrum for each DA PstripdE and PstripE combination. Therefore, the vector created will be of dimension 32x5.
	QQQ5_DA_Tritons->cd();
	for (int i=0; i<stripnum; i++){
		for (int j=0; j<5; j++){
			int k = i+j;
			string name = TSpecBasedE + std::to_string(i) + TSpecBaseE + std::to_string(k);
				TH1D *h = new TH1D(TString(name),"Triton Energy dE Strip " + TString(std::to_string(i)) + " E Strip " + TString(std::to_string(k)), 4096,0,4096);
				sT_Spec.push_back(h);
		}
		DA_T_Spec.push_back(sT_Spec);
		sT_Spec.clear();
	}

	//Creates the individual trition energy spectrum for each DC PstripdE and PstripE combination. Therefore, the vector created will be of dimension 32x5.
	QQQ5_DC_Tritons->cd();
	for (int i=0; i<stripnum; i++){
		for (int j=0; j<5; j++){
			int k = i+j;
			string name = TSpecBasedE + std::to_string(i) + TSpecBaseE + std::to_string(k);
				TH1D *h = new TH1D(TString(name),"Triton Energy dE Strip " + TString(std::to_string(i)) + " E Strip " + TString(std::to_string(k)), 4096,0,4096);
				sT_Spec.push_back(h);
		}
		DC_T_Spec.push_back(sT_Spec);
		sT_Spec.clear();
	}






				//if (si2->at(i).PstripE1 ==1 && si2->at(i).PstripdE==0 && j==0) QQQDAtot->Fill(si2->at(i).dE*0.000529+1.23 + si2->at(i).E1*.0053+7.8547);

				//if (si2->at(i).dE < 911 && si2->at(i).PstripdE == 0 && (si2->at(i).PstripE1 == 0 || si2->at(i).PstripE1 == 1)){
				//	QQQDAdE0->Fill(si2->at(i).E1);
					
				//}

				//if (si2->at(i).E1 > 586 && si2->at(i).E1 < 612 && si2->at(i).PstripdE == 0 && (si2->at(i).PstripE1 == 0 || si2->at(i).PstripE1 == 1)) gate++;





*/

