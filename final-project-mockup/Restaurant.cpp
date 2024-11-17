#include "Restaurant.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream> 
#include <string> 

Restaurant::Restaurant()
{
	name = "NULL";
	rating = 0.0;
	cuisine = "NULL";
	price = 0;
	favorite = false;
	next = nullptr;
}

Restaurant::Restaurant(string name, float rating, string cuisine, int price, bool favorite, Restaurant* next)
{
	this->name = name;
	this->rating = rating;
	this->cuisine = cuisine;
	this->price = price;
	this->favorite = favorite;
	this->next = next;
}

Restaurant::~Restaurant()
{}

void Restaurant::setName(string name)
{
	this->name = name;
}

void Restaurant::setRating(float rating)
{
	this->rating = rating;
}

void Restaurant::setCuisine(string cuisine)
{
	this->cuisine = cuisine;
}

void Restaurant::setPrice(int price)
{
	this->price = price;
}

void Restaurant::setFavorite(bool favorite)
{
	this->favorite = favorite;
}

string Restaurant::getName()const
{
	return name;
}

float Restaurant::getRating()const
{
	return rating;
}

string Restaurant::getCuisine()const
{
	return cuisine;
}

int Restaurant::getPrice()const
{
	return price;
}

Restaurant* Restaurant::getNext()const
{
	return next;
}

void Restaurant::setNext(Restaurant* next)
{
	this->next = next;
}

bool Restaurant::getFavorite()const
{
	return favorite;
}

// the above are more behind the scenes

void Restaurant::rateRestaurant() // mostly conceptual, need to add range checks & whatnot
{
	cout << "You are rating: " << name << endl;

	cout << "Rating (1-5): ";
	cin >> rating;
	
	cout << "Favorite? (0 = no, 1 = yes): ";
	cin >> favorite;
	
	cout << "Your rating has been recorded!" << endl;

	Sleep(2000);
	system("cls");
}

void Restaurant::favoriteRestaurant()
{
	char fav;

	cout << "Favorite? (Y/N): ";
	cin >> fav;

	if (fav == 'y' || fav == 'Y')
	{
		setFavorite(true);
	}
	else if (fav == 'n' || fav == 'N')
	{
		setFavorite(false);
	}
	else
	{
		cout << "Invalid option, returning to menu" << endl;
		Sleep(2000);
		system("cls");
	}

}

//saving restaurant edits to the file
//saving the user edits to the restaurant list from the session
//saving the user edits to the restaurant list from the session
void Restaurant::saveRestaurantsToFile() const {
	std::ofstream file("Restaurants.txt");
	if (!file) {
		std::cerr << "Failed to open file for writing: Restaurants.txt\n";
		return;
	}
	Restaurant* current = head;
	while (current != nullptr) {
		{
			file << current->name << "," << current->cuisine << "," << current->price << "," << current->rating << "\n";
			current = current->next;
		}
		file.close();
	}
}
//initial user interaction stuff - Alex
void Restaurant::displayMenu()
{
	cout << "---- Menu -------------------------------" << endl;
	cout << "1) Search by cuisine" << endl;
	cout << "2) See your favorite restaurants" << endl;
	cout << "3) Rate a restaurant" << endl;
	cout << "4) Help me figure out what to eat" << endl;
	cout << "-----------------------------------------" << endl;
}
void Restaurant::setInitialMenuChoice() {
	int choice; std::cin >> choice; switch (choice) {
	case 1: searchByCuisine();
		break;
	case 2: seeFavoriteRestaurants();
		break;
	case 3: rateRestaurant();
		break;
	case 4: helpMeDecide();
		break;
	default:
		std::cout << "Invalid choice. Please try again.\n";
	}
}
void Restaurant::searchByCuisine() {
	std::string cuisine;
	std::cout << "What type of cuisine are you craving? ";
	std::cin >> cuisine; 

	bool found = false;
	Restaurant* current = head; 
	std::cout << "Restaurants offering " << cuisine << " cuisine:\n";
	while (current != nullptr){
		if (current->cuisine.find(cuisine) != std::string::npos) {
			std::cout << "- " << current->name << " (Cost: $" << current->price << ", Rating: " << current->rating << ")\n";
			found = true;
	} 
		current = current->next; 
	}

	if (!found) { std::cout << "Sorry, we found no restaurants found for the specified cuisine.\n"; }
}
void Restaurant::seeFavoriteRestaurants() {
	// Display the user's favorite restaurants here 
	//I'm hoping this doesn't require too many steps
	std::cout << "Here are your favorite restaurants...\n";
}
void Restaurant::helpMeDecide() {
	//std::cout << "Let me help you figure out what to eat...\n";
	std::cout << "Let's try someething different today!";
}
