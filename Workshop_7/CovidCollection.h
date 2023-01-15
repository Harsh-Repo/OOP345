/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 26/6/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>

namespace sdds 
{
	struct Covid 
	{
		std::string country{};
		std::string city{};
		std::string variant{};
		size_t cases{};
		std::string year{};
		size_t m_deaths{};
	};
	class CovidCollection 
	{
		std::vector<Covid> covid;
		std::string& trim(std::string& s);
	public:
		CovidCollection(std::string filename);
		void display(std::ostream& out) const;
		void sort(std::string fieldname);
		void cleanList();
		bool inCollection(std::string variantname) const;
		std::list<Covid>getListForCountry(std::string countryname) const;
		std::list<Covid>getListForVariant(std::string variantname) const;
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif // !SDDS_COVIDCOLLECTION_H

