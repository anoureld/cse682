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
**   1.0        Sab Fernandes/Maher Noureldine       3/19/2022
*******************************************************************************/

#include "TestHarness.h"
#include <iostream>
#include <iomanip>
#include "TestLibrary.h"
#include "TestSequence.h"
#include "TestExecutor.h"
#include "TestLogger.h"

using namespace std;

using std::cout;
using std::cin;
using std::setw;


TestHarness* TestHarness::instance{ nullptr };

/**
 * State machine for Single-User Test Harness.
 */
void TestHarness::run()
//int main()
{
   // Print header describing purpose of program and giving guidance to user
   cout << "\n\t\t\t\t\t Test Harness";
   cout << "\n-----------------------------------------------------------------------------------------------";
   cout << "\n";
   cout << "\n\tEnables testing of program code.";
   cout << "\n\tAvailable unit tests to be run are instantiated into a test library.";
   cout << "\n\tUsers can select tests from the library to be tested, and insert them into a test sequence.";
   cout << "\n\tUsers can request execution of the test sequence with three different levels of output detail:";
   cout << "\n\t  1) print pass/fail only.";
   cout << "\n\t  2) print pass/fail status, and exception contents if caught.";
   cout << "\n\t  3) print pass/fail, exception contents if caught, start and end timepoints.";
   cout << "\n-----------------------------------------------------------------------------------------------\n";


   do
   {
      // Prompt user for desired action
      cout << "\nPlease choose desired action (enter action number (or 0 for menu, 9 to exit) then hit <return>): ";
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
         if (lcTestSequence->is_empty() == true)
         {
             cout << "\n\tNo tests in current sequence - aborting test sequence execution\n";
             break;
         }
         else
         {
             //lcTestLogger->clearTestLog(false);
             //lnOutputLevel = 1;
             //lcTestExecutor->executeTestSequence(*lcTestSequence, *lcTestLogger);
             //lcTestLogger->printTestResults(lnOutputLevel);
             executeProc();
             break;
         }
      // Print the results of the test sequence that was previously executed
      case 5:
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
          /*lcTestLogger->printTestResults(lnOutputLevel);*/
          printResults(lnOutputLevel);
          break;
      // Clear the results from the Test logger (to get ready to run a new sequence)
      case 6:
          lcTestLogger->clearTestLog(true);
          break;
      // Clear Test Sequence.
      case 7:
          lcTestSequence->clearTestSequence();
          break;
       //Add new test to the library.
      case 8:
          //Add test
          cout << "Start adding test to library...." << endl;
          getNewTestData();
          cout << "Test added to library." << endl;
          break;
       //Terminate the program.
      case 9:
         cout << "\n\nSaving data to data store(s).\n";
         shutdown();
         break;
      // Handle invalid input
      default:
         cout << "\n\tInvalid input - please try again\n";
         break;
      }
   } while (lnDesiredActionInput != 9);
}

/**
 * This method prints the menu of available program options for user to select.
 */
void TestHarness::printMenu()
{
    cout << "\n\tActions available:";
    cout << "\n\t   1 - Display the current test library";
    cout << "\n\t   2 - Display the current test sequence";
    cout << "\n\t   3 - Create a new test sequence (NOTE: this voids the current test sequence)";
    cout << "\n\t   4 - Execute test sequence";
    cout << "\n\t   5 - Print the results of the test sequence previously executed";
    cout << "\n\t   6 - Clear previous test results from the test logger";
    cout << "\n\t   7 - Clear the test sequence.";
    cout << "\n\t   8 - Add new test to the library.";
    cout << "\n\t   9 - Exit the program." << endl;
}


void TestHarness::getNewTestData()
{
    string tName;
    cout << "Please enter Test Name: ";
    cin.ignore();
    getline(std::cin, tName, '\n');
    while (lcTestLibrary->testNameExists(tName))
    {
        cout << "Name already exists, please enter a different name: ";
        getline(cin, tName, '\n');
    }
    //Setting the test name.
    lcTestLibrary->inputTestName(tName);

    //Gathering test data.
    bool tBool1, tBool2, tBool3;
    string bs1, bs2, bs3;
    cout << "Please enter result status (true/false): ";
    bs1 = inputTestData();
    cout << "Please enter Exception status (true/false): ";
    bs2 = inputTestData();
    cout << "Please enter delay status (true/false): ";
    bs3 = inputTestData();
    //Validating data.
    tBool1 = (bs1 == "true") ? true : false;
    tBool2 = (bs2 == "true") ? true : false;
    tBool3 = (bs3 == "true") ? true : false;
    //Setting the values for the test.
    lcTestLibrary->inputTestResult(tBool1);
    lcTestLibrary->inputTestException(tBool2);
    lcTestLibrary->inputTestDelay(tBool3);
    //Adding the test to the library.
    lcTestLibrary->addTestToLibrary();
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
    :lnDesiredActionInput{0}, lnOutputLevel{0}
{
    //instance = new TestHarness();
    lcTestLibrary = new TestLibrary();
    lcTestSequence = new TestSequence();
    lcTestLogger = new TestLogger();
    lcTestExecutor = new TestExecutor();
}

void TestHarness::executeSequence()
{
    //setLogLevel();
    lcTestLogger->clearTestLog(false);
    lcTestExecutor->executeTestSequence(*lcTestSequence, *lcTestLogger);
}

void TestHarness::printResults(int logLvl)
{
    // Display results to user on console.
    string lcNone = "NONE";
    string lcPassed = "Passed";
    string lcFailed = "Failed";
    vector<TestLogger::msTestOutput> result = lcTestLogger->getResultOutput();

    // If logger is empty, print statement saying that
    if (result.empty())
    {
        cout << "\n\t(Logger is empty)\n";
    }
    // If logger is not empty, print test results at requested detail level
    else
    {
        //print pass/fail only
        if (logLvl == 1)
        {
            cout << "\n\tTest Summary:\n";
            cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result\n";
            for (unsigned int i = 0; i < result.size(); i++)
            {
                // Test passes and is exception free
                if (result[i].mbTestResult == true && result[i].mcExceptionsThrown == lcNone)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(15) << lcPassed;
                }
                // Test fails if exception is thrown or boolean predicate indicates fail
                else if (result[i].mcExceptionsThrown != lcNone || result[i].mbTestResult == false)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(15) << lcFailed;
                }
            }
            cout << "\n";
        }
        // print pass/fail status, and exception contents if caught
        else if (logLvl == 2)
        {
            cout << "\n\tTest Summary:\n";
            cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result\n";
            for (unsigned int i = 0; i < result.size(); i++)
            {
                // Test passes and is exception free
                if (result[i].mbTestResult == true && result[i].mcExceptionsThrown == lcNone)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(14) << lcPassed << "\n";
                }
                // Test fails if exception is thrown or boolean predicate indicates fail
                else if (result[i].mcExceptionsThrown != lcNone || result[i].mbTestResult == false)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(14) << lcFailed << "\n";
                }
                cout << "\t\t\tException: " << result[i].mcExceptionsThrown;
            }
            cout << "\n";
        }
        //print pass/fail, exception contents if caught, start and end timepoints
        else if (logLvl == 3)
        {
            cout << "\n\tTest Summary:\n";
            cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result" << setw(24)
                << "Start Timepoint" << setw(24) << "End Timepoint" << "\n";
            for (unsigned int i = 0; i < result.size(); i++)
            {
                // Test passes and is exception free
                if (result[i].mbTestResult == true && result[i].mcExceptionsThrown == lcNone)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(15) << lcPassed
                        << setw(24) << result[i].mcStartTimepoint << setw(24) << result[i].mcEndTimepoint << "\n";
                }
                // Test fails if exception is thrown or boolean predicate indicates fail
                else if (result[i].mcExceptionsThrown != lcNone || result[i].mbTestResult == false)
                {
                    cout << "\n\t" << setw(7) << result[i].mnTestID << setw(20) << result[i].mcTestName << setw(15) << lcFailed
                        << setw(24) << result[i].mcStartTimepoint << setw(24) << result[i].mcEndTimepoint << "\n";
                }
                cout << "\t\t\tException: " << result[i].mcExceptionsThrown;
            }
            cout << "\n";
        }
    }
}

void TestHarness::shutdown()
{
    lcTestLibrary->saveConfig();
    std::cout << "Cleaning up memory allocation" << std::endl;
    delete lcTestLibrary;
    delete lcTestSequence;
    delete lcTestLogger;
    delete lcTestExecutor;
    std::cout << "Memory de-allocated" << std::endl;
}

void TestHarness::setLogLevel()
{
    int logLvl;
    cout << "\n\tPlease choose desired output level then hit <return>";
    cout << "\n\t(1 = summary only, 2 = w/ exceptions, 3 = w/ timestamps and exceptions): ";
    cin >> logLvl;

    while (logLvl < 1 || logLvl > 3 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "\n\tInvalid selection. Please re-enter desired output level then hit <return>";
        cout << "\n\t(1 = summary only, 2 = w/ exceptions, 3 = w/ timestamps and exceptions): ";
        cin >> logLvl;
    }
    lnOutputLevel = logLvl;
}

int TestHarness::getLogLevel()
{
    return lnOutputLevel;
}

void TestHarness::executeProc()
{
    setLogLevel();
    executeSequence();
    printResults(getLogLevel());
}

string TestHarness::inputTestData()
{
    string input;
    getline(cin, input, '\n');
    while (validateTestData(input))
    {
        cout << "Please enter true or false: ";
        getline(cin, input, '\n');
    }
    return input;
}

bool TestHarness::validateTestData(string input)
{
    if ((string)input == "true" || (string)input == "false")
    {
        return false;
    }
    return true;
}
