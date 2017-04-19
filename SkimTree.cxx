#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTree.h"
#include "../goddess/include/GoddessStruct.h"
#include <iostream>
#include <fstream>
#include <algorithm>

bool strip(SiDataBase db){

//	return (db.StripMaxLayer(0,false) > 25 || db.StripMaxLayer(1,false) > 25);
	return (db.MultLayer(0,false) != 1 || db.MultLayer(1,false) != 1);

}


void skimtree(){

for (int run = 404; run < 495; run++){ 
if ((run > 400 && run < 409 && run != 405) || (run > 409 && run < 424) || (run > 431 && run < 435) || (run > 436 && run < 447) || (run > 448 && run < 455) || (run > 455 && run < 458) || (run > 459 && run < 465) || (run > 468 && run < 484) || (run > 484 && run < 495)){

std::cout << "Skimming run " << run << std::endl;

	TFile *oldfile = new TFile("../exec/rootfiles/QQQ5/run" + TString(std::to_string(run)) + "QQQ5_SKIMMED.root");
	TTree *oldtree = (TTree*)oldfile->Get("god");
	int nentries = oldtree->GetEntries();
std::cout << nentries << std::endl;

	vector<GamData> *gam={};
	vector<SiDataBase> *si={};

	oldtree->SetBranchAddress("gam",&gam);
	oldtree->SetBranchAddress("si",&si);

	TFile *newfile = new TFile("../exec/rootfiles/QQQ5/run" + TString(std::to_string(run)) + "QQQ5_SKIMMED_AGAIN.root","recreate");
	TTree *newtree = oldtree->CloneTree(0);

//	int ele;



	for (int n=0; n<nentries; n++){

		oldtree->GetEntry(n);

//		for(unsigned int i = 0; i < si2->size();i++){
			
//			if (si2->at(i).StripMaxLayer(0,false) > 25 || si2->at(i).StripMaxLayer(1,false) > 25) 

//		}

		si->erase( std::remove_if(si->begin(), si->end(), strip), si->end());

		if (si->size() > 0) newtree->Fill();




	}

	gam->clear();
	si->clear();

	newtree->AutoSave();
	newfile->Close();
	oldfile->Close();
}
}
}
