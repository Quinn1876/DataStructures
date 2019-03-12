#pragma once

namespace BinarySearchTree
{
	class TreeNode;
	class BST;

	class TreeNode
	{
		friend class BST;

	private:
		TreeNode* p_left;
		TreeNode* p_right;
		int value;

	public:
		TreeNode(int _value, TreeNode* _left, TreeNode* _right);
		TreeNode(int _value);
		~TreeNode();
	};

	class BST
	{
	private:
		TreeNode* p_root;
		bool insert(int _value, TreeNode * const _node);

	public:
		BST(TreeNode* _root);
		BST();
		~BST();

		// Editing
		bool insert(int _value);
		bool remove_node(TreeNode* _node, TreeNode* _parent = nullptr);

		// Checks
		bool contains(int _value);
		bool is_full(TreeNode* _node = nullptr);
		bool is_balanced();
		// TODO: Depth First Search
		// TODO: Breadth First Search

		// Getters
		int get_min();
		int get_max();
		int get_height();

		// Manipulate
		void rotate_left();
		void rotate_right();
	};
}
