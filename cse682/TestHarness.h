#ifndef TESTHARNESS_H
#define TESTHARNESS_H
/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestExecutor.h
** DESCRIPTION:
** This file includes function definitions and data members for the Test Executor
** software component.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**   1.0        Sab Fernandes/Maher Noureldine           3/19/2022
*******************************************************************************/

#include "TestExecutor.h"
#include "TestLibrary.h"
#include "TestLogger.h"
#include "TestSequence.h"
#include <string>

using std::string;

class TestHarness
{
	public:
		void printMenu();
		void run();
		// singleton class for client-server implementation in phase 2.
		static TestHarness* getInstance();
		void shutdown();
		void setLogLevel();
		int getLogLevel();
		bool validateTestData(string);
		string inputTestData();
	private:
		TestHarness();
		void getNewTestData();
		void executeProc();
		void executeSequence();
		void printResults(int);
		TestLibrary* lcTestLibrary;
		TestSequence* lcTestSequence;
		TestLogger* lcTestLogger;
		TestExecutor* lcTestExecutor;
		int lnDesiredActionInput;
		int lnOutputLevel;
		static TestHarness* instance;
		string libraryConfigFile = "LibraryData.cfg";
};

#endif // !TESTHARNESS_H

