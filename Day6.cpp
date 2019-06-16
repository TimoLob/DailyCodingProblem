#include<iostream>
/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields, 
it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list; 
it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to get_pointer and dereference_pointer functions that converts between nodes and memory addresses.
*/


/*
Addr1 xor Addr2 => both
Addr1 xor both => Addr2
Addr2 xor both => Addr1
*/

using namespace std;

template <class T>
class Node {
public:
	T value;
	Node<T> *both;

	Node()
	{
		both = nullptr;
	}
};





template <class T>
class XorLinkedList {
	private:
		Node<T> *head;


		// Helper Funktion to xor 2 node pointers
		Node<T> *nodeXOR(Node<T> *p1, Node<T> *p2)
		{
			return (Node<T> *)((uintptr_t)p1 ^ (uintptr_t)p2);
		}


	public:
		XorLinkedList()
		{
			head = nullptr;

		}
		
		Node<T> *get(int index)
		{
			Node<T> *ptr = head;
			Node<T> *prev = nullptr;
			Node<T> *next = nodeXOR(ptr->both, prev);
			for (int i = 0;i < index; i++)
			{
				prev = ptr;
				ptr = next;
				next = nodeXOR(ptr->both, prev);
			}
			return ptr;
		}


		void add(T value)
		{
			
			if (isEmpty())
			{
				head = new Node<T>();
				head->value = value;
				head->both = nodeXOR(nullptr, nullptr);
				return;
			}
			
			// Find the last Node
			Node<T> *ptr = head;
			Node<T> *prev = nullptr;
			Node<T> *next = nodeXOR(ptr->both,prev);
			while (next!=0)
			{
				prev = ptr;
				ptr = next;
				next = nodeXOR(ptr->both, prev);
			}


			Node<T> *newNode = new Node<T>();
			newNode->value = value;
			
			Node<T> *newPrev = ptr;
			Node<T> *newNext = nullptr;

			Node<T> *ptrNext = newNode;
			Node<T> *ptrPrev = prev;

			newNode->both = nodeXOR(newPrev, newNext);
			ptr->both = nodeXOR(ptrPrev, ptrNext);

		

		}

		bool isEmpty()
		{
			return head==nullptr;
		}

	
};

int main()
{
	XorLinkedList<int> *list = new XorLinkedList<int>();
	for (int i = 0;i < 10;i++)
		list->add(i * 3);

	for (int i = 0; i < 10;i++)
		cout << list->get(i)->value << endl;
	getchar();
}