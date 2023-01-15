// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 27-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

/* system's library */
#include <iostream>
#include <string>

/* user's library */
#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter = ' ';

    // this function sets the field width of the current object to the value of parameter newWidth
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    // this function returns the field width of the current object
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    // this function extracts a token from string str referred to by the first parameter
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        string result = "";
        size_t init_pos = next_pos;
        next_pos = str.find(m_delimiter, init_pos);
        if (init_pos == next_pos)
        {
            more = false;
            throw "   ERROR: No token.\n";
        }
        else if (next_pos == string::npos)
        {
            result = str.substr(init_pos);
            m_widthField = max(result.length(), m_widthField);
            more = false;
        }
        else
        {
            result = str.substr(init_pos, next_pos - init_pos);
            m_widthField = max(result.length(), m_widthField);
            more = true;
        }
        result.erase(0, result.find_first_not_of(" "));
        result.erase(result.find_last_not_of(" ") + 1);
        next_pos++;
        return result;
    }

    // this function sets the delimiter for the following class to the character received
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    // this function returns the delimiter for the following class
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}