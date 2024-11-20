#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
#include "Restaurant.h"
#include "functions.h"

using namespace std;

// Function to display the main menu and handle user choices
void displayMenu(Node*& restaurantList, Restaurant favorites[], int& favoriteCount,
    stack<string>& searchHistory, vector<string>& allSearches) {
    int choice;
    do {
        // Display menu options
        cout << "\n--- Restaurant Recommendation System ---\n" << endl;
        cout << "1. Search for Restaurants" << endl;
        cout << "2. View Favorite List" << endl;
        cout << "3. Rate a Restaurant" << endl;
        cout << "4. Random Cuisine Generator" << endl;
        cout << "5. Previous Searches" << endl;
        cout << "0. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        // Handle user input for menu options
        switch (choice) {
        case 1:
            searchRestaurants(restaurantList, searchHistory, allSearches, favorites, favoriteCount); // Search functionality
            break;
        case 2:
            displayFavorites(favorites, favoriteCount); // Display the list of favorite restaurants
            break;
        case 3:
            rateRestaurant(restaurantList, favorites, favoriteCount); // Allow the user to rate a restaurant
            break;
        case 4:
            randomCuisine(restaurantList); // Suggest a random cuisine
            break;
        case 5:
            backtrackSearch(searchHistory, restaurantList, favorites, favoriteCount, allSearches); // View previous searches
            break;
        case 0:
            cout << "Exiting the program. Goodbye!" << endl; // Exit the program
            break;
        default:
            cout << "Invalid choice. Please try again." << endl; // Handle invalid input
        }
    } while (choice != 0); // Continue displaying the menu until the user exits
}

int main() {
    // Initialize data structures
    Node* restaurantList = nullptr;                // Linked list to store the list of restaurants
    Restaurant favorites[50];                      // Array to store the user's favorite restaurants
    int favoriteCount = 0;                         // Counter to track the number of favorite restaurants
    stack<string> searchHistory;                   // Stack to store the history of search queries
    vector<string> allSearches;                    // Vector to store all search queries for backtracking


    loadRestaurants("Restaurants.txt", restaurantList);
    displayMenu(restaurantList, favorites, favoriteCount, searchHistory, allSearches);
    deleteList(restaurantList);

    return 0;
}