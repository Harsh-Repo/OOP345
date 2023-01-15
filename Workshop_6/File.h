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
#ifndef SDDS_FILE_H
#define SDDS_FILE_H

/* system's library */
#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

/* user's library */
#include "Flags.h"
#include "Resource.h"

using namespace std;

namespace sdds 
{
    class File : public Resource 
    {
        string m_contents;

    public:
        File(string file_name, string file_contents = "");
        void update_parent_path(const string& p) override;
        NodeType type() const override;
        string path() const override;
        string name() const override;
        int count() const override;
        size_t size() const override;
    };
};
#endif // !SDDS_FILE_H
