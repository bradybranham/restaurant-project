#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Restaurant.h"

using namespace std;

Node* restaurantList = nullptr;
Restaurant favorites[50];
int favoriteCount = 0;

void loadRestaurants(const string& filename);
void displayMenu();
void searchRestaurants();
void displayFavorites();
void rateRestaurant();
void randomCuisine();
void addRestaurantToList(Node*& head, const Restaurant& restaurant);
void deleteList(Node*& head);

int main() {
    loadRestaurants("Restaurants.txt");
    displayMenu();
    deleteList(restaurantList);
    return 0;
}

void loadRestaurants(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, cuisine, dishes;
        double price, rating;

        getline(ss, name, ',');
        getline(ss, cuisine, ',');

        if (ss.peek() == '"') {
            ss.get();
            getline(ss, dishes, '"');
            ss.get();
        }
        else {
            getline(ss, dishes, ',');
        }

        ss >> price;
        ss.ignore();
        ss >> rating;

        Restaurant restaurant(name, cuisine, dishes, price, rating);
        addRestaurantToList(restaurantList, restaurant);
    }
    file.close();
    cout << "Restaurants loaded successfully." << endl;
}

void addRestaurantToList(Node*& head, const Restaurant& restaurant) {
    Node* newNode = new Node(restaurant);
    newNode->next = head;
    head = newNode;
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void displayMenu() {
    int choice;
    do {
        cout << "\n--- Restaurant Recommendation System ---\n" << endl;
        cout << "1. Search for Restaurant" << endl;
        cout << "2. View Favorite List" << endl;
        cout << "3. Rate a Restaurant" << endl;
        cout << "4. Random Cuisine Selection" << endl;
        cout << "0. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: searchRestaurants(); break;
        case 2: displayFavorites(); break;
        case 3: rateRestaurant(); break;
        case 4: randomCuisine(); break;
        case 0: cout << "Exiting the program. Goodbye!" << endl; break;
        default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void searchRestaurants() {
    string query;
    cout << "Enter a cuisine or dish to search: ";
    cin.ignore();
    getline(cin, query);

    // Convert the query to lowercase for case-insensitive comparison
    string lowerQuery = toLowerCase(query);
    Node* current = restaurantList;
    int matchedCount = 0;
    Restaurant matchedRestaurants[100];

    // Traverse the linked list and find matches
    while (current != nullptr) {
        if (current->data.matches(lowerQuery)) {
            matchedRestaurants[matchedCount++] = current->data;
        }
        current = current->next;
    }

    if (matchedCount == 0) {
        cout << "No matching restaurants found." << endl;
        return;
    }

    char submenuChoice;
    do {
        // Display the search results
        cout << left << setw(10) << "No."
            << setw(30) << "Restaurant Name"
            << setw(20) << "Cuisine"
            << setw(40) << "Dishes"
            << setw(20) << "Average Price"
            << setw(10) << "Rating" << endl;
        cout << string(130, '-') << endl;

        for (int i = 0; i < matchedCount; i++) {
            stringstream priceStream;
            priceStream << fixed << setprecision(2) << "$" << matchedRestaurants[i].getPrice();
            string formattedPrice = priceStream.str();

            cout << left << setw(10) << (to_string(i + 1) + ".")
                << setw(30) << matchedRestaurants[i].getName()
                << setw(20) << matchedRestaurants[i].getCuisine()
                << setw(40) << matchedRestaurants[i].getDishes()
                << setw(20) << formattedPrice
                << setw(10) << fixed << setprecision(1) << matchedRestaurants[i].getRating() << endl;
        }

        // Submenu options
        cout << "\nSubmenu:\n"
            << "A - Sort by price (highest to lowest)\n"
            << "B - Sort by rating (highest to lowest)\n"
            << "C - Add a restaurant to favorite list\n"
            << "D - Rate a restaurant\n"
            << "R - Return to main menu\n"
            << "Enter your choice: ";
        cin >> submenuChoice;

        if (submenuChoice == 'A' || submenuChoice == 'a') {
            // Sort by price (highest to lowest)
            for (int i = 0; i < matchedCount - 1; i++) {
                for (int j = 0; j < matchedCount - i - 1; j++) {
                    if (matchedRestaurants[j].getPrice() < matchedRestaurants[j + 1].getPrice()) {
                        swap(matchedRestaurants[j], matchedRestaurants[j + 1]);
                    }
                }
            }
            cout << "\nSorted by Price (Highest to Lowest):\n";
        }
        else if (submenuChoice == 'B' || submenuChoice == 'b') {
            // Sort by rating (highest to lowest)
            for (int i = 0; i < matchedCount - 1; i++) {
                for (int j = 0; j < matchedCount - i - 1; j++) {
                    if (matchedRestaurants[j].getRating() < matchedRestaurants[j + 1].getRating()) {
                        swap(matchedRestaurants[j], matchedRestaurants[j + 1]);
                    }
                }
            }
            cout << "\nSorted by Rating (Highest to Lowest):\n";
        }
        else if (submenuChoice == 'C' || submenuChoice == 'c') {
            // Add a restaurant to the favorite list
            if (favoriteCount >= 50) {
                cout << "Your favorite list is full. Cannot add more restaurants." << endl;
                continue;
            }

            string restaurantName;
            cout << "Enter the name of the restaurant to add to favorites: ";
            cin.ignore();
            getline(cin, restaurantName);

            string lowerInput = toLowerCase(restaurantName);
            bool found = false;

            for (int i = 0; i < matchedCount; i++) {
                if (toLowerCase(matchedRestaurants[i].getName()) == lowerInput) {
                    // Check if the restaurant is already in favorites
                    bool alreadyInFavorites = false;
                    for (int j = 0; j < favoriteCount; j++) {
                        if (toLowerCase(favorites[j].getName()) == lowerInput) {
                            alreadyInFavorites = true;
                            break;
                        }
                    }

                    if (!alreadyInFavorites) {
                        favorites[favoriteCount++] = matchedRestaurants[i];
                        cout << "Restaurant added to your favorite list!" << endl;
                    }
                    else {
                        cout << "This restaurant is already in your favorite list." << endl;
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Restaurant not found in the search results." << endl;
            }
        }
        else if (submenuChoice == 'D' || submenuChoice == 'd') {
            string restaurantName;
            cout << "Enter the name of the restaurant you want to rate: ";
            cin.ignore();
            getline(cin, restaurantName);

            string lowerInput = toLowerCase(restaurantName);
            bool found = false;

            for (int i = 0; i < matchedCount; i++) {
                if (toLowerCase(matchedRestaurants[i].getName()) == lowerInput) {
                    double newRating;
                    cout << "Enter your rating for the restaurant (1-5 stars): ";
                    cin >> newRating;

                    if (newRating >= 1.0 && newRating <= 5.0) {
                        matchedRestaurants[i].updateRating(newRating);
                        cout << "Rating updated successfully!" << endl;

                        for (int j = 0; j < favoriteCount; j++) {
                            if (toLowerCase(favorites[j].getName()) == lowerInput) {
                                favorites[j].updateRating(newRating);
                                cout << "Rating also updated in your favorites list!" << endl;
                                break;
                            }
                        }
                    }
                    else {
                        cout << "Invalid rating. Please enter a value between 1 and 5." << endl;
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Restaurant not found in the search results." << endl;
            }
        }
        else if (submenuChoice == 'R' || submenuChoice == 'r') {
            cout << "Returning to main menu." << endl;
            return;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (submenuChoice != 'R' && submenuChoice != 'r');
}



void displayFavorites() {
    if (favoriteCount == 0) {
        cout << "Your favorite list is empty." << endl;
        return;
    }

    cout << "\n--- Favorite Restaurants ---\n";
    cout << left << setw(10) << "No."
        << setw(30) << "Restaurant Name"
        << setw(20) << "Cuisine"
        << setw(40) << "Dishes"
        << setw(20) << "Average Price"
        << setw(10) << "Rating" << endl;
    cout << string(130, '-') << endl;

    for (int i = 0; i < favoriteCount; i++) {
        stringstream priceStream;
        priceStream << fixed << setprecision(2) << "$" << favorites[i].getPrice();
        string formattedPrice = priceStream.str();

        cout << left << setw(10) << (to_string(i + 1) + ".")
            << setw(30) << favorites[i].getName()
            << setw(20) << favorites[i].getCuisine()
            << setw(40) << favorites[i].getDishes()
            << setw(20) << formattedPrice
            << setw(10) << fixed << setprecision(1) << favorites[i].getRating() << endl;
    }
}

void rateRestaurant() {
    string name;
    cout << "Enter the name of the restaurant you want to rate: ";
    cin.ignore();
    getline(cin, name);

    Node* current = restaurantList;
    bool found = false;

    while (current != nullptr) {
        if (toLowerCase(current->data.getName()) == toLowerCase(name)) {
            double rating;
            cout << "Enter your rating (1-5): ";
            cin >> rating;
            if (rating >= 1.0 && rating <= 5.0) {
                current->data.updateRating(rating);
                cout << "Rating updated successfully!" << endl;

                // Update the rating in the favorites array if the restaurant is in favorites
                for (int i = 0; i < favoriteCount; i++) {
                    if (toLowerCase(favorites[i].getName()) == toLowerCase(name)) {
                        favorites[i].updateRating(rating);
                        break;
                    }
                }
            }
            else {
                cout << "Invalid rating. Please enter a value between 1 and 5." << endl;
            }
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Restaurant not found." << endl;
    }
}

void randomCuisine() {
    if (restaurantList == nullptr) {
        cout << "No restaurants available." << endl;
        return;
    }

    srand(42); // Fixed seed for consistent results
    int count = 0;
    Node* current = restaurantList;

    // Count the total number of restaurants
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Create arrays to track unique cuisines and whether they've been suggested
    string cuisines[100];
    bool suggested[100] = { false };
    int cuisineCount = 0;
    string userResponse;

    // Populate the cuisine array with unique cuisine names
    current = restaurantList;
    while (current != nullptr) {
        string cuisine = current->data.getCuisine();
        bool isUnique = true;

        // Check if this cuisine is already in the array
        for (int i = 0; i < cuisineCount; i++) {
            if (toLowerCase(cuisines[i]) == toLowerCase(cuisine)) {
                isUnique = false;
                break;
            }
        }

        // If the cuisine is unique, add it to the array
        if (isUnique) {
            cuisines[cuisineCount++] = cuisine;
        }

        current = current->next;
    }

    do {
        // If all cuisines have been suggested, exit the loop
        if (cuisineCount == 0) {
            cout << "No more cuisines to suggest. Returning to main menu." << endl;
            return;
        }

        // Randomly select an unseen cuisine
        int randomIndex;
        do {
            randomIndex = rand() % cuisineCount;
        } while (suggested[randomIndex]);

        string selectedCuisine = cuisines[randomIndex];
        suggested[randomIndex] = true; // Mark this cuisine as suggested

        // Ask the user if they want to try this cuisine
        cout << "\nHow about trying some " << selectedCuisine << " cuisine? (yes/no): ";
        cin >> userResponse;

        if (toLowerCase(userResponse) == "no") {
            cout << "Let's try another suggestion!" << endl;
        }
        else if (toLowerCase(userResponse) == "yes") {
            // Display header
            cout << "\n--- Restaurants Offering " << selectedCuisine << " Cuisine ---\n";
            cout << left << setw(10) << "No."
                << setw(30) << "Restaurant's Name"
                << setw(20) << "Cuisine"
                << setw(40) << "Dishes"
                << setw(20) << "Average Price"
                << setw(10) << "Rating" << endl;
            cout << string(130, '-') << endl;

            // Display all restaurants with the selected cuisine type
            int restaurantCount = 0;
            current = restaurantList;
            while (current != nullptr) {
                if (toLowerCase(current->data.getCuisine()) == toLowerCase(selectedCuisine)) {
                    restaurantCount++;
                    stringstream priceStream;
                    priceStream << fixed << setprecision(2) << "$" << current->data.getPrice();
                    string formattedPrice = priceStream.str();

                    cout << left << setw(10) << (to_string(restaurantCount) + ".")
                        << setw(30) << current->data.getName()
                        << setw(20) << current->data.getCuisine()
                        << setw(40) << current->data.getDishes()
                        << setw(20) << formattedPrice
                        << setw(10) << fixed << setprecision(1) << current->data.getRating() << endl;
                }
                current = current->next;
            }

            if (restaurantCount == 0) {
                cout << "No restaurants found offering " << selectedCuisine << " cuisine." << endl;
            }
            return;
        }
        else {
            cout << "Invalid response. Please enter 'yes' or 'no'." << endl;
        }

    } while (toLowerCase(userResponse) != "yes");

    cout << "Returning to main menu." << endl;
}