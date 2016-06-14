{
//cout << "here works" << endl;
//Open the file that stores the data
TFile *data = TFile::Open("rootfiles/run412all.root");
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
TFile *hist = TFile::Open("Analysis.root","RECREATE");
TDirectory *QQQ5_DA_PID = hist->mkdir("DA_PID");
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

std::vector<TH2D*> DA_PIDhists;
std::string PIDbaseDA = "pid_DA_";

//std::vector<TH1F*> DA_Ehists;
//std::string dEbaseDA = "DA_dE_";

std::vector<TH2D*> DA_DPIDhists;
std::string DPIDbaseDA = "Dpid_DA_";

TH2D *PID11_15 = new TH2D("PID11_15","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID16_20 = new TH2D("PID16_20","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID21_25 = new TH2D("PID21_25","QQQ5 PID",4096,0,4096,4096,0,4096);
TH2D *PID26_31 = new TH2D("PID26_31","QQQ5 PID",4096,0,4096,4096,0,4096);

//Histograms are initialized here
QQQ5_DA_PID->cd();
for (int i=0; i<stripnum; i++){
	string name = PIDbaseDA + std::to_string(i);
	TH2D *h = new TH2D(TString(name),"QQQ5 DA dE vs E1 Strip " + TString(std::to_string(i)),4096,0,4096,4096,0,4096);
	DA_PIDhists.push_back(h);
}

pid_DA_0->SetTitle("QQQ5 Particle ID");
pid_DA_0->GetXaxis()->SetTitle("Channel in E1");
pid_DA_0->GetYaxis()->SetTitle("Channel in dE");

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
TH2D *gam_cal = new TH2D("gam_cal","Gammasphere Calibrated Energy",1600,0,16000,110,0,110);

//Gets the number of entries in the tree
int nEntries = nt->GetEntries();

//Here we loop over the events in the tree. The first for loop, loops over the events in the si2 vector. The strip numbers
//are then looped over to create histograms for each strip. 
for(int evt=0;evt<nEntries;evt++){
	nt->GetEntry(evt);
if(evt % 100000 ==0) cout<< "Processing event number "<<evt << " of " << nEntries<<endl;
	//Gammasphere histograms filled here. All of the calibrations are handled at time of fill.
	for(int i = 0; i < gam2->size();i++){
		gam_cal->Fill(gam2->at(i).en*gamcoeff1[gam2->at(i).num]+gamcoeff2[gam2->at(i).num],gam2->at(i).num);

	}
	//QQQ histograms are filled here.
	for(int i = 0; i < si2->size();i++){
		for (int j=0; j<stripnum; j++){
			if (si2->at(i).sectorStr=="DA" && si2->at(i).PstripdE==j){
				DA_PIDhists[j]->Fill(si2->at(i).E1,si2->at(i).dE);
				//QQQ_DA_PID3D->Fill(si2->at(i).E1,si2->at(i).dE,j);
				//DA_Ehists[j]->Fill(si2->at(i).dE);
				QQQDAdE->Fill(si2->at(i).dE,j);
				QQQDAE1->Fill(si2->at(i).E1,j);
				
				if (j>=11 && j<=15) PID11_15->Fill(si2->at(i).E1,si2->at(i).dE);
				if (j>=16 && j<=20) PID16_20->Fill(si2->at(i).E1,si2->at(i).dE);
				if (j>=21 && j<=25) PID21_25->Fill(si2->at(i).E1,si2->at(i).dE);
				if (j>=26 && j<=31) PID26_31->Fill(si2->at(i).E1,si2->at(i).dE);


				//Below is the condition for the Deuteron gate
				if (j<6 && si2->at(i).dE>mul[0]*pow(si2->at(i).E1,exl[0]) && si2->at(i).dE<muh[0]*pow(si2->at(i).E1,exh[0])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);
					//DA_DPIDhists[j]->Fill(si2->at(i).E1,si2->at(i).dE);
				}
				if (j>=6 && j<=10 && si2->at(i).dE>mul[1]*pow(si2->at(i).E1,exl[1]) && si2->at(i).dE<muh[1]*pow(si2->at(i).E1,exh[1])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);
				}
				if (j>=11 && j<=15 && si2->at(i).dE>mul[2]*pow(si2->at(i).E1,exl[2]) && si2->at(i).dE<muh[2]*pow(si2->at(i).E1,exh[2])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);
				}
				if (j>=16 && j<=20 && si2->at(i).dE>mul[3]*pow(si2->at(i).E1,exl[3]) && si2->at(i).dE<muh[3]*pow(si2->at(i).E1,exh[3])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);
				}
				if (j>=21 && j<=25 && si2->at(i).dE>mul[4]*pow(si2->at(i).E1,exl[4]) && si2->at(i).dE<muh[4]*pow(si2->at(i).E1,exh[4])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);
				}
				if (j>=26 && j<=31 && si2->at(i).dE>mul[5]*pow(si2->at(i).E1,exl[5]) && si2->at(i).dE<muh[5]*pow(si2->at(i).E1,exh[5])){
					QQQDAdE_D->Fill(si2->at(i).dE,j);
					QQQDAE1_D->Fill(si2->at(i).E1,j);





				}
			}
		}
	}
}

hist->Write();
hist->Close();


}
