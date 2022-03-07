#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<bits/stdc++.h>
#include <stack>

//--------------Constructor and clear----------------
// o means red and 1 means black


Dictionary::Dictionary()
 {
	nil=new Node("",0);
	nil->left=nil;
	nil->right=nil;
	nil->color=1;
	root=nil;
	current=nil;
	num_pairs=0;
 }
Dictionary::Node::Node(keyType k, valType v)
{
  key=k;
  val=v;
  left=NULL;
  right=NULL;
  parent=NULL;
  color=0;
}

Dictionary::Dictionary(const Dictionary& D)
{
		nil=new Node("",0);
		nil->left=nil;
		nil->right=nil;
		nil->color=1;
		root=nil;
		current=nil;
		num_pairs=0;
		   Dictionary &ref=const_cast <Dictionary &>(D);
		   ref.begin();
		   while(ref.current!=ref.nil)
		   {
			   setValue(ref.current->key,ref.current->val);
			   ref.next();
		   }
}
// clear()
 // Resets this Dictionary to the empty state, containing no pairs.
 void Dictionary::clear()
 {
	 	begin();
	   while(current!=nil)
	   {
		   setValue(current->key,current->val);
		   remove(current->key);
		   begin();
	   }
		nil=new Node("",0);
		nil->left=nil;
		nil->right=nil;
		nil->color=1;
		root=nil;
		current=nil;
		num_pairs=0;
 }

Dictionary::~Dictionary(){
     	begin();
	   while(current!=nil)
	   {
		   setValue(current->key,current->val);
		   remove(current->key);
		   begin();
	   }

}
//-----------------------------------------Helper Function ------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const
{
    if(R!=nil)
    {
    	inOrderString(s,R->left);
    	s=s+R->key+" : "+std::to_string(R->val)+"\n";
    	inOrderString(s,R->right);
    }
}
void Dictionary::preOrderString(std::string& s, Node* R) const
{
    if(R!=nil)
    {
    	s=s+R->key+"\n";
    	preOrderString(s,R->left);
    	preOrderString(s,R->right);
    }
}

//

Dictionary::Node* Dictionary::search(Node* R, keyType k) const
{
	    if (R == nil || R->key == k)
	       return R;

	    if (R->key < k)
	       return search(R->right, k);

	    return search(R->left, k);
}


//

Dictionary::Node* Dictionary::findMax(Node* N)
{
	Node *x=N;
if(x!=nil)
{
while(x->right!=nil)
{
x=x->right;
}
}
return x;
}
Dictionary::Node* Dictionary::findMin(Node* N)
{
	Node *x=N;
while(x!=nil && x->left!=nil)
{
x=x->left;
}
return x;
}

Dictionary::Node* Dictionary::findNext(Node* N)
{
	if (N == nil) {
	    return nil;
	  }
	  if(N->right!=nil)
	  {
         N=findMin(N->right);
	  }
	  else
	  {
		  auto parent = N->parent;
		  while (parent != nil && N == parent->right) {
		         N = parent;
		         parent = parent->parent;
		       }
		       N = parent;
	  }
return N;
}
Dictionary::Node* Dictionary::findPrev(Node* N)
{
	if (N == nil)
	{
		    return nil;
		  }
		  if(N->left!=nil)
		  {
	         N=findMax(N->left);
		  }
		  else
		  {
			  auto parent = N->parent;
			  while (parent != nil && N == parent->left) {
			         N = parent;
			         parent = parent->parent;
			       }
			       N = parent;
	}
	return N;
}

//------------------------------------------------------- RBT Helper function--------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N)
{
	Node* y=N->right;

	N->right=y->left;
	if(y->left!=nil)
	{
		y->left->parent=N;
	}

	y->parent=N->parent;
	if(N->parent==nil)
	{
          root=y;
	}
	else if(N==N->parent->left)
	{
	N->parent->left=y;
	}
	else
	{
		N->parent->right=y;
	}
   y->left=N;
   N->parent=y;

}

// RightRotate()
void Dictionary::RightRotate(Node* N)
{
	Node * y=N->left;
	N->left=y->right;
	if(y->right !=nil)
	{
	y->right->parent=N;
	}
	y->parent=N->parent;
	if(N->parent==nil)
	{
	 root=y;
	}
	else if(N==N->parent->right)
	{
	 N->parent->right=y;
	}
	else
	{
	  N->parent->left=y;
	}
	y->right=N;
	N->parent=y;
}

// RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N)
   {
          while(N->parent->color==0)
          {
               if(N->parent==N->parent->parent->left)
               {
                   Node* y=N->parent->parent->right;
                   if(y->color==0)
                   {
                	   N->parent->color=1;
						 y->color=1;
						 N->parent->parent->color=0;
						 N=N->parent->parent;
                   }
                   else
                   {
                	   if(N==N->parent->right)
					  {
						N=N->parent;
						LeftRotate(N);
					  }
					  N->parent->color=1;
					  N->parent->parent->color=0;
					  RightRotate(N->parent->parent);
                   }
               }
               else
               {
            	  Node* y=N->parent->parent->left;
            	  if(y->color==0)
            	  {
            		N->parent->color=1;
            		 y->color=1;
            		 N->parent->parent->color=0;
            		 N=N->parent->parent;
            	  }
            	  else
            	  {
            		  if(N==N->parent->left)
            		  {
            			N=N->parent;
            			RightRotate(N);
            		  }
            		  N->parent->color=1;
            		  N->parent->parent->color=0;
            		  LeftRotate(N->parent->parent);

            	  }

               }
          }
          root->color=1;
   }
   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v)
   {
	   if(u->parent==nil)
	   {
		root=v;
	   }
	   else if(u==u->parent->left)
	   {
		u->parent->left=v;
	   }
	   else
	   {
		   u->parent->right=v;
	   }
	   v->parent=u->parent;
   }
   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N)
   {
    while(N!=root && N->color==1)
    {
        if(N==N->parent->left)
        {
			Node* w=N->parent->right;
			if(w->color==0)
			{
			   w->color=1;
			   N->parent->color=0;
			   LeftRotate(N->parent);
			   w=N->parent->right;
			}
			if(w->left->color==1 && w->right->color==1)
			{
			w->color=0;
			N=N->parent;
			}
			else
			{
				if(w->right->color==1)
				{
				w->left->color=1;
				w->color=0;
				RightRotate(w);
				w=N->parent->right;
				}
				w->color=N->parent->color;
				N->parent->color=1;
				LeftRotate(N->parent);
				N=root;
			}
        }
        else
        {
        	Node* w=N->parent->left;
			if(w->color==0)
			{
				  w->color=1;
				   N->parent->color=0;
				   RightRotate(N->parent);
				   w=N->parent->left;
			}
			if(w->right->color==1 && w->left->color==1)
			{
		                 w->color=0;
		                 N=N->parent;
			}
			else
			{
               if(w->left->color==1)
               {
            	   w->right->color=1;
            	   w->color=0;
            	   LeftRotate(w);
            	   w=N->parent->left;
               }
               w->color=N->parent->color;
               N->parent->color=1;
               w->left->color=1;
               RightRotate(N->parent);
               N=root;
			}
        }
    }
    N->color=1;
   }

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N)
   {
	     Node* y=N;
	     int y_original_color=y->color;
	     Node* x=nil;
	     if(N->left==nil)
	     {
	         x=N->right;
	         RB_Transplant(N,N->right);
	     }
	     else if(N->right==nil)
	     {
	           x=N->left;
	           RB_Transplant(N,N->left);
	     }
	     else
	     {
	          y=findMin(N->right);
	          y_original_color=y->color;
	          x=y->right;
	          if(y->parent==N)
	          {
	        	x->parent=y;
	          }
	          else
	          {
	        	 RB_Transplant(y,y->right);
	        	 y->right=N->right;
	        	 y->right->parent=y;
	          }
	          RB_Transplant(N,y);
	          y->left=N->left;
	          y->left->parent=y;
	          y->color=N->color;
	     }
	     if(y_original_color==1)
	     {
	    	RB_DeleteFixUp(x);
	     }
   }
//-----------------------------------------------------------------Public---------------------------------------------------
// return size of dictionary
int Dictionary::size() const
{
return num_pairs;
}


// contains()
 // Returns true if there exists a pair such that key==k, and returns false
 // otherwise.
 bool Dictionary::contains(keyType k) const
 {
	 Node *N=search(root,k);
	 if(N!=nil)
	 {
         return true;
	 }
	 return false;
 }
 // getValue()
 // Returns a reference to the value corresponding to key k.
 // Pre: contains(k)
 valType& Dictionary::getValue(keyType k) const
 {
     Node* n=search(root,k);
     if(contains(k)==false)
     {
         throw std::logic_error("Dictionary: getValue(): key "+k+" does not exist");
     }
     else
     {
     	return n->val;
     }
 }


 // hasCurrent()
 // Returns true if the current iterator is defined, and returns false
 // otherwise.
 bool Dictionary::hasCurrent() const
 {
 	if(current!=nil)
 	{
 	return true;
 	}
 	return false;
 }
 // currentKey()
 // Returns the current key.
 // Pre: hasCurrent()
 keyType Dictionary::currentKey() const
 {
   if(hasCurrent())
   {
 	  return current->key;
   }
   else
   {
 	  throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
 }
 // currentVal()
 // Returns a reference to the current value.
 // Pre: hasCurrent()
 valType& Dictionary::currentVal() const
 {
 	 if(hasCurrent())
 	  {
 		  return current->val;
 	  }
 	  else
 	  {
 		  throw std::logic_error("Dictionary: currentVal(): current undefined");
 	  }

 }


 // setValue()
 // If a pair with key==k exists, overwrites the corresponding value with v,
 // otherwise inserts the new pair (k, v).

void Dictionary::setValue(keyType k, valType v)
{
	Node* z=new Node(k,v);
	Node* y=nil;
	Node* x=root;
    while(x!=nil)
    {
       y=x;
       if(z->key==x->key)
       {
    	x->val=v;
    	return;
       }
       else if(z->key<x->key)
       {
    	x=x->left;
       }
       else
       {
    	   x=x->right;
       }
    }
    z->parent=y;
    if(y==nil)
    {
 	   root=z;
    }
    else if(z->key<y->key)
    {
 	y->left=z;
    }
    else
    {
 	   y->right=z;
 	}
    z->right=nil;
    z->left=nil;
    z->color=0;
    num_pairs++;

    RB_InsertFixUp(z);
}
// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k)
{
	   Node* X=search(root,k);
	   if(X!=nil)
	   {
		   if(current==X)
		   {
			   current=nil;
		   }

		   RB_Delete(X);
		   num_pairs--;
		   free(X);
	   }
	   else
	   {
		   throw std::logic_error("Dictionary: remove(): key "+ k +" does not exist");
	   }
}
// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin()
{
current=findMin(root);
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end()
{
current=findMax(root);
}
// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next()
{
	 if (current == nil) {
		 throw std::logic_error("Dictionary: currentKey(): current undefined");
	  }
	  current=findNext(current);
}


// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev()
{

	if(current==nil)
	{
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	current=findPrev(current);
}
// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.

std::string Dictionary::to_string() const
{
	std::string s="";
	inOrderString(s, root);
	return s;

}
// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const
{
	std::string s="";
		preOrderString(s, root);
		return s;

}
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D )
		{
               stream<<D.to_string();
               return stream;
		}
// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==( const Dictionary& A, const Dictionary& B )
		{
	Dictionary &ref=const_cast <Dictionary &>(B);
		if(&A==&B)
		{
		  return (true);
		}
		if(A.root==A.nil && B.root==B.nil)
		{
		return true;
		}
		else if(A.root==A.nil || B.root==B.nil)
		{
			return false;
		}

		if(ref.size()!=A.size())
		{
			return false;
		}
		Dictionary &refthis=const_cast <Dictionary &>(A);
		Dictionary::Node* curr=ref.current;
		Dictionary::Node* currthis=refthis.current;
		ref.begin();
	    refthis.begin();
		while(ref.current!=ref.nil && refthis.current!=refthis.nil)
		{
	       if(ref.current->key!=refthis.current->key || ref.current->val!=refthis.current->val)
	       {
	    	   ref.current=curr;
	    	   refthis.current=currthis;

	        return false;
	       }
		   ref.next();
		   refthis.next();
		}
		  ref.current=curr;
		  refthis.current=currthis;
		return true;
		}

// operator=()
 // Overwrites the state of this Dictionary with state of D, and returns a
 // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D )
{
Dictionary &ref=const_cast <Dictionary &>(D);
if(this==&D)
{
  return (*this);
}
Node* curr=ref.current;
ref.begin();
while(ref.current!=ref.nil)
{
   setValue(ref.current->key,ref.current->val);
   ref.next();
}
ref.current=curr;
	return (*this);
}
