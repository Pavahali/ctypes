[//]: # (It's licensed under MIT, btw)

# An implementation of different data structures in C

> Note: this was copied from https://github.com/Pavahali/templates

---

## Stack

> https://en.wikipedia.org/wiki/Stack_(abstract_data_type)


#### Types
| type                 | description                                                                         |
|:--------------------:|:------------------------------------------------------------------------------------|
| stack_t              | The stack itself. Should be assingned the value of `stack_new()` or zeroed manually |
| struct stack_item_t  | The item stored in the stack                                                        |

#### Methods
| method        | time complexity   | return value | arguments                                    | description                                                    |
|:-------------:|:-----------------:|:------------:|:--------------------------------------------:|:---------------------------------------------------------------|
| stack_new()   | O(1)              | stack_t      |                                              | Returns `stack_t` filled with zeroes                           |
| stack_empty() | O(1)              | int (bool)   | stack_t   `S`                                | Returns a boolean value indicating whether or not `S` is empty |
| stack_size()  | O(1)              | size_t       | stack_t   `S`                                | Returns the number of elements                                 |
| stack_top()   | O(1)              | void*        | stack_t   `S`                                | Accesses the top element                                       |
| stack_push()  | O(1)              |              | stack_t \*`S`<br>void \*`item`<br>size_t `N` | Inserts an element at the top                                  |
| stack_pop()   | O(1)              |              | stack_t \*`S`                                | Removes the top element                                        |


---

## Queue

> https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)


#### Types
| type                | description                                                                        |
|:-------------------:|:-----------------------------------------------------------------------------------|
| queue_t             | The queue itself. Should be assigned the value of `queue_new()` or zeroed manually |
| struct queue_item_t | The item stored in the queue                                                       |

#### Methods
| method        | time complexity | return value | arguments                                    | description                                                    |
|:-------------:|:---------------:|:------------:|:--------------------------------------------:|:---------------------------------------------------------------|
| queue_new()   | O(1)            | queue_t      |                                              | Returns `queue_t` filled with zeroes                           |
| queue_empty() | O(1)            | int (bool)   | queue_t   `Q`                                | Returns a boolean value indicating whether or not `Q` is empty |
| queue_size()  | O(1)            | size_t       | queue_t   `Q`                                | Returns the number of elements                                 |
| queue_front() | O(1)            | void*        | queue_t   `Q`                                | Accesses the first element                                     |
| queue_back()  | O(1)            | void*        | queue_t   `Q`                                | Accesses the last element                                      |
| queue_push()  | O(1)            |              | queue_t \*`Q`<br>void \*`item`<br>size_t `N` | Inserts an element at the end                                  |
| queue_pop()   | O(1)            |              | queue_t \*`Q`                                | Removes the last element                                       |

---

## Deque

> https://en.wikipedia.org/wiki/Double-ended_queue

#### Dependencies
* [comparator.c](comparator.c)

#### Types
| type                | description                                                                        |
|:-------------------:|:-----------------------------------------------------------------------------------|
| deque_t             | The deque itself, should be assigned the value of `deque_new()` or zeroed manually |
| struct deque_item_t | The item stored in the deque                                                       |

#### Methods
Note: Time complexity depends on the deque size

| method             | time complexity | return value | arguments                                                   | description                                                                                      |
|:------------------:|:---------------:|:------------:|:-----------------------------------------------------------:|:-------------------------------------------------------------------------------------------------|
| deque_new()        | O(1)            | queue_t      |                                                             | Returns `deque_t` filled with zeroes                                                             |
| deque_empty()      | O(1)            | int (bool)   | deque_t   `L`                                               | Returns a boolean value indicating wheether or not `L` is empty                                  |
| deque_size()       | O(1)            | size_t       | deque_t   `L`                                               | Returns the number of elements                                                                   |
| deque_front()      | O(1)            | void*        | deque_t   `L`                                               | Accesses the first element                                                                       |
| deque_back()       | O(1)            | void*        | deque_t   `L`                                               | Accesses the last element                                                                        |
| deque_push_front() | O(1)            |              | deque_t \*`L`<br>void \*`item`<br>size_t `N`                | Inserts an element to the beginning                                                              |
| deque_push_back()  | O(1)            |              | deque_t \*`L`<br>void \*`item`<br>size_t `N`                | Inserts an element at the end                                                                    |
| deque_pop_front()  | O(1)            |              | deque_t \*`L`                                               | Removes the first element                                                                        |
| deque_pop_back()   | O(1)            |              | deque_t \*`L`                                               | Removes the last element                                                                         |
| deque_insert()     | O(n)            |              | deque_t \*`L`<br>int `at`<br>void \*`item`<br>size_t `size` | Inserts an element at the specified index<br>(Acts as `deque_push_back()` if deque is too small) |
| deque_remove()     | O(n)            |              | deque_t \*`L`                                               | Removes an element at the specified inde.<br>(Does `nothing` if deque is too small)              |
| deque_at()         | O(n)            | void*        | deque_t   `L`                                               | Accesses an element at the specified index<br>(`0` if not found)                                 |
| deque_count()      | O(n)            | int          | deque_t   `L`<br>void \*`item`<br>size_t `size`             | Returns the number of elements mathing specific key                                              |

## Set

> https://en.wikipedia.org/wiki/Set_(abstract_data_type)


#### Types
| type            | description                                                                              |
|:---------------:|:-----------------------------------------------------------------------------------------|
| set_t           | The set itself, should be assigned the value of `set_new()` or initialised manually      |
| struct set_node | The item stored in the set (called node because set is implemented using red-black tree) |

#### Methods
| method       | time complexity | return value | arguments                                    | description                                                                                       |
|:------------:|:---------------:|:------------:|:--------------------------------------------:|:-------------------------------------------------------------------------------------------------:|
| set_new()    | O(1)            | set_t        | int (*`sgn_cmp`)(cmp_item_t a, cmp_item_t b) | Returns a properly initialised `set_t`. Takes [signum comparator](#signum-compare) as an argument |
| set_size()   | O(1)            | size_t       | set_t  `S`                                   | Returns the number of elements                                                                    |
| set_insert() | O(log n)        | void         | set_t *`S`, cmp_item_t `key`                 | Inserts an element                                                                                |
| set_delete() | O(log n)        | void         | set_t *`S`, cmp_item_t `key`                 | Deletes an element                                                                                |
| set_count()  | O(log n)        | int (bool)   | set_t *`S`, cmp_item_t `key`                 | Returns the number of elements matching specific key (is either 1 or 0)                           |


## Map

> https://en.wikipedia.org/wiki/Associative_array


#### Types
| type            | description                                                                              |
|:---------------:|:-----------------------------------------------------------------------------------------|
| map_t           | The map itself, should be assigned the value of `map_new()` or initialised manually      |
| struct map_node | The item stored in the map (called node because map is implemented using red-black tree) |

#### Methods
| method       | time complexity | return value | arguments                                        | description                                                                                       |
|:------------:|:---------------:|:------------:|:------------------------------------------------:|:-------------------------------------------------------------------------------------------------:|
| map_new()    | O(1)            | set_t        | int (*`sgn_cmp`)(cmp_item_t `a`, cmp_item_t `b`) | Returns a properly initialised `map_t`. Takes [signum comparator](#signum-compare) as an argument |
| map_size()   | O(1)            | size_t       | map_t  `S`                                       | Returns the number of elements                                                                    |
| map_insert() | O(log n)        | void         | map_t *`S`, cmp_item_t `key`                     | Inserts an element with the specified key                                                         |
| map_delete() | O(log n)        | void         | map_t *`S`, cmp_item_t `key`                     | Deletes an element with the specified key                                                         |
| map_find()   | O(log n)        | int (bool)   | map_t *`S`, cmp_item_t `key`                     | Accesses an element with the specified key                                                        |


---
<br>
---

## Helpers
### Comparators

> Comparators are a way to compare data independently of its type.


##### Types
| type       | description                                                |
|:----------:|:-----------------------------------------------------------|
| cmp_item_t | An element which can be compared independently of its type |

##### Methods
| method          | return value | arguments                   | description                                   |
|:---------------:|:------------:|:---------------------------:|:---------------------------------------------:|
| cmp_item()      | void*        | cmp_item_t `item`           | Accesses the data                             |
| cmp_item_new()  | cmp_item_t   | void \*`item`<br>size_t `N` | Initialises new comparable item               |
| cmp_item_copy() | cmp_item_t   | void \*`item`<br>size_t `N` | Allocates new comparable item and copies data |

##### Comparator definition

| return value | arguments                        |
|:------------:|:--------------------------------:|
| int          | cmp_item_t `a`<br>cmp_item_t `b` |


#### Boolean compare

> All boolean comparators answer the same question: "Does `a` have greater value than `b`?"
The definition of the value is up to the comparator


##### Size-only compare

> Compare by size (in bytes)


| method            | question                                               |
|:-----------------:|:-------------------------------------------------------|
| cmp_shorter(a, b) | Is the size of `a` less or equal than the size of `b`? |
| cmp_longer(a, b)  | Is the size of `a` longer than the size of `b`?        |


##### Byte-by-byte compare

> Compare items byte by byte, with the most significant value defined by the platform's default endianness


| method               | endianness         | question                     |
|:--------------------:|:------------------:|:-----------------------------|
| cmp_smaller(a, b)    | Platform's default | Is `a` less or equal to `b`? |
| cmp_greater(a, b)    | Platform's default | Is `a` greater than `b`?     |
| -------------------- | ------------------ | ---------------------------- |
| cmp_equal(a, b)      | Doesn't matter     | Is `a` equal to `b`?         |
| -------------------- | ------------------ | ---------------------------- |
| cmp_smaller_le(a, b) | Little-endian      | Is `a` less or equal to `b`? |
| cmp_greater_le(a, b) | Little-endian      | Is `a` greater than `b`?     |
| cmp_smaller_be(a, b) | Big-endian         | Is `a` less or equal to `b`? |
| cmp_greater_be(a, b) | Big-endlian        | Is `a` greater than `b`?     |


#### Signum compare

> Returns:

| value | condition |
|:-----:|:---------:|
| -1    | a < b     |
|  0    | a == b    |
|  1    | a > b     |

| method              | endianness         | question                                         |
|:-------------------:|:------------------:|:-------------------------------------------------|
| cmp_sgn_size(a, b)  | Platform's default | What is the result of sgn(`a.size` - `b.size`)?  |
| cmp_sgn(a, b)       | Platform's default | What is the result of sgn(`a` - `b`)?            |
| cmp_sgn_le(a, b)    | Little-endian      | What is the result of sgn(`a` - `b`)?            |
| cmp_sgn_be(a, b)    | Big-endlian        | What is the result of sgn(`a` - `b`)?            |
