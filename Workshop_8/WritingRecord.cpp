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

#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds 
{
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) 
    {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees using raw pointers
		size_t i = 0;
		do
		{
			size_t j = 0;
			do
			{
				if (emp[i].id == sal[j].id) 
				{
					EmployeeWage* nonperm = new EmployeeWage(emp[i].name, sal[j].salary);
					try 
					{
						(*nonperm).rangeValidator();
					}
					catch (...) 
					{
						delete nonperm;
						throw;
					}
					if (!activeEmp.SINvalidity(emp[i].id)) 
					{
						throw std::string{ " " };
					};
					activeEmp += std::move(nonperm);
					delete nonperm;
				}
				j++;
			} while (j < sal.size());
			i++;
		} while (i < emp.size());
		return activeEmp;
	}

	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) 
    {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees using smart pointers
		size_t i = 0;
		do
		{
			size_t j = 0;
			do
			{
				if (emp[i].id == sal[j].id) 
				{
					std::unique_ptr<EmployeeWage> nonperm(new EmployeeWage(emp[i].name, sal[j].salary));
					(*nonperm).rangeValidator();
					if (!activeEmp.SINvalidity(emp[i].id)) 
					{
						throw std::string(" ");
					};
					activeEmp += std::move(nonperm);
				}
				j++;
			} while (j < sal.size());
			i++;
		} while (i < emp.size());
		return activeEmp;
	}
}