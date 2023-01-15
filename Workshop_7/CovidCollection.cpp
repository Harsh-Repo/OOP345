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

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>

/* user's library */
#include "CovidCollection.h"

namespace sdds 
{
	/* trim function */
	std::string& CovidCollection::trim(std::string& s) 
	{
		while (s.length() > 0 && s[0] == ' ')
			s.erase(0, 1);
		while (s.length() > 0 && s[s.length() - 1] == ' ')
			s.erase(s.length() - 1, 1);
		return s;
	}

	/* custom constructor */
	CovidCollection::CovidCollection(std::string filename) 
	{
		std::ifstream f(filename);
		if (!f)
			throw "Invalid filename!";
		while (f) 
		{
			Covid new_cc;
			std::string nonperm;
			std::getline(f, nonperm);
			if (f) 
			{
				trim(new_cc.country = nonperm.substr(0, 25));
				trim(new_cc.city = nonperm.substr(25, 25));
				trim(new_cc.variant = nonperm.substr(50, 25));
				try 
				{
					new_cc.year = std::stoi(nonperm.substr(75, 5)) < 0 ? " " : nonperm.substr(75, 5);
				}
				catch (...) 
				{
					new_cc.year = '0';
				}
				new_cc.cases = std::stoi(nonperm.substr(80, 5));
				new_cc.m_deaths = std::stoi(nonperm.substr(85));
				(*this).covid.push_back(new_cc);
			}
		}
		f.close();
	};

	/* this function prints the content of the collection into the parameter (one city details / line) */
	void CovidCollection::display(std::ostream& out) const 
	{
		std::for_each(covid.begin(), covid.end(), [&out](const Covid& covid) 
		{
			out << covid << std::endl;
		});
		auto cases = std::accumulate(covid.begin(), covid.end(), 0u, [](const size_t& details, const Covid& c) 
		{
			return details + c.cases;
		});
		auto deaths = std::accumulate(covid.begin(), covid.end(), 0u, [](const size_t& details, const Covid& c) 
		{
			return details + c.m_deaths;
		});
		for (int i = 0; i < 88; i++)
			out << "-";
		out << std::endl;
		out << "|" << std::right << std::fixed << std::setw(79) << "Total Cases Around the World: " << std::right << std::setw(6) << cases << " |" << std::endl;;
		out << "|" << std::right << std::fixed << std::setw(79) << "Total Deaths Around the World: " << std::right << std::setw(6) << deaths << " |" << std::endl;
	}

	/* this function receives as a parameter(country, variant, cases or deaths) the name of the field used to sort the collection of covids in ascending order */
	void CovidCollection::sort(std::string fieldname) 
	{
		if (fieldname == "country") 
		{
			std::sort(covid.begin(), covid.end(), [](const Covid& c1, const Covid& c2) 
			{
				return c1.country < c2.country;
			});
		}
		else if (fieldname == "variant") 
		{
			std::sort(covid.begin(), covid.end(), [](const Covid& v1, const Covid& v2) 
			{
				return v1.variant < v2.variant;
			});
		}
		else if (fieldname == "cases") 
		{
			std::sort(covid.begin(), covid.end(), [](const Covid& c1, const Covid& c2) 
			{
				return c1.cases < c2.cases;
			});
		}
		else if (fieldname == "deaths") 
		{
			std::sort(covid.begin(), covid.end(), [](const Covid& d1, const Covid& d2) 
			{
				return d1.m_deaths < d2.m_deaths;
			});
		}
	}

	/* this function removes the token [None] from the variant field of the covids that do not have a valid variant */
	void CovidCollection::cleanList() 
	{
		std::transform(covid.begin(), covid.end(), covid.begin(), [](Covid c) 
		{
			if (c.variant == "[None]")
				c.variant = "";
			return c;
		});
	}

	/* this function receives the name of a variant as a parameter, and returns true if the collection contains any city with that variant */
	bool CovidCollection::inCollection(std::string variantname) const 
	{
		auto valid = std::find_if(covid.begin(), covid.end(), [&variantname](const Covid& c) 
		{
			return c.variant == variantname;
		});
		return valid != covid.end();
	}

	/* this function receives the name of a country as a parameter, and returns the list of covids of that country available in the collection */
	std::list<Covid> CovidCollection::getListForCountry(std::string countryname) const 
	{
		auto count = std::count_if(covid.begin(), covid.end(), [&countryname](const Covid& c) 
		{
			return c.country == countryname;
		});
		std::list<Covid>countrylist(count);
		std::copy_if(covid.begin(), covid.end(), countrylist.begin(), [&countryname](const Covid& c) 
		{
			return c.country == countryname;
		});
		return countrylist;
	}

	/* this function receives the name of a variant as a parameter, and returns the list of covids of that variant available in the collection */
	std::list<Covid> CovidCollection::getListForVariant(std::string variantname) const 
	{
		auto count = count_if(covid.begin(), covid.end(), [&variantname](const Covid& c) 
		{
			return c.variant == variantname;
		});
		std::list<Covid>variantlist(count);
		std::copy_if(covid.begin(), covid.end(), variantlist.begin(), [&variantname](const Covid& c) 
		{
			return c.variant == variantname;
		});
		return variantlist;
	}

	/* this function inserts one Covid into the first parameter, using the following format 
	| COUNTRY(20) | CITY(15) | VARIANT(20) | YEAR(6) | CASES | DEATHS |*/
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid) 
	{
		out << "| " << std::left << std::setw(21) << theCovid.country;
		out << " | " << std::left << std::setw(15) << theCovid.city;
		out << " | " << std::left << std::setw(20) << theCovid.variant;
		out << " | " << std::right << std::setw(7) << theCovid.year;
		out << "| " << std::right << std::setw(4) << theCovid.cases;
		out << " | " << std::right << std::setw(3) << theCovid.m_deaths << " |";
		return out;
	}
}
