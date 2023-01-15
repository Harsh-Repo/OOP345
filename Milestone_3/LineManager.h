// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 10-08-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SSDS_LINEMANAGER_H

/* system's library */
#include <iostream>
#include <vector>

/* user's library */
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"

using namespace std;

namespace sdds
{
    class LineManager
    {
        vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder{ 0u };
        Workstation* m_firstStation;

    public:
        LineManager(const string& file, const vector<Workstation*>& stations);
        void reorderStations();
        bool run(ostream& os);
        void display(ostream& os) const;
    };
}
#endif // !SDDS_LINEMANAGER_H

