#ifndef _SINGLY_LINKED_LIST_H_DEF_
#define _SINGLY_LINKED_LIST_H_DEF_

#include <assert.h>
#include <initializer_list>
#include <iostream>

template <typename T> class SinglyLinkedList
{
    public:
        struct Node
        {
            Node() : data(), next(nullptr)
            {
            }

            template <typename... Args> Node(Args... params) : data(params...), next(nullptr)
            {
            }

            bool operator==(const Node& other) const
            {
                return data == other.data;
            }

            bool operator!=(const Node& other) const
            {
                return !(data == other.data);
            }

            T data;
            Node* next;
        };

        SinglyLinkedList() : head(nullptr), back(nullptr), length(0)
        {
        }

        SinglyLinkedList(const std::initializer_list<T>& l) : SinglyLinkedList()
        {
            for (const auto& a : l)
            {
                emplace_back(a);
            }
        }

        SinglyLinkedList(const SinglyLinkedList<T>& other) : SinglyLinkedList()
        {
            copy_all(other);
        }

        ~SinglyLinkedList()
        {
            Node* current = front();
            while (current != nullptr)
            {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

        void append(const SinglyLinkedList<T>& other)
        {
            return copy_all(other);
        }

        template <typename... Args> Node* insert_after(Node* p, Args... params)
        {
            auto* next = p->next;
            p->next = new Node(params...);
            p->next->next = next;
            length++;
            if (p->next->next == nullptr)
            {
                back = p->next;
            }
            return p->next;
        }

        void erase(Node* p)
        {
            Node* current = front();
            if (current == p)
            {
                head = current->next;
            }
            else
            {
                while (current->next != p)
                {
                    current = current->next;
                }
                current->next = p->next;
            }
            length--;
            if (current->next == nullptr)
            {
                back = current;
            }
            delete p;
        }

        Node* find(const T& t)
        {
            Node* current = front();
            while (current != nullptr)
            {
                if (current->data == t)
                {
                    break;
                }
                current = current->next;
            }
            return current;
        }

        bool operator==(const SinglyLinkedList& other) const
        {
            if (other.length != length)
            {
                return false;
            }

            const Node* current_this = front();
            const Node* current_other = other.front();
            while (current_this != nullptr)
            {
                if (*current_this != *current_other)
                {
                    return false;
                }
                current_this = current_this->next;
                current_other = current_other->next;
            }

            return true;
        }

        template <typename... Args> Node* emplace_back(Args... params)
        {
            Node* p = new Node(params...);
            length++;
            if (back == nullptr)
            {
                assert(head == nullptr);
                head = back = p;
                return back;
            }
            back->next = p;
            return back = back->next;
        }

        Node* reverse()
        {
            if (length == 0)
            {
                return nullptr;
            }

            back = head;
            return head = reverse(head, nullptr);
        }

        Node* front()
        {
            return head;
        }

        const Node* front() const
        {
            return head;
        }

        std::size_t size() const
        {
            return length;
        }

    private:
        Node* head;
        Node* back;
        std::size_t length;

        static Node* reverse(Node* p, Node* append)
        {
            auto* next = p->next;
            p->next = append;
            if (next == nullptr)
            {
                return p;
            }

            return reverse(next, p);
        }

        void copy_all(const SinglyLinkedList<T>& other)
        {
            const Node* current_other = other.front();
            while (current_other != nullptr)
            {
                emplace_back(current_other->data);
                current_other = current_other->next;
            }
        }
};

template <typename T> void print(const SinglyLinkedList<T>& l)
{
    const auto* current = l.front();

    std::cout << '[';
    while (current != nullptr)
    {
        std::cout << current->data;
        current = current->next;
        if (current != nullptr)
        {
            std::cout << ", ";
        }
    }
    std::cout << ']' << std::endl;
}

#endif