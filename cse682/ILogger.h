#ifndef ILogger_H
#define ILOGGER_H
/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: ILogger.h
** DESCRIPTION:
** Defines the contract for Loggers for the test harness.
********************************************************************************
** VERSION HISTORY
**    Rev         Author					Date
** -----------------------------------------------------------------------------
**   1.0        Maher Noureldine           3/13/2022
*******************************************************************************/

#include <string>

using namespace std;

class ILogger
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

		virtual void logTestResult(int, string, bool, string, string, string) = 0;
		virtual void clearTestLog(bool) = 0;
		virtual vector<msTestOutput> getResultOutput() = 0;
};

#endif // ILOGGER_H