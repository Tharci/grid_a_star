#ifndef LINKED_LIST_H
#define LINKED_LIST_H


template <class T> class LinkedList
{
	class ListItem
	{
	public:
		T value;
		ListItem* nextItem = nullptr;
	};

	ListItem* m_Location = nullptr;
	int m_Size;

	int m_lastGet_idx = 0;
	ListItem* m_lastGet_item = nullptr;


public:

	LinkedList()
	{
		m_Size = 0;
	}

	~LinkedList()
	{
		clear();
	}


	void append(T new_val)
	{
		if (m_Size == 0)
		{
			m_Location = new ListItem;
			m_Location->value = new_val;

			m_lastGet_item = m_Location;
		}
		else
		{
			ListItem* nextItem_tmp = new ListItem;
			ListItem* lastItem = m_Location;
			while (lastItem->nextItem != nullptr)
			{
				lastItem = lastItem->nextItem;
			}

			lastItem->nextItem = nextItem_tmp;
			nextItem_tmp->value = new_val;
		}

		m_Size++;
	}


	void insert(T new_val, int location)
	{
		if (location == 0)
		{
			ListItem* tmp = m_Location;
			m_Location = new ListItem;
			m_Location->value = new_val;
			m_Location->nextItem = tmp;
		}
		else
		{
			ListItem* tmp = get_ListItem_ref(location-1);
			ListItem* newItem = new ListItem;
			newItem->value = new_val;
			newItem->nextItem = tmp->nextItem;
			tmp->nextItem = newItem;
		}

		m_Size++;

		if (location <= m_lastGet_idx)
		{
			m_lastGet_idx++;
		}
	}


	int size()
	{
		return m_Size;
	}


	T get(int index)
	{
		return get_ref(index);
	}


	T& get_ref(int index)
	{
		int from;
		ListItem* currItem;
		if(m_lastGet_idx <= index)
		{
			from = m_lastGet_idx;
			currItem = m_lastGet_item;
		}
		else
		{
			from = 0;
			currItem = m_Location;
		}

		
		for (int i = from; i < index; i++)
		{
			currItem = currItem->nextItem;
		}


		m_lastGet_idx = index;
		m_lastGet_item = currItem;

		return currItem->value;
	}


	ListItem* get_ListItem_ref(int index)
	{
		ListItem* currItem = m_Location;
		for (int i = 0; i < index; i++)
		{
			currItem = currItem->nextItem;
		}

		return currItem;
	}


	T& operator [](int idx)
	{
		return get_ref(idx);
	}

	void remove(int index)
	{
		if (index == 0)
		{
			ListItem* tmp = m_Location;

			m_Location = m_Location->nextItem;

			delete tmp;
		}
		else
		{
			ListItem* currItem = m_Location;
			currItem = get_ListItem_ref(index - 1);

			ListItem* tmp = currItem->nextItem;

			if (index != m_Size - 1)
			{
				currItem->nextItem = currItem->nextItem->nextItem;
			}
			else
			{
				currItem->nextItem = nullptr;
			}
			
			delete tmp;

		}

		m_Size--;

		if (m_lastGet_idx < index)
		{
			m_lastGet_idx--;
		}
		if (m_lastGet_idx == index)
		{
			m_lastGet_idx = 0;
			m_lastGet_item = m_Location;
		}
	}

	void replace(T new_val, int index)
	{
		ListItem* toReplace = get_ref(index);
		
		toReplace->value = new_val;
	}

	void clear()
	{
		ListItem* prev = m_Location;
		ListItem* next = nullptr;

		for (int i = 0; i < m_Size-1; i++)
		{
			next = prev->nextItem;

			delete prev;

			prev = next;
		}

		delete prev;

		m_Size = 0;
		m_Location = nullptr;
		m_lastGet_idx = 0;
		m_lastGet_item = nullptr;
	}

	void destroy()
	{
		clear();

		delete this;
	}

	//~LinkedList();
};



#endif