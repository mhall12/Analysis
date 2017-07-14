//Matthew Hall
//Analysis code for 19F(3He,t)19Ne performed at Argonne National Lab 9/2015.

#include "MattAnalysis.h"
#include "MattAnalysis2.h"

void histfill(int runnum, ofstream &log1){
	std::cout << "Run " << runnum << " is now being analyzed." << std::endl; 	
	std::cout << "../exec/rootfiles/run" + TString(std::to_string(runnum)) + ".root" << endl;
	//the code opens the file here
	//data = TFile::Open("../exec/rootfiles/QQQ5/run" + TString(std::to_string(runnum)) + "QQQ5_SKIMMED_AGAIN.root");
	//data = TFile::Open("../exec/rootfiles/TotalFiles/run" + TString(std::to_string(runnum)) + "_SKIMMED.root");
	//data = TFile::Open("../exec/rootfiles/TotalFiles/run" + TString(std::to_string(runnum)) + "_AllData.root");
	//data = TFile::Open("/media/mhall12/ne19disk1/TotalRootFiles/run" + TString(std::to_string(runnum)) + ".root");
	//data = TFile::Open("/media/mhall12/ne19disk1/Mult1RootFiles/run" + TString(std::to_string(runnum)) + ".root");
	//data = TFile::Open("/media/mhall12/ne19disk1/TotalRootFilesWithoutSX3Crap/run" + TString(std::to_string(runnum)) + "_SX3Mult1.root");
	//data = TFile::Open("/media/mhall12/ne19disk1/TotalRootFilesWithoutSX3Crap/run" + TString(std::to_string(runnum)) + "_SX3NoHump.root");
	data = TFile::Open("/media/mhall12/ne19disk1/FinalRootFiles/run" + TString(std::to_string(runnum)) + ".root");
	//data = TFile::Open("/media/mhall12/ne19disk1/run" + TString(std::to_string(runnum)) + ".root");
	//trees->cd();

	//the data from trees/god is placed into a container gam2 and si2.
	//nt = (TTree*)data->Get("trees/god");
	nt = (TTree*)data->Get("god");
	gam2={};
	si2={};

	nt->SetBranchAddress("gam",&gam2);
	nt->SetBranchAddress("si",&si2);
	
	nEntries = nt->GetEntries();
	//A generic gate to use whenever I need a quick one. May be commented out much of the time.
	int gate = 0;
	int gamgate = 0;
	int Qgate = 0;
	int Exgate = 0;

	int g238 = 0; //238 keV in 19Ne
	int g238_back = 0;
	int g275 = 0; //275 keV in 19Ne
	int g275_back = 0;
	int g1233 = 0; //1232 keV in 19Ne
	int g1297 = 0;
	int g1340 = 0;
	int g1840 = 0;
	int g2556 = 0;
	int g4362 = 0;
	int g4140 = 0;
	int g2632 = 0;

	int g197 = 0; //19F
	int g109 = 0; //19F
	int g890 = 0; //22Na

	int timegate = 0;

	//Gates for each of the peaks in the triton spectra. Gate 0 refers to the Right most peak, Gate 0 refers to the one to the left and so on...
	int pkgate[4] = {0};

	int DCgate = 0;

int DCtestgate1 = 0;
int DCtestgate2 = 0;

	//Tighter triton gates are defined here for each strip and implemented below. The Gates are drawn for the RAW DATA
	int multhiDA[32] = {36869,43521,53842,61624,49340,40212,71464,51217,95073,87486,56305,56484,52242,50244,60521,58477,1,76951,55477,1,74043,70876,77413,94147,81916,55746,101339,44402,1,1,1,1};
	double exphiDA[32] = {-.582,-.600,-.628,-.652,-.620,-.588,-.674,-.620,-.706,-.700,-.633,-.623,-.617,-.610,-.631,-.625,0,-.676,-.613,0,-.646,-.646,-.6525,-.692,-.6574,-.5995,-.6998,-.5656,0,0,0,0};

	int multloDA[32] = {48465,48904,67376,79593,57971,46821,90206,60449,168350,77873,66289,66867,59435,65073,63094,67867,1,85541,64814,1,61649,89429,1,117354,55882,64826,106899,60760,1,1,1,1};
	double exploDA[32] = {-.646,-.651,-.685,-.715,-.667,-.633,-.730,-.664,-.825,-.706,-.679,-.669,-.657,-.674,-.660,-.669,0,-.715,-.660,0,-.639,-.704,0,-.753,-.604,-.643,-.73,-.641,0,0,0,0};


	//Q-value gates here
	double Qgatelo[5] = {-3.43, -4.78, -6.146, -7.64, -8.1};
	double Qgatehi[5] = {-3.23, -4.58, -5.946, -7.44, -7.795};


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

	double dE;
	double E1;
	double E2;
	
	double ndE;

	double E1N;

	int stripdE;
	int stripE1;
	int stripE2;

	int stripE1N;

	double positionZ;
	double positionS;
	double positionX;
	double positionY;

	int detID = 0;

	double angle;

	double PIDGateHi;
	double PIDGateLo;
	double PIDGateHiCal;
	double PIDGateLoCal;

	int sec = -1;

	double gamEn;

	int Match;

	int BadGams[19] = {7,21,26,27,28,31,35,39,47,48,50,56,62,63,68,87,98,105,110};

	double m3H = 3.016049;
	double m3He = 3.016029;
	double m19Ne = 19.001880;
	double m19F = 18.998403;
	double m27Al = 26.981539;
	double m27Si = 26.986704;
	double utoMeV = 931.4941;

	//Q-value of the reaction
	double Q = 0;
	double QAl;
	double Ex19Ne = 0;

	double tritongate = 0;

	double timediff;

	std::vector<double> gam511;

	int SX3Gate = 0;

	double pi = 3.14159265;

	int ang_bin = 0;

	//In the TimeDiff vector, index 1 refers to the Gamma and index 2 refers to the Si event
	std::vector<std::vector<double>> TimeDiff;

	std::vector<double> SiTime;

	//Saves the Gamma Index number for a time that is in the time gate
	std::vector<int> TimingGammaIndex;

	std::vector<int> BackgroundTiming;


	std::vector<double> ExVec;
	std::vector<double> ExVecWithSX3;

	log1 << "Run Number: " << runnum << " Number of Entries: " << nEntries << std::endl;


	for (int evt=0;evt<nEntries;evt++){
		//Reset the gates to 0 for each entry of the tree.
		gate = 0;
		gamgate = 0;
		Qgate = 0;
		Exgate = 0;

DCtestgate1 = 0;
DCtestgate2 = 0;

		g238 = 0; //238 keV in 19Ne
		g238_back = 0;
		g275 = 0; //275 keV in 19Ne
		g275_back = 0;
		g1233 = 0; //1232 keV in 19Ne
		g1297 = 0;
		g1340 = 0;
		g1840 = 0;
		g2556 = 0;
		g4362 = 0;
		g4140 = 0;
		g2632 = 0;

		//Background Peaks!
		g197 = 0;
		g109 = 0;
		g890 = 0;
		
		timegate = 0;

		tritongate = 0;

		int ExGates[31] = {0};

		gam511.clear();

		DCgate = 0;

		SX3Gate = 0;
				
		for (int g = 0; g<4; g++) pkgate[g] = 0;

		nt->GetEntry(evt);
		if(evt % 10000 == 0){
			cout << "Run " << runnum << ": Processing event number "<< evt << " of " << nEntries << " \r";
			std::cout.flush();
		}

		//We'll use the for loop here to draw gamma gates.
/*
		for (unsigned int i = 0; i < gam2->size();i++){
			//if (gam2->at(i).en*.81 > 236 && gam2->at(i).en*.81 < 242) gamgate++;
			gamEn = pow(gam2->at(i).en,2)*gamcalparams[gam2->at(i).num][0] + gam2->at(i).en*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 

			if (gamEn >= 235 && gamEn <= 241) g238++;
				if (gamEn >= 242 && gamEn <= 248) g238_back++;
			if (gamEn >= 272 && gamEn <= 278) g275++;
				if (gamEn >= 279 && gamEn <= 285) g275_back++;
			if (gamEn >= 1224 && gamEn <= 1238) g1233++;
			if (gamEn >= 1276 && gamEn <= 1314) g1297++;
			if (gamEn >= 1836 && gamEn <= 1843) g1840++;
			if (gamEn >= 2546 && gamEn <= 2566) g2556++;
			if (gamEn >= 4320 && gamEn <= 4409) g4362++;

			if (gamEn >= 194 && gamEn <= 200) g197++;
			if (gamEn >= 106 && gamEn <= 112) g109++;
			if (gamEn >= 886 && gamEn <= 896) g890++;


		}
*/

		//Fill the Si histograms here:
		for(unsigned int i = 0; i < si2->size();i++){

			dE = si2->at(i).ESumLayer(0,false);
			E1 = si2->at(i).ESumLayer(1,false);
			E2 = si2->at(i).ESumLayer(2,false);

			ndE = si2->at(i).ESumLayer(0,true);

			stripdE = si2->at(i).StripMaxLayer(0,false);
			stripE1 = si2->at(i).StripMaxLayer(1,false);
			stripE2 = si2->at(i).StripMaxLayer(2,false);

			positionZ = si2->at(i).PosE1().Z();
			//S is the cylindrical coordinates position of the SX3 detector. It should be a constant value.
			positionS = sqrt(pow(si2->at(i).PosE1().X(),2)+pow(si2->at(i).PosE1().Y(),2));
			positionX = si2->at(i).PosE1().X();
			positionY = si2->at(i).PosE1().Y();

			detID = si2->at(i).telescopeID;

			//rstrip is the difference between the E1 strip number and the dE strip number
			int rstrip = stripE1-stripdE;			

			//c**********************************BEGIN TIMING********************************************
			for (unsigned int w = 0; w < gam2->size();w++){
				TimingGammaIndex.push_back(0);
				BackgroundTiming.push_back(0);
				double gamUncal = gam2->at(w).en;
				gamEn = pow(gamUncal,2)*gamcalparams[gam2->at(w).num][0] + gamUncal*gamcalparams[gam2->at(w).num][1] + gamcalparams[gam2->at(w).num][2]; 
				gamEn = 3.45437e-6*pow(gamEn,2)+.991322*gamEn+3.82698;
				//Further corrections to some detectors
				gamEn = pow(gamEn,2)*GamNorm[gam2->at(w).num][0] + gamEn*GamNorm[gam2->at(w).num][1] + GamNorm[gam2->at(w).num][2];
				

				if (si2->at(i).telescopeID == 1100){
					timediff = (double)gam2->at(w).time - (double)si2->at(i).TimestampMaxLayer(0,false);
					//if (timediff < 445 && timediff > 400){
					if (timediff < 432 && timediff > 412){
						TimingGammaIndex[w]++;
						timegate++;
						if (gamEn >= 235 && gamEn <= 241) g238++;
						if (gamEn >= 272 && gamEn <= 278) g275++;
						if (gamEn >= 1224 && gamEn <= 1238) g1233++;
						if (gamEn >= 1276 && gamEn <= 1314) g1297++;
						if (gamEn >= 1320 && gamEn <= 1360) g1340++;
						if (gamEn >= 1836 && gamEn <= 1843) g1840++;
						if (gamEn >= 2546 && gamEn <= 2566) g2556++;
						if (gamEn >= 4320 && gamEn <= 4409) g4362++;
						if (gamEn >= 4100 && gamEn <= 4180) g4140++;
						if (gamEn >= 2604 && gamEn <= 2660) g2632++;
					}

					if (timediff < 404 || timediff > 460) BackgroundTiming[w]++;


					TDiffDA->Fill(timediff);
					
				}

				if (si2->at(i).telescopeID == 1102){
					timediff = (double)gam2->at(w).time - (double)si2->at(i).TimestampMaxLayer(0,false);
					if (timediff < 208 && timediff > 188){
						TimingGammaIndex[w]++;
						timegate++;
						if (gamEn >= 235 && gamEn <= 241) g238++;
						if (gamEn >= 272 && gamEn <= 278) g275++;
						if (gamEn >= 1224 && gamEn <= 1238) g1233++;
						if (gamEn >= 1276 && gamEn <= 1314) g1297++;
						if (gamEn >= 1320 && gamEn <= 1360) g1340++;
						if (gamEn >= 1836 && gamEn <= 1843) g1840++;
						if (gamEn >= 2546 && gamEn <= 2566) g2556++;
						if (gamEn >= 4320 && gamEn <= 4409) g4362++;
						if (gamEn >= 4100 && gamEn <= 4180) g4140++;
						if (gamEn >= 2604 && gamEn <= 2660) g2632++;
					}

					if (timediff < 180 || timediff > 230) BackgroundTiming[w]++;

					TDiffDC->Fill(timediff);
				}
	
				if (si2->at(i).telescopeID >= 2104 && si2->at(i).telescopeID <= 2110 && si2->at(i).telescopeID != 2106){
					timediff = (double)gam2->at(w).time - (double)si2->at(i).TimestampMaxLayer(1,false);
					if (timediff < 208 && timediff > 188){
						TimingGammaIndex[w]++;

						if (gamEn >= 235 && gamEn <= 241) g238++;
						if (gamEn >= 272 && gamEn <= 278) g275++;
						if (gamEn >= 1224 && gamEn <= 1238) g1233++;
						if (gamEn >= 1276 && gamEn <= 1314) g1297++;
						if (gamEn >= 1320 && gamEn <= 1360) g1340++;
						if (gamEn >= 1836 && gamEn <= 1843) g1840++;
						if (gamEn >= 2546 && gamEn <= 2566) g2556++;
						if (gamEn >= 4320 && gamEn <= 4409) g4362++;
						if (gamEn >= 4100 && gamEn <= 4180) g4140++;
						if (gamEn >= 2604 && gamEn <= 2660) g2632++;

					}

					if (timediff < 180 || timediff > 230) BackgroundTiming[w]++;

					if (si2->at(i).MultLayer(1,false) == 1) TDiffSX3->Fill(timediff);
				}

				if (gamEn > 506 && gamEn < 514) gam511.push_back(gamEn);
				else gam511.push_back(0);


			}
			//c**********************************END TIMING********************************************


			if (si2->at(i).telescopeID == 1100 && si2->at(i).MultLayer(0,false) == 1 && si2->at(i).MultLayer(1,false) == 1){

				//E1 is the normalized x (uncalibrated Energy) E1 value. They are normalized to the rstrip=0 histogram. E1 norm is the normalized E1 energy for each dE strip (i.e. dE strip 0, E strip 0, 1, 2, 3)
				E1norm = E1*normDA0[stripdE][rstrip]+normDA1[stripdE][rstrip];

				//dEcal is the calibrated dE energy. 
				dEcal = calDAdE[stripdE][0]*dE + calDAdE[stripdE][1];

				//E1cal is the calibrated E1 energy, assuming a linear calibration for the 3 highest E peaks. 
				E1cal = E1norm*calDAE1[stripdE][0]+calDAE1[stripdE][1];

				//Variables for the high and low triton PID gates for use in the below if statement are defined here.
				PIDGateHi = multhiDA[stripdE]*pow(E1,exphiDA[stripdE]);
				PIDGateLo = multloDA[stripdE]*pow(E1,exploDA[stripdE]);

				PIDGateHiCal = pow(E1cal,4)*CalPIDGateHi[stripdE][0] + pow(E1cal,3)*CalPIDGateHi[stripdE][1] + pow(E1cal,2)*CalPIDGateHi[stripdE][2] + E1cal*CalPIDGateHi[stripdE][3] + CalPIDGateHi[stripdE][4];
				PIDGateLoCal = pow(E1cal,4)*CalPIDGateLo[stripdE][0] + pow(E1cal,3)*CalPIDGateLo[stripdE][1] + pow(E1cal,2)*CalPIDGateLo[stripdE][2] + E1cal*CalPIDGateLo[stripdE][3] + CalPIDGateLo[stripdE][4];

				//Here we take only the events within the restricted gates. Now with even more restriction!
				if (dE < PIDGateHi && dE > PIDGateLo){
				if (dEcal < PIDGateHiCal && dEcal > PIDGateLoCal){

					tritongate++;

					SiTime.push_back((double)si2->at(i).time);

					//DA_PIDhists is the gated triton PIDs. 
					DA_PIDhists[stripdE]->Fill(E1,dE);
					//These 3 histograms are the energy vs strip number histograms.
					if (dE != 0) QQQDAdE->Fill(dE,stripdE);
					if (E1 != 0) QQQDAE1->Fill(E1,stripE1);
					if (E2 != 0) QQQDAE2->Fill(E2,stripE2);

					//The following histogram was to gate on the gamma lines and try to see what tritons were in coincidence. It didn't work because there were too few counts.
					//if (stripdE == 0 && (stripE1 == 0 || stripE1 == 1) && gamgate>0) QQQDAdE0->Fill(E1);

					//Now we only consider the events that have strip(E1)-strip(dE) between 0 and 4. 
					if (rstrip >= 0 && rstrip <= 4){
						
						//This vector puts the E1 energy spectra for each strip(dE) into individual histograms. They are stored in the DA_Triton_Spectra folder.
						DA_T_Spec[stripdE][rstrip]->Fill(E1);
						if (stripdE == 0 && rstrip == 1) DAvRunCheck->Fill(E1,runnum);	
						
						//normDA0 and normDA1 are the m and b to the mx+b normalization, respectively. The normalization takes the E1 histograms and adds them to the rstrip=0 histogram for each strip(dE).
						if (normDA0[stripdE][rstrip] != 0 ){


							//QQQDAE1sum are the summed normalized E1 histograms. 
							QQQDAE1sum->Fill(E1norm, stripdE);
							

							//QQQDAE1cal are the calibrated DAE1 histograms.
							QQQDAE1cal->Fill(E1cal, stripdE);


							//QQQDAdEcal are the calibrated DAdE histograms.
							QQQDAdEcal->Fill(dEcal, stripdE);

							DA_PIDhists_Cal[stripdE]->Fill(E1cal,dEcal);

							Ecaltot = E1cal + dEcal;
					
							//DA_TotE stores the total energy histograms in the DA_Total_E folder.
							DA_TotE[stripdE]->Fill(Ecaltot);
							//QQQDATot stores the calibrated energy in a strip # vs calibrated energy histogram. 
							QQQDATot->Fill(Ecaltot, stripdE);
							
							if (stripdE < 20){
								//QQQDATot2 stores the calibrated energy BEFORE the Al blocker in strip # vs energy.
								angle = AandEloss[stripdE][0];

								Einit = pow(Ecaltot,3)*AandEloss[stripdE][2]+pow(Ecaltot,2)*AandEloss[stripdE][3]+Ecaltot*AandEloss[stripdE][4]+AandEloss[stripdE][5];

								QQQDATot2->Fill(Einit, stripdE);
								E_v_Ang->Fill(angle*180/pi, Einit);

								//Q-Value Spectrum, calculation of Q-value below. Assume 30MeV for beam energy. Equation 11.10 in Krane.
								Q = Einit*(1+m3H/m19Ne)-30*(1-m3He/m19Ne)-2*sqrt(m3He*m3H/pow(m19Ne,2)*Einit*30)*cos(angle);
								QAl = Einit*(1+m3H/m27Si)-30*(1-m3He/m27Si)-2*sqrt(m3He*m3H/pow(m27Si,2)*Einit*30)*cos(angle);

								Ex19Ne = (m3He + m19F - m3H - m19Ne)*utoMeV - Q;

								QQQDAQ->Fill(Q, stripdE);
								QQQDAQAl->Fill(QAl, stripdE);
								QQQDATotQ->Fill(Q);
					
								QQQDAEx->Fill(Ex19Ne, stripdE);
								QQQDAExTot->Fill(Ex19Ne);
									
								//Q-value gate
								if (Q < -7.2 && Q > -7.4) Qgate++;
								if (Ex19Ne > 4 && Ex19Ne < 5) Exgate++;
//c**c	
if (Ex19Ne > 3.7 && Ex19Ne < 7.5) DCtestgate2++;
								if (Ex19Ne >= 4 && Ex19Ne <= 7){
									ExVec.push_back(Ex19Ne);
									ExVecWithSX3.push_back(Ex19Ne);
								}

								//Put the for loop for the range of Ex gates here
								for (int ex = 0; ex < 31; ex++){
									if (Ex19Ne > ExGateArrLow[ex] && Ex19Ne < ExGateArrHi[ex]) ExGates[ex]++;
								}//closes ex for loop

								//Q-value gate for the intensity histograms filled here.
//								for (int bin = 0; bin < 299; bin++){
//									if (Q < Qbins[bin+1] && Q > Qbins[bin]) Qgatearray[bin][1]++;
//								}//closes the Q-bin gate
								//Qgatevec.push_back(Q);

								//Loop through the Q-value gates determined from the gamma intensity histograms and fill the Q_gated_ histograms.
								for (int g = 0; g < 5; g++){
									if (Q > Qgatelo[g] && Q < Qgatehi[g]){
										Q_gated_E1[stripdE]->Fill(E1norm);
										Q_DA_dE_Gated[stripdE][g]->Fill(dE);
									}//closes if Qgate statement
								}//closes g for loop

							}//closes if strip(dE)<20 

							//The gates are set here. If the gate for each peak is greater than 0, the gamma histogram corresponding to that peak is filled later in the program.
							//There are 4 peaks that were gated on, and each peak has two bounds (hence the p<8). The for loop is incremented by 2 because the 2nd bound is used by doing p+1.
							for (int p = 0; p<8; p+=2){
		
								//if E1norm is less than the first bound and greater than the 2nd bound...
								if (E1norm < boundDA[stripdE][p] && E1norm > boundDA[stripdE][p+1]){
									//...increase the gate of that peak (0,1,2,3) by 1.
									pkgate[p/2]++;
	
									//DA_dE_Gated is the gated dE for each of the four peaks in E1. p/2 because there is 4 peaks
									DA_dE_Gated[stripdE][p/2]->Fill(dE);

								} //closes the gating if statement

							} //closes the gating for loop

						} //closes the if the normalization parameter !=0 if statement.

					} //closes the rstrip condition if statement

					

					if (timegate > 0) QQQDAExtotTiming->Fill(Ex19Ne);

				} //closes the restricted gates if statement
				} //closes resitricted gates if statement

			} //closes the DA if statement

	//c*******************************************DC Begin******************************************************************c//
			if (si2->at(i).telescopeID == 1102 && si2->at(i).MultLayer(0,false) == 1){

				stripdE = stripdE;
				stripE1 = stripE1;
				dE = dE;

				if ((stripdE == 5 && stripE1 == 6 && E1 > 19900) || (stripdE == 8 && stripE1 == 9 && E1 > 23500)) E1 = -1;
				else E1 = E1;

//if (stripdE == 13 && (stripE1 == 15 || stripE1 == 14)) 
//if (stripdE == 17 && (stripE1 == 19 || stripE1 == 20)) DC_PIDhists[stripdE]->Fill(E1,dE);

				E1norm = pow(E1,2)*normDC0[stripdE][rstrip]+E1*normDC1[stripdE][rstrip]+normDC2[stripdE][rstrip];

				PIDGateLo = pow(E1,4)*TGateDCLow[stripdE][0] + pow(E1,3)*TGateDCLow[stripdE][1] + pow(E1,2)*TGateDCLow[stripdE][2] + E1*TGateDCLow[stripdE][3] + TGateDCLow[stripdE][4];
				PIDGateHi = pow(E1,4)*TGateDCHi[stripdE][0] + pow(E1,3)*TGateDCHi[stripdE][1] + pow(E1,2)*TGateDCHi[stripdE][2] + E1*TGateDCHi[stripdE][3] + TGateDCHi[stripdE][4];


				if (stripdE < 22 && dE > PIDGateLo && dE < PIDGateHi){
					tritongate++;
					DC_PIDhists[stripdE]->Fill(E1,dE);
					//if (stripdE == stripE1-1) DC_PIDhists[stripdE]->Fill(E1,dE);
					if (dE != 0) QQQDCdE->Fill(dE,stripdE);
					if (E1 != 0) QQQDCE1->Fill(E1,stripE1);

					//if (stripdE == 8 && stripE1 == 9 && E1norm > 18400 && E1norm < 21000) DCtestgate1++;
					//if (stripdE == 8 && stripE1 == 10 && E1 > 16531 && E1 < 18625) DCtestgate2++;
				
					if (rstrip >= 0 && rstrip <= 4){
						 DC_T_Spec[stripdE][rstrip]->Fill(E1);

						if (((E1norm > 14600 && stripdE == 1) || (stripdE == 2 && E1norm > 16000) || (stripdE == 3 && E1norm > 14500) || (stripdE == 4 && E1norm > 14500) || (stripdE == 6 && E1norm > 12000) || (stripdE >= 7) || stripdE == 5 || (stripdE == 8 && E1norm > 15000)) && E1norm != 0){
							QQQDCE1sum->Fill(E1norm,stripdE);

							if (stripdE == 6 && E1norm > 23800 && E1norm < 25000) DCgate++;

							angle = AandEloss[stripdE][0];
							Einit = pow(E1norm,2)*DCtoTotalE[stripdE][0]+E1norm*DCtoTotalE[stripdE][1]+DCtoTotalE[stripdE][2];

							Q = Einit*(1+m3H/m19Ne)-30*(1-m3He/m19Ne)-2*sqrt(m3He*m3H/pow(m19Ne,2)*Einit*30)*cos(angle);

							//Q-value gate for the intensity histograms filled here.
							for (int bin = 0; bin < 299; bin++){
								if (Q < Qbins[bin+1] && Q > Qbins[bin]) Qgatearray[bin][1]++;
							}//closes the Q-bin gate
						
							QQQDCQ->Fill(Q, stripdE);

							Ex19Ne = (m3He + m19F - m3H - m19Ne)*utoMeV - Q;

							if (Ex19Ne > 3.7 && Ex19Ne < 7.5) DCtestgate1++;

							QQQDCEx->Fill(Ex19Ne, stripdE);
							QQQDCExTot->Fill(Ex19Ne);

							if (Ex19Ne > 4 && Ex19Ne < 5) Exgate++;//DCgate++;
//c***	
							if (Ex19Ne >= 4 && Ex19Ne <= 7){
								ExVec.push_back(Ex19Ne);
								ExVecWithSX3.push_back(Ex19Ne);
							}

							//Put the for loop for the range of Ex gates here
							//Digital Excitation energy spectrum not great below 3.9 MeV...
							if (Ex19Ne > 3.9){
								for (int ex = 0; ex < 31; ex++){
									if (Ex19Ne > ExGateArrLow[ex] && Ex19Ne < ExGateArrHi[ex]) ExGates[ex]++;
								}//closes ex for loop
							}
						}

					} //closes rstrip if statement
				} //closes triton gate if statement

			} //closes DC if statement

	//c*******************************************DC End******************************************************************c//

			//Downstream barrel Si detectors for loop
			if (si2->at(i).telescopeID >= 2104 && si2->at(i).telescopeID <= 2110 && si2->at(i).telescopeID != 2106 && E1 > 300000 && si2->at(i).MultLayer(1,false) == 1){

				if (stripdE == 0 && stripE1 != 3) break;
				if ((stripdE == 1 || stripdE == 2) && (stripE1 != 3 && stripE1 != 2)) break;
				if ((stripdE == 3 || stripdE == 4) && (stripE1 != 2 && stripE1 != 1)) break;
				if (stripdE == 5 && stripE1 != 1) break;
				if ((stripdE == 6 || stripdE == 7) && stripE1 !=0) break;

				if (positionZ >=60) sec = 3;
				if (positionZ >=40 && positionZ < 60) sec = 2;
				if (positionZ >=20 && positionZ < 40) sec = 1;
				if (positionZ < 20) sec = 0;

				//Reinitialize angle to some nonsense value
				angle = -100;

				//Calculate the triton angle in the lab frame:
				if (positionS > 0) angle = atan(positionS/positionZ) * 180 / pi;
				if (angle > -10 && angle < 0) angle = 0;
				if (angle > 90 && angle < 100) angle = 90;
	
				if (angle <= 60) ang_bin = 0;
				else if (angle > 60 && angle <= 70) ang_bin = 1;
				else if (angle > 70 && angle <= 80) ang_bin = 2;
				else if (angle > 80) ang_bin = 3;

				//fix Weird jump in the data for D4 strip 2
				if (si2->at(i).telescopeID == 2107 && stripE1 == 2 && angle > 70) E1 = E1-6500;

				//Normalized E for each detector to the 0th strip
//				E1norm = E1*SX3Norm[si2->at(i).telescopeID - 2104][2*stripE1] + SX3Norm[si2->at(i).telescopeID - 2104][2*stripE1+1];
//				E1norm = pow(E1,2)*SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][0] + E1*SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][1] + SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][2];

				E1norm = E1*SX3Norm_Ang[4*si2->at(i).telescopeID-8416+ang_bin][stripE1];
//				if (detID == 2104) cout << stripE1 << " " << SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][0] << " " << SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][1] << " " <<SX3Renorm[4*si2->at(i).telescopeID-8416+stripE1][2] << endl;
//if (detID == 2104) cout << stripE1 << " " << angle << " " << ang_bin << " " << SX3Norm_Ang[4*si2->at(i).telescopeID-8416+ang_bin][stripdE] << endl;
				//double SX3Norm[4] = {1,1.021282496,1.027428233,1.05339854};

				//E1norm = E1*SX3Norm[stripE1];

//		cout << SX3Norm[i][0] << " " << SX3Norm[i][1] << " " << SX3Norm[i][2] << " " << SX3Norm[i][3] << endl;
//if (positionZ > 75){
				int calanglebin = 0;

				for (int a = 45; a < 90; a+=2){
					if (angle >= a-1 && angle < a+1) calanglebin = (int)(.5*a-22.5);
				}

				E1cal = E1norm*SX3Cal[calanglebin][2*detID-4208]+SX3Cal[calanglebin][2*detID-4208 + 1];

			//	cout << detID << " angle: " << angle << " calanglebin: " << calanglebin << " :0: " << SX3Cal[calanglebin][2*detID-4208] << " :1: " << 

				Q = E1cal*(1+m3H/m19Ne)-30*(1-m3He/m19Ne)-2*sqrt(m3He*m3H/pow(m19Ne,2)*E1cal*30)*cos(angle*pi/180);
				Ex19Ne = (m3He + m19F - m3H - m19Ne)*utoMeV - Q;

				if (Ex19Ne >= 4 && Ex19Ne <= 7){
					ExVecWithSX3.push_back(Ex19Ne);
				
				//	if (Ex19Ne < 5) Exgate++;
				}

				SX3ExTot->Fill(Ex19Ne);

				//if (Ex19Ne > 6.3 && Ex19Ne < 6.5) Exgate++;

				if (g238 > 0 || g275 > 0){
					SX3_Gam_Gated->Fill(angle,E1cal);
					SX3_Q_Gam_Gated->Fill(angle,Q);
					E_v_Ang->Fill(angle,E1cal);
					SX3Ex->Fill(Ex19Ne);
				}
				if (g238_back > 0 || g275_back > 0){
					SX3_Gated_Back->Fill(angle,E1cal);
					SX3_Q_Gated_Back->Fill(angle,Q);
					E_v_AngBack->Fill(angle,E1cal);
					SX3ExBack->Fill(Ex19Ne);
				}

				switch(si2->at(i).telescopeID) {

					case 2104:
						{
						//	D4_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D4_E_Ungated[stripE1]->Fill(E1norm,angle);
							
							D4_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D4_E_Gam_Gated->Fill(angle,E1cal);
							if (g238_back > 0 || g275_back > 0) D4_E_Gated_Back->Fill(angle,E1cal);
						}
						break;


					case 2105: 
						{
						//	D5_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D5_E_Ungated[stripE1]->Fill(E1norm,angle);

							D5_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D5_E_Gam_Gated->Fill(angle,E1cal);

							if (g238_back > 0 || g275_back > 0) D5_E_Gated_Back->Fill(angle,E1cal);

							SX3Gate++;
						}
						break;

					case 2107:
						{
						//	D7_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D7_E_Ungated[stripE1]->Fill(E1norm,angle);

							D7_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D7_E_Gam_Gated->Fill(angle,E1cal);
							if (g238_back > 0 || g275_back > 0) D7_E_Gated_Back->Fill(angle,E1cal);

						}
						break;
					case 2108:
						{
						//	D8_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D8_E_Ungated[stripE1]->Fill(E1norm,angle);

							D8_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D8_E_Gam_Gated->Fill(angle,E1cal);
							if (g238_back > 0 || g275_back > 0) D8_E_Gated_Back->Fill(angle,E1cal);
					
						}
						break;
					case 2109:
						{
						//	D9_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D9_E_Ungated[stripE1]->Fill(E1norm,angle);

							D9_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D9_E_Gam_Gated->Fill(angle,E1cal);
							if (g238_back > 0 || g275_back > 0) D9_E_Gated_Back->Fill(angle,E1cal);

						}
						break;
					case 2110:
						{
						//	D10_PID[stripdE][stripE1][sec]->Fill(E1,dE);
							D10_E_Ungated[stripE1]->Fill(E1norm,angle);

							D10_E_Sum_v_Ang->Fill(E1norm,angle);

							if (g238 > 0 || g275 > 0) D10_E_Gam_Gated->Fill(angle,E1cal);
							if (g238_back > 0 || g275_back > 0) D10_E_Gated_Back->Fill(angle,E1cal);
						}
						break;

				}//closes PID Switch

//}			

			}


		for (unsigned int f = 0; f < gam2->size();f++){
			gamEn = pow(gam2->at(f).en,2)*gamcalparams[gam2->at(f).num][0] + gam2->at(f).en*gamcalparams[gam2->at(f).num][1] + gamcalparams[gam2->at(f).num][2]; 

			if (gamEn != 0 && TimingGammaIndex[f]>0 && Ex19Ne >6.2 && Ex19Ne < 6.6) QQQDAvsGam->Fill(Ex19Ne,gamEn);
			
//			if (TimingGammaIndex[f]>0 && gamEn != 0){
//				for (int Ex = 40; Ex < 70; Ex++){

//					if (detID < 2000) Ex_v_Gam->Fill(gamEn,Ex19Ne);

//				}
//			}
		}


		}//closes silicon detectors loop



		for (unsigned int i = 0; i < gam2->size();i++){
		//if (tritongate > 0){

			double gamUncal = gam2->at(i).en;

			switch(gam2->at(i).num){
				case 31:
				    {
					gamUncal = gamUncal/GamNorm31[runnum-400];
				    }
				    break;
				case 87:
				    {
					gamUncal = gamUncal/GamNorm87[runnum-400];
				    }
				    break;
				default: gamUncal = gamUncal;
				    break;
			}

			gamEn = pow(gamUncal,2)*gamcalparams[gam2->at(i).num][0] + gamUncal*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 
			gamEn = 3.45437e-6*pow(gamEn,2)+.991322*gamEn+3.82698;
			//Further corrections to some detectors
			gamEn = pow(gamEn,2)*GamNorm[gam2->at(i).num][0] + gamEn*GamNorm[gam2->at(i).num][1] + GamNorm[gam2->at(i).num][2];
//			gamEn=gamEn*gamcorr[gam2->at(i).num];

			gam_ind->Fill(gamEn,gam2->at(i).num);

			GamvRunnum[gam2->at(i).num]->Fill(gamUncal,runnum);
//Background timing if statement
			if (gamEn >20 && BackgroundTiming[i]>0){
				gam_totBack->Fill(gamEn);
				if (Exgate > 0) gamExBack->Fill(gamEn);

				//gam_totBack2->Fill(gamEn);
				//if (Exgate > 0) gamExBack2->Fill(gamEn);

				//fill the Bkg histograms 
				for (unsigned int v = 0; v < ExVec.size(); v++){
					for (int ex = 40; ex < ExLoopEnd; ex++){
						int ele = ex-40;

						if (ExVec[v] >= (double)ex/10 && ExVec[v] < (double)ex/10+(double)ExWidth/10){
							QQQExvGam_Bkg[ele]->Fill(gamEn);


						}

					}
				}
			}
//Regular timing if statement			
			//c******Gamma histograms filled below here are suppressed by the time gate with the Si detectors*******
			if (gamEn >20  && TimingGammaIndex[i]>0){// timegate > 0){//

				for (unsigned int j = 0; j < gam2->size();j++){
					if (gamEn > 3000 && gam511[j] > 0 && TimingGammaIndex[j] > 0){
						gamEn += gam511[j];
						//std::cout << "woah!" << std::endl;
					}
				}
				if (g197 == 0 && g109 == 0) gam_tot->Fill(gamEn);
				if (g197 == 0 && g109 == 0) gam_tot2->Fill(gamEn);
				//Fill the gated gammasphere histograms here:
				for (int z=0; z<4; z++){
					if (pkgate[z] > 0) gam_gated[z]->Fill(gamEn);

				}
				for (int ex = 0; ex < 31; ex++){
					if (ExGates[ex] > 0) ExGatedGams[ex]->Fill(gamEn);
				}

				if (Qgate > 0){
					gam_gated[4]->Fill(gamEn);
				}
				//if (Exgate > 0){
				if (DCtestgate1 > 0){
					gam_gated[5]->Fill(gamEn);
					if (gamEn > 1825 && gamEn < 1830) gcount1++;
					if (gamEn > 1842 && gamEn < 1845) gcount2++;

					gamExGated->Fill(gamEn);
					gamExGated2->Fill(gamEn);
				}

				//if (DCgate > 0){
				if (DCtestgate2 > 0){
					gam_gated[6]->Fill(gamEn);
				}

				for (int q = 0; q < 300; q++){
					if (Qgatearray[q][1]>0){

						if (gamEn > 234 && gamEn < 239) int238->Fill(Qgatearray[q][0]);
						if (gamEn > 241 && gamEn < 246) back238->Fill(Qgatearray[q][0]);

						if (gamEn > 270 && gamEn < 276) int275->Fill(Qgatearray[q][0]);
						if (gamEn > 260 && gamEn < 266) back275->Fill(Qgatearray[q][0]);

						if (gamEn > 1224 && gamEn < 1240) int1232->Fill(Qgatearray[q][0]);
						if (gamEn > 1196 && gamEn < 1212) back1232->Fill(Qgatearray[q][0]);

						if (gamEn > 1835 && gamEn < 1847) int1840->Fill(Qgatearray[q][0]);
						if (gamEn > 1823 && gamEn < 1835) back1840->Fill(Qgatearray[q][0]);

						if (gamEn > 2526 && gamEn < 2576) int2556->Fill(Qgatearray[q][0]);
						if (gamEn > 2584 && gamEn < 2634) back2556->Fill(Qgatearray[q][0]);

						if (gamEn > 4138 && gamEn < 4148) int4140->Fill(Qgatearray[q][0]);
						if (gamEn > 4128 && gamEn < 4138) back4140->Fill(Qgatearray[q][0]);

						if (gamEn > 4294 && gamEn < 4376) int4362->Fill(Qgatearray[q][0]);
						if (gamEn > 4400 && gamEn < 4482) back4362->Fill(Qgatearray[q][0]);

						if (gamEn > 1850 && gamEn < 1856) int1853->Fill(Qgatearray[q][0]);
						if (gamEn > 1856 && gamEn < 1862) back1853->Fill(Qgatearray[q][0]);

						if (gamEn >= 1834 && gamEn <= 1844) int1844->Fill(Qgatearray[q][0]);
						if (gamEn >= 1848 && gamEn <= 1858) back1844->Fill(Qgatearray[q][0]);

					}
				}
					


				if (g238 > 0) gam238->Fill(gamEn);
				if (g275 > 0) gam275->Fill(gamEn);
				if (g1233 > 0) gam1233->Fill(gamEn);
				if (g1297 > 0) gam1297->Fill(gamEn);
				if (g1840 > 0) gam1840->Fill(gamEn);
				if (g2556 > 0) gam2556->Fill(gamEn);

				for (unsigned int v = 0; v < ExVec.size(); v++){

					Ex_v_Gam->Fill(gamEn,ExVec[v]);

					for (int ex = 40; ex < ExLoopEnd; ex++){
						int ele = ex-40;

						if (ExVec[v] >= (double)ex/10 && ExVec[v] < (double)ex/10+(double)ExWidth/10){

							QQQExvGam[ele]->Fill(gamEn);
							if (g238 > 0){
								GamGated_QQQ[ele][0]->Fill(gamEn);
								if (g1297 > 0) DblGamGated_QQQ[ele][0]->Fill(gamEn);
								if (g2556 > 0) DblGamGated_QQQ[ele][1]->Fill(gamEn);
								if (g4362 > 0) DblGamGated_QQQ[ele][2]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_QQQ[ele][3]->Fill(gamEn);
								if (g4140 > 0) DblGamGated_QQQ[ele][4]->Fill(gamEn);
							}

							if (g275 > 0){
								GamGated_QQQ[ele][1]->Fill(gamEn);
								if (g1233 > 0) DblGamGated_QQQ[ele][5]->Fill(gamEn);
								if (g1340 > 0) DblGamGated_QQQ[ele][6]->Fill(gamEn);
								if (g2632 > 0) DblGamGated_QQQ[ele][7]->Fill(gamEn);
							}

							if (g1233 > 0){
								GamGated_QQQ[ele][2]->Fill(gamEn);
							}

							if (g1297 > 0){
								GamGated_QQQ[ele][3]->Fill(gamEn);
							}

							if (g1340 > 0){
								GamGated_QQQ[ele][4]->Fill(gamEn);
							}

							if (g2556 > 0){
								GamGated_QQQ[ele][5]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_QQQ[ele][8]->Fill(gamEn);
							}

							if (g1840 > 0){
								GamGated_QQQ[ele][6]->Fill(gamEn);
							}


						}

					}
	
				}

				for (unsigned int v = 0; v < ExVecWithSX3.size(); v++){

					for (int ex = 40; ex < ExLoopEnd; ex++){
						int ele = ex-40;

						if (ExVecWithSX3[v] >= (double)ex/10 && ExVecWithSX3[v] < (double)ex/10+(double)ExWidth/10){

							if (g238 > 0){
								GamGated_Si[ele][0]->Fill(gamEn);
								if (g1297 > 0) DblGamGated_Si[ele][0]->Fill(gamEn);
								if (g2556 > 0) DblGamGated_Si[ele][1]->Fill(gamEn);
								if (g4362 > 0) DblGamGated_Si[ele][2]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_Si[ele][3]->Fill(gamEn);
								if (g4140 > 0) DblGamGated_Si[ele][4]->Fill(gamEn);
							}

							if (g275 > 0){
								GamGated_Si[ele][1]->Fill(gamEn);
								if (g1233 > 0) DblGamGated_Si[ele][5]->Fill(gamEn);
								if (g1340 > 0) DblGamGated_Si[ele][6]->Fill(gamEn);
								if (g2632 > 0) DblGamGated_Si[ele][7]->Fill(gamEn);
							}

							if (g1233 > 0){
								GamGated_Si[ele][2]->Fill(gamEn);
							}

							if (g1297 > 0){
								GamGated_Si[ele][3]->Fill(gamEn);
							}

							if (g1340 > 0){
								GamGated_Si[ele][4]->Fill(gamEn);
							}

							if (g2556 > 0){
								GamGated_Si[ele][5]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_Si[ele][8]->Fill(gamEn);
							}

							if (g1840 > 0){
								GamGated_Si[ele][6]->Fill(gamEn);
							}

						}

					}
	
				}
			}//Closes if GamEn and TimingGammaIndex
	
//		}//Close Triton Gate

			if (gamEn != 0 && TimingGammaIndex[i] > 0){

				for (unsigned int ex = 0; ex < ExVec.size(); ex++){//WithSX3

					if (g238 > 0) gam238vEx->Fill(gamEn,ExVec[ex]);
					if (g275 > 0 && g197 == 0 && g109 == 0 && g890 == 0) gam275vEx->Fill(gamEn,ExVec[ex]);
//if (g238 > 0 && g197 == 0 && g109 == 0 && g890 == 0)
				}

			}

			if (gamEn != 0 && BackgroundTiming[i] > 0){
					if (g238 > 0) gam238_Back->Fill(gamEn);
					if (g275 > 0) gam275_Back->Fill(gamEn);
					if (g1233 > 0) gam1233_Back->Fill(gamEn);
					if (g1297 > 0) gam1297_Back->Fill(gamEn);
					if (g1840 > 0) gam1840_Back->Fill(gamEn);
					if (g2556 > 0) gam2556_Back->Fill(gamEn);

				for (unsigned int v = 0; v < ExVec.size(); v++){

					for (int ex = 40; ex < ExLoopEnd; ex++){
						int ele = ex-40;

						if (ExVec[v] >= (double)ex/10 && ExVec[v] < (double)ex/10+(double)ExWidth/10){

							if (g238 > 0){
								GamGated_QQQ_BkgUnScale[ele][0]->Fill(gamEn);
								if (g1297 > 0) DblGamGated_QQQ_BkgUnScale[ele][0]->Fill(gamEn);
								if (g2556 > 0) DblGamGated_QQQ_BkgUnScale[ele][1]->Fill(gamEn);
								if (g4362 > 0) DblGamGated_QQQ_BkgUnScale[ele][2]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_QQQ_BkgUnScale[ele][3]->Fill(gamEn);
								if (g4140 > 0) DblGamGated_QQQ_BkgUnScale[ele][4]->Fill(gamEn);
							}

							if (g275 > 0){
								GamGated_QQQ_BkgUnScale[ele][1]->Fill(gamEn);
								if (g1233 > 0) DblGamGated_QQQ_BkgUnScale[ele][5]->Fill(gamEn);
								if (g1340 > 0) DblGamGated_QQQ_BkgUnScale[ele][6]->Fill(gamEn);
								if (g2632 > 0) DblGamGated_QQQ_BkgUnScale[ele][7]->Fill(gamEn);
							}

							if (g1233 > 0){
								GamGated_QQQ_BkgUnScale[ele][2]->Fill(gamEn);
							}

							if (g1297 > 0){
								GamGated_QQQ_BkgUnScale[ele][3]->Fill(gamEn);
							}

							if (g1340 > 0){
								GamGated_QQQ_BkgUnScale[ele][4]->Fill(gamEn);
							}

							if (g2556 > 0){
								GamGated_QQQ_BkgUnScale[ele][5]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_QQQ_BkgUnScale[ele][8]->Fill(gamEn);
							}

							if (g1840 > 0){
								GamGated_QQQ_BkgUnScale[ele][6]->Fill(gamEn);
							}

						}

					}
	
				}

				for (unsigned int v = 0; v < ExVecWithSX3.size(); v++){

					for (int ex = 40; ex < ExLoopEnd; ex++){
						int ele = ex-40;

						if (ExVecWithSX3[v] >= (double)ex/10 && ExVecWithSX3[v] < (double)ex/10+(double)ExWidth/10){

							if (g238 > 0){
								GamGated_Si_BkgUnScale[ele][0]->Fill(gamEn);
								if (g1297 > 0) DblGamGated_Si_BkgUnScale[ele][0]->Fill(gamEn);
								if (g2556 > 0) DblGamGated_Si_BkgUnScale[ele][1]->Fill(gamEn);
								if (g4362 > 0) DblGamGated_Si_BkgUnScale[ele][2]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_Si_BkgUnScale[ele][3]->Fill(gamEn);
								if (g4140 > 0) DblGamGated_Si_BkgUnScale[ele][4]->Fill(gamEn);
							}

							if (g275 > 0){
								GamGated_Si_BkgUnScale[ele][1]->Fill(gamEn);
								if (g1233 > 0) DblGamGated_Si_BkgUnScale[ele][5]->Fill(gamEn);
								if (g1340 > 0) DblGamGated_Si_BkgUnScale[ele][6]->Fill(gamEn);
								if (g2632 > 0) DblGamGated_Si_BkgUnScale[ele][7]->Fill(gamEn);
							}

							if (g1233 > 0){
								GamGated_Si_BkgUnScale[ele][2]->Fill(gamEn);
							}

							if (g1297 > 0){
								GamGated_Si_BkgUnScale[ele][3]->Fill(gamEn);
							}

							if (g1340 > 0){
								GamGated_Si_BkgUnScale[ele][4]->Fill(gamEn);
							}

							if (g2556 > 0){
								GamGated_Si_BkgUnScale[ele][5]->Fill(gamEn);
								if (g1840 > 0) DblGamGated_Si_BkgUnScale[ele][8]->Fill(gamEn);
							}

							if (g1840 > 0){
								GamGated_Si_BkgUnScale[ele][6]->Fill(gamEn);
							}

						}

					}
	
				}
			
			}
		}


		for (int c=0; c<300; c++){ Qgatearray[c][1] = 0;}
		timegate = 0;
		SiTime.clear();
		TimingGammaIndex.clear();
		BackgroundTiming.clear();
		ExVec.clear();
		ExVecWithSX3.clear();

	}



	
	
	std::cout << "Run " << runnum << " will now be closed." << std::endl; 
	gam2->clear();
	si2->clear();
	data->Close();


}

//c******************************************************************************************************c//


void MakeMyHists(){

	t.Start();

	gcount1 = 0;	
	gcount2 = 0;
	int stripnum = 32;
	//the hist file is opened here for writing
	string RootFile = "SiQQQHists.root";
	hist = TFile::Open(TString(RootFile),"RECREATE");
	std::ofstream logFile("GoddessAnalysis.log");

	//directories for the histograms are created. 
	Silicon_Detectors = hist->mkdir("Silicon_Detectors");
		Particle_IDs = hist->mkdir("Silicon_Detectors/Particle_IDs");
			QQQ5_DA_PID = hist->mkdir("Silicon_Detectors/Particle_IDs/DA_PID");
			QQQ5_DA_PID_Cal = hist->mkdir("Silicon_Detectors/Particle_IDs/DA_PID_Cal");
			QQQ5_DC_PID = hist->mkdir("Silicon_Detectors/Particle_IDs/DC_PID");
			D4_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D4_FB_PIDs");
			D5_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D5_FB_PIDs");
			D7_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D7_FB_PIDs");
			D8_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D8_FB_PIDs");
			D9_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D9_FB_PIDs");
			D10_FB_PIDs = hist->mkdir("Silicon_Detectors/Particle_IDs/D10_FB_PIDs");
		Triton_Spectra = hist->mkdir("Silicon_Detectors/Triton_Spectra");
			DA_Triton_Spectra = hist->mkdir("Silicon_Detectors/Triton_Spectra/DA_Triton_Spectra");
			DC_Triton_Spectra = hist->mkdir("Silicon_Detectors/Triton_Spectra/DC_Triton_Spectra");
		Calibration_Hists = hist->mkdir("Silicon_Detectors/Calibration_Hists");
			QQQ5_DA_dE_gated = hist->mkdir("Silicon_Detectors/Calibration_Hists/DA_dE_gated");
			Q_Gated_QQQ_DA_E1 = hist->mkdir("Silicon_Detectors/Calibration_Hists/Q_Gated_QQQ_DA_E1");
			Q_Gated_QQQ_DA_dE = hist->mkdir("Silicon_Detectors/Calibration_Hists/Q_Gated_QQQ_DA_dE");
		QQQ5_DA_TotalE = hist->mkdir("Silicon_Detectors/DA_Total_E");
		QQQ5_DC_TotalE = hist->mkdir("Silicon_Detectors/DC_Total_E");
		Strip_vs_E_Hists = hist->mkdir("Silicon_Detectors/Strip_vs_E_Hists");
		SX3_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists");
			D4_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D4_Hists");
				Energy_Ungated4 = hist->mkdir("Silicon_Detectors/SX3_Hists/D4_Hists/Energy_Ungated4");
			D5_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D5_Hists");
				Energy_Ungated5 = hist->mkdir("Silicon_Detectors/SX3_Hists/D5_Hists/Energy_Ungated5");
			D7_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D7_Hists");
				Energy_Ungated7 = hist->mkdir("Silicon_Detectors/SX3_Hists/D7_Hists/Energy_Ungated7");
			D8_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D8_Hists");
				Energy_Ungated8 = hist->mkdir("Silicon_Detectors/SX3_Hists/D8_Hists/Energy_Ungated8");
			D9_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D9_Hists");
				Energy_Ungated9 = hist->mkdir("Silicon_Detectors/SX3_Hists/D9_Hists/Energy_Ungated9");
			D10_Hists = hist->mkdir("Silicon_Detectors/SX3_Hists/D10_Hists");
				Energy_Ungated10 = hist->mkdir("Silicon_Detectors/SX3_Hists/D10_Hists/Energy_Ungated10");
			Gamma_Gated_Background = hist->mkdir("Silicon_Detectors/SX3_Hists/Gamma_Gated_Background");
			Gamma_Gated = hist->mkdir("Silicon_Detectors/SX3_Hists/Gamma_Gated");

	Gamma_Hists = hist->mkdir("Gamma_Hists");
		Gammasphere_Hists = hist->mkdir("Gamma_Hists/Gammasphere_Histograms");
		Gamma_Gated_Hists = hist->mkdir("Gamma_Hists/Gamma_Gated_Histograms");
			Background = hist->mkdir("Gamma_Hists/Gamma_Gated_Histograms/Background");
		Gamma_Intensity_Hists = hist->mkdir("Gamma_Hists/Gamma_Intensity_Histograms");
		Excitation_Energy_Gated = hist->mkdir("Gamma_Hists/Excitation_Energy_Gated");
		Triton_Gated = hist->mkdir("Gamma_Hists/Triton_Gated");
		Gams_vs_Run = hist->mkdir("Gamma_Hists/Gams_vs_Run");
	Timing_Spectra = hist->mkdir("Timing_Spectra");

	Ex_vs_Gammas_Hists = hist->mkdir("Ex_vs_Gammas_Hists");
		QQQ_v_Gam = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam");
			D1_Hists = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists");
			D1_Hists_Bkg1000 = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists_BkgUnScale");
			D1_Hists_Bkg8000 = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists_Bkg8000");
			Ratio_Hists = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/Ratio_Hists");

			QQQ_SingleGammaGated = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated");
			QQQ_SingleGammaGated_Bkg = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated_BkgUnScale");
			QQQ_SingleGammaGated_Bkg = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated_Bkg");

			QQQ_DoubleGammaGated = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated");
			QQQ_DoubleGammaGated_BkgUnScale = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated_BkgUnScale");
			QQQ_DoubleGammaGated_Bkg = hist->mkdir("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated_Bkg");

		Si_v_Gam = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam");
			Si_SingleGammaGated = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated");
			Si_SingleGammaGated_BkgUnScale = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated_BkgUnScale");
			Si_SingleGammaGated_Bkg = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated_Bkg");

			Si_DoubleGammaGated = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated");
			Si_DoubleGammaGated_BkgUnScale = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated_BkgUnScale");
			Si_DoubleGammaGated_Bkg = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated_Bkg");

			TripleGammaGated = hist->mkdir("Ex_vs_Gammas_Hists/Si_v_Gam/TripleGammaGated");

	hist->cd("Silicon_Detectors");
		E_v_Ang = new TH2D("E_v_Ang","Angle vs Triton Energy",60,0,90,1000,0,30);
		E_v_AngBack = new TH2D("E_v_AngBack","Angle vs Triton Energy Background",60,0,90,1000,0,30);

		DAvRunCheck = new TH2D("DAvRunCheck","Run Number vs E1 Energy",4096,0,4096,100,400,500);

	hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam");
		Ex_v_Gam = new TH2D("Ex_v_Gam","Ex vs Gamma Energy for QQQ Detectors",8000,0,8000,30,4,7);
	for (int i = 40; i < ExLoopEnd; i++){ //66 because we are doing .5 MeV bin widths for the Si detectors, the last bin then gives 6.5-7.
		hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists");
		int Ex_BinLow = i;
		//double Ex_BinHi = (double)i/10+(double)ExWidth/10;
		int Ex_BinHi = i+ExWidth;

		std::cout << Ex_BinLow << "****************" << endl;

		TH1D *h16 = new TH1D("Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)),"Excitation Energy Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)),8000,0,8000);

		QQQExvGam.push_back(h16);

		hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists_BkgUnScale");
		
		TH1D *h17 = new TH1D("Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_UnScale","Ex " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)),8000,0,8000);
		QQQExvGam_Bkg.push_back(h17);
//		QQQExvGam_Bkg4k1000.push_back(h17);
//		QQQExvGam_Bkg8k1000.push_back(h18);

		//Add and scale the above hists FIRST before you set the bin content of 8000 bin histogram. 

		hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists_Bkg8000");

		TH1D *h19 = new TH1D("Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "Bkg8k","Ex " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " Background",8000,0,8000);

		QQQExvGam_Bkg8000.push_back(h19);


		
		for (int g = 0; g < 7; g++){

			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated");
			TH1D *h20 = new TH1D("Si_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)),"Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(GatedGams[g])) + " keV Gamma", 8000,0,8000);

			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated_BkgUnScale");
			TH1D *h21 = new TH1D("Si_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_UnScale","Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(GatedGams[g])) + " keV Gamma", 8000,0,8000);
			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated_Bkg");
			TH1D *h22 = new TH1D("Si_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_Bkg","Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(GatedGams[g])) + " keV Gamma", 8000,0,8000);

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated");
			TH1D *h23 = (TH1D*)h20->Clone("QQQ_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)));

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated_BkgUnScale");
			TH1D *h24 = (TH1D*)h21->Clone("QQQ_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_UnScale");

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_SingleGammaGated_Bkg");
			TH1D *h25 = (TH1D*)h22->Clone("QQQ_Gam" + TString(std::to_string(GatedGams[g])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_Bkg");

			SiExvGam.push_back(h20);
			SiExvGam_BkgUnScale.push_back(h21);
			SiExvGam_Bkg.push_back(h22);
			QQQ_SiExvGam.push_back(h23);
			QQQ_SiExvGam_BkgUnScale.push_back(h24);
			QQQ_SiExvGam_Bkg.push_back(h25);
		
		}
	
		GamGated_QQQ.push_back(QQQ_SiExvGam);
		GamGated_QQQ_BkgUnScale.push_back(QQQ_SiExvGam_BkgUnScale);
		GamGated_QQQ_Bkg.push_back(QQQ_SiExvGam_Bkg);
		GamGated_Si.push_back(SiExvGam);
		GamGated_Si_BkgUnScale.push_back(SiExvGam_BkgUnScale);
		GamGated_Si_Bkg.push_back(SiExvGam_Bkg);

		for (int dg = 0; dg < 9; dg++){
			
			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated");
			TH1D *h26 = new TH1D("Si_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)),"Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(DblGatedGams[dg])) + " keV Gamma", 8000,0,8000);

			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated_BkgUnScale");
			TH1D *h27 = new TH1D("Si_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_UnScale","Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(DblGatedGams[dg])) + " keV Gamma", 8000,0,8000);
			hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_DoubleGammaGated_Bkg");
			TH1D *h28 = new TH1D("Si_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_Bkg","Ex Gated from " + TString(std::to_string(Ex_BinLow)) + " to " + TString(std::to_string(Ex_BinHi)) + " & Gated on " + TString(std::to_string(DblGatedGams[dg])) + " keV Gamma", 8000,0,8000);

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated");
			TH1D *h29 = (TH1D*)h26->Clone("QQQ_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)));

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated_BkgUnScale");
			TH1D *h30 = (TH1D*)h27->Clone("QQQ_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_UnScale");

			hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/QQQ_DoubleGammaGated_Bkg");
			TH1D *h31 = (TH1D*)h28->Clone("QQQ_Gam" + TString(std::to_string(DblGatedGams[dg])) + "_Ex_" + TString(std::to_string(Ex_BinLow)) + "_" + TString(std::to_string(Ex_BinHi)) + "_Bkg");

			SiExvDblGam.push_back(h26);
			SiExvDblGam_BkgUnScale.push_back(h27);
			SiExvDblGam_Bkg.push_back(h28);
			QQQ_SiExvDblGam.push_back(h29);
			QQQ_SiExvDblGam_BkgUnScale.push_back(h30);
			QQQ_SiExvDblGam_Bkg.push_back(h31);

		}

		DblGamGated_QQQ.push_back(QQQ_SiExvDblGam);
		DblGamGated_QQQ_BkgUnScale.push_back(QQQ_SiExvDblGam_BkgUnScale);
		DblGamGated_QQQ_Bkg.push_back(QQQ_SiExvDblGam_Bkg);
		DblGamGated_Si.push_back(SiExvDblGam);
		DblGamGated_Si_BkgUnScale.push_back(SiExvDblGam_BkgUnScale);
		DblGamGated_Si_Bkg.push_back(SiExvDblGam_Bkg);

		SiExvGam.clear();
		SiExvGam_BkgUnScale.clear();
		SiExvGam_Bkg.clear();
		QQQ_SiExvGam.clear();
		QQQ_SiExvGam_BkgUnScale.clear();
		QQQ_SiExvGam_Bkg.clear();

		SiExvDblGam.clear();
		SiExvDblGam_BkgUnScale.clear();
		SiExvDblGam_Bkg.clear();
		QQQ_SiExvDblGam.clear();
		QQQ_SiExvDblGam_BkgUnScale.clear();
		QQQ_SiExvDblGam_Bkg.clear();

		hist->cd("Ex_vs_Gammas_Hists/Si_v_Gam/Si_SingleGammaGated");

		
		

	}

	std::cout << GamGated_QQQ.size() << " " << GamGated_QQQ[1].size() << std::endl;

		gam238vEx = new TH2D("gam238vEx","238 keV Gamma Gated on Tritons",8000,0,8000,30,4,7);
		gam275vEx = new TH2D("gam275vEx","275 keV Gamma Gated on Tritons",8000,0,8000,30,4,7);

	//QQQ energy histograms are created here.
	hist->cd("Silicon_Detectors/Strip_vs_E_Hists");
	QQQDAdE = new TH2D("QQQDAdE","QQQ5 DA dE",4096,0,4096,32,0,32);
	QQQDAE1 = new TH2D("QQQDAE1","QQQ5 DA E1",4096,0,4096,32,0,32);
	QQQDAE2 = new TH2D("QQQDAE2","QQQ5 DA E2",4096,0,4096,32,0,32);

	QQQDCdE = new TH2D("QQQDCdE","QQQ5 DC dE",1250,0,50000,32,0,32);
	QQQDCE1 = new TH2D("QQQDCE1","QQQ5 DC E1",1250,0,50000,32,0,32);

	QQQDAE1sum = new TH2D("QQQDAE1sum","QQQ5 DA E1 Summed Histograms",1024,0,1024,32,0,32);
	QQQDAE1cal = new TH2D("QQQDAE1cal","QQQ5 DA E1 Calibrated Histograms",512,0,32,32,0,32);
	QQQDAdEcal = new TH2D("QQQDAdEcal","QQQ5 DA dE Calibrated Histograms",512,0,32,32,0,32);

	QQQDCE1sum = new TH2D("QQQDCE1sum","QQQ5 DC E1 Summed Histograms",1250,0,50000,20,0,20);
	
	QQQDAvsGam = new TH2D("QQQDAvsGam","Gamma Energy vs Ex",2048,0,15,8000,0,8000);

	hist->cd("Silicon_Detectors/DA_Total_E");
	QQQDATot = new TH2D("QQQDATot","QQQ5 DA Total Energy",2048,0,32,32,0,32);
	QQQDATot2 = new TH2D("QQQDATot2","QQQ5 DA Total Energy Before Degradation",2048,15,32,19,0,19);
	QQQDAQ = new TH2D("QQQDAQ","Strip Number vs Reaction Q-Value Spectrum",2048,-15,0,19,0,19);
	QQQDAQAl = new TH2D("QQQDAQAl","Strip Number vs Reaction Q-Value Spectrum 27Al(3He,t)",2048,-15,0,19,0,19);
	QQQDATotQ = new TH1D("QQQDATotQ","QQQ5 DA Q Summed Q-Value Spectrum",2048,-15,0);
	QQQDAEx = new TH2D("QQQDAEx","Strip Number vs Excitation Energy",2048,0,15,19,0,19);
	QQQDAExTot = new TH1D("QQQDAExTot","Excitation Energy of 19Ne",2048,0,15);

	//Test histograms for timing are created here.
	QQQDAExtotTiming = new TH1D("QQQDAExtotTiming","QQQ5 DA Total E Timing Gated",2048,0,15);

	std::string gambase = "gam_pk";

	hist->cd("Silicon_Detectors/DC_Total_E");
	QQQDCQ = new TH2D("QQQDCQ","Strip Number vs Reaction Q-Value Spectrum",2048,-15,0,19,0,19);
	QQQDCEx = new TH2D("QQQDCEx","Strip Number vs Excitation Energy",2048,0,15,19,0,19);
	QQQDCExTot = new TH1D("QQQDCExTot","Excitation Energy of 19Ne",2048,0,15);

	hist->cd("Gamma_Hists/Gammasphere_Histograms");
	gam_ind = new TH2D("gam_ind","Individual Gammasphere Detectors",10000,0,10000,111,0,111);
	gam_tot = new TH1D("gam_tot","Summed Gammasphere Spectrum",8000,0,8000);

	gam_tot2 = new TH1D("gam_tot2","Summed Gammasphere Spectrum without Background",8000,0,8000);
	gam_totBack = new TH1D("gam_totBack","Summed Gammasphere Spectrum Background",1000,0,8000);
	gam_totBack2 = new TH1D("gam_totBack2","Summed Gammasphere Spectrum Background 2",1000,0,8000);
	gam_totBackAvg = new TH1D("gam_totBackAvg","Summed Gammasphere Spectrum Background Averaged",1000,0,8000);
	gam_totBackAvg8000 = new TH1D("gam_totBackAvg8000","Summed Gammasphere Spectrum Background Averaged",8000,0,8000);

	gam_ind->GetXaxis()->SetTitle("Channel Number");
	gam_ind->GetYaxis()->SetTitle("Gammasphere Detector Number");
	gam_ind->GetXaxis()->CenterTitle();
	gam_ind->GetYaxis()->CenterTitle();

	gam_tot->GetXaxis()->SetTitle("Energy (keV)");
	gam_tot->GetYaxis()->SetTitle("Counts");
	gam_tot->GetXaxis()->CenterTitle();
	gam_tot->GetYaxis()->CenterTitle();


	for (int i=0; i<7; i++){
		string namegam = gambase + std::to_string(i);
		TH1D *h = new TH1D(TString(namegam),"Gated Gammasphere Spectrum Triton Peak " + TString(std::to_string(i)),8000,0,8000);

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
	std::string QE1base = "Q_gated_E1_";
	std::string QdEbase = "Q_gated_dE_";
		
	for (int i=0; i<stripnum; i++){
		hist->cd("Silicon_Detectors/Particle_IDs/DA_PID");
		//Creates the summed DA PID plots (with coincidences of PstripE-PstripdE <=4)
		string nameDA = PIDbaseDA + std::to_string(i);
		TH2D *h0 = new TH2D(TString(nameDA),"QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),1024,0,1024,4096,0,4096);					

		DA_PIDhists.push_back(h0);

		DA_PIDhists.back()->GetXaxis()->SetTitle("Channel Number in E1");
		DA_PIDhists.back()->GetYaxis()->SetTitle("Channel Number in dE");
		DA_PIDhists.back()->GetXaxis()->CenterTitle();
		DA_PIDhists.back()->GetYaxis()->CenterTitle();

		hist->cd("Silicon_Detectors/Particle_IDs/DA_PID_Cal");
		TH2D *g0 = new TH2D(TString(nameDA)+"_cal","QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),1024,0,32,500,0,6);					

		DA_PIDhists_Cal.push_back(g0);

		DA_PIDhists_Cal.back()->GetXaxis()->SetTitle("E1 Energy (MeV)");
		DA_PIDhists_Cal.back()->GetYaxis()->SetTitle("dE Energy (MeV)");
		DA_PIDhists_Cal.back()->GetXaxis()->CenterTitle();
		DA_PIDhists_Cal.back()->GetYaxis()->CenterTitle();

		hist->cd("Silicon_Detectors/Particle_IDs/DC_PID");
		//Creates the summed DC PID plots (with coincidences of PstripE-PstripdE <=4)
		string nameDC = PIDbaseDC + std::to_string(i);
		TH2D *h1 = new TH2D(TString(nameDC),"QQQ5 DC dE vs E1 Strip " + TString(std::to_string(i)),1250,0,50000,1250,0,50000);

		DC_PIDhists.push_back(h1);

		DC_PIDhists.back()->GetXaxis()->SetTitle("Channel Number in E1");
		DC_PIDhists.back()->GetYaxis()->SetTitle("Channel number in dE");
		DC_PIDhists.back()->GetXaxis()->CenterTitle();
		DC_PIDhists.back()->GetYaxis()->CenterTitle();

		hist->cd("Silicon_Detectors/Triton_Spectra/DA_Triton_Spectra");
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

		hist->cd("Silicon_Detectors/Triton_Spectra/DC_Triton_Spectra");
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


		hist->cd("Silicon_Detectors/Calibration_Hists/DA_dE_gated");

		for (int j=0; j<4; j++){
			
			string dEgatename = dEgatebase + std::to_string(i) + std::to_string(j);
			TH1D *h4 = new TH1D(TString(dEgatename),"DA dE " + TString(std::to_string(i)) + " gated on peak " + TString(std::to_string(j)),4096,0,4096);
			dE_gated.push_back(h4);

		}

		DA_dE_Gated.push_back(dE_gated);
		dE_gated.clear();

		hist->cd("Silicon_Detectors/DA_Total_E");

		string nametotDA = baseDAtot + std::to_string(i);
		TH1D *h5 = new TH1D(TString(nametotDA),"QQQ5 DA Total Energy Strip " + TString(std::to_string(i)),512,0,32);					

		DA_TotE.push_back(h5);
		DA_TotE.back()->GetXaxis()->SetTitle("Energy (MeV)");
		DA_TotE.back()->GetYaxis()->SetTitle("Counts");
		DA_TotE.back()->GetXaxis()->CenterTitle();
		DA_TotE.back()->GetYaxis()->CenterTitle();

		hist->cd("Silicon_Detectors/Calibration_Hists/Q_Gated_QQQ_DA_E1");
		string QE1gated = QE1base + std::to_string(i);
		TH1D *h6 = new TH1D(TString(QE1gated),"Q Gated QQQ DA E1 Strip " + TString(std::to_string(i)),4096,0,4096);
		Q_gated_E1.push_back(h6);


		hist->cd("Silicon_Detectors/Calibration_Hists/Q_Gated_QQQ_DA_dE");
		for (int j=0; j<5; j++){
			string QdEgated = QdEbase + std::to_string(i) + std::to_string(j);	
			TH1D *h7 = new TH1D(TString(QdEgated),"Q Gated QQQ DA dE Strip " + TString(std::to_string(i)),4096,0,4096);
			Q_gated_dE.push_back(h7);
		}

		Q_DA_dE_Gated.push_back(Q_gated_dE);
		Q_gated_dE.clear();
		
	}

	//Initialization of the BB10 vs SX3 histograms is here:
	string FBbase;
	string FBname;

	for (int k = 0; k < 6; k++){

		switch (k){
			case 0: hist->cd("Silicon_Detectors/Particle_IDs/D4_FB_PIDs");
				FBbase = "D4_";
				break;
			case 1: hist->cd("Silicon_Detectors/Particle_IDs/D5_FB_PIDs");
				FBbase = "D5_";
				break;
			case 2: hist->cd("Silicon_Detectors/Particle_IDs/D7_FB_PIDs");
				FBbase = "D7_";
				break;
			case 3: hist->cd("Silicon_Detectors/Particle_IDs/D8_FB_PIDs");
				FBbase = "D8_";
				break;
			case 4: hist->cd("Silicon_Detectors/Particle_IDs/D9_FB_PIDs");
				FBbase = "D9_";
				break;
			case 5: hist->cd("Silicon_Detectors/Particle_IDs/D10_FB_PIDs");
				FBbase = "D10_";
				break;
		}//closes switch statement

		//Pos sector: -30 to -10 sector 0, -10 to 10 sector 1, 10 to 30 sector 2, 30 to 50 sector 3

		//these vectors should be identified by vec[BB10 strip][SX3 strip][pos sector]


		for (int p = 0; p < 8; p++){

			for (int n = 0; n < 4; n++){


				for (int s = 0; s < 4; s++){

					if (p == 0 && n != 3) break;
					if ((p == 1 || p == 2) && (n != 3 && n != 2)) break;
					if ((p == 3 || p == 4) && (n != 2 && n != 1)) break;
					if (p == 5 && n != 1) break;
					if ((p == 6 || p == 7) && n !=0) break;

					FBname = FBbase + std::to_string(p) + "_" + std::to_string(n) + "_sec" + std::to_string(s);

					TH2D *h8 = new TH2D(TString(FBname),"BB10 Strip " + TString(std::to_string(p)) + " SX3 Strip " + TString(std::to_string(n)) + " Position Sector " + TString(std::to_string(s)),1250,0,900000,1250,0,300000);

					PIDCont.push_back(h8);

				} //closes position sector loop

				PIDCont2.push_back(PIDCont);
				PIDCont.clear();

			} //closes SX3 strip number loop
	
			switch (k){
				case 0: D4_PID.push_back(PIDCont2);
					break;
				case 1: D5_PID.push_back(PIDCont2);
					break;
				case 2: D7_PID.push_back(PIDCont2);
					break;
				case 3: D8_PID.push_back(PIDCont2);
					break;
				case 4: D9_PID.push_back(PIDCont2);
					break;
				case 5: D10_PID.push_back(PIDCont2);
					break;
				}//closes switch statement
			
			PIDCont2.clear();

		}//closes BB10 strip number loop

	}//closes outer switch statement loop

	Timing_Spectra->cd();

	TDiffDA = new TH1D("TDiffDA","Timing Difference Between Gammasphere and QQQ5 DA",1000,-500,500);
	TDiffDC = new TH1D("TDiffDC","Timing Difference Between Gammasphere and QQQ5 DC",1000,-500,500);
	TDiffSX3 = new TH1D("TDiffSX3","Timing Difference Between Gammasphere and SX3",1000,-500,500);


	gam_DA = new TH2D("gam_DA","Timing Difference Between Gammasphere and QQQ5 DA",2000,-1000,1000,32,0,32);
	gam_DC = new TH2D("gam_DC","Timing Difference Between Gammasphere and QQQ5 DC",2000,-1000,1000,32,0,32);

	TimeHist = new TH1D("TimeHist","Timing Difference for different QQQ5 Peaks",1000,-500,500);

	gamTime = new TH2D("gamTime","Gamma Energy vs Timing Difference", 1000,-500,500,4000,0,8000);

	gam511vtime = new TH1D("gam511vtime","Gamma 511 intensity vs timing",1000,-500,500); 
	gam511vtimeBACK = new TH1D("gam511vtimeBACK","Gamma 511 intensity vs timing",1000,-500,500);

	gam238vtime = new TH1D("gam238vtime","Gamma 238 intensity vs timing",1000,-500,500); 
	gam238vtimeBACK = new TH1D("gam238vtimeBACK","Gamma 238 intensity vs timing",1000,-500,500);

	gam1233vtime = new TH1D("gam1233vtime","Gamma 1233 intensity vs timing",1000,-500,500); 
	gam1233vtimeBACK = new TH1D("gam1233vtimeBACK","Gamma 1233 intensity vs timing",1000,-500,500);

	gam1633vtime = new TH1D("gam1633vtime","Gamma 1633 intensity vs timing",1000,-500,500); 
	gam1633vtimeBACK = new TH1D("gam1633vtimeBACK","Gamma 1633 intensity vs timing",1000,-500,500);

	hist->cd("Gamma_Hists/Gamma_Gated_Histograms");

	gam238 = new TH1D("gam238","Gammas Gated on 237 keV Peak",8000,0,8000);
	gam275 = new TH1D("gam275","Gammas Gated on 272 keV Peak",8000,0,8000);
	gam1233 = new TH1D("gam1233","Gammas Gated on 1233 keV Peak",8000,0,8000);
	gam1297 = new TH1D("gam1297","Gammas Gated on 1297 keV Peak",8000,0,8000);
	gam1840 = new TH1D("gam1840","Gammas Gated on 1840 keV Peak",8000,0,8000);
	gam2556 = new TH1D("gam2556","Gammas Gated on 2556 keV Peak",8000,0,8000);

	hist->cd("Gamma_Hists/Gamma_Gated_Histograms/Background");

	gam238_Back = new TH1D("gam238_Back","Gammas Gated on 237 keV Peak",8000,0,8000);
	gam275_Back = new TH1D("gam275_Back","Gammas Gated on 272 keV Peak",8000,0,8000);
	gam1233_Back = new TH1D("gam1233_Back","Gammas Gated on 1233 keV Peak",8000,0,8000);
	gam1297_Back = new TH1D("gam1297_Back","Gammas Gated on 1297 keV Peak",8000,0,8000);
	gam1840_Back = new TH1D("gam1840_Back","Gammas Gated on 1840 keV Peak",8000,0,8000);
	gam2556_Back = new TH1D("gam2556_Back","Gammas Gated on 2556 keV Peak",8000,0,8000);

	hist->cd("Gamma_Hists/Gamma_Intensity_Histograms");

	int238 = new TH1D("int238","Intensity of 238 keV Gamma vs Q-Value",300,-15,0);
	back238 = new TH1D("back238","Background of 238 keV Gamma vs Q-Value",300,-15,0);

	int275 = new TH1D("int275","Intensity of 275 keV Gamma vs Q-Value",300,-15,0);
	back275 = new TH1D("back275","Background of 275 keV Gamma vs Q-Value",300,-15,0);

	int1232 = new TH1D("int1232","Intensity of 1232 keV Gamma vs Q-Value",300,-15,0);
	back1232 = new TH1D("back1232","Background of 1232 keV Gamma vs Q-Value",300,-15,0);

	int1840 = new TH1D("int1840","Intensity of 1840 keV Gamma vs Q-Value",300,-15,0);
	back1840 = new TH1D("back1840","Background of 1840 keV Gamma vs Q-Value",300,-15,0);

	int2556 = new TH1D("int2556","Intensity of 2556 keV Gamma vs Q-Value",300,-15,0);
	back2556 = new TH1D("back2556","Background of 2556 keV Gamma vs Q-Value",300,-15,0);

	int4140 = new TH1D("int4140","Intensity of 4140 keV Gamma vs Q-Value",300,-15,0);
	back4140 = new TH1D("back4140","Background of 4140 keV Gamma vs Q-Value",300,-15,0);

	int4362 = new TH1D("int4362","Intensity of 4362 keV Gamma vs Q-Value",300,-15,0);
	back4362 = new TH1D("back4362","Background of 4362 keV Gamma vs Q-Value",300,-15,0);

	int1853 = new TH1D("int1853","Intensity of 1853 keV Gamma vs Q-Value",300,-15,0);
	back1853 = new TH1D("back1853","Background of 1853 keV Gamma vs Q-Value",300,-15,0);

	int1844 = new TH1D("int1844","Intensity of 1844 keV Gamma vs Q-Value",300,-15,0);
	back1844 = new TH1D("back1844","Background of 1844 keV Gamma vs Q-Value",300,-15,0);

	hist->cd("Gamma_Hists/Triton_Gated");

	gamExGated = new TH1D("gamExGated","Gammas Gated on Tritons",8000,0,8000);
	gamExGated2 = new TH1D("gamExGated2","Gammas Gated on Tritons Background Subtracted",8000,0,8000);
	gamExBack = new TH1D("gamExBack","Gammas Gated on Tritons Background (Low Timing Gate)",1000,0,8000);
	gamExBack2 = new TH1D("gamExBack2","Gammas Gated on Tritons Background (High Timing Gate)",1000,0,8000);
	gamExBackAvg = new TH1D("gamExBackAvg","Gammas Gated on Tritons Background (Average)",1000,0,8000);
	gamExBackAvg8000 = new TH1D("gamExBackAvg8000","Gammas Gated on Tritons Background (Average)",8000,0,8000);


	hist->cd("Gamma_Hists/Excitation_Energy_Gated");
	double gatenum=0;

	for (int i=0; i<31; i++){
		ExGateArrLow[i] = gatenum;
		gatenum += 0.3;
		ExGateArrHi[i] = ExGateArrLow[i]+0.5;

		string ExNameBase = "Ex_" + std::to_string(ExGateArrLow[i]) + "_" + std::to_string(ExGateArrHi[i]);
		
		TH1D *h9 = new TH1D(TString(ExNameBase),"Gated Gammasphere Spectrum Ex " + TString(std::to_string(ExGateArrLow[i])) + " to " + TString(std::to_string(ExGateArrHi[i])),8000,0,8000);

		ExGatedGams.push_back(h9);

	}

	hist->cd("Gamma_Hists/Gams_vs_Run");
	for (int i = 0; i < 111; i++){
	
		TH2D *hgam = new TH2D("Gam_" + TString(std::to_string(i)),"Gam " + TString(std::to_string(i)),5000,0,10000,100,400,500);
		GamvRunnum.push_back(hgam);

	}

	hist->cd("Silicon_Detectors/SX3_Hists");
	SX3_Gam_Gated = new TH2D("SX3_Gam_Gated","SX3 Summed Energy Gamma Gated Background",30,30,90,300,10,25);
	SX3_Gated_Back = new TH2D("SX3_Gated_Back","SX3 Summed Gamma Gated Background",30,30,90,300,10,25);

	SX3_Q_Gam_Gated = new TH2D("SX3_Q_Gam_Gated","SX3 Summed Q-value Gamma Gated Background",30,30,90,300,-15,0);
	SX3_Q_Gated_Back = new TH2D("SX3_Q_Gated_Back","SX3 Summed Q-value Gamma Gated Background",30,30,90,300,-15,0);

	SX3Ex = new TH1D("SX3Ex","Excitation Energy of 19Ne in SX3 Gamma Gated",800,0,8);
	SX3ExBack = new TH1D("SX3ExBack","Excitation Energy of 19Ne in SX3 Background",800,0,8);
	SX3ExTot = new TH1D("SX3ExTot","Excitation Energy of 19Ne in SX3 Ungated",800,0,8);

	string D4base = "D4_E_";
	string D5base = "D5_E_";
	string D7base = "D7_E_";
	string D8base = "D8_E_";
	string D9base = "D9_E_";
	string D10base = "D10_E_";

	for (int i = 0; i < 4; i++){
		hist->cd("Silicon_Detectors/SX3_Hists/D4_Hists/Energy_Ungated4");
			TH2D *h10 = new TH2D(TString(D4base) + TString(std::to_string(i)),"D4 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D4_E_Ungated.push_back(h10);

			if (i == 3) D4_E_Sum_v_Ang = new TH2D(TString(D4base) + TString("Sum_v_Ang"),"D4 Energy Summed",500,0,1000000,30,30,90);
		hist->cd("Silicon_Detectors/SX3_Hists/D5_Hists/Energy_Ungated5");
			TH2D *h11 = new TH2D(TString(D5base) + TString(std::to_string(i)),"D5 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D5_E_Ungated.push_back(h11);

			if (i == 3) D5_E_Sum_v_Ang = new TH2D(TString(D5base) + TString("Sum_v_Ang"),"D5 Energy Summed",500,0,1000000,30,30,90);
		hist->cd("Silicon_Detectors/SX3_Hists/D7_Hists/Energy_Ungated7");
			TH2D *h12 = new TH2D(TString(D7base) + TString(std::to_string(i)),"D7 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D7_E_Ungated.push_back(h12);

			if (i == 3) D7_E_Sum_v_Ang = new TH2D(TString(D7base) + TString("Sum_v_Ang"),"D7 Energy Summed",500,0,1000000,30,30,90);
		hist->cd("Silicon_Detectors/SX3_Hists/D8_Hists/Energy_Ungated8");
			TH2D *h13 = new TH2D(TString(D8base) + TString(std::to_string(i)),"D8 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D8_E_Ungated.push_back(h13);

			if (i == 3) D8_E_Sum_v_Ang = new TH2D(TString(D8base) + TString("Sum_v_Ang"),"D8 Energy Summed",500,0,1000000,30,30,90);
		hist->cd("Silicon_Detectors/SX3_Hists/D9_Hists/Energy_Ungated9");
			TH2D *h14 = new TH2D(TString(D9base) + TString(std::to_string(i)),"D9 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D9_E_Ungated.push_back(h14);

			if (i == 3) D9_E_Sum_v_Ang = new TH2D(TString(D9base) + TString("Sum_v_Ang"),"D9 Energy Summed",500,0,1000000,30,30,90);
		hist->cd("Silicon_Detectors/SX3_Hists/D10_Hists/Energy_Ungated10");
			TH2D *h15 = new TH2D(TString(D10base) + TString(std::to_string(i)),"D10 Energy Ungated Strip " + TString(std::to_string(i)),500,0,1000000,30,30,90);
			D10_E_Ungated.push_back(h15);

			if (i == 3) D10_E_Sum_v_Ang = new TH2D(TString(D10base) + TString("Sum_v_Ang"),"D10 Energy Summed",500,0,1000000,30,30,90);
	}



	hist->cd("Silicon_Detectors/SX3_Hists/Gamma_Gated_Background");

		D4_E_Gated_Back = new TH2D(TString(D4base) + TString("Gated_Back"),"D4 Energy Gamma Gated Background",30,30,90,500,0,25);
		D5_E_Gated_Back = new TH2D(TString(D5base) + TString("Gated_Back"),"D5 Energy Gamma Gated Background",30,30,90,500,0,25);
		D7_E_Gated_Back = new TH2D(TString(D7base) + TString("Gated_Back"),"D7 Energy Gamma Gated Background",30,30,90,500,0,25);
		D8_E_Gated_Back = new TH2D(TString(D8base) + TString("Gated_Back"),"D8 Energy Gamma Gated Background",30,30,90,500,0,25);
		D9_E_Gated_Back = new TH2D(TString(D9base) + TString("Gated_Back"),"D9 Energy Gamma Gated Background",30,30,90,500,0,25);
		D10_E_Gated_Back = new TH2D(TString(D10base) + TString("Gated_Back"),"D10 Energy Gamma Gated Background",30,30,90,500,0,25);

//		D7Gated = new TH2D("D7Gated","D7 Energy Gamma Gated",500,0,1000000,30,30,90);

	hist->cd("Silicon_Detectors/SX3_Hists/Gamma_Gated");
	
		D4_E_Gam_Gated = new TH2D(TString(D4base) + TString("Gam_Gated"),"D4 Energy Gamma Gated ",30,30,90,500,0,25);
		D5_E_Gam_Gated = new TH2D(TString(D5base) + TString("Gam_Gated"),"D5 Energy Gamma Gated ",30,30,90,500,0,25);
		D7_E_Gam_Gated = new TH2D(TString(D7base) + TString("Gam_Gated"),"D7 Energy Gamma Gated ",30,30,90,500,0,25);
		D8_E_Gam_Gated = new TH2D(TString(D8base) + TString("Gam_Gated"),"D8 Energy Gamma Gated ",30,30,90,500,0,25);
		D9_E_Gam_Gated = new TH2D(TString(D9base) + TString("Gam_Gated"),"D9 Energy Gamma Gated ",30,30,90,500,0,25);
		D10_E_Gam_Gated = new TH2D(TString(D10base) + TString("Gam_Gated"),"D10 Energy Gamma Gated ",30,30,90,500,0,25);


	//The files for the normalization parameters and gates are opened here.
	ifstream inFile0("textfiles/AnglesAndELoss2.txt");	
	ifstream inFile1("textfiles/E1normmultDA.txt");
	ifstream inFile2("textfiles/E1normaddDA.txt");
	ifstream inFile3("textfiles/gates.txt");
	ifstream inFile4("textfiles/dEECal2.txt");
	//ifstream inFile4("E1cal.txt");
	//ifstream inFile5("dEcal.txt");
//	ifstream inFile6("textfiles/GamCalParamsQuadREDO.txt");
	ifstream inFile6("textfiles/GamCalParamsQuad.txt");
//	ifstream inFile6("textfiles/GamCalParamsQuadREDO2.txt");
//	ifstream inFile6("textfiles/GamCalLinWHighREDO2.txt");
//	ifstream inFile6("textfiles/GamCalLinWHighREDOcompat.txt");
//	ifstream inFile6("GamCal/QuadraticCalibration.txt");
//	ifstream inFile6("GamCal/PeakFinderLinear.txt");
//	ifstream inFile6("GamCal/PeakFinderQuad.txt");
//	ifstream inFile6("GamCal/LinearCalibration.txt");
//	ifstream inFile7("angleassign.txt");
//	ifstream inFile8("energyloss.txt");
	ifstream inFile9("textfiles/Qbins.txt");
	ifstream inFile10("textfiles/QQQDCTGates.txt");
	ifstream inFile11("textfiles/CalGatesLo.txt");
	ifstream inFile12("textfiles/CalGatesHi.txt");

	ifstream inFile13("textfiles/E1normmult2DC.txt");
	ifstream inFile14("textfiles/E1normmult1DC.txt");
	ifstream inFile15("textfiles/E1normaddDC.txt");
	ifstream inFile16("textfiles/DCtoQ.txt");

//	ifstream inFile17("textfiles/SX3Norm.txt");
	ifstream inFile18("textfiles/SX3RenormParams.txt");
	ifstream inFile19("textfiles/SX3Norm_Angle.txt");
	ifstream inFile20("textfiles/SX3Cal.txt");

	ifstream inFile21("textfiles/GamCorr1.txt");

	ifstream inFile22("GamCal/GamNorm31.txt");
	ifstream inFile23("GamCal/GamNorm87.txt");

	ifstream inFile24("textfiles/GamNorm.txt");

	ifstream inFile25("textfiles/DCtoTotalE.txt");

	for (int i = 0; i<20; i++){

		inFile0 >> AandEloss[i][0] >> AandEloss[i][1] >> AandEloss[i][2] >> AandEloss[i][3] >> AandEloss[i][4] >> AandEloss[i][5];

	} 

	//build the arrays for the gates and normalization parameters:

	for (int i=0; i<32; i++){

		inFile4 >> calDAE1[i][0] >> calDAE1[i][1] >> calDAdE[i][0] >> calDAdE[i][1];

		inFile16 >> DCtoQ[i][0] >> DCtoQ[i][1] >> DCtoQ[i][2];
		inFile25 >> DCtoTotalE[i][0] >> DCtoTotalE[i][1] >> DCtoTotalE[i][2];

//		inFile4 >> calDAE1[i][0] >> calDAE1[i][1];
//		inFile5 >> calDAdE[i][0] >> calDAdE[i][1];
		
		for (int k = 0; k<8; k++){

			inFile3 >> boundDA[i][k];

		}

		for (int j=0; j<5; j++){

			inFile1 >> normDA0[i][j];
			inFile2 >> normDA1[i][j];

			inFile13 >> normDC0[i][j];
			inFile14 >> normDC1[i][j];
			inFile15 >> normDC2[i][j];
			
		}

//		if (i<20) inFile7 >> stripangle[i][0] >> stripangle[i][1];

//		if (i<12) inFile8 >> energyloss[i][0] >> energyloss[i][1] >> energyloss[i][2] >> energyloss[i][3] >> energyloss[i][4] >> energyloss[i][5];

		inFile11 >> CalPIDGateLo[i][0] >> CalPIDGateLo[i][1] >> CalPIDGateLo[i][2] >> CalPIDGateLo[i][3] >> CalPIDGateLo[i][4];
		inFile12 >> CalPIDGateHi[i][0] >> CalPIDGateHi[i][1] >> CalPIDGateHi[i][2] >> CalPIDGateHi[i][3] >> CalPIDGateHi[i][4];


	}

	for (int i=0; i<111; i++){

		inFile6 >> gamcalparams[i][0] >> gamcalparams[i][1] >> gamcalparams[i][2];

		inFile21 >> gamcorr[i];

		inFile24 >> GamNorm[i][0] >> GamNorm[i][1] >> GamNorm[i][2];

	}

	for (int i=0; i<300; i++){
		
		inFile9 >> Qbins[i] >> buff >> Qgatearray[i][0] >> Qgatearray[i][1];

		if (i < 44){
			if (i < 22) inFile10 >> TGateDCLow[i][0] >> TGateDCLow[i][1] >> TGateDCLow[i][2] >> TGateDCLow[i][3] >> TGateDCLow[i][4];
			if (i > 21) inFile10 >> TGateDCHi[i-22][0] >> TGateDCHi[i-22][1] >> TGateDCHi[i-22][2] >> TGateDCHi[i-22][3] >> TGateDCHi[i-22][4];
		}

	}

//	for (int i = 0; i < 7; i++){
//		for (int j = 0; j < 4; j++){
//			inFile17 >> SX3Norm[i][0] >> SX3Norm[i][1] >> SX3Norm[i][2] >> SX3Norm[i][3] >> SX3Norm[i][4] >> SX3Norm[i][5] >> SX3Norm[i][6] >> SX3Norm[i][7];
//		}


//	}

	for (int i = 0; i < 28; i++){

		inFile18 >> SX3Renorm[i][0] >> SX3Renorm[i][1] >> SX3Renorm[i][2];
		inFile19 >> SX3Norm_Ang[i][0] >> SX3Norm_Ang[i][1] >> SX3Norm_Ang[i][2] >> SX3Norm_Ang[i][3];

	}

	for (int i = 0; i < 23; i++){

		inFile20 >> SX3Cal[i][0] >> SX3Cal[i][1] >> SX3Cal[i][2] >> SX3Cal[i][3] >> SX3Cal[i][4] >> SX3Cal[i][5] >> SX3Cal[i][6] >> SX3Cal[i][7] >> SX3Cal[i][8] >> SX3Cal[i][9] >> SX3Cal[i][10] >> SX3Cal[i][11] >> SX3Cal[i][12] >> SX3Cal[i][13]; 	

	}

	for (int i = 0; i < 95; i++){

		inFile22 >> GamNorm31[i];
		inFile23 >> GamNorm87[i];


	}


	

//	for (int i=0; i<22; i++){
//		std::cout << TGateDCHi[i][0] << " " << TGateDCHi[i][1] << " " << TGateDCHi[i][2] << " " << TGateDCHi[i][3] << " " << TGateDCHi[i][4] << std::endl;
//
//	}

	//close the files here
	inFile0.close();
	inFile1.close();
	inFile2.close();
	inFile3.close();
	inFile4.close();
//	inFile5.close();
	inFile6.close();
//	inFile7.close();
//	inFile8.close();
	inFile9.close();
	inFile10.close();



	int numruns = 0;
	for (int run = 404; run < 495; run++){
		//Only some runs actually have data and will be made into histograms using this code.
		if ((run > 400 && run < 409 && run != 405 && run != 406) || (run > 409 && run < 424) || (run > 431 && run < 435) || (run > 436 && run < 447) || (run > 448 && run < 455) || (run > 455 && run < 458) || (run > 459 && run < 465) || (run > 468 && run < 484) || (run > 484 && run < 495)){
			t.Stop();
			t.Print();
			t.Start(false);
			histfill(run,logFile);
			numruns++;
		}
	}
	
	int238->Add(back238,-1);
	int275->Add(back275,-1);
	int1232->Add(back1232,-1);
	int1840->Add(back1840,-1);
	int2556->Add(back2556,-1);
	int4140->Add(back4140,-1);
	int4362->Add(back4362,-1);

//	int1853->Add(back1853,-1);
//	int1844->Add(back1844,-1);

	gam511vtime->Add(gam511vtimeBACK,-1);
	gam238vtime->Add(gam238vtimeBACK,-1);
	gam1233vtime->Add(gam1233vtimeBACK,-1);

	float average=0;
	float average2=0;

	float ReducedContent = 0;
	float ReducedContent2 = 0;

	double scale4k;
	double scale8k;

	double BinConts;
	//RealExLoopEnd is the actual endpoint number of the for loops calculated with the ExWidth variable.
	int RealExLoopEnd = 30-ExWidth+1;
	//Set the scale factors here for the histograms that go from 0 to 4000 and 4000 to 8000.
	//Also do the scaling here before the contents get transfered to the final 8000 bin background hist.
//	for (int ex = 0; ex < RealExLoopEnd; ex++){
//		scale4k = QQQExvGam[ex]->Integral(24,4000) / QQQExvGam_Bkg4k1000[ex]->Integral(1,100);;
//		scale8k = QQQExvGam[ex]->Integral(4000,8000) / QQQExvGam_Bkg8k1000[ex]->Integral(1,100);
		
//		QQQExvGam_Bkg4k1000[ex]->Scale(scale4k);
//		QQQExvGam_Bkg8k1000[ex]->Scale(scale8k);

//		std::cout << "tot: " << QQQExvGam[ex]->Integral(4000,8000) << " Back: " << QQQExvGam_Bkg8k1000[ex]->Integral(1,100) << " Scale: " << scale8k << endl;

//	}

	//Do the scaling from one histogram in smaller chunks. 
	double CombinedConts = 0;
	double CombinedContsQQQ = 0;
	double CombinedContsSi = 0;
	double ContsAvg = 0;
	double ContsAvgQQQ = 0;
	double ContsAvgSi = 0;
	double scaling = 0;
	double scaling2 = 0;

	double SiscalingGamSingle = 0;
	double QQQscalingGamSingle = 0;

	double SiscalingGamDouble = 0;
	double QQQscalingGamDouble = 0;

	double errors = 0;
	double errorsQQQ = 0;
	double errorsSi = 0;

	int g1 = 0;	
	int g2 = 0;

	for (int ex = 0; ex < RealExLoopEnd; ex++){

		for (int bin = 1; bin <= 8000; bin++){

			if ((bin == 1 || (bin-1) % 500 == 0) && bin != 8000) scaling = QQQExvGam[ex]->Integral(bin,bin+499)/QQQExvGam_Bkg[ex]->Integral(bin,bin+499);

			if (bin < 3001){//800 bins (20keV/bin)
				if ((bin == 1 || (bin-1) % 100 == 0) && bin != 8000 /*&& bin > 100*/){
					if (bin+100 < 238 && (bin+200) > 238) scaling2 = scaling2;
					//else if (bin <= 275 && (bin+19) >= 275) scaling2 = scaling2;
					//else if (bin <= 511 && (bin+19) >= 511) scaling2 = scaling2;
					//else if (bin <= 1231 && (bin+19) >= 1231) scaling2 = scaling2;
					//else if (bin <= 1268 && (bin+19) >= 1268) scaling2 = scaling2;
					else if (bin+100 <= 1839 && (bin+200) >= 1839) scaling2 = scaling2;
					//else if (bin <= 1841 && (bin+19) >= 1841) scaling2 = scaling2;
					else if (bin+100 <= 2556 && (bin+200) >= 2556) scaling2 = scaling2;

					else scaling2 = QQQExvGam[ex]->Integral(bin+100,bin+200)/QQQExvGam_Bkg[ex]->Integral(bin+100,bin+200);


				}
				

				if ((bin-1) % 2 == 0){
					CombinedConts = 0; //if the bin number-1 is div by 4, 5,9,etc, then reset combined conts to 0.
//					cout << "*********** RESET ************" << endl;
				}
				CombinedConts += QQQExvGam_Bkg[ex]->GetBinContent(bin);
				cout << QQQExvGam_Bkg[ex]->GetBinContent(bin) << endl;
				
				if (bin % 2 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
					ContsAvg = CombinedConts/2 * scaling2;
					errors = sqrt(pow(sqrt(CombinedConts)/2 * scaling2,2) + pow(.05*CombinedConts/2 * scaling2,2));

//					cout << "Scale = " << scaling2;
//					cout << "Error = " << errors << endl;
										
					for (int i = bin-1; i < bin+1; i++){

						QQQExvGam_Bkg8000[ex]->SetBinContent(i,ContsAvg);
						QQQExvGam_Bkg8000[ex]->SetBinError(i,errors);

					}

				}
				
			}

			else if (bin > 3000 && bin < 5001){//500 bins (40 keV/bin)
				if ((bin-1) % 250 == 0){
					scaling2 = QQQExvGam[ex]->Integral(bin,bin+249)/QQQExvGam_Bkg[ex]->Integral(bin,bin+249);

				}
				if ((bin-3001) % 5 == 0) CombinedConts = 0;//Resets CombinedConts at 17,33,etc.
				CombinedConts += QQQExvGam_Bkg[ex]->GetBinContent(bin);
				
				if ((bin-3000) % 5 == 0){//when bin is divisible by 16 calc the average and feed it into the background hist
					ContsAvg = CombinedConts/5 * scaling2;
					errors = sqrt(CombinedConts)/5 * scaling2;

					for (int i = bin-4; i < bin + 1; i++){

						QQQExvGam_Bkg8000[ex]->SetBinContent(i,ContsAvg);
						QQQExvGam_Bkg8000[ex]->SetBinError(i,errors);

					}


				}
				
			}
			else if (bin > 5000){//100 bins (80 keV/bin)
				if ((bin-5001) % 10 == 0) CombinedConts = 0;//Resets CombinedConts at 80,160,etc.
				CombinedConts += QQQExvGam_Bkg[ex]->GetBinContent(bin);
				
				if ((bin-5000) % 10 == 0){//when bin is divisible by 16 calc the average and feed it into the background hist
					ContsAvg = CombinedConts/10 * scaling;
					errors = sqrt(CombinedConts)/10 * scaling;

					for (int i = bin-9; i < bin + 1; i++){

						QQQExvGam_Bkg8000[ex]->SetBinContent(i,ContsAvg);
						QQQExvGam_Bkg8000[ex]->SetBinError(i,errors);

					}


				}
			}

			

		}//End the bin for loop

//Put normalizations for the Gamma Gated Background Histograms here!
		for (int i = 0; i < 7; i++){

			for (int bin = 1; bin <= 8000; bin++){ 

				if (bin < 3001){

					if ((bin == 1 || (bin-1) % 200 == 0)){

						if (bin < 238 && (bin+200) > 238) SiscalingGamSingle = GamGated_Si[ex][i]->Integral(bin+200,bin+400)/GamGated_Si_BkgUnScale[ex][i]->Integral(bin+200,bin+400);
						else if (bin+200 <= 1839 && (bin+400) >= 1839) QQQscalingGamSingle = QQQscalingGamSingle;
						else if (bin+200 <= 2556 && (bin+400) >= 2556) QQQscalingGamSingle = QQQscalingGamSingle;
						else QQQscalingGamSingle = GamGated_QQQ[ex][i]->Integral(bin+200,bin+400)/GamGated_QQQ_BkgUnScale[ex][i]->Integral(bin+200,bin+400);
						
						if (bin < 238 && (bin+200) > 238) SiscalingGamSingle = GamGated_Si[ex][i]->Integral(bin+200,bin+400)/GamGated_Si_BkgUnScale[ex][i]->Integral(bin+200,bin+400);
						else if (bin <= 1839 && (bin+200) >= 1839) SiscalingGamSingle = SiscalingGamSingle;
						else if (bin <= 2556 && (bin+200) >= 2556) SiscalingGamSingle = SiscalingGamSingle;
						else SiscalingGamSingle = GamGated_Si[ex][i]->Integral(bin,bin+200)/GamGated_Si_BkgUnScale[ex][i]->Integral(bin,bin+200);
						
					
					}

					if ((bin-1) % 5 == 0){
						CombinedContsQQQ = 0;
						CombinedContsSi = 0; 
					}
					CombinedContsQQQ += GamGated_QQQ_BkgUnScale[ex][i]->GetBinContent(bin);
					CombinedContsSi += GamGated_Si_BkgUnScale[ex][i]->GetBinContent(bin);

				
					if (bin % 5 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
						ContsAvgQQQ = CombinedContsQQQ/5 * QQQscalingGamSingle;
						ContsAvgSi = CombinedContsSi/5 * SiscalingGamSingle;
			
						errorsQQQ = sqrt(pow(sqrt(CombinedContsQQQ)/5 * QQQscalingGamSingle,2) + pow(.05*CombinedContsQQQ/5 * QQQscalingGamSingle,2));
						errorsSi = sqrt(pow(sqrt(CombinedContsSi)/5 * SiscalingGamSingle,2) + pow(.05*CombinedContsSi/5 * SiscalingGamSingle,2));
										
						for (int j = bin-4; j < bin+1; j++){

							GamGated_QQQ_Bkg[ex][i]->SetBinContent(j,ContsAvgQQQ);
							GamGated_QQQ_Bkg[ex][i]->SetBinError(j,errorsQQQ);
							GamGated_Si_Bkg[ex][i]->SetBinContent(j,ContsAvgSi);
							GamGated_Si_Bkg[ex][i]->SetBinError(j,errorsSi);


						}

					}


				}

				if (bin > 3000 && bin < 5001){

					if ((bin == 1 || (bin-1) % 100 == 0)){
						
						QQQscalingGamSingle = GamGated_QQQ[ex][i]->Integral(bin+100,bin+200)/GamGated_QQQ_BkgUnScale[ex][i]->Integral(bin+100,bin+200);
						SiscalingGamSingle = GamGated_Si[ex][i]->Integral(bin+100,bin+200)/GamGated_Si_BkgUnScale[ex][i]->Integral(bin+100,bin+200);
						
					}

					if ((bin-1) % 50 == 0){
						CombinedContsQQQ = 0;
						CombinedContsSi = 0; 
					}
					CombinedContsQQQ += GamGated_QQQ_BkgUnScale[ex][i]->GetBinContent(bin);
					CombinedContsSi += GamGated_Si_BkgUnScale[ex][i]->GetBinContent(bin);

				
					if (bin % 50 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
						ContsAvgQQQ = CombinedContsQQQ/50 * QQQscalingGamSingle;
						ContsAvgSi = CombinedContsSi/50 * SiscalingGamSingle;
			
						errorsQQQ = sqrt(pow(sqrt(CombinedContsQQQ)/50 * QQQscalingGamSingle,2) + pow(.05*CombinedContsQQQ/50 * QQQscalingGamSingle,2));
						errorsSi = sqrt(pow(sqrt(CombinedContsSi)/50 * SiscalingGamSingle,2) + pow(.05*CombinedContsSi/50 * SiscalingGamSingle,2));
										
						for (int j = bin-49; j < bin+1; j++){

							GamGated_QQQ_Bkg[ex][i]->SetBinContent(j,ContsAvgQQQ);
							GamGated_QQQ_Bkg[ex][i]->SetBinError(j,errorsQQQ);

							GamGated_Si_Bkg[ex][i]->SetBinContent(j,ContsAvgSi);
							GamGated_Si_Bkg[ex][i]->SetBinError(j,errorsSi);

						}

					}


				}

				if (bin > 5000 && bin < 8001){

					if ((bin == 1 || (bin-1) % 100 == 0)){
						
						QQQscalingGamSingle = GamGated_QQQ[ex][i]->Integral(bin+100,bin+200)/GamGated_QQQ_BkgUnScale[ex][i]->Integral(bin+100,bin+200);
						SiscalingGamSingle = GamGated_Si[ex][i]->Integral(bin+100,bin+200)/GamGated_Si_BkgUnScale[ex][i]->Integral(bin+100,bin+200);
						
					}

					if ((bin-1) % 100 == 0){
						CombinedContsQQQ = 0;
						CombinedContsSi = 0; 
					}
					CombinedContsQQQ += GamGated_QQQ_BkgUnScale[ex][i]->GetBinContent(bin);
					CombinedContsSi += GamGated_Si_BkgUnScale[ex][i]->GetBinContent(bin);

				
					if (bin % 100 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
						ContsAvgQQQ = CombinedContsQQQ/100 * QQQscalingGamSingle;
						ContsAvgSi = CombinedContsSi/100 * SiscalingGamSingle;
			
						errorsQQQ = sqrt(pow(sqrt(CombinedContsQQQ)/100 * QQQscalingGamSingle,2) + pow(.05*CombinedContsQQQ/100 * QQQscalingGamSingle,2));
						errorsSi = sqrt(pow(sqrt(CombinedContsSi)/100 * SiscalingGamSingle,2) + pow(.05*CombinedContsSi/100 * SiscalingGamSingle,2));
										
						for (int j = bin-99; j < bin+1; j++){

							GamGated_QQQ_Bkg[ex][i]->SetBinContent(j,ContsAvgQQQ);
							GamGated_QQQ_Bkg[ex][i]->SetBinError(j,errorsQQQ);

							GamGated_Si_Bkg[ex][i]->SetBinContent(j,ContsAvgSi);
							GamGated_Si_Bkg[ex][i]->SetBinError(j,errorsSi);


						}
					}


				}

			}

		}

		for (int i = 0; i < 9; i++){

			CombinedContsQQQ = 0;
			CombinedContsSi = 0;

			if (i == 0){
				g1 = 238;
				g2 = 1297;
			}
			else if (i == 1){
				g1 = 238;
				g2 = 2556;
			}
			else if (i == 2){
				g1 = 238;
				g2 = 4362;
			}
			else if (i == 3){
				g1 = 238;
				g2 = 1840;
			}
			else if (i == 4){
				g1 = 238;
				g2 = 4140;
			}
			else if (i == 5){
				g1 = 275;
				g2 = 1233;
			}
			else if (i == 6){
				g1 = 275;
				g2 = 1340;
			}
			else if (i == 7){
				g1 = 275;
				g2 = 2632;
			}
			else if (i == 8){
				g1 = 1840;
				g2 = 2556;
			}

			for (int bin = 1; bin <= 8000; bin++){ 

				if (bin < 3001){

					if ((bin == 1 || (bin-1) % 500 == 0)){

						if (bin < g1 && bin+500 > g1){
							QQQscalingGamDouble = (DblGamGated_QQQ[ex][i]->Integral(bin,g1-50)+DblGamGated_QQQ[ex][i]->Integral(g1+50,bin+500))/(DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(bin,g1-50)+DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(g1+50,bin+500));

							SiscalingGamDouble = (DblGamGated_Si[ex][i]->Integral(bin,g1-50)+DblGamGated_Si[ex][i]->Integral(g1+50,bin+500))/(DblGamGated_Si_BkgUnScale[ex][i]->Integral(bin,g1-50)+DblGamGated_Si_BkgUnScale[ex][i]->Integral(g1+50,bin+500));

						}

						else if (bin < g2 && bin+500 > g2){
							QQQscalingGamDouble = (DblGamGated_QQQ[ex][i]->Integral(bin,g2-50)+DblGamGated_QQQ[ex][i]->Integral(g2+50,bin+500))/(DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(bin,g2-50)+DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(g2+50,bin+500));

							SiscalingGamDouble = (DblGamGated_Si[ex][i]->Integral(bin,g2-50)+DblGamGated_Si[ex][i]->Integral(g2+50,bin+500))/(DblGamGated_Si_BkgUnScale[ex][i]->Integral(bin,g2-50)+DblGamGated_Si_BkgUnScale[ex][i]->Integral(g2+50,bin+500));

						}
						
						else{
							QQQscalingGamDouble = DblGamGated_QQQ[ex][i]->Integral(bin,bin+500)/DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(bin,bin+500);

							SiscalingGamDouble = DblGamGated_Si[ex][i]->Integral(bin,bin+500)/DblGamGated_Si_BkgUnScale[ex][i]->Integral(bin,bin+500);

						}
						
					
					}

					if ((bin-1) % 100 == 0){
						CombinedContsQQQ = 0;
						CombinedContsSi = 0; 
					}
					CombinedContsQQQ += DblGamGated_QQQ_BkgUnScale[ex][i]->GetBinContent(bin);
					CombinedContsSi += DblGamGated_Si_BkgUnScale[ex][i]->GetBinContent(bin);

				
					if (bin % 100 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
						ContsAvgQQQ = CombinedContsQQQ/100 * QQQscalingGamDouble;
						ContsAvgSi = CombinedContsSi/100 * SiscalingGamDouble;
			
						errorsQQQ = sqrt(pow(sqrt(CombinedContsQQQ)/100 * QQQscalingGamDouble,2) + pow(.05*CombinedContsQQQ/100 * QQQscalingGamDouble,2));
						errorsSi = sqrt(pow(sqrt(CombinedContsSi)/100 * SiscalingGamDouble,2) + pow(.05*CombinedContsSi/100 * SiscalingGamDouble,2));
										
						for (int j = bin-99; j < bin+1; j++){

							DblGamGated_QQQ_Bkg[ex][i]->SetBinContent(j,ContsAvgQQQ);
							DblGamGated_QQQ_Bkg[ex][i]->SetBinError(j,errorsQQQ);
							DblGamGated_Si_Bkg[ex][i]->SetBinContent(j,ContsAvgSi);
							DblGamGated_Si_Bkg[ex][i]->SetBinError(j,errorsSi);


						}

					}


				}

				if (bin > 3000 && bin < 8001){

					if ((bin == 1 || (bin-1) % 1000 == 0)){

						if (bin < g2 && bin+1000 > g2){
							QQQscalingGamDouble = (DblGamGated_QQQ[ex][i]->Integral(bin,g2-50)+DblGamGated_QQQ[ex][i]->Integral(g2+50,bin+1000))/(DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(bin,g2-50)+DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(g2+50,bin+1000));

							SiscalingGamDouble = (DblGamGated_Si[ex][i]->Integral(bin,g2-50)+DblGamGated_Si[ex][i]->Integral(g2+50,bin+1000))/(DblGamGated_Si_BkgUnScale[ex][i]->Integral(bin,g2-50)+DblGamGated_Si_BkgUnScale[ex][i]->Integral(g2+50,bin+1000));

						}
						
						else{
							QQQscalingGamDouble = DblGamGated_QQQ[ex][i]->Integral(bin,bin+1000)/DblGamGated_QQQ_BkgUnScale[ex][i]->Integral(bin,bin+1000);

							SiscalingGamDouble = DblGamGated_Si[ex][i]->Integral(bin,bin+1000)/DblGamGated_Si_BkgUnScale[ex][i]->Integral(bin,bin+1000);

						}
						
					
					}

					if ((bin-1) % 200 == 0){
						CombinedContsQQQ = 0;
						CombinedContsSi = 0; 
					}
					CombinedContsQQQ += DblGamGated_QQQ_BkgUnScale[ex][i]->GetBinContent(bin);
					CombinedContsSi += DblGamGated_Si_BkgUnScale[ex][i]->GetBinContent(bin);

				
					if (bin % 200 == 0){//on the even values of bin, calculate the average and feed it into the Background hist.
						ContsAvgQQQ = CombinedContsQQQ/200 * QQQscalingGamDouble;
						ContsAvgSi = CombinedContsSi/200 * SiscalingGamDouble;
			
						errorsQQQ = sqrt(pow(sqrt(CombinedContsQQQ)/200 * QQQscalingGamDouble,2) + pow(.05*CombinedContsQQQ/200 * QQQscalingGamDouble,2));
						errorsSi = sqrt(pow(sqrt(CombinedContsSi)/200 * SiscalingGamDouble,2) + pow(.05*CombinedContsSi/200 * SiscalingGamDouble,2));
										
						for (int j = bin-199; j < bin+1; j++){

							DblGamGated_QQQ_Bkg[ex][i]->SetBinContent(j,ContsAvgQQQ);
							DblGamGated_QQQ_Bkg[ex][i]->SetBinError(j,errorsQQQ);

							DblGamGated_Si_Bkg[ex][i]->SetBinContent(j,ContsAvgSi);
							DblGamGated_Si_Bkg[ex][i]->SetBinError(j,errorsSi);

						}

					}


				}


			}

		}




	}//End for the Ex loop

	for (int bin=1; bin<=1000; bin++){
		average = (gam_totBack->GetBinContent(bin) + gam_totBack2->GetBinContent(bin)) / 2;

		gam_totBackAvg->SetBinContent(bin,average);

		average2 = (gamExBack->GetBinContent(bin) + gamExBack2->GetBinContent(bin)) / 2;

		gamExBackAvg->SetBinContent(bin,average2);
	}

	int bincounter = 1;

	for (int bin = 1; bin <= 1000; bin++){
		//FYI 16=8000/500
		ReducedContent = gam_totBackAvg->GetBinContent(bin) / 8;
		ReducedContent2 = gamExBackAvg->GetBinContent(bin) / 8;

		//for (int bin2 = bincounter; bin2 <= (bincounter+15); bin2++){
		for (int bin2 = bincounter; bin2 <= (bincounter+7); bin2++){

			gam_totBackAvg8000->SetBinContent(bin2,ReducedContent);
			gamExBackAvg8000->SetBinContent(bin2,ReducedContent2);
			

		}
		
		//Set the bin conts for the 4k and 8k histograms here
/*
		for (int ex = 0; ex < RealExLoopEnd; ex++){
			//less than 501 means 0 to 4000
			if (bin < 501) BinConts = QQQExvGam_Bkg4k1000[ex]->GetBinContent(bin) / 8;
			else if (bin > 500) BinConts = QQQExvGam_Bkg8k1000[ex]->GetBinContent(bin) / 8;

			for (int bin2 = bincounter; bin2 <= (bincounter+7); bin2++){

				QQQExvGam_Bkg8000[ex]->SetBinContent(bin2,BinConts);
			
			}

		}
*/
		bincounter += 8;
	}
/*
	int bincounter2 = 1;

	for (int bin = 1; bin <= 100; bin++){

		for (int ex = 0; ex < RealExLoopEnd; ex++){
			//less than 501 means 0 to 4000
			if (bin < 51) BinConts = QQQExvGam_Bkg4k1000[ex]->GetBinContent(bin) / 80;
			else if (bin > 50) BinConts = QQQExvGam_Bkg8k1000[ex]->GetBinContent(bin) / 80;

			for (int bin2 = bincounter2; bin2 <= (bincounter2+79); bin2++){

				QQQExvGam_Bkg8000[ex]->SetBinContent(bin2,BinConts);
			
			}

		}

		bincounter2 += 80;




	}
*/
	//Ratio histograms created here.

	double RatioError = 0;

	for (int ex = 0; ex < RealExLoopEnd; ex++){

		hist->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/Ratio_Hists");

		TH1D *ratio = (TH1D*)QQQExvGam[ex]->Clone("ratio_" + TString(std::to_string((int)ex+4)) + "_" + TString(std::to_string((int)ex+4 + ExWidth)));

		ratio->Divide(QQQExvGam_Bkg8000[ex]);
//ratio->Add(QQQExvGam_Bkg8000[ex],-1);
		RatioVec.push_back(ratio);

		for (int bin = 1; bin <=8000; bin++){

			double Bkg = (double)QQQExvGam_Bkg8000[ex]->GetBinContent(bin);
			double Sig = (double)QQQExvGam[ex]->GetBinContent(bin);

			if (Bkg != 0) RatioError = sqrt(pow(1/(Bkg)*sqrt(Sig),2)+pow((Sig/pow(Bkg,2))*sqrt(Bkg),2));
			else if (Bkg == 0) RatioError = 1;
//			if (Bkg != 0) RatioError = sqrt(pow((Bkg)*sqrt(Sig),2)+pow((Sig)*sqrt(Bkg),2));

			RatioVec[ex]->SetBinError(bin, RatioError);

			//if (ex == 23 && (Sig/Bkg - RatioError) >=1) std::cout << bin << std::endl; 

		}

	}

	double gamExInt = gamExGated->Integral();
	double gamExInt2 = (gamExBack->Integral() + gamExBack2->Integral())/2;

	double gam_totInt = gam_tot->Integral();
	double gam_totInt2 = (gam_totBack->Integral() + gam_totBack2->Integral())/2;
	
	double ScaleFactor_tot = gam_totInt/gam_totInt2;
	double ScaleFactorEx = gamExInt/gamExInt2;

	gam_totBackAvg8000->Scale(ScaleFactor_tot);
	gamExBackAvg8000->Scale(ScaleFactorEx);

	gam_tot2->Add(gam_totBackAvg8000,-1);
	gamExGated2->Add(gamExBackAvg8000,-1);

	D4_E_Gam_Gated->Add(D4_E_Gated_Back,-1);
	D5_E_Gam_Gated->Add(D5_E_Gated_Back,-1);
	D7_E_Gam_Gated->Add(D7_E_Gated_Back,-1);
	D8_E_Gam_Gated->Add(D8_E_Gated_Back,-1);
	D9_E_Gam_Gated->Add(D9_E_Gated_Back,-1);
	D10_E_Gam_Gated->Add(D10_E_Gated_Back,-1);

	SX3_Gam_Gated->Add(SX3_Gated_Back,-1);
	SX3_Q_Gam_Gated->Add(SX3_Q_Gated_Back,-1);
	SX3Ex->Add(SX3ExBack,-1);

	E_v_Ang->Add(E_v_AngBack,-1);

	double g238Int = gam238->Integral();
	double g275Int = gam275->Integral();
	double g1233Int = gam1233->Integral();
	double g1297Int = gam1297->Integral();
	double g1840Int = gam1840->Integral();
	double g2556Int = gam2556->Integral();

	double g238BackInt = gam238_Back->Integral();
	double g275BackInt = gam275_Back->Integral();
	double g1233BackInt = gam1233_Back->Integral();
	double g1297BackInt = gam1297_Back->Integral();
	double g1840BackInt = gam1840_Back->Integral();
	double g2556BackInt = gam2556_Back->Integral();

	double g238Scale = g238Int/g238BackInt;
	double g275Scale = g275Int/g275BackInt;
	double g1233Scale = g1233Int/g1233BackInt;
	double g1297Scale = g1297Int/g1297BackInt;
	double g1840Scale = g1840Int/g1840BackInt;
	double g2556Scale = g2556Int/g2556BackInt;

	gam238_Back->Scale(g238Scale);
	gam275_Back->Scale(g275Scale);
	gam1233_Back->Scale(g1233Scale);
	gam1297_Back->Scale(g1297Scale);
	gam1840_Back->Scale(g1840Scale);
	gam2556_Back->Scale(g2556Scale);


//Probably don't want to do this, if the bin content is negative just say it indicates less background than expected in that region. ***
//	for (int bin=1; bin<=8000; bin++){
//		if (gamExGated2->GetBinContent(bin) < 0) gamExGated2->SetBinContent(bin,0);
//	}

	
	std::cout << std::endl << "The number of runs analyzed was: " << numruns << std::endl;
	std::cout << "Writing data to " << RootFile << std::endl;
	hist->Write();
	hist->Close();

	logFile.close();

	std::cout << gcount1 << " * " << gcount2 << std::endl;

	t.Stop();
	t.Print();

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






				//if (stripE1 ==1 && stripdE==0 && j==0) QQQDAtot->Fill(dE*0.000529+1.23 + E1*.0053+7.8547);

				//if (dE < 911 && stripdE == 0 && (stripE1 == 0 || stripE1 == 1)){
				//	QQQDAdE0->Fill(E1);
					
				//}

				//if (E1 > 586 && E1 < 612 && stripdE == 0 && (stripE1 == 0 || stripE1 == 1)) gate++;







	//strip number angle assignments.
//	double stripangle[20][2];
	
	//cubic energy loss parameters through the Al blocker. In the file, Column 1: Angle in Deg, Column 2: Angle in Rad, Column 3,4,5,6 are the parameters Ax^3+Bx^2+Cx+D in that order.
//	double energyloss[12][6];



*/

//gamma data for loop for timing histograms 
/*
					for (unsigned int w = 0; w < gam2->size();w++){

						gamEn = pow(gam2->at(w).en,2)*gamcalparams[gam2->at(w).num][0] + gam2->at(w).en*gamcalparams[gam2->at(w).num][1] + gamcalparams[gam2->at(w).num][2]; 

						timediff = (double)gam2->at(w).time - (double)si2->at(i).TimestampMaxLayer(0,false);
				
						if (gamEn > 505 && gamEn < 515) gam511vtime->Fill(timediff);
						if (gamEn > 490 && gamEn < 500) gam511vtimeBACK->Fill(timediff);

						if (gamEn > 232 && gamEn < 239) gam238vtime->Fill(timediff);
						if (gamEn > 225 && gamEn < 232) gam238vtimeBACK->Fill(timediff);

						if (gamEn > 1223 && gamEn < 1241) gam1233vtime->Fill(timediff);
						if (gamEn > 1205 && gamEn < 1223) gam1233vtimeBACK->Fill(timediff);

						if (gamEn > 1628 && gamEn < 1639) gam1633vtime->Fill(timediff);
						if (gamEn > 1675 && gamEn < 1686) gam1633vtimeBACK->Fill(timediff);

						gam_DA->Fill(timediff,stripdE);
						if ((timediff < 216 && timediff > 176) || (timediff < 430 && timediff > 400)) timegate++;
						if (Ex19Ne > 5.15) TimeHist->Fill(timediff);

						gamTime->Fill(timediff,gamEn);

						if ( (73 < timediff && timediff < 104) || (190 < timediff && timediff < 217) || (416 < timediff && timediff < 440)) QQQDAvsGam->Fill(Ex19Ne,gamEn); 

					}
*/

