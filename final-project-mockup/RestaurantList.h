#pragma once

#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


class RestaurantList
{
private:
	Restaurant* first;
	int count;
    void getRestaurantsFromFile(const string& filename);


public:
    RestaurantList();
    ~RestaurantList();

    void addRestaurant(Restaurant* restaurant);
    void searchRestaurant(const string& cuisine);
    void displayAllRestaurants();
    void displayFavorites();
    void addFavorite(const string& name);
    void removeFavorite(const string& name);

};

