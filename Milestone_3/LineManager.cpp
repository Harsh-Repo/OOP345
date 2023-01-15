// Name:	Harsh Patel
// Seneca Student ID:	146315205
// Seneca email: hpatel262@myseneca.ca
// Date of completion: 10-08-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

/* system's library */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

/* user's library */
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"
#include "LineManager.h"

using namespace std;

namespace sdds
{
    // this constructor receives the name of the file that identifies the active stations on the assembly line (example: AssemblyLine.txt) and the collection of workstations available for configuring the assembly line
    LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
    {
        Utilities nonperm;
        string ln = "", cur_w = "", nxt_w = "";
        size_t pos = 0u;
        bool result = false;
        vector<string> v_curw, v_nxtw;
        ifstream ifile(file);
        if (!ifile)
            throw string("\nFailed to open file") + string(file);
        else
        {
            while (getline(ifile, ln))
            {
                if (!ln.empty())
                {
                    cur_w = nonperm.extractToken(ln, pos, result);
                    v_curw.push_back(cur_w);
                    nxt_w = !result ? "" : nonperm.extractToken(ln, pos, result);
                    v_nxtw.push_back(nxt_w);

                    auto c_err = any_of(stations.begin(), stations.end(), [=](Workstation* cur_s)
                        {
                            if ((*cur_s).getItemName() == cur_w)
                            {
                                if (!nxt_w.empty())
                                {
                                    auto n_err = any_of(stations.begin(), stations.end(), [=](Workstation* nxt_s)
                                        {
                                            if ((*nxt_s).getItemName() == nxt_w)
                                            {
                                                (*cur_s).setNextStation(nxt_s);
                                                return true;
                                            }
                                            else
                                            {
                                                return false;
                                            }
                                        });
                                    if (!n_err)
                                        throw string("\n Not found");
                                    else if (cur_w == nxt_w)
                                        throw string("\n Not found");
                                }
                                m_activeLine.push_back(cur_s);
                                return true;
                            }
                            else
                                return false;
                        });
                    if (!c_err)
                        throw string("\n Something's wrong!");
                }
            }
            ifile.close();
            for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* cur_s)
                {
                    auto start = any_of(stations.begin(), stations.end(), [=](Workstation* nxt_s)
                        {
                            if ((*nxt_s).getNextStation() == cur_s)
                                return true;
                            else
                                return false;
                        });
                    if (!start)
                        m_firstStation = cur_s;
                });
            m_cntCustomerOrder = g_pending.size();
        }
    }

    // this modifier reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable
    void LineManager::reorderStations()
    {
        Workstation* nxt_w = m_firstStation;
        vector<Workstation*> v_w;
        while (nxt_w)
        {
            v_w.push_back(nxt_w);
            nxt_w = (*nxt_w).getNextStation();
        }
        m_activeLine = v_w;
    }

    // this modifier performs one iteration of operations on all of the workstations in the current assembly line 
    bool LineManager::run(ostream& os)
    {
        static size_t count = 0u;
        os << "Line Manager Iteration: " << ++count << endl;
        if (!g_pending.empty())
        {
            *m_activeLine.front() += move(g_pending.front());
            g_pending.pop_front();
        }
        for (auto i : m_activeLine)
            (*i).fill(os);
        for (auto i : m_activeLine)
            (*i).attemptToMoveOrder();
        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    // this query displays all active stations on the assembly line in their current order
    void LineManager::display(ostream& os) const
    {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* w)
            {
                (*w).display(os);
            });
    }
}
