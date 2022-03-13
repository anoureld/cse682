#ifndef ITEST_H_
#define ITEST_H_

/*
* PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
** NAME: ITest.h
**
** DESCRIPTION:
** defines the contract for Test drivers for the test harness
**
**
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0          Sab                  2/5
**
*/

#include <string>
using std::string;

class ITest
{
public:
	virtual bool operator()(void) = 0;
	virtual string getTestName() = 0;
	virtual int getTestID() = 0;
	virtual bool getPauseExecution() = 0;
};

#endif // !ITEST_H_