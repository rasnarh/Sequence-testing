/****************************************************************
* NAME        : RASNA RAHMAT HUSAIN
* ASSIGNMENT  : 10
* FILE NAME   : Sequence.cpp
* DATE        : 06/16/2019
* INSTRUCTOR  : David Harden
* DESCRIPTION : This file contains the Class definitions for
*               Sequence class.
*
*******************************************************************/


#include <iostream>
#include <assert.h>
#include "sequence.h"

using namespace std;


namespace cs_sequence
{



	Sequence::Sequence()
	{
		numItems = 0;
		headPtr = NULL;
		tailPtr = NULL;
		cursor = NULL;
		precursor = NULL;
	}
	// postcondition : The Sequence has been initialized to an empty
	//                 Sequence.





	void Sequence::clear() 
	{
		node* remove_node = headPtr;

		while (remove_node != NULL)
		{
			remove_node = remove_node->next;
			delete headPtr;
			headPtr = remove_node;
		}

		headPtr = NULL;
		tailPtr = NULL;
		cursor = NULL;
		precursor = NULL;
		numItems = 0;

	}





	void Sequence::copy(const Sequence &s) 
	{
		node* new_node = s.headPtr;


		while (new_node != NULL)
		{
			attach(new_node->data);
			new_node = new_node->next;
		}
	}




	Sequence::~Sequence() 
	{
		clear();
	}




	Sequence::Sequence(const Sequence &s) :Sequence() 
	{
		copy(s);
	}





	void Sequence::operator=(const Sequence &s)
	{

		if (this == &s) 
			return;
		clear();

		numItems = 0;
		int index = 1;

		for (cursor = s.headPtr; cursor != s.cursor; cursor = cursor->next)
		{
			index++;
		}

		copy(s);
		cursor = headPtr;

		if (index == 1)
		{
			precursor = NULL;
		}
		else
		{
			precursor = headPtr;
		}
		numItems = s.numItems;
	}




	void Sequence::start()
	{
		if (headPtr == NULL)
		{
			cursor = NULL;
			precursor = NULL;
		}

		else
		{
			// set cursor to first item in the sequence
			cursor = headPtr;
			precursor = NULL;
		}
	}
	// postcondition : The first item in the Sequence becomes the 
	//                 current item (but if the Sequence is empty, 
	//                 then there is no current item).







	void Sequence::advance()
	{
		assert(is_item());


		if(is_item())
		{
			precursor = cursor;
			cursor = cursor->next;
		}
		else
		{
			cursor = NULL;
		}
	}
	// precondition  : is_item() returns true
	// Postcondition : If the current item was already the last 
	//                 item in the Sequence, then there is no 
	//                 longer any current item. Otherwise, the 
	//                 new current item is the item immediately 
	//                 after the original current item.






	
	void Sequence::insert(const value_type& entry)
	{
		node* new_node = new node;
		new_node->data = entry;
		numItems++;

		if (cursor == headPtr || cursor == nullptr) 
		{
			// insert at front (or into empty list).
			new_node->next = headPtr;         // precursor remains nullptr.

			headPtr = new_node;

			if (numItems == 1)
			{
				tailPtr = new_node;
			}
		}

		else 
		{
			// inserting anywhere else
			new_node->next = cursor;  
			
			// tailPtr, headPtr and precursor don't change.
			precursor->next = new_node;

		}

		cursor = new_node;

	}
	// Postcondition : A new copy of entry has been inserted 
	//                 in the Sequence before the current item. 
	//                 If there was no current item, then the
	//                 new entry has been inserted at the front.
	//                 In either case, the new item is now the
	//                 current item of the Sequence.




	
	void Sequence::attach(const value_type& entry)
	{
		node* new_node = new node;

		new_node->data = entry;
		new_node->next = NULL;
		numItems++;



		if (headPtr == NULL)
		{
			new_node->next = NULL;
			headPtr = new_node;
			tailPtr = new_node;
			cursor = new_node;
		}

		else if (cursor == NULL)
		{

			tailPtr->next = new_node;
			precursor = tailPtr;
			cursor = new_node;
			tailPtr = new_node;
		}

		else if (tailPtr == NULL)
		{
			headPtr = new_node;
			tailPtr = new_node;
			cursor = new_node;
		}


		else if (cursor == tailPtr)
		{
			tailPtr->next = new_node;
			precursor = tailPtr;
			cursor = new_node;
			tailPtr = new_node;
		}
		else
		{
			new_node->next = cursor->next;
			cursor->next = new_node;
			precursor = cursor;
			cursor = new_node;
		}		
	}

	// Not required this week
	// Postcondition : A new copy of entry has been inserted in
	//                 the Sequence after the current item. If
	//                 there was no current item, then the new
	//                 entry has been attached to the end of the
	//                 Sequence. In either case, the new item is
	//                 now the current item of the Sequence.





	void Sequence::remove_current()
	{
		assert(cursor != NULL);

		if (is_item())
		{
			if (precursor == NULL)
			{
				headPtr = cursor->next;
				numItems--;

				if (cursor->next == NULL)
				{
					tailPtr = NULL;
				}

				delete cursor;
				cursor = headPtr;
			}

			else
			{
				precursor->next = cursor->next;
				numItems--;

				if (cursor->next == NULL)
				{
					tailPtr = precursor;
				}

				delete cursor;

				if (precursor == NULL)
				{
					start();
				}

				else
				{
					cursor = precursor->next;
				}
			}

		}

	}


	// Not required this week
	// Precondition  : is_item returns true.
	// Postcondition : The current item has been removed from the
	//                 Sequence.  If the item removed was the last
	//                 item in the Sequence, then there is now no
	//                 current item.  Otherwise, the item that was
	//                 after the removed item is now the current
	//                 item.
	





	Sequence::size_type Sequence::size() const
	{
		return numItems;
	}
	// Postcondition : Returns the number of items in the Sequence.






	bool Sequence::is_item() const
	{
		if (cursor != NULL) 
		{
			return true;
		}

		return false;
	}
	// Postcondition : A true return value indicates that there is 
	//                 a valid "current" item that may be retrieved 
	//                 by the current member function (listed below).
	//                 A false return value indicates that there is 
	//                 no valid current item.





	Sequence::value_type Sequence::current()
	{
		if (is_item())
		{
			return cursor->data;
		}
		else

		{
			return -1;
		}
	}
	// Precondition  : is_item() returns true
	// Postcondition : The current item in the Sequence is returned.
}