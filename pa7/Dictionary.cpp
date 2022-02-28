/* 
#  Name: Yue Zhang
#  CruzId: yzhan760
#  Assignment No: pa7
#  This program written for Dictionary ADT
*/


#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<bits/stdc++.h>
#include <stack>

// constructor
Dictionary::Dictionary()
 {
	nil=NULL;
	root=NULL;
	current=NULL;
	num_pairs=0;
 }

 // Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
  key=k;
  val=v;
  left=NULL;
  right=NULL;
  parent=NULL;
}


// paramaterized constructor
Dictionary::Dictionary(const Dictionary& D)
{
		nil=NULL;
		root=NULL;
		current=NULL;
		num_pairs=0;
		   Dictionary &ref=const_cast <Dictionary &>(D);
		   ref.begin();
		   while(ref.current!=NULL)
		   {
			   setValue(ref.current->key,ref.current->val);
			   ref.next();
		   }
}

// Destructor
Dictionary::~Dictionary(){
     	begin();
	   while(current!=NULL)
	   {
		   setValue(current->key,current->val);
		   remove(current->key);
		   begin();
	   }

}

// inOrder traversal
void Dictionary::inOrderString(std::string& s, Node* R) const
{
    if(R!=NULL)
    {
    	inOrderString(s,R->left);
    	s=s+R->key+" : "+std::to_string(R->val)+"\n";
    	inOrderString(s,R->right);
    }
}

// preOrder traversal
void Dictionary::preOrderString(std::string& s, Node* R) const
{
    if(R!=NULL)
    {
    	s=s+R->key+"\n";
    	preOrderString(s,R->left);
    	preOrderString(s,R->right);
    }
}


// searching key
Dictionary::Node* Dictionary::search(Node* R, keyType k) const
{
	    if (R == NULL || R->key == k)
	       return R;

	    if (R->key < k)
	       return search(R->right, k);

	    return search(R->left, k);
}


// find leftmost node
Dictionary::Node* Dictionary::findMax(Node* N)
{
	Node *x=N;
if(x!=NULL)
{
while(x->right!=NULL)
{
x=x->right;
}
}
return x;
}

// find right most node
Dictionary::Node* Dictionary::findMin(Node* N)
{
	Node *x=N;
while(x!=NULL && x->left!=NULL)
{
x=x->left;
}
return x;
}


// find  next 
Dictionary::Node* Dictionary::findNext(Node* N)
{
	if (N == NULL) {
	    return NULL;
	  }
	  if(N->right!=NULL)
	  {
         N=findMin(N->right);
	  }
	  else
	  {
		  auto parent = N->parent;
		  while (parent != NULL && N == parent->right) {
		         N = parent;
		         parent = parent->parent;
		       }
		       N = parent;
	  }
return N;
}


// find prev
Dictionary::Node* Dictionary::findPrev(Node* N)
{
	if (N == NULL) {
		    return NULL;
		  }
		  if(N->left!=NULL)
		  {
	         N=findMax(N->left);
		  }
		  else
		  {
			  auto parent = N->parent;
			  while (parent != NULL && N == parent->left) {
			         N = parent;
			         parent = parent->parent;
			       }
			       N = parent;
		  }
	return N;
}




//-----------------------------------------------------------------Public---------------------------------------------------


// size
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
	 if(N!=NULL)
	 {
         return true;
	 }
	 return false;
 }


// get value
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
	if(current!=NULL)
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

// clear()
 // Resets this Dictionary to the empty state, containing no pairs.
 void Dictionary::clear()
 {
	 	begin();
	   while(current!=NULL)
	   {
		   setValue(current->key,current->val);
		   remove(current->key);
		   begin();
	   }
			nil=NULL;
			root=NULL;
			current=NULL;
			num_pairs=0;
 }

void Dictionary::setValue(keyType k, valType v)
{
	Node* node=new Node(k,v);
	if(root==NULL)
	{
		root=node;
		nil=node;
		num_pairs++;
		return;
	}
	else if(root->key==k)
	{
		root->val=v;
		return;
	}
	else
	{
		Node *temp= root;
		Node *tempnode=NULL;
		while(temp!=NULL)
		{
			tempnode=temp;
			if(temp->key==k)
			{
               temp->val=v;
               return;
			}
			else if(k<temp->key)
			{
				temp=temp->left;
			}
			else
			{
				temp=temp->right;
			}
		}
		if(tempnode!=NULL)
		{
			if(k<tempnode->key)
			{
               tempnode->left=node;
               tempnode->left->parent=tempnode;
               num_pairs++;
			}
			else
			{
				tempnode->right=node;
				tempnode->right->parent=tempnode;
				num_pairs++;
			}
		}

	}
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k)
{
  auto TransPlant=[](Dictionary &D, Node * U, Node* V)
		{
           if(U->parent==NULL)
           {
             D.root=V;
           }
           else if(U==U->parent->left)
           {
                U->parent->left=V;
           }
           else
           {
               U->parent->right=V;
           }
           if(V!=NULL)
           {
            V->parent=U->parent;
           }
		};
   auto Delete=[&](Dictionary &D, Node* Z)
   {
           if(Z->left==NULL)
           {
        	   TransPlant(D,Z,Z->right);
           }
           else if(Z->right==NULL)
           {
        	TransPlant(D,Z,Z->left);
           }
           else
           {
        	   Node *Y= findMin(Z->right);
        	   if(Y->parent!=Z)
        	   {
        		  TransPlant(D,Y,Y->right);
        		  Y->right=Z->right;
        		  Y->right->parent=Y;
        	   }
        	   TransPlant(D,Z,Y);
        	   Y->left=Z->left;
        	   Y->left->parent=Y;
           }
   };

   Node* X=search(root,k);
   if(X!=NULL)
   {
	   if(X==current)
	   {
		   current=NULL;
	   }

	   Delete((*this),X);
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
	 if (current == NULL) {
	    throw std::logic_error("Dictionary: next(): current not defined");
	  }
	  current=findNext(current);
}
void Dictionary::prev()
{
	if(current==NULL)
	{
		 throw std::logic_error("Dictionary: prev(): current not defined");
	}
	current=findPrev(current);
}
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

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const
{
	Dictionary &ref=const_cast <Dictionary &>(D);
	if(this==&D)
	{
	  return (true);
	}
	if((*this).root==NULL && D.root==NULL)
	{
	return true;
	}
	else if((*this).root==NULL || D.root==NULL)
	{
		return false;
	}

	if(ref.size()!=(*this).size())
	{
		return false;
	}
	Dictionary &refthis=const_cast <Dictionary &>(*this);

	ref.begin();
    refthis.begin();
	while(ref.current!=NULL && refthis.current!=NULL)
	{

       if(ref.current->key!=refthis.current->key && ref.current->val!=refthis.current->val)
       {
        return false;
       }
	   ref.next();
	   refthis.next();
	}

	return true;
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
		if(A.root==NULL && B.root==NULL)
		{
		return true;
		}
		else if(A.root==NULL || B.root==NULL)
		{
			return false;
		}

		if(ref.size()!=A.size())
		{
			return false;
		}
		Dictionary &refthis=const_cast <Dictionary &>(A);
		ref.begin();
	    refthis.begin();
		while(ref.current!=NULL && refthis.current!=NULL)
		{
	       if(ref.current->key!=refthis.current->key || ref.current->val!=refthis.current->val)
	       {
	        return false;
	       }
		   ref.next();
		   refthis.next();
		}

		return true;
		}



// operator=()
 // Overwrites the state of this Dictionary with state of D, and returns a
 // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D )
{

Dictionary &ref=const_cast <Dictionary &>(D);
ref.begin();
if(this==&D)
{
  return (*this);
}
while(ref.current!=NULL)
{

   setValue(ref.current->key,ref.current->val);
   ref.next();
}
	return (*this);
}

