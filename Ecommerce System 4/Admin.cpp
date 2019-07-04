#include "Admin.h"
//here is the default constructor 
Admin::Admin()
{
	name; 
	password; 
}
//destructor is below 
Admin::~Admin()
{
}
//addProd adds a node to the inventory 
void Admin::addProd(LinkedList *inv) {
	int input = 0;
	cout << "What is the item number of the product you would like to add to the inventory linked list?" << endl; 
	cin >> input; 
	//validates the input 
	while (input < 0) {
		cout << "Input for item number cannot be negative. Please reneter a valid value" << endl; 
		cin >> input; 
	}
	//then procceds to add the node if valid item number given before 
	Inventory* temp = searchNode(inv, input);
	if (temp != nullptr) {
		cout << "Since this item number already exists inside the inventory. You will be updating the quantity instead of directly adding a product. Please enter a quantity value" << endl;
		cin >> input;
		while (input <= 0) {
			cout << "Input for quantity cannot be less than or equal to zero. Please reenter a valid input" << endl;
			cin >> input;
		}
		int qty = temp->getQty(); 
		temp->setQty(qty + input); 
	}
	if (temp == nullptr) {
		Inventory *node = new Inventory();
		node->setItemNumber(input);
		cout << "What is the name of the product you would like to add?" << endl;
		string stringInput = " ";
		cin >> stringInput;
		node->setName(stringInput);
		cout << "What is the cost of the product you would like to add?" << endl;
		double input2 = 0;
		cin >> input2;
		while (input2 < 0) {
			cout << "Cost cannot be negative" << endl; 
			cin >> input2; 
		}
		node->setCost(input2);
		cout << "What is the quantity of the product you woud like to add?" << endl;
		cin >> input;
		while (input <= 0) {
			cout << "Input for quantity cannot be less than or equal to zero. Please reenter a valid input" << endl;
			cin >> input;
		}
		node->setQty(input);
		*inv += *node;
		cout << "Item has been added to the inventory successfully" << endl;
	}
}
//deleteNode deletes a specific item from item from the inventory list
void Admin::deleteNode(LinkedList *list) {
	//outputs a message and takes in input
	int input = 0;
	cout << "What item would you like to delete from inventory? Enter in the item number of the item" << endl;
	cin >> input; 
	//calls searchNode to return the address of the searched node 
	Inventory *obj = searchNode(list, input); 
	//if it the address is nullptr, then output an error message
	if (obj == nullptr) {
		cout << "Sorry, the item you are trying to search for to delete does not exist inside the Inventory" << endl; 
	}
	//else proceed to delete the node 
	else {
		list->deleteNode(*obj, input); 
	}

 }

//searchNode returns the address of the node if it is found 
Inventory* Admin::searchNode(LinkedList *list, int &num) {
	Inventory* current = list->getHead();
	bool found = false;
	//as long as the end is not reached of the linked list, keep traversing
	while (current != NULL)
	{
		//if the item number matches with an exisitng node, then return it 
		if ((current)->getItemNumber() == num)
		{ 
			found = true;
			return current;
		}
		//otherwise go to the next node to traverse
		current = current->next;
	}
	if (!found)
	{
		//if not found. return nullptr 
		return nullptr;
	}
}
//updateQty updates a quantity for a node inside the inventory list 
void Admin::updateQty(LinkedList *list) {
	//outputs a message and takes in input
	int input = 0; 
	cout << "What is the item number of the product inside the inventory whose quantity you would like to update?" << endl;
	cin >> input; 
	//calls searchNode to return the address of the searched node 
	Inventory *obj = searchNode(list, input); 
	//if address is null, then output an error message
	if (obj == nullptr) {
		cout << "Sorry, the item you tried to change quantity of does not exist inside the Inventory" << endl; 
	}
	//else proceed to change the quantity
	else {
		int quantity = 0; 
		cout << "What would you like the new quantity of the product to be now?" << endl; 
		cin >> quantity; 
		while (quantity < 0) {
			cout << "Quantity cannot be negative. Please reenter a valid value" << endl; 
			cin >> quantity; 
		}
		obj->setQty(quantity);
		cout << "The quantity has been changed" << endl; 
	}
}
//updateCost updates a cost of a node inside the inventory linked list 
void Admin::updateCost(LinkedList *list) {
	//outputs a message to admin and takes in the input 
	int input = 0;
	cout << "What is the item number of the product inside the inventory whose cost you would like to update?" << endl;
	cin >> input;
	//call the searchNode and returns the address into obj pointer 
	Inventory *obj = searchNode(list, input);
	//if the address is nullptr, it means that the node does not exist inside the inventory linked list 
	if (obj == nullptr) {
		cout << "Sorry, the item you tried to change cost of does not exist inside the Inventory" << endl;
	}
	//else proceed to update the cost of that specific item inside the inventory node 
	else {
		double cost = 0;
		cout << "What would you like the new cost of the product to be now?" << endl;
		cin >> cost;
		while (cost < 0) {
			cout << "Cost cannot be negative. Please reenter a valid value" << endl; 
			cin >> cost; 
		}
		obj->setCost(cost);
		cout << "The cost has been changed" << endl;
	}
}
//validateAdmin validates the username and password of the admin
bool Admin::validateAdmin(string name, string password) {
	//converts each character to lower case to test lowercase versions of input just in case
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]); 
	}
	for (int i = 0; i < password.length(); i++) {
		password[i] = tolower(password[i]);
	}
	//checks if user name and password matches 
	if (name == "admin" && password == "admin")
	{
		return true; 
	}
	//return false if there are invalid inputs 
	else
	{
		return false; 
	}
}