//
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include <array>

namespace dsa {
    // Node class
    template <typename T>
    class Node {
    public:
        // Properties
        T data;
        Node<T> *next;

        // Constructor
        Node() : data(NULL), next(NULL){};
        Node(T x) : data(x), next(NULL){};

        void setData(T data) {
            this->data = data;
        }

        T getData() {
            return this->data;
        }

        void setNext(Node<T> next) {
            this->next = next;
        }

        T getNext() {
            return this->next;
        }
    };
    // Linkedlist class
    template <typename T>
    class LinkedList {
    public:
        // Properties
        Node<T> *head;
        Node<T> *tail;
        int size;

        // Constructor
        LinkedList() : head(NULL), tail(NULL), size(0){};

        // Functions
        void addToList(T data) {
            Node<T> *newNode = new Node<T>(data);
            // List is empty
            if (size == 0) {
                this->head = newNode;
                this->tail = newNode;
                this->head->next = tail;
                this->size++;
            }
            else {
                this->tail->next = newNode;
                this->tail = newNode;
                this->size++;
            }


            // List is not empty
        }

        void printList() {
            Node<T> *tempNode = this->head;

            while(tempNode->next != NULL) {
                std::cout << tempNode->data << "\n";
                tempNode = tempNode->next;
            }
            std::cout << tempNode->data << "\n";
        }
    };

};

int main() {
    std::cout << "Test" << '\n';
    std::array<std::string, 5> mytest = {"I", "AM", "TESTING", "MY", "CODE"};;
    std::array<int, 5> mytest2 = {1, 2, 3, 4, 5};

    dsa::LinkedList<std::string> myList;

    for (std::string i : mytest) {
        myList.addToList(i);
    }

    myList.printList();
    return 0;
}