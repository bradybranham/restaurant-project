#include "Restaurant.h"
using namespace std;

void displayMenu();
int makeSelection();

int main()
{
	Restaurant restaurant;
	restaurant.loadRestaurantsFromFile("Restaurants.txt"); // Load the restaurant data from a file
	restaurant.displayMenu();
	restaurant.setInitialMenuChoice();
	restaurant.saveRestaurantsToFile();


	return 0;
}

void displayMenu()
{
	cout << "---- Menu -------------------------------" << endl;
	cout << "1) Search by cuisine" << endl;
	cout << "2) See your favorite restaurants" << endl;
	cout << "3) Rate a restaurant" << endl;
	cout << "4) Help me figure out what to eat" << endl;
	cout << "-----------------------------------------" << endl;
}

int makeSelection()
{
	int choice;

	cout << "Your selection: ";
	cin >> choice;

	if (choice <= 0 || choice >= 5)
	{
		cout << "Invalid choice" << endl;
		Sleep(2000);
		system("cls");
	}
	else
	{
		return choice;
	}

}
