#ifndef COIN_POUCH_H
#define COIN_POUCH_H

/*////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: coin_pouch.h
	Date Created: 11/10/18

	Class Name: CoinPouch

	Manager Functions:
		Default Ctor,
		1 Arg Ctor,
		Copy Ctor,
		Dtor,

	Methods:
		op =, CoinPouch &, 1 arg
		SetMoney, void, 1 arg
		GetMoney, int
		DisplayContent, void
		IsBroke, bool

*/////////////////////////////////////
class CoinPouch
{
public:
	CoinPouch();
	CoinPouch(int amount);
	CoinPouch(const CoinPouch & copy);
	~CoinPouch();

	CoinPouch & operator = (const CoinPouch & right);
	void SetMoney(int amount);
	int GetMoney();
	void DisplayContent();
	bool IsBroke();

private:
	unsigned int m_money;
};

#endif // !COIN_POUCH_H