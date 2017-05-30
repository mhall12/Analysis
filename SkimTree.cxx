#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTree.h"
#include "../goddess/include/GoddessStruct.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "MattAnalysis.h"
#include "MattAnalysis2.h"

bool strip(SiDataBase db){
//db stands for Data Base
// Skimming bool functions I have used in the past:
//	return (db.StripMaxLayer(0,false) > 25 || db.StripMaxLayer(1,false) > 25);
//	return (db.MultLayer(0,false) != 1 || db.MultLayer(1,false) != 1);

//	return ((db.ESumLayer(1,false) < 300000 && db.telescopeID > 1102) || (db.MultLayer(0,false) != 1 || db.MultLayer(1,false) != 1) || (db.ESumLayer(0,false) > 40000 && db.telescopeID > 1102));

//	return (db.telescopeID != 2105 && db.telescopeID != 2104 && db.telescopeID !=2107 && db.telescopeID !=2108 && db.telescopeID !=2109 && db.telescopeID !=2110);

//	return (db.telescopeID < 2000 && ((db.MultLayer(0,false) != 1 || db.MultLayer(1,false) != 1) || (db.StripMaxLayer(0,false) > 25 || db.StripMaxLayer(1,false) > 25)));

//	return (db.telescopeID > 2000 && (db.ESumLayer(0,false) > 35000 || db.ESumLayer(1,false) < 300000));

//	return (db.MultLayer(1,false) != 1);

	double m3H = 3.016049;
	double m3He = 3.016029;
	double m19Ne = 19.001880;
	double m19F = 18.998403;
	double m27Al = 26.981539;
	double m27Si = 26.986704;

	double Q = 0;
	double pi = 3.14159265;

	double E1cal = 0;
	double E1norm = 0;

	double angle = -100;
	int ang_bin = 0;

	double positionZ =  db.PosE1().Z();
			//S is the cylindrical coordinates position of the SX3 detector. It should be a constant value.
	double positionS = sqrt(pow( db.PosE1().X(),2)+pow( db.PosE1().Y(),2));

	int stripE1 = db.StripMaxLayer(1,false);
	double E1 = db.ESumLayer(1,false);

	if (db.telescopeID > 2000){
		if (positionS > 0) angle = atan(positionS/positionZ) * 180 / pi;
		if (angle > -10 && angle < 0) angle = 0;
		if (angle > 90 && angle < 100) angle = 90;


		if (angle <= 60) ang_bin = 0;
		else if (angle > 60 && angle <= 70) ang_bin = 1;
		else if (angle > 70 && angle <= 80) ang_bin = 2;
		else if (angle > 80) ang_bin = 3;

		if ( db.telescopeID == 2107 && stripE1 == 2 && angle > 70) E1 = E1-6500;
		E1norm = E1*SX3Norm_Ang[4* db.telescopeID-8416+ang_bin][stripE1];

		int calanglebin = 0;

		for (int a = 45; a < 90; a+=2){
			if (angle >= a-1 && angle < a+1) calanglebin = (int)(.5*a-22.5);
		}

		E1cal = E1norm*SX3Cal[calanglebin][2* db.telescopeID-4208]+SX3Cal[calanglebin][2* db.telescopeID-4208 + 1];
		Q = E1cal*(1+m3H/m19Ne)-30*(1-m3He/m19Ne)-2*sqrt(m3He*m3H/pow(m19Ne,2)*E1cal*30)*cos(angle*pi/180);

	}

	return (db.telescopeID > 2000 && Q < -10.25);

}


void skimtree(){
//Fill from text files here:
	ifstream inFile19("textfiles/SX3Norm_Angle.txt");
	ifstream inFile20("textfiles/SX3Cal.txt");

	for (int i = 0; i < 28; i++){

		inFile19 >> SX3Norm_Ang[i][0] >> SX3Norm_Ang[i][1] >> SX3Norm_Ang[i][2] >> SX3Norm_Ang[i][3];

	}

	for (int i = 0; i < 23; i++){

		inFile20 >> SX3Cal[i][0] >> SX3Cal[i][1] >> SX3Cal[i][2] >> SX3Cal[i][3] >> SX3Cal[i][4] >> SX3Cal[i][5] >> SX3Cal[i][6] >> SX3Cal[i][7] >> SX3Cal[i][8] >> SX3Cal[i][9] >> SX3Cal[i][10] >> SX3Cal[i][11] >> SX3Cal[i][12] >> SX3Cal[i][13]; 	

	}

for (int run = 404; run < 495; run++){ 
if ((run > 400 && run < 409 && run != 405 && run !=406) || (run > 409 && run < 424) || (run > 431 && run < 435) || (run > 436 && run < 447) || (run > 448 && run < 455) || (run > 455 && run < 458) || (run > 459 && run < 465) || (run > 468 && run < 484) || (run > 484 && run < 495)){

std::cout << "Skimming run " << run << std::endl;

//	TFile *oldfile = new TFile("../exec/rootfiles/TotalFiles/run" + TString(std::to_string(run)) + ".root");
	TFile *oldfile = new TFile("/media/mhall12/ne19disk1/TotalRootFilesWithoutSX3Crap/run" + TString(std::to_string(run)) + "_SX3Mult1.root");
	TTree *oldtree = (TTree*)oldfile->Get("god");
	int nentries = oldtree->GetEntries();
std::cout << nentries << std::endl;

	vector<GamData> *gam={};
	vector<SiDataBase> *si={};

	oldtree->SetBranchAddress("gam",&gam);
	oldtree->SetBranchAddress("si",&si);

//	TFile *newfile = new TFile("../exec/rootfiles/TotalFiles/run" + TString(std::to_string(run)) + ".root","recreate");
	TFile *newfile = new TFile("/media/mhall12/ne19disk1/FinalRootFiles/run" + TString(std::to_string(run)) + ".root","recreate");
	TTree *newtree = oldtree->CloneTree(0);

//	int ele;



	for (int n=0; n<nentries; n++){

		oldtree->GetEntry(n);

//		int percentage = (int)n/nentries;

		if(n % 10000 == 0){
			cout << "Run " << run << ": Processing event number "<< n << " of " << nentries << " \r";
			std::cout.flush();
		}
//		for(unsigned int i = 0; i < si2->size();i++){
			
//			if ( db.StripMaxLayer(0,false) > 25 ||  db.StripMaxLayer(1,false) > 25) 

//		}
//the remove if function loops through the vector and removes each element that is fed a "true" bool by the strip function.
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
