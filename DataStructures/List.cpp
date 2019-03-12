#include "pch.h"
#include "LinkedList.h"


template<typename T>
LinkedList::List<T>::List() :
	p_head(nullptr),
	p_tail(nullptr) {}

template<typename T>
LinkedList::List<T>::~List()
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
LinkedList::ListNode<T>* LinkedList::List<T>::get_node(T const _value)
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
 bool LinkedList::List<T>::delete_node(ListNode<T>* const p_node)
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
 void LinkedList::List<T>::print_values()
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
 T LinkedList::List<T>::pop_front()
{
	T value = this->p_head->value;
	this->p_head = this->p_head->p_next;
	delete this->p_head->p_prev;
	this->p_head->p_prev = nullptr;

	return value;
}

template<typename T>
 T LinkedList::List<T>::pop_back()
{
	T value = this->p_tail->value;
	this->p_tail = this->p_tail->p_prev;
	delete this->p_tail->p_next;
	this->p_tail->p_next = nullptr;

	return value;
}

// Deletes all nodes with a given value
template<typename T>
 bool LinkedList::List<T>::delete_value(T const  _value)
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
 bool LinkedList::List<T>::delete_index(unsigned int const _index)
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
