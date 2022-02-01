/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
**
** NAME: TestLibrary.cpp
**
** DESCRIPTION:
** This file provides functionality for the Test Libray software
** component. It is responsible for maintaining a repository of Test objects.
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
#include "TestLibrary.h"

using std::cout;
using std::string;
using std::setw;
using std::fixed;

TestLibrary::TestLibrary()
{
	initializeTestLibrary();
}

void TestLibrary::initializeTestLibrary()
{
	// Instantiate callable test objects
	Test lcModule1v10("Module 1 v1.0", false, false, false); // module 1 v1.0 fails
	Test lcModule1v11("Module 1 v1.1", true, false, false);  // module 2 v2.0 passes
	Test lcModule2v10("Module 2 v1.0", false, false, false); // module 2 v1.0 fails
	Test lcModule2v11("Module 2 v1.1", false, true, false); // module 2 v1.1 fails and pauses execution
	Test lcModule3v10("Module 3 v1.0", true, false, true); // module 3 v1.0 throws exception

	// load test objects into library
	mcLibrary.push_back(lcModule1v10);
	mcLibrary.push_back(lcModule1v11);
	mcLibrary.push_back(lcModule2v10);
	mcLibrary.push_back(lcModule2v11);
	mcLibrary.push_back(lcModule3v10);
}

void TestLibrary::viewTestLibrary()
{
   // Print table and column headings
	cout << "\n\tCurrent test library:\n";
	cout << "\n\t" << setw(8) << "TestID" << setw(20) << "TestName" << "\n\n";

   // If Test Library is empty print error message
	if (0 == mcLibrary.size())
	{
		cout << "\t  (No tests in library)\n";
	}

   // Test Library is not empty, then print all Test objects contained within library
	else
	{
		for (unsigned int i = 0; i < mcLibrary.size(); i++)
		{
			cout << "\t" << setw(8) << mcLibrary[i].getTestID() << setw(20) << mcLibrary[i].getTestName() << "\n";
		}
	}
}
