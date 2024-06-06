#pragma once
// Circular_Linked_list.h
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        if (head != nullptr) {
            Node<T>* current = head;
            do {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            } while (current != head);
        }
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            newNode->next = head;
            temp->next = newNode;
            head = newNode;
        }
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* getHead() const {
        return head;
    }
};