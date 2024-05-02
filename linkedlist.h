#include <utility>
#include <stddef.h>
#include <stdexcept>

// Forward declaration so I can use it as a friend class
template <typename T>
class LinkedList;

template <typename T>
class Node
{
	// LinkedList can rearrange pointers as needed but no public consumers should be able to
	friend class LinkedList<T>;

	T data;
	Node *next = nullptr;
	Node *prev = nullptr;

	// Constructor / Destructor
	Node(const T& data) : data(data) {}
	Node(T&& data) noexcept : data(std::move(data)) {}
	~Node() = default;

	// Copy constructor
	Node(const Node& copy) : data(copy.data), next(copy.next), prev(copy.prev) {}

	Node(Node&& move) : data(std::move(move.data)),
						next(move.next),
						prev(move.prev)
	{
		move.next = nullptr;
		move.prev = nullptr;
	}

	const T& getData()
	{
		return data;
	}
};

template <typename T>
class LinkedList
{
	// Private members
	Node<T> *head;
	Node<T> *tail;

	// Internal insertion function
	void insertAt(Node<T>* new_node, size_t index)
	{
		// We don't have to iterate for the easy case at the beginning
		if (index == 0)
		{
			new_node->next = head;
			if (head != nullptr)
			{
				head->prev = new_node;
			}
			head = new_node;
			if (tail == nullptr)
			{
				tail = new_node;
			}
			return;
		}

		// Iterate through the linked list until we find the index we want
		auto current_node = head;
		size_t current_index = 0;
		while (current_node != nullptr && current_index < index - 1)
		{
			current_node = current_node->next;
			current_index++;
		}
		// Bail if index doesn't exist in LinkedList
		if (current_node == nullptr)
		{
			// Clean up before exception
			delete new_node;
			throw std::out_of_range("LinkedList: Index out of range");
		}

		// Splice the new node in and we're done!
		new_node->next = current_node->next;
		new_node->prev = current_node;
		if (current_node->next != nullptr)
		{
			current_node->next->prev = new_node;
		}
		else
		{
			// Update tail if inserting at end
			tail = new_node;
		}
		current_node->next = new_node;
	}

public:
	LinkedList() : head(nullptr), tail(nullptr){};
	~LinkedList()
	{
		while (head != nullptr)
		{
			Node<T> *temp = head->next;
			delete head;
			head = temp;
		}
	}

	void insert(const T& data, size_t index)
	{
		auto new_node = new Node<T>(data);
		insertAt(new_node, index);
	}

	void emplace(T&& data, size_t index)
	{
		auto new_node = new Node<T>(std::move(data));
		insertAt(new_node, index);
	}

	void remove(size_t index)
	{
		if (head == nullptr)
		{
			throw std::out_of_range("LinkedList: cannot remove, head empty");
		}

		if (index == 0)
		{
			auto old_head = head;
			head = head->next;
			if (head != nullptr)
			{
				head->prev = nullptr;
			}
			else
			{
				tail = nullptr;
			}
			delete old_head;
			return;
		}

		// Iterate through the linked list until we find the index we want
		auto current_node = head;
		size_t current_index = 0;
		while (current_node != nullptr && current_index < index - 1)
		{
			current_node = current_node->next;
			current_index++;
		}
		// Bail if index doesn't exist in LinkedList
		if (current_node == nullptr)
		{
			// Clean up before exception
			throw std::out_of_range("LinkedList: Index out of range");
		}

		// Found it! Fix the next node and previous node's pointers
		if (current_node->next != nullptr)
		{
			current_node->next->prev = current_node->prev;
		}
		else
		{
			tail = current_node->prev;
		}
		current_node->prev->next = current_node->next;
		delete current_node;
	}

	T& operator[](size_t index)
	{
		if (index < 0)
		{
			throw std::out_of_range("LinkedList: Index out of range");
		}
		auto current_node = head;
		int count = 0;
		while (current_node != nullptr && count < index)
		{
			current_node = current_node->next;
			count++;
		}
		if (current_node == nullptr)
		{
			throw std::out_of_range("LinkedList: Index out of range");
		}
		return current_node->data;
	}

	// Iterator class
	class Iterator
	{
	private:
		Node<T> *current_node;

	public:
		Iterator(Node<T> *node) : current_node(node) {}

		T& operator*() const
		{
			return current_node->data;
		}

		Iterator &operator++()
		{
			current_node = current_node->next;
			return *this;
		}

		Iterator &operator--()
		{
			current_node = current_node->prev;
			return *this;
		}

		bool operator!=(const Iterator &other) const
		{
			return current_node != other.current_node;
		}
	};

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	Iterator cursorFrom(size_t index)
	{
		if (index < 0)
		{
			throw std::out_of_range("LinkedList::Iterator: Index out of range");
		}
		auto current_node = head;
		int count = 0;
		while (current_node != nullptr && count < index)
		{
			current_node = current_node->next;
			count++;
		}
		if (current_node == nullptr)
		{
			throw std::out_of_range("LinkedList::Iterator: Index out of range");
		}
		return Iterator(current_node);
	}

	// Reverse iterator class
	class ReverseIterator
	{
	private:
		Node<T> *current_node;

	public:
		ReverseIterator(Node<T> *node) : current_node(node) {}

		T& operator*() const
		{
			return current_node->data;
		}

		ReverseIterator &operator++()
		{
			current_node = current_node->prev;
			return *this;
		}

		ReverseIterator &operator--()
		{
			current_node = current_node->next;
			return *this;
		}

		bool operator!=(const ReverseIterator &other) const
		{
			return current_node != other.current_node;
		}
	};

	ReverseIterator rbegin()
	{
		return ReverseIterator(tail);
	}

	ReverseIterator rend()
	{
		return ReverseIterator(nullptr);
	}

	ReverseIterator rcursorFrom(size_t index)
	{
		if (index < 0)
		{
			throw std::out_of_range("LinkedList::ReverseIterator: Index out of range");
		}
		auto current_node = head;
		int count = 0;
		while (current_node != nullptr && count < index)
		{
			current_node = current_node->next;
			count++;
		}
		if (current_node == nullptr)
		{
			throw std::out_of_range("LinkedList::ReverseIterator: Index out of range");
		}
		return ReverseIterator(current_node);
	}
};