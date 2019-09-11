
#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{ 
	
	header.next = &trailer; 
	trailer.prev = &header;
	
	if (dll.isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}
  
	DListNode* node;
	node = dll.getFirst();
	
	while (node!= dll.getAfterLast()){
		insertLast(node->obj);//insert new element
		node = node->next;//set node to next node
	}
	
}

// move constructor
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& dll)
{
	header = dll.header;
	trailer = dll.trailer;
	
	dll.header = dll.trailer;
	dll.trailer = dll.header;
}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
   DListNode *prev_node;
   DListNode *node = header.next;
  
   // clear old list:
	while(node != &trailer) {
		prev_node = node;
		node = node->next;
		delete prev_node;
  }
  
	header.next = &trailer;
	trailer.prev = &header;

	// copy from dll:
	if (dll.isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}
	
	node = dll.getFirst();
	while(node!= dll.getAfterLast()){
		insertLast(node->obj);// insert new element
		node = node->next;// set node to next node
	}
  
}

// move assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& dll)
{
    header = 0;
	trailer = 0;

	header = dll.header;
	trailer = dll.trailer;
	
	dll.header = dll.trailer;
	dll.trailer = dll.header;
	
	return *this;
}

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{ 
  if (isEmpty()){
	DListNode *newNode = new DListNode(newobj, &header, &trailer);
	header.next = newNode;
	trailer.prev = newNode;
	return;
  }
	
	DListNode *newNode = new DListNode(newobj, &header, header.next);
	header.next->prev = newNode; // set newNode before the original first object
	header.next = newNode; // set newNode as new first object
	
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
   if (isEmpty()){
	DListNode *newNode = new DListNode(newobj, &header, &trailer);
	header.next = newNode;
	trailer.prev = newNode;
	return;
   }
	
	DListNode *newNode = new DListNode(newobj, trailer.prev, &trailer);
	trailer.prev->next = newNode; // insert newNode after original last object
	trailer.prev = newNode; // set newNode as new last object

	
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
    if (isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}

	DListNode *node = header.next;

	node->next->prev = &header; // address of header relocated
	header.next = node->next; // second object becomes first object
	int obj = node->obj; 
	delete node;
	return obj;

}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
    if (isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}
	
	DListNode *node = trailer.prev;
	
	node->prev->next = &trailer; // address of trailer relocated
	trailer.prev = node->prev; // second to last object becomes last object
	int obj = node->obj;
	delete node;
	return obj;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    DListNode *prev_node;
	DListNode *cur_node = header.next;
	
	while (cur_node != &trailer) { // while the cur_node node is not the trailer...
		prev_node = cur_node;
		cur_node = cur_node->next; // iterate
		delete prev_node;
	}
	
	header.next = &trailer;
	trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{ 
	if (isEmpty()){
		throw EmptyDLinkedListException("Empty Linked List");
	}
	
	return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
   if  (isEmpty()){
		throw EmptyDLinkedListException("Empty Linked List");
	}
	
	return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
	
	if (p.next == &trailer){ 
		insertLast(newobj);
		return;
	}
	
	if (&p == &trailer){
		throw EmptyDLinkedListException("Can't insert past the tail.");
	}
	
	DListNode *newNode = new DListNode(newobj, &p, p.next);
	p.next->prev = newNode; // sets newNode before p's original next
	p.next = newNode; // sets p's next to newNode
	
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
	if (p.prev == &header){
		insertFirst(newobj);
		return;
	}
	
	if (&p == &header){
		throw EmptyDLinkedListException("Can't insert before the head.");
	}
	
	DListNode *newNode = new DListNode(newobj, p.prev, &p);
	p.prev->next = newNode; // sets newNode after p's original prev
	p.prev = newNode; // sets p's prev to newNode
}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode &p)
{
    if (isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}
		
	if (&p == &trailer){
		throw EmptyDLinkedListException("Can't remove past the trailer in the list");
	}
	
	if (p.next == &trailer) // if this is the last element...
	{
		throw EmptyDLinkedListException("Can't remove the trailer");
	}
	
	DListNode *cur_node;
	cur_node = &p; // goes to node p
	cur_node = cur_node->next; // moves to the node after p
	p.next = cur_node->next; // sets p's next to the node after cur_node
	cur_node->next->prev = &p; // sets the node before cur_node's next to p
	// cout << "The node containing " << cur_node->obj << ", after " << &p << " has been deleted. " << endl;
	delete cur_node; // deletes the node after p
	cur_node = NULL; // frees the dangling pointer
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode &p)
{
	
	if (isEmpty()){
		throw EmptyDLinkedListException("Empty list");
	}
	if (&p == &header){
		throw EmptyDLinkedListException("Can't remove before the header in the list");
	}
	if (p.prev == &header){ // if this is the first element...
		throw EmptyDLinkedListException("Can't remove the header");
	}
	
	DListNode *cur_node;
	cur_node = &p; // goes to node p
	cur_node = cur_node->prev; // moves to the node before p
	p.prev = cur_node->prev; // sets p's prev to the node before cur_node
	cur_node->prev->next = &p; // sets the node after cur_node's prev to p
	// cout << "The node containing " << cur_node->obj << ", before " << &p << " has been deleted. " << endl;
	delete cur_node; // deletes the node before p
	cur_node = NULL; // frees the dangling pointer
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
    DListNode* cur_node = dll.getFirst();
	int count = 0;
	
	while (cur_node != dll.getAfterLast()) {
		count++;
		cur_node = cur_node->next; //iterate
	}
	
	return count;
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  
  DListNode *cur_node = dll.getFirst();
  
  while (cur_node != dll.getAfterLast()){ // traverses until it hits the trailer's NULLPTR
	out << cur_node->obj << " "; // print object
	cur_node = cur_node->next; // iterate
  }
  
  return out;
}
