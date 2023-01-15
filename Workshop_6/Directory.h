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
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

/* system's library */
#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <vector>

/* user's library */
#include "Flags.h"
#include "Resource.h"

using namespace std;

namespace sdds
{
    class Directory : public Resource
    {
        vector<Resource*> m_contents;

    public:
        Directory(string directory_name);
        void update_parent_path(const string& p) override;
        NodeType type() const override;
        string path() const override;
        string name() const override;
        int count() const override;
        size_t size() const override;
        Directory& operator+=(Resource* r);
        Resource* find(const string& name, const vector<OpFlags>& f = {});
        ~Directory();
        Directory& operator=(const Directory& d) = delete;
        Directory& operator=(Directory&& d) = delete;
        void remove(const string& path, const vector<OpFlags>& f = {});
        void display(ostream& os, const vector<FormatFlags>& f = {}) const;
    };
};
#endif // !SDDS_DIRECTORY_H
