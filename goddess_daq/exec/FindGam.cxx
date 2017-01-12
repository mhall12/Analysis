#include <fstream>
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include "TSpectrum.h"
#include "FindGam.h"

void QuadCalc(){

	std::ifstream hep("gamhep.txt");
	std::ofstream out("GamCalParamsQuadREDO.txt");

	double HighEn[111] = {};
	double Sxx = 0;
	double Sxy = 0;
	double sxy = 0;
	double Sxx2 = 0;
	double Sx2x2 = 0;
	double Sx2y = 0;
	double sx2y = 0;
	double nn = 13;
	double sx = 0;
	double sy = 0;
	double sx2 = 0;
	double sx3 = 0;
	double sx4 = 0;

	//Quadratic equation of the form Ax2+Bx+C
	double A = 0;
	double B = 0;
	double C = 0;

	std::vector<std::vector<double>> PeakPos2(PeakPos);

	double gamEnergies2[13] = {846.8, 1238.2, 2598.86, 121.78, 244.7, 344.27, 778.9, 867.4, 964.1, 1085, 1112, 1408, 6130};

	for (int i = 0; i < 111; i++){
		
		hep >> HighEn[i];
		
		if (HighEn[i] != 0){
			PeakPos2[i].push_back(HighEn[i]);

			for (int j = 0; j < 13; j++){
				sx += PeakPos2[i][j];
				sy += gamEnergies2[j];
				sx2 += pow(PeakPos2[i][j],2);
				sxy += PeakPos2[i][j]*gamEnergies2[j];
				sx3 += pow(PeakPos2[i][j],3);
				sx4 += pow(PeakPos2[i][j],4);
				sx2y += pow(PeakPos2[i][j],2)*gamEnergies2[j];
			}

		Sxx = sx2/nn-pow(sx/nn,2);
		Sxy = sxy/nn-sx/nn*sy/nn;
		Sxx2 = sx3/nn-sx/nn*sx2/nn;
		Sx2x2 = sx4/nn-sx2/nn*sx2/nn;
		Sx2y = sx2y/nn-sx2/nn*sy/nn;

		A = (Sx2y*Sxx-Sxy*Sxx2)/(Sxx*Sx2x2-pow(Sxx2,2));
		
		B = (Sxy*Sx2x2-Sx2y*Sxx2)/(Sxx*Sx2x2-pow(Sxx2,2));

		C = sy/nn-B*sx/nn-A*sx2/nn;

		}
		else{
			A = 0;
			B = 0;
			C = 0;
		}

		out << A << " " << B << " " << C << endl;

		Sxx = 0;
		Sxy = 0;
		sxy = 0;
		Sxx2 = 0;
		Sx2x2 = 0;
		Sx2y = 0;
		sx2y = 0;
		nn = 13;
		sx = 0;
		sy = 0;
		sx2 = 0;
		sx3 = 0;
		sx4 = 0;
		A = 0;
		B = 0;
		C = 0;

	}

}

void RegCalc2()
{
	std::ifstream hep("gamhep.txt");
	std::ofstream out3("GamCalLinWHighREDO.txt");

	double gamEnergies3[13] = {846.8, 1238.2, 2598.86, 121.78, 244.7, 344.27, 778.9, 867.4, 964.1, 1085, 1112, 1408, 6130};

	double sy = 0;
	double sx2 = 0;
	double sx = 0;
	double sxy = 0;
	double n = 12;
	double slope = 0;
	double offset = 0;

	double HighEn;
	
	std::vector<std::vector<double>> PeakPos3(PeakPos);

	for (int i=0; i<111; i++){

		hep >> HighEn;

		PeakPos3[i].push_back(HighEn);
		
		if (HighEn != 0){
			
			for (int j = 0; j < 13; j++){
				sx2 += pow(PeakPos3[i][j],2);
				sx += PeakPos3[i][j];
				sxy += PeakPos3[i][j]*gamEnergies3[j];
				sy += gamEnergies3[j];



			}

			offset = (sy*sx2-sx*sxy)/(n*sx2-pow(sx,2));
			slope = (n*sxy-sx*sy)/(n*sx2-pow(sx,2));
		}

		out3 << slope << " " << offset << std::endl;

		slope = 0;
		offset = 0;
		sy = 0;
		sx2 = 0;
		sx = 0;
		sxy = 0;

	}
}


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

    if (whichspec == 0){
		if (detno != 96 && detno != 95 && detno != 76 && detno != 70 && detno != 31 && detno != 26 && detno != 84) thresh = 0.004;
		else if (detno == 96 || detno == 95 || detno == 76 || detno == 70 || detno ==31 || detno == 26) thresh = .0004;
		else thresh = 0.008;

    }
    else{ 
		if (detno != 110) thresh = .005;
		else if (detno == 110) thresh = .05;
    }
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

    int LowBoundCo[3] = {1036, 1511, 3177};
    int LowBoundEu[9] = {147, 296, 417, 950, 1060, 1176, 1327, 1359, 1721};

    int HiBoundCo[3] = {1055, 1539, 3226};
    int HiBoundEu[9] = {158, 311, 434, 970, 1080, 1199, 1352, 1384, 1749};



int CoPks = 0;
int EuPks = 0;

    //Print out the location of the different peaks
    for (Int_t i=1; i <= nFound; i++) {
        //printf("%f\n", xpos[i-1]);
	//ouf 
	//std::cout << xpos[i-1] << std::endl;

    	if (whichspec == 0){
		for (int j=0; j<3; j++){
			if (detno != 73 && xpos[i-1] > LowBoundCo[j] && xpos[i-1] < HiBoundCo[j]){
				Peaks.push_back(xpos[i-1]);
				//std::cout << xpos[i-1] << std::endl;
				CoPks += 1;
			}
			if (detno == 73 && xpos[i-1] > LowBoundCo[j]*1.2 && xpos[i-1] < HiBoundCo[j]*1.2){
				Peaks.push_back(xpos[i-1]);
				CoPks += 1;
			}
		}
	}
	else{
		for (int j=0; j<9; j++){
			if (detno != 73 && xpos[i-1] > LowBoundEu[j] && xpos[i-1] < HiBoundEu[j]){
				if (xpos[i-1] != Peaks.back()){
					Peaks.push_back(xpos[i-1]);
					//std::cout << xpos[i-1] << std::endl;
					EuPks+=1;
				}
			}
			if (detno == 73 && xpos[i-1] > LowBoundEu[j]*1.2 && xpos[i-1] < HiBoundEu[j]*1.2){
				if (xpos[i-1] != Peaks.back()){
					Peaks.push_back(xpos[i-1]);
					//std::cout << xpos[i-1] << std::endl;
					EuPks+=1;
				}
		

			}
		}

	}

    }

	if (EuPks == 9) EuCounter+=1;
	if (CoPks == 3) CoCounter+=1;
	if (CoPks == 2) Co2Counter+=1;
	if (CoPks == 4) Co4Counter+=1;

	cout << "Det No: " << detno << " Co Peaks: " << CoPks << " Eu Peaks: " << EuPks << endl;

}

void CalGam(){

	EuCounter=0;
	CoCounter=0;
	Co2Counter=0;
	Co4Counter=0;

	//TFile *gright = TFile::Open("GamRight.root");
	//TFile *gleft = TFile::Open("GamLeft.root");
	TFile *gCo = TFile::Open("GamCo.root");
	TFile *gEu = TFile::Open("GamEu.root");

	std::ofstream outFile("GamCalParamsREDO.txt");

	TH1 *hist1;
	TH1 *hist2;
	//outFile << "Gammasphere Right Peaks:" << std::endl;
	for (int i = 0; i<111; i++){

		gCo->cd();

		hist1 = (TH1*) gCo->Get("Gammasphere_Energy/gam_" + TString(std::to_string(i)));
		if (i != 80) hist1->Rebin(2);	
		else hist1->Rebin(4);
		
		PeakFinder(hist1, outFile, 0, i);
			
		gEu->cd();
	
		hist2 = (TH1*) gEu->Get("Gammasphere_Energy/gam_" + TString(std::to_string(i)));
		hist2->Rebin(1);
		
		PeakFinder(hist2, outFile, 1, i);
		
		//cout << Peaks.size() << endl;

		PeakPos.push_back(Peaks);

		Peaks.clear();

		//if (i != 60){
		hist2->Reset();
		hist1->Reset();
		//}
	}	


	RegCalc(outFile);
	QuadCalc();
	RegCalc2();

	cout << "Number of Detectors with 9 Eu Peaks: " << EuCounter << endl;
	cout << "Number of Detectors with 3 Co Peaks: " << CoCounter << endl;
	cout << "Number of Detectors with 2 Co Peaks: " << Co2Counter << endl;
	cout << "Number of Detectors with 4 Co Peaks: " << Co4Counter << endl;

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

