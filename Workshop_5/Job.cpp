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

/* system's library */
#include <iostream>
#include <iomanip>
#include <exception>

/* user's library */
#include "Job.h"

using namespace std;

namespace sdds
{
    // default constructor
    Job::Job() : title{""}, indicating_units{0}, remaining_units{0}, active{false}
    {
    }

    // customer constructor - receives the title of the job
    Job::Job(string title) : title{title}
    {
        indicating_units = title.length() % 10 + 1;
        remaining_units = indicating_units;
        active = true;
    }

    // a query that returns whether the job is active or not
    bool Job::is_active() const
    {
        return active;
    }

    // a query that returns whether the job is complete or not
    bool Job::is_complete() const
    {
        return remaining_units == 0;
    }

    // a query that returns a copy of the title of the job
    string Job::name() const
    {
        return title;
    }

    // this function inserts the job details into the output stream (received as an argument) and returns nothing
    void Job::display(ostream& os) const
    {
        os << "`" << title << "` ";
        os << "[" << setfill('0') << setw(2) << remaining_units << "/";
        os << setfill('0') << setw(2) << indicating_units << " remaining]";
    }

    // helper function - displays the job details
    ostream& operator<<(ostream& os, Job& job)
    {
        job.display(os);
        return os;
    }

    void Job::operator()(unsigned int work)
    {
        if (work > remaining_units)
        {
            remaining_units = 0;
            active = false;
            throw underflow_error("The handled work [" + to_string(work) + "], is more than the remaining work [" + to_string(remaining_units) + "].");
        }
        else
        {
            remaining_units -= work;
            if (remaining_units == 0)
            {
                active = false;
            }
        }
    }
}

