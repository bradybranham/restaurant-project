#include "Restaurant.h"
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

// Function to convert a string to lowercase
// Used for case-insensitive comparisons
string toLowerCase(const string& str) {
    string lowerStr;
    for (char ch : str) {
        lowerStr += tolower(ch); // Convert each character to lowercase
    }
    return lowerStr;
}

// Constructor to initialize a Restaurant object with name, cuisine, dishes, price, and rating
Restaurant::Restaurant(string name, string cuisine, string dishes, double price, double rating)
    : name(name), cuisine(cuisine), dishes(dishes), price(price), rating(rating) {
}

string Restaurant::getName() const {
    return name;
}

string Restaurant::getCuisine() const {
    return cuisine;
}

string Restaurant::getDishes() const {
    return dishes;
}

double Restaurant::getPrice() const {
    return price;
}

double Restaurant::getRating() const {
    return rating;
}

// Function to check if a restaurant matches a given query
// Compares the query with the cuisine type and dishes (case-insensitive)
bool Restaurant::matches(const string& query) const {
    string lowerQuery = toLowerCase(query); // Convert query to lowercase for comparison
    return toLowerCase(cuisine).find(lowerQuery) != string::npos || // Check if cuisine matches query
        toLowerCase(dishes).find(lowerQuery) != string::npos;    // Check if dishes match query
}

// Function to display the restaurant's details
void Restaurant::display() const {
    cout << "Name: " << name
        << "\nCuisine: " << cuisine
        << "\nDishes: " << dishes
        << "\nAverage Price: $" << price
        << "\nRating: " << rating << "\n" << endl;
}

// Function to update the restaurant's rating
// Used when a user rates the restaurant
void Restaurant::updateRating(double newRating) {
    rating = newRating; // Update the rating with the new value
}