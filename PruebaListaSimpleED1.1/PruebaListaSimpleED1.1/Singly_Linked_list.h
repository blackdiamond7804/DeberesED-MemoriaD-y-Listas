#pragma once
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* getHead() const {
        return head;
    }
};