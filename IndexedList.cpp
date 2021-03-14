#include <exception>
#include <iostream>
#include "IndexedList.h"
#include "ListIterator.h"

//Mentionez ca la testQuantity() dureaza mai mult la rulare (in jur de 1 min sau mai mult)

//voi nota Q ca si Theta
//Constructor pt lista (nu avem o lista propriu-zisa, ci cu ajutorul lui head, care initial e NULL, se formeaza aceasta)
//Complexitate: Q(1) in toate cazurile
IndexedList::IndexedList() {
	//TODO - Implementation
    head = NULL; 
}

//parcurge toate nodurile si returneaza lungimea listei (nr de noduri)
//Complexitate: best case:Q(1), worst case:O(n), average: O(n)
int IndexedList::size() const {
    //TODO - Implementation
    int count = 0;
    ListNode* current;//pointer nod
    current = head;
    while (current != NULL)
    {
        current = current->Next;//current ia adresa urmatorului nod
        count++;
    }
    return count;
}

//Daca lungimea listei e 0, adica nu sunt deloc noduri, returnez true, altfel fals
//Complexitate: best=worst=average case = Q(1)
bool IndexedList::isEmpty() const {
    //TODO - Implementation
    if (size() == 0)
        return true;
    else
        return false;
}

//Gasesc nodul de la o pozitie data si returnez valoarea nodului(Info)
//Complexitate: best:Q(1), worst=average=O(n)
TElem IndexedList::getElement(int pos) const {
    //TODO - Implementation
    ListNode* current=head; //am facut un nod cu care sa parcurg lista
    if (pos<0 || pos>size()) //daca pozitia e invalida, arunc o exceptie
    {
        std::exception e;
        throw e;
    }
    if (current->Next == NULL) //daca e primul element
    {
        return current->Info;
    }
    int i = 0;
    while (i < pos) //cat timp nu am ajuns la pozitia dorita, merg mai departe in lista cu next
    {
        current = current->Next; //current ia adresa urmatorului nod
        i++;
    }
    return current->Info; //returnez valoarea nodului
}

//Caut un nod dupa o pozitie data si ii modific valoarea
//Complexitate: best:Q(1), worst=average=O(n)
TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
    TElem aux = NULL_TELEM; //in aux memorez valoarea veche
    if (pos<0 || pos>size()) //pozitie invalida
    {
        std::exception e;
        throw e;
    }
    ListNode* current=head;
    int i = 0;
    while (i < pos)
    {
        i++;
        current = current->Next;
    }
    aux = current->Info; //valoarea veche o memorez in aux
    current->Info = e; //modific valoarea    
    return aux; //returnez valoarea veche
}

//Complexitate: best:Q(1)(cand lista e goala); worst=Q(n); average=O(n)- trebuie parcursa lista pana la final pt a adauga nodul
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
        while (current->Next != NULL) //parcurg lista cu next
            current = current->Next;
        current->Next = nou; //aici am ajuns la finalul listei, deci inserez nodul, dandu-i lui current adresa noului nod
    } 
}

//Complexitate: best:Q(1)(cand inserez pe prima pozitie), worst=average=O(n)
void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
    ListNode* nou = new ListNode; //am creat un nod nou (nodul pe care trebe sa il inserez)
    nou->Info = e;
    nou->Next = NULL;
    if (pos<0 || pos>size()) //pozitie invalida
    {
        std::exception e;
        throw e;
    }
    else
        if (pos == 0) //cand inserez pe prima pozitie, modific headul
        {
            nou->Next = head;
            head = nou;
            return;
        }
        else
        {
            ListNode* prev = new ListNode; //prev va fi nodul de dinainte de cel care trebuie inserat
            prev = head;
            for (int i = 0; i < pos ; i++) //merg cu prev pana la pozitia pos (nu ajung pe pos,ci pe pos-1)
                prev = prev->Next;
            nou->Next = prev->Next; //noul nod va primi adresa nodului care ar fi urmat dupa prev
            prev->Next=nou;
        }
}

//Complexitate: best=Q(1), worst=Q(n), average=O(n)
TElem IndexedList::remove(int pos) {
    //TODO - Implementation
    ListNode* current = head;
    TElem var = NULL_TELEM; //in var memorez valoarea nodului pe care il elimin

    if (pos<0 || pos>size()-1) //daca pozitia e invalida, arunc exceptie
    {
        std::exception e;
        throw e;
    }

    if (pos == 0) // elimin nodul de pe prima pozitie prin faptul ca mut headul pe urmatoarea pozitie
    {  
        ListNode* oldHead = head;
        var = head->Info;
        head = head->Next;
        delete oldHead;
        return var;
    }

    //nodul previous e nodul de dinainte de nodul care trebuie eliminat si nodul after e cel de dupa
    //pt a elimina nodul, voi lega nodul previous de after 
    int i = 1;
    ListNode* previous;
    ListNode* after;
    previous = current;
    current = current->Next;
    after = current;
    after = after->Next;
    while (i < pos )
    {
        previous = previous->Next;
        current = current->Next;
        after = after->Next;
        i++;

    }
    if (previous->Next == NULL) //daca mai este un singur element in lista
    {
        var = previous->Info;
        delete previous;
        previous = head;
        return var;
    }
    if (after==NULL) //cazul in care e ultimul element din lista
    {
        previous->Next=NULL; //previous devine ultimul nod din lista
        var = current->Info;
        delete current;
        return var;
    }
    else //daca nu s-a incadrat in unul din cazurile de mai sus, inseamna ca nodul pe care vreau sa il elimin e pe la mijlocul listei
    {
        previous->Next = after; //previous ia adresa lui after, ca si cand se sare peste un nod
        var = current->Info;
        current->Next = NULL; //sterg atat adresa, cat si elementul
        delete current;
        return var;

    }
}

//Complexitate: best=Q(1), worst=Q(n), average=O(n)
//Cauta un element dupa valoare si returneaza prima aparitie sau -1 daca nu se afla in lista
int IndexedList::search(TElem e) const{
    //TODO - Implementation
    ListNode* current = head;
    int i = 0;
    if (head->Info == e) //daca e primul element
        return 0;
    while (current!=NULL)
    {
        if (current->Info == e) //aici am gasit elementul
            return i;
        current = current->Next;
        i++;
    }
    return -1; //elementul cu valoarea e nu se afla in lista
}

//Complexitate: Q(1) in toate cazurile
//Construieste un obiect de tip iterator
ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

//Complexitate: best=Q(1), worst=average=O(n)
//Destructor
IndexedList::~IndexedList() {
	//TODO - Implementation
    if (!isEmpty()) //daca lista nu e goala
    {
        ListNode* current = head;
        while (current != NULL) { //cat timp mai sunt noduri, parcurg lista si le sterg
            ListNode* next = current->Next;
            delete current;
            current = next;
        }
        head = NULL;
    }
}

//functia suplimentara
//Elimin noduri din k in k
void IndexedList::k_te_Element(int k)
{
    ListNode* current = head;
    if (k<0 || k>size() - 1) //daca pozitia e invalida, arunc exceptie
    {
        std::exception e;
        throw e;
    }
    int i = 0;
    while (i < size()-1)
    {
        if (current != NULL)
            remove(i);
        i = i + k-1; //-1 fiindca am eliminat deja un nod (pt a merge din k in k)
        int aux = k-1;
        while (aux > 0 && current!=NULL) //vreau sa ma mut la nodul urmator adica +k
        {
            if (current == NULL)
                break;
            current = current->Next;
            aux--;
        }
    }
}
//Complexitatea ar fi Q(n) pe toate cazurile fiindca trebuie sa parcurg toata lista
//Am comentat apelul functiei suplimentare fiindca imi arunca o exceptie si nu am mai avut timp sa o repar