#include "entity.h"
/*//////////////////////////////////////////
	Author: Jacob Vanderkarr
	Filename: entity.cpp
	Date: 11/19/18

	Implementation file for the entity class
*///////////////////////////////////////////

//default ctor
Entity::Entity() : m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH), m_name("DudeGuy")
{}

//default one arg ctor
Entity::Entity(String name) : m_name(name), m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH)
{}

//copy ctor
Entity::Entity(const Entity & copy) : m_name(copy.m_name), m_health(copy.m_health), m_armour(copy.m_armour), m_mana(copy.m_mana), m_strength(copy.m_strength), m_wallet(copy.m_wallet)
{}

//dtor
Entity::~Entity()
{}

Entity & Entity::operator=(const Entity & right)
{
	if (this != &right)
	{
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
	Purpose: Sets the name of the entity

	Pre-Con: This obj exists

	Post-Con: name has been set
*////////////////////////////////////////////////////////////////////////////
void Entity::SetName(String name)
{
	this->m_name = name;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the health of the entity

	Pre-Con: This obj exists

	Post-Con: health has been set
*////////////////////////////////////////////////////////////////////////////
void Entity::SetHealth(int hp)
{
	this->m_health = hp;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the armour of the entity

	Pre-Con: This obj exists

	Post-Con: armour has been set
*////////////////////////////////////////////////////////////////////////////
void Entity::SetArmour(int arm)
{
	this->m_armour = arm;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the mana of the entity

	Pre-Con: This obj exists

	Post-Con: mana has been set
*////////////////////////////////////////////////////////////////////////////
void Entity::SetMana(int mana)
{
	this->m_mana = mana;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Sets the strength of the entity

	Pre-Con: This obj exists

	Post-Con: strength has been set
*////////////////////////////////////////////////////////////////////////////
void Entity::SetStrength(int strength)
{
	this->m_strength = strength;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the name of the entity

	Pre-Con: This obj exists

	Post-Con: returns name
*////////////////////////////////////////////////////////////////////////////
const String Entity::GetName() const
{
	return this->m_name;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the health of the entity

	Pre-Con: This obj exists

	Post-Con: returns health
*////////////////////////////////////////////////////////////////////////////
int Entity::GetHealth() const
{
	return this->m_health;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the armour amount of the Entity

	Pre-Con: This obj exists

	Post-Con: returns armour amount
*////////////////////////////////////////////////////////////////////////////
int Entity::GetArmour() const
{
	return this->m_armour;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the mana of the entity

	Pre-Con: This obj exists

	Post-Con: returns mana
*////////////////////////////////////////////////////////////////////////////
int Entity::GetMana() const
{
	return this->m_mana;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the strength of the entity

	Pre-Con: This obj exists

	Post-Con: returns strength
*////////////////////////////////////////////////////////////////////////////
int Entity::GetStrength() const
{
	return this->m_strength;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: returns the wallet of the entity

	Pre-Con: This obj exists

	Post-Con: returns wallet
*////////////////////////////////////////////////////////////////////////////
const CoinPouch & Entity::GetWallet() const
{
	return this->m_wallet;
}

/*///////////////////////////////////////////////////////////////////////////
	Purpose: Add money to entities wallet

	Pre-Con: This obj exists

	Post-Con: adds money to the wallet, can take negatives in context,
		adding a negative amount will subtract.
*////////////////////////////////////////////////////////////////////////////
void Entity::AddMoney(int amount)
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
	Purpose: remove money from entities wallet

	Pre-Con: This obj exists

	Post-Con: removes money from the wallet, can take negatives in context,
		removing a negative amount will add to the wallet.
*////////////////////////////////////////////////////////////////////////////
void Entity::RmvMoney(int amount)
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

/*///////////////////////////////////////////////////////////////////////////
	Purpose: displays info about the entity

	Pre-Con: This obj exists, mode is selected

	Post-Con: displays info in either minimized or detailed mode
*////////////////////////////////////////////////////////////////////////////
void Entity::Info(bool mode) const
{
	std::cout << "Entity Information:" << std::endl;
	std::cout << "Name: " << this->m_name << std::endl;
	std::cout << "Stats: Health [" << this->m_health << "], Armour [" << this->m_armour <<
		"], Mana [" << this->m_mana << "], Strength [" << this->m_strength << "]" << std::endl;
	std::cout << "Wallet ";
	this->m_wallet.DisplayContent();
	std::cout << std::endl;
}