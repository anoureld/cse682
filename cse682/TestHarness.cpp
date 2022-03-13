/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: Test.cpp
** DESCRIPTION:
** This file provides functionality for the Test Harness software
** component. It is responsible for allowing a user to select and execute any 
** number of small unit tests.
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**   1.0        Sab Fernandes       13/3/2022
*******************************************************************************/

#include "TestHarness.h"
#include <iostream>
#include "TestLibrary.h"
#include "TestSequence.h"
#include "TestExecutor.h"
#include "TestLogger.h"

using namespace std;

using std::cout;
using std::cin;


TestHarness* TestHarness::instance{ nullptr };

/**
 * State machine for Single-User Test Harness.
 */
void TestHarness::run()
//int main()
{
   // Print header describing purpose of program and giving guidance to user
   cout << "\n-----------------------------------------------------------------------------------------------";
   cout << "\n\t\t Test Harness";
   cout << "\n";
   cout << "\n\tEnables testing of program code.";
  cout << "\n\tAvailable unit tests to be run are instantiated into a test library.";
   cout << "\n\tUsers can select tests from the library to be tested, and insert them into a test sequence.";
   cout << "\n\tUsers can request execution of the test sequence with three different levels of output detail:";
   cout << "\n\t  1) print pass/fail only.";
   cout << "\n\t  2) print pass/fail status, and exception contents if caught.";
   cout << "\n\t  3) print pass/fail, exception contents if caught, start and end timepoints.";
   cout << "\n-----------------------------------------------------------------------------------------------\n";

   // Declare variables to hold user input
   int lnDesiredActionInput{ 0 };
   int lnOutputLevel{ 0 };

   do
   {
      // Prompt user for desired action
      cout << "\nPlease choose desired action (enter action number (or 0 for menu) then hit <return>): ";
      cin >> lnDesiredActionInput;
      
      // Input guard
      while (cin.fail())
      {
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cout << "\n\tInvalid input - please try again:";
          cin >> lnDesiredActionInput;
      }
      switch (lnDesiredActionInput)
      {
      // Print Menu of available actions
      case 0:
         printMenu();
         break;
      // View current Test Library
      case 1:
         lcTestLibrary->viewTestLibrary();
         break;
      // View current test Sequence
      case 2:
         lcTestSequence->viewTestSequence();
         break;
      // Enter new Test Sequence (NOTE: this action voids the current test sequence)
      case 3:
         lcTestSequence->inputTestSequence(*lcTestLibrary);
         break;
      // Execute Test Sequence and print results with no debugging information
      case 4:
         lcTestLogger->clearTestLog(false);
         lnOutputLevel = 1;
         lcTestExecutor->executeTestSequence(*lcTestSequence, *lcTestLogger);
         lcTestLogger->printTestResults(lnOutputLevel);
         break;
      // Execute Test Sequence and print results with moderate debugging information
      case 5:
         lcTestLogger->clearTestLog(false);
         lnOutputLevel = 2;
         lcTestExecutor->executeTestSequence(*lcTestSequence, *lcTestLogger);
         lcTestLogger->printTestResults(lnOutputLevel);
         break;
      // Execute Test Sequence and print results with detailed debugging information
      case 6:
         lcTestLogger->clearTestLog(false);
         lnOutputLevel = 3;
         lcTestExecutor->executeTestSequence(*lcTestSequence, *lcTestLogger);
         lcTestLogger->printTestResults(lnOutputLevel);
         break;
      // Print the results of the test sequence that was previously executed
      case 7:
          // Prompt user for desired output level
          cout << "\n\tPlease choose desired output level then hit <return>";
          cout << "\n\t(1 = summary only, 2 = w/ exceptions, 3 = w/ timestamps and exceptions): ";
          cin >> lnOutputLevel;
          //Input guard
          while (cin.fail() || 1 > lnOutputLevel || 3 < lnOutputLevel)
          {
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              cout << "\n\t\tInvalid input - please try again: ";
              cin >> lnOutputLevel;
          }
          // print results
          lcTestLogger->printTestResults(lnOutputLevel);
          break;
      // Clear the results from the Test logger (to get ready to run a new sequence)
      case 8:
          lcTestLogger->clearTestLog(true);
          break;
      // Clear Test Sequence.
      case 9:
          lcTestSequence->clearTestSequence();
          break;
      // Exit Program
      case 10:
          //Add test
          lcTestLibrary->addTest();
          lcTestLibrary->saveConfig();
          break;
      case 11:
         cout << "\n\nSaving data to data store(s).\n";
         shutdown();
         break;
      // Handle invalid input
      default:
         cout << "\n\tInvalid input - please try again\n";
         break;
      }
   } while (lnDesiredActionInput != 11);
}

/**
 * This method prints the menu of available program options for user to select.
 */
void TestHarness::printMenu()
{
   cout << "\n\tActions available (note that test sequence execution (options 4, 5, & 6) will clear previous log results):";
   cout << "\n\t   1 - Display the current test library";
   cout << "\n\t   2 - Display the current test sequence";
   cout << "\n\t   3 - Create a new test sequence (NOTE: this voids the current test sequence)";
   cout << "\n\t   4 - Execute test sequence, print pass/fail status only";
   cout << "\n\t   5 - Execute test sequence, print pass/fail status and exception contents";
   cout << "\n\t   6 - Execute test sequence, print pass/fail status, exception contents, & start and end timepoints";
   cout << "\n\t   7 - Print the results of the test sequence previously executed";
   cout << "\n\t   8 - Clear previous test results from the test logger";
   cout << "\n\t   9 - Clear the test sequence.";
   cout << "\n\t   10 - Add new test to the library.";
   cout << "\n\t   11 - Exit the program." << endl;
}

/*public get instance to return an instance of the test harness*/
TestHarness* TestHarness::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TestHarness();
    }

    return instance;
}

/* Private constructor*/
TestHarness::TestHarness()
{
    //instance = new TestHarness();
    lcTestLibrary = new TestLibrary();
    lcTestSequence = new TestSequence();
    lcTestLogger = new TestLogger();
    lcTestExecutor = new TestExecutor();
}

void TestHarness::shutdown()
{
    // write to file. 
    //TestLibrary Write to file
    lcTestLibrary->saveConfig();
    std::cout << "Cleaning up memory allocation" << std::endl;
    delete lcTestLibrary;
    delete lcTestSequence;
    delete lcTestLogger;
    delete lcTestExecutor;
    std::cout << "Memory de-allocated" << std::endl;
}