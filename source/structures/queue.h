#include <cstdio>

template <typename T> class Queue;

template <typename T>
class Queue_node
{
	friend class Queue<T>;
public:
	Queue_node(T data);
private:
	T data;
	Queue_node<T> *next;
};

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

	void enqueue(T data);
	bool dequeue(T *data);

	bool is_empty() const;
	int get_size() const;
private:
	int size;
	Queue_node<T> head;
	Queue_node<T> *back;
};

template <typename T>
Queue_node<T>::Queue_node(T data)
	: data(data)
{
	next = NULL;
}

template <typename T>
Queue< T >::Queue()
	: head(0)
{
	size = 0;

	back = &head;
}

template <typename T>
Queue< T >::~Queue()
{
	Queue_node<T> *to_delete;

	while(head.next != NULL)  {
		to_delete = head.next;
		head.next = head.next->next;

		delete to_delete;
	}
}

template <typename T>
void Queue<T>::enqueue(T data)
{
	back->next = new Queue_node<T>(data);

	back = back->next;

	size++;
}

template <typename T>
bool Queue<T>::dequeue(T *data)
{
	if(size == 0)
		return false;

	*data = head.next->data;

	Queue_node<T> *to_delete = head.next;

	head.next = head.next->next;

	delete to_delete;

	size--;

	if(size == 0)
		back = &head;

	return true;
}

template <typename T>
bool Queue<T>::is_empty() const
{
	return head.next == NULL;
}

template <typename T>
int Queue<T>::get_size() const
{
	return size;
}

