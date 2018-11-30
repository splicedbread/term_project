#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include "enemy.h"
/*/////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: linked_list.h
	Template(s): Node and LinkedList

	Purpose: Node is a data container, LinkedList is a datastructure of nodes
*//////////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////
	Node holds data and some pointers to the next & previous node
*/////////////////////////////////////////////////////////////////
template <class T>
class LinkedList;

template <class T>
struct Node
{
friend class LinkedList<T>;
public:
	~Node()
	{
		delete m_data;
	};
private:
	Node<T> * m_next = nullptr;
	Node<T> * m_prev = nullptr;
	T * m_data;
};

template <class T>
class LinkedList
{
private:
	Node<T> * m_head;
	Node<T> * m_current;
	Node<T> * m_tail;
	int m_current_pos;
	bool Find(T * n);
public:
	LinkedList();
	LinkedList(T * data);
	~LinkedList();

	void SetData(T * data);
	T * GetData() const;

	bool NextNode();
	bool PreviousNode();
	bool SetCurrentPos(int num);
	int GetCurrentPos();

	void Insert(T * in);
	bool Delete(T * out);

	void Purge();
	void Display();
};
//default ctor
template <class T>
LinkedList<T>::LinkedList(): m_head(nullptr), m_tail(m_head), m_current(m_head), m_current_pos(0)
{}
//one arg ctor, takes in data and assigns m_next and m_prev as nullptr
template <class T>
LinkedList<T>::LinkedList(T * data): m_head(new Node<T>(data)), m_tail(m_head), m_current(m_head), m_current_pos(0)
{
	m_head->m_next(nullptr);
	m_head->m_prev(nullptr);
}

//default dtor, calls purge on exit to free memory
template <class T>
LinkedList<T>::~LinkedList()
{
	Purge();
}

/*//////////////////////////////////////////////////////
	SetData sets/overwrites the data of the current node
*///////////////////////////////////////////////////////
template<class T>
void LinkedList<T>::SetData(T * data)
{
	m_current->m_data = data;
}

/*/////////////////////////////////////////////////
	GetData returns a constant version of the data
*//////////////////////////////////////////////////
template<class T>
T * LinkedList<T>::GetData() const
{
	return m_current->m_data;
}

/*///////////////////////////////////////////////////////////////////////////////////////
	Next node checks the next node and then sets the current pointer to the next pointer. 
*////////////////////////////////////////////////////////////////////////////////////////
template<class T>
bool LinkedList<T>::NextNode()
{
	bool flag = false;
	if (m_current->m_next != nullptr)
	{
		m_current_pos++;
		m_current = m_current->m_next;
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

/*////////////////////////////////////////////////////////////////
	Previous Node checks the previous node and then sets the
	current pointer as the previous node
*/////////////////////////////////////////////////////////////////
template<class T>
bool LinkedList<T>::PreviousNode()
{
	bool flag = false;
	if (m_current->m_prev != nullptr)
	{
		m_current_pos--;
		m_current = m_current->m_prev;
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

/*///////////////////////////////////////////////////////////
	SetCurrentPos will attempt to set the current node
	and pos to the desired num, if that num is out of bounds
	then it will return false;
*///////////////////////////////////////////////////////////
template<class T>
bool LinkedList<T>::SetCurrentPos(int num)
{
	m_current = m_head;
	m_current_pos = 0;
	bool flag = false;
	if (m_current_pos == num)
	{
		flag = true;
	}
	while (!flag && m_current->m_next != nullptr)
	{
		if (m_current_pos == num)
		{
			flag = true;
		}
		NextNode();
	}
	return flag;
}


/*/////////////////////////////////
	returns the m_current_pos value
*//////////////////////////////////
template<class T>
int LinkedList<T>::GetCurrentPos()
{
	return m_current_pos;
}

/*//////////////////////////////////////////////////////////////////////////////////
	Find returns true if a given node is found (typically used in delete or purge)
		returns false if the node is not found
*///////////////////////////////////////////////////////////////////////////////////
template <class T>
bool LinkedList<T>::Find(T * n)
{
	bool found = false;
	m_current_pos = 0;
	m_current = m_head;
	if (m_current->m_data == n.m_data)
	{
		found = true;
	}
	while (!found && m_current->m_next != nullptr)
	{
		if (n.m_data == m_current->m_data)
		{
			found = true;
		}
		else
		{
			m_current = m_current->m_next;
			m_current_pos++;
		}
	}
	return found;
}

/*///////////////////////////////////////////////////////////////////////
	Insert is a append style insert, only inserts at the end of the list
*////////////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::Insert(T * in)
{
	if (m_head == nullptr)
	{
		m_head = new Node<T>;
		m_head->m_data = in;
		m_tail = m_head;
		m_current = m_head;
		m_current_pos = 0;
	}
	else 
	{
		m_tail->m_next = new Node<T>;
		m_tail->m_next->m_data = in;
		m_tail->m_next->m_prev = m_tail;
		m_tail = m_tail->m_next;
		m_current = m_head;
		m_current_pos = 0;
	}

}

/*////////////////////////////////////////////////////////
	Delete searches for the node to delete, and then does
	returns true or false if it was deleted or not
*/////////////////////////////////////////////////////////
template <class T>
bool LinkedList<T>::Delete(T * out)
{
	bool found = false;

	Node<T> * travel = m_head;

	while (travel != nullptr && travel->m_data != out)
	{
		travel = travel->m_next;
	}
	if (travel != nullptr)
	{
		found = true;
		if (travel != m_head && travel != m_tail)
		{
			travel->m_next->m_prev = travel->m_prev;
			travel->m_prev->m_next = travel->m_next;
		}
		else if (travel == m_head)
		{
			m_head = m_head->m_next;
		}
		else
		{
			m_tail = m_tail->m_prev;
		}
		delete travel;
	}

	return found;
}

/*////////////////////////////////////////////
	Purge calls delete until the list is empty
*/////////////////////////////////////////////
template <class T>
void LinkedList<T>::Purge()
{
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		travel = travel->m_next;
		travel != nullptr ? Delete(travel->m_prev->m_data) : Delete(m_head->m_data);
	}
}

/*/////////////////////////////////////////////////////////////////
	Display displays each piece of data one by one in the console
*//////////////////////////////////////////////////////////////////
template <class T>
void LinkedList<T>::Display()
{
	m_current = m_head;
	m_current_pos = 0;
	while (m_current != nullptr)
	{
		std::cout << "pos[" << m_current_pos << "]: " << m_current->m_data << std::endl;
		m_current = m_current->m_next;
		m_current_pos++;
	}
	m_current = m_head;
	m_current_pos = 0;
}

#endif // !LINKED_LIST_H;