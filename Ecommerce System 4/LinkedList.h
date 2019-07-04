#pragma once
#include"Inventory.h"
class LinkedList
{
//private member variables below
private:
	Inventory *head = nullptr;
//public member variables below  
public:
	LinkedList();
	LinkedList(Inventory &head); 
	~LinkedList();
	//defintion of inline function called getHead, which returns the head of the list 
	Inventory* getHead() {
		return head;
	}
	void operator+=(Inventory &node);
	void deleteNode(Inventory &node, int &itemNumber);
};

