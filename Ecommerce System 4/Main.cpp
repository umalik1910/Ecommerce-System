/*
 * Author: Utsav Malik
 * NetID: uxm170000
 * Due Date: May 5, 2019
 *
 * Course: CS-1337
 * Section: 012
 * Name: Project 4
 *
 *
 */
 //below are the preprocessor directives
#include <iostream>
#include <string>
#include<fstream>
#include <cstdlib>
#include "LinkedList.h"
#include"Customer.h"
#include"Admin.h"
using namespace std;
//function prototypes below 
void inFile(fstream &file, int &itemName, LinkedList *list, Inventory *head);
bool askCustomerOption(string &input, Customer *user, LinkedList *list, int &itemNumber);
void askQuantity(int quantity, Inventory *temp, LinkedList *list, Customer *user, int &itemNumber);
void displayMenu();
void printInvoice(Customer *user, fstream &outputFile); 
void updateFile(fstream &file, LinkedList *list);
//below is the main function that calls other class objects and functions to run the program 
int main() {
	//initilaize bool stop to false
	bool stop = false;
	//set an int itemNumber to 0
	int itemNumber = 0;
	//set string input to empty string to avoid garbage values
	string input = " ";
	//set int name to 0 
	int name = 0;
	//Call the defualt constructor to make a Admin type object called admin
	Admin admin;
	//a fstream file type object is declared called file
	fstream file;
	//a string variable called fileName is declared to hold the name of input file. 
	string fileName = "ProductData.csv";
	//attempt to open the file in input mod only
	file.open(fileName, ios::in);
	//Call the default constrcutor of Inventory to make a pointer that points to a dynamically created Inventory object called head
	Inventory *head = new Inventory();
	//Call the overloaded constructor of LinkedList with head passed in to make a pointer that points to a dynamically created Linked List object
	LinkedList *list = new LinkedList(*head);
	//Create a pointer to a Customer object set to nullptr 
	Customer *customer = nullptr;
	//set strring input2 to an empty string 
	string input2 = " ";
	//cal inFile function read in the csv file and create the inventory linked list
	inFile(file, name, list, head);
	//set string input3 to empty string 
	string input3 = " ";
	//set bool done to false
	bool done = false;
	//while done is true keep loop going on
	while (!done)
	{
		//call to displayMenu function
		displayMenu();
		//take innput from user
		cin >> input2;

		//while input does not match any of the valid options 
		while (input2 != "1" && input2 != "A" && input2 != "Admin" && input2 != "admin" && input2 != "2" && input2 != "C" && input2 != "Customer" && input2 != "customer" && input2 != "3" && input2 != "E" && input2 != "Exit" && input2 != "exit")
		{
			//output error message 
			cout << "Please enter a valid input" << endl;
			//call displayMenu function 
			displayMenu();
			//take input again 
			cin >> input2;
		}
		//if user's input matches to any of the Admin's options, then proceed. 
		if (input2 == "1" || input2 == "A" || input2 == "Admin" || input2 == "admin")
		{
			//ask for user name and take in input (username is: Admin or admin")
			cout << "What is the username?" << endl;
			cin >> input2;
			//ask for password and take in input (password is: Admin or admin")
			cout << "What is the password?" << endl;
			cin >> input3;
			//call validateAdmin on admin object and check if the username or password is incorrect
			if (!admin.validateAdmin(input2, input3))
			{
				//error message given
				cout << "Incorrect inputs, access not given!" << endl;
				//menu is displayed again with function call
				displayMenu();
				//take in input 
				cin >> input2;
				//validate if input is for a valid choice
				while (input2 != "1" && input2 != "A" && input2 != "Admin" && input2 != "admin" && input2 != "2" && input2 != "C" && input2 != "Customer" && input2 != "customer" && input2 != "3" && input2 != "E" && input2 != "Exit" && input2 != "exit")
				{
					cout << "Please enter a valid input" << endl;
					displayMenu();
					cin >> input2;
				}
			}
			//if username and password are correct for admin then proceed
			if (admin.validateAdmin(input2, input3)) {
				//set bool type done2 to false
				bool done2 = false;
				//while done2 is true proceed to admin interface
				while (!done2)
				{
					//ouput menu 
					cout << "Admin interface: Please pick the option by selecting the correct number below" << endl;
					cout << "1-Update Cost" << endl;
					cout << "2-Update Quantity" << endl;
					cout << "3-Add a Product to Inventory" << endl;
					cout << "4-Delete a Product from Inventory" << endl;
					cout << "5-Exit" << endl;
					//take in input 
					cin >> input;
					//check if input matches any of the options below and call the proper function then on admin object or end the loop 
					if (stoi(input) == 1) {
						admin.updateCost(list);
					}
					if (stoi(input) == 2)
						admin.updateQty(list);
					if (stoi(input) == 3)
						admin.addProd(list);
					if (stoi(input) == 4)
						admin.deleteNode(list);
					if (stoi(input) == 5) {
						done2 = true; 
					}
					//if input does not match any of the options then proceed to ouptut an error message to the admin
					if (stoi(input) != 1 && stoi(input) != 2 && stoi(input) != 3 && stoi(input) != 4 && stoi(input) != 5) {
						cout << "Please reenter a valid input number choice from the menu" << endl;	
					}
				}
			}
		}
		//while input2 matches for any of the options for Customer then proceed 
		while (input2 == "2" || input2 == "C" || input2 == "Customer" || input2 == "customer")
		{
			//if customer is null then set the pointet to a dynamically created Customer type object 
			if (customer == nullptr) {
				customer = new Customer();
			}
			//while stop is true 
			while (!stop)
			{
				//set stop to the function call of askCustomerOption
				stop = askCustomerOption(input2, customer, list, itemNumber);
			}
			//is stop is false then display menu and take in input again 
			if (stop) {
				break;
			}
		}
		//if any of the inputs matches to exit then set done to true 
		if (input2 == "3" || input2 == "E" || input2 == "Exit" || input2 == "exit")
		{
			done = true;
		}
	}
	
	//if customer exists and the there is an item inside the shopping cart then proceed to make an invoice txt file for the customer and print out their invoice to the console window only 
	if (customer != nullptr && customer->cart->getHead() != nullptr)
	{
		//declare and initialize all the variables below
		string first = " ";
		string last = " ";
		string street = " ";
		string city = " ";
		string state = " ";
		int zip = 0;
		//if the shopping cart exists then proceeed to require the customer to fill in their information since they did make a purchase. 
		customer->fillInInfo(first, last, street, state, city, zip);
		string nameOfOutputFile = customer->getFileName();
		fstream outputFile(nameOfOutputFile.c_str(), ios::out);
		printInvoice(customer, outputFile);
		customer->printLinkedList(customer->cart);
	}
	//close the file 
	file.close();
	//reopen the file in output mode only 
	file.open(fileName, ios::out);
	//call updateFile to update the csv file 
	updateFile(file, list);
	//close the file 
	file.close(); 
	//delete customer 
	delete customer; 
	//set customer to nullptr 
	customer = nullptr; 
	//delete list
	delete list; 
	//set list to nullptr 
	list = nullptr; 
	system("pause");
	return 0; 
}

//function defintion of inFile that reads in the csv file into the inventory linked list 
void inFile(fstream &file, int &itemName, LinkedList *list, Inventory *head) {
	//checks if the file opened or not 
	if (!file)
	{
		cout << "File could not open successfuly" << endl;
	}
	//else seekg is used to move around the pointer position of the file to read in the file contents. 
	else
	{
		int itemNumber = 0;
		string name = " ";
		double cost = 0;
		int qty = 0;
		file.seekg(0L, ios::beg);
		file >> itemNumber;
		head->setItemNumber(itemNumber);
		file.seekg(8L, ios::cur);
		file >> itemName;
		auto name2 = to_string(itemName);
		head->setName(name2);
		file.seekg(1L, ios::cur);
		file >> cost; 
		head->setCost(cost);
		file.seekg(1L, ios::cur);
		file >> qty; 
		head->setQty(qty);
		while (file.good())
		{
			Inventory *newNode = new Inventory();
			file >> itemNumber;
			//if the fail flag of file gets triggered then break out of the loop 
			if (file.fail())
			{
				break; 
			}
			newNode->setItemNumber(itemNumber);
			file.seekg(8L, ios::cur);
			file >> itemName;
			auto name2 = to_string(itemName);
			newNode->setName(name2);
			file.seekg(1L, ios::cur);
			file >> cost; 
			newNode->setCost(cost);
			file.seekg(1L, ios::cur);
			file >> qty; 
			newNode->setQty(qty);
			//append the new nodes being made to put inside the linked list 
			*list += *newNode; 
		}
	}
}

//below is the askCustomerOption function that asks the Customer for his or her options and takes in the input 
bool askCustomerOption(string &input, Customer *user, LinkedList *list, int &itemNumber) {
	//set bool type done to false 
	bool done = false; 
	//done is true keep the while loop going on
	while (!done)
	{
		//output menu to the customer and take in input 
		cout << "Hello customer what would you like to do" << endl;
		cout << "Please pick the appropriate number based on your option" << endl;
		cout << "Menu" << endl;
		cout << "1-Add item to shopping cart" << endl;
		cout << "2-Delete Item from shopping cart." << endl;
		cout << "3-Update Qty of item in shopping cart" << endl;
		cout << "4-Exit" << endl;
		cin >> input;
		//the swtich below handles each respective case for customer 
		switch (stoi(input)) {
		case 1: {
			LinkedList *cart = new LinkedList();
			int quantity = 0;
			bool done2 = false;
			while (!done2) {
				
				
				while (input != "0")
				{
					
					cout << "What item would you like to buy from inventory? Please enter 0 if you are done. Enter cart to view current contents inside shopping cart" << endl;
					cin >> input;
					if (input == "cart" || input == "Cart")
					{
						user->displayShoppingCart(user->cart);
						continue;
					}
					if (input == "0") {
						break; 
					}
					int temp2 = stoi(input);
					Inventory *temp = (user->searchNode(list, temp2));
					 
					if (temp == NULL)
					{
						cout << "Sorry, the item was not found" << endl;
					}
					else if (temp != NULL)
					{
						askQuantity(quantity, temp, list, user, itemNumber);
						Inventory *obj = user->cart->getHead();
					}
				}
				return false; 
			}
		}
		break;
		case 3: {
			LinkedList *cart = new LinkedList();
			cout << "What item's quantity would you like to change inside shopping cart? Please enter the item number" << endl;
			cin >> input;
			int temp = stoi(input);
			Inventory *cartTemp = (user->searchNode(user->cart, temp));
			Inventory *inventoryTemp = (user->searchNode(list, temp));
			if (cartTemp == nullptr) {
				cout << "Sorry, that item does not exist inside the shopping cart" << endl;
				return false;
			}
			if (cartTemp != NULL)
			{
				cout << "What would you like the quantity of " << cartTemp->getItemNumber() << " to be changed to? It must be within the Inventory quantity constraint" << endl;
				cin >> input;
				while (stoi(input) < 0)
				{
					cout << "Your new quantity cannot be negative, please try again" << endl;
					cin >> input;
				}
				if (input == "0")
				{
					int itemNum = cartTemp->getItemNumber();
					int qty = cartTemp->getQty();
					int qty2 = inventoryTemp->getQty();
					inventoryTemp->setQty(qty + qty2);
					user->cart->deleteNode(*cartTemp, itemNum);
					return false;
				}
				if (stoi(input) < cartTemp->getQty() && stoi(input) <= inventoryTemp->getQty())
				{
					int quantityDiff = cartTemp->getQty() - stoi(input);
					int inventQty = inventoryTemp->getQty();
					inventoryTemp->setQty(quantityDiff + inventQty);
					cartTemp->setQty(stoi(input));
					cout << "Quantity has been updated in the shopping cart" << endl;
					return false;
				}
				else if (stoi(input) > cartTemp->getQty() && stoi(input) <= inventoryTemp->getQty())
				{
					int quantityDiff = stoi(input) - cartTemp->getQty();
					int inventQty = inventoryTemp->getQty();
					inventoryTemp->setQty(inventQty - quantityDiff);
					cartTemp->setQty(stoi(input));
					cout << "Quantity has been updated in the shopping cart" << endl; 
					return false;
				}
				else if (stoi(input) == cartTemp->getQty()) {
					cout << "Quantity will not be changed beacuse that exact quantity already exists inside the shopping cart" << endl; 
					return false; 
				}
				else {
					cout << "The input is invalid please enter a valid quantity within the inventory's constraint" << endl; 
					cin >> input; 

				}
			}
		}
				break;
		case 2: {
			cout << "Please enter the item number of the item that you like to delete from shopping cart?" << endl;
			cin >> input;
			int temp2 = stoi(input);
			Inventory *shopTemp = (user->searchNode(user->cart, temp2));
			Inventory *inventTemp = (user->searchNode(list, temp2));
			Inventory *temp = user->cart->getHead();
			if (shopTemp == NULL)
			{
				cout << "Sorry, this item does not exist inside the shopping cart" << endl;
			}
			if (shopTemp != NULL) {
				int quantity = shopTemp->getQty();
				int quantity2 = inventTemp->getQty();
				inventTemp->setQty(quantity + quantity2);
				user->cart->deleteNode(*shopTemp, temp2);
			}
			return false;

		}
			break;
		case 4: {
			return true;
		}
		default:
		{
			cout << "Improper use of input, please reenter a correct input number value" << endl;
			return false;
		}

		}
	}
}

//the askQuantity function takes in quantity from the user and then validates it and puts items inside shopping cart if everything is valid 
void askQuantity(int quantity, Inventory *temp, LinkedList *list, Customer *user, int &itemNumber) {
	//output message to user and take in input
	cout << "Enter the number of quantity of the item " << temp->getItemNumber() << endl;
	cin >> quantity;
	bool stop = false;
	//while stop is true keep the loop going on
		while (!stop)
		{
			//checks if quantity in stock already is zero for that product
			if (temp->getQty() == 0)
			{
				//give the error message
				cout << "Sorry, we have zero quantity of that product available" << endl;
				//set the stop variable to true to stop the while loop.
				stop = true;
			}
			else
			{
				//checks if the quantity number given is invalid or not. It is invalid if we do not have that much in stock beforehand.
				if (quantity > temp->getQty())
				{
					//give error message
					cout << "Sorry, we do not have enough quantity for that product. Please reenter a a number for quantity that we do have" << endl;
					//set stop to false to make the while loop to keep going on
					stop = false;
					//take in input once again
					cin >> quantity;
				}
				//checks if user's input is zero or not 
				else if (quantity == 0)
				{
					//sets stop to true
					stop = true;
				}
				//checks if quantity input is negative or not. If so, gives error message and takes in input again.
				else if (quantity < 0)
				{
					cout << "Quantity value cannot be negative. Please reenter a number for quantity that we do have" << endl;
					stop = false;
					cin >> quantity;
				}
				//if it is valid quantity input, then puts the item inisde the shoppingCart for customer 
				else if (quantity <= temp->getQty() && quantity != 0)
				{
					Inventory *object = new Inventory();
					int itemNumber = 0;
					itemNumber = temp->getItemNumber();
					string name = temp->getName();
					double cost = temp->getCost();
					object->setItemNumber(itemNumber);
					object->setName(name);
					object->setQty(quantity);
					object->setCost(cost);
					//adds item to shopping cart if the item does not exist inside the shopping cart before 
					if (user->searchNode(user->cart, itemNumber) == nullptr)
					{

						*(user->cart) += *object;
						int qty = temp->getQty();
						int qty2 = object->getQty();
						qty -= qty2;
						temp->setQty(qty);
						cout << "Item has been added to the shopping cart" << endl; 
					
					}
					//checks if there is that specific item number inside the shopping cart, if there is then it prevents from creating a duplicate item inside shopping cart and only updates the quantity instead. 
					else if (user->searchNode(user->cart, itemNumber) != nullptr)
					{
						int qty = object->getQty();
						int qty2 = temp->getQty();
						temp->setQty(qty2 - qty);
						int qty3 = (user->searchNode(user->cart, itemNumber))->getQty();
						(user->searchNode(user->cart, itemNumber))->setQty(qty3 + qty);
						cout << "Item has been added to the shopping cart" << endl;
						
					}
					//sets stop to true for the  loop
					stop = true;
				}
			}
		}
	
}
//displayMenu function defintion below displays the options for the main interface of the program 
void displayMenu() {
	cout << "Hello user. Are you admin, customer, or would you like to exit out of program? Choose an option from menu below" << endl;
	cout << "1 - Admin or A - Admin" << endl;
	cout << "2 - Customer or C - Customer" << endl;
	cout << "3 - Exit or E - Exit" << endl;
}
//function defintion of printInvoice that will print the invoice at the end to the LastName + "Invoice.txt” file 
void printInvoice(Customer *user, fstream &outputFile) {
	//set a Inventory node pointer called current to point at where head is at
	Inventory *current = user->cart->getHead();
	// double type local variable called total is set to 0. 
	double total = 0;
	//output message given  below with correct formatting 
	outputFile << "Customer Name: " << user->getFirstName() << " " << user->getLastName() << endl;
	outputFile << "Customer Address:" << user->getStreet() << endl << setw(26) << user->getCtiy() << "," << user->getState() << " " << user->getZipCode() << endl;
	outputFile << "Item Number		Item Name		Qty		Unit Cost		Total" << endl;
	outputFile << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	while (current != NULL) {
		outputFile << setw(24) << left << current->getItemNumber() << setw(24) << "Product " + current->getName() << setw(16) << current->getQty() << setw(24) << current->getCost() << setprecision(2) << fixed << (current->getCost() * current->getQty());
		outputFile << endl;
		total += (current->getQty() * current->getCost());
		current = current->next; //Set the current node to the next node
	}
	outputFile << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	outputFile << setw(90) << setprecision(2) << fixed << right << "Total: $" << total << endl;
}

//updateFile updates the “ProductData.csv” file at the end with the new contents  
void updateFile(fstream &file, LinkedList *list)
{
	//sets current to point to where the head of linked list passed is at 
	Inventory* current = list->getHead();
	//while current is not empty or at end keep traversing the list
	while (current != NULL)
	{
		//if the quantity of the item is not zero, only then update the file 
		if (current->getQty() != 0)
		{
			file << current->getItemNumber() << "," << "Product " << current->getName() << "," << setprecision(2) << fixed << current->getCost() << "," << current->getQty() << endl;
		}
		current = current->next; //set current to the next node
	}

}

