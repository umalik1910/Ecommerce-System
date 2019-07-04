#pragma once
//below are the proper preprocessor directives
#include<string>
#include<iostream>
#include"LinkedList.h"
#include<iomanip>
#include<fstream>
using namespace std;
class Customer 
{
//below are the private member variables for customer class
private:
	string firstName = " ";
	string lastName = " "; 
	string cityAddress = "";
	string streetAddress = "";
	string stateAddress = "";
	int zipcode = 0;
	string filename = " "; 
//below are the public member variables for customer class
public: 
	LinkedList *cart = nullptr;
	Inventory* searchNode(LinkedList *list, int &num); 
	Customer();
	Customer(string first, string last, string city, string street, string state, int zip);
	void fillInInfo(string first, string last, string city, string street, string state, int zip);
	void displayShoppingCart(LinkedList *list); 
	string getFileName(); 
	void printLinkedList(LinkedList *list); 
	//below are the inline member functions of customer class
	//getFirstName returns firstName of the customer 
	string getFirstName() {
		return firstName;
	}
	//getLastName returns the lastName of the customer
	string getLastName() {
		return lastName;
	}
	//getCity returns the cityAddress of the customer 
	string getCtiy() {
		return cityAddress;
	}
	//getState returns the stateAddress of the customer 
	string getState() {
		return stateAddress;
	}
	//getZipCode returns the zipcode of the customer
	int getZipCode()
	{
		return zipcode; 
	}
	//getStreet returns the streetAddress of the customer 
	string getStreet() {
		return streetAddress; 
	}
	//below is the destructor header for Customer 
	~Customer();
};

