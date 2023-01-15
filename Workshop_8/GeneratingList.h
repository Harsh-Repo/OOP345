/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 1/7/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds 
{
	template<typename T>
	class GeneratingList 
	{

		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) 
		{
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) 
			{
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
		bool SINvalidity(const std::string& sin)
		{
			int digits = sin.length();
			int total = std::stoi(sin.substr(digits - 1, 1));
			int parity = (digits - 2) % 2;
			int i = 0;
			do
			{
				int digit = std::stoi(sin.substr(i, 1));
				if ((i % 2) == parity)
					digit = digit * 2;
				if (digit > 9)
					digit -= 9;
				total += digit;
				i++;
			} while (i <= digits - 2);
			return (total % 10) == 0;
		}

		//TODO: Overload the += operator with a smart pointer
		// as a second operand.
		void operator+= (std::unique_ptr<T> sp) 
		{
			list.push_back(*sp);
		}

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		void operator+= (T* rp) 
		{
			list.push_back(*rp);
		}
		
		void print(std::ostream& os) const 
		{
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) 
	{
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
