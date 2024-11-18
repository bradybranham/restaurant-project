#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>

std::string toLowerCase(const std::string& str);

class Restaurant {
private:
    std::string name;
    std::string cuisine;
    std::string dishes;
    double price;
    double rating;

public:
    Restaurant() : price(0.0), rating(0.0) {}
    Restaurant(std::string name, std::string cuisine, std::string dishes, double price, double rating);

    std::string getName() const;
    std::string getCuisine() const;
    std::string getDishes() const;
    double getPrice() const;
    double getRating() const;

    bool matches(const std::string& query) const;
    void display() const;
    void updateRating(double newRating);
};

// Node structure for the linked list
struct Node {
    Restaurant data;
    Node* next;
    Node(Restaurant restaurant) : data(restaurant), next(nullptr) {}
};

#endif