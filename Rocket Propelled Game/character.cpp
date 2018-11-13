#include "character.h"
#include <iostream>

Character::Character() : m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH), m_name("DudeGuy")
{}

Character::Character(String name) : m_name(name), m_health(STRD_HEALTH), m_armour(STRD_ARMOUR), m_mana(STRD_MANA), m_strength(STRD_STRGTH)
{}

Character::Character(const Character & copy) : m_name(copy.m_name), m_health(copy.m_health), m_armour(copy.m_armour), m_mana(copy.m_mana), m_strength(copy.m_strength), m_inventory(copy.m_inventory), m_wallet(copy.m_wallet)
{}

Character::~Character()
{}

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

void Character::SetName(String name)
{
	this->m_name = name;
}

void Character::SetHealth(int hp)
{
	this->m_health = hp;
}

void Character::SetArmour(int arm)
{
	this->m_armour = arm;
}

void Character::SetMana(int mana)
{
	this->m_mana = mana;
}

void Character::SetStrength(int strength)
{
	this->m_strength = strength;
}

const String Character::GetName() const
{
	return this->m_name;
}

int Character::GetHealth() const
{
	return this->m_health;
}

int Character::GetArmour() const
{
	return this->m_armour;
}

int Character::GetMana() const
{
	return this->m_mana;
}

int Character::GetStrength() const
{
	return this->m_strength;
}

const BackPack & Character::GetInv() const
{
	return this->m_inventory;
}

const CoinPouch & Character::GetWallet() const
{
	return this->m_wallet;
}

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

void Character::DropObj(const Potion & pt)
{
	m_inventory.Remove(pt);
}

void Character::DropObj(const Item & itm)
{
	m_inventory.Remove(itm);
}

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
