#ifndef MY_VERT
#define MY_VERT

#include <utility> // for std::swap

template <class Type>
class vertex {
    struct node {
        Type item;
        node* link;
        node(const Type& i, node* l = nullptr) : item(i), link(l) {}
    };

public:
    class edgeIterator {
    public:
        // STL iterator typedefs (minimal)
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = Type*;
        using reference         = Type&;

        edgeIterator() : current(nullptr) {}
        explicit edgeIterator(node* n) : current(n) {}

        reference operator*() const { return current->item; }
        pointer operator->() const { return &(current->item); }

        // Pre-increment
        edgeIterator& operator++() {
            if (current) current = current->link;
            return *this;
        }
        // Post-increment
        edgeIterator operator++(int) {
            edgeIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const edgeIterator& rhs) const { return current == rhs.current; }
        bool operator!=(const edgeIterator& rhs) const { return current != rhs.current; }

    private:
        node* current;
        friend class vertex;
    };

    vertex() : neighbors(nullptr) {}

    vertex(const vertex& other) : neighbors(nullptr) {
        copyFrom(other);
    }

    vertex& operator=(const vertex& rhs) {
        if (this != &rhs) {
            clear();
            copyFrom(rhs);
        }
        return *this;
    }

    ~vertex() { clear(); }

    edgeIterator begin() const { return edgeIterator(neighbors); }
    edgeIterator end() const { return edgeIterator(nullptr); }

    void addEdge(const Type& edge) {
        neighbors = new node(edge, neighbors);
    }

private:
    node* neighbors;

    void clear() {
        while (neighbors) {
            node* temp = neighbors;
            neighbors = neighbors->link;
            delete temp;
        }
    }

    void copyFrom(const vertex& other) {
        // Copy in reverse, then reverse again to preserve order
        node* rev = nullptr;
        for (node* curr = other.neighbors; curr; curr = curr->link) {
            rev = new node(curr->item, rev);
        }
        // Now add in correct order
        while (rev) {
            addEdge(rev->item);
            node* temp = rev;
            rev = rev->link;
            delete temp;
        }
    }
};

#endif
