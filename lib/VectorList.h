//
// Created by antilopa on 13.05.24.
//

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
struct VectorList{
    VectorList(VectorList<T>* _next, const T _element, VectorList<T>* _prev){
        this->next = _next;
        this->element = T{_element};
        this->prev=_prev;
    };
    T element;
    VectorList<T>* next;
    VectorList<T>* prev;
};

#endif //VECTOR_H
