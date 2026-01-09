/*
CS 201: Fundamental Structures of Computer Science I
Fall 2025
Homework Assignment 3
Student Name: Sıla Bozkurt
Student ID: 22401775
Section: 3
Instructor: Ercüment Çiçek
Assistants: Mehmet Alper Yılmaz
Submission Date: 12.12.2025
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();

    void append(T data);
    void prepend(T data);
    void insert(T data, int position);
    void remove(int position);
    void display() const;

    T& get(int position) const;
    int getSize() const;
    bool isEmpty() const;

    void insertSorted(T data);

private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

    Node* getNodeAt(int position) const;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
    Node* current = other.head;
    while (current) {
        append(current->data); // Deep copy
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::append(T data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::prepend(T data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::insert(T data, int position) {
    if (position < 0 || position > size) {
        return;
    }

    if (position == 0) {
        prepend(data);
        return;
    }

    if (position == size) {
        append(data);
        return;
    }

    Node* newNode = new Node(data);
    Node* prev = getNodeAt(position - 1);
    newNode->next = prev->next;
    prev->next = newNode;
    size++;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if (position < 0 || position >= size) {
        return;
    }

    Node* toDelete = nullptr;

    if (position == 0) {
        toDelete = head;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
    } else {
        Node* prev = getNodeAt(position - 1);
        toDelete = prev->next;
        prev->next = toDelete->next;
        if (toDelete == tail) {
            tail = prev;
        }
    }

    delete toDelete;
    size--;
}

template <typename T>
void LinkedList<T>::display() const {
    Node* current = head;
    while (current) {
        cout << current->data << endl; 
        current = current->next;
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(int position) const {
    if (position < 0 || position >= size) {
        return nullptr;
    }

    Node* current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current;
}

template <typename T>
T& LinkedList<T>::get(int position) const {
    return getNodeAt(position)->data;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void LinkedList<T>::insertSorted(T data) {
    if (!head || data < head->data) {
        prepend(data);
        return;
    }
    if (data > tail->data) {
        append(data);
        return;
    }
    Node* current = head;
    int position = 0;
    while (current && current->data < data) {
        current = current->next;
        position++;
    }
    insert(data, position);
}
#endif