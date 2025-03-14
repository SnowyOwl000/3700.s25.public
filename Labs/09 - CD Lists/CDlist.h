//
// Created by bob on 4/3/20.
//
// Updated by bob on 3/13/23.
//

#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <cstdint>
#include <stdexcept>

template <typename ListType>
struct CDListNode {
    ListType
        datum;
    CDListNode<ListType>
        *next;
};

template <typename ListType>
class CDList {
public:
        
    //=========================================================================
    //--------------------------- common operations ---------------------------
    //=========================================================================

    //=========================================================================
    // LinearList()
    //  constructor
    //

    CDList() {

        head = nullptr;     // as discussed in the slides
        count = 0;
    }

    //=========================================================================
    // LinearList(LinearList<ListType> &l)
    //  copy constructor
    //

        CDList(CDList<ListType> &l) {
            CDListNode<ListType>
                *ptr,
                *tmp=l.head,
                **prev = &head;

            // count once for each node in existing list
            for (uint32_t i=0;i<l.count;i++) {
                // make a new node
                ptr = new CDListNode<ListType>;

                // copy one value from existing list
                ptr->datum = tmp->datum;

                // attach new node to end of new list
                *prev = ptr;

                // move pointer (to pointer) to end of new list
                prev = &((*prev)->next);

                // move to next node in existing list
                tmp = tmp->next;
            }

            count = l.count;
        }

    //=========================================================================
    // ~LinearList()
    //  destructor
    //

    ~CDList() { clear(); }

    //=========================================================================
    // uint32_t size()
    //  return size of list (number of nodes)
    //

    uint32_t size() { return count; }

    //=========================================================================
    // bool isEmpty()
    //  return true if list is empty, false otherwise
    //

    bool isEmpty() { return count == 0; }

    //=========================================================================
    // void clear()
    //  remove all nodes from list, reset head and count
    //
    // Notes:
    // - uses a counted loop instead of looking for the nullptr. that way, if
    //   this is changed to a circular list (which has no null pointers), the
    //   code won't be affected.
    //

    void clear() {
        CDListNode<ListType>
            *tmp;

        for (int i=0;i<count;i++) {
            tmp = head->next;           // remember second node in the list
            delete head;                // remove the first node
            head = tmp;                 // second node moves to front
        }

        head = nullptr;                 // all nodes removed, reset list
        count = 0;
    }

    //=========================================================================
    //----------------------- list-specific operations ------------------------
    //=========================================================================

    //=========================================================================
    // uint32_t search(const ListType &key)
    //  search for key in the list
    //
    // Parameter:
    //  key - what to look for
    //
    // Returns:
    //  - index of first occurrence if key exists in the list
    //  - throws a domain_error exception if key is not in the list
    //

    uint32_t search(const ListType &key) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        for (int i=0;i<count;i++) {     // step through the list
            if (key == tmp->datum)      // if key found, stop and return index
                return i;
            tmp = tmp->next;            // walk to next node
        }

        // if we get here, the key was not in the list
        throw std::domain_error("key not found");
    }

    //=========================================================================
    // ListType &operator[](int32_t pos)
    //  return reference to element at given position, works like array []
    //
    // Parameter:
    //  pos - position in the list to access
    //
    // Returns:
    //  - reference to specified element in the list
    //  - throws a domain_error exception if pos is invalid (< 0 or >= count)
    //

    ListType &operator[](int32_t pos) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        if (pos < 0 || pos >= count)
            throw std::domain_error("Invalid index");

        for (int i=0;i<pos;i++)         // step through the list
            tmp = tmp->next;            // walk to next node

        return tmp->datum;              // return reference;
    }

    //=========================================================================
    // void map(void (*fp)(ListType &))
    //  apply given function to each element in the list
    //
    // Parameter:
    //  fp - pointer to function to call
    //

    void map(void (*fp)(ListType &)) {
        CDListNode<ListType>
            *tmp = head;                // start at head of list

        for (int i=0;i<count;i++) {     // step through the list
            (*fp)(tmp->datum);          // call the function, pass the datum
            tmp = tmp->next;            // walk to next node
        }
    }

    //=========================================================================
    // void insert(uint32_t pos,const ListType &d)
    //  insert element into the list
    //
    // Parameters:
    //  pos - position of new element; subsequent elements shifted
    //    d - value to be inserted
    //
    // Notes:
    //  - throws a domain_error exception if pos is invalid (> count)
    //  - predecessor work is done by pointing to the pointers. this allows all
    //    positions in the list to be treated identically, without regard to
    //    whether it is the list object or a node pointing to the new node.
    //    conceptually the walking process is the same.
    //

    void insert(uint32_t pos, const ListType &d) {
        CDListNode<ListType>
            *ptr,
            **pred;

        // step 0: validate pos
        if (pos > count)
            throw std::domain_error("Invalid index");

        // step 1: allocate new node and place datum
        ptr = new CDListNode<ListType>;
        ptr->datum = d;

        // step 2: find the predecessor
        pred = &head;
        for (int i=0;i<pos;i++)
            pred = &((*pred)->next);	// walk to next pointer

        // step 3: copy predecessor's next pointer to new node
        ptr->next = *pred;

        // step 4: predecessor points to new node
        *pred = ptr;

        // step 5: update count
        count++;
    }

    //=========================================================================
    // void remove(uint32_t pos)
    //  remove element from the list
    //
    // Parameter:
    //  pos - position of element to be removed; subsequent elements shifted
    //
    // Notes:
    //  - throws a domain_error exception if pos is invalid (>= count)
    //  - predecessor work is done by pointing to the pointers. this allows all
    //    positions in the list to be treated identically, without regard to
    //    whether it is the list object or a node pointing to the new node.
    //    conceptually the walking process is the same.
    //

    void remove(uint32_t pos) {
        CDListNode<ListType>
            *ptr,
            **pred;

        // step 0: validate pos
        if (pos >= count)
            throw std::domain_error("Invalid index");

        // step 1: find the predecessor
        pred = &head;
        for (int i=0;i<pos;i++)
            pred = &((*pred)->next);

        // step 2: remember node to be deleted
        ptr = *pred;

        // step 3: copy ntbd's pointer to predecessor... pointing around ntbd
        *pred = ptr->next;

        // step 4: delete the node
        delete ptr;

        // step 5: update count
        count--;
    }

private:
    CDListNode<ListType>
        *head;
    uint32_t
        count;

};

#endif //LINEARLIST_H
