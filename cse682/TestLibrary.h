#ifndef TESTLIBRARY_H
#define TESTLIBRARY_H
/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestLibrary.h
** DESCRIPTION:
** This file includes function definitions and data members for the Test Library
** software component.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0        Maher Noureldine	3/19/2022
*******************************************************************************/

#include <vector>
#include "Test.h"
#include <string.h>

using namespace std;
using std::vector;

class TestLibrary
{
    public:
   /**
    * Default Constructor
    * Create TestLibrary Object
    */
	TestLibrary();
   /**
    * This method creates callable Test Objects and stores them
    * in the vector<Test> macLibrary data memeber.
    */
	void initializeTestLibrary();
   /**
    * This method prints the Test Objects in TestLibrary.
    */
	void viewTestLibrary();
    // Read the config file for test library data
    void readConfig();
    // parse the string 
    void acquireTestInfo(const string&);
    // Return the test library.
    vector<ITest*> getMcLibrary();

    /*//Check if current test exists in the library.*/
    bool testNameExists(string);

    /*Input the test name*/
    void inputTestName(string);
    void inputTestResult(bool);
    void inputTestDelay(bool);
    void inputTestException(bool);

    // Add test to the library.
    void addTestToLibrary();

    // Write the library data to file
    void saveConfig();

    private:
        //Test attributes.
        string tName;
        bool tBool1, tBool2, tBool3;
        //Data member setters.
        void setTestName(string);
        void setTestResult(bool);
        void setTestDelay(bool);
        void setTestException(bool);

        class TestData {
            public:
                string tName;
                bool tBoolVal1;
                bool tBoolVal2;
                bool tBoolVal3;
                TestData(string, bool, bool, bool);
        };
     /*// Vector of Test objects */
     vector<ITest*> mcLibrary;
     vector<TestData> fileTestData;
     /*//Input new test data*/
     string inputTestData();
};

#endif // TESTLIBRARY_H