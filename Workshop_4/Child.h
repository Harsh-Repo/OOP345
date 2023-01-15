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

#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H

/* system's library */
#include <iostream>
#include <string>

/* user's library */
#include "Toy.h"

using namespace std;

namespace sdds {
	class Child
	{
	private:
		Toy* toy{};
		size_t number;
		std::string child_name;
		int child_age;
	public:
		Child();
		Child(const Child& c);
		Child& operator=(const Child& c);
		Child(Child&& c) noexcept;
		Child& operator=(Child&& c) noexcept;
		~Child();
		Child(std::string name, int age, const Toy* toys[], size_t count);
		size_t size() const;
		friend std::ostream& operator<<(std::ostream& os, const Child& c);
	};
}
#endif // !SDDS_CHILD_H
