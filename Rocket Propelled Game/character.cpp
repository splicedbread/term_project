#include "character.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: character.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

//default ctor
Character::Character() : Entity()
{}

//one arg ctor
Character::Character(String name) : Entity(name)
{}

//copy ctor
Character::Character(const Character & copy) : Entity(copy), m_inventory(copy.m_inventory)
{}

//dtor
Character::~Character()
{}

//op = overload
Character & Character::operator=(const Character & right)
{
	if (this != &right)
	{
		this->m_inventory = right.m_inventory;
		this->m_wallet = right.m_wallet;
		this->m_name = right.m_name;
		this->m_health = right.m_health;
		this->m_armour = right.m_armour;
		this->m_mana = right.m_mana;
		this->m_strength = right.m_strength;
	}
	return *this;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the inventor of the character

	Pre-Con: This obj exists

	Post-Con: returns inventory
*////////////////////////////////////////////////////////////////////////////
const BackPack & Character::GetInv() const
{
	return this->m_inventory;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: displays info about the character

	Pre-Con: This obj exists, mode is selected

	Post-Con: displays info in either minimized or detailed mode
*////////////////////////////////////////////////////////////////////////////
void Character::Info(bool mode) const
{
	std::cout << "Character Information:" << std::endl;
	std::cout << "Name: " << this->m_name << std::endl;
	std::cout << "Stats: Health [" << this->m_health << "], Armour [" << this->m_armour <<
		"], Mana [" << this->m_mana << "], Strength [" << this->m_strength << "]" << std::endl;
	std::cout << "Wallet ";
	this->m_wallet.DisplayContent();
	std::cout << "Inventory: " << std::endl;
	this->m_inventory.Display(mode);
	std::cout << std::endl;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Add object to players inventory
	 + overload
	Pre-Con: This obj exists

	Post-Con: returns true if successful, returns false if nothing could be added
*////////////////////////////////////////////////////////////////////////////
bool Character::PickupObj(const Potion & pt)
{
	bool flag = false;
	if (m_inventory.GetAvailable() > 0)
	{
		m_inventory.Add(pt);
		flag = true;
	}
	return flag;
}

bool Character::PickupObj(const Item & itm)
{
	bool flag = false;
	if (m_inventory.GetAvailable() > 0)
	{
		m_inventory.Add(itm);
		flag = true;
	}
	return flag;
}


/*///////////////////////////////////////////////////////////////////////////
	Purpose: removes object from players inventory
	 + overload
	Pre-Con: This obj exists

	Post-Con: returns true if successful, returns false if nothing could be removed or found
*////////////////////////////////////////////////////////////////////////////
void Character::DropObj(const Potion & pt)
{
	m_inventory.Remove(pt);
}

void Character::DropObj(const Item & itm)
{
	m_inventory.Remove(itm);
}