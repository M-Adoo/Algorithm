//RB_Tree.hpp
//The code of red black trees
//2011/12/31    by Adoo
// The foundation :http://www.roading.org/?p=691

#ifndef RB_TREES_HPP
#define RB_TREES_HPP
#include<iterator>
#include<iomanip>
#include<deque>
enum RB_Color{
	red,
	black
};
template<typename Type>
class RB_Tree{
private:
	struct rb_node;
	class node_iterator;
public:
	typedef  node_iterator iterator;
	typedef const node_iterator const_iterator;

	RB_Tree(){
		_nil->_color=black;
		_root=_nil;
	};
	~RB_Tree()
	{
		for(iterator iter=begin(); iter !=end();)
		{
			eraser(iter++);
		}
		_root=_nil;
	}
	iterator begin(){
		return sub_min(_root);
	}
	iterator end(){
		return iterator(_nil);
	}
	static iterator sub_min(iterator iter){
			rb_node  *min=iter.pointer();
 			while(min->_left !=_nil)
			{
				min=min->_left;
			}
			return min;
	}
	iterator insert(Type value){
		rb_node *y=_nil;
		rb_node *z=new rb_node;            //create a node by the value
		//needn't set the z's color ,because red is rb_node's default color
		z->_value=value;
		z->_left=_nil;
		z->_right=_nil;

		rb_node* x=_root;                                      //x iterator from _root
		while(x !=_nil )
		{
			y=x;
			if(x->_value< z->_value)
				x=x->_right;
			else
				x=x->_left;
		}
		z->_parent=y;
		if(y==_nil)       //determine z should be y's left or right
			_root=z;
		else
			if(y->_value < z->_value)
				y->_right=z;
			else
				y->_left=z;
		
		rb_insert_fixup(z);   //restore the red black properties
		return z;
	}
	iterator eraser(iterator iter){
		rb_node* z=iter.pointer();
		rb_node* y=z;
		RB_Color y_color=y->_color;
		rb_node *x=NULL;

		if(z->_left==_nil ){ //case1: z's left child is nil
			x=z->_right;
			transplant(z, z->_right);
		}
		else{
			if(z->_right==_nil){// case2: z's right child is nil
				x=z->_left;
				transplant(z, z->_left);
			}
			else{//case3: both children of z are not nil 
				y=sub_min(z->_right).pointer();
				y_color=y->_color;
			    x=y->_right;
				if(y->_parent==z)
					x->_parent=y;
				else{
					transplant(y, y->_right);
					//link z's right subtree into y, only y isn't z's child;
					y->_right=z->_right;
					y->_right->_parent=y;
				}
				transplant(z, y);
				//link z's subtree into y.
				y->_left=z->_left;
				y->_left->_parent=y;
				y->_color=z->_color;
			}
		}
		iterator result = ++iterator(z);
		delete z;
		if(y_color==black)
			eraser_fixup(x);
		return result;
	};

private:
	void transplant(rb_node *u, rb_node *v){
		if(u->_parent == _nil)
		{
			_root=v;
		}
		else
			if(u== u->_parent->_left)
				u->_parent->_left=v;
			else
				u->_parent->_right=v;
		v->_parent=u->_parent;
	};
	void left_rotate(rb_node *x){
		rb_node*  y=x->_right;            //set y
		x->_right=y->_left;                 //turn y's left subtree into x's right subtree
		if(y->_left !=_nil)
			y->_left->_parent=x;         
		y->_parent=x->_parent;         //link y to x's parent
		if(x->_parent != _nil )
		{
			if(x->_parent->_left==x)
				x->_parent->_left=y;
			else
				x->_parent->_right=y;
		}
		else
			_root=y;
		y->_left=x;                               //put x on y's left
		x->_parent=y;
	}
	void right_rotate(rb_node *x)
	{
		rb_node* y=x->_left;            //set y;
		x->_left=y->_right;               //turn y's right subtree into x's left subtree
		if(y->_right != _nil)
			y->_right->_parent=x;
		y->_parent=x->_parent;        //link y to x's parent
		if(x->_parent != _nil)
		{
			if(x==x->_parent->_left)
				x->_parent->_left=y;
			else
				x->_parent->_right=y;
		}
		else
			_root=y;
		y->_right=x;            //put x on y's right;
		x->_parent=y;
	}
	void rb_insert_fixup(rb_node* z){
		while(z->_parent->_color==red){
			if(z->_parent==z->_parent->_parent->_left){
				rb_node* y=z->_parent->_parent->_right;
				if(y->_color==red){
					z->_parent->_color=black;
					y->_color=black;
					z->_parent->_parent->_color=red;
					z=z->_parent->_parent;
				}
				else{
					if(z==z->_parent->_right){
						z=z->_parent;
						left_rotate(z);
					}
					z->_parent->_color=black;
					z->_parent->_parent->_color=red;
					right_rotate(z->_parent->_parent);
				}
			}
			else{
				rb_node* y=z->_parent->_parent->_left;
				if(y->_color==red){
					z->_parent->_color=black;
					y->_color=black;
					z->_parent->_parent->_color=red;
					z=z->_parent->_parent;
				}
				else{
					if(z==z->_parent->_left){
						z=z->_parent;
						right_rotate(z);
					}
					z->_parent->_color=black;
					z->_parent->_parent->_color=red;
					left_rotate(z->_parent->_parent);
				}
			}
		}
		_root->_color=black;
	};;
	void eraser_fixup(rb_node* x){
		while(x != _root && x->_color ==black){
			if(x==x->_parent->_left){
				rb_node* w=x->_parent->_right;
				if(w->_color == red){               //case 1:  x's sbling w is red.
					x->_parent->_color=red;     
				    w->_color=black;
					left_rotate(x->_parent);       //convert case 1 to case 2.
				}
				else{//case 2 : x's sbling w is black.
					if(w->_left->_color == black && w->_right->_color == black){
						//case 2.1 : both children of w are black
						w->_color=red;
						x=x->_parent;
					}
					else{
						if(w->_left->_color==red && w->_right->_color==black){
							//case 2.2: w's left child is red and w's right child is black. 
							//we convert this case to case 2.3.
							w->_left->_color=black;
							w->_color=red;
							right_rotate(w);
							w=x->_parent->_right;
						}
						//case 2.3: w's right child is red;
						w->_color=x->_parent->_color;
						w->_parent->_color=black;
						w->_right->_color= black;
						left_rotate(x->_parent);
						x=_root; //terminate the loop;
					}
				}
			}
			else{
				rb_node* w=x->_parent->_right;
				if(w->_color == red){               
					x->_parent->_color=red;     
					w->_color=black;
					left_rotate(x->_parent);      
				}
				else{
					if(w->_right->_color == black && w->_left->_color == black){
						w->_color=red;
						x=x->_parent;
					}
					else{
						if(w->_right->_color==red && w->_left->_color == black){
							w->_right->_color=black;
							w->_color=red;
							left_rotate(w);
							w=x->_parent->_left;
						}
						w->_color=x->_parent->_color;
						w->_parent->_color=black;
						w->_left->_color= black;
						right_rotate(x->_parent);
						x=_root; //terminate the loop;
					}
				}
			}
		}
		x->_color=black;
	};

private:
	rb_node* _root;
public:
	static rb_node* _nil;
};

template<typename Type>
struct RB_Tree<Type>::rb_node
{
		Type _value;
		rb_node  *_left;
		rb_node  *_right;
		rb_node  *_parent;
		RB_Color _color;
		rb_node()
			:_value(Type()),_left(NULL),_right(NULL),_parent(NULL),_color(red)
		{};
	};

template<typename Type>
class RB_Tree<Type>::node_iterator: 
	public std::iterator<std::bidirectional_iterator_tag ,rb_node>
{
public:
	node_iterator(rb_node* n): _node(n){};

 Type& operator* () const{
		return _node->_value;
	};

	rb_node* operator ->()const
	{
		return _node;
	};

	node_iterator operator++ ()
	{
		if(_node==RB_Tree<Type>::_nil)
			return _node;
		if(_node->_right!=RB_Tree<Type>::_nil)
		{
			*this=RB_Tree<Type>::sub_min(_node->_right);
		}
		else
		{
			rb_node *parent=_node->_parent;
			while(parent !=RB_Tree<Type>::_nil&& _node==parent->_right)
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

	bool operator ==( node_iterator r_iter)
	{
	   return _node == r_iter._node;
	};

	bool operator !=( node_iterator r_iter){
		 return _node != r_iter._node;
	}

	rb_node* pointer()
	{
		return _node;
	}
private:
	rb_node* _node;
};
#endif
//¸÷ÖÖ