{
//cout << "here works" << endl;
//Open the file that stores the data
TFile *data = TFile::Open("rootfiles/run474.root");
trees->cd();
//Copy the tree into a new tree called nt
TTree *nt = (TTree*)data->Get("trees/god");

//Create containers for the data in the tree
vector<GamData> *gam2={};
vector<SiData> *si2={};

//cout<<"Allie will be right"<<endl;
nt->SetBranchAddress("gam",&gam2);
nt->SetBranchAddress("si",&si2);

//Open a new file to store the histograms. Directories in the file are also made here.
TFile *hist = TFile::Open("Analysis2.root","RECREATE");

TDirectory *QQQ5_DC_PID = hist->mkdir("DC_PID");
TDirectory *QQQ5_DA = hist->mkdir("DA_Energy");
TDirectory *QQQ5_DA_D = hist->mkdir("DA_Deuteron_Energy");
//TDirectory *QQQ5_DA_DPID = hist->mkdir("DA_PID_Deuterons");
TDirectory *Gammasphere = hist->mkdir("Gammasphere_Energy");

//Gammasphere calibration parameters are here.
double gamcoeff1[110]={};
double gamcoeff2[110]={};

//*************This is temporary to initialize all parameters to 1*******************
for (int i;i<110;i++){
	gamcoeff1[i]=1;
}

//These arrays hold the constants used in the gates. The first 6 entries are for analog, the last 6 are for digital.
double mul[12]={46738,73843,57267,85193,84011,76104,0,0,0,0,0,0};
double exl[12]={-.686,-.752,-.702,-.77,-.752,-.732,0,0,0,0,0,0};
double muh[12]={67515,61741,61061,57871,67551,88670,0,0,0,0,0,0};
double exh[12]={-.705,-.684,-.67,-.662,-.669,-.721,0,0,0,0,0,0};


int stripnum=32;

std::vector<TH2D*> DC_PIDhists;
std::string PIDbaseDC = "pid_DC_";

//std::vector<TH1F*> DA_Ehists;
//std::string dEbaseDA = "DA_dE_";

std::vector<TH2D*> DA_DPIDhists;
std::string DPIDbaseDA = "Dpid_DA_";

TH2D *PID11_15 = new TH2D("PID11_15","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID16_20 = new TH2D("PID16_20","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID21_25 = new TH2D("PID21_25","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID26_31 = new TH2D("PID26_31","QQQ5 PID",4096,0,4096,4096,0,4096);

//Histograms are initialized here
QQQ5_DC_PID->cd();
for (int i=0; i<stripnum; i++){
	string name = PIDbaseDC + std::to_string(i);
	TH2D *h = new TH2D(TString(name),"QQQ5 DC dE vs E1 Strip " + TString(std::to_string(i)),5000,0,50000,5000,0,50000);
	DC_PIDhists.push_back(h);
}

//TH3D *QQQ_DA_PID3D = new TH3D("QQQ_DA_PID3D","QQQ5 DA dE vs E1",4096,0,4096,4096,0,4096,32,0,32);

QQQ5_DA->cd();
//for (int i=0; i<stripnum; i++){
//	string name = dEbaseDA + std::to_string(i);
//	TH1F *h = new TH1F(TString(name),"QQQ5 DA dE Strip " + TString(std::to_string(i)),4096,0,4096);
//	DA_Ehists.push_back(h);
//}
TH2D *QQQDAdE = new TH2D("QQQDAdE","QQQ5 DA dE",4096,0,4096,32,0,32);
TH2D *QQQDAE1 = new TH2D("QQQDAE1","QQQ5 DA E1",4096,0,4096,32,0,32);

//This set of histograms was just to prove that it works and can be taken away at any time.
//QQQ5_DA_DPID->cd();
//for (int i=0; i<stripnum; i++){
//	string name = DPIDbaseDA + std::to_string(i);
//	TH2D *h = new TH2D(TString(name),"QQQ5 DA dE vs E1 Deuterons Strip " + TString(std::to_string(i)),4096,0,4096,4096,0,4096);
//	DA_DPIDhists.push_back(h);
//}

//Deuteron gated QQQ histograms
QQQ5_DA_D->cd();
TH2D *QQQDAdE_D = new TH2D("QQQDAdE_D","QQQ5 DA dE",4096,0,4096,32,0,32);
TH2D *QQQDAE1_D = new TH2D("QQQDAE1_D","QQQ5 DA E1",4096,0,4096,32,0,32);

//Gammasphere histograms initialized here. There are ~110 detectors and the energy range we want is 16000 keV.
Gammasphere->cd();
TH2D *gam_cal = new TH2D("gam_cal","Gammasphere Calibrated Energy",16000,0,16000,110,0,110);

//Gets the number of entries in the tree
int nEntries = nt->GetEntries();

//Here we loop over the events in the tree. The first for loop, loops over the events in the si2 vector. The strip numbers
//are then looped over to create histograms for each strip. 
std::vector<int> usedEvt0;
std::vector<int> usedEvt1;
std::vector<int> usedEvt2;
std::vector<int> usedEvt3;
std::vector<int> usedEvt4;
int used0 = 0;
int used1 = 0;
int used2 = 0;
int used3 = 0;
int used4 = 0;

for(int evt=0;evt<nEntries;evt++){
	nt->GetEntry(evt);
	usedEvt0.push_back(-1);
	usedEvt1.push_back(-1);
	usedEvt2.push_back(-1);
	usedEvt3.push_back(-1);
	usedEvt4.push_back(-1);
if(evt % 100000 ==0) cout<< "Processing event number "<<evt << " of " << nEntries<<endl;
	//Gammasphere histograms filled here. All of the calibrations are handled at time of fill.
//	for(int i = 0; i < gam2->size();i++){
//		gam_cal->Fill(gam2->at(i).en*gamcoeff1[gam2->at(i).num]+gamcoeff2[gam2->at(i).num],gam2->at(i).num);
//
//	}

	//QQQ histograms are filled here.
	for (int i = 0; i < si2->size(); i++){
		used0 = 0;
		used1 = 0;
		used2 = 0;
		used3 = 0;
		used4 = 0;
		for (int j=0; j < si2->size(); j++){
			//this for loop checks to see if an event was used already
			for (int k=0; k < usedEvt0.size(); k++){
				if (i == usedEvt0[k] || j == usedEvt0[k]) used0 = 1;
			}
			if (si2->at(i).sectorStr=="DC" && si2->at(j).sectorStr=="DC" && i!=j && used0 == 0){
				if (si2->at(i).dE != 0 && si2->at(j).E1 !=0 && si2->at(i).PstripdE == si2->at(j).PstripE1){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(j).E1,si2->at(i).dE);
					usedEvt0.push_back(i);
					usedEvt0.push_back(j);
				}
				if (si2->at(i).E1 != 0 && si2->at(j).dE !=0 && si2->at(i).PstripE1 == si2->at(j).PstripdE){
					DC_PIDhists[si2->at(j).PstripdE]->Fill(si2->at(i).E1,si2->at(j).dE);
					usedEvt0.push_back(i);
					usedEvt0.push_back(j);
				}
			}



			for (int k=0; k < usedEvt1.size(); k++){
				if (i == usedEvt1[k] || j == usedEvt1[k]) used1 = 1;
			}
			if (si2->at(i).sectorStr=="DC" && si2->at(j).sectorStr=="DC" && i!=j && used1 == 0){
				if (si2->at(i).dE != 0 && si2->at(j).E1 !=0 && si2->at(i).PstripdE == si2->at(j).PstripE1-1){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(j).E1,si2->at(i).dE);
					usedEvt1.push_back(i);
					usedEvt1.push_back(j);
				}
				if (si2->at(i).E1 != 0 && si2->at(j).dE !=0 && si2->at(i).PstripE1 == si2->at(j).PstripdE+1){
					DC_PIDhists[si2->at(j).PstripdE]->Fill(si2->at(i).E1,si2->at(j).dE);
					usedEvt1.push_back(i);
					usedEvt1.push_back(j);
				}
			}



			for (int k=0; k < usedEvt2.size(); k++){
				if (i == usedEvt2[k] || j == usedEvt2[k]) used2 = 1;
			}
			if (si2->at(i).sectorStr=="DC" && si2->at(j).sectorStr=="DC" && i!=j && used2 == 0){
				if (si2->at(i).dE != 0 && si2->at(j).E1 !=0 && si2->at(i).PstripdE == si2->at(j).PstripE1-2){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(j).E1,si2->at(i).dE);
					usedEvt2.push_back(i);
					usedEvt2.push_back(j);
				}
				if (si2->at(i).E1 != 0 && si2->at(j).dE !=0 && si2->at(i).PstripE1 == si2->at(j).PstripdE+2){
					DC_PIDhists[si2->at(j).PstripdE]->Fill(si2->at(i).E1,si2->at(j).dE);
					usedEvt2.push_back(i);
					usedEvt2.push_back(j);
				}
			}

			for (int k=0; k < usedEvt3.size(); k++){
				if (i == usedEvt3[k] || j == usedEvt3[k]) used3 = 1;
			}
			if (si2->at(i).sectorStr=="DC" && si2->at(j).sectorStr=="DC" && i!=j && used3 == 0){
				if (si2->at(i).dE != 0 && si2->at(j).E1 !=0 && si2->at(i).PstripdE == si2->at(j).PstripE1-3){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(j).E1,si2->at(i).dE);
					usedEvt3.push_back(i);
					usedEvt3.push_back(j);
				}
				if (si2->at(i).E1 != 0 && si2->at(j).dE !=0 && si2->at(i).PstripE1 == si2->at(j).PstripdE+3){
					DC_PIDhists[si2->at(j).PstripdE]->Fill(si2->at(i).E1,si2->at(j).dE);
					usedEvt3.push_back(i);
					usedEvt3.push_back(j);
				}
			}

			for (int k=0; k < usedEvt4.size(); k++){
				if (i == usedEvt4[k] || j == usedEvt4[k]) used4 = 1;
			}
			if (si2->at(i).sectorStr=="DC" && si2->at(j).sectorStr=="DC" && i!=j && used4 == 0){
				if (si2->at(i).dE != 0 && si2->at(j).E1 !=0 && si2->at(i).PstripdE == si2->at(j).PstripE1-4){
					DC_PIDhists[si2->at(i).PstripdE]->Fill(si2->at(j).E1,si2->at(i).dE);
					usedEvt4.push_back(i);
					usedEvt4.push_back(j);
				}
				if (si2->at(i).E1 != 0 && si2->at(j).dE !=0 && si2->at(i).PstripE1 == si2->at(j).PstripdE+4){
					DC_PIDhists[si2->at(j).PstripdE]->Fill(si2->at(i).E1,si2->at(j).dE);
					usedEvt4.push_back(i);
					usedEvt4.push_back(j);
				}
			}
		}
	}					
usedEvt0.clear();
usedEvt1.clear();
usedEvt2.clear();
usedEvt3.clear();
usedEvt4.clear();



}



hist->Write();
hist->Close();


}
