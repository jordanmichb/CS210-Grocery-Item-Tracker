#include <iostream>

#include "ItemTracker.h"

using namespace std;

int main()
{
	// Create object of type ItemTracker.
	ItemTracker item1;

	// Loop coninuously.
	while (1)
	{
		// Condition to end loop if ReadUserInput returns false (option 4 is chosen).
		if (!item1.ReadUserInput())
		{
			cout << "Exiting program." << endl;
			break;
		}
	}
	return 0;
}