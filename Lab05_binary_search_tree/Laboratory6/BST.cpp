#include "BST.h"
#include "ListIterator.h"

// complexity Theta(1)
node_pointer BST::init_node(INFO elem_info)
{
	node_pointer temp_node = new node;
	temp_node->inf = elem_info;
	temp_node->left_child = nullptr;
	temp_node->right_child = nullptr;

	return temp_node;
}

// complexity O(n) because in the worst case we might have a three where each node has only 1 child
// average would be O(log(n))
bool BST::search(INFO elem_information)
{
	if (this->is_empty())
		return false;
	else
	{
		return this->search_rec(this->root, elem_information);
	}
}

node_pointer BST::search_ret(INFO elem_information)
{
	if (this->is_empty())
		return nullptr;
	else
	{
		return this->search_rec_ret(this->root, elem_information);
	}
}

// same as for search
node_pointer BST::search_rec_ret(node_pointer node, INFO elem_information)
{
	if (node == nullptr)
		return nullptr;
	else
	{
		if (node->inf == elem_information)
			return node;
		else if (this->rel(node->inf, elem_information))
		{
			this->search_rec(node->right_child, elem_information);
		}
		else
		{
			this->search_rec(node->left_child, elem_information);
		}
	}
}

// same as for search
bool BST::search_rec(node_pointer node, INFO elem_information)
{
	if (node == nullptr)
		return false;
	else
	{
		if (node->inf == elem_information)
			return true;
		else if (this->rel(node->inf, elem_information))
		{
			return this->search_rec(node->left_child, elem_information);
		}
		else
		{
			return this->search_rec(node->right_child, elem_information);
		}
	}
}

// complexity Theta(1)
INFO BST::get_element(ListIterator it)
{
	return it.getCurrent();
}

// complexity O(n) because in the worst case we might have a three where each node has only 1 child
// average would be O(log(n))
bool BST::add(INFO elem_information)
{
	if (this->is_empty())
	{
		node_pointer new_node = init_node(elem_information);
		this->root = new_node;
	}
	else
	{
		add_element_rec(this->root, elem_information);
	}

	this->size_of_list++;

	return true;
}

node_pointer BST::add_element_rec(node_pointer node, INFO elem_information)
{
	if (node == nullptr)
		node = this->init_node(elem_information);
	else if (this->rel(node->inf, elem_information))
	{
		node->left_child = this->add_element_rec(node->left_child, elem_information);
	}
	else
	{
		node->right_child = this->add_element_rec(node->right_child, elem_information);
	}
	return node;
}

// same as for search but we return the parent
node_pointer BST::search_remove(node_pointer node, node_pointer parent, INFO elem_information)
{
	if (node == nullptr)
		return parent;
	// maybe parent
	else
	{
		if (node->inf == elem_information)
			return parent;
		else if (this->rel(node->inf, elem_information))
		{
			return this->search_remove(node->left_child, node, elem_information);
		}
		else
		{
			return this->search_remove(node->right_child, node, elem_information);
		}
	}
}

// complexity O(n+m)
bool BST::remove(INFO elem_information)
{
	node_pointer parent = search_remove(this->root, nullptr, elem_information);
	if (parent == nullptr)
	{
		return false;
	}
	node_pointer child = nullptr;
	int right = -1;


	if (parent->right_child != nullptr && parent->right_child->inf == elem_information)
	{
		child = parent->right_child;
		right = 1;
	}
	else if (parent->left_child != nullptr && parent->left_child->inf == elem_information)
	{
		child = parent->left_child;
		right = 0;
	}

	if (child != nullptr)
	{
		// the node to be removed has no descendant
		if (child->left_child == nullptr && child->right_child == nullptr)
		{
			if (right == 1)
			{
				parent->right_child = nullptr;
				this->size_of_list--;
				return true;
			}
			if (right == 0)
			{
				parent->left_child = nullptr;
				this->size_of_list--;
				return true;
			}
		}
		// the node to be removed has one descendant
		else if (child->left_child != nullptr && child->right_child == nullptr)
		{
			if (right == 1)
			{
				parent->right_child = child->left_child;
				this->size_of_list--;
				return true;
			}
			if (right == 0)
			{
				parent->left_child = child->left_child;
				this->size_of_list--;
				return true;
			}
		}
		else if	(child->left_child == nullptr && child->right_child != nullptr)
		{
			if (right == 1)
			{
				parent->right_child = child->right_child;
				this->size_of_list--;
				return true;
			}
			if (right == 0)
			{
				parent->left_child = child->right_child;
				this->size_of_list--;
				return true;
			}
		}
		// the node to be removed has two descendants
		else if (child->left_child != nullptr && child->right_child != nullptr)
		{
			node_pointer max_left_subtree = child->left_child;
			node_pointer max_left_subtree_parent = child->left_child;
			while (max_left_subtree->right_child != nullptr)
			{
				max_left_subtree_parent = max_left_subtree;
				max_left_subtree = max_left_subtree->right_child;
			}

			// first put it into the position to be deleted
			child = max_left_subtree;

			// delete the max
			if (max_left_subtree->left_child == nullptr)
			{
				max_left_subtree_parent->right_child = nullptr;
				this->size_of_list--;
				return true;
			}
			else
			{
				max_left_subtree_parent->right_child = max_left_subtree->left_child;
				this->size_of_list--;
				return true;
			}
		}
	}

	return false;
}

// complexity Theta(1)
ListIterator BST::iterator() const
{
	return ListIterator(*this);
}

// complexity Theta(1)
bool BST::is_empty()
{
	if (this->size() == 0)
		return true;
	return false;
}

typedef bool is_unique;

/*
pseudocode:
	function uniqueCount(list):

	numbers_array : INFO[STACK_SIZE]
	uniqueness_array : is_unique[STACK_SIZE]

	for i <- 0; STACK_SIZE; 1 do
		uniqueness_array[i] <- false
	end-for

	i <- false
	it <- [list].iterator()
	while it.valid() do
		elem <- it.getCurrent()
		found <- false

		for  j = 0; i; 1 do
			if numbers_array[j] = elem then
				uniqueness_array[j] <- false
				found <- true
				break
			end-if
		end-for

		if found = false then
			numbers_array[i] <- elem
			uniqueness_array[i] <- true
			i <- i+1
		end-if

		it.next()
	end-while

	total <- 0
	for j <- 0; i; 1 do
	
		if uniqueness_array[j] = true then
			total <- total+1
		end-if
	end-for

	uniqueCount <- total
	end-function
*/

// complexity:
// best: O(list size^2)
// worst: O(list size^2)
// average: O(list size^2)
int BST::uniqueCount() const
{
	INFO numbers_array[STACK_SIZE];
	is_unique uniqueness_array[STACK_SIZE];

	for (is_unique ua : uniqueness_array)
	{
		ua = false;
	}

	int i=0;
	bool found;

	ListIterator it = this->iterator();
	while (it.valid()) {
		INFO elem = it.getCurrent();
		found = false;

		for (int j = 0; j < i; j++)
		{
			if (numbers_array[j] == elem)
			{
				uniqueness_array[j] = false;
				found = true;
				break;
			}
		}

		if (found == false)
		{
			numbers_array[i] = elem;
			uniqueness_array[i] = true;
			i++;
		}

		it.next();
	}

	int total = 0;
	for (int j = 0; j < i; j++)
	{
		if (uniqueness_array[j] == true)
			total++;
	}

	return total;
}
