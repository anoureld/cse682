/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
** NAME: Test.h
**
** DESCRIPTION:
** This file includes function definitions and data members for the Test 
** software component.
**
**
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0          Sab                  2/5
**
*******************************************************************************/

#ifndef TEST_H
#define TEST_H

#include "ITest.h"
#include <string>

using std::string;

class Test : public ITest
{
public:

   /**
    * Default Constructor
    * Create TestSequence Object
    */
	Test();

   /**
    * Parameterized Constructor
    * Create TestSequence Object
    * @param  acTestName Test Name
    * @param  abTestResult Defines test result
    * @param  abPauseExecution Determines if test execution pauses
    * @param  abThrowsException Determines if test throws exception
    */
	Test(string acTestName, bool abTestResult, bool abPauseExecution, bool abThrowsException);

    /*
    * Destructor
    * Destructs object
    * Decrements static variable containing count of Test objects
    * */
    ~Test();

   /**
    * This method is called to access the test ID data member.
    * @return mnTestID data member
   */
	int getTestID();

   /**
    * This method is called to access the test name data member.
    * @return mcTestName data member
   */
	string getTestName();

    /**
     * This method is called to access the pause execution flag data member.
     * @return mbPauseExecution data member
    */
    bool getPauseExecution();

   /**
    * This method is called to access the result data member.
    * @return mbTestResult data member
   */
	bool getTestResult();

   /**
    * Overriden operator function. This makes Test.cpp a functor and 
    * allows any instance of the Test class to be treated as a function.
    * This method is called to simulate a unit test execution. 
    * @return bool true if simulated test passes, false otherwise.
    *         Invalid simulated tests may throw an exception. 
   */
	bool operator()(void);

private:
   // A static (shared class-wide) integer representing the number of test objects.
	static int snNumUnitTests;

   // An integer representing the Test objects unique reference number.
	int mnTestID;

   // A string name for Test object.
	string mcTestName;

   // A boolean that allows Test Object creator to determine if 
   // simulated test will throw an exception.
	bool mbThrowsException;

    // A boolean that allows Test Object creator to determine if 
    // simulated test will demonstrate a pause in execution
    // (to validate correct implementation of timepoint stamps).
    bool mbPauseExecution;

   // A boolean that allows Test Object creator to set simulated test
   // output. True = Pass, False = Failed.
	bool mbTestResult;
};

#endif // TEST_H