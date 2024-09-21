#pragma once
#include "Lock.h"

template<typename T>
class LockQueue
{
public:
	void Push(T item)
	{
		WRITE_LOCK;
		_items.push(item);
	}

	T Pop()
	{
		WRITE_LOCK;
		if (_items.empty())
			return T();

		T ret = _items.front();
		_items.pop();
		return ret;
	}

	void PopAll(OUT vector<T>& items)
	{
		WRITE_LOCK;
		while (1)
		{
			if (_items.empty())
				return;
			else
			{
				T item = _items.front();
				_items.pop();
				items.push_back(item);
			}

		}

	}

	void Clear()
	{
		WRITE_LOCK;
		_items = queue<T>();
	}

private:
	USE_LOCK;
	queue<T> _items;
};