#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Windows.h"
using namespace std;

class Restaurant
{
private:
	string name;
	float rating;
	string cuisine;
	int price;
	bool favorite;
	Restaurant* next;
	Restaurant* head; 

public:
	Restaurant();
	Restaurant(string name, float rating, string cuisine, int price, bool favorite, Restaurant* next);
	~Restaurant();
	void setName(string name);
	void setRating(float rating);
	void setCuisine(string cuisine);
	void setPrice(int price);
	void setFavorite(bool favorite);
	string getName()const;
	float getRating()const;
	string getCuisine()const;
	int getPrice()const;
	Restaurant* getNext()const;
	bool getFavorite()const;
	void setNext(Restaurant* next);
	void loadRestaurantsFromFile(const std::string& filename);
	void saveRestaurantsToFile() const;

		// the above are more behind the scenes
	//I'll be adding ui features - Alex
	void setInitialMenuChoice(); 
	void displayMenu();
	void searchByCuisine();
	void seeFavoriteRestaurants();
	void helpMeDecide();

	void rateRestaurant();
	void favoriteRestaurant();

};
