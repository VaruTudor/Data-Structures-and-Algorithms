#include "Bag.h"
#include "BagIterator.h"

#include <iostream>
#include <math.h>

// auxiliary functions
// complexity O(sqrt(x))
bool prime(int x)
{
	int d = 2;
	while (d <= sqrt(x))
	{
		if (x % d == 0)
		{
			return false;
		}
		d++;
	}
	return true;
}

// complexity O(sqrt(x)) (?)
int next_prime(int number)
{
	/*
		finds the next prime number ~ twice as large
	*/
	int next_prime_number = number * 2;

	if (prime(next_prime_number))
		return next_prime_number;

	while (!prime(next_prime_number))
	{
		next_prime_number++;
	}

	return next_prime_number;
}

//Bag methods
// complexity Theta(capacity)
Bag::Bag()
{
	// capacity should always be a prime number
	this->size_of_bag = 0;
	this->capacity = 17;
	this->elements = new Telem[this->capacity];
	for (int i = 0; i < this->capacity; i++)
	{
		this->elements[i] = EMPTY_POSITION;
	}
}

Bag::~Bag()
{
	delete[] this->elements;
}

// complexity Theta(1)
Telem Bag::at(int positon)
{
	return this->elements[positon];
}

// complexity Theta(1)
bool Bag::isEmpty()
{
	if (this->size_of_bag == 0)
		return true;
	return false;
}

// complexity O(capacity)
int Bag::main_hash_function(Telem element)
{

	int aux_element = abs(element);
	bool found = false;
	int probe_number = 0;
	int position = -1;

	while (!found)
	{
		position = (this->first_hash_function(aux_element) + probe_number * this->second_hash_function(aux_element) ) % this->capacity;

		if (this->elements[position] == EMPTY_POSITION || this->elements[position] == DELETED_POSITION)
		{
			found = true;
		}
		else
		{
			probe_number++;
			if (probe_number >= this->capacity)
				return -1;
		}
	}

	return position;
}

// complexity Theta(1)
int Bag::first_hash_function(Telem element)
{
	return element % this->capacity;
}

// complexity Theta(1)
int Bag::second_hash_function(Telem element)
{
	return 1 + (element % (this->capacity-1) );
}


// complexity O(capacity) amortized
bool Bag::add(Telem element)
{
	int position = this->main_hash_function(element);
	if (position != -1)
	{
		this->elements[position] = element;
		this->size_of_bag++;
		return true;
	}
	// in case no free position was found, we must recapacity
	else 
	{
		//resize
		//we rehash the entire bag with a new capacity
		this->resize();

		position = this->main_hash_function(element);
		//std::cout << position << std::endl;
		this->elements[position] = element;
		this->size_of_bag++;
		return true;
	}

	// if element has not been added return false
	return false;
}

// complexity Theta(capacity)
void Bag::resize()
{
	Telem* auxiliary_elements = new Telem[this->size_of_bag];
	int j = 0;
	for (int i = 0; i < this->capacity; i++)
	{
		if (this->elements[i] != EMPTY_POSITION && this->elements[i] != DELETED_POSITION)
		{
			auxiliary_elements[j] = this->elements[i];
			j++;
		}
	}

	this->capacity = next_prime(this->capacity);
	this->elements = new Telem[this->capacity];
	int position;

	for (int i = 0; i < this->capacity; i++)
	{
		this->elements[i] = EMPTY_POSITION;
	}

	for (int i = 0; i < j; i++)
	{
		position = this->main_hash_function(auxiliary_elements[i]);
		this->elements[position] = auxiliary_elements[i];
	}
}

// complexity O(capcity)
bool Bag::search(Telem element)
{
	int probe_number = 0;
	int position = -1;

	int aux_elem = abs(element);

	while (probe_number < this->capacity)
	{
		position = (this->first_hash_function(aux_elem) + probe_number * this->second_hash_function(aux_elem)) % this->capacity;
		if (this->elements[position] == EMPTY_POSITION)
		{
			return false;
		}
		else if (this->elements[position] != element)
		{
			probe_number++;
		}
		else if (this->elements[position] == element)
		{
			return true;
		}
	}
	return false;
}

// complexity O(capcity)
int Bag::nrOccurrences(Telem element)
{
	int probe_number = 0;
	int frequency = 0;
	int position = -1;
	int aux_elem = abs(element);

	while (probe_number < this->capacity)
	{
		position = (this->first_hash_function(aux_elem) + probe_number * this->second_hash_function(aux_elem)) % this->capacity;
		//std::cout << "brbr" <<this->elements[position] << std::endl;
		if (this->elements[position] == EMPTY_POSITION)
		{
			return frequency;
		}
		else if (this->elements[position] != element)
		{
			probe_number++;
		}
		else if (this->elements[position] == element)
		{
			frequency++;
			probe_number++;
		}
	}
	return frequency;
}

// complexity O(capcity)
bool Bag::remove(Telem element)
{
	int probe_number = 0;
	int position = -1;
	int aux_elem = abs(element);

	while (probe_number < this->capacity)
	{
		position = (this->first_hash_function(aux_elem) + probe_number * this->second_hash_function(aux_elem)) % this->capacity;
		if (this->elements[position] == EMPTY_POSITION)
		{
			return false;
		}
		else if (this->elements[position] != element)
		{
			probe_number++;
		}
		else if (this->elements[position] == element)
		{
			this->elements[position] = DELETED_POSITION;
			this->size_of_bag--;
			return true;
		}
	}
	return false;
}

// complexity Theta(capcity)
void Bag::print()
{
	for (int i = 0; i < this->capacity; i++)
	{
		std::cout << this->elements[i] << std::endl;
	}
}

int Bag::uniqueCount() const
{
	int i;
	int counter = this->size_of_bag;

	for (i = 0; i < this->capacity; i++)
	{
		int probe = 0;
		int k = i + (i + 1) * probe % this->capacity;
		int* probe_array = new int[probe];
		while (this->elements[k] != EMPTY_POSITION && probe < this->capacity-1)
		{
			for (int j = 0; j < probe; j++)
			{
				if (this->elements[k] == this->elements[j])
				{
					counter--;
					//counter
				}
				else
				{
					probe_array[probe] = this->elements[k];
				}
			}
			probe++;
			k = i + (i + 1) * probe % this->capacity;
			for (int j = 0; j < probe; j++)
			{
				std::cout << probe_array[j];
			}

		}
	}


	return counter;
}

#define UNIQUE -777777
#define NOT_UNIQUE 777777


/*
function uniqueCount2 (ht) is:
//pre: ht is a HashTable
//post: calculates the unique elems

	unique_elems : T[this->capacity];
	unique_arr : T[this->capacity];
	size : Integer
	i : Integer
	size <- 0;

	for i <- 0; this->capacity; 1
		unique_arr[i] <- UNIQUE;
		unique_elems[i] <- EMPTY_POSITION;
	end-for

	for i <- 0; this->capacity; 1
		if (this->elements[i] != EMPTY_POSITION && this->elements[i] != DELETED_POSITION)
			found <- 0;
			for j <- 0; size; 1
				if (unique_elems[j] = this->elements[i])
					unique_arr[j] <- NOT_UNIQUE;
					found <- 1;
					break;
				end-if
			end-for
			if (found = 0)
				unique_elems[size] <- this->elements[i];
				size <- size + 1;
			end-if
		end-if
	end-for

	unique_count <- 0;

	for i = 0; this->capacity; 1
		if (unique_arr[i] = UNIQUE && unique_elems[i] != EMPTY_POSITION)
			unique_count <- unique_count + 1
	end-for

	uniqueCount2 <- unique_count;


	complexity: O(m^2)
*/
int Bag::uniqueCount2() const
{
	int* unique_elems = new int[this->capacity];
	int* unique_arr = new int[this->capacity];
	int size = 0;

	for (int i = 0; i < this->capacity; i++)
	{
		unique_arr[i] = UNIQUE;
		unique_elems[i] = EMPTY_POSITION;
	}

	for (int i = 0; i < this->capacity; i++)
	{
		if (this->elements[i] != EMPTY_POSITION && this->elements[i] != DELETED_POSITION)
		{
			int found = 0;
			for (int j = 0; j <= size; j++)
			{
				if (unique_elems[j] == this->elements[i])
				{
					unique_arr[j] = NOT_UNIQUE;
					found = 1;
					break;
				}	
			}
			if (found == 0)
			{
				unique_elems[size] = this->elements[i];
				size++;
			}
		}
	}

	int unique_count = 0;

	for (int i = 0; i < this->capacity; i++)
	{
		if (unique_arr[i] == UNIQUE && unique_elems[i] != EMPTY_POSITION)
			unique_count++;
	}

	return unique_count;
}

// complexity Theta(1)
BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}


#include <assert.h>

void test_prime()
{
	assert(prime(5) == true);
	assert(prime(9) == false);
	assert(prime(15) == false);
	assert(prime(19) == true);
	assert(prime(7) == true);
	assert(prime(12) == false);
	assert(prime(37) == true);
}

void test_next_prime()
{
	assert(next_prime(17) == 37);
	assert(next_prime(5) == 11);
	assert(next_prime(12) == 29);
	assert(next_prime(30) == 61);
}