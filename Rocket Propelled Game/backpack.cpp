#include "backpack.h"
#include <iostream>
using std::cout;
using std::endl;
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: backpack.cpp
	Date: 11/11/18

	Modifications:
*///////////////////////////

//default ctor
BackPack::BackPack() : m_itemAmount(0), m_itemLimit(0)
{}

//one arg ctor, controls the itemlimit
BackPack::BackPack(int size) : m_itemAmount(0), m_itemLimit(size)
{}

//copy ctor
BackPack::BackPack(const BackPack & copy) : m_itemAmount(copy.m_itemAmount), m_itemLimit(copy.m_itemLimit), m_ptbelt(copy.m_ptbelt), m_items(copy.m_items)
{}

//dtor
BackPack::~BackPack()
{}

//op = overload
BackPack & BackPack::operator = (const BackPack & right)
{
	if (this != &right)
	{
		this->m_itemAmount = right.m_itemAmount;
		this->m_itemLimit = right.m_itemLimit;
		this->m_ptbelt = right.m_ptbelt;
		this->m_items = right.m_items;
	}
	return *this;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Upgrades the capacity of the backpack, currently no upper limit

	Pre-Con: This obj exists

	Post-Con: limit has been raised
*////////////////////////////////////////////////////////////////////////////
void BackPack::UpgradeBP()
{
	this->m_itemLimit = this->m_itemLimit + 5;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Downgrades the capacity of the backpack, cannot be smaller than 5

	Pre-Con: This obj exists

	Post-Con: backpack has been downgraded, or not
*////////////////////////////////////////////////////////////////////////////
void BackPack::DowngradBP()
{
	if (this->m_itemLimit > 5)
	{
		this->m_itemLimit = this->m_itemLimit - 5;
	}
	else
	{
		cout << "cannot downgrade backpack further" << endl;
	}
}

/*////////////////////////////////////////////////////////////////////////////////
	Purpose: being able to add a potion to the inventory is useful

	Pre-Con: this obj exists

	Post-Con: if there is room to add a potion, a potion is added to the backpack
*/////////////////////////////////////////////////////////////////////////////////
void BackPack::Add(const Potion& pt)
{
	if (this->m_itemAmount < this->m_itemLimit)
	{
		this->m_ptbelt.Insert(pt);
		//after inserting a potion, increase how many items are in the backpack
		this->m_itemAmount++;
	}
	else
	{
		cout << "There is no more additional space in your backpack" << endl;
	}
}

/*////////////////////////////////////////////////////////////////////////////////
	Purpose: being able to add an item to the inventory is useful

	Pre-Con: this obj exists

	Post-Con: if there is room to add an item, an item is added to the backpack
*/////////////////////////////////////////////////////////////////////////////////
void BackPack::Add(const Item & itm)
{
	if (this->m_itemAmount < this->m_itemLimit)
	{
		this->m_items.Insert(itm);
		//after inserting an item, increase how many items are in the backpack
		this->m_itemAmount++;
	}
	else
	{
		cout << "There is no more additional space in your backpack" << endl;
	}
}

/*//////////////////////////////////////////////////////////////////////////
	Purpose: removing a potion could be used somewhere else for using it,
			or to drop a potion to make space for a new item/potion

	Pre-Con: this obj exist

	Post-Con: removed potion, or it didnt find it
*///////////////////////////////////////////////////////////////////////////
void BackPack::Remove(const Potion & pt)
{
	if (Find(pt))
	{
		this->m_ptbelt.Delete(pt);
		cout << pt.GetName() << " removed" << endl;
		this->m_itemAmount--;
	}
	else
	{
		cout << "You cannot remove what you do not have" << endl;
	}
}

/*//////////////////////////////////////////////////////////////////////////
	Purpose: removing an item could be used somewhere else for using it,
			or to drop an item to make space for a new item

	Pre-Con: this obj exist

	Post-Con: removed item, or it didnt find it
*///////////////////////////////////////////////////////////////////////////
void BackPack::Remove(const Item & itm)
{
	if (Find(itm))
	{
		this->m_items.Delete(itm);
		cout << itm.GetName() << " removed" << endl;
		this->m_itemAmount--;
	}
	else
	{
		cout << "You cannot remove what you do not have" << endl;
	}
}

/*/////////////////////////////////////////////////////////////////////
	Purpose: Linear search for a potion within the potion dynamic array

	Pre-Con: This obj exists

	Post-Con: returns either true or false if the obj is found
*//////////////////////////////////////////////////////////////////////
bool BackPack::Find(const Potion & pt)
{
	bool flag = false;
	if (this->m_itemAmount != 0)
	{
		for (int i = 0; !flag && (i < this->m_ptbelt.GetElements() + 1);i++)
		{
			if (pt == this->m_ptbelt[i])
			{
				flag = true;
			}
		}
	}
	return flag;
}

/*/////////////////////////////////////////////////////////////////////
	Purpose: Linear search for an item within the item dynamic array

	Pre-Con: This obj exists

	Post-Con: returns either true or false if the obj is found
*//////////////////////////////////////////////////////////////////////
bool BackPack::Find(const Item & itm)
{
	bool flag = false;
	if (this->m_itemAmount != 0)
	{
		for (int i = 0; !flag && (i < this->m_items.GetElements() + 1); i++)
		{
			if (itm == this->m_items[i])
			{
				flag = true;
			}
		}
	}
	return flag;
}

/*////////////////////////////////////////////////////////////////////////
	Purpose: Display a quick look at the inventory and space remaining,
			then display details on what is inside the inventory

	Pre-Con: This obj exists

	Post-Con: will output based on number of items/potions
*//////////////////////////////////////////////////////////////////////////
void BackPack::Display()
{
	cout << "Backpack status: (" << this->m_itemAmount << "/"
		<< this->m_itemLimit << ") spaces used." << endl;
	cout << "Number of Potions: [" << this->m_ptbelt.GetElements() << "]" << endl;
	cout << "Number of Items: [" << this->m_items.GetElements() << "]" << endl;

	cout << "\nDetailed information below:" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\nAvailable Potions:";

	if (this->m_ptbelt.GetElements() > 0)
	{
		cout << endl << endl;
		for (int i = 0; i < this->m_ptbelt.GetElements(); i++)
		{
			cout << i + 1 << ". ";
			this->m_ptbelt[i].Display();
			cout << endl;
		}
	}
	else
	{
		cout << " N/A" << endl;
	}

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\nAvailable Items:";
	if (this->m_items.GetElements() > 0)
	{
		cout << endl << endl;
		for (int i = 0; i < this->m_items.GetElements(); i++)
		{
			cout << i + 1 << ". ";
			this->m_items[i].Display();
			cout << endl;
		}
	}
	else
	{
		cout << " N/A" << endl;
	}

	cout << endl << "End of detailed information\n~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}