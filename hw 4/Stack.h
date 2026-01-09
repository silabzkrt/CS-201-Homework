/*
CS 201: Fundamental Structures of Computer Science I
Fall 2025
Homework Assignment 4
Student Name: Sıla Bozkurt
Student ID: 22401775
Section: 3
Instructor: Ercüment Çiçek
Assistants: Mehmet Alper Yılmaz, Sude Önder
Submission Date: 24.12.2025
*/
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <cstddef>

template <typename T>
class Stack {
public:
    Stack() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Stack(std::size_t reserveCount) : data_(nullptr), size_(0), capacity_(0) {
        if (reserveCount > 0) {
            data_ = new T[reserveCount];
            capacity_ = reserveCount;
        }
    }

    // Copy constructor
    Stack(const Stack& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        if (capacity_ > 0) {
            data_ = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    // Copy assignment operator
    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;
        T* newData = nullptr;
        if (other.capacity_ > 0) {
            newData = new T[other.capacity_];
            for (std::size_t i = 0; i < other.size_; ++i) {
                newData[i] = other.data_[i];
            }
        }
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    ~Stack() { delete[] data_; }

    // Add an element to the top
    void push(const T& value) {
        ensure_capacity(size_ + 1);
        data_[size_++] = value;
    }

    // Remove and return the element at the top
    T pop() {
        if (empty()) {
            throw std::out_of_range("pop() from empty stack");
        }
        T value = data_[--size_];
        return value;
    }

    // Peek at the top element (no removal)
    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top() on empty stack");
        }
        return data_[size_ - 1];
    }
    T& top() {
        if (empty()) {
            throw std::out_of_range("top() on empty stack");
        }
        return data_[size_ - 1];
    }

    // State helpers
    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }
    void clear() { size_ = 0; }
    void reserve(std::size_t n) { ensure_capacity(n); }

    void swap(Stack& other) {
        T* tmpData = data_;
        data_ = other.data_;
        other.data_ = tmpData;
        
        std::size_t tmpSize = size_;
        size_ = other.size_;
        other.size_ = tmpSize;
        
        std::size_t tmpCap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = tmpCap;
    }

private:
    void ensure_capacity(std::size_t minCapacity) {
        if (capacity_ >= minCapacity) return;
        std::size_t newCap = capacity_ ? capacity_ * 2 : 4;
        if (newCap < minCapacity) newCap = minCapacity;
        T* newData = new T[newCap];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
    }

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif