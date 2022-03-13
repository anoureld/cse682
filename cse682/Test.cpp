/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: Test.cpp
** DESCRIPTION:
** This file provides functionality for the Test Harness software
** component. It is responsible for defining a test unit object.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**	1.0			Maher Noureldine	13/3/2022
*******************************************************************************/

#include <exception>
#include "Test.h"

// Initialize static member representing the number of test objects
int Test::snNumUnitTests = 0;

Test::Test()
	: mcTestName{ "BLANK" }, mbTestResult{ 0 }, mbPauseExecution{ 0 }, mbThrowsException{ 0 }
{
	// Set Test ID to next value
	snNumUnitTests++;
	mnTestID = snNumUnitTests;
}

Test::Test(string acTestName, bool abTestResult, bool abPauseExecution, bool abThrowsException)
	: mcTestName{ acTestName }, mbTestResult{ abTestResult }, mbPauseExecution{ abPauseExecution }, mbThrowsException{ abThrowsException }
{
   // Set Test ID to next value
	snNumUnitTests++;
	mnTestID = snNumUnitTests;
}

Test::~Test()
{
	// Decrement count of Test objects when object goes out of scope
	snNumUnitTests--;
}

int Test::getTestID()
{
	return mnTestID;
}

string Test::getTestName()
{
	return mcTestName;
}

bool Test::getPauseExecution()
{
	return mbPauseExecution;
}

bool Test::getTestResult()
{
	return mbTestResult;
}

bool Test::operator()(void)
{
	// Test not-designed to throw exception 
	if (!mbThrowsException)
	{
		return mbTestResult;
	}

   // Test designed to throw exception
	else
	{
		throw std::exception("divide by zero");
		return mbTestResult;
	}
}