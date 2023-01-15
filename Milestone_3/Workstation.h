// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 10-08-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

/* system's library */
#include <iostream>
#include <deque>

/* user's library */
#include "Station.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds
{
    extern deque<CustomerOrder> g_pending;
    extern deque<CustomerOrder> g_completed;
    extern deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{ nullptr };

    public:
        Workstation(const string& w) : Station(w) {};
        Workstation(const Workstation& w) = delete;
        Workstation& operator=(const Workstation& w) = delete;
        Workstation(Workstation&& w) = delete;
        Workstation& operator=(Workstation&& w) = delete;
        void fill(ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}
#endif // !SDDS_WORKSTATION_H


