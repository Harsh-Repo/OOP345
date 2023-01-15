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
#include <iomanip>

/* user's library */
#include "Toy.h"

using namespace std;

namespace sdds 
{
	// a modifier that receives number of toys to be ordered and updates the following with the received value
	void sdds::Toy::update(int numItems)
	{
		num_items = numItems;
	}
	
	// a constructor responsible for extracting information about the toy from the string and storing the tokens in the instance's attributes
	Toy::Toy(const string& toy)
	{
		string str = toy;
		string id, name, num, price;
		id = str.substr(0, str.find(":"));
		str.erase(0, str.find(":") + 1);
		name = str.substr(0, str.find(":"));
		str.erase(0, str.find(":") + 1);
		num = str.substr(0, str.find(":"));
		str.erase(0, str.find(":") + 1);
		price = str.substr(0, str.find(":"));
		str.erase(0, str.find(":") + 1);
		name.erase(0, name.find_first_not_of(' '));
		name.erase(name.find_last_not_of(' ') + 1);
		order_id = stoi(id);
		toy_name = name;
		num_items = stoi(num);
		toy_price = stod(price);
	}
	
	// friend helpers -- insertion operator overload
	ostream& operator<<(ostream& os, const Toy& t)
	{
		double sub_t = t.toy_price * double(t.num_items);
		double tax = sub_t * t.sales_tax;
		double total = sub_t + tax;
		os << "Toy";
		os << setw(8) << t.order_id << ":";
		os << right << setw(18) << t.toy_name;
		os << setw(3) << t.num_items;		
		os << " items" << setw(8) << fixed << setprecision(2) << t.toy_price;
		os << "/item  subtotal:" << setw(7) << fixed << setprecision(2) << sub_t;
		os << " tax:" << setw(6) << fixed << setprecision(2) << tax;
		os << " total:" << setw(7) << fixed << setprecision(2) << total << endl;
		return os;
	}
}

