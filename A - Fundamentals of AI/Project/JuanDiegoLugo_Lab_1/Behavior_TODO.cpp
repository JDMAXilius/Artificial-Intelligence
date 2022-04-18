//! \file Behavior_TODO.cpp
//! \brief Implements the <code>fullsail_ai::fundamentals::Behavior</code> abstract class.
//! \author Jeremiah Blanchard with code from Cromwell D. Enage

// #include <queue>   NOTE: Only use if your QueueList is not working
#include <stack>
#include <queue>
#include "Behavior.h"
#include"../QueueList/QueueList.h"

namespace fullsail_ai { namespace fundamentals {

	// DO NOT Edit or Use these two variables for any reason, it is for memory leak check purposes only.
	unsigned Behavior::createdCount = 0;
	unsigned Behavior::destroyedCount = 0;

	unsigned Behavior::getCreatedCount()
	{
		return createdCount;
	}

	unsigned Behavior::getDestroyedCount()
	{
		return destroyedCount;
	}

	Behavior::Behavior(char const* _description)
	{
		description = _description;
	}

	char const* Behavior::toString() const
	{
		return description;
	}

	// DO NOT edit this function, it is supposed to just return false
	bool Behavior::isLeaf() const
	{
		return false;
	}

	//! \brief Returns the number of child nodes stored in this <code>%Behavior</code>.
	DLLEXPORT size_t Behavior::getChildCount() const
	{
		//return createdCount++;
		return this->children.size();
	}

	//! \brief Returns a pointer to the index-th child node stored in this
	//! <code>%Behavior</code>.
	//!
	//! \pre      \a index <code>\< getChildCount()</code>
	//! \post     <code>NULL != getChild(index)</code>
	DLLEXPORT Behavior* Behavior::getChild(size_t index)
	{
		/*for (size_t i = 0; i < children.size(); i++)
		{
			return children[index];
		}*/
		if (index < getChildCount())
		{

		}
			return children[index];
	}
	DLLEXPORT Behavior const* Behavior::getChild(size_t index) const
	{
		if (index < getChildCount())
		{

		}
			return children[index];
	}

	//! \brief Adds a child to the child behaviors of this <code>%Behavior</code>.
	//!
	//! \pre      \a child <code>\!= NULL</code>
	DLLEXPORT void Behavior::addChild(Behavior* child)
	{
		children.push_back(child);
		child->parent = this;
	}

	//=====================
	//  TRAVERSAL METHODS
	//=====================

	//! \brief Traverses the root and all sub-nodes breadth-first.
	//!
	//! \param   dataFunction  a single-argument function that accepts the traversed node
	//!                        a valid argument.
	//!
	//! \pre     <code>NULL !=</code> \a this
	DLLEXPORT void Behavior::breadthFirstTraverse(void (*dataFunction)(Behavior const*)) const
	{
		//queue.enqueue(rootNode);
		//	while (queue.notEmpty())
		//	{
		//		Node node = queue.popfront();
		//		function(node);
		//		queue.enqueue(each child of node);
		//	}
		
		//QueueList<const Behavior*> queue;
		std::queue<const Behavior*> queue;
		//Behavior const* node;
		//queue.enqueue(this);
		queue.push(this);
		while (!queue.empty())
		{
			const Behavior* node;
			//node = queue.getfront();
			node = queue.front();
			//queue.dequeue();
			queue.pop();
			dataFunction(node);
			for (size_t i = 0; i < node->getChildCount(); i++)
			{
				//queue.enqueue(node->children[i]);
				queue.push(node->children[i]);
			}
		}
	}

	//! \brief Traverses the root and all sub-nodes in pre-order fashion.
	//!
	//! \param   dataFunction  a single-argument function that accepts the traversed node
	//!                        a valid argument.
	//!
	//! \pre     <code>NULL !=</code> \a this
	DLLEXPORT void Behavior::preOrderTraverse(void (*dataFunction)(Behavior const*)) const
	{
		//node is just datafunction(this)
		//then we need to loop through our children
		//so children[0]->preorderTraverse(dataFunction)
		//same as post just the datafunction(this) is in a different spot
		
		size_t size = children.size();
		dataFunction(this);
		for (size_t i = 0; i < size; i++)
		{
			children[i]->preOrderTraverse(dataFunction);
		}
	}

	//! \brief Traverses the root and all sub-nodes in post-order fashion.
	//!
	//! \param   dataFunction  a single-argument function that accepts the traversed node
	//!                        a valid argument.
	//!
	//! \pre     <code>NULL !=</code> \a this
	DLLEXPORT void Behavior::postOrderTraverse(void (*dataFunction)(Behavior const*)) const
	{
		size_t size = children.size();
		for (size_t i = 0; i < size; i++)
		{
			children[i]->postOrderTraverse(dataFunction);
		}
		dataFunction(this);
	}

	/*breadthFirst(Node* root)
	{
		if (!root)
			return NULL;

		list nodeQueue;
		nodeQueue.enqueue(root);

		while (!nodeQueue.empty())
		{
			Node* current = nodeQueue.dequeue();

			if this node is the goal, return;

			for each child of current :
			{
				nodeQueue.enqueue(child);
			}
		}
		return NULL;
	}*/

	//! \TODO
	//!   - Implement the <code>Behavior</code> methods.
	
	////Preorder Traversal
	//void traverse(Node node, F function)
	//{
	//	function(node);
	//	traverse(each child of node);
	//}
	////Postorder Traversa
	//void traverse(Node node, F function)
	//{
	//	traverse(each child of node);
	//	function(node);
	//}
	////Breadth-First Traversal
	//traverse(Node rootNode, F function)
	//{
	//	queue.enqueue(rootNode);
	//	while (queue.notEmpty())
	//	{
	//		Node node = queue.popfront();
	//		function(node);
	//		queue.enqueue(each child of node);
	//	}
	//}

	//size_t getChildCount() const;
	//Behavior* getChild(size_t i);
	//Behavior const* getChild(size_t i) const;
	//void addChild(Behavior* child;
	//void breadthFirstTraverse(void (*dataFunction)(Behavior const*))const;
	//void preOrderTraverse(void (*dataFunction)(Behavior const*))const;
	//void postOrderTraverse(void (*dataFunction)(Behavior const*))const;

}}  // namespace fullsail_ai::fundamentals
