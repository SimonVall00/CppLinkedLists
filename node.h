#pragma once

template <class T>
class Node
{
public:
    T value;
    Node<T>* next;
    Node<T>* previous;
    bool startNode;
    bool endNode;

    Node();
};

template<class T>
inline Node<T>::Node() : value(NULL), next(nullptr), previous(nullptr), startNode(false), endNode(false)
{
}
