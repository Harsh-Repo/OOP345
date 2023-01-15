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

#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H

/* system's library */
#include <iostream>
#include <string>

/* user's library */
#include "Toy.h"

using namespace std;

namespace sdds
{
	class ConfirmOrder 
	{
	private:
		const Toy** dyn_ptr{nullptr};
		size_t no{0};
	public:
		ConfirmOrder() = default;
		ConfirmOrder(const ConfirmOrder& co);
		ConfirmOrder& operator=(const ConfirmOrder& co);
		ConfirmOrder(ConfirmOrder&& co)noexcept;
		ConfirmOrder& operator=(ConfirmOrder&& co)noexcept;
		~ConfirmOrder();
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);
		friend std::ostream& operator<<(std::ostream& os, const ConfirmOrder& co);
	};
}
#endif // !SDDS_CONFIRMORDER_H

