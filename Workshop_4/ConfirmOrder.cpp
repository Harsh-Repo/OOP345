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
#include "ConfirmOrder.h"

using namespace std;

namespace sdds 
{
	// copy constructor 
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& co)
	{
		*this = co;
	}

	// copy assignment
	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& co)
	{
		if (this != &co)
		{
			no = co.no;
			delete[] dyn_ptr;
			dyn_ptr = new const Toy * [no];
			for (size_t i = 0; i < no; i++)
			{
				dyn_ptr[i] = co.dyn_ptr[i];
			}
		}
		return *this;
	}

	// move constructor
	ConfirmOrder::ConfirmOrder(ConfirmOrder&& co) noexcept
	{
		*this = move(co);
	}

	// move assignment
	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& co) noexcept
	{
		if (this != &co)
		{
			no = co.no;
			delete[] dyn_ptr;
			dyn_ptr = co.dyn_ptr;
			co.dyn_ptr = nullptr;
			co.no = 0;
		}
		return *this;
	}

	// destructor
	ConfirmOrder::~ConfirmOrder()
	{
		delete[] dyn_ptr;
		dyn_ptr = nullptr;
	}

	// this function adds the toy toy to the array by adding its address
	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy)
	{
		bool arr = false;
		for (size_t i = 0; i < no; i++) 
		{
			if (dyn_ptr[i] == &toy) 
			{
				arr = true;
			}
		}
		if (!arr)
		{
			const Toy** nonperm = nullptr;
			nonperm = new const Toy* [no + 1];

			for (size_t i = 0; i < no; i++)
			{
				nonperm[i] = dyn_ptr[i];
			}

			nonperm[no] = &toy;
			no++;
			delete[] dyn_ptr;
			dyn_ptr = nonperm;
		}
		return *this;
	}

	// this function removes the toy toy to the array by adding its address
	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy)
	{
		bool arr = false;
		for (size_t i = 0; i < no; i++) 
		{
			if (dyn_ptr[i] == &toy) 
			{
				arr = true;
			}
		}
		if (arr)
		{
			for (size_t i = 0; i < no; i++)
			{
				if (dyn_ptr[i] == &toy) 
				{
					dyn_ptr[i] = nullptr;
				}
			}
			no--;
		}
		return *this;
	}

	// Friend Helpers -- insertion operator overload
	ostream& operator<<(ostream& os, const ConfirmOrder& co)
	{
		os << "--------------------------" << endl;
		os << "Confirmations to Send" << endl;
		os << "--------------------------" << endl;
		if (co.no == 0) 
		{
			os << "There are no confirmations to send!\n";
		}
		else 
		{
			for (size_t i = 0; i < co.no; i++) 
			{
				if (co.dyn_ptr[i] != nullptr) 
				{
					os << *co.dyn_ptr[i];
				}
			}
		}
		os << "--------------------------\n";		
		return os;
	}
}
