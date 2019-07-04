#include "LinkedList.h"
#include "Inventory.h"
#include "Customer.h"

//default constructor below
LinkedList::LinkedList()
{
}
//overloaded consttructor that makes the Inventory object passed the head of the list 
LinkedList::LinkedList(Inventory &node) {
	this->head = &node;
}
//the destructor below traverses through the list the and deletes each node one by one 
LinkedList::~LinkedList()
{
	Inventory* currentNode = head;                //Create a temporary node to use to transverse through the linked list
	Inventory* nextNode;             //Create a temporary node to keep track of the next node
	while (currentNode != nullptr) {                //Traverse the linked list until you reach the end
		nextNode = currentNode->next;                //Set the next node
		delete currentNode;							 //Delete the current node
		currentNode = nextNode;                        //Set current node to the next node
	}
	head = nullptr; 
}
//the overloaded operator += below is able to add two inventory objects together, used for appending 
void LinkedList::operator+=(Inventory &node) {
		Inventory *current = head;                 
		Inventory *newNode = &node;           
		//checks if head is null 
		if (head == NULL)
		{
			head = newNode;
		} 
		else
		{
			while (current->next) {                        //Traverse the linked list until you reach the end
				current = current->next;
			}
			current->next = newNode; //At the end set the current to point to the new node
			current = current->next; //current points to the next node to it 
		}
}
//deleteNode deletes a specific node inside the list
void LinkedList::deleteNode(Inventory &node, int &itemNumber) {
	//set the current pointer to the head 
	Inventory *current = head;
	//set the previous pointer to nullptr for now 
	Inventory *previous = NULL; 
	//while the itemNumber does not match keep traversing 
	while (current != NULL && current->getItemNumber() != itemNumber) {
		previous = current; 
		current = current->next;  
	}
	//checks if the head needs to be deleted 
	if (current == head)
	{
		head = head->next;
		current->next = NULL;
		delete current;
		cout << "The item is deleted" << endl;
	}
	//else be able to delete any other node that is not the head 
	else
	{

		previous->next = current->next;
		current->next = NULL;
		delete current;
		cout << "The item is deleted" << endl;

	}

}

