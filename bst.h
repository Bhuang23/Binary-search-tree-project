
#pragma once

#include <iostream>
using namespace std;
template<typename TKey, typename TValue>
class binarysearchtree
{
	private:
	struct NODE
	{
		TKey Key;
		TValue Value;
		NODE* Left;
		NODE* Right;
	};
	NODE* Root;  // pointer to root node of tree (nullptr if empty)
    int   Size;  // # of nodes in the tree (0 if empty)
	void _inorder(NODE* cur)
    {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }
	void copy(NODE * othernode)//copy constructor helper function
    {
			if(othernode == nullptr)
			{
				return;
			}
			else
			{
				insert(othernode->Key, othernode->Value);
				copy(othernode->Left);
				copy(othernode->Right);
			}
		}
    void _destructor(NODE* cur)//destructor helper function
    {
    if (cur == nullptr)
      return;
    else
    {
      _destructor(cur->Left);
      _destructor(cur->Right);
	  delete cur;
    }
  }
	public:
	binarysearchtree()//constructor
	{
		Root = nullptr;
		Size = 0;
	}
	virtual ~binarysearchtree()//destructor
	{
		//
		// TODO:
		//
		_destructor(Root);
	}
	binarysearchtree(binarysearchtree& other)//copy constructor
	{
		Root = nullptr;
		Size = 0;
		copy(other.Root);
	}
	int height()//height function
	{
		//
		// TODO:
		//
		return _height(Root);
	}

	int _height(NODE * cur)//height helper function
	{
		if(cur == nullptr)
		 {
			return -1;
		 }
		 else
		 {
			int heightl = _height(cur->Left);
			int heightr = _height(cur->Right);
			if(heightl > heightr)
			{
			   return heightl+1;
			}
			else
			{
			   return heightr+1;
			}
		 }
	}
	void insert(TKey key, TValue value)// insert function with parameters Tkey key, TValue value
	{
		NODE* prev = nullptr;
		NODE* cur = Root;

		//
		// 1. Search to see if tree already contains key:
		//
		while (cur != nullptr)
		{
		  if (key == cur->Key)  // already in tree
			return;

		  if (key < cur->Key)  // search left:
		  {
			prev = cur;
			cur = cur->Left;
		  }
		  else
		  {
			prev = cur;
			cur = cur->Right;
		  }
		}//while
		//
		// 2. if we get here, key is not in tree, so allocate
		// a new node to insert:
		// 
		//
		// TODO: allocate a new node, store key and value, initialize
		// pointer fields:
		//
		NODE *temp =  new NODE(); 
		temp->Key = key; 
		temp->Value = value;
		temp->Left = temp->Right = NULL; 
		//
		// 3. link in the new node:
		//
		// NOTE: cur is null, and prev denotes node where
		// we fell out of the tree.  if prev is null, then
		// the tree is empty and the Root pointer needs 
		// to be updated.
		//
		if(prev == nullptr)
		{
		   Root = temp;
		}
		else if( key > prev->Key)
		{
			  prev->Right = temp;
		}
	    else
	    {
			  prev->Left = temp;
	    }
		//
		// TODO: link in the new node, updating Root 
		// pointer as appropriate
		//
		// 
		// 4. update size and we're done:
		//
		Size++;
		//
		// TODO:
		//
    }
	TValue* search(TKey key)//search function with parameter Tkey key and returns reference to the node's Value
	{
		NODE* cur = Root;

		while (cur != nullptr)
		{
		  if (key == cur->Key)  // already in tree
			return &(cur->Value);

		  if (key < cur->Key)  // search left:
		  {
			cur = cur->Left;
		  }
		  else
		  {
			cur = cur->Right;
		  }
		}//while  

		// if get here, not found
		return nullptr;

	}
	  // 
	  // size:
	  //
	  // Returns the # of nodes in the tree, 0 if empty.
	  //
	  int size()
	  {
		return Size;
	  }
	  void inorder()//prints the tree inorder
	  {
		 cout << "Inorder: ";

		 _inorder(Root);

		 cout << endl;
	  }
	  void clear()//empties the tree
	  {
			//
			// Re-initialize root pointer and size to "empty":
			//
			_destructor(Root);
			Root = nullptr;
			Size = 0;
	  }

};