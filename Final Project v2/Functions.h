#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Restaurant.h"
#include <stack>
#include <vector>
#include <string>

// Function declarations
void loadRestaurants(const std::string& filename, Node*& restaurantList);
void addRestaurantToList(Node*& head, const Restaurant& restaurant);
void deleteList(Node*& head);

void searchRestaurants(Node*& restaurantList, std::stack<std::string>& searchHistory,
    std::vector<std::string>& allSearches, Restaurant favorites[], int& favoriteCount);

void displayFavorites(Restaurant favorites[], int favoriteCount);
void rateRestaurant(Node*& restaurantList, Restaurant favorites[], int& favoriteCount);
void randomCuisine(Node*& restaurantList);
void backtrackSearch(std::stack<std::string>& searchHistory, Node*& restaurantList,
    Restaurant favorites[], int& favoriteCount, std::vector<std::string>& allSearches);

#endif