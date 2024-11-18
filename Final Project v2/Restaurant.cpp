#include "Restaurant.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

string toLowerCase(const string& str) {
    string lowerStr;
    for (char ch : str) {
        lowerStr += tolower(ch);
    }
    return lowerStr;
}

Restaurant::Restaurant(string name, string cuisine, string dishes, double price, double rating)
    : name(name), cuisine(cuisine), dishes(dishes), price(price), rating(rating) {
}

string Restaurant::getName() const { return name; }
string Restaurant::getCuisine() const { return cuisine; }
string Restaurant::getDishes() const { return dishes; }
double Restaurant::getPrice() const { return price; }
double Restaurant::getRating() const { return rating; }

bool Restaurant::matches(const string& query) const {
    string lowerQuery = toLowerCase(query);
    return toLowerCase(cuisine).find(lowerQuery) != string::npos ||
        toLowerCase(dishes).find(lowerQuery) != string::npos;
}

void Restaurant::display() const {
    cout << "Name: " << name << "\nCuisine: " << cuisine
        << "\nDishes: " << dishes << "\nAverage Price: $" << price
        << "\nRating: " << rating << "\n" << endl;
}

void Restaurant::updateRating(double newRating) {
    rating = newRating;
}