#ifndef TESTSEQUENCE_H
#define TESTSEQUENCE_H
/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestSequence.h
** DESCRIPTION:
** This file includes function definitions and data members for the Test Sequence
** software component.
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0        Maher Noureldine     3/12/2022
**
*******************************************************************************/


// #include <vector>
#include <list>
#include "Test.h"
#include "TestLibrary.h"
#include "ITest.h"

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
    * clears current test sequence
    */
    void clearTestSequence();
    /**
    * Returns current test sequence
    */
    vector<ITest*> getMcSequence();

    /*
    * Function to check if the test sequence is empty.
    * Returns true if it's empty.
    * Returns false if it's not empty.
    */
    bool is_empty();

   /**
    * Adds arcTestLib to current test sequence.
    * @param arcTestLib Reference to current test library
    */
	void inputTestSequence(TestLibrary& arcTestLib);
   
    private:
    // A list of Test Objects used as the "test sequence" that
    vector<ITest*> mcSequence;
};
#endif // TESTSEQUENCE_H