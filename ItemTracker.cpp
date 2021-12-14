#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <Python.h>

#include "ItemTracker.h"

using namespace std;

// Function to call procedures from Python that return no value.
void ItemTracker::CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	// Changed to strcpy_s, std::strcpy marked unsafe
	strcpy_s(procname, pName.length() + 1, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// Function to call procedures from Python that take a string parameter and return an int variable.
int ItemTracker::callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	// Changed to strcpy_s, std::strcpy marked unsafe
	strcpy_s(procname, proc.length() + 1, proc.c_str());

	char* paramval = new char[param.length() + 1];
	// Changed to strcpy_s, std::strcpy marked unsafe
	strcpy_s(paramval, param.length() + 1, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

void ItemTracker::DisplayMenu()
{
	// Set fill characters and manipulate format to print top border of box 
	cout << setfill('-') << setw(55) << "" << endl;
	cout << setfill(' ');
	cout << setw(2) << left << "|" << "Select an Option";
	cout << setw(37) << right << "|" << endl;
	cout << setfill('-') << setw(55) << "" << endl;
	// Reset fill character
	cout << setfill(' ');

	// Format and display four menu options
	cout << setw(2) << left << "|" << "1- View Frequency of All Items Purchased in a Day";
	cout << setw(4) << right << "|" << endl;

	cout << setw(2) << left << "|" << "2- View a Specific Item's Frequency";
	cout << setw(18) << right << "|" << endl;

	cout << setw(2) << left << "|" << "3- View Purchasing Frequency Histogram";
	cout << setw(15) << right << "|" << endl;

	cout << setw(2) << left << "|" << "4- Exit Program";
	cout << setw(38) << right << "|" << endl;

	// Set fill characters and manipulate format to print bottom border of box
	cout << setfill('-') << setw(55) << "" << endl;
	// Reset fill character
	cout << setfill(' ');
}

int ItemTracker::GetUserInput()
{
	bool validInput = false;
	int input;

	while (!validInput)
	{
		DisplayMenu();

		// Get and validate user input
		try
		{
			cin >> input;
			cout << endl;

			// Condition for if cin fails from invalid input type.
			if (cin.fail())
			{
				throw invalid_argument("Invalid input. Your input must be 1, 2, 3, or 4.");
			}

			if ((input < 1) || (input > 4))
			{
				throw runtime_error("Invalid input. Your input must be 1, 2, 3, or 4.");
			}
		}
		// Catch for input that isn't an integer.
		catch (invalid_argument& excpt)
		{
			cout << excpt.what() << endl;
			cout << endl;
			cout << endl;

			// Clear error state.
			cin.clear();
			// Ignore up to 500 characters or until newline is reached, used to clear cin.
			cin.ignore(500, '\n');

			continue;  // Restart loop
		}
		// Catch for number that isn't 1, 2, 3, or 4.
		catch (runtime_error& excpt)
		{
			cout << excpt.what() << endl;
			cout << endl;
			cout << endl;

			continue;  // Restart loop
		}
		// If this point is reached, no exceptions were thrown and input is valid. Loop can end.
		validInput = true;
	}
	// Input is valid, update variable.
	userInput = input;
}

// Function for menu option 1.
void ItemTracker::ListAllFrequencies()
{
	// Use CallProcedure to use Python function to list all frequencies.
	CallProcedure("ListAllFrequencies");
	cout << endl;
	// Print message to prompt user to press any key to continue, system will wait until key is pressed.
	system("pause");
	cout << endl;
}

// Function for menu option 2.
void ItemTracker::ListSpecificFrequency()
{
	string searchItem;

	// Take input to pass as parameter.
	cout << "Enter an item to count: ";
	cin.ignore();
	cin >> searchItem;
	// Change first letter to capital.
	searchItem[0] = (toupper(searchItem[0]));
	cout << endl;

	// Call function from Python and output results.
	cout << searchItem << ": " << callIntFunc("ListSpecificFrequency", searchItem) << endl;
	cout << endl;
	// Print message to prompt user to press any key to continue, system will wait until key is pressed
	system("pause");
	cout << endl;
}

// Function for menu option 3.
void ItemTracker::CreateHistogram()
{
	ifstream inFS;
	string itemName;
	int itemNum;

	// Call Python procedure to create a file for C++ to read.
	CallProcedure("CreateFrequencyFile");

	// Open the file created in Python.
	inFS.open("frequency.dat");

	// Loop until end of file is reached.
	while (!inFS.eof())
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Take string and int from file and assign to respective variables.
		inFS >> itemName >> itemNum;
		cout << endl;
		cout << itemName << " ";
		// Loop to print the correct number of asterisks.
		for (int i = 0; i < itemNum; ++i)
		{
			// Change text color for asterisks.
			SetConsoleTextAttribute(hConsole, 11);
			cout << "*";
		}
		// Change text color back to white.
		SetConsoleTextAttribute(hConsole, 7);
	}
	// Close the file.
	inFS.close();
	cout << endl;
	cout << endl;
	// Print message to prompt user to press any key to continue, system will wait until key is pressed.
	system("pause");
	cout << endl;
}

// Function to act on user input.
bool ItemTracker::ReadUserInput()
{
	GetUserInput();

	if (userInput == 1)
	{
		ListAllFrequencies();
		return true;
	}
	else if (userInput == 2)
	{
		ListSpecificFrequency();
		return true;
	}
	else if (userInput == 3)
	{
		CreateHistogram();
		return true;
	}
	else if (userInput == 4)
	{
		return false;
	}
}