//doublylinkedlist.h

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T* data);
    bool empty() const { return (head == nullptr); }
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

//Node constructor.
template <class T>
DoublyLinkedList<T>::Node::Node() {
  data=nullptr;
  next=nullptr;
  prev=nullptr;
}

//Node(T* data) constructor
template <class T>
DoublyLinkedList<T>::Node::Node(T* data) {
  this->data=data; //TODO is this correct?
  next=nullptr;
  prev=nullptr;
}

//DoublyLinkedList constructor.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
  head=nullptr;
  tail=nullptr;
  current=nullptr;
}

//DoublyLinkedList destructor.
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  while(head!=nullptr) {
    Node* tmp=head;
    head=head->next;
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
    head=new Node(data);
    tail=head;
    current=head;
  }
  else {
    Node* tmp=tail;
    tail->next=new Node(data);
    tail=tail->next;
    tail->prev=tmp;
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
    current=head;
    return current->data;
  }
  else {
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
  if(current!=nullptr) {
    current=current->next;
    return current->data;
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
  if(current->next!=nullptr) {
  Node* tmp=current;
  current=current->next;
  delete tmp;
  return current->data;
  }
  else {
    Node* tmp=current;
    current=current->prev;
    delete tmp;
    return nullptr;
  }
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
