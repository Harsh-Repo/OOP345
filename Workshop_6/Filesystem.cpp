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
#include <utility>
#include <fstream>
#include <sstream>
#include <stdexcept>

/* user's library */
#include "File.h"
#include "Directory.h"
#include "Resource.h"
#include "Filesystem.h"

using namespace std;

namespace sdds
{
    // a query that reads the input
    string Filesystem::read_input(string input, unsigned int& position, bool space) 
    {
        char cur = input[position];
        string res = "";
        bool no_spc = false;
        string spc = "";
        while (position < input.length()) 
        {
            if (cur == '\n' || cur == '|' || cur == '\r') 
            {
                break;
            }
            else if (cur != ' ' && !no_spc) 
            {
                no_spc = true;
                res += cur;
            }
            else if (no_spc) 
            {
                if (cur == ' ') 
                {
                    if (space) 
                    {
                        spc += cur;
                    }
                }
                else 
                {
                    res += spc + cur;
                    spc = "";
                }

            }
            cur = input[++position];
        }
        position++;
        return res;
    }

    // a query that gets file path
    vector<string> Filesystem::get_file_path(string fp) 
    {
        int pos = 0;
        vector<string> f_path;
        for (unsigned int i = 0; i < fp.length(); i++) 
        {
            if (fp[i] == '/') 
            {
                int prev = pos;
                pos = i + 1;
                f_path.emplace_back(fp.substr(prev, pos - prev));
            }
        }
        return f_path;
    }

    // a query that gets file name
    string Filesystem::get_file_name(string fn) 
    {
        int pos = 0;
        string f_name = "";
        for (unsigned int i = 0; i < fn.length(); i++) 
        {
            if (fn[i] == '/') 
            {
                pos = i + 1;
            }
        }
        f_name = fn.substr(pos, fn.length());
        return f_name;
    }

    // custom constructor
    Filesystem::Filesystem(string file_name, string root_name) 
    {
        Directory* nonperm = new Directory(root_name);
        m_root = nonperm;
        m_current = nonperm;
        ifstream f(file_name);
        string line, f_name, f_contents;
        vector<string> f_path;
        unsigned int pos = 0;
        if (f.is_open()) 
        {
            while (getline(f, line)) 
            {
                f_name = read_input(line, pos, false);
                f_contents = read_input(line, pos, true);
                f_path = get_file_path(f_name);
                f_name = get_file_name(f_name);
                Directory* m_cur = m_root;
                vector<OpFlags> f_flag;
                f_flag.push_back(OpFlags::RECURSIVE);
                for (auto res = f_path.begin(); res != f_path.end(); res++) 
                {
                    Directory* dir = new Directory(*res);
                    try 
                    {
                        *m_cur += dir;
                        m_cur = dir;
                    }
                    catch (...) 
                    {
                        delete dir;
                        m_cur = dynamic_cast<Directory*>((*m_cur).find(*res));
                    }
                }
                if (f_name.length() > 0) 
                {
                    File* f = new File(f_name, f_contents);
                    try 
                    {
                        *m_cur += f;
                    }
                    catch (...) 
                    {
                        delete f;
                    }
                }
                pos = 0;
            }
        }
        else 
        {
            delete nonperm;
            throw invalid_argument("Invalid file!");
        }
    }

    // move constructor
    Filesystem::Filesystem(Filesystem&& f) 
    {
        *this = move(f);
    }

    // move assignment
    Filesystem& Filesystem::operator=(Filesystem&& f) 
    {
        if (this == &f) 
        {
            return *this;
        }
        swap(m_root, f.m_root);
        swap(m_current, f.m_current);
        return *this;
    }

    // destructor
    Filesystem::~Filesystem()
    {
        delete m_root;
    }

    // a query that adds a resource to the current directory
    Filesystem& Filesystem::operator+=(Resource* r) 
    {
        *m_current += r;
        return *this;
    }

    // a query that changes the current directory to the directory (located in the current directory) whose name matches argument
    Directory* Filesystem::change_directory(const string& path) 
    {
        if (path == "") 
        {
            m_current = m_root;
        }
        else 
        {
            Resource* r = m_current->find(path);
            if (r == nullptr) 
            {
                throw invalid_argument("Cannot change directory! " + path + " was not found!");
            }
            else 
            {
                m_current = dynamic_cast<Directory*>(r);
            }
        }
        return m_current;
    }

    // a query that returns the current directory
    Directory* Filesystem::get_current_directory() const 
    {
        return m_current;
    }
}
