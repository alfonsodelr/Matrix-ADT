#include<iostream>
#include<string>
#include "List.h"

// Class Constructors & Destructors ----------------------------------------

List::Node::Node(ListElement x)
{
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List()
{

}
// Creates new List in the empty state.

// Copy constructor.
List::List(const List& L)
{

}

// Destructor
List::~List()
{

}


// Access functions --------------------------------------------------------

int List::length() const
{

}
// Returns the length of this List.

ListElement List::front() const
{

}
// Returns the front element in this List.
// pre: length()>0

ListElement List::back() const
{

}
// Returns the back element in this List.
// pre: length()>0

int List::position() const
{

}
// Returns the position of cursor in this List: 0 <= position() <= length().

ListElement List::peekNext() const
{

}
// Returns the element after the cursor.
// pre: position()<length()

ListElement List::peekPrev() const
{

}
// Returns the element before the cursor.
// pre: position()>0


// Manipulation procedures -------------------------------------------------

void List::clear()
{

}
// Deletes all elements in this List, setting it to the empty state.

void List::moveFront()
{

}
// Moves cursor to position 0 in this List.

void List::moveBack()
{

}
// Moves cursor to position length() in this List.

ListElement List::moveNext()
{

}
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 

ListElement List::movePrev()
{

}
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0

void List::insertAfter(ListElement x)
{

}
// Inserts x after cursor.

void List::insertBefore(ListElement x)
{

}
// Inserts x before cursor.

void List::setAfter(ListElement x)
{

}
// Overwrites the List element after the cursor with x.
// pre: position()<length()

void List::setBefore(ListElement x)
{

}
// Overwrites the List element before the cursor with x.
// pre: position()>0

void List::eraseAfter()
{

}
// Deletes element after cursor.
// pre: position()<length()

void List::eraseBefore()
{

}
// Deletes element before cursor.
// pre: position()>0


// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x)
{

}
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 

int List::findPrev(ListElement x)
{

}
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 

void List::cleanup()
{

}
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 

List List::concat(const List& L) const
{

}
// the same two retained elements that it did before cleanup() was called.
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.

std::string List::to_string() const
{

}
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.

bool List::equals(const List& R) const
{

}
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.


// Overriden Operators -----------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const List& L )
{

}
// operator<<()
// Inserts string representation of L into stream.

bool operator==( const List& A, const List& B )
{
    
}
// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.

List& List::operator=( const List& L )
{

}
// operator=()
// Overwrites the state of this List with state of L.


