#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>

// Function to convert a string to lowercase
// Used for case-insensitive comparisons
std::string toLowerCase(const std::string& str);

class Restaurant {
private:
    std::string name;
    std::string cuisine;
    std::string dishes;
    double price;
    double rating;

public:
    // Default constructor initializing price and rating to 0.0
    Restaurant() : price(0.0), rating(0.0) {}

    // Constructor w/ parameters to initialize all attributes
    Restaurant(std::string name, std::string cuisine, std::string dishes, double price, double rating);

    std::string getName() const;

    std::string getCuisine() const;

    std::string getDishes() const;

    double getPrice() const;

    double getRating() const;

    // Function to check if a restaurant matches a given query
    // Compares the query to the cuisine type and dishes (case-insensitive)
    bool matches(const std::string& query) const;

    // Function to display the restaurant's details
    void display() const;

    // Function to update the restaurant's rating
    void updateRating(double newRating);
};

// Structure representing a Node in a linked list
// Each Node contains a Restaurant object and a pointer to the next Node
struct Node {
    Restaurant data; // Restaurant data stored in the Node
    Node* next;      // Pointer to the next Node in the list

    // Constructor to initialize the Node with a Restaurant object
    Node(Restaurant restaurant) : data(restaurant), next(nullptr) {}
};

#endif