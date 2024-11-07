#include "Restaurant.h"

Restaurant::Restaurant()
{
	name = "NULL";
	rating = 0.0;
	cuisine = "NULL";
	price = 0;
	favorite = false;
	next = nullptr;
}

Restaurant::Restaurant(string name, float rating, string cuisine, int price, bool favorite, Restaurant* next)
{
	this->name = name;
	this->rating = rating;
	this->cuisine = cuisine;
	this->price = price;
	this->favorite = favorite;
	this->next = next;
}

Restaurant::~Restaurant()
{}

void Restaurant::setName(string name)
{
	this->name = name;
}

void Restaurant::setRating(float rating)
{
	this->rating = rating;
}

void Restaurant::setCuisine(string cuisine)
{
	this->cuisine = cuisine;
}

void Restaurant::setPrice(int price)
{
	this->price = price;
}

void Restaurant::setFavorite(bool favorite)
{
	this->favorite = favorite;
}

string Restaurant::getName()const
{
	return name;
}

float Restaurant::getRating()const
{
	return rating;
}

string Restaurant::getCuisine()const
{
	return cuisine;
}

int Restaurant::getPrice()const
{
	return price;
}

bool Restaurant::setFavorite()const
{
	return favorite;
}

// the above are more behind the scenes

void Restaurant::rateRestaurant()
{
	cout << "You are rating: " << name << endl;
	cout << "Rating: "
}
