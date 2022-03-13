/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestLogger.cpp
** DESCRIPTION:
** This file provides functionality for the Test Logger software component. 
** It is responsible for formatting, storing, and outputting unit test
** results.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0         M. Noureldine       3/13/2022
*******************************************************************************/
#include <iomanip>
#include <iostream>
#include "TestLogger.h"

using std::cout;
using std::setw;

TestLogger::TestLogger() {}
void TestLogger::logTestResult(int anTestID, string acTestShortName, bool abTestResult, string acExceptionsThrown, string acStartTimepoint, string acEndTimepoint)
{
	// Gather test results inside a single struct instance
	msTestOutput lsTestOutput;
	lsTestOutput.mnTestID = anTestID;
	lsTestOutput.mcTestName = acTestShortName;
	lsTestOutput.mbTestResult = abTestResult;
	lsTestOutput.mcExceptionsThrown = acExceptionsThrown;
	lsTestOutput.mcStartTimepoint = acStartTimepoint;
	lsTestOutput.mcEndTimepoint = acEndTimepoint;
	
   // Add test result struct to test output vector
	mcAllTestOutputs.push_back(lsTestOutput);
}
void TestLogger::printTestResults(int anDetailLevel)
{
	string lcNone = "NONE";
	string lcPassed = "Passed";
	string lcFailed = "Failed";

	// If logger is empty, print statement saying that
	if (mcAllTestOutputs.empty())
	{
		cout << "\n\t(Logger is empty)\n";
	}
	// If logger is not empty, print test results at requested detail level
	else
	{
		//print pass/fail only
		if (anDetailLevel == 1)
		{
			cout << "\n\tTest Summary:\n";
			cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result\n";
			for (unsigned int i = 0; i < mcAllTestOutputs.size(); i++)
			{
				// Test passes and is exception free
				if (mcAllTestOutputs[i].mbTestResult == true && mcAllTestOutputs[i].mcExceptionsThrown == lcNone)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(15) << lcPassed;
				}
				// Test fails if exception is thrown or boolean predicate indicates fail
				else if (mcAllTestOutputs[i].mcExceptionsThrown != lcNone || mcAllTestOutputs[i].mbTestResult == false)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(15) << lcFailed;
				}
			}
			cout << "\n";
		}
		// print pass/fail status, and exception contents if caught
		else if (anDetailLevel == 2)
		{
			cout << "\n\tTest Summary:\n";
			cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result\n";
			for (unsigned int i = 0; i < mcAllTestOutputs.size(); i++)
			{
				// Test passes and is exception free
				if (mcAllTestOutputs[i].mbTestResult == true && mcAllTestOutputs[i].mcExceptionsThrown == lcNone)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(14) << lcPassed << "\n";
				}
				// Test fails if exception is thrown or boolean predicate indicates fail
				else if (mcAllTestOutputs[i].mcExceptionsThrown != lcNone || mcAllTestOutputs[i].mbTestResult == false)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(14) << lcFailed << "\n";
				}
				cout << "\t\t\tException: " << mcAllTestOutputs[i].mcExceptionsThrown;
			}
			cout << "\n";
		}
		//print pass/fail, exception contents if caught, start and end timepoints
		else if (anDetailLevel == 3)
		{
			cout << "\n\tTest Summary:\n";
			cout << "\n\t" << setw(4) << "Test ID" << setw(20) << "Test Name" << setw(15) << "Test Result" << setw(24)
				<< "Start Timepoint" << setw(24) << "End Timepoint" << "\n";
			for (unsigned int i = 0; i < mcAllTestOutputs.size(); i++)
			{
				// Test passes and is exception free
				if (mcAllTestOutputs[i].mbTestResult == true && mcAllTestOutputs[i].mcExceptionsThrown == lcNone)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(15) << lcPassed
						<< setw(24) << mcAllTestOutputs[i].mcStartTimepoint << setw(24) << mcAllTestOutputs[i].mcEndTimepoint << "\n";
				}
				// Test fails if exception is thrown or boolean predicate indicates fail
				else if (mcAllTestOutputs[i].mcExceptionsThrown != lcNone || mcAllTestOutputs[i].mbTestResult == false)
				{
					cout << "\n\t" << setw(7) << mcAllTestOutputs[i].mnTestID << setw(20) << mcAllTestOutputs[i].mcTestName << setw(15) << lcFailed
						<< setw(24) << mcAllTestOutputs[i].mcStartTimepoint << setw(24) << mcAllTestOutputs[i].mcEndTimepoint << "\n";
				}
				cout << "\t\t\tException: " << mcAllTestOutputs[i].mcExceptionsThrown;
			}
			cout << "\n";
		}
	}
}

void TestLogger::clearTestLog(bool abPrintMsg)
{
	mcAllTestOutputs.clear();
	if (abPrintMsg)
	{
		cout << "\n\tTest logger cleared\n";
	}
}