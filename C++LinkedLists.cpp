// C++LinkedLists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "doubly_linked_list.h"

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

int main()
{
    DoublyLinkedList<int>* list = DBG_NEW DoublyLinkedList<int>;

    list->insertFirst(11);
    list->insertFirst(12);
    list->insertLast(14);

    list->printAll();

    delete list;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
