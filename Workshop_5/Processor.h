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

#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

/* system's library */
#include <iostream>
#include <functional>
#include <string>

/* user's library */
#include "CentralUnit.h"
#include "Job.h"

using namespace std;

namespace sdds 
{
    class Processor 
    {
        CentralUnit<Processor>* m_host;
        string m_brand;
        string m_code;
        int m_power;
        Job* m_current = nullptr;
        void (CentralUnit<Processor>::* callback)(CentralUnit<Processor>&, Processor*) = nullptr;
        function<void(Processor*)> error = nullptr;

        public:
        Processor(CentralUnit<Processor>* host, string brand, string code, int power);
        void run();
        explicit operator bool() const;
        Processor& operator+=(Job*& job);
        Job* get_current_job() const;
        ~Processor();
        void on_complete(void (CentralUnit<Processor>::* callback)(CentralUnit<Processor>&, Processor*));
        void on_error(function<void(Processor*)> error);
        void operator()();
        Job* free();
        friend ostream& operator<<(ostream& os, const Processor& p);
        void complete_job();
    };
    ostream& operator<<(ostream& os, const Processor& p);
};
#endif