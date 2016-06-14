{
//cout << "here works" << endl;
//Open the file that stores the data
TFile *data = TFile::Open("rootfiles/run427.root");
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
TFile *hist = TFile::Open("GamEu.root","RECREATE");

TDirectory *Gammasphere = hist->mkdir("Gammasphere_Energy");

std::vector<TH1D*> gamhists;
std::string gambase = "gam_";

Gammasphere->cd();

for (int i=0; i<111; i++){
	string name = gambase + std::to_string(i);
	TH1D *h = new TH1D(TString(name),"Gammasphere Detector " + TString(std::to_string(i)),16000,0,16000);
	gamhists.push_back(h);
}


//Gets the number of entries in the tree
int nEntries = nt->GetEntries();

//Here we loop over the events in the tree. The first for loop, loops over the events in the si2 vector. The strip numbers
//are then looped over to create histograms for each strip. 
for(int evt=0;evt<50000000;evt++){
	nt->GetEntry(evt);
if(evt % 100000 == 0) cout<< "Processing event number "<<evt << " of " << nEntries<<endl;
	//Gammasphere histograms filled here. All of the calibrations are handled at time of fill.
	for(int i = 0; i < gam2->size();i++){
		for (int j =0 ; j<111; j++){
			if (j==gam2->at(i).num) gamhists[j]->Fill(gam2->at(i).en);
		}
	}
	
}

hist->Write();
hist->Close();


}
