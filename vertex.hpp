#ifndef MY_VERT
#define MY_VERT

template <class Type >
class vertex
{
struct node
{
Type item ;
node * link ;
};
public :
class edgeIterator
{
public :
friend class vertex ;
edgeIterator ();
edgeIterator ( node *);
edgeIterator operator ++( int );
Type operator *();
bool operator ==( const edgeIterator &);
bool operator !=( const edgeIterator &);
private :
node * current ;
};
vertex ();
vertex ( const vertex &);
const vertex & operator =( const vertex &);
~ vertex ();
edgeIterator begin ();
edgeIterator end ();
void addEdge ( const Type &);
private :
node *neighbors ;
};

template <class Type >
vertex<Type>::edgeIterator::edgeIterator(){
    current = nullptr;
}
template <class Type >
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge){
    current = edge;
}
template <class Type >
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int){
    this->current = current->link;
    return this->current;
}
template <class Type >
Type vertex<Type>::edgeIterator::operator*(){
 return current->item;
}

template <class Type >
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs){
 return this->current == rhs.current;
}

template <class Type >
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs){
 return this->current != rhs.current;
}

template <class Type >
vertex<Type>::vertex(){
    neighbors = nullptr;
}

template <class Type >
vertex<Type>::vertex(const vertex<Type>& copy){
    edgeIterator edge = copy.begin();
    while(edge != nullptr){
        this->addEdge(edge);
        edge++;
    }
}

template <class Type >
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs){
    edgeIterator edge = rhs.begin();
    while(edge != nullptr){
        this->addEdge(edge);
        edge++;
    }

    return this;
}

template <class Type >
vertex<Type>::~vertex(){
    node *temp;
    while(neighbors != nullptr){
        temp = neighbors;
        neighbors = neighbors->link;
        delete temp;
    }
}

template <class Type >
typename vertex<Type>::edgeIterator vertex<Type>::begin(){
    edgeIterator curr(neighbors);

    return curr;
}

template <class Type >
typename vertex<Type>::edgeIterator vertex<Type>::end(){
    edgeIterator curr(neighbors);
    while(curr != nullptr){
        curr++;
    }

    return curr;
}

template <class Type >
void vertex<Type>::addEdge(const Type& edge){
    node *tmp;
    tmp = new node;
    tmp->item = edge;
    if (neighbors == nullptr) {
        tmp->link = nullptr;
    }
    tmp->link = neighbors;
    neighbors = tmp;
}

#endif