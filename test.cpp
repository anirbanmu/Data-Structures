#include <assert.h>

#include "singly_linked_list.h"

using namespace std;

void test_singly_linked_list()
{
    {
        const auto init_list = initializer_list<unsigned>{56, 4, 3, 656, 45};

        SinglyLinkedList<unsigned> l = init_list;
        print(l);

        SinglyLinkedList<unsigned> l2(l);
        print(l2);

        assert(l == l2);

        l2.reverse();
        print(l2);

        l2.append(l);
        print(l2);

        auto* found = l2.find(56);
        assert(found != nullptr);
        cout << found->data << endl;

        l2.insert_after(found, 2);
        print(l2);
    }
}

int main(int, char**)
{
    test_singly_linked_list();
    return 0;
}