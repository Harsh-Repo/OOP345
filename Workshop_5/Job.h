/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 12/6/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */

#ifndef SDDS_JOB_H
#define SDDS_JOB_H

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

namespace sdds 
{
    class Job 
    {
        string title;
        unsigned int indicating_units;
        unsigned int remaining_units;
        bool active;

        public:
        Job();
        Job(string title);
        bool is_active() const;
        bool is_complete() const;
        string name() const;
        void display(ostream& os) const;
        void operator()(unsigned int work);
    };
    ostream& operator<<(ostream& os, Job& job);
};
#endif