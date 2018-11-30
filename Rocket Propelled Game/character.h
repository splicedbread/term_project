#ifndef CHARACTER_H
#define CHARACTER_H
#include "entity.h"
#include "backpack.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: backpack.h
	Date: 11/12/18

	Class: Character
	Purpose: A class that will be used to interact with the game

	Manager Functions:
		Character();
		Character(String name);
		Character(const Character & copy);
		~Character();

	Methods:
		Character & operator = (const Character & right);
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
		const BackPack & GetInv() const;
		const CoinPouch & GetWallet() const;
		void Info(bool mode) const;
		bool PickupObj(const Potion & pt);
		bool PickupObj(const Item & itm);
		void DropObj(const Potion & pt);
		void DropObj(const Item & itm);
		void AddMoney(int amount);
		void RmvMoney(int amount);
*/////////////////////////////////////////////////////////////////////////////
class Character : public Entity
{
public:
	Character();
	Character(String name);
	Character(const Character & copy);
	~Character();

	Character & operator = (const Character & right);

	const BackPack & GetInv() const;

	void Info(bool mode) const;

	bool PickupObj(const Potion & pt);
	bool PickupObj(const Item & itm);
	void DropObj(const Potion & pt);
	void DropObj(const Item & itm);
	void DropEverything();

private:
	BackPack m_inventory;
};
#endif // !CHARACTER_H
