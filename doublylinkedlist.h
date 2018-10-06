/**
 * @file doublylinkedlist.h
 *
 * @breif
 *    definitions of doubly linked list class and node sub-class
 *
 * @author Connor Richards
 *         Judy Challinger
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T* data);
    bool empty() const { return (head == nullptr); }

    void printList();

    T* remove();
    T* first();
    T* next();
  private:
    class Node {
      public:
        Node();
        Node(T* data);
        Node* next;
        Node* prev;
        T* data;
    };
    Node* head;
    Node* tail;
    Node* current;
};

//no args. node constructor
template <class T>
DoublyLinkedList<T>::Node::Node() {
  //set all vars. to null
  data=nullptr;
  next=nullptr;
  prev=nullptr;
}

//Node(T* data) constructor
template <class T>
DoublyLinkedList<T>::Node::Node(T* data) {
  //give the node tha passed in data
  //but other vars. should be null
  this->data=data;
  next=nullptr;
  prev=nullptr;
}

//DoublyLinkedList constructor.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
  //set all DLL vars. to null
  head=nullptr;
  tail=nullptr;
  current=nullptr;
}

//DoublyLinkedList destructor.
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  while(head!=nullptr) {
    //iterate through list and delete each node
    Node* tmp=head;
    head=head->next;
    delete tmp->data;
    delete tmp;
  }
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {
  if(empty()) {
    //if list empty
    //creates new node with passed in data
    //and sets all DLL vars to point to it
    head=new Node(data);
    tail=head;
    current=head;
  }
  else {
    //if non-empty list, place new node on end
    //of list with passed in data
    Node* tmp=tail;
    tail->next=new Node(data);
    tail=tail->next;
    tail->prev=tmp;
    tail->next=nullptr;
    current=tail;
  }
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {
  if(head!=nullptr) {
    //returns head if it points to something
    current=head;
    return current->data;
  }
  else {
    //returns nothing if empty list
    current=nullptr;
    return nullptr;
  }
}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {
  //ensure current points to something
  if(current!=nullptr) {
    if(current->next!=nullptr) {
      //moves to next if there is anything
      current=current->next;
      return current->data;
    }
    else {
      //sets current to null if nothing to next to
      current=nullptr;
      return nullptr;
    }
  }
  else {
    return nullptr;
  }
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {
  //ensure current is pointing to something
  if(current!=nullptr) {
    if(current->next!=nullptr) {
      //case of removing with multiple in list
      Node* tmp=current;
      if(head==current) {
        //case of removing the first thing
        head=head->next;
        current=current->next;
        delete tmp;
        return current->data;
      }
      else {
        //case of removing a middle item
        Node* tmp2=current->prev;
        current=current->next;
        current->prev=tmp->prev;
        tmp2->next=current;
        delete tmp;
        return current->data;
      }
    }
    else {
      //case of deleting last in list
      Node* tmp=current;
      if(head==current) {
        //case of deleting only item
        head=nullptr;
        tail=nullptr;
      }
      else if(tail->prev!=nullptr) {
        //case of deleting last from a multiple list
        tail=tail->prev;
      }
      current=nullptr;
      delete tmp;
      return nullptr;
    }
  }
  return nullptr;
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
