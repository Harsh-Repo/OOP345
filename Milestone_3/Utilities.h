// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 10-08-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

/* system's library */
#include <iostream>

using namespace std;

namespace sdds
{
    class Utilities
    {
        size_t m_widthField{ 1u };
        static char m_delimiter;

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        string extractToken(const string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}
#endif // !SDDS_UTILITIES_H