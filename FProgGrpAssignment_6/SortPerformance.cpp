#include <iostream>
#include <stdexcept> // allowing out_of_range
#include <iomanip>
#include <string>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}

    bool operator>(const Node<T>& other) const {
        return this->data > other.data;
    }

    bool operator<(const Node<T>& other) const {
        return this->data < other.data;
    }

    bool operator==(const Node<T>& other) const {
        return this->data == other.data;
    }
};

template<typename T>
class OrderedLinkedList {
private:
    Node<T>* head;

public:
    OrderedLinkedList() : head(nullptr) {}

    ~OrderedLinkedList() {
        clear();
    }

    void AddItem(const T* value) {
    	Node<T>* newNode = new Node<T>(*value);

    	// list is empty, OR new node should be placed before head
    	if (!head || *head > *newNode) {
    	    newNode->next = head;
    	    head = newNode;
   	 	} else {
        	// find correct position for new node
        	Node<T>* current = head;

        // traverse until we find value less than new node, OR end of list
        while (current->next && *current->next < *newNode) {
            current = current->next; // next node
        }

        // inserting new node...
        newNode->next = current->next;
        current->next = newNode;
        }
    }


    // NOTE: This specifies only pointers to be passed to and from the class.
    // Therefore, it is the caller's responsibility to delete the node after use in
    // order to avoid memory leaks.
    Node<T>* RemoveItem(const T& value) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        // traverse list to find node with value
        while (current != nullptr) {
            if (*current == value) {
                // is this node head of list?
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    // by writing prev to next, 'jump' over the node we grab
                    prev->next = current->next;
                }
                current->next = nullptr;
                return current;
            }

            prev = current;
            current = current->next;
        }

        // if val not found, return nullptr
        return nullptr;
    }

    bool IsInList(const T& value) {
        Node<T>* current = head;

        // traverse list to find node with value
        while (current != nullptr) {
            if (*current == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool IsEmpty() {
        return head == nullptr;
    }

    int Size() {
        int count = 0;
        Node<T>* current = head;

        // traverse list
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        return count;
    }

    // Clears the linked list and deallocates memory
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};