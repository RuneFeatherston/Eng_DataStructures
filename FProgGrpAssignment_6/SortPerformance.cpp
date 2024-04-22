#include <iostream>
#include <stdexcept> // allowing out_of_range
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

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

int* generateArray(int size) {
    srand(time(0));
    int *arrPtr = new int[size];
    for (int i = 0; i < size; ++i) {
        arrPtr[i] = rand() % (size * 2 + 1);
    }
    return arrPtr;
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int size) {
    quickSortHelper(arr, 0, size - 1);
}

void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }
    
    for (int i = size - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Counting Sort
void countingSort(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int count[max + 1] = {0};
    int output[size];
    
    for (int i = 0; i < size; ++i) {
        count[arr[i]]++;
    }
    
    for (int i = 1; i <= max; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = size - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }
}

// Radix Sort
void countingSortRadix(int arr[], int size, int exp) {
    int output[size];
    int count[10] = {0};
    
    for (int i = 0; i < size; ++i) {
        count[(arr[i] / exp) % 10]++;
    }
    
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = size - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortRadix(arr, size, exp);
    }
}

int main() {
    int sizes[] = {10, 100, 500, 5000, 25000};
    for (int size : sizes) {
        int* arr = generateArray(size);
        
        auto start = high_resolution_clock::now();
        bubbleSort(arr, size);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Bubble Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        insertionSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Insertion Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        mergeSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Merge Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        quickSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Quick Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        heapSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Heap Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        countingSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Counting Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
        
        arr = generateArray(size);
        
        start = high_resolution_clock::now();
        radixSort(arr, size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Radix Sort for size " << size << " took: " << duration.count() << " microseconds." << endl;
        
        delete[] arr;
    }
    return 0;
}
