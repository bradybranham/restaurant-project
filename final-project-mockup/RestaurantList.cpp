#include "RestaurantList.h"


void RestaurantList::getRestaurantsFromFile(const string& filename)
{
	ifstream file("Restaurants.txt");

	if (!file.is_open())
	{
		cerr << "Error: Could not open file!" << endl;
		return;
	}
	else
	{
		string line;
        while (getline(file, line)) 
        {
            stringstream ss(line);
            string name, cuisine, priceStr, ratingStr;
            float rating;
            int price;

            // Extract fields separated by commas
            if (getline(ss, name, ',') &&
                getline(ss, cuisine, ',') &&
                getline(ss, priceStr, ',') &&
                getline(ss, ratingStr, ',')) 
            {

                // Convert avgPriceStr and ratingStr to numeric values
                try
                {
                    price = stoi(priceStr);
                    rating = stof(ratingStr);
                }
                catch (const invalid_argument& e) 
                {
                    cerr << "Error: Invalid number format in line: " << line << endl;
                    continue;
                }

                Restaurant* newRestaurant = new Restaurant(name, rating, cuisine, price, false, nullptr);
                addRestaurant(newRestaurant);
            }
            else 
            {
                cerr << "Error: Incorrectly formatted line: " << line << endl;
            }
        }

        file.close();
	}
}


// Default constructor
RestaurantList::RestaurantList()
{
	first = nullptr;
	count = 0;
}



// Destructor
RestaurantList::~RestaurantList()
{
    Restaurant* current = first;

    while (first) 
    {
		current = first->getNext();
		delete first;
		first = current;
    }
	count = 0;
}

void RestaurantList::addRestaurant(Restaurant* newResto)
{
    if (newResto == nullptr)
    {
        cerr << "Error: Failed to allocate memory for new restaurant." << endl;
        return;
    }
    
    // Case 1: if the list of restaurant is currently empty
    if (!first)
    {
        try 
        {
            first = newResto;
            count++;
        }
        catch (const bad_alloc& e) 
        {
            cerr << "Error: Fail to allocate memory for a new restaurant" << e.what() << endl;
            delete newResto;
        }
        return;
    }

    // Traverse to the end of the list
    Restaurant* current = first;
    try 
    {
        while (current->getNext()) 
        {
            current = current->getNext();
        }
        current->setNext(newResto);
        count++;
    }
    catch (const bad_alloc& e) 
    {
        cerr << "Error: Fail to allocate memory for a new restaurant" << e.what() << endl;
        delete newResto;
    }
}

void RestaurantList::addFavorite(const string& restoName)
{
    Restaurant* current = first;

    while (current)
    {
        if (current->getName() == restoName)
        {
            current->setFavorite(true);
            cout << restoName << " has been saved to Favorite List!\n";
            return;
        }
        current = current->getNext();
    }
}

void RestaurantList::displayFavorites()
{
    Restaurant* current = first;
    
    while (current)
    {
        if (current->getFavorite())
        {
            cout << current->getName() << "  |  " << current->getCuisine() << "  |  "
                << current->getPrice() << "  |  " << current->getRating() << endl;
        }
        current = current->getNext();
    }
}

void RestaurantList::removeFavorite(const string& restoName)
{
    Restaurant* current = first;		// Create a pointer traversing thru the list
    Restaurant* previous = nullptr;	    // Point to the previous Node

    bool found = false;

    // Make sure the list is not empty
    if (count == 0)
        cout << "ERROR: Your favorite list is empty! Cannot remove\n";

    // Check if the item is in the first node
    else if (first->getName() == restoName)
    {
        current = first->getNext();
        delete first;
        first = current;
        count--;
        found = true;
    }

    else
    {
        current = first->getNext();
        previous = first;

        // While it is not the end of the list
        while (current)
        {
            // If restaurant is found
            if (current->getName() == restoName)
            {
                previous->setNext(current->getNext());
                delete current;
                count--;
                found = true;
                break;
            }
            previous = current;
            current = current->getNext();
        }
    }
    current = previous = nullptr;

    // Display message when item is not found
    if (!found)
        cout << restoName << "' is not found!\n";
}