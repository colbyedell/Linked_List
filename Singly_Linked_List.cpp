#include <iostream>

class Node {
  public:
    Node* next;
    int key;

    Node(){ // No-argument constructor that initializes the node's variables to default values.
      next = NULL;
      key = 0;
    }

    Node(Node * _next, int _key){ // User-defined constructor which sets the node's "next" pointer and key value to the values passed into the constructor.
      next = _next;
      key = _key;
    }
};

class LinkedList {
  private:
    Node* head;
    Node* tail;

  public:
    LinkedList(){ // No-argument constructor which initializes head and tail pointers to null.
      head = NULL;
      tail = NULL;
    }

    void PushFront(int _key){ // Push a node to the front of the list.
      if (this->Empty()) { // If the list is empty when we attempt to push a new node, initialize the list with the node we are attempting to create.
        Node * temp = new Node(NULL, _key); // If the list is empty, the node's "next" pointer should point to null, as there is no next node.
        
        head = temp; // The list's head pointer points to the one and only node in our list.
        tail = temp; // The list's tail pointer points to the one and only node in our list.
      } else { // If the array is NOT empty when we attempt to push a new node, simply push it to the front of the list. 
        Node * temp = new Node(head, _key); // Initialize a node with a specified key, whose "next" pointer will point to the current first node in the list.
        
        head = temp; // Set the head pointer to this new node.
      }
    }

    int TopFront(){ // Return the contents (key) of the first node in the list, given that the list is not empty.
      if(!(this->Empty())) {
        return head->key; 
      } else {
        std::cout << "List is empty. Cannot return the contents of the first node in an empty array. Returning default value of 0." << std::endl;
        return 0;
      }
    }

    void PopFront(){ // Delete the first node in the list.
      if (!(this->Empty())) { // If the list is empty, there is nothing to pop. We will only pop if the list is nonempty.
        Node * temp = new Node(); // Initialize a new placeholder node.
        
        temp = head; // Set this placeholder node to reference the current first node in our list.
        
        if(this->Size() == 1){ // If our list only has one element, our list will be empty after this pop, so reset head and tail accordingly.
          head = NULL;
          tail = NULL;
        } else {
          head = head->next; // Set the head pointer to the next node, which will become the new first node in our list.
        }

        delete temp; // Delete the original head node, thus deleting the original first node in our list.
      }
    }

    void PushBack(int _key){ // Push a node to the back of the list.
      if (this->Empty()) { // If the list is empty when we attempt to push a new node, initialize the list with the node we are attempting to create.
        Node * temp = new Node(NULL, _key); // If the list is empty, the node's "next" pointer should point to null, as there is no next node.
        
        head = temp; // The list's head pointer points to the one and only node in our list.
        tail = temp; // The list's tail pointer points to the one and only node in our list.
      } else { // If the list is NOT empty when we attempt to push a new node, push it to the back of the list.
        Node * temp = new Node(NULL, _key);
        
        tail->next = temp; // Set the "next" pointer of our current last node to point to our new node.
        tail = temp; // Update the tail pointer to point to our new last node.
      }
    }

    int TopBack(){ // Return the contents (key) of the last node in the list.
      if(!(this->Empty())) {
        return tail->key; 
      } else {
        std::cout << "List is empty. Cannot return the contents of the last node in an empty array. Returning default value of 0." << std::endl;
        return 0;
      }
    }

    void PopBack(){ // Delete the last node in the list.
      if (!(this->Empty())) { // If the list is empty when we attempt to push a new node, initialize the list with the node we are attempting to create.
        Node * current = new Node(); 
        current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
        
        if(this->Size() == 1){ // If our list only has one element, our list will be empty after this pop. Reset head and tail accordingly, delete the temporary arrays, and exit the method.
          head = NULL;
          tail = NULL;
          delete current;
          return;
        }
        
        Node * previous = new Node();
        
        while(current->next != NULL){ // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list.
          previous = current; // After we've iterated over a node, update our "previous" reference accordingly.
          current = current->next; // Set our "current" node reference to the next node.
        }
        
        tail = previous; // Update the tail to reference our new last node (after deleting the current last node.)
        previous->next = NULL; // Remove the reference to the current last node, updating the "next" pointer in our new last element.
        
        delete current; // Delete the previous last element.
      }
    }

    bool Find(int _key){ // Determine whether a key is contained in the list.
      Node * current = new Node(); // Initialize a node pointer which we will use to "walk through" our list.
      current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
      
      for(int i = 0; i < this->Size(); i++) { // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list.
        if(current->key == _key){ // If the key we are looking for is contained within the current node we are checking, return true.
          return true;
        } else { // If the current key does not match the one we are looking for, move to the next node.
          current = current->next;
        }
      }

      return false;
    }

    void Erase(int _key){ // Delete the first node that contains a given key within the list.
      if(this->Find(_key)){ // If the key we're looking for is within the list, delete it.
        Node * current = new Node();
        Node * previous = new Node();
        current = head;
        previous = current;
        
        for (int i = 0; i < this->Size(); i++) {
          if(current->key == _key){ // If the key we wish to delete is within the node we're checking, run the instructions below.
            if (current->next != NULL){ // If there is no node after the one we're deleting, we must update the tail.
              previous->next = current->next; // Set the previous node's next pointer to reference the node after the one we're deleting.
            } else {
              previous->next = NULL;
              tail = previous;
            }

            if(head == current){ // If the key we want to delete happens to be the first element, update the head accordingly.
              if(current->next == NULL){ // If the current node is ALSO the last node, the list will be empty after deletion. Update head and tail accordingly.
                head = NULL;
                tail = NULL;
              } else {
                head = current->next;
              }
            }
            
            delete current; // Delete the current node.
          } else { // If the key we wish to delete is NOT within the node we're checking, run the instructions below.
            previous = current; // After we've iterated over a node, update our "previous" reference accordingly.
            current = current->next; // Set our "current" node reference to the next node.
          }
        }  
      } else { // If the key we're looking for is not within the list, we cannot delete it.
        std::cout << "The key you're referencing does not exist within your list." << std::endl;
      }
    }

    bool Empty(){ // Returns true if the list is empty, and false if the list is not empty.
      return (head == NULL && tail == NULL) ? true : false;
    }

    void AddBefore(int _node, int _key){ // Insert a node before the specified index.
      if(this->Size() - 1 < _node){ // If the list's size - 1 is smaller than the index of the node we wish to insert behind, adding before it is impossible, as that index doesn't exist in our list.
        std::cout << "Invalid index." << std::endl;
      } else {
        Node * current = new Node();
        Node * previous = new Node();
        int node = 0; // Initialize a counter which we will use to keep track of our current index.
        current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
        
        while(node < _node){ // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list.
          previous = current; // After we've iterated over a node, update our "previous" reference accordingly.
          current = current->next; // Set our "current" node reference to the next node.
          node++;
        }

        Node * temp = new Node(current, _key); // Initialize a new node, which will be the one we actually insert into the array. Its "next" pointer will reference the "current" node, which is the index we wish to insert behind.
        previous->next = temp; // Update the previous node's "next" pointer to reference the node we've just inserted.

        if (_node == 0){ // If the index we're inserting "before" is 0, it is the new first node. Update head accordingly.
          head = temp;
        }
      }
    }

    void AddAfter(int _node, int _key){ // Insert a node after the specified index.
      if(this->Size() - 1 < _node){ // If the list's size - 1 is smaller than the index of the node we wish to insert in front of, adding after it is impossible, as that index doesn't exist in our list.
        std::cout << "Invalid index." << std::endl;
      } else {
        Node * current = new Node(); // Initialize a node which we will use to "walk through" our list.
        int node = 0; // Initialize a counter which we will use to keep track of our current index.
        current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
      
        while(node < _node){ // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list.
          current = current->next;
          node++;
        }

        Node * temp = new Node(current->next, _key); // Initialize a new node, which will be the one we actually insert into the array. Its "next" pointer will reference the current pointer's "next" reference, which is the index we wish to insert behind.
        current->next = temp; // Update the current node's "next" pointer to reference our new node.
        
        if (temp->next == NULL) // Update the tail pointer of our list if necessary, which occurs when the node we've just inserted is the new last node.
          tail = temp;
      }
    }

    void DisplayAll(){ // Print all the elements (keys) in the list.
      Node * current = new Node(); // Initialize a node which we will use to "walk through" our list.
      current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
      
      for (int i = 0; i < this->Size(); i++) { // Iterate through all elements of the list, printing each key.
        std::cout << current->key << " ";
        current = current->next;
      }
      std::cout << std::endl; // Once we have output all elements in our list, move the console "cursor" to the next line.
    }

    int Size(){ // Return the number of nodes in the list.
      if(this->Empty()){ // If our list is empty, return a size of 0.
        return 0;
      }
      
      Node * current = new Node(); // Initialize a node which we will use to "walk through" our list.
      int size = 0; // Initialize a counter which we will use to keep track of the number of nodes in our list.
      
      current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
      
      while(current->next != NULL){ // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list by incrementing our counter and moving to the next element.
        size++;
        current = current->next;
      }

      return ++size; // Return the final node count (incremented, to count for the last element) once we've iterated through and counted each node in the list.
    }

    void ReplaceKey(int _node, int _key){ // Overwrite the key of a node in a given index.
      if(this->Size() - 1 < _node){ // If the list's size - 1 is smaller than the index of the node we wish to insert in front of, replacing at that index is impossible, as that index doesn't exist in our list.
        std::cout << "Invalid index for replacement." << std::endl;
      } else {
        Node * current = new Node(); // Initialize a node which we will use to "walk through" our list.
        int node = 0; // Initialize a counter which we will use to keep track of our current index.
        current = head; // Set the "current" node pointer to reference the head node, which is where we will begin "walking through" our list.
      
        while(node < _node){ // While a next node exists (in other words, until we have reached the end of our list,) continue "walking through" the list by incremending our index and moving to the next element.
          node++;
          current = current->next;
        }

        current->key = _key;
      }
    }
};

int main() {
  LinkedList * myList = new LinkedList();

  myList->PushFront(25);
  myList->PushFront(50);
  myList->PushFront(90);
  myList->PushFront(40);
  myList->PushBack(35);
  myList->DisplayAll();
  
  std::cout << myList->TopFront() << std::endl;
  std::cout << myList->TopBack() << std::endl;
  myList->PopFront();
  myList->DisplayAll();

  myList->PopBack();
  myList->DisplayAll();

  myList->PushBack(10);
  myList->PushBack(12);
  myList->PushBack(14);
  myList->DisplayAll();

  std::cout << "Is 25 in the list? (1 for yes, 0 for no): " << myList->Find(25) << std::endl;
  std::cout << "Is 6 in the list? (1 for yes, 0 for no): " << myList->Find(6) << std::endl;
  std::cout << "Is the list empty? (1 for yes, 0 for no): " << myList->Empty() << std::endl;

  myList->AddBefore(3, 94);
  myList->DisplayAll();

  myList->AddAfter(2, 5);
  myList->DisplayAll();

  std::cout << "Current size of list: " << myList->Size() << std::endl;
  myList->ReplaceKey(6, 87);
  myList->DisplayAll();

  myList->PopFront();
  myList->PopFront();
  myList->PopFront();
  myList->PopFront();
  myList->PopFront();
  myList->PopFront();
  myList->PopFront();
  myList->PopBack();

  std::cout << "Is the list empty? (1 for yes, 0 for no): " << myList->Empty() << std::endl;
  
  delete myList;
  
  return 0;
}