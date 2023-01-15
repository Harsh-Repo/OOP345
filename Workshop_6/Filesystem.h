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

#pragma once
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

/* system's library */
#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <vector>

/* user's library */
#include "File.h"
#include "Directory.h"
#include "Resource.h"

using namespace std;

namespace sdds 
{
    class Filesystem 
    {
        Directory* m_root;
        Directory* m_current;
        string read_input(string input, unsigned int& position, bool space = false);
        vector<string> get_file_path(string fp);
        string get_file_name(string fn);

    public:
        Filesystem(string file_name, string root_name = "");
        Filesystem(const Filesystem& f) = delete;
        Filesystem(Filesystem&& f);
        Filesystem& operator=(const Filesystem& f) = delete;
        Filesystem& operator=(Filesystem&& f);
        ~Filesystem();
        Filesystem& operator+=(Resource* r);
        Directory* change_directory(const string& path = "");
        Directory* get_current_directory() const;
    };
};
#endif // !SDDS_FILESYSTEM_H
