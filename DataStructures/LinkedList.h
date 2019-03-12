/*
@auth: Quinn Hodges
@data: Feb. 28, 2019
@
@ttle: LinkedList
@
@nspc: LinkedList
@clss: ListNode<T>
@desc: Holds the data needed to traverse the list
	   Holds a single value of type T
@
@clss: List<T>
@desc: Base list class. Has functions for deleting and printing values from the list
@
@clss: UnorderedList<T>
@desc: A list that allows for insertion at any point
@
@clss: OrderedList<int>
@desc: A list that sorts itself apon insertion
@
@nspc: OrderedListTest
@nspc: UnorderedListTest
*/
#pragma once
#include <iostream>


namespace LinkedList
{
	template<typename T>
	class ListNode;
	template<typename T>
	class List;
	template<typename T>
	class UnorderedList;
	class OrderedList;


	template<typename T>
	class List
	{
	protected:
		ListNode<T>* p_head;
		ListNode<T>* p_tail;

		ListNode<T>* get_node(T const _value);
		bool delete_node(ListNode<T>* const p_node);

	public:
		List();
		~List();

		virtual  void print_values();

		virtual  T pop_front();
		virtual  T pop_back();

		virtual  bool delete_value(T const _value);
		virtual  bool delete_index(unsigned int const _index);
	};

	template<typename T>
	class UnorderedList : public List<T>
	{
	public:
		 void append_front(T const _value);
		 void append_back(T const _value);

		 bool replace_value(T const _old, T const _new);
		 bool replace_index(unsigned int const _index, T const _value);
	};

	class OrderedList : public List<int>
	{
	public:
		 void insert(int _value);
	};

	template<typename T>
	class ListNode
	{
		friend class List<T>;
		friend class UnorderedList<T>;
		friend class OrderedList;
	private:
		ListNode<T>* p_next;
		ListNode<T>* p_prev;
		T value;
	public:
		ListNode(T const _value);
		~ListNode();
	};

	template<typename T>
	ListNode<T>::ListNode(T const  _value) :
		p_next(nullptr),
		p_prev(nullptr),
		value(_value) {}

	template<typename T>
	ListNode<T>::~ListNode()
	{
		// Unalloc will take place in the List
		p_next = nullptr;
		p_prev = nullptr;
	}

	template<typename T>
	List<T>::List() :
		p_head(nullptr),
		p_tail(nullptr) {}

	template<typename T>
	List<T>::~List()
	{
		while (this->p_head != this->p_tail)
		{
			this->p_head = this->p_head->p_next;
			delete this->p_head->p_prev;
			this->p_head->p_prev = nullptr;
		}
		delete this->p_head;
		this->p_head = nullptr;
		this->p_tail = nullptr;

	}

	// returns the first node with a given value
	template<typename T>
	ListNode<T>* List<T>::get_node(T const _value)
	{
		ListNode<T>* p_node = this->p_head;
		while (p_node->value != _value)
		{
			if (p_node->p_next == nullptr) { return nullptr; }
			else { p_node = p_node->p_next; }
		}

		return p_node;
	}

	template<typename T>
	bool List<T>::delete_node(ListNode<T>* const p_node)
	{
		if (p_node == nullptr)
			return false;
		else
		{
			p_node->p_prev->p_next = p_node->p_next;
			p_node->p_next->p_prev = p_node->p_prev;
			delete p_node;
			return true;
		}
	}

	template<typename T>
	void List<T>::print_values()
	{
		ListNode<T>* p_node = this->p_head;
		while (p_node->p_next != nullptr)
		{
			std::cout << p_node->value << std::endl;
			p_node = p_node->p_next;
		}
		std::cout << p_node->value << std::endl;
	}

	template<typename T>
	T List<T>::pop_front()
	{
		T value = this->p_head->value;
		this->p_head = this->p_head->p_next;
		delete this->p_head->p_prev;
		this->p_head->p_prev = nullptr;

		return value;
	}

	template<typename T>
	T List<T>::pop_back()
	{
		T value = this->p_tail->value;
		this->p_tail = this->p_tail->p_prev;
		delete this->p_tail->p_next;
		this->p_tail->p_next = nullptr;

		return value;
	}

	// Deletes all nodes with a given value
	template<typename T>
	bool List<T>::delete_value(T const  _value)
	{
		ListNode<T>* p_node = this->get_node(_value);
		if (p_node == nullptr) return false;
		while (this->delete_node(p_node))
		{
			p_node = this->get_node(_value);
		}

		return true;
	}

	// Deletes the node at a given index(index starts at 0)
	template<typename T>
	bool List<T>::delete_index(unsigned int const _index)
	{
		ListNode<T>* p_node = this->p_head;
		for (unsigned int i = 0; i < _index; i++)
		{
			// less then used because i is always one less then the index at the end of the block
			if (p_node->p_next == nullptr)
			{
				// Index out of range
				return false;
			}
			p_node = p_node->p_next;
		}

		return this->delete_node(p_node);
	}

	template<typename T>
	void UnorderedList<T>::append_front(T const  _value)
	{
		if (this->p_head == nullptr)
		{
			this->p_head = new ListNode<T>(_value);
			this->p_tail = this->p_head;
		}
		else
		{
			this->p_head->p_prev = new ListNode<T>(_value);
			this->p_head->p_prev->p_next = this->p_head;
			this->p_head = this->p_head->p_prev;
		}
	}

	template<typename T>
	void UnorderedList<T>::append_back(T const  _value)
	{
		if (this->p_head == nullptr)
		{
			this->p_head = new ListNode<T>(_value);
			this->p_tail = this->p_head;
		}
		else
		{
			this->p_tail->p_next = new ListNode<T>(_value);
			this->p_tail->p_next->p_prev = this->p_tail;
			this->p_tail = this->p_tail->p_next;
		}
	}

	// replaces all values with the new value
	template<typename T>
	bool UnorderedList<T>::replace_value(T const _old, T const _new)
	{
		ListNode<T>* p_node = this->get_node(_old);
		if (p_node == nullptr) return false;
		while (p_node != nullptr)
		{
			p_node->value = _new;
			p_node = this->get_node(_old);
		}
		return true;
	}

	// replaces the value of the node at _index with _value
	template<typename T>
	bool UnorderedList<T>::replace_index(unsigned int const _index, T const _value)
	{
		ListNode<T>* p_node = this->p_head;
		for (unsigned int i = 0; i < _index; i++)
		{
			// less then used because i is always one less then the index at the end of the block
			if (p_node->p_next == nullptr)
			{
				// Index out of range
				return false;
			}
			p_node = p_node->p_next;
		}
		p_node->value = _value;
		return true;
	}


	void OrderedList::insert(int _value)
	{
		ListNode<int>* p_node = new ListNode<int>(_value);

		if (this->p_head == nullptr)
		{
			this->p_head = p_node;
			this->p_tail = p_node;
			return;
		}

		if (_value >= this->p_tail->value)
		{
			this->p_tail->p_next = p_node;
			p_node->p_prev = this->p_tail;
			this->p_tail = p_node;
			return;
		}

		if (_value <= this->p_head->value)
		{
			this->p_head->p_prev = p_node;
			p_node->p_next = this->p_head;
			this->p_head = p_node;
			return;
		}

		ListNode<int>* p_traveler = this->p_head;
		while (p_node->value > p_traveler->value)
		{
			p_traveler = p_traveler->p_next;
		}
		p_traveler->p_prev->p_next = p_node;
		p_node->p_prev = p_traveler->p_prev;
		p_traveler->p_prev = p_node;
		p_node->p_next = p_traveler;

		p_traveler = nullptr;
		p_node = nullptr;
	}
};


///////////////////////////////////////// TESTS ////////////////////////////////////////////////////

namespace UnorderedListTest
{
	template<typename T>
	void test1(LinkedList::UnorderedList<T>);
	template<typename T>
	void test2(LinkedList::UnorderedList<T>);
	template<typename T>
	void test3(LinkedList::UnorderedList<T>);
	template<typename T>
	void test4(LinkedList::UnorderedList<T>);


	template<typename T>
	void test1(LinkedList::UnorderedList<T> testList)
	{
		for (int i = 0; i < 10; i++)
		{
			testList.append_back(i);
		}

		testList.print_values();
	}

	template<typename T>
	void test2(LinkedList::UnorderedList<T> testList)
	{
		for (int i = 0; i < 10; i++)
		{
			testList.append_back(i);
		}
		std::cout << testList.pop_front() << std::endl;
		std::cout << testList.pop_back() << std::endl;
	}

	template<typename T>
	void test3(LinkedList::UnorderedList<T> testList)
	{
		for (int i = 0; i < 10; i++)
		{
			testList.append_back(i);
		}

		for (int i = 4; i <= 6; i++)
		{
			testList.delete_value(i);
		}
		testList.print_values();

		testList.delete_index(1);
		testList.delete_index(20);
		std::cout << "--" << std::endl;
		testList.print_values();
	}

	template<typename T>
	void test4(LinkedList::UnorderedList<T> testList)
	{
		for (int i = 0; i < 21; i++)
		{
			testList.append_front(i % 2);
		}

		testList.replace_value(1, 10);
		testList.print_values();
		std::cout << "--" << std::endl;

		for (unsigned int i = 0; i < 21; i++)
		{
			if (i % 3 == 0)
			{
				testList.replace_index(i, 3);
			}
		}

		testList.print_values();
	}
};

namespace OrderedListTest
{
	void test1(LinkedList::OrderedList testList);

	void test1(LinkedList::OrderedList testList)
	{
		for (int i = 0; i < 15; i++)
		{
			testList.insert(i);
		}
		testList.insert(30);
		for (int i = 0; i < 5; i++)
		{
			testList.insert(i * 10);
		}

		testList.print_values();

	}
};

