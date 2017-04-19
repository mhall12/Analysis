// UserEventFilterTemplate version 161024 //

#include <iostream>

#include "SortManager.h"

bool SortManager::GetWriteEventFlag()
{
    bool flag = false;

//     if ( GEB_event->ptgd.size() > 0 )
//     {
//         for ( unsigned int i = 0; i < GEB_event->ptgd.size(); i++ )
//         {
//             if ( GEB_event->ptgd[i]->type == 16 )
//             {
//                 return false;
//             }
//         }
//     }

//     if ( gammaDets->size() > 0 )
//     {
// 
//     }
// 

//Triton Gates ************************
	double mul[32]={43356,47301,55277,68240,50739,44543,71183,54248,114490,96941,59191,56499,54775,59010,66248,66414,0,82813,57864,0,72850,78679,95508,138803,111410,71611,110175,68139,0,0,0,0};
	double exp[32]={-0.638,-0.649,-0.666,-0.698,-0.655,-0.63,-0.697,-0.656,-0.767,-0.748,-0.668,-0.654,-0.653,-0.666,-0.678,-0.676,0,-0.719,-0.653,0,-0.675,-0.691,-0.723,-0.791,-0.744,-0.676,-0.752,-0.675,0,0,0,0};

	double DCco1[32]={0,-0.00000603,0.00000319,-0.00000938,0.0000112,0.0000137,0.0000224,0.0000117,0.000000328,-0.0000344,-0.0000397,-0.0000272,-0.0000356,0.00000487,0.0000072,-0.000014,0,-0.0000158,-0.0000104,-0.00000725,-0.0000224,-0.00002,-0.00000642,-0.0000112,0.000000662,-0.0000171,-0.0000144,-0.000012,0,0,0,0};
	double DCco2[32]={0,-0.399,-0.602,-0.278,-0.926,-1.032,-1.3,-0.9889,-0.552,0.583,0.803,0.347,0.663,-0.766,-0.742,-0.158,0,-0.0636,-0.21,-0.422,0.156,0.0503,-0.396,-0.12,-0.666,-0.0441,-0.106,-0.276,0,0,0,0};
	double DCco3[32]={0,27000,27200,25300,27200,26480,29000,27479,25600,28000,26700,29600,27600,29100,27700,25700,0,26000,25700,27700,25000,25800,27600,26500,29300,27700,27600,26700,0,0,0,0};
//**************************************

    if ( siDets->size() > 0 )
    {
        for ( auto itr = siDets->begin(); itr != siDets->end(); itr++ )
        {
            SiDataBase siData = *itr;

            if ( siData.telescopeID == 1100 && siData.ESumLayer(0,false) > mul[siData.StripMaxLayer(0,false)]*pow(siData.ESumLayer(1,false),exp[siData.StripMaxLayer(0,false)]) && siData.StripMaxLayer(0,false) < 25 && siData.StripMaxLayer(1,false) < 25)
            {
                flag = true;
                break;
            }
	    if ( siData.telescopeID == 1102 && siData.ESumLayer(0,false) > (DCco1[siData.StripMaxLayer(0,false)]*pow(siData.ESumLayer(1,false),2) + DCco2[siData.StripMaxLayer(0,false)]*siData.ESumLayer(1,false) + DCco3[siData.StripMaxLayer(0,false)]) && siData.StripMaxLayer(0,false) < 25 && siData.StripMaxLayer(1,false) < 25)
            {
                flag = true;
                break;
            }

	    if (siData.telescopeID >= 2104 && siData.telescopeID <= 2110 && siData.telescopeID != 2106 && siData.ESumLayer(0,false) < 35000 && siData.ESumLayer(1,false) > 260000)//>= 2104 && siData.telescopeID <= 2110 && siData.telescopeID != 2106)
	    {
		flag = true;
		break;

	    }
        }
    }
// 
//     if ( ionChamber->size() > 0 )
//     {
// 
//     }

//     flag = true;

    return flag;
}
