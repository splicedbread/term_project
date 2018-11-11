#ifndef ITEM_H
#define ITEM_H
#include "string.h"
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
protected:
	String m_name;
	String m_description;
	String m_cost;
	long int m_costSize;

	void FormatCost(String& cst);
	bool ValidateCost(String& cst);
};
#endif // !ITEM_H
