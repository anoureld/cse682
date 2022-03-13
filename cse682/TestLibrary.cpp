/*******************************************************************************
** PROJECT:
** Test Harness, CSE 682 Software Engineering.
** NAME: TestLibrary.cpp
** DESCRIPTION:
** This file provides functionality for the Test Libray software
** component. It is responsible for maintaining a repository of Test objects.
********************************************************************************
** VERSION HISTORY
**    Rev         Author              Date
** -----------------------------------------------------------------------------
**   1.0          Sab/Maher			13/3/2022
*******************************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include "TestLibrary.h"

using namespace std;
using std::cout;
using std::string;
using std::setw;
using std::fixed;

TestLibrary::TestLibrary()
{
	initializeTestLibrary();
}

void TestLibrary::initializeTestLibrary()
{
	// Instantiate callable test objects
	//ITest* lcTestOb1 = new Test("Function 1 v1.0", false, false, false); // function 1 v1.0 fails
	//ITest* lcTestOb2 = new Test("Function 1 v1.1", true, false, false);  // function 2 v2.0 passes
	//ITest* lcTestOb3 = new Test("Function 2 v1.0", false, false, false); // function 2 v1.0 fails
	//ITest* lcTestOb4 = new Test("Function 2 v1.1", false, true, false); // function 2 v1.1 fails and pauses execution
	//ITest* lcTestOb5 = new Test("Function 3 v1.0", true, false, true); // function 3 v1.0 throws exception


	//load test objects into library
	//mcLibrary.push_back(lcTestOb1);
	//mcLibrary.push_back(lcTestOb2);
	//mcLibrary.push_back(lcTestOb3);
	//mcLibrary.push_back(lcTestOb4);
	//mcLibrary.push_back(lcTestOb5);

	readConfig();

	for (size_t i = 0; i < fileTestData.size(); i++)
	{
		ITest* lcTestOb = new Test(fileTestData[i].tName, fileTestData[i].tBoolVal1, fileTestData[i].tBoolVal2, fileTestData[i].tBoolVal3);
		mcLibrary.push_back(lcTestOb);
	}
}

void TestLibrary::viewTestLibrary()
{
   // Print table and column headings
	cout << "\n\tCurrent test library:\n";
	cout << "\n\t" << setw(8) << "TestID" << setw(20) << "TestName" << "\n\n";

   // If Test Library is empty print error message
	if (0 == mcLibrary.size())
	{
		cout << "\t  (No tests in library)\n";
	}

   // Test Library is not empty, then print all Test objects contained within library
	else
	{
		for (unsigned int i = 0; i < mcLibrary.size(); i++)
		{
			cout << "\t" << setw(8) << mcLibrary[i]->getTestID() << setw(20) << mcLibrary[i]->getTestName() << "\n";
		}
	}
}

void TestLibrary::readConfig()
{
	std::ifstream myfile("../cse682/LibraryData.txt");
	string stringLine;

	if (myfile.is_open()) {
		while (myfile) {
			getline(myfile, stringLine);
			acquireTestInfo(stringLine);
			if (myfile.eof()) {
				myfile.close();
				break;
			}
		}
	}
	else
	{
		std::cout << " Issue reading test configuration. aborting" << std::endl;
	}
}

TestLibrary::TestData::TestData(string n, bool b1, bool b2, bool b3)
	:tName{ n }, tBoolVal1{ b1 }, tBoolVal2{ b2 }, tBoolVal3{ b3 }
{}

void TestLibrary::acquireTestInfo(const string& str) {
	string delim1 = ":";
	string delim2 = ",";
	
	size_t pos = str.find(delim1);
	string stringAfterdelim = str.substr(pos + delim1.size());

	string name;
	string bs1, bs2, bs3;
	//std::cout << str << std::endl;
	// get the name
	pos = stringAfterdelim.find(delim2);
	name = stringAfterdelim.substr(0, pos);
	stringAfterdelim = stringAfterdelim.substr(pos+1, stringAfterdelim.size());
	//std::cout << name << " - " << stringAfterdelim << std::endl;

	pos = stringAfterdelim.find(delim2);
	bs1 = stringAfterdelim.substr(0, pos);
	stringAfterdelim = stringAfterdelim.substr(pos+1, stringAfterdelim.size());
	//std::cout << bs1 << " - " << stringAfterdelim << std::endl;
	
	pos = stringAfterdelim.find(delim2);
	bs2 = stringAfterdelim.substr(0, pos);
	stringAfterdelim = stringAfterdelim.substr(pos+1, stringAfterdelim.size());
	//std::cout << bs2 << " - " << stringAfterdelim << std::endl;

	pos = stringAfterdelim.find(delim2);
	bs3 = stringAfterdelim.substr(0, pos);
	stringAfterdelim = stringAfterdelim.substr(pos+1, stringAfterdelim.size());
	//std::cout << bs3 << " - " << stringAfterdelim << std::endl;

	bool b1, b2, b3;
	b1 = (bs1 == "true") ? true : false;
	b2 = (bs2 == "true") ? true : false;
	b3 = (bs3 == "true") ? true : false;
	//std::cout << name << b1 << b2 << b3 << std::endl;

	fileTestData.push_back(TestData(name, b1, b2, b3));
}

void TestLibrary::saveConfig()
{
	// write to the file
	std::cout << "Saving config to data store" << std::endl;
	std::ofstream myfile("../cse682/LibraryData.txt");

	if (myfile.is_open())
	{
		for (size_t i = 0; i < fileTestData.size(); i++)
		{
			myfile << "Test" << i + 1 << ":" << fileTestData[i].tName << "," << ((fileTestData[i].tBoolVal1 == true) ? "true" : "false") << ","
				<< ((fileTestData[i].tBoolVal2 == true) ? "true" : "false") << "," << ((fileTestData[i].tBoolVal3 == true) ? "true" : "false");
			//std::cout << "Test" << i+1 << ":" << fileTestData[i].tName << "," << ((fileTestData[i].tBoolVal1 == true)? "true":"false") << "," 
				//<< ((fileTestData[i].tBoolVal2 == true)?"true":"false") << "," << ((fileTestData[i].tBoolVal3 == true)?"true":"false") << std::endl;
			if (i < fileTestData.size() - 1)
			{
				myfile << std::endl;
			}
		}
		// close file
		myfile.close();
	}
	else
	{
		std::cout << "Could not save library data. Please check the LibraryData.txt file" << std::endl;
	}
}

vector<ITest*> TestLibrary::getMcLibrary()
{
	return mcLibrary;
}


void TestLibrary::addTestToLibrary()
{
	string tName;
	bool tBool1, tBool2, tBool3;
	string bs1, bs2, bs3;

	cout << "Please enter your test name: ";
	cin.ignore();
	getline(std::cin, tName);
	for (size_t i = 0; i < getMcLibrary().size(); i++)
	{
		if (tName == getMcLibrary()[i]->getTestName())
		{
			cout << "Test name already exists, please enter a different name: ";
			cin.ignore();
			getline(cin, tName, '\n');
		}
	}
	cout << "Please enter result status: ";
	cin.ignore();
	getline(cin, bs1, '\n');
	while (validateTestData(bs1))
	{
		cout << "Please enter true or false: ";
		getline(cin, bs1, '\n');
	}

	cout << "Please enter Exception status: ";
	cin.ignore();
	getline(cin, bs2, '\n');
	while (validateTestData(bs2))
	{
		cout << "Please enter true or false: ";
		getline(cin, bs2, '\n');
	}

	cout << "Please enter delay status: ";
	cin.ignore();
	getline(cin, bs3, '\n');
	while (validateTestData(bs3))
	{
		cout << "Please enter true or false: ";
		getline(cin, bs3, '\n');
	}

	tBool1 = (bs1 == "true") ? true : false;
	tBool2 = (bs2 == "true") ? true : false;
	tBool3 = (bs3 == "true") ? true : false;

	fileTestData.push_back(TestData(tName, tBool1, tBool2, tBool3));
	ITest* lcTestOb = new Test(tName, tBool1, tBool2, tBool3);
	mcLibrary.push_back(lcTestOb);
}

bool TestLibrary::validateTestData(string input)
{
	if (strcmp(input.c_str(), "true") != 0 && strcmp(input.c_str(), "false") != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}