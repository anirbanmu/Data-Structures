#include <assert.h>
#include <vector>
#include <algorithm>

#include "singly_linked_list.h"

using namespace std;

template <typename T, typename U> void verify_equal(const T& expected, const SinglyLinkedList<U>& actual)
{
    assert(expected.size() == actual.size());

    const auto* node = actual.front();
    for (const auto& e : expected)
    {
        assert(e == node->data);
        node = node->next;
    }
    assert(node == nullptr);
}

void test_singly_linked_list()
{
    {
        const auto init_list = initializer_list<unsigned>{56, 4, 3, 656, 45};

        SinglyLinkedList<unsigned> l = init_list;
        verify_equal(init_list, l);

        SinglyLinkedList<unsigned> l2(l);
        verify_equal(init_list, l2);

        assert(l == l2);

        l2.reverse();
        auto l2_expected = vector<unsigned>(init_list);
        reverse(l2_expected.begin(), l2_expected.end());
        verify_equal(l2_expected, l2);

        l2.append(l);
        l2_expected.insert(l2_expected.end(), init_list.begin(), init_list.end());
        verify_equal(l2_expected, l2);

        auto* found = l2.find(56);
        assert(found != nullptr);
        assert(found->data == 56);

        l2.insert_after(found, 2);
        l2_expected.insert(++find(l2_expected.begin(), l2_expected.end(), 56), 2);
        verify_equal(l2_expected, l2);

        l2.erase(found);
        l2_expected.erase(find(l2_expected.begin(), l2_expected.end(), 56));
        verify_equal(l2_expected, l2);

        found = l2.find(45);
        assert(found != nullptr);
        assert(found->data == 45);
        assert(found == l2.front());

        l2.erase(found);
        l2_expected.erase(find(l2_expected.begin(), l2_expected.end(), 45));
        verify_equal(l2_expected, l2);
    }
}

int main(int, char**)
{
    test_singly_linked_list();
    return 0;
}