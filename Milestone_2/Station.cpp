// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 27-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>

/* user's library */
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds
{
    size_t Station::m_widthField = 0u;
    size_t Station::id_generator = 0u;

    // custom 1-argument constructor
    Station::Station(const std::string& s)
    {
        Utilities u;
        s_id = ++Station::id_generator;
        bool object = true;
        size_t position = 0u;
        const char* space = " \t\n\r\f\v";
        try
        {
            s_itemname = u.extractToken(s, position, object);
            s_serialno = stoi(u.extractToken(s, position, object));
            s_stkitems = stoi(u.extractToken(s, position, object));
            Station::m_widthField = max(u.getFieldWidth(), Station::m_widthField);
            s_description = u.extractToken(s, position, object);
            s_description.erase(0, s_description.find_first_not_of(space));
            s_description.erase(s_description.find_last_not_of(space) + 1);
        }
        catch (string error)
        {
            cout << error;
        }
    }

    // this function returns the name of the current Station object
    const string& Station::getItemName() const
    {
        return s_itemname;
    }

    // this function returns the next serial number to be used on the assembly line and increments s_serialno
    size_t Station::getNextSerialNumber()
    {
        ++s_serialno;
        return s_serialno - 1;
    }

    // this function returns the remaining quantity of items in the Station object
    size_t Station::getQuantity() const
    {
        return s_stkitems;
    }

    // this function subtracts 1 from the available quantity; should not drop below 0
    void Station::updateQuantity()
    {
        s_stkitems == 0 ? s_stkitems = 0 : --s_stkitems;
    }

    // this function inserts information about the current object into stream os
    void Station::display(ostream& os, bool full) const
    {
        /*
        001 | Armchair        | 654321 |   10 | Upholstered Wing Chair
        */

        os << right << setw(3) << setfill('0') << s_id << " | ";
        os << left << setw(Station::m_widthField) << setfill(' ') << s_itemname << " | ";
        os << right << setw(6) << setfill('0') << s_serialno << " | ";
        if (full)
        {
            os << setw(4) << setfill(' ') << right << s_stkitems << " | ";
            os << s_description << endl;
        }
        else
            os << endl;
    }
}