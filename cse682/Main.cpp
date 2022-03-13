/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: Test.h
** DESCRIPTION:
** This file includes function definitions and data members for the Test
** software component.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**    1.0          Sab Fernandes     3/13/2022
*******************************************************************************/

#include <fstream>
#include <iostream>

#include "TestHarness.h"

int main()
{
	TestHarness* th = TestHarness::getInstance();
	th->run();
}