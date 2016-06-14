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
	int gate = 0;
	int mult[32] = {36869,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double expo[32] = {-.582,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	for (int evt=0;evt<nEntries;evt++){
		gate = 0;
		nt->GetEntry(evt);
		if(evt % 100000 == 0) cout << "Run " << runnum << ": Processing event number "<<evt << " of " << nEntries << endl;
				
			//Fill the Si histograms here:
		for(int i = 0; i < si2->size();i++){
			if (si2->at(i).E1 < 620 && si2->at(i).E1 > 577 && si2->at(i).PstripE1 == 1) gate++;
			for (int j=0; j<32; j++){
				if (si2->at(i).sectorStr == "DA"){
				if (si2->at(i).PstripdE == 0 && si2->at(i).dE < mult[0]*pow(si2->at(i).E1,expo[0]) && si2->at(i).dE > 48465*pow(si2->at(i).E1,-.646)){
					DA_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(i).E1,si2->at(i).dE);
					if (si2->at(i).PstripdE == j) QQQDAdE->Fill(si2->at(i).dE,j);
					if (si2->at(i).PstripE1 == j) QQQDAE1->Fill(si2->at(i).E1,j);

					if (si2->at(i).PstripE1 ==1 && si2->at(i).PstripdE==0 && j==0) QQQDAtot->Fill(si2->at(i).dE*0.000529+1.23 + si2->at(i).E1*.0053+7.8547);
				}
				}
				if (si2->at(i).sectorStr == "DC"){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(i).E1,si2->at(i).dE);
					QQQDCdE->Fill(si2->at(i).dE,si2->at(i).PstripdE);
					QQQDCE1->Fill(si2->at(i).E1,si2->at(i).PstripE1);
				}
			}	

		}
		for (int i = 0; i < gam2->size();i++){
			if (gate > 0) gam_cal->Fill(gam2->at(i).en,gam2->at(i).num); //Gamma histogram filled by energy and detector number

		}

	}





	std::cout << "Run " << runnum << " will now be closed." << std::endl; 
	gam2->clear();
	si2->clear();
	data->Close();
}

//***********************************************************//


void MakeMyHists(){

	int stripnum = 32;
	//the hist file is opened here for writing
	hist = TFile::Open("TotalData.root","RECREATE");
	//directories for the PID histograms are created. Directories for the other QQQ histograms are not created because they are put in 2D histograms.
	QQQ5_DA_PID = hist->mkdir("DA_PID");
	QQQ5_DC_PID = hist->mkdir("DC_PID");

	//QQQ energy histograms are created here.
	QQQDAdE = new TH2D("QQQDAdE","QQQ5 DA dE",4096,0,4096,32,0,32);
	QQQDAE1 = new TH2D("QQQDAE1","QQQ5 DA E1",4096,0,4096,32,0,32);

	QQQDCdE = new TH2D("QQQDCdE","QQQ5 DC dE",5000,0,50000,32,0,32);
	QQQDCE1 = new TH2D("QQQDCE1","QQQ5 DC E1",5000,0,50000,32,0,32);

	gam_cal = new TH2D("gam_cal","Gammasphere Calibrated Energy",12500,0,25000,110,0,110);
	gam_tot = new TH1D("gam_tot","Total Gammasphere Spectrum",12500,0,25000);

	QQQDAtot = new TH1D("QQQDAtot","Total Energy Strip 0",8000,0,16);
	
	//base histogram names for histogram vectors
	std::string PIDbaseDA = "pid_DA_";
	std::string PIDbaseDC = "pid_DC_";
	//
	QQQ5_DA_PID->cd();
	for (int i=0; i<stripnum; i++){
		string name = PIDbaseDA + std::to_string(i);
		TH2D *h = new TH2D(TString(name),"QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),4096,0,4096,4096,0,4096);
		DA_PIDhists.push_back(h);
	}

	QQQ5_DC_PID->cd();
	for (int i=0; i<stripnum; i++){
		string name = PIDbaseDC + std::to_string(i);
		TH2D *h = new TH2D(TString(name),"QQQ5 DC dE vs E1 Strip " + TString(std::to_string(i)),5000,0,50000,5000,0,50000);
		DC_PIDhists.push_back(h);
	}


	for (int run = 410; run < 419; run++){
		histfill(run);
	}


	std::cout << "Writing data to TotalData.root" << std::endl;
	hist->Write();
	hist->Close();


}
