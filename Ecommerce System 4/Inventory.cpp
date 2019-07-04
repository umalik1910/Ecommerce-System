#include "Inventory.h"

//defintions of the constructors and destructors below 
Inventory::Inventory()
{
	itemNumber;
	name;
	cost;
	qty;

}
Inventory::Inventory(int itemNum, string Name, double Cost, int quantity) {
	itemNumber = itemNum; 
	name = Name; 
	cost = Cost; 
	qty = quantity; 
}
Inventory::~Inventory()
{
}
