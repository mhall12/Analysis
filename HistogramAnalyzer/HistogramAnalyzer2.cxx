//#include "../MattAnalysis2.h"
//#include "../MattAnalysis.h"

{
#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include <math.h>

	//Set Parameters here!
	int rebinning = 1;
	int ExStart = 40; //Excitation energy starting point (multiplied by 10);
	int ExEnd = 48;

	TString Histograms = "SiQQQHists";
	TFile *Hists = TFile::Open("../" + Histograms + ".root");


	//Draw the hists we want to copy first!
	Hists->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists");
//Must change the names of these histograms from Ex_50_56
	Ex_40_48->Draw();
	Hists->cd("Ex_vs_Gammas_Hists/QQQ_v_Gam/1D_Hists_Bkg8000");
	Ex_40_48Bkg8k->Draw();

  	TFile* fileResults = TFile::Open("ParticlesOnly/Ex_" + TString(std::to_string(ExStart)) + "_" + TString(std::to_string(ExEnd)) + ".root","RECREATE");
   	fileResults->cd();

	//Get the signal histogram and copy it into the new file:
	TDirectory *dir1 = (TDirectory*)Hists->FindObject("Ex_vs_Gammas_Hists");
	TDirectory *dir2 = (TDirectory*)dir1->FindObject("QQQ_v_Gam");
	TDirectory *dir3 = (TDirectory*)dir2->FindObject("1D_Hists");
	TH1D *SigHist = (TH1D*)dir3->FindObject("Ex_" + TString(std::to_string(ExStart)) + "_" + TString(std::to_string(ExEnd)));

	//Get the background histogram and copy it into the new file:
	TDirectory *dir4 = (TDirectory*)dir2->FindObject("1D_Hists_Bkg8000");
	TH1D *BackHist = (TH1D*)dir4->FindObject("Ex_" + TString(std::to_string(ExStart)) + "_" + TString(std::to_string(ExEnd)) + "Bkg8k");

	std::vector<std::vector<int>> rbinvec;
	std::vector<std::vector<double>> rbinvecsigma;
	std::vector<int> veccont;
	std::vector<double> vecsigma;

//	TH1D *BackHist2 = new TH1D("BackHist2","",8000,0,8000);

	for (int rbin = 1; rbin < 11; rbin++){
	if (rbin != 3 && rbin != 6 && rbin != 9 && rbin != 7){

		TH1D *SigRBin = (TH1D*)SigHist->Clone();
		TH1D *BackHist2 = (TH1D*)SigHist->Clone();
		TH1D *BackRBin = (TH1D*)BackHist->Clone();	

		//TH1D *RatioHist = new TH1D("RatioHist","Ratio Ex ",8000,0,8000);
		//RatioHist->Add(SigRBin,1);

		TH1D *RatioHist = (TH1D*)SigRBin->Clone();
		TH1D *SigRBin2 = (TH1D*)SigRBin->Clone();


		SigRBin->Rebin(rbin);
		SigRBin2->Rebin(rbin);
	//	if (rbin == 1) SigRBin->Sumw2();
		BackRBin->Rebin(rbin);
		BackHist2->Rebin(rbin);
	//	if (rbin == 1) BackRBin->Sumw2();
		RatioHist->Rebin(rbin);
		RatioHist->SetTitle("Peak Significance");
	
		int binstop = (int)8000/rbin;
		int counter = 0;
		double RatioError = 0;
		double Ratio; 
		double diff = -5;

//		RatioHist->Divide(BackRBin);
//		TH1D *RatioHist2 = (TH1D*)RatioHist->Clone();

		//Make the first element in the vector the rbin value.
		veccont.push_back(rbin);
		vecsigma.push_back(rbin);

		for (int bin = 1; bin <= binstop; bin++){

			double Bkg = (double)BackRBin->GetBinContent(bin);
			double Sig = (double)SigRBin->GetBinContent(bin);

			double BkgErr = (double)BackRBin->GetBinError(bin);

			BackHist2->SetBinContent(bin,Bkg);

			//if (bin > 20 && Bkg != 0) diff = (Sig-Bkg)/BkgErr;
			//else diff = -5;
			if (bin > 20 && Bkg != 0 && (2*Sig*log(1+(Sig-Bkg)/Bkg)-2*(Sig-Bkg)) > 0 && (1+(Sig-Bkg)/Bkg) > 0 && Sig > Bkg) diff = sqrt(2*Sig*log(1+(Sig-Bkg)/Bkg)-2*(Sig-Bkg));
			else diff = 0;

			//RatioHist->SetBinError(bin, RatioError);
			RatioHist->SetBinContent(bin, diff);

			//Make vecs for events above threshold
			if (diff >= 2 && bin < (ExEnd*100 + 1)){
				veccont.push_back(bin*rbin);
				vecsigma.push_back(diff);
			}
			 

		}

		rbinvec.push_back(veccont);
		rbinvecsigma.push_back(vecsigma);
		veccont.clear();
		vecsigma.clear();

		//All the canvas stuff now goes here.

		//Size of canvas (used to make things pretty)
		int H_ref = 850;
		int W_ref = 900;

		// references for T, B, L, R
		float T = 0.08*H_ref;
		float B = 0.12*H_ref;
		float L = 0.12*W_ref;
		float R = 0.04*W_ref;
		//Create the canvas and make it look nice
		TCanvas* canv1 = new TCanvas("met" + TString(std::to_string(rbin)),"met" + TString(std::to_string(rbin)),50,50,W_ref,H_ref);
		canv1->cd();
		canv1->SetFillColor(0);
		canv1->SetBorderMode(0);
		canv1->SetFrameFillStyle(0);
		canv1->SetFrameBorderMode(0);
		canv1->SetLeftMargin( L/W_ref );
		canv1->SetRightMargin( R/W_ref );
		canv1->SetTopMargin( T/H_ref );
		canv1->SetBottomMargin( B/H_ref );
		canv1->SetTickx(0);
		canv1->SetTicky(0);
		canv1->SetGrid();
		gStyle->SetGridStyle(3); 

		//Need two TPads, one for the histograms and one for the ratio plots:
		TPad *p1a = new TPad("p1a","",0.,.3,1.,1.);
		p1a->SetBottomMargin(0.2);
		p1a->Draw();
		TPad *p1b = new TPad("p1b","",0.,0.,1.,.4);
		p1b->SetTopMargin(.1);
		p1b->SetBottomMargin(0.2);
		p1b->Draw();
		p1a->cd();
		p1a->SetGridx();
		p1a->SetLogy();

		gStyle->SetOptStat(0);
		gPad->Update();
		
		//Draw SigRBin and BackRBin on the same pad
		SigRBin->Draw("E");
		SigRBin2->Draw("SAME");
		SigRBin->GetYaxis()->SetTitle("Counts");
		SigRBin->GetYaxis()->CenterTitle();
		BackRBin->SetLineColor(kRed);
		BackHist2->SetLineColor(kRed);
		BackRBin->Draw("SAME E");
		BackHist2->Draw("SAME");
		gPad->Update();

		p1b->cd();

		p1b->SetGridx();
		p1b->SetGridy();

		RatioHist->Draw("");
//		RatioHist2->Draw("SAME");

		RatioHist->GetXaxis()->SetTitle("Gamma Ray Energy (keV)");
		RatioHist->GetYaxis()->SetTitle("Significance");
		RatioHist->GetXaxis()->SetLabelSize(0.06);
		RatioHist->GetYaxis()->SetLabelSize(0.06);
		RatioHist->GetXaxis()->SetTitleSize(0.06);
		RatioHist->GetYaxis()->SetTitleOffset(.5);
		RatioHist->GetYaxis()->CenterTitle();
		RatioHist->GetXaxis()->CenterTitle();
		RatioHist->GetYaxis()->SetTitleSize(0.06);
		
		TLine *line = new TLine(0,2,8000,2);
		line->Draw("SAME");
	
		gStyle->SetOptStat(0);
		gPad->Update();

		canv1->Write();

		SigRBin->SetName("RBin" + TString(std::to_string(rbin)) + "_Sig");
		BackRBin->SetName("RBin" + TString(std::to_string(rbin)) + "_Back");
		RatioHist->SetName("Ratio" + TString(std::to_string(rbin)));

	

	}
	}

	ofstream outfile("ParticlesOnly/Ex_" + std::to_string(ExStart) + "_" + std::to_string(ExEnd) + ".txt");

	int LgRbinVec = 0;

	for (int i = 0; i < rbinvec.size(); i++){

		if (rbinvec[i].size() > LgRbinVec) LgRbinVec = rbinvec[i].size();

		cout << rbinvec[i].size() << endl;


	}

	
	for (int i = 0; i < rbinvec.size(); i++){

		for (int j = 0; j <= LgRbinVec; j++){
		
			if (j > rbinvec[i].size()){
				rbinvec[i].push_back(0);
				rbinvecsigma[i].push_back(0);
			}

		}

	}

	for (int i = 0; i < LgRbinVec; i++){
		
		outfile << rbinvec[0][i] << " " << rbinvecsigma[0][i]
			<< " "
			<< rbinvec[1][i] << " " << rbinvecsigma[1][i]
			<< " "
			<< rbinvec[2][i] << " " << rbinvecsigma[2][i]
			<< " "
			<< rbinvec[3][i] << " " << rbinvecsigma[3][i]
			<< " "
			<< rbinvec[4][i] << " " << rbinvecsigma[4][i]
			<< " "
			<< rbinvec[5][i] << " " << rbinvecsigma[5][i]
			<< " "
			<< endl;
	}

	SigHist->Write();
	BackHist->Write();
	fileResults->Write();

















}
