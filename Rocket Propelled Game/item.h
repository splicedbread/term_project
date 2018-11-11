#ifndef ITEM_H
#define ITEM_H
#include "string.h"
/*
	Author: Jacob Vanderkarr
	Date: 11/11/18
	FileName: item.h
	Class: Item

	Purpose: Base class that contains basic functionality that
			allows a general purpose usage for items in the RPG
			such as potions, armour, weapons etc.

	Manager Functions:
		Item();
		Item(String nm, String dsc, String cst);
		Item(String nm, String dsc);
		Item(String nm);
		~Item();

	Methods:
	  Getters:
		const String GetName() const;
		const String GetDesc() const;
		const String GetCost() const;
		const String GetCostSize() const;
	  Setters:
		void SetName(String nm);
		void SetDesc(String dsc);
		void SetCost(String cst);
	  Display:
		virtual void Display() const;
		virtual void DisplayCost() const;
	  Comparison operators:
		virtual Item & operator = (const Item & right);
		virtual bool operator == (const Item & right) const;
		virtual bool operator != (const Item & right) const;
		virtual bool operator > (const Item & right) const;
		virtual bool operator >= (const Item & right) const;
		virtual bool operator < (const Item & right) const;
		virtual bool operator <= (const Item & right) const;
	  Helper Methods
		void FormatCost(String& cst);
		bool ValidateCost(String& cst);
*/
class Item
{
public:
	Item();
	Item(String nm, String dsc, String cst);
	Item(String nm, String dsc);
	Item(String nm);
	~Item();
	const String GetName() const;
	const String GetDesc() const;
	const String GetCost() const;
	const String GetCostSize() const;

	void SetName(String nm);
	void SetDesc(String dsc);
	void SetCost(String cst);

	virtual void Display() const;
	virtual void DisplayCost() const;

	virtual Item & operator = (const Item & right);
	virtual bool operator == (const Item & right) const;
	virtual bool operator != (const Item & right) const;
	virtual bool operator > (const Item & right) const;
	virtual bool operator >= (const Item & right) const;
	virtual bool operator < (const Item & right) const;
	virtual bool operator <= (const Item & right) const;

protected:
	String m_name;
	String m_description;
	String m_cost;
	long int m_costSize;

	void FormatCost(String& cst);
	bool ValidateCost(String& cst);
};
#endif // !ITEM_H
