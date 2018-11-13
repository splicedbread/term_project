#ifndef BACKPACK_H
#define BACKPACK_H
#include "item.h"
#include "potion.h"
#include "dynamic_array.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: backpack.h
	Date: 11/11/18

	Class: BackPack
	Purpose: A class that will hold all items and potions for the character

	Manager Functions:
		BackPack();
		BackPack(int size);
		BackPack(const BackPack & copy);
		~BackPack();

	Methods:
		BackPack & operator = (const BackPack & right);
		void AddPotion(const Potion& pt);
		void Remove(const Potion & pt);
		void AddItem(const Potion & itm);
		void Remove(const Item & itm);
		bool Find(const Potion & pt);
		bool Find(const Item & itm);
		void Display();
*/////////////////////////////////////////////////////////////////////////////
class BackPack
{
public:
	BackPack();
	BackPack(int size);
	BackPack(const BackPack & copy);
	~BackPack();

	BackPack & operator = (const BackPack & right);
	void UpgradeBP();
	void DowngradBP();
	void Add(const Potion & pt);
	void Add(const Item & itm);
	void Remove(const Potion & pt);
	void Remove(const Item & itm);
	bool Find(const Potion & pt);
	bool Find(const Item & itm);
	void Display(bool mode) const;
	int GetAvailable() const;
	const DynamicArray<Potion> & GetPotions() const;
	const DynamicArray<Item> & GetItems() const;

	static const int STRD_BKPK_SIZE = 5;
private:
	int m_itemAmount;
	int m_itemLimit;
	DynamicArray<Potion> m_ptbelt;
	DynamicArray<Item> m_items;
};
#endif // !BACKPACK_H
