//! \file QueueList_TODO.h
//! \brief Defines the <code>fullsail_ai::data_structures::QueueList</code> class template
//! implementation.
//! \author Cromwell D. Enage
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

#include "QueueList.h"

namespace fullsail_ai { namespace fundamentals {

	//! \TODO
	//!   - Complete the definition of the <code>QueueList::Iterator</code> pre-increment operator.
	/*template <typename T>
	QueueList<T>::Iterator()
	{

	}*/
	//!   - Complete the definition of the <code>QueueList::Iterator</code> dereference operator.
	//!   - Define the <code>QueueList</code> constructor.
	//! \brief Default constructor.
	template <typename T>
	QueueList<T>::QueueList()
	{
		front = nullptr;
		back = nullptr;
	}
	//!   - Define the <code>QueueList</code> destructor.
	//! \brief Cleans up all internal memory.
	template <typename T>
	QueueList<T>::~QueueList()
	{
		/*if (front != nullptr) {

			Node* tempH = front;
			
			Node* tempHN = tempH->next;
			delete tempH;
			tempH = tempHN;

			front = nullptr;
		}*/
		removeAll();
	}
	//!   - Define the <code>QueueList</code> methods.
	

	template <typename T>
	typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
	{
		// TODO: Complete the definition of this operator.
		/*if (front != nullptr)
		{
			front = front->next;
		}*/
		//return *this;
		//this->currentNode = this->currentNode->next;
		front = front->next;
		return (*this);
	}

	template <typename T>
	T QueueList<T>::Iterator::operator*() const
	{
		// TODO: Complete the definition of this operator.
		//Iterator temp2 = *this;
		//return temp2.front->data;
		//return this->currentNode->data;
		return this->front->data;
	}

	template <typename T>
	bool QueueList<T>::isEmpty() const
	{
		//! \brief Adds the specified element to this <code>%QueueList</code>.
		//!
		//! \param   element  the specified element.
		//!
		//! \post
		//!   - <code>contains()</code> will return <code>true</code> if \a element is passed in.
		if (front == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	
	template <typename T>
	void QueueList<T>::enqueue(T element)
	{
		//! \brief Returns the first element in this <code>%QueueList</code>.
		//!
		//! \pre
		//!   - <code>isEmpty()</code> returns <code>false</code>.
		
		/*Node* temp = back;
		
		temp->next = element;
		*/
		/*Node* temp = back;
		back = back->next;
		back->data = element;
		delete temp;*/
		
		Node* temp = new Node(element);
		if (isEmpty())
		{
			front = temp;
			back = front;
		}
		else
		{
			if (front->next == nullptr)
			{
				front->next = temp;
			}
			back->next = temp;
			back = temp;//
		}

		/*if (isEmpty())
		{
			front = new Node(element);
			back = front;
		}
		else
		{
			Node* help = new Node(element);
			if (front->next == nullptr)
				front->next = help;
			back->next = help;
			back = help;
		}*/

	}

	template <typename T>
	T QueueList<T>::getFront() const
	{
		//! \brief Removes the first element from this <code>%QueueList</code>.
		//!
		//! \pre
		//!   - <code>isEmpty()</code> returns <code>false</code>.
		//! \post
		//!   - <code>contains()</code> will return <code>false</code> if the removed element
		
		return front->data;
	}

	template <typename T>
	void QueueList<T>::dequeue()
	{
		//! \brief Removes all elements from this <code>%QueueList</code>.
		//!
		//! \post
		//!   - <code>isEmpty()</code> will return <code>true</code>.
		//! 
		//if (front == NULL)
		//{
		//	//front->data = NULL;
		if (front != nullptr)
		//if (isEmpty())
		{
			if (back == front)
			{
				delete front;
				front = nullptr;
				back = nullptr;
			}
			else
			{
				Node* temp = front->next;
				//delete temp;
				delete front;
				front = temp;
			}
		}
	}
	
	template <typename T>
	void QueueList<T>::removeAll()
	{
		//! \brief Returns <code>true</code> if this <code>%QueueList</code>
		//! possesses the specified element, <code>false</code> otherwise.
		/*Node* temp, store;
		temp = front;
		while (temp != nullptr)
		{
			store = temp->next;
			delete temp;
			temp = store;
		}*/
		while (front)
		{
			dequeue();
		}

		front = nullptr;
		back = nullptr;
	}

	template <typename T>
	bool QueueList<T>::contains(T element) const
	{
		//! \brief Finds the first occurrence of the specified element and
		//! removes it from the <code>%QueueList</code>.
		//!
		//! \pre
		//!   - <code>isEmpty()</code> returns <code>false</code>.
		//front->data = element;
		Node* temp = front;
		//while (front)
		////while (!isEmpty())
		//{
		//	if (temp->data == element)
		//	{
		//		return true;
		//		temp = temp->next;
		//	}
		//	/*else
		//	{
		//		return false;
		//	}*/
		//}
		//return false;

		while (temp)
		{
			if (temp->data == element)
				return true;
			temp = temp->next;
		}
		return false;
	}
	
	template <typename T>
	void QueueList<T>::remove(T element)
	{

		//// If the head is to be deleted
		//if (front->data == element)
		//{
		//	delete front;
		//	front = front->next;
		//	return;
		//}

		//// If there is only one element in the list
		//if (front->next == NULL)
		//{
		//	// If the head is to be deleted. Assign null to the head
		//	if (front->data == element)
		//	{
		//		delete front;
		//		front = NULL;
		//		return;
		//	}
		//	return;
		//}

		//// Else loop over the list and search for the node to delete
		//Node* temp = front;
		//while (temp->next != NULL)
		//{
		//	// When node is found, delete the node and modify the pointers
		//	if (temp->next->data == element)
		//	{
		//		Node* temp_ptr = temp->next->next;
		//		delete temp->next;
		//		temp->next = temp_ptr;
		//		return;
		//	}
		//	temp = temp->next;
		//}
		//
		//Node* temp = front;
		////Traverse the list, starting at the beginning;
		//while (temp != NULL) {
		//	temp = temp->next;
		//}
		//while (there are nodes to traverse)
		//{
		//	if (the node matches the data)
		//	if (temp->data == element)
		//	{
		//		//remove the node, adjust the list pointers, and exit;
		//		delete front;
		//		front = front->next;
		//		return;
		//	}
		//}

		/*Node* temp, store;
		temp = front;
		while (temp != nullptr)
		{
			if (temp->data == element)
			{
				store = temp->next;
				delete temp;
				temp = store;
			}
			store = temp->next;
			
		}*/
		Node* temp = front;
		Node* previous;
		while (temp)
		{
			if (temp->data == element)
			{
				if (temp == front && front == back) // last element
				{
					front = nullptr;
					back = nullptr;
					delete temp;
				}
				else if (temp == front) // front element
				{
					front = front->next;
					delete temp;
				}
				else if (temp == back) // back element
				{
					previous->next = nullptr;
					back = previous;
					delete temp;
				}
				else // middle element
				{
					previous->next = temp->next;
					delete temp;
				}

				break;
			}

			previous = temp;
			temp = temp->next;
		}
	}
	
	

}}  // namespace fullsail_ai::fundamentals

#endif  // _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

