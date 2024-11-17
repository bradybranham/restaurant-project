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
	// the above are more behind the scenes
	
	void saveRestaurantsToFile() const;
	void setInitialMenuChoice(); 
	//I'll be adding ui features - Alex
	//commenting out to not conflate the work Gemma did - Alex
	//void displayMenu();
	//void searchByCuisine();
	//void seeFavoriteRestaurants();
	//void helpMeDecide();
	//void loadRestaurantsFromFile(const std::string& filename);

	void rateRestaurant();
	void favoriteRestaurant();

};
