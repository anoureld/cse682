/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
**
** NAME: TestLogger.cpp
**
** DESCRIPTION:
** This file provides functionality for the Test Logger software
** component. It is responsible for formatting, storing, and outputting unit test
** results.
**
**
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**
**
*******************************************************************************/

#include <iomanip>
#include <iostream>
#include <sstream>
#include "TestSequence.h"

using std::cout;
using std::cin;
using std::ostringstream;
using std::string;
using std::vector;
using std::list;
using std::setw;
using std::fixed;

TestSequence::TestSequence() 
{
}

void TestSequence::viewTestSequence()
{
   // Print table and column headings
	cout << "\n\n\tCurrent test sequence is:\n";
	cout << "\n\t" << setw(8) << "TestID" << setw(20) << "TestName" << "\n\n";
	
   // If no Test Objects in sequence print error message
   if (mcSequence.empty())
	{
		cout << "\t  (No tests in current sequence)\n";
	}

   // Test sequence is not empty, print name and ID of all Test Objects within the current Test Sequence
	else
	{
		for (auto elem : mcSequence)
		{
			cout << "\t" << setw(8) << elem->getTestID() << setw(20) << elem->getTestName() << "\n";
		}
	}
}

void TestSequence::inputTestSequence(TestLibrary& arcTestLib)
{
   // If no Test Objects within the Test Library print error message
	if (0 == arcTestLib.mcLibrary.size())
	{
		cout << "\n\tNo tests in library - aborting test sequence selection\n";
	}

   // Test Library is not empty, prompt user to select tests to add to sequence 
	else
	{
		// Clear the current test sequence
		mcSequence.clear();

		// Print available tests
		arcTestLib.viewTestLibrary();

		// Temp variable to hold user input
		int lnInputTestID{ 1 };

		while (0 != lnInputTestID)
		{
			// Prompt user to choose Tests to add to sequence
			cout << "\n\tInput number of test (from the listing above) to be added to the new sequence";
			cout << "\n\t(enter zero to end sequence input): ";
			cin >> lnInputTestID;

			// Input guard
			while (cin.fail() || 0 > lnInputTestID || signed(arcTestLib.mcLibrary.size()) < lnInputTestID)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "\n\t\tInvalid input - please try again: ";
				cin >> lnInputTestID;
			}
			 // Exit condition. User ends sequence entry
			if (0 == lnInputTestID)
			{
				cout << "\n\tTest sequence input ended\n";
			}
			// For valid input add to test sequence vector, then print updated Test Sequence
			else
			{
				// Add test to sequence
				mcSequence.push_back(arcTestLib.mcLibrary[lnInputTestID - 1]);

				// Display current sequence
				viewTestSequence();
			}
		}
	}
}
