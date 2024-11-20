#include "functions.h"
#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Function to load restaurants from a file and store them in a linked list
void loadRestaurants(const string& filename, Node*& restaurantList) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, cuisine, dishes;
        double price, rating;

        // Parse the restaurant's data from the line
        getline(ss, name, ',');
        getline(ss, cuisine, ',');

        if (ss.peek() == '"') { // Handle quoted dishes (e.g., "dish1, dish2")
            ss.get();
            getline(ss, dishes, '"');
            ss.get();
        }
        else {
            getline(ss, dishes, ',');
        }

        ss >> price;
        ss.ignore(); // Ignore the comma
        ss >> rating;

        // Create a Restaurant object and add it to the list
        Restaurant restaurant(name, cuisine, dishes, price, rating);
        addRestaurantToList(restaurantList, restaurant);
    }
    file.close();
    cout << "Restaurants loaded successfully." << endl;
}

// Add a Restaurant object to the beginning of a linked list
void addRestaurantToList(Node*& head, const Restaurant& restaurant) {
    Node* newNode = new Node(restaurant);
    newNode->next = head; // Point the new node to the current head
    head = newNode;       // Update the head to the new node
}

// Delete the entire linked list to free memory
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp; // Free the memory of each node
    }
}

// Function to search for restaurants based on a user query
void searchRestaurants(Node*& restaurantList, stack<string>& searchHistory,
    vector<string>& allSearches, Restaurant favorites[], int& favoriteCount) {
    string query;
    cout << "Enter a cuisine or dish to search: ";
    cin.ignore();
    getline(cin, query);
    cout << endl;

    if (!query.empty()) {
        // Add the query to search history and full history for backtracking
        searchHistory.push(query);
        allSearches.push_back(query);
    }
    else {
        cout << "Search query cannot be empty. Please try again." << endl;
        return;
    }

    // Convert the query to lowercase for case-insensitive comparison
    string lowerQuery = toLowerCase(query);
    Node* current = restaurantList;
    int matchedCount = 0;
    Restaurant matchedRestaurants[100];

    // Traverse the list and collect matches
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
        // Display the matched restaurants
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

        // Provide options for sorting, adding to favorites, or rating
        cout << "\nSubmenu:\n\n"
            << "A - Sort by price (highest to lowest)\n"
            << "B - Sort by rating (highest to lowest)\n"
            << "C - Add a restaurant to favorite list\n"
            << "D - Rate a restaurant\n"
            << "R - Return to main menu\n\n"
            << "Enter your choice: ";
        cin >> submenuChoice;

        if (submenuChoice == 'A' || submenuChoice == 'a') {
            // Sort matched restaurants by price (descending)
            auto comparePrice = [](const Restaurant& a, const Restaurant& b) {
                return a.getPrice() < b.getPrice();
                };
            std::priority_queue<Restaurant, vector<Restaurant>, decltype(comparePrice)> priceQueue(comparePrice);

            for (int i = 0; i < matchedCount; i++) {
                priceQueue.push(matchedRestaurants[i]);
            }

            for (int i = 0; i < matchedCount; i++) {
                matchedRestaurants[i] = priceQueue.top();
                priceQueue.pop();
            }

            cout << "\nSorted by Price (Highest to Lowest):\n\n";
        }

        else if (submenuChoice == 'B' || submenuChoice == 'b') {
            // Sort matched restaurants by rating (descending)
            auto compareRating = [](const Restaurant& a, const Restaurant& b) {
                return a.getRating() < b.getRating();
                };
            std::priority_queue<Restaurant, vector<Restaurant>, decltype(compareRating)> ratingQueue(compareRating);

            for (int i = 0; i < matchedCount; i++) {
                ratingQueue.push(matchedRestaurants[i]);
            }

            for (int i = 0; i < matchedCount; i++) {
                matchedRestaurants[i] = ratingQueue.top();
                ratingQueue.pop();
            }

            cout << "\nSorted by Rating (Highest to Lowest):\n\n";
        }

        else if (submenuChoice == 'C' || submenuChoice == 'c') {
            // Add a restaurant to the favorites list
            if (favoriteCount >= 50) {
                cout << "Your favorite list is full. Cannot add more restaurants." << endl;
                continue;
            }

            string restaurantName;
            cout << "\nEnter the name of the restaurant to add to favorites: ";
            cin.ignore();
            getline(cin, restaurantName);

            string lowerInput = toLowerCase(restaurantName);
            bool found = false;

            for (int i = 0; i < matchedCount; i++) {
                if (toLowerCase(matchedRestaurants[i].getName()) == lowerInput) {
                    // Check if the restaurant is already in the favorites list
                    bool alreadyInFavorites = false;
                    for (int j = 0; j < favoriteCount; j++) {
                        if (toLowerCase(favorites[j].getName()) == lowerInput) {
                            alreadyInFavorites = true;
                            break;
                        }
                    }

                    if (!alreadyInFavorites) {
                        favorites[favoriteCount++] = matchedRestaurants[i];
                        cout << "\nRestaurant added to your favorite list!\n" << endl;
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

        else if (submenuChoice == 'R' || submenuChoice == 'r') {
            // Exit submenu
            cout << "\nReturning to main menu." << endl;
            return;
        }

        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (submenuChoice != 'R' && submenuChoice != 'r');
}

// Function to display the user's favorite restaurants
void displayFavorites(Restaurant favorites[], int favoriteCount) {
    if (favoriteCount == 0) { // Check if the favorites list is empty
        cout << "Your favorite list is empty." << endl;
        return;
    }

    // Display header for the table
    cout << "\n--- Favorite Restaurants ---\n";
    cout << left << setw(10) << "No."
        << setw(30) << "Restaurant Name"
        << setw(20) << "Cuisine"
        << setw(40) << "Dishes"
        << setw(20) << "Average Price"
        << setw(10) << "Rating" << endl;
    cout << string(130, '-') << endl;

    // Loop through the favorites array and display each restaurant
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

// Function to allow the user to rate a restaurant
void rateRestaurant(Node*& restaurantList, Restaurant favorites[], int& favoriteCount) {
    string name;
    cout << "Enter the name of the restaurant you want to rate: ";
    cin.ignore();
    getline(cin, name);

    Node* current = restaurantList;
    bool found = false;

    // Traverse the linked list to find the restaurant
    while (current != nullptr) {
        if (toLowerCase(current->data.getName()) == toLowerCase(name)) {
            double rating;
            cout << "\nEnter your rating (1-5): ";
            cin >> rating;

            if (rating >= 1.0 && rating <= 5.0) {
                // Update the rating in the restaurant list
                current->data.updateRating(rating);
                cout << "\nRating updated successfully!" << endl;

                // Also update the rating in the favorites list if applicable
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

// Function to suggest a random cuisine to the user
void randomCuisine(Node*& restaurantList) {
    if (restaurantList == nullptr) { // Check if the list is empty
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

    // Create arrays to store unique cuisines and track suggestions
    string cuisines[100];
    bool suggested[100] = { false };
    int cuisineCount = 0;
    string userResponse;

    // Populate the cuisine array with unique cuisine types
    current = restaurantList;
    while (current != nullptr) {
        string cuisine = current->data.getCuisine();
        bool isUnique = true;

        for (int i = 0; i < cuisineCount; i++) {
            if (toLowerCase(cuisines[i]) == toLowerCase(cuisine)) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            cuisines[cuisineCount++] = cuisine;
        }
        current = current->next;
    }

    do {
        if (cuisineCount == 0) { // Check if all cuisines have been suggested
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

        // Ask the user if they want to try the cuisine
        cout << "How about trying some " << selectedCuisine << " cuisine? (yes/no): ";
        cin >> userResponse;

        if (toLowerCase(userResponse) == "no") {
            cout << "\nLet's try another suggestion!\n" << endl;
        }
        else if (toLowerCase(userResponse) == "yes") {
            // Display restaurants offering the selected cuisine
            cout << "\n--- Restaurants Offering " << selectedCuisine << " Cuisine ---\n\n";
            cout << left << setw(10) << "No."
                << setw(30) << "Restaurant's Name"
                << setw(20) << "Cuisine"
                << setw(40) << "Dishes"
                << setw(20) << "Average Price"
                << setw(10) << "Rating" << endl;
            cout << string(130, '-') << endl;

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

// Function to allow the user to revisit previous searches
void backtrackSearch(std::stack<std::string>& searchHistory, Node*& restaurantList,
    Restaurant favorites[], int& favoriteCount, std::vector<std::string>& allSearches) {
    if (allSearches.empty()) { // Check if there are no previous searches
        cout << "No previous searches to display." << endl;
        return;
    }

    // Display all previous searches
    cout << "--- All Previous Searches ---\n\n";
    for (size_t i = 0; i < allSearches.size(); ++i) {
        cout << (i + 1) << ". " << allSearches[i] << endl;
    }

    // Prompt the user to select a search to revisit
    int choice;
    cout << "\nEnter the number of the search you want to revisit (0 to return to main menu): ";
    cin >> choice;

    if (choice == 0) { // Exit backtracking
        cout << "Returning to main menu." << endl;
        return;
    }

    if (choice < 1 || choice > allSearches.size()) {
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    // Retrieve and revisit the selected query
    string selectedQuery = allSearches[choice - 1];
    cout << "\nRevisiting search: \"" << selectedQuery << "\"\n\n";

    string lowerQuery = toLowerCase(selectedQuery);
    Node* current = restaurantList;
    int matchedCount = 0;
    Restaurant matchedRestaurants[100];

    while (current != nullptr) {
        if (current->data.matches(lowerQuery)) {
            matchedRestaurants[matchedCount++] = current->data;
        }
        current = current->next;
    }

    if (matchedCount == 0) {
        cout << "No matching restaurants found for \"" << selectedQuery << "\"." << endl;
    }
    else {
        // Display matched restaurants for the revisited query
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
    }
}