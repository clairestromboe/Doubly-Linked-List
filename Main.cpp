#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;
int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList dll;
  cout << "list: " << dll << endl << endl;
 
 
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl << endl;


  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertFirst(i);
  }
  cout << "list: " << dll << endl << endl;

  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;
  cout << endl;
  
  cout << "Re-make list for more testing: " << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl << endl;

  // more testing...
  // test for insertAfter
		dll.insertAfter(*dll.getFirst(), 15);
		cout << "Insert 15 after 10: " << endl;
		cout << dll << endl << endl;

  // test for insertBefore
		dll.insertBefore(*dll.getFirst()->next->next->next, 25);
		cout << "Insert 25 before 30: " << endl;
		cout << dll << endl << endl;

  // test for removeAfter: remove 15 after 10
		dll.removeAfter(*dll.getFirst());
		cout << "Remove 15 after 10: " << endl;
		cout << dll << endl << endl;

  // test for removeBefore: remove 25 before 30
		dll.removeBefore(*dll.getFirst()->next->next->next);
		cout << "Remove 25 before 30: " << endl;
		cout << dll << endl << endl;

  // test for DoublyLinkedListLength
		int length = DoublyLinkedListLength(dll);
		cout << "list length: " << length << endl << endl;
		
		

  return 0;
}
