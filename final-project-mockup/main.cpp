#include "Restaurant.h"
using namespace std;
//moving this function into the Restaurant class - Alex
//void displayMenu();
//moving a version of this into the Restaurant class - Alex
//int makeSelection();

int main()
{
	Restaurant restaurant;
	RestaurantList restaurantlist;
	restaurantlist.getRestaurantsFromFile("Restaurants.txt"); // Load the restaurant data from a file
	restaurant.displayMenu();
	restaurant.setInitialMenuChoice();
	restaurant.saveRestaurantsToFile();


	return 0;
}

//void displayMenu()
//{
	//cout << "---- Menu -------------------------------" << endl;
	//cout << "1) Search by cuisine" << endl;
	//cout << "2) See your favorite restaurants" << endl;
	//cout << "3) Rate a restaurant" << endl;
	//cout << "4) Help me figure out what to eat" << endl;
	//cout << "-----------------------------------------" << endl;
//}

//int makeSelection()
//{
	//int choice;

	//cout << "Your selection: ";
	//cin >> choice;

	//if (choice <= 0 || choice >= 5)
	//{
		//cout << "Invalid choice" << endl;
		//Sleep(2000);
		//system("cls");
	//}
	//else
	//{
		//return choice;
	//}

//}
