/*******************************************************************************
** PROJECT:
** Test Harness, CSE 687 Object-Oriented Design, Fall 2021
** NAME: TestExecutor.cpp
** DESCRIPTION:
** This file provides functionality for the Test Executor software
** component.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0        Maher/Sab             13/3/2022
*******************************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "TestExecutor.h"
#include <thread>
#include <chrono>

using std::cout;
using std::string;
using std::ostringstream;
using std::setw;
using std::setfill;
using namespace std::this_thread;
using namespace std::chrono;

void TestExecutor::executeTestSequence(TestSequence& arcTestSequence, TestLogger& arcTestLogger)
{
   // If test sequence is empty print error message
   //if (arcTestSequence.getMcSequence().empty()) 
   //{
     // cout << "\n\tNo tests in current sequence - aborting test sequence execution\n";
   //}
   //else // Test sequence not empty then invoke callable object and store output
   //{
      // Invoke callable Test Objects
      for (auto lcCurrentTest : arcTestSequence.getMcSequence())
      {
         // Store test output
         int lnTestID = lcCurrentTest->getTestID();
         string lcTestName = lcCurrentTest->getTestName();
         bool lbTestResult{ false };
         string lcExceptionsThrown{ "NONE" };
         string lcStartTimepoint{ "NOT SET" };
         string lcEndTimepoint{ "NOT SET" };
         struct tm lsNewTime;
         ostringstream lcStartStream;
         ostringstream lcEndStream;

         // Record time prior to test execution
         time_t lnNow = time(0);
         localtime_s(&lsNewTime, &lnNow);
         lcStartStream << (1 + lsNewTime.tm_mon) << '/' << lsNewTime.tm_mday << '/' << (1900 + lsNewTime.tm_year)
             << " " << setfill('0') << setw(2) << lsNewTime.tm_hour << ":" << setw(2)
             << lsNewTime.tm_min << ":" << setw(2) << lsNewTime.tm_sec;
         lcStartTimepoint = lcStartStream.str();
         
         // Pause execution to demonstrate correct implementation of start & end timepoint stamps
         if ((*lcCurrentTest).getPauseExecution())
         {
             sleep_for(2s);
         }

         //  invoke callable object within scope of try block
         try {
            // invoking of callable object
            lbTestResult = (*lcCurrentTest)();
         }

         // Catch and log exceptions 
         catch (const std::exception& axThrownException) {
            lcExceptionsThrown = "Caught throwable of type exception with details \"" + (string)axThrownException.what() + "\"\n";
         }
         catch (int anThrownInt) {
            lcExceptionsThrown = "Caught throwable of type integer with details \"" + std::to_string(anThrownInt) + "\"\n";
         }
         catch (string acThrownString) {
            lcExceptionsThrown = "Caught throwable of type string with details \"" + acThrownString + "\"\n";
         }
         catch (char anThrownChar) {
            lcExceptionsThrown = "Caught throwable of type char with details \"" + std::to_string(anThrownChar) + "\"\n";
         }
         catch (...) {
            lcExceptionsThrown = "Caught throwable that was not type exception, string, int, or char\n";
         }

         // Record time after test execution
         lnNow = time(0);
         localtime_s(&lsNewTime, &lnNow);
         lcEndStream << (1 + lsNewTime.tm_mon) << '/' << lsNewTime.tm_mday << '/' << (1900 + lsNewTime.tm_year)
             << " " << setfill('0') << setw(2) << lsNewTime.tm_hour << ":" << setw(2)
             << lsNewTime.tm_min << ":" << setw(2) << lsNewTime.tm_sec;
         lcEndTimepoint = lcEndStream.str();
         // Provide test output to logger
         arcTestLogger.logTestResult(lnTestID, lcTestName, lbTestResult, lcExceptionsThrown, lcStartTimepoint, lcEndTimepoint);
      }
   //}
}