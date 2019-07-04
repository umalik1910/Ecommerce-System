#pragma once
#include <string>
#include <iostream>
#include"LinkedList.h"
#include"Inventory.h"
#include"Customer.h"
using namespace std; 
class Admin
{
//below are the private member variables  
private:
	string name = "Admin"; 
    string password = "Admin"; 
//below are the public member variables 
public:
	Admin();
	~Admin();
	void addProd(LinkedList *Inventory); 
	void deleteNode(LinkedList *list); 
	Inventory* searchNode(LinkedList *list, int &num);
	void updateQty(LinkedList *list); 
	void updateCost(LinkedList *list); 
	bool validateAdmin(string name, string password); 
};

