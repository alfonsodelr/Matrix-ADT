#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported types -------------------------------------------------------------
typedef int ListElement;

class List{

private:

   // private Node struct
   struct Node{
      // Node fields
      ListElement data;
      Node* next;
      Node* prev;
      // Node constructor
      Node(ListElement x);
   };

   // List fields
   Node* frontDummy;
   Node* backDummy;
   Node* beforeCursor;
   Node* afterCursor;
   int pos_cursor;
   int num_elements;

public:

   // Class Constructors & Destructors ----------------------------------------
   
   List();
   // Creates new List in the empty state.

   List(const List& L);
   // Copy constructor.

   ~List();
   // Destructor


   // Access functions --------------------------------------------------------

   int length() const;
   // length()
   // Returns the length of this List.

   ListElement front() const;
   // front()
   // Returns the front element in this List.
   // pre: length()>0

   ListElement back() const;
   // back()
   // Returns the back element in this List.
   // pre: length()>0

   int position() const;
   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().

   ListElement peekNext() const;
   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()

   ListElement peekPrev() const;
   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0


   // Manipulation procedures -------------------------------------------------

   void clear();
   // clear()
   // Deletes all elements in this List, setting it to the empty state.

   void moveFront();
   // moveFront()
   // Moves cursor to position 0 in this List.

   void moveBack();
   // moveBack()
   // Moves cursor to position length() in this List.

   ListElement moveNext();
   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 

   ListElement movePrev();
   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0

   void insertAfter(ListElement x);
   // insertAfter()
   // Inserts x after cursor.

   void insertBefore(ListElement x);
   // insertBefore()
   // Inserts x before cursor.

   void setAfter(ListElement x);
   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()

   void setBefore(ListElement x);
   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0

   void eraseAfter();
   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()

   void eraseBefore();
   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0


   // Other Functions ---------------------------------------------------------

   int findNext(ListElement x);
   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 

   int findPrev(ListElement x);
   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 

   void cleanup();
   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
 
   List concat(const List& L) const;
   // the same two retained elements that it did before cleanup() was called.
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.

   std::string to_string() const;
   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.

   bool equals(const List& R) const;
   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.


   // Overriden Operators -----------------------------------------------------
   
   friend std::ostream& operator<<( std::ostream& stream, const List& L );
   // operator<<()
   // Inserts string representation of L into stream.

   friend bool operator==( const List& A, const List& B );
   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.

   List& operator=( const List& L );
   // operator=()
   // Overwrites the state of this List with state of L.

};


#endif