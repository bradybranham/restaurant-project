#pragma once
#include <iostream>
#include <iomanip>
#include <string>
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
	bool setFavorite()const;
		// the above are more behind the scenes

	void rateRestaurant();

};
