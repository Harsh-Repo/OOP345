/*
--------------------------------
Name    : Harsh Patel
Email   : hpatel262@myseneca.ca
Id 		: 146315205
Section : NEE
Date    : 12/6/22
--------------------------------
*/

/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments. */

/* system's library */
#include <iostream>
#include <iomanip>
#include <string>

/* user's library */
#include "Job.h"
#include "CentralUnit.h"
#include "Processor.h"

void printLine() 
{
    std::cout << std::setfill('-') << std::setw(45) << "-" << std::setfill(' ') << "\n";
}

void printHeader(std::string label) 
{
    size_t padLeft = (45 - label.length()) / 2;

    printLine();
    std::cout << std::setw(padLeft) << " " << label << std::endl;
    printLine();
}

// main begins execution
int main(int argc, char** argv) 
{
    std::cout << "Command Line:\n";
    printLine();
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    printLine();
    std::cout << "\n";

    // TODO: If the number of arguments passed in is less than 2,
    //       print an error message and force exit the program with a code of -1.
    if (argc < 2) 
    {
        std::cout << "**ERROR: Invalid number of arguments provided." << std::endl;
        std::exit(-1);
    }

    printHeader("CPU SETUP");

    try 
    {
        sdds::CentralUnit<sdds::Processor> fake_host("fake", "invalid file");
    } catch (std::invalid_argument& e) 
    {
        std::cout << "**EXPECTED EXCEPTION: " << e.what() << std::endl;
    }

    sdds::CentralUnit<sdds::Processor>* cpu = new sdds::CentralUnit<sdds::Processor>("Processing", argv[1]);

    try 
    {
        sdds::CentralUnit<sdds::Processor> test_host = *cpu;
    } catch (...) 
    {
        std::cout << "**EXPECTED EXCEPTION: Central Unit cannot be copy-assigned." << std::endl;
    }

    if (std::is_copy_assignable<sdds::CentralUnit<sdds::Processor>>::value) 
    {
        std::cout << "**EXCEPTION: Central Unit should not support copy operations.\n"
                  << std::endl;
    }

    if (!std::is_move_constructible<sdds::CentralUnit<sdds::Processor>>::value || !std::is_move_assignable<sdds::CentralUnit<sdds::Processor>>::value) 
    {
        std::cout << "**EXCEPTION: Central Unit should support move operations.\n"
                  << std::endl;
    }

    cpu->display();

    printLine();

    printHeader("ADD PROCESSOR");

    *cpu += new sdds::Processor(cpu, "AMD", "FX-Windsor-2", 2);
    cpu->display();

    printLine();

    printHeader("ADD JOBS");

    *cpu += "Add two numbers";
    *cpu += "Join two strings";
    *cpu += "Subtract n numbers";
    *cpu += "Add a file";

    std::cout << "Successfully added 4 jobs to the queue." << std::endl;
    try 
    {
        *cpu += "Divide 2 integers";
    } catch (...) 
    {
        std::cout << "**EXPECTED EXCEPTION: Job queue is full." << std::endl;
    }

    printLine();

    printHeader("RUN CPU");

    cpu->run();
    *cpu += "Divide 2 integers";
    cpu->display();
    std::cout << std::endl;

    try 
    {
        sdds::Processor* mv = (*cpu)["Add a file"];
        (void)mv;  // supress unused variable warning
    } catch (std::out_of_range& e) 
    {
        std::cout << "**EXPECTED EXCEPTION: " << e.what() << std::endl
                  << std::endl;
    }

    std::cout << "CPU run #2" << std::endl;
    cpu->run();
    cpu->display();
    std::cout << std::endl
              << std::endl;

    sdds::Processor* dvp = (*cpu)["Divide 2 integers"];
    std::cout << "**Confirmed " << *dvp << " in CPU\n\n";

    for (auto i = 0; cpu->has_jobs(); i++) 
    {
        std::cout << "CPU run # " << i + 3 << std::endl;
        cpu->run();
        cpu->display();
        std::cout << std::endl;
    }

    printLine();

    delete cpu;
}