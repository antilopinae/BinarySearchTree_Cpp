//
// Created by antilopa on 12.05.24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdlib>

#include "TypeObject.h"
#include "VectorList.h"
#include "Exception.h"

template <class T>
class LinkedList{
private:
    TypeObject<VectorList<T>> * _end;
    TypeObject<VectorList<T>> * _top;
    size_t size = 0;
protected:
    void (*print_element)(T element);
public:
    LinkedList();
    T GetFirst();
    T GetLast() const;
    T Get(size_t index);
    size_t GetLength() const;
    void Append(const T item);
    void Prepend(const T item);
    void InsertAt(const T item, size_t index);
    void DeleteList();
    void Delete(size_t index);
    void Concat(LinkedList <T> * const list);
    void ForEach(void (*action)(T&));
    LinkedList<T>* GetSubsequence(size_t startIndex, size_t endIndex);
    ~LinkedList();
};


template <typename T>
LinkedList<T>::LinkedList() {
    _end = new TypeObject<VectorList<T>>();
    _top = new TypeObject<VectorList<T>>();
};

template <typename T>
T LinkedList<T>::GetFirst(){
    if(!_end->isEmpty()) return _end->getElement()->element;
    else throw IllegalException("Collection is empty!");
};


template <typename T>
T LinkedList<T>::GetLast() const{
    if(!_top->isEmpty()) return _top->getElement()->element;
    else throw IllegalException("Collection is empty!");
};


template <typename T>
T LinkedList<T>::Get(size_t index){
    VectorList<T>* next;
    if(!_end->isEmpty()) next = _end->getElement();
    else throw IllegalException("Collection is empty!");

    while(index > 0 && next -> next){
        --index;
        next = next -> next;
    }
    if(next && index == 0) return next -> element;
    else throw IndexOutOfBoundsException("Index out of bounds!");
};


template <typename T>
size_t LinkedList<T>::GetLength() const{
    VectorList<T>* next;
    size_t index = 1;
    if(!_end->isEmpty()) next = _end->getElement();
    else return 0;

    while( next -> next){
        ++index;
        next = next -> next;
    }
    return index;
};


template <typename T>
void LinkedList<T>::Append(const T item){
    VectorList<T>* top;
    if(!_top->isEmpty()) top = _top->getElement();
    else top = 0;

    VectorList<T>* element = new VectorList<T>{0, item, top};
    if(top) {
        top->next = element;
        _top->initialize(element);
    }
    else {
        _top->initialize(element);
        _end->initialize(element);
    }
};


template <typename T>
void LinkedList<T>::Prepend(T item){
    VectorList<T>* end;
    if(!_end->isEmpty()) end = _end->getElement();
    else end = 0;
    VectorList<T>* element = new VectorList<T>{end, item, 0};

    if(end){
        end->prev = element;
        _end->initialize(element);
    }
    else{
        _top->initialize(element);
        _end->initialize(element);
    }
};


template <typename T>
void LinkedList<T>::InsertAt(const T item, size_t index){
    if(index<0) throw IndexOutOfBoundsException("Index out of bounds!");
    if(_end->isEmpty() && index!=0) throw IndexOutOfBoundsException("Index out of bounds!");
    VectorList<T>* next;
    if(_end->isEmpty()) next = 0;
    else next = _end->getElement();

    if(next){
        while(index > 0 && next -> next){
            --index;
            next = next -> next;
        }
        VectorList<T>* element = new VectorList<T>{next, item, next->prev};
        if(next->prev){
            next->prev->next = element;
            next->prev = element;
        }
        else{
            _end->initialize(element);
        }
    }
    else{
        VectorList<T>* element = new VectorList<T>{0, item, 0};
        _top->initialize(element);
        _end->initialize(element);
    }
};

template <typename T>
void LinkedList<T>::Concat(LinkedList<T> * const list) {
    VectorList<T>* next;
    if(list->_end->isEmpty()) next = 0;
    else next = list->_end->getElement();

    while(next){
        this->Append(next->element);
        next = next->next;
    }
};

template <typename T>
void LinkedList<T>::ForEach(void (*action)(T&)) {
    VectorList<T>* next;
    if(!_end->isEmpty()) next = _end->getElement();

    while( next -> next){
        action(next->element);
        next = next -> next;
    }
};

template <typename T>
LinkedList<T>* LinkedList<T>::GetSubsequence(size_t startIndex, size_t endIndex) {
    if(startIndex>endIndex) throw IllegalException("Subsequence had a size less then zero");

    VectorList<T>* next;
    if(!_top->isEmpty()) next = _end->getElement();
    else throw IndexOutOfBoundsException("Index out of bounds!");

    size_t index = startIndex;

    while(index > 0 && next -> next){
        --index;
        next = next -> next;
    }
    if(!next) throw IndexOutOfBoundsException("Index out of bounds!");

    LinkedList<T>* collection = new LinkedList<T>();

    while(startIndex < endIndex && next->next){
        collection->Append(next->element);
        next = next->next;
        ++startIndex;
    }
    if(!next->next && startIndex < endIndex) throw IndexOutOfBoundsException("Index out of bounds!");

    collection->Append(next->element);
    return collection;
};

template <typename T>
void LinkedList<T>::Delete(size_t index){
    if(index<0) throw IndexOutOfBoundsException("Index out of bounds!");
    if(_end->isEmpty() && index!=0) throw IndexOutOfBoundsException("Index out of bounds!");

    VectorList<T>* next;
    if(_end->isEmpty()) next = 0;
    else next = _end->getElement();

    if(next){
        while(index > 0 && next -> next){
            --index;
            next = next -> next;
        }
        if(next->next && next->prev){
            next->prev->next = next -> next;
            next->next->prev = next -> prev;
            free(next);
        }
        else{
            if(next->next && !next->prev){
                next->next->prev = 0;
                VectorList<T>* _next = next->next;
                _end->reset();

                _end->initialize(_next);
            }
            else if(!next->next && next->prev){
                VectorList<T>* _prev = next->prev;
                _top->reset();
                _top->initialize(_prev);
                _prev->next = 0;
            }
            else{
                _end->reset();
                _top->resetEmpty();
            }
        }
    }
};

template <typename T>
void LinkedList<T>::DeleteList(){
    size_t length = this->GetLength();
    for(size_t i = 0; i < length; ++i){
        this->Delete(0);
    }
};

template <typename T>
LinkedList<T>::~LinkedList(){
    if(!_end->isEmpty()){
        VectorList<T> *next = _end->getElement();
        VectorList<T> *prev;
        while(next->next){
            prev = next;
            next = next->next;
            free(prev);
        }
        free(next);
    }
    delete _end;
    delete _top;
};

#endif // LINKED_LIST_H
