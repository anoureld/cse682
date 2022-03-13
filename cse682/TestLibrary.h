/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
** NAME: TestLibrary.h
**
** DESCRIPTION:
** This file includes function definitions and data members for the Test Library
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

#ifndef TESTLIBRARY_H
#define TESTLIBRARY_H

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

	// Vector of Test objects 
   // (i.e., 'test library' of available tests)
	vector<ITest*> mcLibrary;

    // Read the config file for test library data
    void readConfig();

    // parse the string 
    void acquireTestInfo(const string&);

    // Write the library data to file
    void saveConfig();

    private:
        class TestData {
            public:
                string tName;
                bool tBoolVal1;
                bool tBoolVal2;
                bool tBoolVal3;
                TestData(string, bool, bool, bool);
        };
        
     vector<TestData> fileTestData;

};

#endif // TESTLIBRARY_H