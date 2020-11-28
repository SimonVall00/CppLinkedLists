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
class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

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
};

template<class T>
inline SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr)
{
    Node<T>* startNode = DBG_NEW Node<T>;
    Node<T>* endNode = DBG_NEW Node<T>;

    startNode->startNode = true;
    endNode->endNode = true;
    startNode->next = endNode;

    this->head = startNode;
}

template<class T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
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
inline void SinglyLinkedList<T>::insertFirst(T value)
{
    Node<T>* newNode = DBG_NEW Node<T>;

    newNode->value = value;
    newNode->next = this->head->next;

    this->head->next = newNode;
}

template<class T>
inline void SinglyLinkedList<T>::insertLast(T value)
{
    Node<T>* newNode = DBG_NEW Node<T>;
    Node<T>* current = this->head;

    newNode->value = value;

    if (current->next->endNode)
    {
        newNode->next = current->next;
        current->next = newNode;
        return;
    }

    while (!current->next->endNode)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

template<class T>
inline bool SinglyLinkedList<T>::insertAfter(T newValue, T afterValue)
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

    return true;
}

template<class T>
inline bool SinglyLinkedList<T>::insertBefore(T newValue, T beforeValue)
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

    return true;
}

template<class T>
inline T SinglyLinkedList<T>::removeFirst()
{
    Node<T>* temp = this->head->next;
    T value = NULL;

    if (temp->endNode)
    {
        return NULL;
    }

    this->head->next = temp->next;
    value = temp->value;

    delete temp;

    return value;
}

template<class T>
inline T SinglyLinkedList<T>::removeLast()
{
    Node<T>* current = this->head;
    Node<T>* temp;
    T value = NULL;

    if (current->next->endNode)
    {
        return NULL;
    }

    while (!current->next->next->endNode)
    {
        current = current->next;
    }

    temp = current->next;
    value = current->next->value;
    current->next = current->next->next;

    delete temp;

    return value;
}

template<class T>
inline bool SinglyLinkedList<T>::remove(T value)
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

        delete temp;

        return true;
    }

    while (!current->next->endNode)
    {
        if (current->next->value == value)
        {
            temp = current->next;
            current->next = current->next->next;

            delete temp;

            return true;
        }

        current = current->next;
    }

    return false;
}

template<class T>
inline bool SinglyLinkedList<T>::find(T value)
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
inline int SinglyLinkedList<T>::count()
{
    Node<T>* current = this->head->next;
    int elements = 0;

    while (!current->endNode) {
        elements++;
        current = current->next;
    }

    return elements;
}

template<class T>
inline void SinglyLinkedList<T>::printAll()
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
