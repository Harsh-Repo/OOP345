// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 10-08-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>
#include <deque>

/* user's library */
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"

using namespace std;

namespace sdds 
{
	deque<CustomerOrder>g_pending{};
	deque<CustomerOrder>g_completed{};
	deque<CustomerOrder>g_incomplete{};

	// this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing
	void Workstation::fill(ostream& os) 
	{
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	// this function attempts to move the order order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder() 
	{
		bool result = false;
		if (!m_orders.empty()) 
		{
			if (m_orders.front().isItemFilled(getItemName())) 
			{
				if (!m_pNextStation) 
				{
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(move(m_orders.front()));
					else
						g_incomplete.push_back(move(m_orders.front()));
				}
				else 
				{
					*m_pNextStation += move(m_orders.front());
				}
				m_orders.pop_front();
				result = true;
			}
			else if (!getQuantity()) 
			{
				if (!m_pNextStation)
					g_incomplete.push_back(move(m_orders.front()));
				else
					*m_pNextStation += move(m_orders.front());
				m_orders.pop_front();
				result = true;
			}
		}
		return result;
	}

	// this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation
	void Workstation::setNextStation(Workstation* station) 
	{
		if (m_pNextStation != nullptr)
			delete m_pNextStation;
		m_pNextStation = station;
	}

	// this query returns the address of next Workstation
	Workstation* Workstation::getNextStation() const 
	{
		return m_pNextStation;
	}

	// this query inserts the name of the Item for which the current object is responsible into stream os following the format
	// ITEM_NAME --> NEXT_ITEM_NAME
	void Workstation::display(ostream& os) const 
	{
		if (m_pNextStation) 
		{
			os << getItemName() << " --> " << (*m_pNextStation).getItemName() << endl;
		}
		else {
			os << getItemName() << " --> End of Line" << endl;
		}
	}

	// this function moves the CustomerOrder referenced in parameter newOrder to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}