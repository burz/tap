#include <cstdlib>

template <typename T> class Stack;

template <typename T>
class Stack_node
{
	friend class Stack< T >;
public:
	Stack_node(T data, Stack_node< T > *next);
private:
	T data;
	Stack_node<T> *next;
};

template <typename T>
class Stack
{
public:
	Stack();
	~Stack();

	void push(T data);
	bool top(T *data) const;
	bool pop(T *data);

	bool is_empty() const;
	int get_size() const;
private:
	int size;
	Stack_node<T> *head;
};

template <typename T>
Stack_node<T>::Stack_node(T data, Stack_node< T > *next)
	: data(data), next(next)
{
}

template < typename T >
Stack< T >::Stack()
{
	size = 0;
	head = NULL;
}

template < typename T >
Stack< T >::~Stack()
{
	Stack_node< T > *to_delete;

	while(size != 0) {
		to_delete = head;

		head = head->next;

		delete to_delete;
	}
}

template < typename T >
void Stack< T >::push(T data)
{
	Stack_node< T > *new_node = new Stack_node< T >(data, head);

	head = new_node;

	size++;
}

template < typename T >
bool Stack< T >::top(T *data) const
{
	if(size == 0)
		return false;

	*data = head->data;

	return true;
}

template < typename T >
bool Stack< T >::pop(T *data)
{
	if(size == 0)
		return false;

	data* = head->data;

	Stack_node< T > *to_delete = head;

	head = head->next;

	delete to_delete;

	size--;

	return true;
}

template < typename T >
bool Stack< T >::is_empty() const
{
	return head == NULL;
}

template < typename T >
int Stack< T >::get_size() const
{
	return size;
}
