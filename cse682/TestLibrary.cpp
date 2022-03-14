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
**   1.0          Sab/Maher			13/4/2022
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
	cout << "Start adding test to library...." << endl;
	string tName;
	bool tBool1, tBool2, tBool3;
	string bs1, bs2, bs3;

	cout << "Please enter your test name: ";
	cin.ignore();
	getline(std::cin, tName, '\n');
	while (testNameExists(tName))
	{
		cout << "Please enter a different name: ";
		getline(cin, tName, '\n');
	} 

	cout << "Please enter result status (true/false): ";
	bs1 = inputTestData();

	cout << "Please enter Exception status (true/false): ";
	bs2 = inputTestData();

	cout << "Please enter delay status (true/false): ";
	bs3 = inputTestData();

	tBool1 = (bs1 == "true") ? true : false;
	tBool2 = (bs2 == "true") ? true : false;
	tBool3 = (bs3 == "true") ? true : false;

	fileTestData.push_back(TestData(tName, tBool1, tBool2, tBool3));
	ITest* lcTestOb = new Test(tName, tBool1, tBool2, tBool3);
	mcLibrary.push_back(lcTestOb);
}

bool TestLibrary::testNameExists(string tName)
{
	for (size_t i = 0; i < getMcLibrary().size(); i++)
	{
		if ((string)tName == (string)getMcLibrary()[i]->getTestName())
		{
			return true;
		}
	}
	return false;
}

string TestLibrary::inputTestData()
{
	string input;
	getline(cin, input, '\n');
	while (validateTestData(input))
	{
		cout << "Please enter true or false: ";
		getline(cin, input, '\n');
	}
	return input;
}

bool TestLibrary::validateTestData(string input)
{
	if ((string) input == "true" || (string) input == "false")
	{
		return false;
	}
		return true;
}