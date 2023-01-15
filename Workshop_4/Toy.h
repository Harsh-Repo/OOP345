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

#ifndef SDDS_TOY_H
#define SDDS_TOY_H

/* system's library */
#include <iostream>
#include <string>

using namespace std;

namespace sdds 
{
	class Toy
	{
		unsigned int order_id;
		std::string toy_name;
		int num_items;
		double toy_price;
		double sales_tax = 0.13;
	public:
		Toy() = default;
		void update(int numItems);
		Toy(const std::string& toy);
		friend std::ostream& operator<<(std::ostream& os, const Toy& t);
	};
}
#endif // !SDDS_TOY_H
