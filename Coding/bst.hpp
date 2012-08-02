//BST.hpp     A data structure which be called  binary search tree 
//  2011/12/17   By Adoo
// homepage:  http://www.roading.org
#ifndef BST_HPP
#define BST_HPP
#include<iterator>

// The binary search tree template
template<typename T>
class BST{
private:
	struct node ;
	class node_iterator;
public:
	typedef node_iterator iterator;
	typedef const node_iterator const_iterator;

	BST():_root(NULL){};

	iterator begin(){
		return node_iterator(_root).min();
	}

	iterator end(){
		return iterator(NULL);
	}
	
	iterator find(T value){
		node* x=_root;
		while(x!=NULL && value != x->_value)
		{
			if(value < x->_value)
				x=x->_left;
			else
				x=x->_right;
		}
		return x;
	}

	iterator insert(T value)
	{
		node  *z=new node;
		z->_value=value;
		if(_root == NULL )
			return _root=z;
		node* p=NULL;
		node* x=_root;
		while(x != NULL)
		{
			p=x;
			if(z->_value  <  x->_value)
				x=x->_left;
			else
				x=x->_right;
		}
		z->_parent=p;
		if(z->_value < p->_value )
			p->_left=z;
		else
			p->_right=z;
		return z;
	}

	template<typename iter_type>
	iterator insert(iter_type iter)
	{
		return insert(*iter);
	}
	void  eraser(iterator iter)
	{
		if(iter->_left == NULL)
		{
			transplant(iter,iter->_right);
		}
		else 
			if(iter->_right==NULL)
			{
				transplant(iter,iter->_left);
			}
			else{
				iterator isuc=iterator(iter->_right).min();
				if(isuc->_parent != iter.pointer())
					{
						transplant(isuc,isuc->_right);
						isuc->_right=iter->_right;
						isuc->_right->_parent=isuc.pointer();
				}
				transplant(iter,isuc);
				isuc->_left=iter->_left;
				isuc->_left->_parent=isuc.pointer();
			}
			delete iter.pointer();
	}

	void eraser(iterator ibeg, iterator iend){
		while( ibeg !=iend )
		{
			eraser(ibeg++);
		}
	}

    int eraser(T value){
		iterator iter=find(value);
		while(iter != end())
		{
			eraser(iter);
			iter =find(value);
		};
	}	

	~  BST()
	{
		iterator iter=begin();
		eraser(begin(),end());
	}
	
private:
	node*  _root;
	void transplant(iterator ito , iterator  ifrom)
	{//transplate(), which replaces one subtree as a child of its parent with another subtree. 
		if(ito->_parent == NULL )
			_root=ifrom.pointer();
		else
			if(ito.pointer() == ito->_parent->_left )
				 ito->_parent->_left=ifrom.pointer();
			else
				 ito->_parent->_right=ifrom.pointer();
		if(ifrom != NULL)
	    	ifrom->_parent=ito->_parent;
	}
	
};


//The node for binary search tree
template<typename T>
struct BST<T>::node{
	node():_value(T()),_left(NULL),_right(NULL),_parent(NULL){};
	T  _value;
	node  *_left;
	node  *_right;
	node  *_parent;
	// I should implement some override operator at here , but  I omit these. 
};

template<typename T>
class BST<T>::node_iterator: public std::iterator<std::bidirectional_iterator_tag ,node>
{
public:
	node_iterator(node* n): _node(n){};

	T& operator* (){
		return _node->_value;
	}

	node* operator ->()
	{
		return _node;
	}

	node_iterator operator++ ()
	{
		if(_node==NULL)
			return NULL;
		if(_node->_right!=NULL)
		{
			*this=node_iterator(_node->_right).min();
		}
		else
		{
			node *parent=_node->_parent;
			while(parent != NULL && _node==parent->_right)
			{
				_node=parent;
				parent=parent->_parent;
			}
			_node=parent;
		}
		return *this;
	}
	
	node_iterator operator++(int){
		node_iterator ret(*this);
		++*this;
		return ret;
	}


	node_iterator min()
	{
		node  *min=_node;
			while(min->_left != NULL)
			{
				min=min->_left;
			}
			return min;
	}

	bool operator ==( node_iterator r_iter)
	{
		if(_node ==r_iter._node )
				return true;
		if(_node != NULL && r_iter._node != NULL)
				 return _node->_value==r_iter->_value && _node->_left==r_iter->_left && _node->_right==r_iter->_right;
		else
			return false;
	}

	bool operator !=(const node_iterator r_iter){
		return !operator==(r_iter);
	}

	node* pointer()
	{
		return _node;
	}
private:
	node* _node;
};



#endif