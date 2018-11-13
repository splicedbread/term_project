#include "coin_pouch.h"
#include <iostream>
/*////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 11/10/18
	FileName: coin_pouch.cpp

	Purpose: Implementation file for the CoinPouch class

	Modifications:
*//////////////////////////////////////////////////////

//default ctor
CoinPouch::CoinPouch() : m_money(0)
{}

//1 arg ctor
CoinPouch::CoinPouch(int amount) : m_money(amount)
{}

//copy ctor
CoinPouch::CoinPouch(const CoinPouch & copy) : m_money(copy.m_money)
{}

//dtor
CoinPouch::~CoinPouch()
{}

/*///////////////////////////////////////////////////////////
	Name: operator =

	Purpose: overides the '=' functionality,
		sets this objects money value equal to the rights

	Pre-con: this object exists, right object exists

	Post-con: this objects money is equal to rights
*////////////////////////////////////////////////////////////
CoinPouch & CoinPouch::operator = (const CoinPouch & right)
{
	if (this != &right)
	{
		this->m_money = right.m_money;
	}
	return *this;
}

/*////////////////////////////////////////////////////////
	Name: SetMoney

	Purpose: a setter used to interact with m_money

	Pre-Con: This object exists, amount is greater than 0

	Post-Con: amount is assigned to m_money
*/////////////////////////////////////////////////////////
void CoinPouch::SetMoney(int amount)
{
	if (this->m_money >= 0 && (this->m_money + amount) >= 0)
	{
		this->m_money = amount;
	}
	else
	{
		std::cout << "character cannot go into debt" << std::endl;
	}
}

/*/////////////////////////////////////////////////////////
	Name: GetMoney

	Purpose: Taken directly from the federal reserve, this
		getter function just returns the m_money variable
*//////////////////////////////////////////////////////////
const int CoinPouch::GetMoney() const
{
	return this->m_money;
}

/*////////////////////////////////////////////////////////////////
	Name: DisplayContent

	Purpose: Keeping in theme with the Potion class,
			This method will display the money in the same format
			that the potion costs is displayed

	Pre-Cond: this object exists

	Post-Cond: will either display in a formatted way, or empty
*//////////////////////////////////////////////////////////////////
void CoinPouch::DisplayContent() const
{
	if (!this->IsBroke())
	{
		int copper = 0;
		int silver = 0;
		int gold = 0;
		int platnium = 0;

		copper = this->m_money;
		while (copper > 99)
		{
			silver++;
			copper -= 100;
		}

		while (silver > 99)
		{
			gold++;
			silver -= 100;

		}

		while (gold > 99)
		{
			platnium++;
			gold -= 100;

		}

		std::cout << "Contents: ["
			<< platnium << "] Platnium, ["
			<< gold << "] Gold, ["
			<< silver << "] Silver, ["
			<< copper << "] Copper " << std::endl;
	}
	else
	{
		std::cout << "Contents: empty" << std::endl;
	}
}

/*///////////////////////////////////////////////////////////////////
	Name: IsBroke

	Purpose: while may some consider it break even, having no money
		means you are broke in this case

	Pre-Con: This object exists

	Post-Con: returns true if m_money is equal to 0
*////////////////////////////////////////////////////////////////////
bool CoinPouch::IsBroke() const
{
	return (m_money == 0);
}