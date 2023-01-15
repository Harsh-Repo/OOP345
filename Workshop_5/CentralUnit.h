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

#ifndef SDDS_CENTRAL_UNIT_H
#define SDDS_CENTRAL_UNIT_H

/* system's library */
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <utility>

/* user's library */
#include "Job.h"

using namespace std;

namespace sdds 
{
    template<typename T>
    class CentralUnit 
    {
        string m_type;
        T** m_items;
        static const int MAXIMUM_JOBS = 4;
        Job* m_jobs[MAXIMUM_JOBS];
        size_t m_size;
        size_t m_count;
        size_t m_max;

    public:
        ostream& log = cout;
        CentralUnit(string type, string fn);
        CentralUnit(const CentralUnit& cu);
        CentralUnit(CentralUnit&& cu);
        CentralUnit& operator=(const CentralUnit& cu) = delete;
        CentralUnit& operator=(CentralUnit&& cu);
        ~CentralUnit();
        CentralUnit& operator+=(string job_name);
        void run();
        bool has_jobs() const;
        size_t get_available_units() const;
        string readLine(string nextline, unsigned int& position);
        void complete_job(CentralUnit& cu, T* t);
        void operator+=(T* t);
        T* operator[](string title) const;
        void display() const;
    };
};

namespace sdds
{
    // custom constructor
    template<typename T>
    CentralUnit<T>::CentralUnit(string type, string fn) :
        m_type{type}, m_items{nullptr}, m_size{0}, m_count{0} 
    {
        unsigned int index = 0, w_cap = 0;
        string u_type, u_name;
        ifstream rfile(fn);
        string nextline;
        if (rfile.is_open())
        {
            while (rfile)
            {
                getline(rfile, nextline);
                if (rfile)
                {
                    index++;
                }
            }
            m_items = new T * [index];
            m_size = index;
            m_max = index;
            rfile.clear();
            rfile.seekg(0, ios::beg);
            index = 0;
            while (rfile)
            {
                getline(rfile, nextline);
                if (!rfile)
                {
                    break;
                }
                unsigned int position = 0;
                u_type = readLine(nextline, position);
                u_name = readLine(nextline, position);
                try
                {
                    w_cap = stoi(readLine(nextline, position));
                }
                catch (invalid_argument& error)
                {
                    w_cap = 1;
                }
                T* t = new T(this, u_type, u_name, w_cap);
                (*t).on_complete(&CentralUnit<T>::complete_job);
                (*t).on_error([this](T* unit)
                    {
                        (*this).log << "Failed to complete job " << (*unit).get_current_job()->name() << endl;
                        (*this).log << (get_available_units() + 1) << " units available." << endl;
                    });
                m_items[index] = t;
                index++;
            }
        }
        else
        {
            throw invalid_argument("File cannot be opened.");
        }
    }

    // copy constructor
    template<typename T>
    CentralUnit<T>::CentralUnit(const CentralUnit<T>& cu)
    {
        throw string("Cannot create a new instance from a copy");
    }

    // move constructor
    template<typename T>
    CentralUnit<T>::CentralUnit(CentralUnit<T>&& cu)
    {
        *this = cu;
    }

    // move assignment
    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator=(CentralUnit<T>&& cu)
    {
        if (this == &cu)
        {
            return *this;
        }
        swap(m_type, cu.m_type);
        swap(m_items, cu.m_items);
        swap(m_jobs, cu.m_jobs);
        swap(m_size, cu.m_size);
        swap(m_max, cu.m_max);
        swap(m_count, cu.m_count);
        return *this;
    }

    // destructor
    template<typename T>
    CentralUnit<T>::~CentralUnit()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            delete m_items[i];
        }
        delete[] m_items;
        for (size_t i = 0; i < m_count; i++)
        {
            delete m_jobs[i];
        }
    }

    // this function creates a new Job object that is added to the job queue, and returns a reference to the current central unit
    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator+=(string job_name)
    {
        if (m_count >= MAXIMUM_JOBS)
        {
            throw string("Job queue full!");
        }
        m_jobs[m_count++] = new Job(job_name);
        return *this;
    }

    // this function runs a cycle for each individual unit
    template<typename T>
    void CentralUnit<T>::run()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(*m_items[i]) && m_count > 0)
            {
                (*m_items[i]) += m_jobs[m_count - 1];
                m_jobs[--m_count] = nullptr;
            }
            (*m_items[i])();
        }
    }

    // a query that returns if there are any jobs assigned to its units or waiting to be assigned to a unit
    template<typename T>
    bool CentralUnit<T>::has_jobs() const
    {
        size_t jobs_assigned = 0;
        for (size_t i = 0; i < m_size; i++)
        {
            if (*m_items[i])
            {
                jobs_assigned++;
            }
        }
        return jobs_assigned + m_count;
    }

    // a query that returns the number of units without jobs assigned to them
    template<typename T>
    size_t CentralUnit<T>::get_available_units() const
    {
        size_t jobs_unassigned = 0;
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(*m_items[i]))
            {
                jobs_unassigned++;
            }
        }
        return jobs_unassigned;
    }

    template<typename T>
    string CentralUnit<T>::readLine(string nextline, unsigned int& position)
    {
        char current = nextline[position];
        string input = "";
        while (position < nextline.length())
        {
            if (current != ' ')
            {
                if (current == '|')
                {
                    break;
                }
                else
                {
                    input += current;
                }
            }
            current = nextline[++position];
        }
        position++;
        return input;
    }

    // this function frees the unit received and clears memory allocated for the job that was assigned to that unit
    template<typename T>
    void CentralUnit<T>::complete_job(CentralUnit<T>& cu, T* t)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (cu.m_items[i] == t)
            {
                cu.m_items[i]->complete_job();
                log << get_available_units() << " units available." << endl;
            }
        }
    }

    // updated custom constructor
    template<typename T>
    void CentralUnit<T>::operator+=(T* t)
    {
        if (!(*t))
        {
            if (m_size == m_max)
            {
                m_max *= 2;
                T** nonperm = m_items;
                m_items = new T * [m_max];
                for (size_t i = 0; i < m_size; i++)
                {
                    m_items[i] = nonperm[i];
                }
                delete[] nonperm;
            }
            (*t).on_complete(&CentralUnit<T>::complete_job);
            (*t).on_error([this](T* unit)
                {
                    (*this).log << "Failed to complete job " << (*unit).get_current_job()->name() << endl;
                    (*this).log << (get_available_units() + 1) << " units available." << endl;
                });
            m_items[m_size++] = t;
        }
        else
        {
            throw string("Unit is not available");
        }
    }

    // a query that receives the title of a job as a C - style null - terminated string and returns a pointer to the unit that is currently assigned a job that matches the given title
    // else, reports an std::out_of_range error with the following message
    template<typename T>
    T* CentralUnit<T>::operator[](string title) const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (*m_items[i] && m_items[i]->get_current_job()->name() == title)
            {
                return m_items[i];
            }
        }
        throw out_of_range("Job is not being handled by a unit.");
    }

    // a query that receives and returns nothing and displays the central unit's current state
    template<typename T>
    void CentralUnit<T>::display() const
    {
        log << "Central " << m_type << " Unit list" << endl;
        for (size_t i = 0; i < m_size; i++)
        {
            log << "[" << setfill('0') << std::setw(4) << (i + 1) << "] " << (*m_items[i]) << endl;
        }
    }
}
#endif