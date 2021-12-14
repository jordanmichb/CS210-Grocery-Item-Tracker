#ifndef CORNERGROCERTRACKINGPROGRAM_ITEMTRACKER_H_
#define CORNERGROCERTRACKINGPROGRAM_ITEMTRACKER_H_

#include <string>

using namespace std;

class ItemTracker
{
	// Public members for use in main.
	public:
		bool ReadUserInput();
	// Private members for use within class.
	private:
		int userInput;
		void CallProcedure(string pName);
		int callIntFunc(string proc, string param);
		void DisplayMenu();
		int GetUserInput();
		void ListAllFrequencies();
		void ListSpecificFrequency();
		void CreateHistogram();
};

#endif