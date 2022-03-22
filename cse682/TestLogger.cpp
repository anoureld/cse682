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

void TestLogger::clearTestLog(bool abPrintMsg)
{
	mcAllTestOutputs.clear();
	if (abPrintMsg)
	{
		cout << "\n\tTest logger cleared\n";
	}
}

vector<TestLogger::msTestOutput> TestLogger::getResultOutput()
{
	return mcAllTestOutputs;
}