//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------

/* 
#  Name: Yue Zhang
#  CruzId: yzhan760
#  Assignment No: pa7
#  This program written for top level client
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   int x;
   string Z[] = {"apple", "juice", "banana", "fruit", "time", "pass", "like", "that", "i", "good", "lobster", "sea", "whale", "flee"};

   Dictionary A;
   Dictionary B;

   // insert some pairs into A
   for(int i=0; i<14; i++){
      A.setValue(Z[i], i+1);
   }

   // print size of A
   cout << "A.size() = " << A.size() << endl;

   // call operator=()
   B = A;

   // set value
   A.setValue("apple", 78);

   // call copy constructor
   Dictionary C = B;

   //set value
   C.setValue("time",0);
   cout << endl;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << B << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   try{
      A.getValue("afterday");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.getValue("juice") *= 10; // change the value associated with "happy"
   cout << A.getValue("juice") << endl << endl;
   C.remove("juice");
   C.remove("time");
   C.remove("that");

   // check state of C
   cout << "C.size() = " << C.size() << endl  << C << endl;
   cout << C.pre_string() << endl;

   // do forward iteration on C
   for(C.begin(); C.hasCurrent(); C.next()){
      s = C.currentKey();
      x = C.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on C
   for(C.end(); C.hasCurrent(); C.prev()){
      s = C.currentKey();
      x = C.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl;
   cout<<"Has current: "<<(C.hasCurrent()?"true":"false") ;
   cout << endl;

   return( EXIT_SUCCESS );
}
