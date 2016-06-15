#include <fstream>
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include "TSpectrum.h"
#include "FindGam.h"

void RegCalc(std::ostream& oufcal)
{

	double gamEnergies[12] = {846.8, 1238.2, 2598.86, 121.78, 244.7, 344.27, 778.9, 867.4, 964.1, 1085, 1112, 1408};

	double sy = 0;
	double sx2 = 0;
	double sx = 0;
	double sxy = 0;
	double n = 12;
	double slope = 0;
	double offset = 0;

	int nocal = 0;

	for (int i=0; i<111; i++){
		//cout << PeakPos[i].size() << endl;
		if (PeakPos[i].size() == 12){
			//cout << "TRUE" << endl;
			for (int j = 0; j < 12; j++){
				sx2 += pow(PeakPos[i][j],2);
				sx += PeakPos[i][j];
				sxy += PeakPos[i][j]*gamEnergies[j];
				sy += gamEnergies[j];



			}
					//	cout << "sx2 " << sx2 << "sx " << sx << "sxy " << sxy << "sy " << sy << endl;
			offset = (sy*sx2-sx*sxy)/(n*sx2-pow(sx,2));
			slope = (n*sxy-sx*sy)/(n*sx2-pow(sx,2));
		}

		oufcal << slope << " " << offset << std::endl;
			
		if (slope != 0) nocal += 1;


		slope = 0;
		offset = 0;
		sy = 0;
		sx2 = 0;
		sx = 0;
		sxy = 0;

	}

	cout << "Number of calibrated detectors: " << nocal << endl;

}

void PeakFinder(TH1* h1, std::ostream& ouf, int whichspec, int detno)
{
    //Construct TSpectrum with max number of peaks 20
    TSpectrum *spec = new TSpectrum();
    
    //Find the peaks, nSigma is the approximate sigma of the peaks, threshold discards any peak with amplitude less than thresh*highest_peak
    Double_t nSigma = 1;
    Double_t thresh;

    if (whichspec == 0) thresh = 0.004;
    else thresh = .005;

    Int_t nFound = spec->Search(h1, nSigma, "", thresh);
    
    //Print out the number of found peaks
    //cout << "Number of Peaks Found: " << nFound << " for detector #" << detno << endl;
    
    
    //Get the X and Y positions of the peaks and sort them into arrays
    Double_t *xpos = spec->GetPositionX();
    Double_t *ypos = spec->GetPositionY();
    Double_t xswap = 0;
    Double_t yswap = 0;
    Int_t count = 0;
    
    while (count < nFound) {
        for (Int_t i = count; i < nFound; i++) {
            if (xpos[i] < xpos[count]) {
                xswap = xpos[count];
                xpos[count] = xpos[i];
                xpos[i] = xswap;
                
                yswap = ypos[count];
                ypos[count] = ypos[i];
                ypos[i] = yswap;
            }
        }
        count++;
    }
  /*  
    int LowBoundCo[3] = {1020, 1500, 3150};
    int LowBoundEu[9] = {120, 250, 400, 920, 1030, 1150, 1300, 1300, 1700};

    int HiBoundCo[3] = {1070, 1550, 3250};
    int HiBoundEu[9] = {180, 350, 450, 1000, 1100, 1230, 1450, 1450, 1790};
*/

    int LowBoundCo[3] = {1036, 1518, 3188};
    int LowBoundEu[9] = {147, 296, 417, 950, 1060, 1176, 1329, 1359, 1721};

    int HiBoundCo[3] = {1049, 1533, 3219};
    int HiBoundEu[9] = {156, 308, 431, 965, 1075, 1196, 1349, 1377, 1743};





int CoPks = 0;
int EuPks = 0;

    //Print out the location of the different peaks
    for (Int_t i=1; i <= nFound; i++) {
        //printf("%f\n", xpos[i-1]);
	//ouf 
	//std::cout << xpos[i-1] << std::endl;

    	if (whichspec == 0){
		for (int j=0; j<3; j++){
			if (xpos[i-1] > LowBoundCo[j] && xpos[i-1] < HiBoundCo[j]){
				Peaks.push_back(xpos[i-1]);
				//std::cout << xpos[i-1] << std::endl;
				CoPks += 1;
			}
		}
	}
	else{
		for (int j=0; j<9; j++){
			if (xpos[i-1] > LowBoundEu[j] && xpos[i-1] < HiBoundEu[j]){
				if (xpos[i-1] != Peaks.back()){
					Peaks.push_back(xpos[i-1]);
					//std::cout << xpos[i-1] << std::endl;
					EuPks+=1;
				}
			}
		}

	}

    }

	cout << "Det No: " << detno << " Co Peaks: " << CoPks << " Eu Peaks: " << EuPks << endl;

}

void CalGam(){

	//TFile *gright = TFile::Open("GamRight.root");
	//TFile *gleft = TFile::Open("GamLeft.root");
	TFile *gCo = TFile::Open("GamCo.root");
	TFile *gEu = TFile::Open("GamEu.root");

	std::ofstream outFile("GamCalParams.txt");

	TH1 *hist1;
	TH1 *hist2;
	//outFile << "Gammasphere Right Peaks:" << std::endl;
	for (int i = 0; i<111; i++){

		gCo->cd();

		hist1 = (TH1*) gCo->Get("Gammasphere_Energy/gam_" + TString(std::to_string(i)));

		PeakFinder(hist1, outFile, 0, i);
			
		gEu->cd();
	
		hist2 = (TH1*) gEu->Get("Gammasphere_Energy/gam_" + TString(std::to_string(i)));
		
		PeakFinder(hist2, outFile, 1, i);
		
		//cout << Peaks.size() << endl;

		PeakPos.push_back(Peaks);

		Peaks.clear();

		hist2->Reset();
		hist1->Reset();
	}	


	RegCalc(outFile);




/*
	gleft->cd();

	for (int i; i<110; i++){
		hist2 = (TH1*) gEu->get("Gammasphere/gam_" + TString(std::to_string(i));
		
		PeakFinder(hist2, outFile, 1, i);
		hist2->Reset();
	}
*/

	//gright->Close();
	//gleft->Close();
	//gCo->Close();
	//gEu->Close();

}

