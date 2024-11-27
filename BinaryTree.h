#pragma once
#include <iostream>
#include <vector>
#include <iomanip> 
#include <string>  
#include <cmath>  

/// <summary>
/// This class is a template class so we have to put the .cpp inside the .h to avoid issues
/// </summary>
/// <typeparam name="T"></typeparam>

template <typename T>
class BinaryTree
{

private:

	std::vector<std::vector <T>> _tree;

	int _depth;

public:

	BinaryTree();

	BinaryTree(int depth);

	void setDepth(int depth);

	void setNode(int level, int index, T value);

	T getNode(int level, int index)const;

	void display()const;

};


template <typename T>
BinaryTree<T>::BinaryTree() {
	_depth = 0;
	setDepth(_depth);
}


template <typename T>
BinaryTree<T>::BinaryTree(int depth) {
	_depth = depth;
	setDepth(_depth);	
}

/// <summary>
/// In this method, we add 1 to the given depth because the first level of a binary tree is 0.
/// We resize the tree at this new depth.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="depth"></param>
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
	_depth = depth;
	_tree.resize(_depth + 1); 
	for (int i = 0;i < _depth + 1;i++) {
		_tree[i].resize(i + 1);
	}
}


template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
	if (level <= _depth && level >= 0 && index >= 0 && index <= level) {
		_tree[level][index] = value;
	}
	else {
		std::cerr << "Invalid level or index" << std::endl;
	}
}


template <typename T>
T BinaryTree<T>::getNode(int level, int index)const {
	if (level <= _depth && level >= 0 && index >= 0 && index <= level) {
		return _tree[level][index];
	}
	else {
		std::cerr << "Invalid level or index" << std::endl;
		return T(); // We return something to avoid error
	}
}

/// <summary>
/// This method is used to display our tree. We choose to apply an easy-to-read display without any '/' or '\'.
/// The children are only display with alignments to avoid too many things in the console
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
void BinaryTree<T>::display() const {
	std::cout << std::endl;

	int maxWidth = (1 << (_depth - 1)) * 4; // Maximal tree width

	for (int level = 0; level < _depth; ++level) {
		int numNodes = 1 << level;              // Amount of nodes at this level
		int spaceBetween = maxWidth / numNodes; // Space between two nodes
		int leadingSpace = spaceBetween / 2 - 2; // Initial space to centered the nodes

		// Initial space to centered the nodes
		std::cout << std::string(leadingSpace, ' ');

		// We display the nodes
		for (int i = 0; i < numNodes; ++i) {
			if (i < _tree[level].size()) {
				// We display the node's value
				std::cout << std::setw(2) << _tree[level][i];
			}
			else {
				// We put a 0 if there is no value
				std::cout << std::setw(2) << 0;
			}

			// Space between nodes
			if (i < numNodes - 1) {
				std::cout << std::string(spaceBetween - 2, ' ');
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
