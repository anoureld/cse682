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
**    1.0        Maher Noureldine	13/2/2022
*******************************************************************************/

#include <vector>
#include "Test.h"

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
    // Write the library data to file
    void saveConfig();
    // Return the test library.
    vector<ITest*> getMcLibrary();
    // Add test to the library.
    void addTestToLibrary();


    private:
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
     /*//Check if current test exists in the library.*/
     bool testNameExists(string);
     /*//Validate new test data*/
     bool validateTestData(string);
     /*//Input new test data*/
     string inputTestData();
};

#endif // TESTLIBRARY_H