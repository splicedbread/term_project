#include "character.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: character.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

//default ctor
Character::Character() : m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH), m_name("DudeGuy")
{}

//one arg ctor
Character::Character(String name) : m_name(name), m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH)
{}

//copy ctor
Character::Character(const Character & copy) : m_name(copy.m_name), m_health(copy.m_health), m_armour(copy.m_armour), m_mana(copy.m_mana), m_strength(copy.m_strength), m_inventory(copy.m_inventory), m_wallet(copy.m_wallet)
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
	Purpose: Sets the name of the character

	Pre-Con: This obj exists

	Post-Con: name has been set
*////////////////////////////////////////////////////////////////////////////
void Character::SetName(String name)
{
	this->m_name = name;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the health of the character

	Pre-Con: This obj exists

	Post-Con: health has been set
*////////////////////////////////////////////////////////////////////////////
void Character::SetHealth(int hp)
{
	this->m_health = hp;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the armour of the character

	Pre-Con: This obj exists

	Post-Con: armour has been set
*////////////////////////////////////////////////////////////////////////////
void Character::SetArmour(int arm)
{
	this->m_armour = arm;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the mana of the character

	Pre-Con: This obj exists

	Post-Con: mana has been set
*////////////////////////////////////////////////////////////////////////////
void Character::SetMana(int mana)
{
	this->m_mana = mana;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the strength of the character

	Pre-Con: This obj exists

	Post-Con: strength has been set
*////////////////////////////////////////////////////////////////////////////
void Character::SetStrength(int strength)
{
	this->m_strength = strength;
}


/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the name of the character

	Pre-Con: This obj exists

	Post-Con: returns name
*////////////////////////////////////////////////////////////////////////////
const String Character::GetName() const
{
	return this->m_name;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the health of the character

	Pre-Con: This obj exists

	Post-Con: returns health
*////////////////////////////////////////////////////////////////////////////
int Character::GetHealth() const
{
	return this->m_health;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the armour amount of the character

	Pre-Con: This obj exists

	Post-Con: returns armour amount
*////////////////////////////////////////////////////////////////////////////
int Character::GetArmour() const
{
	return this->m_armour;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the mana of the character

	Pre-Con: This obj exists

	Post-Con: returns mana
*////////////////////////////////////////////////////////////////////////////
int Character::GetMana() const
{
	return this->m_mana;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the strength of the character

	Pre-Con: This obj exists

	Post-Con: returns strength
*////////////////////////////////////////////////////////////////////////////
int Character::GetStrength() const
{
	return this->m_strength;
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
	Purpose: returns the wallet of the character

	Pre-Con: This obj exists

	Post-Con: returns wallet
*////////////////////////////////////////////////////////////////////////////
const CoinPouch & Character::GetWallet() const
{
	return this->m_wallet;
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

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Add money to players wallet
	 
	Pre-Con: This obj exists

	Post-Con: adds money to the wallet, can take negatives in context,
		adding a negative amount will subtract.
*////////////////////////////////////////////////////////////////////////////
void Character::AddMoney(int amount)
{
	if (amount > 0)
	{
		this->m_wallet.SetMoney(this->m_wallet.GetMoney() + amount);
	}
	else
	{
		RmvMoney(amount*-1);
	}
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: remove money from players wallet

	Pre-Con: This obj exists

	Post-Con: removes money from the wallet, can take negatives in context,
		removing a negative amount will add to the wallet.
*////////////////////////////////////////////////////////////////////////////
void Character::RmvMoney(int amount)
{
	if (amount >= 0)
	{
		this->m_wallet.SetMoney(this->m_wallet.GetMoney() - amount);
	}
	else
	{
		AddMoney(amount*-1);
	}
}
