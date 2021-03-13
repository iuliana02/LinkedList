#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>


ListIterator::ListIterator(const IndexedList& list) : list(list){
   //TODO - Implementation
   current = list.head;
}

void ListIterator::first(){
    //TODO - Implementation
    current = list.head;
}

void ListIterator::next(){
    //TODO - Implementation
    if (current!=NULL)
        current = current->Next;
    else
    {
        std::exception e;
        throw e;
    }
}

bool ListIterator::valid() const{
    //TODO - Implementation
    if (current!= NULL)
        return true;
	return false;
}

TElem ListIterator::getCurrent() const{
   //TODO - Implementation
    if (valid() == true)
        return current->Info;
    else
    {
        std::exception e;
        throw e;
    }
}