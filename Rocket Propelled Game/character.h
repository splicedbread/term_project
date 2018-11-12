#ifndef CHARACTER_H
#define CHARACTER_H
#include "string.h"
#include "backpack.h"
#include "coin_pouch.h"
class Character
{
public:
	Character();
	Character(String name);
	Character(const Character & copy);
	~Character();

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

	bool PickupObj(const Potion & pt);
	bool PickupObj(const Item & itm);
	void DropObj(const Potion & pt);
	void DropObj(const Item & itm);

	static const int STRD_HEALTH = 50;
	static const int STRD_ARMOUR = 0;
	static const int STRD_MANA = 20;
	static const int STRD_STRGTH = 5;

private:
	BackPack m_inventory;
	CoinPouch m_wallet;
	String m_name;
	int m_health;
	int m_armour;
	int m_mana;
	int m_strength;
};
#endif // !CHARACTER_H
