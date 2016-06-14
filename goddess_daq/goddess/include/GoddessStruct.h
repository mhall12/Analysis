#ifndef GODDESSSTRUCT_H
#define GODDESSSTRUCT_H

#include "TVector3.h"

///Structure of gamma ray data from DGS
struct GamData {
	///The calibrated energy of the gamma.
	float en;
	///The type of gamma ray detector. GE=1, BGO=2
	int type;
	//The number of the gamma ray detector
	int num;
	///The time of the gamma relative to the beginning of the event.
	unsigned int time;
};

///Structure of silicon data from ORRUBA
struct SiData {
	///The energy deposited in the dE layer.
	float dE;
	///The energy deposited in the E1 layer.
	float E1;
	///The energy deposited in the E2 layer.
	float E2;
	///The event interation position.
	TVector3 pos;
	///The sector the silicon event occured
	int sector;
	///True if in the barrel, otherwise occured in the endcap.
	bool barrel;
	///True if upstream, otherwise occured downstream.
	bool upstream;
	///The string describing which sector the islicon stack is located in.
	std::string sectorStr;
	///The time of the particle relative to the beginning of the event.
	unsigned int time;
        ///The front side strip number dE
        int PstripdE;
	///The front side strip number E1
	int PstripE1;
	int PstripE2;
        ///The back side strip number
        int NstripdE;
        int NstripE1;
        int NstripE2;
	int depth;
	int throwaway;
  
};

///Structure of the ion chamber data, including the scintillator.
struct IonData {
	///The energy deposited in the dE anodes.
	float dE;
	///The residaul energy in resE anodes.
	float resE;
	///The energy deposited in the E1 anodes.
	float E;
	///Energy deposited in the siPMTs.
	float scintE[4];
	///Timing of the siPMTs.
	float scintT[4];
	///The time of the ion relative to the beginning of the event.
	unsigned int time;
};
#endif
