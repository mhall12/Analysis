void PeakFinder(TH1F* h1, std::ostream& ouf)
{
    //Construct TSpectrum with max number of peaks 20
    TSpectrum *spec = new TSpectrum(32);
    
    //Find the peaks, nSigma is the approximate sigma of the peaks, threshold discards any peak with amplitude less than thresh*highest_peak
    Double_t nSigma = 1;
    Double_t thresh = 1e-1;
    Int_t nFound = spec->Search(h1, nSigma, "", thresh);
    
    //Print out the number of found peaks
    cout << "Number of Peaks Found: " << nFound << endl;
    
    
    //Get the X and Y positions of the peaks and sort them into arrays
    Float_t *xpos = spec->GetPositionX();
    Float_t *ypos = spec->GetPositionY();
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
    
    //Print out the location of the different peaks
    for (Int_t i=1; i <= nFound; i++) {
        //printf("%f\n", xpos[i-1]);
	ouf << xpos[i-1] << std::endl;
    }
}

void main(){

	TFile *gright = TFile::Open("GamRight.root");
	TFile *gleft = TFile::Open("GamLeft.root");

	std::ofstream outFile("peaks.txt");

	gright->cd();

	TH1 *hist1;
	TH1 *hist2;
	outFile << "Gammasphere Right Peaks:" << std::endl;
	for (int i; i<110; i++){
		hist1 = (TH1*) gright->get("Gammasphere_Energy/gam_" + TString(std::to_string(i));
		outFile << "Peaks above threshold for detector " << i << std::endl;
		PeakFinder(hist1, outFile);

	}	

	gleft->cd();

	for (int i; i<110; i++){
		hist2 = (TH1*) gleft->get("Gammasphere/gam_" + TString(std::to_string(i));
		
		PeakFinder(hist2, outFile);

	}

	gright->close();
	gleft->close();


}

