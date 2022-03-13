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
		virtual void logTestResult(int, string, bool, string, string, string) = 0;
		virtual void printTestResults(int) = 0;
		virtual void clearTestLog(bool) = 0;
};

#endif // ILOGGER_H