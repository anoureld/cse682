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
		void logTestResult(int anTestID, string acTestName, bool abTestResult, 
			string acExceptionsThrown, string acStartTimepoint, string acEndTimepoint);
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