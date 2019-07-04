#include "Customer.h"
#include <string.h>
//below is the defintion of the default cosntructor 
Customer::Customer()
{
	cart = new LinkedList(); 
}
//below is the overloaded constructor defintion of the Customer type object 
Customer::Customer(string first, string last, string city, string street, string state, int zip)
{
	cart = new LinkedList();
	firstName = first; 
	lastName = last; 
	cityAddress = city; 
	streetAddress = street; 
	stateAddress = state; 
	zipcode = zip; 
}
//fillInInfo function below takes in the information of the customer and stores thhe info. in the respective member variables 
void Customer::fillInInfo(string first, string last, string city, string street, string state, int zip) {
		//string first = " ";
		cout << "What is your first name?" << endl;
		cin >> first;
		//string last = " ";
		cout << "What is your last name?" << endl;
		cin >> last;
		cout << "Please enter in the street of your address" << endl;
		//string street = " ";
		cin.ignore(100, '\n');
		getline(cin, street);
		cout << "What city are you from?" << endl;
		//string city = " ";
		cin >> city;
		cout << "What state are you from? Please enter the state abbreviation" << endl;
		//string state = " ";
		cin >> state;
		cout << "What is your zipcode" << endl;
		//int zip = 0;
		cin >> zip;
		firstName = first; 
		lastName = last; 
		streetAddress = street; 
		cityAddress = city; 
		stateAddress = state; 
		zipcode = zip; 
}
//below is the destructor 
Customer::~Customer()
{
	delete cart; 
	//cart = nullptr; 
}

//below is the definition of searchNode that returns the pointer the Invetory node if it finds that object 
Inventory* Customer:: searchNode(LinkedList *list, int &num) {
	//set a pointer to a dynamically created Inventory object with the list's head
	Inventory* current = list->getHead();
	bool found = false; 
	//as long as the end is not reached of the linked list, keep traversing
		while (current != NULL)
		{
			//if the item number matches with an exisitng node, then return it 
			if ((current)->getItemNumber() == num)
			{
				//set found to true 
				 found = true; 
				 return current;
			}
			//otherwise go to the next node to traverse
			current = current->next;
		}
		//if found is false, return nullptr
		if (!found)
		{
			return nullptr;
		}
}
//displayShoppingCart function below displays the contents of the shopping cart 
void Customer::displayShoppingCart(LinkedList *list) {
	//set a node pointer called current to point at where head is at
	Inventory *node  = list->getHead();
	// double type local variable called total is set to 0. 
	double total = 0;
	//output message given  below with correct formatting 
	cout << "Item Number		Item Name		Qty		Unit Cost		Total" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	//while end of the list not reached, keep outputting the contents of the list and keep track of total, which is outputted at the end as well
	while (node != NULL) {
		cout << setw(24) << left << node->getItemNumber() << setw(24) << "Product " + node->getName() << setw(16) << node->getQty() << setw(24) << node->getCost() << setprecision(2) << fixed << (node->getCost() * node->getQty());
		cout << endl;
		total += (node->getCost() * node->getQty());
		node = node->next; //Set the current node to the next node
	}
	cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(90) << setprecision(2) << fixed << right << "Total: $" << total << endl;
}
//getFileName attaches the lastname of the customer to "_Invoice.txt" and returns the filename
string Customer::getFileName() {
	filename = lastName;
	filename += "_Invoice.txt";
	return filename; 
}
//printLinkedList is used to print the LinkedList contents 
void Customer::printLinkedList(LinkedList *list) {
		Inventory *current = list->getHead(); //set a node pointer called current to point at where head is at
		// double type local variable called total is set to 0. 
		double total = 0;
		cout << "Customer Name: " << firstName << " " << lastName << endl;
		cout << "Customer Address: " << streetAddress << endl << setw(26) << cityAddress << "," << stateAddress << " " << zipcode << endl;
		//output message given  below with correct formatting 
		cout << "Item Number		Item Name		Qty		Unit Cost		Total" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		//while end of the list not reached, keep outputting the contents of the list and keep track of total, which is outputted at the end as well
		while (current != NULL) {
			cout << setw(24) << left << current->getItemNumber() << setw(24) << "Product " + current->getName() << setw(16) << current->getQty() << setw(24) << current->getCost() << setprecision(2) << fixed << (current->getCost() * current->getQty());
			cout << endl;
			total += (current->getCost() * current->getQty());
			current = current->next; //Set the current node to the next node
		}
		cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(90) << setprecision(2) << fixed << right << "Total: $" << total << endl;
	}
