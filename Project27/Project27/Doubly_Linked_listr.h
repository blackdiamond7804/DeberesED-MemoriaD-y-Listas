#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* getHead() const {
        return head;
    }
};

