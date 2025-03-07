//Standard inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions


//Including RooUtil
#include "EventNtuple/inc/RooUtil.h"

void RooUtilParticleInfoHist(string filename)
{
    //initialize RooUtil to begin reading files
    RooUtil util(filename);
    int eventNumber = util.GetNEntries();
    cout << filename << " has " << eventNumber << " entries."

    //Print the Outputs of Entry NUmber, PDG, nhits, startCode, and rank for each particle track
    for (int i_event=0; i_event < eventNumber;i_event++)
    {
        const auto& event = util.GetEvent(i_event);
        if (event.trkmcsim != nullptr)
        {
         for (const auto& trkmcsim : *(event.trkmcsim))
            {
                cout << "New Track!" << endl;
                for (const auto& sim : trkmcsim)
                    {  
                        cout << "Entry Number: " << i_event
                             << " PDG Number: " << sim.pdg
                             << " Tracker Hits: " << sim.nhits
                             << " Process Code: " << sim.startCode
                             << " Rank: " << sim.rank << endl;
                             //if want to manually print these out in the console, open the file in root, then enter the tree and use the scan feature-> ntuple->Scan("trkmcsim.pdg:trkmcsim.nhits:trkmcsim.startCode:trkmcsim.rank"
                    }
             }
         }
    }
}
