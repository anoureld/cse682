/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
** NAME: TestSequence.h
**
** DESCRIPTION:
** This file includes function definitions and data members for the Test Sequence
** software component.
**
** DESIGN CONSIDERATIONS:
** None
**
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**
**
*******************************************************************************/

#ifndef TESTSEQUENCE_H
#define TESTSEQUENCE_H

// #include <vector>
#include <list>
#include "Test.h"
#include "TestLibrary.h"

// using std::vector;
using std::list;

class TestSequence
{

public:
   /**
    * Default Constructor
    * Create TestSequence Object
    */
	TestSequence();

   /**
    * Diplays current test sequence
    */
	void viewTestSequence();

   /**
    * Adds arcTestLib to current test sequence.
    * @param arcTestLib Reference to current test library
    */
	void inputTestSequence(TestLibrary& arcTestLib);

    // A list of Test Objects used as the "test sequence" that
    // will be executed by the test harness. 
    vector<ITest*> mcSequence;
};

#endif // TESTSEQUENCE_H