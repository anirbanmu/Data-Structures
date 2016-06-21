#include <assert.h>

#include "singly_linked_list.h"

void test_singly_linked_list()
{
    {
        const auto init_list = std::initializer_list<unsigned>{56, 4, 3, 656, 45};

        SinglyLinkedList<unsigned> l = init_list;
        print_singly_linked_list(l);

        SinglyLinkedList<unsigned> l2(l);
        print_singly_linked_list(l2);

        assert(l == l2);

        l2.reverse();
        print_singly_linked_list(l2);
    }
}

int main(int, char**)
{
    test_singly_linked_list();
    return 0;
}