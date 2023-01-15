/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 6/6/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */


/* system's library */
#include <iostream>
#include <string>

/* user's library */
#include "Child.h"

using namespace std;

namespace sdds 
{
	// default constructor
	Child::Child()
	{
		delete[] toy;
		toy = nullptr;
		number = 0;
		child_name = "";
		child_age = 0;
	}

	// copy constructor
	Child::Child(const Child& c)
	{
		*this = c;
	}
	
	// copy assignment
	Child& Child::operator=(const Child& c)
	{
		if (this != &c)
		{
			number = c.number;
			child_name = c.child_name;
			child_age = c.child_age;
			delete[] toy;
			toy = new Toy[number];
			for (size_t i = 0; i < number; i++)
			{
				toy[i] = c.toy[i];
			}
		}
		return *this;
	}
	
	// move constructor
	Child::Child(Child&& c) noexcept
	{
		*this = move(c);
	}

	// move assignment
	Child& Child::operator=(Child&& c) noexcept
	{
		if (this != &c)
		{
			number = c.number;
			child_name = c.child_name;
			child_age = c.child_age;
			delete[] toy;
			toy = c.toy;
			c.toy = nullptr;
			c.number = 0;
			c.child_name = "";
			c.child_age = 0;
		}
		return *this;
	}

	// destructor
	Child::~Child()
	{
		delete[] toy;
		toy = nullptr;
	}

	// constructor provided (workshop) 
	Child::Child(std::string name, int age, const Toy* toys[], size_t count)
	{
		toy = new Toy[count];
		child_name = name;
		child_age = age;
		number = count;
		for (size_t i = 0; i < count; i++)
		{
			toy[i] = *toys[i];
		}
	}

	// a query that returns the number of toys stored in the array attribute
	size_t Child::size() const
	{
		return number;
	}
	
	// Friend Helpers -- insertion operator overload
	ostream& operator<<(ostream& os, const Child& c)
	{
		static size_t CALL_CNT;
		++CALL_CNT;
		os << "--------------------------\n"
			<< "Child " << CALL_CNT << ": " << c.child_name << " " << c.child_age << " years old:" << endl;
			os << "--------------------------\n";
		if (c.number == 0) 
		{
			os << "This child has no toys!" << endl;
		}
		else 
		{
			for (size_t i = 0; i < c.number; i++) 
			{
				os << c.toy[i];
			}
		}
		os << "--------------------------\n";
		return os;
	}
}

