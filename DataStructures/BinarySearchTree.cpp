#include "pch.h"
#include "BinarySearchTree.h"

// TODO: Write Tests !!!!!!!!!!!!!!

BinarySearchTree::TreeNode::TreeNode(int _value, TreeNode * _left, TreeNode * _right)
	:p_left(_left), p_right(_right), value(_value){}

BinarySearchTree::TreeNode::TreeNode(int _value)
{
	TreeNode(_value, nullptr, nullptr);
}

BinarySearchTree::TreeNode::~TreeNode()
{
	if (this->p_left != nullptr) { delete this->p_left; this->p_left = nullptr; }
	if (this->p_right != nullptr) { delete this->p_right; this->p_right = nullptr; }
}

BinarySearchTree::BST::BST(TreeNode * _root)
	:p_root(_root){}

BinarySearchTree::BST::BST()
{
	BST(nullptr);
}

BinarySearchTree::BST::~BST()
{
	delete this->p_root;
	this->p_root = nullptr;
}

bool BinarySearchTree::BST::insert(int _value, TreeNode * _node)
{
	bool inserting{ true };
	while (inserting)
	{
		if (_value > _node->value)
		{
			if (_node->p_right == nullptr)
			{
				_node->p_right = new TreeNode(_value);
				inserting = false;
			}
			else
			{
				_node = _node->p_right;
			}
		}
		else if (_value < _node->value)
		{
			if (_node->p_left == nullptr)
			{
				_node->p_left = new TreeNode(_value);
				inserting = false;
			}
			else
			{
				_node = _node->p_left;
			}
		}
		else
		{
			return false; // NO DUPLICATES
		}
	}

	return true; // Value inserted
}

bool BinarySearchTree::BST::insert(int _value)
{
	return this->insert(_value, this->p_root);
}

bool BinarySearchTree::BST::remove_node(TreeNode * _node, TreeNode* _parent)
{
	//  TODO: implement case for when _node is root
	if (_parent == nullptr)
	{
		_parent = this->p_root;
	}
	if (_node->value > _parent->value)
	{
		if (_node == _parent->p_right)
		{
			// Found the parent
			if (_node->p_right != nullptr && _node->p_left != nullptr)
			{
				TreeNode* p_traveler = _node->p_right;
				_parent->p_right = p_traveler;

				while (p_traveler->p_left != nullptr)
				{
					p_traveler = p_traveler->p_left;
				}
				p_traveler->p_left = _node->p_left;

				_node->p_left = nullptr;
				_node->p_right = nullptr;
				delete _node;
				_node = nullptr;
				p_traveler = nullptr;
			}
			else if (_node->p_left == nullptr)
			{
				_parent->p_right = _node->p_right;
				_node->p_right = nullptr;
				delete _node;
				_node = nullptr;
			}
			else if (_node->p_right == nullptr)
			{
				_parent->p_right = _node->p_left;
				_node->p_left = nullptr;
				delete _node;
				_node = nullptr;
			}
			return true;
		}
		else
		{
			return remove_node(_node, _parent->p_right);
		}
	}
	else if (_node->value < _parent->value)
	{
		if (_node == _parent->p_left)
		{
			// Found the parent
			if (_node->p_right != nullptr && _node->p_left != nullptr)
			{
				TreeNode* p_traveler = _node->p_right;
				_parent->p_left = p_traveler;

				while (p_traveler->p_left != nullptr)
				{
					p_traveler = p_traveler->p_left;
				}
				p_traveler->p_left = _node->p_left;

				_node->p_left = nullptr;
				_node->p_right = nullptr;
				delete _node;
				_node = nullptr;
				p_traveler = nullptr;
			}
			else if (_node->p_left == nullptr)
			{
				_parent->p_left = _node->p_right;
				_node->p_right = nullptr;
				delete _node;
				_node = nullptr;
			}
			else if (_node->p_right == nullptr)
			{
				_parent->p_left = _node->p_left;
				_node->p_left = nullptr;
				delete _node;
				_node = nullptr;
			}
			return true;
		}
		else
		{
			return remove_node(_node, _parent->p_left);
		}
	}
	return false;
}

bool BinarySearchTree::BST::contains(int _value)
{
	TreeNode* p_traveler = this->p_root;
	while (p_traveler->value != _value)
	{
		if (_value > p_traveler->value)
			p_traveler = p_traveler->p_right;
		else if (_value < p_traveler->value)
			p_traveler = p_traveler->p_left;

		if(p_traveler == nullptr)
			return false;
	}
	return true;
}

bool BinarySearchTree::BST::is_full(TreeNode* _node)
{
	// TODO: IMPLEMENT
	if (_node == nullptr)
		_node = this->p_root;
	return false;
}

bool BinarySearchTree::BST::is_balanced()
{
	// TODO: IMPLEMENT
	return false;
}

int BinarySearchTree::BST::get_min()
{
	TreeNode* p_traveler = this->p_root;
	while (p_traveler->p_left != nullptr)
		p_traveler = p_traveler->p_left;
	return p_traveler->value;
}

int BinarySearchTree::BST::get_max()
{
	TreeNode* p_travler = this->p_root;
	while (p_travler->p_right != nullptr)
		p_travler = p_travler->p_right;
	return p_travler->value;
}

int BinarySearchTree::BST::get_height()
{

	return 0;
}
