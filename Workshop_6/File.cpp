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

/* user's library */
#include "File.h"

using namespace std;

namespace sdds
{
    // custom constructor
    File::File(string file_name, string file_contents) : m_contents{ file_contents } 
    {
        (*this).m_name = file_name;
    }

    // a query that sets the parent path to the parameter
    void File::update_parent_path(const string& p) 
    {
        m_parent_path = p;
    }

    // a query that returns Flags::FILE
    NodeType File::type() const 
    {
        return NodeType::FILE;
    }

    // a query that returns the full absolute path of the file
    string File::path() const 
    {
        return m_parent_path + m_name;
    }

    // a query that returns the name of the file
    string File::name() const 
    {
        return m_name;
    }

    // a query that returns -1
    int File::count() const 
    {
        return -1;
    }

    // a query that returns the size of the file in bytes
    size_t File::size() const 
    {
        return m_contents.length();
    }
}

