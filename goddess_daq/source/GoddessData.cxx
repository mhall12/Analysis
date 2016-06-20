#include "GoddessData.h"

//ROOT Headers
#include "TDirectory.h"
#include "TFile.h"
#include "TMath.h"

//GEBSort Headers
#include "gdecomp.h"

//GODDESS Headers
#include "Detector.h"
#include "QQQ5.h"
#include "superX3.h"
#include "BB10.h"
#include "LiquidScint.h"

#include <iostream>

GoddessData::GoddessData(std::string configFilename)
{
	config = new GoddessConfig("goddess.position",configFilename);

	gamData = new std::vector<GamData>;
	siData = new std::vector<SiData>;
	ionData = new std::vector<IonData>;
	siCont = new std::vector<SiData>;
	siContBack = new std::vector<SiData>;

	gDirectory->pwd();
	TFile *f = gDirectory->GetFile();
	if (!f) {
		std::cerr << "ERROR: Not in a ROOT File?\n";
		return;
	}

	f->cd("/trees");
	tree=new TTree("god","GODDESS Tree");
	tree->Branch("timestamp",&firstTimestamp);
	tree->Branch("gam",&gamData);
	tree->Branch("si",&siData);
	tree->Branch("ic",&ionData);
	tree->Branch("test",&test);

	// ORRUBA histograms
	f->cd("/hists");
	TDirectory *dirOrruba = gDirectory->mkdir("orruba");
	dirOrruba->cd();
	TDirectory *dirRaw = gDirectory->mkdir("raw");
	dirRaw->cd();
	enRawA = new TH2F("enRawA","Raw Analog Energies;Energy [Ch];Channel",4196,0,4096,400,0,400);
	enRawD = new TH2F("enRawD","Raw Digital Energies;Energy [Ch];Channel",4196,0,1E6,400,0,400);
	enCalA = new TH2F("enCalA","Calibrated Analog Energies;Energy [MeV];Channel",4196,0,4096,400,0,400);
	enCalD = new TH2F("enCalD","Calibrated Digital Energies;Energy [MeV];Channel",4196,0,4096,400,0,400);
	analogMult = new TH1F("analogMult", "Number of triggers in the analog system;Multiplicty;Counts / Multiplicty", 5,0,5);
	analogADCMult = new TH1F("analogADCMult", "Number of ADCs readout per trigger;Multiplicty;Counts / Multiplicty", 400,0,400);
	digitalMult = new TH1F("digitalMult", "Number of triggers in the digital system;Multiplicty;Counts / Multiplicty", 400,0,400);
	hDetPosMult = new TH1F("detPosMult", "Number of sectors hit in an event;Sector Multiplicity;Counts / Multiplicity", 32,0,32);
	detMult = new TH1F("detMult", "Number of detectors hit in an event; Detector Multiplicity;Counts / Multiplicty",48,0,48);

	dirOrruba->cd();
	endcapHitPatternUpstream = new TH2F("hitEndcapUp","Upstream Endcap Hit Pattern",16,0,TMath::TwoPi(),32,0,32);
	endcapHitPatternDownstream = new TH2F("hitEndcapDown","Downstream Endcap Hit Pattern",16,0,TMath::TwoPi(),32,0,32);
	sX3HitPattern = new TH2F("sX3HitPattern","Cumulative SuperX3 Hit Pattern;Azimuthal Angle [deg];Z Position [mm]",48,0,360,8,-80,80);


	//dirOrruba->cd();
	//InitSuperX3Hists();

	//dirOrruba->cd();
	//InitQQQ5Hists();

	//dirOrruba->cd();
	//InitBB10Hists();

	//dirOrruba->cd();
	//InitGammaHists();

	//gDirectory->cd("/hists");
	//TDirectory *dirLiquidScint = gDirectory->mkdir("LiquidScint");
	//dirLiquidScint->cd();
	//InitLiquidScintHists();

}
void GoddessData::InitBB10Hists() {
	TClonesArray* bb10s =config->GetBB10s();
	int nbb10s = bb10s->GetEntries();
	TDirectory *dirBB10 = gDirectory->mkdir("bb10");
	
	for (int i = 0; i < nbb10s; i++) {
	  BB10* bb10 = (BB10*) bb10s->At(i);
	        std::string name = bb10->GetPosID();
		int daqType = bb10->GetDAQType();
		dirBB10->cd();
		TDirectory *dirDet = gDirectory->mkdir(name.c_str());
		dirDet->cd();
		gDirectory->mkdir("en")->cd();

		int maxRawEn = 4096;
		int BB10_Enbins = 4096;
		if (daqType == GEB_TYPE_DFMA) maxRawEn = 5e5;
		BB10RawEn.emplace(name,new TH2F(Form("BB10RawEn_%s",name.c_str()),Form("Raw BB10 %s energy per strip;Energy [Ch];Channel",name.c_str()), BB10_Enbins,0,maxRawEn,8,0,8));
		BB10CalEn.emplace(name,new TH2F(Form("BB10CalEn_%s",name.c_str()),Form("Cal BB10 %s energy per strip;Energy [Ch];Channel",name.c_str()), BB10_Enbins,0,15,8,0,8));
		
	}
}

void GoddessData::InitQQQ5Hists() {

	TClonesArray *qqq5s=config->GetQQQ5s();
	int nqqq5s = qqq5s->GetEntries();
	TDirectory *dirQQQ5 = gDirectory->mkdir("qqq5");

	for (int i = 0; i < nqqq5s; i++) {
	  QQQ5* qqq5 = (QQQ5*)qqq5s->At(i);
		std::string name = qqq5->GetPosID();
		int daqType = qqq5->GetDAQType();
		dirQQQ5->cd();
		TDirectory *dirDet = gDirectory->mkdir(name.c_str());
		dirDet->cd();
		gDirectory->mkdir("en")->cd();

		int maxRawEn = 4096;
		int qqq5_Enbins = 4096;
		if (daqType == GEB_TYPE_DFMA) maxRawEn = 5e5;
		
		QQQenRawFront.emplace(name,new TH2F(Form("QQQenRawFront_%s",name.c_str()),Form("Raw QQQ5 %s energy per front strip;Energy [Ch];Channel",name.c_str()), qqq5_Enbins,0,maxRawEn,32,0,32));

		QQQenCalFront.emplace(name,new TH2F(Form("QQQenCalFront_%s",name.c_str()),Form("Cal QQQ5 %s energy per front strip;Energy [MeV];Channel",name.c_str()), qqq5_Enbins,0,15,32,0,32));

		QQQenRawBack.emplace(name,new TH2F(Form("QQQenRawBack_%s",name.c_str()),Form("Raw QQQ5 %s energy per back strip;Energy [Ch];Channel",name.c_str()), qqq5_Enbins,0,maxRawEn,4,0,4));

		QQQenCalBack.emplace(name,new TH2F(Form("QQQenCalBack_%s",name.c_str()),Form("Cal QQQ5 %s energy per back strip;Energy [MeV];Channel",name.c_str()), qqq5_Enbins,0,15,4,0,4));

		dirDet->cd();
		gDirectory->mkdir("mult")->cd();

		QQQHitPat.emplace(name,new TH2F(Form("QQQHitPat_%s",name.c_str()),Form("QQQ5 Hit Pattern %s;Front [strip];Back [strip]",name.c_str()),32,0,32,4,0,4));
		QQQFrontMult.emplace(name,new TH1F(Form("QQQFrontMult_%s",name.c_str()),Form("QQQ5 %s multiplicity;multiplicity",name.c_str()),20,0,20));
		QQQBackMult.emplace(name,new TH1F(Form("QQQBackMult_%s",name.c_str()),Form("QQQ5 %s multiplicitymultiplicity",name.c_str()),20,0,20));
	}

}
void GoddessData::InitSuperX3Hists() {
	TDirectory *dirSX3 = gDirectory->mkdir("sx5");

	TClonesArray *sx3s = config->GetSuperX3s();
	int nsx3s = sx3s->GetEntries();

	for (int i=0;i< nsx3s;i++) {
		std::string name = ((superX3*)sx3s->At(i))->GetPosID();
		dirSX3->cd();

		superX3* sx3 = (superX3*)sx3s->At(i);
		int daqType = sx3->GetDAQType();
		
		TDirectory *dirDet = gDirectory->mkdir(name.c_str());
		dirDet->cd();
		gDirectory->mkdir("en")->cd();

		int maxRawEn = 4096;
		int sx3_Enbins = 4096;
		if (daqType == GEB_TYPE_DFMA) maxRawEn = 5e5;

		sX3stripEnRaw[name] = new TH2F(Form("sX3stripEnRaw%s",name.c_str()),
			Form("SuperX3 strip raw energy vs strip %s;energy [ch];strip", name.c_str()),sx3_Enbins,0,maxRawEn, 8, 0,8);
		sX3stripEnCal[name] = new TH2F(Form("sX3stripEnCal%s",name.c_str()),
			Form("SuperX3 strip cal energy vs strip %s;energy [keV];strip", name.c_str()),sx3_Enbins,0,maxRawEn, 8, 0,8);
		sX3backEnRaw[name] = new TH2F(Form("sX3backEnRaw%s",name.c_str()),
			Form("SuperX3 back raw energy vs strip %s;energy [ch];strip", name.c_str()),sx3_Enbins,0,maxRawEn, 4, 0,4);
		sX3backEnCal[name] = new TH2F(Form("sX3backEnCal%s",name.c_str()),
			Form("SuperX3 back cal energy vs strip %s;energy [keV];strip", name.c_str()),sx3_Enbins,0,15, 4, 0,4);
		sx3StripTotEn[name] = new TH2F(Form("sX3StripTotEn%s",name.c_str()),Form("SuperX3 total energy vs strip %s;energy [ch];strip", name.c_str()),1024,0,maxRawEn, 4, 0,4);
		
		dirDet->cd();
		gDirectory->mkdir("pos")->cd();

		sX3nearFar[name] = new TH2F*[4];
		sX3nearFarCal[name] = new TH2F*[4];
		sX3posRaw_enRaw[name] = new TH2F*[4];
		sX3posRaw_enCal[name] = new TH2F*[4];
		sX3posCal_enCal[name] = new TH2F*[4];
		
		for (int strip=0; strip < 4; strip++) {
			sX3posRaw_enCal[name][strip] = new TH2F(Form("sX3posRaw_enCal_%s_%i",name.c_str(),strip),
				Form("super X3 raw position vs cal energy %s_%i",name.c_str(),strip),512, -1,1,1024,0,maxRawEn);

			sX3posCal_enCal[name][strip] = new TH2F(Form("sX3posCal_enCal_%s_%i",name.c_str(),strip),
				Form("super X3 cal position vs cal energy %s_%i",name.c_str(),strip),512, -1,1,1024,0,maxRawEn);

			sX3posRaw_enRaw[name][strip] = new TH2F(Form("sX3posRaw_enRaw_%s_%i",name.c_str(),strip),
				Form("super X3 raw position vs raw energy %s_%i",name.c_str(),strip),512, -1,1,1024,0,maxRawEn);

			sX3nearFar[name][strip] = new TH2F(Form("sX3nearFar_%s_%i",name.c_str(),strip),
				Form("sX3 near strip vs far strip %s %i", name.c_str(),strip), 1024,0,maxRawEn,1024,0,maxRawEn);
			sX3nearFarCal[name][strip] = new TH2F(Form("sX3nearFarCal_%s_%i",name.c_str(),strip),
				Form("sX3 near strip vs far calibrated strip %s %i", name.c_str(),strip), 1024,0,maxRawEn,1024,0,maxRawEn);
		}

		dirDet->cd();
		gDirectory->mkdir("mult")->cd();

		sX3HitPat[name] = new TH2F(Form("sX3HitPat_%s",name.c_str()),
			Form("SuperX3 Hit Pattern %s;Front [strip];Back [strip]",name.c_str()),8,0,8,4,0,4);

		sX3frontMult[name] = new TH1F(Form("sX3FrontMult_%s",name.c_str()),
			Form("super X3 %s multiplicity;multiplicity",name.c_str()),20,0,20);

		sX3backMult[name] = new TH1F(Form("sX3BackMult_%s",name.c_str()),
			Form("super X3 %s multiplicity;multiplicity",name.c_str()),20,0,20);

	}

}
void GoddessData::InitLiquidScintHists() {
	std::vector<LiquidScint*> liquids = config->GetLiquidScints();
	int nliquids = liquids.size();

	for (int iLiq=0;iLiq<nliquids;iLiq++) {
		std::string name=liquids[iLiq]->GetDescription();
		LiquidScint_PSD_E[name] = new TH2F(Form("LiquidScint_PSD_E_%s",name.c_str()),Form("Liquid Scintillator PSD vs E %s",name.c_str()),512,0,4096,512,0,4096);
		LiquidScint_psdRaw[name] = new TH1F(Form("LiquidScint_PSD_%s",name.c_str()),Form("Liquid Scintillator PSD %s",name.c_str()),4096,0,4096);
		LiquidScint_enRaw[name] = new TH1F(Form("LiquidScint_E_%s",name.c_str()),Form("Liquid Scintillator E %s",name.c_str()),4096,0,4096);
		LiquidScint_tacRaw[name] = new TH1F(Form("LiquidScint_TAC_%s",name.c_str()),Form("Liquid Scintillator TAC %s",name.c_str()),4096,0,4096);
		hLiqRawEnNeuGate[name] = new TH1F(Form("hLiqRawEnNeuGate_%s",name.c_str()),Form("Liquid Scint Raw E, Neutron Gated %s;Energy [ch]",name.c_str()),4096,0,4096);
		hLiqPSDNeuGate[name] = new TH1F(Form("hLiqPSDNeuGate_%s",name.c_str()),Form("Liquid Scint PSD, Neutron Gated %s;PSD [ch]",name.c_str()),4096,0,4096);
		hLiqTACNeuGate[name] = new TH1F(Form("hLiqTACNeuGate_%s",name.c_str()),Form("Liquid Scint TAC, Neutron Gated %s;TAC [ch]",name.c_str()),4096,0,4096);
		hGamNeuGate[name] = new TH1F(Form("hGamNeuGate_%s",name.c_str()),Form("Gammas, Neutron Gated %s;Energy [ch]",name.c_str()),1000,0,4000);
		hGamVsLiqNeuGate[name] = new TH2F(Form("hGamVsLiqNeuGate_%s",name.c_str()),Form("Gammas vs Liquid E, Neutron Gated %s;Energy [ch]",name.c_str()),512,0,4096,500,0,4000);

	}
}

void GoddessData::InitGammaHists() {
		TDirectory *dirDet = gDirectory->mkdir("gamma");
		dirDet->cd();
		gDirectory->mkdir("gamma")->cd();

		upstreamGam= new TH1F("upstreamGam","gammas gated on upstream particles", 4096, 0, 4096);
		downstreamGam= new TH1F("downstreamGam","gammas gated on downstream particles", 4096, 0, 4096);
}

void GoddessData::Fill(GEB_EVENT *gebEvt, std::vector<DGSEVENT> *dgsEvts, std::vector<DFMAEVENT> *dgodEvts, std::vector<AGODEVENT> *agodEvts) {
	//Map of channels to suppress, This occurs if they were not found in the map.
	static std::map<std::pair<short, short>, bool> suppressCh;

	//Loop over GEB_event and get the lowest timestmap
	firstTimestamp = gebEvt->ptgd[0]->timestamp;
	for (int i = 1; i < gebEvt->mult; i++)
		if (gebEvt->ptgd[i]->timestamp < firstTimestamp)
			firstTimestamp = gebEvt->ptgd[i]->timestamp;


	analogMult->Fill(agodEvts->size());
	// getting data from analog events
	for (size_t i=0;i<agodEvts->size();i++) {
		AGODEVENT agodEvt = agodEvts->at(i);

		analogADCMult->Fill(agodEvt.values.size());
		for (size_t j=0;j<agodEvt.values.size();j++) {
			unsigned long int value = agodEvt.values[j];
			unsigned short channel = agodEvt.channels[j];
			DAQchannel=channel;
			DAQCh_Energy[channel] = value;
			//unsigned long long timestamp = agodEvt.timestamp;

			enRawA->Fill(value,channel);

			std::pair<short, short> key = std::make_pair(GEB_TYPE_AGOD, channel);
			if (suppressCh.find(key) != suppressCh.end()) continue;

			Detector *det = config->SetRawValue(GEB_TYPE_AGOD, channel, value);
			if (!det) {
				suppressCh[key] = true;
				continue;
			}	
			//det->SetTimestamp(timestamp);

			std::string posID;
			orrubaDet* siDet = dynamic_cast<orrubaDet*>(det);
			IonChamber *ionChamber_ = dynamic_cast<IonChamber*>(det);
			LiquidScint *liquidScint_ = dynamic_cast<LiquidScint*>(det);
			if (siDet) {
				posID = siDet->GetPosID();
				//We only push the detector back onto the silicon stack if we haven't already added it.
				if(siDets.find(posID)==siDets.end()) {
					siDets[posID] = siDet;
					//siAnalogMult++;
				}
			}
			else if (liquidScint_) {
				posID = liquidScint_->GetDescription();
				liquidScints[posID] = liquidScint_;
			}
			else if (ionChamber_) {
				posID = "ion";
				ionChamber = ionChamber_;
			}

			firedDets[posID] = det;
		}
	}

	digitalMult->Fill(dgodEvts->size());
	// getting data from digital events	
	for (size_t i=0;i<dgodEvts->size();i++) {
		DFMAEVENT dgodEvt = dgodEvts->at(i);
		unsigned int value=dgodEvt.ehi;
		unsigned short channel=dgodEvt.tid;
		//unsigned long long timestamp = dgodEvt.LEDts;

		DAQchannel=channel;
		//DAQCh_Energy[channel] = value; //filling this will overwrite the analog
		enRawD->Fill(value,channel);

		std::pair<short,short> key=std::make_pair(GEB_TYPE_DFMA,channel);
		if (suppressCh.find(key) != suppressCh.end()) {
			continue;
		}

		Detector *det=config->SetRawValue(GEB_TYPE_DFMA,channel,value);
		if (!det) {
			suppressCh[key]=true;
			continue;
		}
		//siDetContactMult++;

		//Take whatever the timestamp is for this channel.
		//	This is not clear that it is the best method as one detecotr may have various 
		//	timestamps
		//det->SetTimestamp(timestamp);

		std::string posID;
		orrubaDet* siDet = dynamic_cast<orrubaDet*>(det);
		IonChamber *ionChamber_ = dynamic_cast<IonChamber*>(det);
		LiquidScint *liquidScint_ = dynamic_cast<LiquidScint*>(det);
		if (siDet) {
			posID = siDet->GetPosID();
			//We only push the detector back onto the silicon stack if we haven't already added it.
			if(siDets.find(posID)==siDets.end()) {
				siDets[posID] = siDet;
				//siDigitalMult++;
			}
		}
		else if (liquidScint_) {
			posID = liquidScint_->GetDescription();
			liquidScints[posID] = liquidScint_;
		}
		else if (ionChamber_) {
			posID = "ion";
			ionChamber = ionChamber_;
		}

		firedDets[posID] = det;
	}

	//FillHists(dgsEvts);
	FillTrees(dgsEvts,dgodEvts,agodEvts);

	//We clear everything here since we know what was actually fired.
	for (auto itr = firedDets.begin(); itr != firedDets.end(); ++itr) {
		itr->second->Clear();
	}
	firedDets.clear();
	siDets.clear();
	liquidScints.clear();
	
	for (int i = 0; i < 400; i++) {DAQCh_Energy[i] = 0.0;}
	
}

void GoddessData::FillHists(std::vector<DGSEVENT> *dgsEvts) {
	std::map<std::string, int> numSectorHits;

	unsigned short numDetsOverThresh = 0;
	// loop over fired detectors
	for (auto detItr=siDets.begin();detItr!=siDets.end(); ++detItr) {
		//Get detector pointer from iteratot
		orrubaDet* det = detItr->second;
		//Get some information about the detector.
		std::string detPosID = det->GetPosID();
		std::string detType = det->IsA()->GetName();
		//unsigned short sector = det->GetSector();
		
		if (det->GetContactMult()) numDetsOverThresh++;

		//Get the maps of the raw and calibrated energies for front and back.
		// Each map has the channel that fired as the key.
		siDet::ValueMap frontRawEn = det->GetRawEn(siDet::pType);
		siDet::ValueMap frontCalEn = det->GetCalEn(siDet::pType);
		siDet::ValueMap backRawEn = det->GetRawEn(siDet::nType);
		siDet::ValueMap backCalEn = det->GetCalEn(siDet::nType);

		//Handle BB10 detectors.
		if(detType =="BB10"){
		  //---Raw Energy---
		  for (auto itr=frontRawEn.begin(); itr!=frontRawEn.end();++itr) {
		    BB10RawEn[detPosID]->Fill(itr->second, itr->first);
		  }
		  //---Cal Energy---
		  for (auto itr=frontCalEn.begin(); itr!=frontCalEn.end();++itr) {
		    BB10CalEn[detPosID]->Fill(itr->second, itr->first);
		  }
		}
		//Handle QQQ5 detectors.
		else if (detType == "QQQ5") {
			//---Raw Energy---
			for (auto itr=frontRawEn.begin(); itr!=frontRawEn.end();++itr) {
			        QQQenRawFront[detPosID]->Fill(itr->second, itr->first);
			}
			for (auto itr=backRawEn.begin(); itr!=backRawEn.end();++itr) {
				QQQenRawBack[detPosID]->Fill(itr->second, itr->first);
			}

			//Lets ignore the hits with all strips below threhsold.
			if (det->GetContactMult() == 0) {
				continue;
			}

			//---Multiplicty---
			QQQFrontMult[detPosID]->Fill(frontCalEn.size());
			QQQBackMult[detPosID]->Fill(backCalEn.size());

			//---Cal Energy---
			for (auto itr=frontCalEn.begin(); itr!=frontCalEn.end();++itr) {
				QQQenCalFront[detPosID]->Fill(itr->second, itr->first);
			}
			for (auto itr=backCalEn.begin(); itr!=backCalEn.end();++itr) {
				QQQenCalBack[detPosID]->Fill(itr->second, itr->first);
			}

			//---Hit Patterns---
			TH2F *endcapHitPattern;
			if (det->GetUpStream()) endcapHitPattern = endcapHitPatternUpstream;
			else endcapHitPattern = endcapHitPatternDownstream;
			for (auto itrFront=frontCalEn.begin();itrFront!=frontCalEn.end();++itrFront) {
				for (auto itrBack=backCalEn.begin();itrBack!=backCalEn.end();++itrBack) {
					QQQHitPat[detPosID]->Fill(itrFront->first,itrBack->first);
					float angle = ((QQQ5*)det)->GetAzimuthalBins()[itrBack->first] * TMath::DegToRad() + TMath::Pi()/16;
					endcapHitPattern->Fill(angle,itrFront->first);
				}
			}
		} //Done with QQQ5 detectors
		//Handle Super X3 detectors
		else if (detType == "superX3") {
			superX3 *sx3= (superX3*) det;

			//---Raw Energy---
			for (auto itr=frontRawEn.begin(); itr!=frontRawEn.end();++itr) {
				sX3stripEnRaw[detPosID]->Fill(itr->second, itr->first);
			}
			for (auto itr=backRawEn.begin(); itr!=backRawEn.end();++itr) {
				sX3backEnRaw[detPosID]->Fill(itr->second,itr->first);
			}
			
			//---Raw Positions---
			//for loop over 8 contacts/4 strips
			for (int i=0;i<4;i++) {
			  unsigned short near = sx3->GetNearContact(i);
			  unsigned short far = sx3->GetFarContact(i);
			  if ( (frontRawEn.find(near)!=frontRawEn.end()) && (frontRawEn.find(far)!=frontRawEn.end()) ) {
				  sX3posRaw_enRaw[detPosID][i]->Fill( ((frontRawEn[far]-frontRawEn[near])/(frontRawEn[far]+frontRawEn[near])) , (frontRawEn[far] + frontRawEn[near]) );
				  sX3nearFar[detPosID][i]->Fill(frontRawEn[far], frontRawEn[near]);
				  sx3StripTotEn[detPosID]->Fill(frontRawEn[far]+frontRawEn[near], i );
			  }
			}	

			//Lets ignore the detectors with all strips below threhsold.
			if (det->GetContactMult() == 0) {
				continue;
			}
			sX3frontMult[detPosID]->Fill(frontCalEn.size());
			sX3backMult[detPosID]->Fill(backCalEn.size());
			
			//---Cal Energy---
			for (auto itr=frontCalEn.begin(); itr!=frontCalEn.end();++itr) {
				sX3stripEnCal[detPosID]->Fill(itr->second, itr->first);
			}
			for (auto itr=backCalEn.begin(); itr!=backCalEn.end();++itr) {
				sX3backEnCal[detPosID]->Fill(itr->second,itr->first);
			}

			
			//for loop over 8 contacts/4 strips
			/// -- Trying to take the values that were further calibrated in superX3 class 
			/// -- and fill histograms here. All are returning zeros.
			for (int i=0;i<4;i++) {
			  unsigned short near = sx3->GetNearContact(i);
			  unsigned short far = sx3->GetFarContact(i);
			        if ((frontCalEn.find(near)!=frontCalEn.end()) && (frontCalEn.find(far)!=frontCalEn.end())) {
				  sX3posRaw_enCal[detPosID][i]->Fill(sx3->GetStripPosRaw()[i],sx3->GetStripEnergies()[i]);
				  sX3posCal_enCal[detPosID][i]->Fill(sx3->GetStripPosCal()[i],sx3->GetStripEnergies()[i]);
				  sX3nearFarCal[detPosID][i]->Fill(sx3->GetNearCalEnergy()[i],sx3->GetFarCalEnergy()[i]);
				}
			}
			
			numSectorHits[detPosID]++;
			// hit pattern
			for (auto itrFront=frontCalEn.begin();itrFront!=frontCalEn.end();++itrFront) {
				for (auto itrBack=backCalEn.begin();itrBack!=backCalEn.end();++itrBack) {
					sX3HitPat[detPosID]->Fill(itrFront->first,itrBack->first);
					float angle = ((superX3*)det)->GetAzimuthalCenterBins()[itrFront->first];
					float zPos = ((superX3*)det)->GetZCenterBins()[itrBack->first];
					sX3HitPattern->Fill(angle,zPos);
				}
			}
		} //Done with Super X3 detectors

		//Loop over the DGS events.
		for (size_t i=0;i<dgsEvts->size();i++) {
			//Fill a histogram based on upstream / downstream.
			if (det->GetUpStream()) {
				upstreamGam->Fill(dgsEvts->at(i).ehi);
			} else {
				downstreamGam->Fill(dgsEvts->at(i).ehi);
			}
		}
	} //Finished looping over fired silicon detectors.
	
	//Begin loop of liquid scintillators.
	for (auto lsItr=liquidScints.begin();lsItr!=liquidScints.end();++lsItr) {
	  std::string description = lsItr->first;
	  LiquidScint* liquidScint = lsItr->second;

		float rawEnergy = liquidScint->GetRawEnergy();
		float psd_ = liquidScint->GetRawPSD();
		float tac_ = liquidScint->GetRawTAC();
		
		//Fill Raw properties.
		LiquidScint_PSD_E[description]->Fill(rawEnergy,psd_);
		LiquidScint_enRaw[description]->Fill(rawEnergy);
		LiquidScint_psdRaw[description]->Fill(psd_);
		if(tac_ != 0){
			LiquidScint_tacRaw[description]->Fill(tac_);
		}

		//Rough neutron gates based on PSD and Timing.
		if ((description == "90deg" && psd_ > 350 && tac_ < 660) || (description == "downstream" && psd_ > 725 && tac_ > 2141)) {
			hLiqRawEnNeuGate[description]->Fill(rawEnergy);
			hLiqPSDNeuGate[description]->Fill(psd_);
			hLiqTACNeuGate[description]->Fill(tac_);
			for (size_t i=0;i<dgsEvts->size();i++) {
				hGamNeuGate[description]->Fill(dgsEvts->at(i).ehi);
				hGamVsLiqNeuGate[description]->Fill(rawEnergy,dgsEvts->at(i).ehi);
			}
		}
	} //End loop over liquid scintillators.

	//Fill the detector and position multiplicty histograms.
	detMult->Fill(numDetsOverThresh);
	hDetPosMult->Fill(numSectorHits.size());	
}

void GoddessData::FillTrees(std::vector<DGSEVENT> *dgsEvts, std::vector<DFMAEVENT> *dgodEvts, std::vector<AGODEVENT> *agodEvts) {
	///A map of SiData based on the position in the barrel.
	std::map<std::string, SiData> siMap;
	std::map<std::string, SiData> siMap2;

	for (auto detItr=siDets.begin();detItr!=siDets.end(); ++detItr) {

		orrubaDet* det = detItr->second;
		//Skip detectors with no contacts above threshold.
		//if (det->GetContactMult() == 0) continue;
		std::string detPosID = det->GetPosID();
		std::string detType = det->IsA()->GetName();
		
		std::string sectorStr = detPosID.substr(0,detPosID.find('_'));

		siDet::ValueMap frontRawEn = det->GetRawEn(siDet::pType);
		siDet::ValueMap frontCalEn = det->GetCalEn(siDet::pType);
		siDet::ValueMap backRawEn = det->GetRawEn(siDet::nType);
		siDet::ValueMap backCalEn = det->GetCalEn(siDet::nType);
		
		bool firstDet = false;
		if (siMap.find(sectorStr) == siMap.end()) firstDet = true;
		//Get the data matching the sector string, if it doens't exist a new datum is ctreated automatically.
		SiData *datum = &siMap[sectorStr];
		SiData *datumback = &siMap2[sectorStr];

		//If this sector is new we need to initialize it with default values.
		if (firstDet) {
			datum->dE = 0;
			datum->E1 = 0;
			//datum->E2 = 0;
			datum->sectorStr = sectorStr;
			datumback->sectorStr = sectorStr;
		}

		if (detType=="QQQ5"){
		for (auto itr=frontRawEn.begin(); itr!=frontRawEn.end();++itr){
			datum->dE = 0;
			datum->E1 = 0;
			datum->E2 = 0;
			datum->PstripdE = 0;
			datum->PstripE1 = 0;
			datum->PstripE2 = 0;

			if (det->GetDepth() == 0){
				datum->dE = itr->second;
				datum->PstripdE = itr->first;
			}
			else if (det->GetDepth() == 1){
				datum->E1 = itr->second;
				datum->PstripE1 = itr->first;
			}
//			else if (det->GetDepth() == 2){
//				datum->E2 = itr->second;
//				datum->PstripE2 = itr->first;
//			}

			datum->sectorStr = sectorStr;


				//for (auto itr2 = siMap.begin(); itr2 != siMap.end(); ++itr2) {
				//	SiData datum2 = itr2->second;
					//We only push back if there was an E1 value.
					//if (datum.E1) {
				//		siData->push_back(datum2);
					//}
			SiData datum2 = siMap.begin()->second;				//}
			//siData->push_back(datum2);
			siCont->push_back(datum2);

		}
/*
		for (auto itr2=backRawEn.begin(); itr2!=backRawEn.end();++itr2){

			datumback->NstripdE = 10;
			datumback->NstripE1 = 10;
			datumback->NstripE2 = 0;	

			if (det->GetDepth() == 0){
				datumback->NstripdE = itr2->first;
			}
			else if (det->GetDepth() == 1){
				datumback->NstripE1 = itr2->first;
			}
			//else if (det->GetDepth() == 2){
			//	datum->E2 = itr->second;
			//	datum->PstripE2 = itr->first;
			//}

			datumback->sectorStr = sectorStr;


				//for (auto itr2 = siMap.begin(); itr2 != siMap.end(); ++itr2) {
				//	SiData datum2 = itr2->second;
					//We only push back if there was an E1 value.
					//if (datum.E1) {
				//		siData->push_back(datum2);
					//}
			//}
			SiData datum3 = siMap2.begin()->second;
			//siData->push_back(datum2);
			siContBack->push_back(datum3);

		


		}
*/

		}
	}

//Triton Gates ************************
	double mul[32]={43356,47301,55277,68240,50739,44543,71183,54248,114490,96941,59191,56499,54775,59010,66248,66414,0,82813,57864,0,72850,78679,95508,138803,111410,71611,110175,68139,0,0,0,0};
	double exp[32]={-0.638,-0.649,-0.666,-0.698,-0.655,-0.63,-0.697,-0.656,-0.767,-0.748,-0.668,-0.654,-0.653,-0.666,-0.678,-0.676,0,-0.719,-0.653,0,-0.675,-0.691,-0.723,-0.791,-0.744,-0.676,-0.752,-0.675,0,0,0,0};

	double DCco1[32]={0,-0.00000603,0.00000319,-0.00000938,0.0000112,0.00000281,0.0000224,-0.00000189,0.000000328,-0.0000344,-0.0000397,-0.0000272,-0.0000356,0.00000487,0.0000072,-0.000014,0,-0.0000158,-0.0000104,-0.00000725,-0.0000224,-0.00002,-0.00000642,-0.0000112,0.000000662,-0.0000171,-0.0000144,-0.000012,0,0,0,0};
	double DCco2[32]={0,-0.399,-0.602,-0.278,-0.926,-0.689,-1.3,-0.542,-0.552,0.583,0.803,0.347,0.663,-0.766,-0.742,-0.158,0,-0.0636,-0.21,-0.422,0.156,0.0503,-0.396,-0.12,-0.666,-0.0441,-0.106,-0.276,0,0,0,0};
	double DCco3[32]={0,27000,27200,25300,27200,26200,29000,25900,25600,28000,26700,29600,27600,29100,27700,25700,0,26000,25700,27700,25000,25800,27600,26500,29300,27700,27600,26700,0,0,0,0};
//**************************************


	SiData data;
//	int used = 0;
	std::vector<int> usedEvt;
	for (int i=0;i<siCont->size();i++){
		if (siCont->at(i).dE > 0){
			for (int j=0;j<siCont->size();j++){
//				for (int k=0;k<siCont->size();k++){


						if (i!=j){
							data.dE = siCont->at(i).dE;
							data.E1 = siCont->at(j).E1;
//							data.E2 = siCont->at(k).E2;
							data.PstripdE = siCont->at(i).PstripdE;
							data.PstripE1 = siCont->at(j).PstripE1;
//							data.PstripE2 = siCont->at(k).PstripE2;
							//if (siContBack->size()>=i && siContBack->size()>=j){
							//data.NstripdE = siCont->size();//at(i).NstripdE;
							//data.NstripE1 = siContBack->size();//at(j).NstripE1;
							//}
							data.sectorStr = siCont->at(i).sectorStr;
							if (siCont->at(i).dE != 0 && siCont->at(j).E1 != 0 && data.PstripE1-data.PstripdE <= 5){
								if (data.sectorStr=="DA" && data.dE > mul[data.PstripdE]*pow(data.E1,exp[data.PstripdE])){
									siData->push_back(data);
									//usedEvt.push_back(i);
									//usedEvt.push_back(j);
								}
								if (data.sectorStr=="DC" && data.dE > (DCco1[data.PstripdE]*pow(data.E1,2) + DCco2[data.PstripdE]*data.E1 + DCco3[data.PstripdE])){
									siData->push_back(data);
									//usedEvt.push_back(i);
									//usedEvt.push_back(j);

								}
							}
						}
//				}
//				used = 0;
			}
		}
	}
//test comment
/*
	for (int i=0;i<siContBack->size();i++){
			data.NstripdE = siContBack->at(i).NstripdE;
			data.NstripE1 = siContBack->at(i).NstripE1;
			siData->push_back(data);

	}
*/
/*
//coefficients for the triton gates are as follows
	double mul[32]={43356,47301,55277,68240,50739,44543,71183,54248,114490,96941,59191,56499,54775,59010,66248,66414,0,82813,57864,0,72850,78679,95508,138803,111410,71611,110175,68139,0,0,0,0};
	double exp[32]={-0.638,-0.649,-0.666,-0.698,-0.655,-0.63,-0.697,-0.656,-0.767,-0.748,-0.668,-0.654,-0.653,-0.666,-0.678,-0.676,0,-0.719,-0.653,0,-0.675,-0.691,-0.723,-0.791,-0.744,-0.676,-0.752,-0.675,0,0,0,0};

//	double DCco1[32]={0,-0.00000603,0.00000319,-0.00000938,0.0000112,0.00000281,0.0000224,-0.00000189,0.000000328,-0.0000344,-0.0000397,-0.0000272,-0.0000356,0.00000487,0.0000072,-0.000014,0,-0.0000158,-0.0000104,-0.00000725,-0.0000224,-0.00002,-0.00000642,-0.0000112,0.000000662,-0.0000171,-0.0000144,-0.000012,0,0,0,0};
//	double DCco2[32]={0,-0.399,-0.602,-0.278,-0.926,-0.689,-1.3,-0.542,-0.552,0.583,0.803,0.347,0.663,-0.766,-0.742,-0.158,0,-0.0636,-0.21,-0.422,0.156,0.0503,-0.396,-0.12,-0.666,-0.0441,-0.106,-0.276,0,0,0,0};
//	double DCco3[32]={0,27000,27200,25300,27200,26200,29000,25900,25600,28000,26700,29600,27600,29100,27700,25700,0,26000,25700,27700,25000,25800,27600,26500,29300,27700,27600,26700,0,0,0,0};

	SiData data;
	int used0 = 0;
	std::vector<int> usedEvt0;
	//Loop over the Si Events and only save the ones we want.
	for (int i=0; i<siCont->size(); i++){
		used0 =0;
		for (int j=0; j<siCont->size(); j++){
			//the following checks to see if the event in question has been written already.
			for (int k=0; k < usedEvt0.size(); k++){
				if (i == usedEvt0[k] || j == usedEvt0[k]) used0 = 1;
			}//closes k for loop
			if (siCont->at(i).sectorStr=="DA" && siCont->at(j).sectorStr=="DA" && i!=j && used0 == 0){
				//the strip conditions work because there are no events with the strip number of E1 being less than dE
				if (siCont->at(i).dE != 0 && siCont->at(j).E1 !=0 && siCont->at(i).PstripdE >= siCont->at(j).PstripE1-4){
//					if (siCont->at(i).dE > mul[siCont->at(i).PstripdE]*pow(siCont->at(j).E1,exp[siCont->at(i).PstripdE])){
						data.dE = siCont->at(i).dE;
						data.E1 = siCont->at(j).E1;
						//data.E2 = siCont->at(i).E2;
						data.PstripdE = siCont->at(i).PstripdE;
						data.PstripE1 = siCont->at(j).PstripE1;
						//data.PstripE2 = siCont->at(i).PstripE2;
						data.sectorStr = siCont->at(i).sectorStr;
						usedEvt0.push_back(i);
						usedEvt0.push_back(j);
						siData->push_back(data);
//					}//closes gate if statement
				}//closes !=0 and rstrip if statement
				if (siCont->at(i).E1 != 0 && siCont->at(j).dE !=0 && siCont->at(i).PstripE1-4 <= siCont->at(j).PstripdE){
//					if (siCont->at(j).dE > mul[siCont->at(j).PstripdE]*pow(siCont->at(i).E1,exp[siCont->at(j).PstripdE])){
						data.dE = siCont->at(i).dE;
						data.E1 = siCont->at(j).E1;
						//data.E2 = siCont->at(i).E2;
						data.PstripdE = siCont->at(i).PstripdE;
						data.PstripE1 = siCont->at(j).PstripE1;
						//data.PstripE2 = siCont->at(i).PstripE2;
						data.sectorStr = siCont->at(i).sectorStr;
						usedEvt0.push_back(i);
						usedEvt0.push_back(j);
						siData->push_back(data);
//					}//closes gate if statement
				}//closes !=0 and rstrip if statement

			}//closes =DA if statement

			if (siCont->at(i).sectorStr=="DC" && siCont->at(j).sectorStr=="DC" && i!=j && used0 == 0){
				if (siCont->at(i).dE != 0 && siCont->at(j).E1 !=0 && siCont->at(i).PstripdE >= siCont->at(j).PstripE1-4){
					if (siCont->at(i).dE > DCco1[siCont->at(i).PstripdE]*pow(siCont->at(j).E1,2)+DCco2[siCont->at(i).PstripdE]*siCont->at(j).E1+DCco3[siCont->at(i).PstripdE]){
						data.dE = siCont->at(i).dE;
						data.E1 = siCont->at(j).E1;
						//data.E2 = siCont->at(i).E2;
						data.PstripdE = siCont->at(i).PstripdE;
						data.PstripE1 = siCont->at(j).PstripE1;
						//data.PstripE2 = siCont->at(i).PstripE2;
						data.sectorStr = siCont->at(i).sectorStr;
						usedEvt0.push_back(i);
						usedEvt0.push_back(j);
						siData->push_back(data);
					}
				}
				if (siCont->at(i).E1 != 0 && siCont->at(j).dE !=0 && siCont->at(i).PstripE1-4 <= siCont->at(j).PstripdE){
					if (siCont->at(j).dE > DCco1[siCont->at(j).PstripdE]*pow(siCont->at(i).E1,2)+DCco2[siCont->at(j).PstripdE]*siCont->at(i).E1+DCco3[siCont->at(j).PstripdE]){
						data.dE = siCont->at(i).dE;
						data.E1 = siCont->at(j).E1;
						//data.E2 = siCont->at(i).E2;
						data.PstripdE = siCont->at(i).PstripdE;
						data.PstripE1 = siCont->at(j).PstripE1;
						//data.PstripE2 = siCont->at(i).PstripE2;
						data.sectorStr = siCont->at(i).sectorStr;
						usedEvt0.push_back(i);
						usedEvt0.push_back(j);
						siData->push_back(data);
					}
				}





			}

		}//closes j for loop
	}//closes i for loop
*/
	if (siData->size() > 0){

	//Loop over the DGS events	
		for (unsigned int dgsEvtNum=0;dgsEvtNum<(dgsEvts->size());dgsEvtNum++) {
			GamData datum;
			datum.en = dgsEvts->at(dgsEvtNum).ehi;
			datum.type = dgsEvts->at(dgsEvtNum).tpe;
			datum.num = dgsEvts->at(dgsEvtNum).tid;
			gamData->push_back(datum);
		}
		
		tree->Fill();

	}

	//Deal with the ion chamber
	//if (firedDets.find("ion") != firedDets.end()) {
	//	IonData datum;
	//	datum.dE = ionChamber->GetAnodeDE();
	//	datum.resE = ionChamber->GetAnodeResE();
	//	datum.E = ionChamber->GetAnodeE();
	//	ionData->push_back(datum);
	//}

	//Deal with the neutron detectors
/*
	for (auto lsItr=liquidScints.begin();lsItr!=liquidScints.end();++lsItr) {
		LiquidScint *liqDet = lsItr->second;	
	}
*/

	//if (!gamData->empty() && !siData->empty()) tree->Fill();
	//std::cout << ionData->size() << '\n';
//only fill the tree if there was a triton event.


	gamData->clear();
	siData->clear();
	siCont->clear();
	siContBack->clear();
	//ionData->clear();
}

