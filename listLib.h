//FREE TO CUSTOMIZE

/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

class DSAException
{
    int _error;
    string _text;

  public:
    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char *text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string &getErrorText() { return _text; }
};

template <class T>
struct L1Item
{
    T data;
    L1Item<T> *next;
    L1Item() : next(NULL) {}
    L1Item(T &a) : data(a), next(NULL) {}
};

template <class T>
class L1List
{
  public:
    L1Item<T> *_head; // The head pointer of linked list
    L1Item<T> *_tail; //The end pointer of linked list
    size_t _size;     // number of elements in this list
  public:
    L1List() : _head(NULL), _size(0) {}
    void clean();
    bool isEmpty()
    {
        return _head == NULL;
    }
    size_t getSize()
    {
        return _size;
    }
    T &operator[](int i);

    int push_back(T &a);
    int insertHead(T &a);

    int removeHead();
    int removeLast();
    void traverse(void (*op)(T &))
    {
        L1Item<T> *p = _head;
        while (p)
        {
            op(p->data);
            p = p->next;
        }
    }
    void traverse(void (*op)(T &, void *), void *pParam)
    {
        L1Item<T> *p = _head;
        while (p)
        {
            op(p->data, pParam);
            p = p->next;
        }
    }
};
template <class T>
T &L1List<T>::operator[](int i)
{
    L1Item<T> *ptmp = _head;
    for (int index = 0; index < i; index++)
    {
        ptmp = ptmp->next;
    }
    return ptmp->data;
}
/// Insert item to the end of the list
template <class T>
int L1List<T>::push_back(T &a)
{
    if (isEmpty())
    {
        _head = _tail = new L1Item<T>(a);
    }
    else
    {
        _tail->next = new L1Item<T>(a);
        _tail = _tail->next;
    }
    _size++;
    return 0;
}
/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a)
{
    L1Item<T> *p = new L1Item<T>(a);
    p->next = _head;
    _head = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead()
{
    if (_head)
    {
        L1Item<T> *p = _head;
        _head = p->next;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast()
{
    if (_head)
    {
        if (_head->next)
        {
            L1Item<T> *prev = _head;
            L1Item<T> *pcur = prev->next;
            while (pcur->next)
            {
                prev = pcur;
                pcur = pcur->next;
            }
            delete pcur;
            prev->next = NULL;
        }
        else
        {
            delete _head;
            _head = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}
#endif //A01_LISTLIB_H
