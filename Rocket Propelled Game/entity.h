#ifndef ENTITY_H
#define ENTITY_H
#include "String.h"
#include "weapon.h"
#include "coin_pouch.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: entity.h
	Date: 11/19/18

	Class: Entity
	Purpose: A class that will be used to interact with the game
		base class to character, and enemy

	Manager Functions:
		Entity();
		Entity(String name);
		Entity(const Character & copy);
		~Entity();

	Methods:
		Entity & operator = (const Character & right);
		void SetName(String name);
		void SetHealth(int hp);
		void SetArmour(int arm);
		void SetMana(int mana);
		void SetStrength(int strength);
		const String GetName() const;
		int GetHealth() const;
		int GetArmour() const;
		int GetMana() const;
		int GetStrength() const;
		const CoinPouch & GetWallet() const;
		void Info(bool mode) const;
		void AddMoney(int amount);
		void RmvMoney(int amount);
*/////////////////////////////////////////////////////////////////////////////
class Entity
{
public:
	Entity();
	Entity(String name);
	Entity(const Entity & copy);
	virtual ~Entity() = 0;

	Entity & operator = (const Entity & right);

	void SetName(String name);
	void SetHealth(int hp);
	void SetArmour(int arm);
	void SetMana(int mana);
	void SetStrength(int strength);

	const String GetName() const;
	int GetHealth() const;
	int GetArmour() const;
	int GetMana() const;
	int GetStrength() const;
	const CoinPouch & GetWallet() const;

	const Weapon & GetWep() const;
	void SetWep(const Weapon wep);

	void AddMoney(int amount);
	void RmvMoney(int amount);

	virtual void Info(bool mode) const;

	enum Moves
	{
		NORMAL, SPECIAL, RAGE, BLOCK, NOTHING
	};

	int actionMoves(Moves type);

	static const int STRD_HEALTH = 150;
	static const int STRD_ARMOUR = 0;
	static const int STRD_MANA = 20;
	static const int STRD_STRGTH = 2;
	static const Weapon STRD_WEP;

protected:
	CoinPouch m_wallet;
	Weapon m_wep;
	String m_name;
	int m_health;
	int m_armour;
	int m_mana;
	int m_strength;
};
#endif // !ENTITY_H