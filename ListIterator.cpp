#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

//Constructor pt iterator: initializez current(iteratorul) cu list.head
//Complexitate: Q(1) pt toate cazurile
ListIterator::ListIterator(const IndexedList& list) : list(list){
   //TODO - Implementation
   current = list.head;
}

//Complexitate: Q(1) pt toate cazurile
void ListIterator::first(){
    //TODO - Implementation
    current = list.head;
}

//Complexitate: best,worst,average=Q(1), fiindca se modifica doar adresa nodului curent
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

//Verifica daca iteratorul nu are adresa NULL;  complexitate: Q(1) in toate cazurile
bool ListIterator::valid() const{
    //TODO - Implementation
    if (current!= NULL)
        return true;
	return false;
}

//Returneaza valoarea nodului de la adresa curenta, iar daca adresa e invalida arunca o exceptie
//Complexitate: Q(1) pt toate cazurile
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
