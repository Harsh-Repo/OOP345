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

/* user's library */
#include "Processor.h"

using namespace std;

namespace sdds
{
    // custom constructor
    Processor::Processor(CentralUnit<Processor>* host, string brand, string code, int power) :
        m_host{host}, m_brand{brand}, m_code{code}, m_power{power}, m_current{nullptr}
    {
    }

    // this function checks for jobs assigned to the processor and then performs the actions accordingly
    void Processor::run()
    {
        if (m_host == nullptr || m_current == nullptr)
        {
            return;
        }
        try {
            (*m_current)(m_power);
            if (!(*m_current).is_active())
            {
                delete m_current;
                m_current = nullptr;
            }
        }
        catch (underflow_error& error)
        {
            (*m_host).log << "Processed over quota for ";
            (*m_current).display((*m_host).log);
            delete m_current;
            m_current = nullptr;
        }
    }

    // a true/false representation of the processor - returns true if a job is assigned else, returns false
    Processor::operator bool() const
    {
        return m_current != nullptr;
    }

    // this function assigns a job to the processor else, if already assigned reports an exception
    Processor& Processor::operator+=(Job*& job)
    {
        if (m_current != nullptr)
        {
            throw string("Job already assigned");
        }
        m_current = job;
        return *this;
    }

    // a query that returns the job currently assigned to the processor
    Job* Processor::get_current_job() const
    {
        return m_current;
    }

    // destructor
    sdds::Processor::~Processor()
    {
        delete m_current;
    }

    // this function takes the address of a callback function to register and run when a job finishes processing as an argument and sets the respective instance member - returns nothing
    void Processor::on_complete(void (CentralUnit<Processor>::* callback)(CentralUnit<Processor>&, Processor*))
    {
        (*this).callback = callback;
    }

    // this function takes, as an argument, an std::function callback to register and run when a job encounters an error during processing and sets the respective instance member - returns nothing
    void Processor::on_error(function<void(Processor*)> error)
    {
        (*this).error = error;
    }

    // operator overload -- makes Processor a functor
    void Processor::operator()()
    {
        if (m_host == nullptr || m_current == nullptr)
        {
            return;
        }
        try 
        {
            (*m_current)(m_power);
            if (!(*m_current).is_active())
            {
                if (callback != nullptr)
                {
                    ((*m_host).*callback)(*m_host, this);
                }
                delete m_current;
                m_current = nullptr;
            }
        }
        catch (underflow_error& err)
        {
            if (error != nullptr)
            {
                error(this);
            }
            delete m_current;
            m_current = nullptr;
        }
    }

    // friend helper
    ostream& operator<<(ostream& os, const Processor& p)
    {
        os << "(" << p.m_power << ") " << p.m_brand << " " << p.m_code;
        if (p.m_current != nullptr)
        {
            os << " processing ";
            p.m_current->display(os);
        }
        return os;
    }

    // this function frees the unit received and clears memory allocated for the job that was assigned to that unit
    void Processor::complete_job()
    {
        (*m_host).log << "[COMPLETE] ";
        (*m_current).display((*m_host).log);
        delete m_current;
        m_current = nullptr;
        (*m_host).log << " using " << *this << endl;
    }
}