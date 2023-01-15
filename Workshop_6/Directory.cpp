/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 18/6/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */

/* system's library */
#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>

/* user's library */
#include "File.h"
#include "Directory.h"

using namespace std;

namespace sdds
{
    // custom constructor 
    Directory::Directory(string directory_name) 
    {
        (*this).m_name = directory_name;
    }

    // a query that sets the parent path to the parameter
    void Directory::update_parent_path(const string& p) 
    {
        m_parent_path = p;
        for (auto res = m_contents.begin(); res != m_contents.end(); res++) 
        {
            (*res)->update_parent_path(path());
        }
    }

    // a query that returns Flags::DIR
    NodeType Directory::type() const 
    {
        return NodeType::DIR;
    }

    // a query that returns the full absolute path of the directory
    string Directory::path() const 
    {
        return m_parent_path + m_name;
    }

    // a query that returns the name of the directory
    string Directory::name() const 
    {
        return m_name;
    }

    // a query that returns the number of resources that this directory holds
    int Directory::count() const 
    {
        return m_contents.size();
    }

    // a query that returns the size of the directory in bytes
    size_t Directory::size() const 
    {
        size_t sum = 0;
        for (auto it = m_contents.begin(); it != m_contents.end(); it++) 
        {
            sum += (*it)->size();
        }
        return sum;
    }

    // this query adds a resource to the directory and returns a reference to the current directory
    Directory& Directory::operator+=(Resource* r) 
    {
        bool match = false;
        for (auto res = m_contents.begin(); res != m_contents.end(); res++) 
        {
            if ((*res)->name() == r->name()) 
            {
                match = true;
                break;
            }
        }
        if (match) 
        {
            throw invalid_argument("Resource already exists!");
        }
        else 
        {
            r->update_parent_path(path());
            m_contents.emplace_back(r);
        }
        return *this;
    }

    // this query finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found
    Resource* Directory::find(const string& name, const vector<OpFlags>& f) 
    {
        Resource* rf = nullptr;
        bool match = false;
        for (auto res = f.begin(); res != f.end(); res++) 
        {
            if ((*res) == OpFlags::RECURSIVE) 
            {
                match = true;
                break;
            }
        }
        for (auto res = m_contents.begin(); res != m_contents.end(); res++) 
        {
            if ((*res)->name() == name) 
            {
                rf = (*res);
                break;
            }
            else if (match && (*res)->type() == NodeType::DIR) 
            {
                Directory* nonperm = dynamic_cast<Directory*>(*res);
                rf = (*nonperm).find(name, f);
            }
        }
        return rf;
    }

    // destructor
    Directory::~Directory() 
    {
        for (auto res = m_contents.begin(); res != m_contents.end(); res++) 
        {
            delete* res;
        }
    }

    // a query that deletes a resource from the directory whose name matches the first argument and
    // if not, reports an exception of type std::string with the message NAME does not exist in DIRECTORY_NAME
    void Directory::remove(const string& path, const vector<OpFlags>& f) 
    {
        bool match = false;
        for (auto res = f.begin(); res != f.end(); res++) 
        {
            if ((*res) == OpFlags::RECURSIVE) 
            {
                match = true;
                break;
            }
        }
        Resource* r = find(path);
        if (r == nullptr) 
        {
            throw string(path + "does not exist in " + name());
        }
        else if ((*r).type() == NodeType::DIR) 
        {
            if (match) 
            {
                for (unsigned int i = 0; i < m_contents.size(); i++) 
                {
                    if (m_contents[i]->name() == path) 
                    {
                        Resource* nonperm = m_contents[i];
                        m_contents.erase(m_contents.begin() + i);
                        delete nonperm;
                        break;
                    }
                }
            }
            else 
            {
                throw invalid_argument(path + "is a directory. Pass the recursive flag to delete directories.");
            }
        }
        else 
        {
            for (unsigned int i = 0; i < m_contents.size(); i++) 
            {
                if (m_contents[i]->name() == path) 
                {
                    Resource* nonperm = m_contents[i];
                    m_contents.erase(m_contents.begin() + i);                   
                    delete nonperm;
                    break;
                }
            }
        }
    }

    // display function
    void Directory::display(ostream& os, const vector<FormatFlags>& f) const 
    {
        bool match = false;
        for (auto res = f.begin(); res != f.end(); res++) 
        {
            if ((*res) == FormatFlags::LONG) 
            {
                match = true;
                break;
            }
        }
        os << "Total size: " << size() << " bytes" << endl;
        for (auto res = m_contents.begin(); res != m_contents.end(); res++) 
        {
            if ((*res)->type() == NodeType::FILE) 
            {
                os << "F | ";
            }
            else 
            {
                os << "D | ";
            }
            os << setw(15) << left << (*res)->name() << " |";
            if (match) 
            {
                os << " ";
                if ((*res)->count() >= 0) 
                {
                    os << setw(2) << right << to_string((*res)->count());
                }
                else 
                {
                    os << setw(2) << right << "";
                }
                os << " | ";
                os << right << setw(10) << (to_string((*res)->size()) + string(" bytes"));
                os << " | ";
            }
            os << endl;
        }
    }
}
