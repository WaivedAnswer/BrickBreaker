//NodeIterator.h
#ifndef _NODE_ITERATOR_H
#define _NODE_ITERATOR_H
#include "MenuNode.h"

class NodeIterator
{
	public:
		virtual void First() = 0;
		virtual void Next() = 0;
		virtual void Prev() = 0;
		virtual bool IsDone() const = 0;
		virtual MenuNode* CurrentNode() const = 0;
	protected:
		NodeIterator();
};
#endif
