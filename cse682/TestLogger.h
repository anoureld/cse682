#ifndef TESTLOGGER_H
#define TESTLOGGER_H
/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestLogger.h
** DESCRIPTION:
** This file includes function definitions and data members for the Test Logger.
** software component.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0         Maher Noureldine       3/12/2022
**	  1.1		  Sabyson Fernandes	     3/19/2022
*******************************************************************************/

#include <string>
#include <vector>
#include "ILogger.h"

using std::string;
using std::vector;

class TestLogger : public ILogger
{
	public:
		// Grouped variables that define the results of a single test
		struct msTestOutput
		{
			int mnTestID = 0;
			string mcTestName;
			bool mbTestResult = 0;
			string mcExceptionsThrown;
			string mcStartTimepoint;
			string mcEndTimepoint;
		};

		/**
		 * Constructor
		 * Create TestLogger Object
		 */
		TestLogger();
		/**
		* This method loads parameters into vector <msTestOutput> allTestOutputs data member.
		* @param anTestID Test Object identifier
		* @param acTestName Test Object name
		* @param abTestResult Simulated test result from invoking Test Object
		* @param acExceptionsThrown Exceptions thrown from invoking Test Object.
		* @param arStartTime Time test execution starts
		* @param arEndTime Time test execution ends
		*/
		void logTestResult(int anTestID, string acTestName, bool abTestResult, string acExceptionsThrown, string acStartTimepoint, string acEndTimepoint);
		/**
		* Print test results.
		* @param detailLevel 1 = Pass/Fail;
		*                    2 = Pass/Fail and application specific messages;
		*                    3 = Pass/Fail, application specific messages, date and time
		*/
		void printTestResults(int aDetailLevel);
		/**
		* This method clears data member values in preparation for the execution of another
		* test sequence.
		*/
		void clearTestLog(bool abPrintMsg);

		/**
		* This method returns a reference to the output vector with stored results
		*/
		vector<msTestOutput> getResultOutput();

	private:
		// Vector of msTestOutput
		// Stores multiple sets of test results
		vector <msTestOutput> mcAllTestOutputs;
};
#endif // TESTLOGGER_H