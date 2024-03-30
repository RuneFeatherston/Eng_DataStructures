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

    // Constructor - allow value to be written to newly created node
    Node(T data) : data(data), next(nullptr) {}

    // Overload comparison operators
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
    Node<T>* currentPosition;

public:
    // Constructor - initialize linked list, making a head node.
    OrderedLinkedList() : head(nullptr), currentPosition(nullptr) {}

    // Destructor - remove all node instances when the OrderdLinkedList is deleted.
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


    // NOTE: The assignment specifies only pointers to be passed to and from the class.
    // Therefore, it is the caller's responsibility to delete the node after use in
    // order to avoid memory leaks.
    Node<T>* GetItem(const T& value) {
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

    void Reset() {
        currentPosition = head;
    }

    T* SeeNext() {
        if (head == nullptr) {
            throw out_of_range("Cannot proceed: Linked list is empty.");
        }

        if (currentPosition == nullptr) {
            currentPosition = head;
        }

        T* itemData = &(currentPosition->data);
        currentPosition = currentPosition->next;

        if (currentPosition == nullptr) {
            currentPosition = nullptr; // Reset currentPosition when reaching the end of the list
        }

        return itemData;
    }

	T* SeeAt(int index) {
    	if (head == nullptr) {
    	    throw out_of_range("Cannot proceed: Linked list is empty.");
    	}

    	if (index < 0) {
    	    throw out_of_range("Invalid index: Index must be non-negative.");
    	}

    	int count = 0;
    	Node<T>* current = head;

    	// Traverse list to find node at specified index
    	while (current != nullptr && count < index) {
    	    current = current->next;
    	    count++;
    	}

    	if (current == nullptr) {
    	    throw out_of_range("Invalid index: Index is out of range.");
    	}

		currentPosition = current->next; // Set the location for SeeNext
    	return &(current->data);
	}


    // Clears the linked list and deallocates memory
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

	    // Display all items in the list
    void DisplayAll() {
        Node<T>* current = head;
        while (current != nullptr) {
            current->data.DisplayInfo();
            current = current->next;
        }
    }

};

class Student {
private:
    string FirstName;
    string LastName;
    string MNumber;
    float GPA;
    int Age; // Updated member variable to hold age in years

public:
    // Constructor
    Student(string firstName, string lastName, string mNumber, int age, float gpa = 0.0)
        : FirstName(firstName), LastName(lastName), MNumber(mNumber), Age(age), GPA(gpa) {}

    // GetName method
    string GetName() const {
        return FirstName + " " + LastName;
    }

    // GetMNumber method
    string GetMNumber() const {
        return MNumber;
    }

    // GetAge method
    int GetAge() const {
        return Age;
    }

	// Display student info in a basic ASCII table with consistent spacing
    void DisplayInfo() const {
        cout << "+------------+------------+--------------+" << endl;
        cout << "| First Name | Last Name  | MNumber      |" << endl;
        cout << "+------------+------------+--------------+" << endl;
        cout << "| " << setw(10) << left << FirstName << " | " << setw(10) << left << LastName << " | " << setw(10) << left << MNumber << " |" << endl;
        cout << "+------------+------------+--------------+" << endl;
    }

    // Overloaded comparison operators
    bool operator>(const Student& other) const {
        return MNumber > other.MNumber;
    }

    bool operator<(const Student& other) const {
        return MNumber < other.MNumber;
    }

    bool operator==(const Student& other) const {
        return MNumber == other.MNumber;
    }
};

int main() {
    OrderedLinkedList<Student> list;
    int choice;
    string firstName, lastName, mNumber; // Declare mNumber here

    do {
        cout << "Linked List Operations Menu" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display all students" << endl;
        cout << "3. Check if Student is in the List" << endl;
        cout << "4. Check if List is Empty" << endl;
        cout << "5. Get Size of List" << endl;
        cout << "6. See Next Student" << endl;
        cout << "7. Reset Position" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                int age;
                float gpa;

                cout << "Enter student details:" << endl;
                cout << "First Name: ";
                cin >> firstName;
                cout << "Last Name: ";
                cin >> lastName;
                cout << "MNumber: ";
                cin >> mNumber;
                cout << "Age: ";
                cin >> age;
                cout << "GPA: ";
                cin >> gpa;

                Student* newStudent = new Student(firstName, lastName, mNumber, age, gpa);
                list.AddItem(newStudent);
                cout << "Student added successfully." << endl;
                break;
            }
            case 2:
                cout << "All Students:" << endl;
                list.DisplayAll();
                break;
            case 3:
                cout << "Enter the student's MNumber to check: ";
                cin >> mNumber;
                if (list.IsInList(Student("", "", mNumber, 0))) {
                    cout << "Student is in the list." << endl;
                } else {
                    cout << "Student is not in the list." << endl;
                }
                break;
            case 4:
                if (list.IsEmpty()) {
                    cout << "List is empty." << endl;
                } else {
                    cout << "List is not empty." << endl;
                }
                break;
            case 5:
                cout << "Size of the list: " << list.Size() << endl;
                break;
            case 6:
                try {
                    const Student* nextStudent = list.SeeNext();
                    cout << "Next student in the list: " << nextStudent->GetName() << endl;
                } catch (const std::out_of_range& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            case 7:
                list.Reset();
                cout << "Position reset to the beginning of the list." << endl;
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid choice." << endl;
        }
    } while (choice != 8);

    return 0;
}
