/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
**
** NAME: TestExecutor.h
**
** DESCRIPTION:
** This file includes function definitions and data members for the Test Executor
** software component.
**
**
********************************************************************************
** VERSION HISTORY
**
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**
**
*******************************************************************************/

#ifndef TESTEXECUTOR_H
#define TESTEXECUTOR_H

#include "Test.h"
#include "TestSequence.h"
#include "TestLogger.h"

class TestExecutor
{
public:

    /**
    * This method invokes all callable objects contained within in the testSequence. 
    * Results of simulated test results are sent to the testLogger to be stored 
    * and formatted.
    * @param arcTestSequence Reference to current Test Sequence
    * @param arcTestLogger Reference to current Test Logger
    */
	void executeTestSequence(TestSequence& arcTestSequence, TestLogger& arcTestLogger);
};

#endif // TESTEXECUTOR_H