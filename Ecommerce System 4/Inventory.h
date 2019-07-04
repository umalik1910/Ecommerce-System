#pragma once
//below are the preprocesser directives 
#include<iostream>
#include<string>
#include <fstream>
using namespace std; 
class Inventory
{
//below are the protected member variables 
protected:
	int itemNumber = 0;
	string name = " ";
	double cost = 0;
	int qty = 0;
//below are the public member variables 
public:
	//pointer to an Inventory type is set to nullptr 
	Inventory *next = nullptr;
	//constructor header
	Inventory();
	Inventory(int itemNum, string Name, double Cost, int quantity); 
	//below are the accessors and mutator functions for each the appropriate member variable of the class 
	int getItemNumber() {
		return itemNumber; 
	}
	string getName() {
		return name; 
	}
	double getCost() {
		return cost;
	}
	int getQty() {
		return qty; 
	}
	void setItemNumber (int num)  {
		itemNumber = num; 
	}
	void setName(string itemName) {
		name = itemName;
	}
	void setCost(double cos) {
		cost = cos;
	}
	void setQty(int quantity) {
		qty = quantity;
	}
	//destructor header
	~Inventory();
};

