{
//cout << "here works" << endl;
//Open the file that stores the data
TFile *data = TFile::Open("rootfiles/run430.root");
TFile *data2 = TFile::Open("rootfiles/run431.root");

//Copy the tree into a new tree called nt1
TTree *nt1 = (TTree*)data->Get("trees/god");
TTree *nt2 = (TTree*)data2->Get("trees/god");
//Create containers for the data in the tree
vector<GamData> *gam2={};
vector<GamData> *gam22={};

//cout<<"Allie will be right"<<endl;
nt1->SetBranchAddress("gam",&gam2);
nt2->SetBranchAddress("gam",&gam22);

//Open a new file to store the histograms. Directories in the file are also made here.
TFile *hist = TFile::Open("Gam.root","RECREATE");

TDirectory *Gammasphere = hist->mkdir("Gammasphere_Energy");

std::vector<TH1D*> gamhists;
std::string gambase = "gam_";

Gammasphere->cd();

for (int i=0; i<111; i++){
	string name = gambase + std::to_string(i);
	TH1D *h = new TH1D(TString(name),"Gammasphere Detector " + TString(std::to_string(i)),25000,0,25000);
	gamhists.push_back(h);
}

TH2D *gam_cal = new TH2D("gam_cal","Gammasphere Calibrated Energy",2500,0,25000,110,0,110);

//Gets the number of entries in the tree
int nEntries = nt1->GetEntries();

//Here we loop over the events in the tree. The first for loop, loops over the events in the si2 vector. The strip numbers
//are then looped over to create histograms for each strip. 

for(int evt=0;evt<nEntries;evt++){
	nt1->GetEntry(evt);
if(evt % 100000 == 0) cout<< "Right: Processing event number "<< evt << " of " << nEntries<<endl;
	//Gammasphere histograms filled here. All of the calibrations are handled at time of fill.
	for(int i = 0; i < gam2->size();i++){
		for (int j =0 ; j<111; j++){
			if (j==gam2->at(i).num) gamhists[j]->Fill(gam2->at(i).en);
			gam_cal->Fill(gam2->at(i).en,gam2->at(i).num);
		}
	}
	
}

int nEntries2 = nt2->GetEntries();

for(int evt=0;evt<nEntries2;evt++){
	nt2->GetEntry(evt);
if(evt % 100000 == 0) cout<< "Left: Processing event number "<< evt << " of " << nEntries<<endl;
	//Gammasphere histograms filled here. All of the calibrations are handled at time of fill.
	for(int i = 0; i < gam22->size();i++){
		for (int j =0 ; j<111; j++){
			if (j==gam22->at(i).num) gamhists[j]->Fill(gam22->at(i).en);
			gam_cal->Fill(gam22->at(i).en,gam22->at(i).num);
		}
	}
	
}

hist->Write();
hist->Close();


}
