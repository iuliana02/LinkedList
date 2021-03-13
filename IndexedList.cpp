#include <exception>
#include <iostream>
#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() {
	//TODO - Implementation
    head = NULL; 
}

int IndexedList::size() const {
    //TODO - Implementation
    int count = 0;
    ListNode* current=head;//pointer nod
    while (current != NULL)
    {       
        current = current->Next;//current ia adresa urmatorului nod
        count++;
    }
    return count;
}


bool IndexedList::isEmpty() const {
    //TODO - Implementation
    if (size() == 0)
        return true;
    else
        return false;
}

TElem IndexedList::getElement(int pos) const {
    //TODO - Implementation
    ListNode* current=head;
    if (pos<0 || pos>size())
    {
        std::exception e;
        throw e;
    }
    if (current == NULL)
    {
        return current->Info;
    }
    int i = 0;
    while (i < pos)
    {
        current = current->Next;
        i++;
    }
    return current->Info;
}

TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
    if (pos<0 || pos>size() )
    {
        std::exception e;
        throw e;
    }
    ListNode* current=head;
    int i = 0;
    while (i < pos)
    {
        current = current->Next;
        if (current == NULL) //daca am ajuns la sfarsitul listei
            return;
        i++;
    }
    TElem aux = current->Info;
    current->Info = e;    
    return aux;
}

void IndexedList::addToEnd(TElem e) {
    //TODO - Implementation
    ListNode* nou = new ListNode; //am creat un nod nou
    nou->Info = e;
    nou->Next = NULL;
    if (head == NULL) //lista e goala
    {
        head = nou;
        return;
    }
    else //daca lista nu e goala, o parcurg pana la final
    {
        ListNode* current = head;
        while (current->Next != NULL)
            current = current->Next;
        current->Next = nou;
    } 
}

void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
    ListNode* nou = new ListNode; //am creat un nod nou (nodul pe care trebe sa il inserez)
    nou->Info = e;
    nou->Next = NULL;
    if (pos<0 || pos>size())
    {
        std::exception e;
        throw e;
    }
    else
        if (pos == 0)
        {
            nou->Next = head;
            head = nou;
            return;
        }
        else
        {
            ListNode* prev = new ListNode;
            prev = head;
            for (int i = 0; i < pos ; i++)
                prev = prev->Next;
            nou->Next = prev->Next;
            prev->Next=nou;
        }
}

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
    ListNode* current = head;
    if (pos<0 || pos>size() || current== NULL) //daca pozitia e invalida sau daca lista e goala
    {
        std::exception e;
        throw e;
    }
    TElem var = NULL_TELEM; //in var memorez valoarea nodul pe care il elimin

    if (pos == 0) // elimin nodul de pe prima pozitie
    {  
        ListNode* oldHead = head;
        var = head->Info;
        head = head->Next;
        delete oldHead;
        return var;
    }
    //nodul previous e nodul de dinainte de nodul care trebui eliminat si nodul after e cel de dupa
    //pt a elimina nodul, voi lega nodul previous de after
 
    int i = 1;
    ListNode* previous=current;
    current = current->Next;
    while (i < pos && current != NULL)
    {
        previous = current;
        current = current->Next;
        i++;
    }
    ListNode* after = current;
    after = current->Next;
    if (current != NULL)
    {
        previous->Next = after;
        var = current->Info;
        current->Next = NULL;
        delete current;
    }
    return var;
}

int IndexedList::search(TElem e) const{
    //TODO - Implementation
    ListNode* current = head;
    int i = 0;
    while (current != NULL && current->Info != e)
    {
        current = current->Next;
        i++;
    }
	return i;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//TODO - Implementation
    ListNode* current = head;
    while (current != 0) {
        ListNode* next = current->Next;
        delete current;
        current = next;
    }
    head = 0;
}