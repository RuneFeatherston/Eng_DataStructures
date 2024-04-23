#include <iostream>
#include <stdexcept> // allowing out_of_range
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <time.h>
#include <vector>

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

/*
The reason why a template function was used for all of the sorting algorithms is because
this project uses multiple types, both the table generation for step 2, and the 'student' 
class for step three,
*/

// Bubble Sort template function
template<typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort template function
template<typename T>
void insertionSort(T arr[], int size) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template<typename T>
void merge(T arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    T* L = new T[n1];
    T* R = new T[n2];
    
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
    
    delete[] L;
    delete[] R;
}

template<typename T>
void mergeSortHelper(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

// Merge Sort template function
template<typename T>
void mergeSort(T arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

template<typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void quickSortHelper(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Quick Sort template function
template<typename T>
void quickSort(T arr[], int size) {
    quickSortHelper(arr, 0, size - 1);
}

template<typename T>
void heapify(T arr[], int size, int i) {
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
        std::swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

// Heap Sort template function
template<typename T>
void heapSort(T arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }
    
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Counting Sort template function
template<typename T>
void countingSort(T arr[], int size) {
    T max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int* count = new int[max + 1] {0};
    T* output = new T[size];
    
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

    delete[] count;
    delete[] output;
}

template<typename T>
void countingSortRadix(T arr[], int size, int exp) {
    T* output = new T[size];
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

    delete[] output;
}

// Radix Sort template function
template<typename T>
void radixSort(T arr[], int size) {
    T max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortRadix(arr, size, exp);
    }
}

// Function to run sorting algorithm and return average time taken
// Utilize a function pointer for ease of use
template<typename T>
double runSort(T arr[], int size, void (*sortFunc)(T[], int)) {
    const int num_runs = 10;
    double total_time = 0.0;

    for (int i = 0; i < num_runs; ++i) {
        T* tempArr = new T[size];
        copy(arr, arr + size, tempArr);
        auto start = high_resolution_clock::now();
        sortFunc(tempArr, size);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total_time += duration.count();
        delete[] tempArr;
    }

    return total_time / num_runs;
}
template<typename T>
void generateTable(void (*sortFuncArr[])(T[], int), const std::string sortFuncNames[], int numSortFuncs, int testArrRange[], int sizeTestArrRange) {
    // There was some weirdness with 'ambiguity' in the compilier due to the string sortFuncNames,
    // especially considering 'using namespace std'. The scope inclusion operator is just a bandaid
    // for it all, so this isn't the cleanest code.

    std::cout << std::setw(25) << "Sorting Algorithm";
    for (int i = 0; i < sizeTestArrRange; ++i) {
        std::cout << std::setw(15) << testArrRange[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < numSortFuncs; ++i) {
        std::cout << std::setw(25) << sortFuncNames[i];
        for (int j = 0; j < sizeTestArrRange; ++j) {
            std::cout << std::setw(15) << "-------------------------";
        }
        std::cout << std::endl;
        
        std::cout << std::setw(25) << " " << " | ";
        for (int j = 0; j < sizeTestArrRange; ++j) {
            std::cout << std::setw(12) << testArrRange[j] << " | ";
        }
        std::cout << std::endl;

        std::cout << std::setw(25) << "-------------------------";
        for (int j = 0; j < sizeTestArrRange; ++j) {
            std::cout << std::setw(15) << "-------------------------";
        }
        std::cout << std::endl;

        std::cout << std::setw(25) << " " << " | ";
        for (int j = 0; j < sizeTestArrRange; ++j) {
            int size = testArrRange[j];
            int* arr = generateArray(size);
            double average_time = runSort(arr, size, sortFuncArr[i]);
            std::cout << std::setw(12) << average_time << " | ";
            delete[] arr;
        }
        std::cout << std::endl;
    }
}

int main() {
    int testArrRange[] = {10, 100, 500, 5000, 25000};
    int sizeTestArrRange = 5;
    int numSortFuncs = 7;
    const string sortFuncNames[] =
    {
        "Bubble Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
        "Heap Sort",
        "Counting Sort",
        "Radix Sort"
    };
    void (*sortFuncArr[])(int*, int) = 
    {
        bubbleSort<int>, 
        insertionSort<int>, 
        mergeSort<int>, 
        quickSort<int>, 
        heapSort<int>, 
        countingSort<int>, 
        radixSort<int>
    };

    generateTable(sortFuncArr, sortFuncNames, numSortFuncs, testArrRange, sizeTestArrRange);

    return 0;
}