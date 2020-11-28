#pragma once

#include <iostream>
#include <vector>

#include "node.h"

// compile by using: cl /EHsc /W4 /D_DEBUG /MDd file_name.cpp
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

template <class T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFirst(T value);
    void insertLast(T value);
    bool insertAfter(T newValue, T afterValue);
    bool insertBefore(T newValue, T beforeValue);

    T removeFirst();
    T removeLast();
    bool remove(T value);

    bool find(T value);

    int count();

    void printAll();

private:
    Node<T>* head;
    Node<T>* tail;
};

template<class T>
inline DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr)
{
    Node<T>* startNode = DBG_NEW Node<T>;
    Node<T>* endNode = DBG_NEW Node<T>;

    startNode->startNode = true;
    endNode->endNode = true;
    startNode->next = endNode;
    endNode->previous = startNode;

    this->head = startNode;
    this->tail = endNode;
}

template<class T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node<T>* current = this->head;
    std::vector<Node<T>*> elements;

    while (!current->endNode)
    {
        elements.push_back(current);
        current = current->next;
    }

    elements.push_back(current);

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        delete elements[i];
    }
}

template<class T>
inline void DoublyLinkedList<T>::insertFirst(T value)
{
    Node<T>* newNode = DBG_NEW Node<T>;

    newNode->value = value;

    newNode->next = this->head->next;
    this->head->next = newNode;

    newNode->next->previous = newNode;
    newNode->previous = this->head;
}

template<class T>
inline void DoublyLinkedList<T>::insertLast(T value)
{
    Node<T>* newNode = DBG_NEW Node<T>;

    newNode->value = value;

    newNode->next = this->tail;
    this->tail->previous->next = newNode;

    newNode->previous = this->tail->previous;
    newNode->next->previous = newNode;
}

template<class T>
inline bool DoublyLinkedList<T>::insertAfter(T newValue, T afterValue)
{
    Node<T>* newNode = DBG_NEW Node<T>;
    Node<T>* current = this->head;

    newNode->value = newValue;

    if (current->next->endNode)
    {
        return false;
    }

    while (!current->next->endNode)
    {
        if (current->value == afterValue)
        {
            break;
        }
        current = current->next;
    }

    if (current->next->endNode)
    {
        return false;
    }

    newNode->next = current->next;
    current->next = newNode;

    newNode->next->previous = newNode;
    newNode->previous = current;

    return true;
}

template<class T>
inline bool DoublyLinkedList<T>::insertBefore(T newValue, T beforeValue)
{
    Node<T>* newNode = DBG_NEW Node<T>;
    Node<T>* current = this->head;

    newNode->value = newValue;

    if (current->next->endNode)
    {
        return false;
    }

    while (!current->next->endNode)
    {
        if (current->next->value == beforeValue)
        {
            break;
        }
        current = current->next;
    }

    if (current->next->endNode)
    {
        return false;
    }

    newNode->next = current->next;
    current->next = newNode;

    newNode->next->previous = newNode;
    newNode->previous = current;

    return true;
}

template<class T>
inline T DoublyLinkedList<T>::removeFirst()
{
    Node<T>* temp = this->head->next;
    T value = NULL;

    if (temp->endNode)
    {
        return NULL;
    }

    value = temp->value;

    this->head->next->next->previous = this->head;
    this->head->next = this->head->next->next;

    delete temp;

    return value;
}

template<class T>
inline T DoublyLinkedList<T>::removeLast()
{
    Node<T>* temp = this->tail->previous;
    T value = NULL;

    if (temp->startNode)
    {
        return NULL;
    }

    value = temp->value;

    this->tail->previous->previous->next = this->tail;
    this->tail->previous = this->tail->previous->previous;

    delete temp;

    return value;
}

template<class T>
inline bool DoublyLinkedList<T>::remove(T value)
{
    Node<T>* current = this->head;
    Node<T>* temp;

    if (current->next->endNode)
    {
        return false;
    }

    if (current->next->next->endNode && current->next->value == value)
    {
        temp = current->next;
        current->next = current->next->next;
        current->next->previous = current;

        delete temp;

        return true;
    }

    while (!current->next->endNode)
    {
        if (current->next->value == value)
        {
            temp = current->next;
            current->next = current->next->next;
            current->next->previous = current;

            delete temp;

            return true;
        }

        current = current->next;
    }

    return false;
}

template<class T>
inline bool DoublyLinkedList<T>::find(T value)
{
    Node<T>* current = this->head;

    while (!current->endNode)
    {
        if (current->value == value)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

template<class T>
inline int DoublyLinkedList<T>::count()
{
    Node<T>* current = this->head->next;
    int elements = 0;

    while (!current->endNode)
    {
        elements++;
        current = current->next;
    }

    return elements;
}

template<class T>
inline void DoublyLinkedList<T>::printAll()
{
    Node<T>* current = this->head;

    while (!current->endNode)
    {
        if (!current->startNode)
        {
            std::cout << current->value << " ";
        }

        current = current->next;
    }

    std::cout << std::endl;
}
