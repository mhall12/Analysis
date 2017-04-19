//Matthew Hall
//Analysis code for 19F(3He,t)19Ne performed at Argonne National Lab 9/2015.

#include "GamAnalysis.h"

void histfill(string file, ofstream &log1){
	
	std::cout << "/media/ds1/GamRootFiles/" + TString(file) << endl;
	//the code opens the file here
	data = TFile::Open("/media/ds1/GamRootFiles/" + TString(file));
	//trees->cd();

	//the data from trees/god is placed into a container gam2 and si2.
	//nt = (TTree*)data->Get("trees/god");
	nt = (TTree*)data->Get("god");
	gam2={};
	si2={};

	nt->SetBranchAddress("gam",&gam2);
	nt->SetBranchAddress("si",&si2);
	
	nEntries = nt->GetEntries();

	int g238 = 0; //238 keV in 19Ne
	int g275 = 0; //275 keV in 19Ne
	int g1233 = 0; //1232 keV in 19Ne
	int g1297 = 0;
	int g1840 = 0;
	int g2556 = 0;
	int g1340 = 0;
	int g1584 = 0;

	int timegate = 0;
	double gamEn;
	double gamEn2;

	int BadGams[19] = {7,21,26,27,28,31,35,39,47,48,50,56,62,63,68,87,98,105,110};

	double timediff;

	std::vector<double> gam511;


	//In the TimeDiff vector, index 1 refers to the Gamma and index 2 refers to the Si event
	std::vector<std::vector<double>> TimeDiff;

	//Saves the Gamma Index number for a time that is in the time gate
	std::vector<int> TimingGammaIndex;
	

	log1 << file << " Number of Entries: " << nEntries << std::endl;


	for (int evt=0;evt<nEntries;evt++){
		//Reset the gates to 0 for each entry of the tree.

		g238 = 0; //238 keV in 19Ne
		g275 = 0; //275 keV in 19Ne
		g1233 = 0; //1232 keV in 19Ne
		g1297 = 0;
		g1840 = 0;
		g2556 = 0;
		g1340 = 0;
		g1584=0;

		gam511.clear();

		nt->GetEntry(evt);
		if(evt % 100000 == 0){
			cout << file << ": Processing event number "<< evt << " of " << nEntries << " \r";
			std::cout.flush();
		}

		//We'll use the for loop here to draw gamma gates.

		for (unsigned int i = 0; i < gam2->size();i++){
			TimingGammaIndex.push_back(0);
		}

		for (unsigned int i = 0; i < gam2->size();i++){
			//if (gam2->at(i).en*.81 > 236 && gam2->at(i).en*.81 < 242) gamgate++;
			gamEn = pow(gam2->at(i).en,2)*gamcalparams[gam2->at(i).num][0] + gam2->at(i).en*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 

			if (gamEn >= 236 && gamEn <= 240) g238++;
			if (gamEn >= 272 && gamEn <= 278) g275++;
			if (gamEn >= 1224 && gamEn <= 1238) g1233++;
			if (gamEn >= 1290 && gamEn <= 1304) g1297++;
			if (gamEn >= 1335 && gamEn <= 1345) g1340++;
			if (gamEn >= 1835 && gamEn <= 1845) g1840++;
			if (gamEn >= 2550 && gamEn <= 2561) g2556++;
			if (gamEn >= 1579 && gamEn <= 1589) g1584++;

			for (unsigned int j = 0; j < gam2->size();j++){
				gamEn2 = pow(gam2->at(j).en,2)*gamcalparams[gam2->at(j).num][0] + gam2->at(j).en*gamcalparams[gam2->at(j).num][1] + gamcalparams[gam2->at(j).num][2]; 
				timediff = (double)gam2->at(i).time - (double)gam2->at(j).time;


				if (j > i){				


					TDiffGam->Fill(timediff);

					if (timediff > -12){
						TimingGammaIndex[i]++;
						TimingGammaIndex[j]++;
					}

					if (gamEn > 235 && gamEn < 241){
						TDiffGam238->Fill(timediff);

						if (gamEn2 > 1276 && gamEn2 < 1314) TDiff238vs1297->Fill(timediff);

						if (gamEn2 > 1224 && gamEn2 < 1238) TDiff275vs1233->Fill(timediff);


					}//closes gam 238 if

				}//closes if j>i

				//if (i != j && timediff == 0) gamvgam->Fill(gamEn,gamEn2);
			
			}//closes j for loop


		}//closes i for loop



		for (unsigned int i = 0; i < gam2->size();i++){
			
			gamEn = pow(gam2->at(i).en,2)*gamcalparams[gam2->at(i).num][0] + gam2->at(i).en*gamcalparams[gam2->at(i).num][1] + gamcalparams[gam2->at(i).num][2]; 

			gam_ind->Fill(gamEn,gam2->at(i).num);

			if (TimingGammaIndex[i]>0){
				gam_tot->Fill(gamEn);

				//Fill the gated gammasphere histograms here
				
				if (g238 > 0 && g2556 > 0) gam238->Fill(gamEn);
				if (g275 > 0) gam275->Fill(gamEn);
				if (g1233 > 0) gam1233->Fill(gamEn);
				if (g1297 > 0) gam1297->Fill(gamEn);
				if (g1840 > 0) gam1840->Fill(gamEn);

				if (g238 > 0 && g1840 > 0 && g2556 > 0) g64cascade->Fill(gamEn);

				if (g275 > 0 && g1233 > 0) g275and1233->Fill(gamEn);
				if (g238 > 0 && g1297 > 0) g238and1297->Fill(gamEn);
				if (g238 > 0 && g2556 > 0) g238and2556->Fill(gamEn);
				if (g238 > 0 && g1340 > 0) g238and1340->Fill(gamEn);
				if (g2556 > 0 && g1840 > 0) g2556and1840->Fill(gamEn);

				if (g238 > 0 && g1584 > 0 && g2556 > 0) g238and2556and1584->Fill(gamEn);
			}
			

		}

		timegate = 0;
		TimingGammaIndex.clear();

	}



	
	
	std::cout << file << " will now be closed." << std::endl; 
	gam2->clear();
	si2->clear();
	data->Close();


}

//********************************************************************************************************//


void MakeMyHists(){

	int stripnum = 32;
	//the hist file is opened here for writing
	hist = TFile::Open("GammaOnly.root","RECREATE");
	std::ofstream logFile("GammaOnly.log");

	//directories for the histograms are created. 
	Gamma_Hists = hist->mkdir("Gamma_Hists");
		Gammasphere_Hists = hist->mkdir("Gamma_Hists/Gammasphere_Histograms");
		Gamma_Gated_Hists = hist->mkdir("Gamma_Hists/Gamma_Gated_Histograms");
	Timing_Spectra = hist->mkdir("Timing_Spectra");

	hist->cd("Gamma_Hists/Gammasphere_Histograms");
	gam_ind = new TH2D("gam_ind","Individual Gammasphere Detectors",10000,0,10000,111,0,111);
	gam_tot = new TH1D("gam_tot","Summed Gammasphere Spectrum",8000,0,8000);


	gam_ind->GetXaxis()->SetTitle("Channel Number");
	gam_ind->GetYaxis()->SetTitle("Gammasphere Detector Number");
	gam_ind->GetXaxis()->CenterTitle();
	gam_ind->GetYaxis()->CenterTitle();

	gam_tot->GetXaxis()->SetTitle("Energy (keV)");
	gam_tot->GetYaxis()->SetTitle("Counts");
	gam_tot->GetXaxis()->CenterTitle();
	gam_tot->GetYaxis()->CenterTitle();

	gamvgam = new TH2D("gamvgam","Gamma Energy vs Coincident Gamma Energy",8000,0,8000,8000,0,8000);

	Timing_Spectra->cd();
	TDiffGam238 = new TH1D("TDiffGam238","Timing Difference Between 238 keV Gamma and Others",4500,-1000,500);
	TDiffGam = new TH1D("TDiffGam","Timing Difference Between Coincident Gammas",2000,-1000,1000);

	TDiff238vs1297 = new TH1D("TDiff238vs1297","Timing Difference Between 238 keV and 1297 keV",2000,-1000,1000);

	TDiff275vs1233 = new TH1D("TDiff275vs1233","Timing Difference Between 275 keV and 1233 keV",2000,-1000,1000);

	hist->cd("Gamma_Hists/Gamma_Gated_Histograms");
	gam238 = new TH1D("gam238","Gammas Gated on 237 keV Peak",8000,0,8000);
	gam275 = new TH1D("gam275","Gammas Gated on 272 keV Peak",8000,0,8000);
	gam1233 = new TH1D("gam1233","Gammas Gated on 1233 keV Peak",8000,0,8000);
	gam1297 = new TH1D("gam1297","Gammas Gated on 1297 keV Peak",8000,0,8000);
	gam1840 = new TH1D("gam1840","Gammas Gated on 1840 keV Peak",8000,0,8000);
	
	g64cascade = new TH1D("g64cascade","Gammas Gated on 238 2556 and 1840",8000,0,8000);
	g238and1297 = new TH1D("g238and1297","Gammas Gated on 238 and 1297",8000,0,8000);
	g275and1233 = new TH1D("g275and1233","Gammas Gated on 275 and 1233",8000,0,8000);
	g238and2556 = new TH1D("g238and2556","Gammas Gated on 238 and 2556",8000,0,8000);
	g238and1340 = new TH1D("g238and1340","Gammas Gated on 238 and 1340",8000,0,8000);
	g2556and1840 = new TH1D("g2556and1840","Gammas Gated on 2556 and 1840",8000,0,8000);
	g238and2556and1584 = new TH1D("g238and2556and1584","Gammas Gated on 238 and 2556 and 1584",8000,0,8000);

	//The files for the normalization parameters and gates are opened here.

	ifstream inFile1("textfiles/GamFileNames.txt");
	ifstream inFile6("textfiles/GamCalParamsQuadREDO.txt");
//	ifstream inFile6("textfiles/GamCalLinWHighREDOcompat.txt");



	for (int i=0; i<111; i++){

		inFile6 >> gamcalparams[i][0] >> gamcalparams[i][1] >> gamcalparams[i][2];

	}


	//close the files here
	inFile6.close();

	int numruns = 0;

	string filebuffer;

	for (int run = 0; run < 127; run++){
		inFile1 >> filebuffer;

		//if (run >=11 && run <25) histfill(filebuffer,logFile);
		histfill(filebuffer,logFile);

		numruns++;

	}
	

	std::cout << std::endl << "The number of files analyzed was: " << numruns << std::endl;
	std::cout << "Writing data to GammaOnly.root" << std::endl;
	hist->Write();
	hist->Close();

	logFile.close();

}



//Old code that works and has been taken out of the program is dumped here at the end.


