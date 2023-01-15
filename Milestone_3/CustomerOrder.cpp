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
#include <algorithm>

/* user's library */
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0u;

    // custom 1-argument constructor
    CustomerOrder::CustomerOrder(const string& co)
    {
        Utilities u;
        bool object = true;
        size_t position = 0u;
        size_t index = 0u;
        try
        {
            m_name = u.extractToken(co, position, object);
            m_product = u.extractToken(co, position, object);
            m_cntItem = count(co.begin(), co.end(), u.getDelimiter()) - 1;
            if (m_cntItem)
                m_lstItem = new Item * [m_cntItem];
            while (object && m_cntItem)
            {
                m_lstItem[index] = new Item(u.extractToken(co, position, object));
                ++index;
            }
            CustomerOrder::m_widthField = max(u.getFieldWidth(), CustomerOrder::m_widthField);
        }
        catch (string error)
        {
            cout << error;
        }
    }

    // copy constructor -- if called, this function throws an exception
    CustomerOrder::CustomerOrder(const CustomerOrder& co)
    {
        throw false;
    }

    // move constructor -- this function promises to not to throw an exception
    CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
    {
        *this = move(co);
    }

    // move assignment -- this function promises to not to throw an exception
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
    {
        if (this != &co)
        {
            if (m_lstItem)
            {
                for (auto i = 0u; i < m_cntItem; ++i)
                    delete m_lstItem[i];
                delete[] m_lstItem;
            }
            m_name = co.m_name;
            m_product = co.m_product;
            m_cntItem = co.m_cntItem;
            m_lstItem = co.m_lstItem;
            co.m_name = "";
            co.m_product = "";
            co.m_cntItem = 0u;
            co.m_lstItem = nullptr;
        }
        return *this;
    }

    // destructor
    CustomerOrder::~CustomerOrder()
    {
        if (m_lstItem)
        {
            for (auto i = 0u; i < m_cntItem; ++i)
                delete m_lstItem[i];
            //delete[] m_lstItem;
            //m_lstItem = nullptr;
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    // this function returns true if all the items in the order have been filled; false otherwise
    bool CustomerOrder::isOrderFilled() const
    {
        bool result = true;
        for (auto i = 0u; i < m_cntItem; ++i)
            // !m_lstItem[i]->m_itemName == itemName ? result = false : result = true;
            if (m_lstItem[i]->m_isFilled == false) 
                result = false;
        return result;         
    }

    // this function returns true if all items specified by itemName have been filled
    // and if the item doesn't exist in the order, this query returns true
    bool CustomerOrder::isItemFilled(const string& itemName) const
    {
        // bool result = false;
        bool result = true;
        for (auto i = 0u; i < m_cntItem; ++i)
            // m_lstItem[i]->m_itemName == itemName ? result = false : result = true;
            if(m_lstItem[i]->m_itemName == itemName &&!m_lstItem[i]->m_isFilled) 
                result = false;
        return result;
    }

    // this modifier fills one item in the current order that the Station specified in the first parameter

    /*void CustomerOrder::fillItem(Station& station, ostream& os)
    {
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName.compare(station.getItemName())==0&& station.getQuantity()>0&&!m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity())
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled ";
                }
                else
                    os << "    Unable to fill ";
                    os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }*/
    void CustomerOrder::fillItem(Station& station, ostream& os)
    {
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    // m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled ";
                    os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                    break;
                }
                else
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }

    // this query displays the state of the current object in the format
    void CustomerOrder::display(ostream& os) const
    {
        /*
        CUSTOMER_NAME - PRODUCT
        [SERIAL] ITEM_NAME - STATUS
        [SERIAL] ITEM_NAME - STATUS
        ...
        */

        os << m_name << " - " << m_product << endl;
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << left << setw(CustomerOrder::m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }
}