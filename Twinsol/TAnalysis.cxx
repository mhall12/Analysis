//Matthew Hall
//Twinsol 19F(3He,t) analysis code. Experiment run in June 2016.

#include "TAnalysis.h"

void histfill(string runfile){
	std::cout << "Run file " << runfile << " is now being analyzed." << std::endl;
	
	datafile = TFile::Open("/media/ds1/19F3HeTwinsol/rootfiles/" + TString(runfile));
	
	newtree = (TTree*)datafile->Get("t2");
	double ene2[200] = {};
	long long int timefull2[200] = {};

	double dESBcalE;
	double TotE = 0;
	double GamCalE;
	double ReGamCalE;

	double E1calE[5] = {};
	double dE2calE[5] = {};

	long long int tdiff;

	int TritonGate = 0;
	int TritonGate64 = 0;

	//Calibration Parameters used to fix the Rough Calibration and make it agree with the Gammasphere calibration
	double GamReCal[2] = {.9702, 38.871}; 

	newtree->SetBranchAddress("ene",&ene2);
	newtree->SetBranchAddress("timefull",&timefull2);

	nEntries = newtree->GetEntries();

	for (int evt = 0; evt < nEntries; evt++){

		TritonGate = 0;
		TritonGate64 = 0;

		for (int i = 0; i < 5; i++){
			E1calE[i] = 0;
			dE2calE[i] = 0;
		}

		newtree->GetEntry(evt);

		if (evt % 100000 == 0) std::cout << "Processing event number " << evt << " of " << nEntries << std::endl;


		for (int i = 0; i<48; i++){

			if (ene2[i] > 0) RawData[i]->Fill(ene2[i]);

		}

		dESBcalE = ene2[35] * dESBcal[0][0] + dESBcal[0][1];

		if (runmode == 2 && ene2[35] > 0) dESB->Fill(dESBcalE); 

		if (runmode != 0){
			for (int i = 0; i < 5; i++){
				if (ene2[i+37] > 0) dE2calE[i] = ene2[i+37] * dE2cal[i][0] + dE2cal[i][1];
				if (ene2[i+42] > 0) E1calE[i] = ene2[i+42] * E1cal[i][0] + E1cal[i][1];			

				if (ene2[i+37] > 0) dE2hists[i]->Fill(dE2calE[i]);
				if (ene2[i+42] > 0) E1hists[i]->Fill(E1calE[i]);

				SBvdE2[i]->Fill(dE2calE[i],dESBcalE);
				
				//for (int j = 0; j < 4; j++){
				//	if (i < 4 && dE2calE[i] != 0 && E1calE[j] != 0){
				//		TotE = dE2calE[i] + dE2calE[j];
					//Only Picking out the backside of dE2
					if (i == 4){
						TotE = dE2calE[i] + dESBcalE;
						SBvTotE->Fill(TotE,dESBcalE);
					}

				//}

				if (TotE > 9.84 && TotE < 12.65 && dESBcalE > 1.25 && dESBcalE < 2.2){
					TritonGate++;

					for (int j = 0; j < 16; j++){
						GamCalE = ene2[j]*GamCalParams[j][0] + GamCalParams[j][1];

						tdiff = timefull2[j] - timefull2[i+37];

					//	if (ene2[j] > 0) std::cout << "Gamma Time: " << timefull2[j] << " Si Time: " << timefull2[i+37] << std::endl; 

						if (GamCalE > 0) TimeDiff->Fill(tdiff);

					}
				}

				if (TotE > 9.9 && TotE < 10.7 && dESBcalE > 1.25 && dESBcalE < 2.2) TritonGate64++;

			}
		
			for (int i = 0; i < 16; i++){
				GamCalE = ene2[i]*GamCalParams[i][0] + GamCalParams[i][1];
				ReGamCalE = GamCalE*0.9702 + 38.871;

				if (ReGamCalE > 40){
					GamCalHists[i]->Fill(ReGamCalE);
					GamTot->Fill(ReGamCalE);
				
					if (TritonGate > 0) GamTotT->Fill(ReGamCalE);
					if (TritonGate64 > 0) GamTotT64->Fill(ReGamCalE);
					if ((i == 0 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12 || i == 13) && TritonGate64 > 0) GoodGamTotT64->Fill(ReGamCalE);
				}
			}
		}
	}


}

void MakeMyHists(){

	//runmode = 0 is for calibration, runmode = 1 is for 8.5 MV data, runmode = 2 is for 7 MV data;
	runmode = 2;
	
	if (runmode == 0){
		hist = TFile::Open("CalibrationData60Co.root","RECREATE");
		std::cout << "Calibration Run Mode. CalibrationData.root will be recreated." << std::endl;
	}
	if (runmode == 1){
		hist = TFile::Open("DataHighE.root","RECREATE");
		std::cout << "Data with 8.5 MV on the Tandem. DataHighE.root will be recreated." << std::endl;
	}
	if (runmode == 2){
		hist = TFile::Open("DataLowEtest.root","RECREATE");
		std::cout << "Data with 7.0 MV on the Tandem. DataLowE.root will be recreated." << std::endl;
	}
	
	ifstream DataFiles("textfiles/runfiles.txt");
	ifstream SiCal("textfiles/SiCal.txt");
	ifstream GamCal("textfiles/GamCal.txt");

	//Si calibrations filled here
	for (int i = 0; i < 16; i++){
		if (i < 5) SiCal >> dE1cal[i][0] >> dE1cal[i][1];
		if (i == 5) SiCal >> dESBcal[0][0] >> dESBcal[0][1];
		if (i > 5 && i < 11) SiCal >> dE2cal[i-6][0] >> dE2cal[i-6][1];
		if (i > 10 && i < 16) SiCal >> E1cal[i-11][0] >> E1cal[i-11][1];


	}

	Raw_Data = hist->mkdir("Raw_Data");

	Raw_Data->cd();
	int nbins = 7000;


	for (int i = 0; i < 48; i++){
		if (i > 15) nbins = 2000;
		string RawName = "ene" + std::to_string(i);
		TH1D *h0 = new TH1D(TString(RawName), "ene[" + TString(std::to_string(i)) + "]", nbins,0,35000);

		RawData.push_back(h0);

	}


	if (runmode == 2 || runmode == 1){
		Si_Detectors = hist->mkdir("Si_Detectors");
		Clovers = hist->mkdir("Clovers");
		Single_Channel_Histograms = hist->mkdir("Si_Detectors/Single_Channel_Histograms");
		Single_Gamma_Dets = hist->mkdir("Clovers/Single_Gamma_Dets");
		Timing_Histograms = hist->mkdir("Timing_Histograms");

		hist->cd("Si_Detectors/Single_Channel_Histograms");
		
		if (runmode == 2) dESB = new TH1D("dESB","dE1 Single SB Calibrated",2000,0,20);

		for (int i = 0; i < 5; i++){

			TH1D *h1 = new TH1D("E1_" + TString(std::to_string(i)), "E1 Detector Channel " + TString(std::to_string(i)) + " Calibrated", 2000,0,20);
			E1hists.push_back(h1);

			TH1D *h2 = new TH1D("dE2_" + TString(std::to_string(i)), "dE2 Detector Channel " + TString(std::to_string(i)) + " Calibrated", 2000,0,20);
			dE2hists.push_back(h2);
		}

		PIDs = hist->mkdir("Si_Detectors/PIDs");

		hist->cd("Si_Detectors/PIDs");
		
		for (int i = 0; i<5; i++){
			TH2D *h3 = new TH2D("SBvdE2_" + TString(std::to_string(i)), "Surface Barrier dE vs dE2 Strip " + TString(std::to_string(i)), 2000,0,20,2000,0,20);
			SBvdE2.push_back(h3);
		}


		SBvTotE = new TH2D("SBvTotE", "Surface Barrier dE vs Total E", 2000,0,20,2000,0,20);

		Clovers->cd();

		GamTot = new TH1D("GamTot","Total Calibrated Clovershare Spectrum",8000,0,8000);

		GamTotT = new TH1D("GamTotT","Total Calibrated Clovershare Spectrum Triton Gated",8000,0,8000);

		GamTotT64 = new TH1D("GamTotT64","Total Calibrated Clovershare Spectrum 6.4 MeV Triton Gated",8000,0,8000);

		GoodGamTotT64 = new TH1D("GoodGamTotT64","Total Calibrated Clovershare Spectrum 6.4 MeV Triton Gated",8000,0,8000);

		hist->cd("Clovers/Single_Gamma_Dets");

		int CloverDetNo;
		int CloverNo;
		
		for (int i = 0; i < 16; i++){

			GamCal >> GamCalParams[i][0] >> GamCalParams[i][1];

			if (i < 4){
				CloverDetNo = 35;
				CloverNo = i;
			}

			if (i > 3 && i < 8){
				CloverDetNo = 31;
				CloverNo = i - 4;
			}

			if (i > 7 && i < 12){
				CloverDetNo = 18;
				CloverNo = i - 8;
			}
			
			if (i > 11){
				CloverDetNo = 7;
				CloverNo = i - 12;
			}
		
			TH1D *h4 = new TH1D("gam_" + TString(std::to_string(CloverDetNo)) + "_" + TString(std::to_string(CloverNo)), "Detector #" + TString(std::to_string(CloverDetNo)) + " Clover #" + TString(std::to_string(CloverNo)), 8000, 0, 8000);

			GamCalHists.push_back(h4);


		}

		hist->cd("Timing_Histograms");

		TimeDiff = new TH1D("TimeDiff","Timing Difference Between Gamma and Si Dets",400,-10000000,10000000);

		

		

	}


	string filebuffer;


	for (int i=0; i<181;i++){
		DataFiles >> filebuffer;		
		
		if (runmode == 0 && i > 5 && i < 12) histfill(filebuffer);
	
		if (runmode == 1 && i > 16 && i < 80) histfill(filebuffer);

//		if (runmode == 2 && i > 85 && i < 171) histfill(filebuffer);

		if (runmode == 2 && i > 85 && i < 95) histfill(filebuffer);


	}

	hist->Write();
	hist->Close();


	DataFiles.close();
	SiCal.close();



}









/*


	for (int run=0; run<200; run++){
		
		bool b = std::ifstream('filename').good();

	}


	int num = 0;
	string filename;
	filename = "run0155-00.root";

	bool b = std::ifstream(filename.c_str()).good();

	if (b) num = 1;

	cout << "num is " << num << endl;

	return 0;



*/











