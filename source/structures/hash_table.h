#pragma once

#define DEFAULT_HASH_SIZE 29

template <typename K, typename D> class Hash_table;
template <typename K, typename D> class Hash_table_iterator;

template <typename K, typename D>
class Hash_node
{
  friend class Hash_table<K, D>;
  friend class Hash_table_iterator<K, D>;
public:
  Hash_node();
  Hash_node(K key, D data);
private:
  K key;
  D data;

  Hash_node<K, D> *next;
};

template <typename K, typename D>
class Hash_table
{
public:
  Hash_table(int (*hash_function)(K key), int (*compare_to)(K key1, K key2));
  Hash_table(int (*hash_function)(K key), int (*compare_to)(K key1, K key2), int initial_size);
  ~Hash_table();

  void add(K key, D data);
  bool get(K key, D *data);
  void remove(K key);

  Hash_table_iterator<K, D> get_iterator() const;
private:
  int size;

  int (*hash_function)(K key);
  int (*compare_to)(K key1, K key2);

  int capacity;
  Hash_node<K, D> *table;
};

template <typename K, typename D>
class Hash_table_iterator
{
public:
  Hash_table_iterator(int size, Hash_node<K, D> *table);

  bool has_next() const;
  bool next(D *data);
private:
  int current_position;
  int nodes_left;

  Hash_node<K, D> *table;
  Hash_node<K, D> *current_node;
};

template <typename K, typename D>
Hash_node<K, D>::Hash_node()
{
  next = 0;
}

template <typename K, typename D>
Hash_node<K, D>::Hash_node(K key, D data)
  : key(key), data(data)
{
  next = 0;
}

template <typename K, typename D>
Hash_table<K, D>::Hash_table(int (*hash_function)(K key), int (*compare_to)(K key1, K key2))
  : hash_function(hash_function), compare_to(compare_to)
{
  size = 0;

  table = new Hash_node<K, D>[DEFAULT_HASH_SIZE];

  capacity = DEFAULT_HASH_SIZE;
}

template <typename K, typename D>
Hash_table<K, D>::Hash_table(int (*hash_function)(K key), int (*compare_to)(K key1, K key2), int initial_size)
  : hash_function(hash_function), compare_to(compare_to)
{
  size = 0;

  table = new Hash_node<K, D>[initial_size];

  capacity = initial_size;
}

template <typename K, typename D>
Hash_table<K, D>::~Hash_table()
{
  Hash_node<K, D> *to_delete;

  for(int i = 0; i < capacity; i++)
    while(table[i].next != 0)  {
      to_delete = table[i].next;

      table[i].next = table[i].next->next;

      delete to_delete;
    }

  delete [] table;
}

template <typename K, typename D>
void Hash_table<K, D>::add(K key, D data)
{
  int hash = (*hash_function)(key);

  Hash_node<K, D> *node = &table[hash % capacity];

  while(node->next != 0) {
    if(( *compare_to)(node->next->key, key) == 0)
      return;

    node = node->next;
  }

  node->next = new Hash_node<K, D>(key, data);

  size++;
}

template <typename K, typename D>
bool Hash_table<K, D>::get(K key, D *data)
{
  int hash = (*hash_function)(key);

  Hash_node<K, D> *node = &table[hash % capacity];

  while(node->next != 0) {
    if((*compare_to)(node->next->key, key) == 0)  {
      *data = node->next->data;

      return true;
    }

    node = node->next;
  }

  return false;
}

template <typename K, typename D>
void Hash_table<K, D>::remove(K key)
{
  int hash = (*hash_function)(key);

  Hash_node<K, D> *node = &table[hash % capacity];

  while(node->next != 0)  {
    if((*compare_to)(node->next->key, key) == 0)  {
      Hash_node<K, D> *to_delete = node->next;

      node->next = node->next->next;

      delete to_delete;

      size--;

      return;
    }

    node = node->next;
  }
}

template <typename K, typename D>
Hash_table_iterator<K, D> Hash_table<K, D>::get_iterator() const
{
  Hash_table_iterator<K, D> iterator(size, table);

  return iterator;
}

template <typename K, typename D>
Hash_table_iterator<K, D>::Hash_table_iterator(int size, Hash_node<K, D> *table)
  : table(table)
{
  nodes_left = size;

  current_node = table;

  current_position = 0;
}

template <typename K, typename D>
bool Hash_table_iterator<K, D>::has_next() const
{
  return nodes_left != 0;
}

template <typename K, typename D>
bool Hash_table_iterator<K, D>::next(D *data)
{
  if(nodes_left == 0)
    return false;

  if(current_node->next == 0)  {
    while(table[++current_position].next == 0);
  
    current_node = table[current_position].next;
  }
  else
    current_node = current_node->next;

  *data = current_node->data;

  nodes_left--;

  return true;
}
