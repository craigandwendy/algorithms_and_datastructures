# Datastructures


## Pointer
Imagine the memory of your computer is a city, with thousands or even millions of households. A friend invites you to his/her house, at this point there are two possibilities to reach the house, either you check the whole city or more likely you check his/her address, which is (a lot) faster.

A pointer is just a variable that holds the address of some memory. For example the pointer P equals to 0x235a4, this means nothing else then: At memory address 0x0031c we have a variable P that contains the value (of type address) 0x235a4. It is important to understand, that we interact via variables instead of the real values. Meaning variable A with address 0x235a4 equals 5. We can either print the address of A (-> 0x235a4) or we can print the value of A (-> 5).

|  Variable  |  Address  |  Value  |
|  --------  |  -------  |  -----  |
|     P      |  0x0031c  | 0x235a4 |
|     A      |  0x235a4  |    5    |

In C code this will look like this
```
void main() {
  int A = 5;
  int *P = &A;

  // let's print the addresses of A and P
  printf("%p", &P);  // 0x0x0031c
  printf("%p", &A);  // 0x235a4

  // let's print the value of A and P
  printf("%d", A);  // 5
  printf("%p", P);  // 0x235a4 -> here we have to use %p because P stores an address and not an integer

  // It is possible to print the value of A without actually using A
  print("%d", *P);  // we call * dereferencing which is nothing other than: Go to the address stored in P and print it's value
}
```

Although pointers seem to be a quite abstract concept, they come in handy when we have to dynamically allocate memory. Dynamic memory allocation means: We don't know how long our array is going to be, maybe the user will only need size 10 and maybe 1000000000000. Dynamic memory allocation is needed, because if we always create an array with size 10000000000 our memory will be very soon exceeded, meaning we cannot load any further values.

It is also possible to create a long chain of pointers.

|  Variable  |  Address  |  Value  |
|  --------  |  -------  |  -----  |
|     A      |  0x00001  | 0x00002 |
|     B      |  0x00002  | 0x00003 |
|     C      |  0x00003  | 0x00004 |
|     D      |  0x00004  | 0x00005 |
|     E      |  0x00005  | 0x00006 |
|     F      |  0x00006  | 0x00007 |
|     G      |  0x00007  | 0x00008 |
|     H      |  0x00008  | 0x00009 |
|     I      |  0x00009  | 0x00010 |
|     J      |  0x00010  |    5    |

Starting at A, following this long chain will end at J and return the value 5. Some might have noticed that this is quite similar to an array, when we increment the index i by 1 we get to the next value (actually: We increment the address by 1 and that's how we iterate). Here we see how an array is actually implemented in C (probably also in other programming languages). Once the size is defined, our machine searches for a place in memory, where n consecutive addresses are free (or available). But what if inside our memory every second address is already occupied? In this case we are not able to intialize an array of any size greater than 1. Using pointers we can avoid this problem.

|  Variable  |  Address  |  Value  |
|  --------  |  -------  |  -----  |
|     A      |  0x00001  | 0x00003 |
|     B      |  0x00002  |Occupied |
|     C      |  0x00003  | 0x00005 |
|     D      |  0x00004  |Occupied |
|     E      |  0x00005  | 0x00007 |
|     F      |  0x00006  |Occupied |
|     G      |  0x00007  | 0x00009 |
|     H      |  0x00008  |Occupied |
|     I      |  0x00009  | 0x00010 |
|     J      |  0x00010  |    5    |

Our chain of pointers look like this:

```
|-------|   |-------|   |-------|   |-------|   |-------|   |-------|
|0x00003|-->|0x00005|-->|0x00007|-->|0x00009|-->|0x00010|-->|   5   |
|-------|   |-------|   |-------|   |-------|   |-------|   |-------|
```

Using our known variables A to J we can access every element in O(1). But we need to store N variables, which is hard when we don't know how bi N will be.

In the table showing our memory we cannot define an array of size greater 1. Our machine tries to find consecutive free memory, which does not exist, but the pointer will not face these problems. As a reader you might ask yourself: ,,Ok, we created a kind of chain, but our chain only contains one single value!''. Yes, this is totally correct. In the next chapter, we will introduce ("a tool") how we can have such a chain, where we can store at any address additional values.


## Linked List

In the previous section we have seen, how pointers are defined and we already touched a little bit on the topic of arrays. Here, we are going to discuss, how pointer can be used to create dynamic arrays (arrays that can change their size).

#### Struct

Before actually introducing the concept of a struct (also known as structure), we will first have a look at our memory from the previous section.

|  Variable  |  Address  |  Value  |
|  --------  |  -------  |  -----  |
|     A      |  0x00001  | 0x00003 |
|     B      |  0x00002  |Occupied |
|     C      |  0x00003  | 0x00004 |
|     D      |  0x00004  |Occupied |
|     E      |  0x00005  | 0x00005 |
|     F      |  0x00006  |Occupied |
|     G      |  0x00007  | 0x00009 |
|     H      |  0x00008  |Occupied |
|     I      |  0x00009  | 0x00010 |
|     J      |  0x00010  |    5    |

The question came up: How can we store along our chain of pointers additional values, such that we create a kind of dynamic array. Well the answer is quite easy, why don't we define our own datastructure? This is the central concept of structs. Let's have a look at the code and how one can imagine this inside our memory. From now own we will not use the term chain of pointers but stick to linked list.

```
struct Node {
  int value;  // along our linked list we want to save integers
  struct Node *next;  // this is how we can go to the next value
}

void insert_ele(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref; /* used in step 5*/

    new_node->value = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
      last = last->next;
    }

    last->next = new_node;
    return;
}

void main() {
  int N = 5;  // our linked list has length 5
  int i;

  struct Node *head = Null;  // every linked list has a head, this is the entry point of our list

  for (i=1;i<N;i++) {
    insert_ele(&head, i);
  }
  
}
```

The reader might ask, what are we actually doing here. No worries, we will look at it more in detail in the next section. It is important to get the concept of structs.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    -    |0x00003 |
|            |  0x00002  |Occupied |
|            |  0x00003  |    0    |0x00005 |
|            |  0x00004  |Occupied |
|            |  0x00005  |    1    |0x00007 |
|            |  0x00006  |Occupied |
|            |  0x00007  |    2    |0x00009 |
|            |  0x00008  |Occupied |
|            |  0x00009  |    3    |0x00010 |
|            |  0x00010  |    4    |  Null  |

By using structs we can create our own data structure. In the code we call it Node. Every Node that we insert in our linked list, has a value and a pointer pointing to the next value (=it contains the address where the next value is saved). Once the process is finished it is not possible to access a value in O(1), we cannot do something like this arr[3], but we have to iterate through our linked list, starting at the head, this is one tradeoff between arrays and linked lists.

This is how we can also illustrate our linked list, with our own defined datastructure struct Node:

```
|--Val--|--Next--|   |--Val--|--Next--|   |--Val--|--Next--|   |--Val--|--Next--|   |--Val--|--Next--|   |--Val--|--Next--|
|   -   |0x00003 |-->|   0   |0x00005 |-->|   1   |0x00007 |-->|   2   |0x00009 |-->|   3   |0x00010 |-->|   4   |  NULL  |
|-------|--------|   |-------|--------|   |-------|--------|   |-------|--------|   |-------|--------|   |-------|--------|
```

The last element of a linked list always points to Null meaning it does not point anywhere. Since the memory allocation is random, we can never predict the address of our next Node, also since the address of every Node, excluding the head, is only temporary stored, we cannot access any element in O(1) like in arrays. We have to iterate through our linked list to access all elements. The iteration starts from the head and then follows goes to the address stored in next.


What is important: we have seen that using structs we can create our own datastructure, this enables us to create a chain of pointers, where we can store at every address along the chain additional values.

#### Singly Linked List

In the previous section we have seen what structs are, and how we can use them. In this section, we will restruture the code from above and show how the linked list is actually created.

```
struct Node {
  int value;  // along our linked list we want to save integers
  struct Node *next;  // this is how we can go to the next value
}

void insert_ele(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;  // used in step 5

    new_node->value = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
      last = last->next;
    }

    last->next = new_node;
    return;
}

void main() {
  int N = 3;  // our linked list has length 3
  int i;

  struct Node *head = Null;  // every linked list has a head, this is the entry point of our list

  for (i=1;i<N;i++) {
    insert_ele(&head, i);
  }
  
}
```

Inside main() we defined a Node head. head is nothing else than a variable that will work as our entry point for our linked list. We don't really care about the address of the other nodes, as we simply do not need them, to get access to our linked list, but it is important to have an entry point, the entry point must never change, else we might not be able to reach our linked list.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |   NULL  |        |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |         |        |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|            |  0x00010  |         |        |

This is how our memory looks like before calling create_linked_list(). When we call insert_ele() the following is happening. At the beginning we defined a temporary pointer called last, which first points to head. Then a node is created, with our value and pointer to the next element. First we check if head equals NULL. If True, we can directly insert our value at the beginning. head->next will be randomly decided, and is usually the first free next memory address, in this case 0x00003.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    0    |  NULL  |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |         |        |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|    last    |  0x00010  | 0x00001 |        |

In the second iteration, last will check if head is NULL, this is False, therefore we're entering the while loop and follow our chaing, until we reached the end.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    0    |0x00003 |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |    1    |  NULL  |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|    last    |  0x00010  | 0x00003 |        |

This is then repeated until we end our for loop


|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    0    |0x00003 |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |    1    |0x00005 |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |    2    |  NULL  |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|    last    |  0x00010  | 0x00005 |        |

At this stage we have finished our iteration and end our function. We have built our first linked list!

#### Doubly Linked List

As the name already suggests, a doubly linked list is a linked list, with two pointers, one is next and one is previous. The advantage of this is, that it is possible to start from the beginning or from the end. This allows us to search elements in O(0.5*N) which is O(N) at the end of the day. On the other side, a doubly linked list uses more memory as every node has a second pointer, more data = more memory used.

Let's have a look of how our previous singly linked list looks like as a doubly linked list

|  Variable  |  Address  |  Value  |  Next  |  Previous  |
|  --------  |  -------  |  -----  |  ----  |  --------  |
|    head    |  0x00001  |    0    |0x00003 |            |
|            |  0x00002  |Occupied |        |            |
|            |  0x00003  |    1    |0x00005 |  0x00001   |
|            |  0x00004  |Occupied |        |            |
|            |  0x00005  |    2    |  NULL  |  0x00003   |
|            |  0x00006  |Occupied |        |            |
|            |  0x00007  |         |        |            |
|            |  0x00008  |Occupied |        |            |
|            |  0x00009  |         |        |            |
|    last    |  0x00010  | 0x00005 |        |            |

The idea of a doubly linked list or even a n-linked list is used in many other datastructures e.g., a binary tree is a doubly linked list, then there are trees with 3 outgoing pointers (red-black trees), etc. You can lookup the implementation of doubly linked lists for example in binary_search_tree.c. But let's still have a look at the struct used.

```
// struct for doubly linked lists
struct Node {
  int value;
  struct Node* next;
  struct Node* previous;
}

// struct for "normal" trees
struct Node {
  int value;
  struct Node* left;   // left is the next left pointer
  struct Node* right;  // right is the next right pointer
}

// struct for red black trees
struct Node {
  int value;
  struct Node* parent;  // pointer to previous
  struct Node* left;
  struct Node* right;
}
```


## Stack

If you have heard about recursion you must have already enountered or heared about stacks. How can we imagine a stack in real life? You have a collection of CDs one of top of each other. Now you want to play one CD that is in the middle of the stack. To access it you have to remove every CD one by one until you find the CD you have looked for. This operation is called pop. The opposite operation, stacking CDs one by one, is called push. These are the two basic operations that can be performed on a stack. Let's go to a more abstract level now. A stack is a singly linked list, where elements are always inserted at the beginning and removed at the beginning, instead of updating the end, we update head everytime one of the two operators is done.

Now we will have a look at an example:

```
This is an initialized stack, without any elements

|_____|<--head
```

Let's push 3

```
|  3  |<--head
|_____|
```

push(2) then push(1)

```
|  1  |<--head
|  2  |
|  3  |
|_____|
```

We can also create a second stack, we will pop our first stack and than take the popped element and push it on the second stack.

```
|  1  |<--head   |_____|<--head
|  2  |
|  3  |
|_____|
```

pop() does not need any arguments, because we always remove the element at the head.

```
|  2  |<--head   |  1  |<--head
|  3  |          |_____|
|_____|
```

Let's pop the remaining element resulting into this:


```
|_____|<--head   |  3  |<--head
                 |  2  |
                 |  1  |
                 |_____|
```

Stacks use a LIFO principle. Last in first out, our last element pushed on the left stack is the first one that was popped.



## Queue

You have probably had many situations where you came across a queue e.g., waiting in a grocery store, creating a music playlist, even a traffic jam is a queue. So what do all of these examples have in common? Well the principle is called FIFO, written out: first in first out. In other words we insert an element at the tail of a linked list, this operation is call enqueue. When we dequeue an element from our linked list we remove the element at the head.

Let's see an example, first we will intiliaze a queue, then enqueue some element and dequeue some elements.

```
head
| Val  |  Next  |   |
| Null |  Null  |-->|
|______|________|   |
tail

enqueue(1)

head
| Val  |  Next  |   | Val  |  Next  |   |
| Null |  Null  |-->|  1   |  Null  |-->|
|______|________|   |______|________|   |
                     tail

enqueue(2)

head
| Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   |
| Null |  Null  |-->|  1   |  Null  |-->|  2   |  Null  |-->|
|______|________|   |______|________|   |______|________|   |
                                         tail

enqueue(3)

head
| Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   |
| Null |  Null  |-->|  1   |  Null  |-->|  2   |  Null  |-->|  3   |  Null  |-->|
|______|________|   |______|________|   |______|________|   |______|________|   |
                                                             tail

dequeue()

head
| Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   |
| Null |  Null  |-->|  2   |  Null  |-->|  3   |  Null  |-->|
|______|________|   |______|________|   |______|________|   |
                                         tail

enqueue(1)

head
| Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   | Val  |  Next  |   |
| Null |  Null  |-->|  2   |  Null  |-->|  3   |  Null  |-->|  1   |  Null  |-->|
|______|________|   |______|________|   |______|________|   |______|________|   |
                                                             tail
```

Know you have seen how a queue works, for the implementation I ask you to have a look in queue.c. In the example we just made, we have two pointers: a head and a tail. While the head never changes the tail always gets updated and points on the last element. What is the advantage of having a tail pointer? In the section singly linked list, we learned that it is not possible to access any value in O(1) in a linked list, this means we always have to start at the head and iterate until we arrive at the tail. This takes O(N) time, which generally can be considered ok, but if we have a pointer always pointing at the last element, we can insert elements in O(1) time, which is a lot better than O(N). Of course the tail pointer takes up some extra memory, but this little amount of memory compared to O(N) vs O(1) is completely worth the tradeoff.

## Trees

Up until now, we have seen the most basic datastructures. Now we are going to expand our knowledge and skills to build more complex datastructures, that have many advantages and which allow to optimize time and space complexity.

#### Binary-Tree

Let's define a (d-ary) tree generally:
* Every tree must have a root
* Every root must have at least null branches (the tree trunk is also considered to be a branch)

Definition binary tree:
* It must have a root
* It can have 0, 1 or 2 children

Now that we have defined a tree generally, let's have a look on binary trees. As the name suggest binary trees, are trees whose root has exactly two branches.

```
This is a basic tree (actually the most basic form of a tree is just the root)
   Root
   /  \
left  right

A Node looks like this, every Node is also a root (think of it as a recursive concept)

|-------------------------|
|   l   |   val   |   r   |
| 0x004 |    3    | 0x009 |
|-------------------------|

A binary tree is a slightly modified linked list, instead of pointing to previous and next, it points to two next elements, which are called left and right.

We can also make a bigger binary tree

         Root
         /   \
        l     r
       / \   / \
      l   r  l  r

```

At this point we must introduce the binary search tree. It is a binary tree with some additional contstraints

Definition binary search tree:
* It must have a root
* It can have 0, 1 or 2 children
* root->left->value < root->value
* root->right->value > root->value

The binary search tree allows to search elements in a linked list in log(n) time respectively in O(n), on average still better than a linked list with O(n). Also a binary search tree is considered sorted, so sorting is O(1), we can apply some tree traversal algorithms and print out an array resp. a list in O(n). Insertion takes between log(n) and O(n), depending how balanced the tree is.


#### Red-Black-Tree

A red-black-tree is a binary search tree with some more constraints. It uses colors to color each node this ensures that the tree always stays balanced such that searching and inserting take O(log(n)).


#### Further Variants

There are other balanced binary trees. You can look them up on the internet:

https://www.geeksforgeeks.org/types-of-binary-tree/

## Hash Tables

A hash table is an array, where every element of the array is a linked list. Similar to a matrix with N rows but and every row has between 0 and M columns. Every hash table has a hash function, which can be defined by the user. The idea of a hash function is to distribute all elements uniformly, such that we can reduce the look up time to O(N/k) where k is the number of slots and N is the number of all elements, respectively O(1). You can kind of imagine a hash table as an excel spreadsheet.

#### Open Addressing

Collisions in hash tables happen quite often. A collision is: when A is already at HT[2] and B was also assigned to HT[2]. But since HT[2] is already occupied, it has to move to another slot. Open Addressing solves this problem by simply assigning B to another slot. The advantage of this distribution process is, that every slot will take at most 1 element, in best case we can look up the value in O(1) in worst case O(n). Depending on the hash function we use we can reduce the average runtime.

#### Chaining

Unlike open addressing chaining does not care about collisions. In fact when there is a collision, chaining just takes the element and inserts it at the head of the linked list. Example: A is at HT[2], B get assigned to HT[2] -> collision. Insert B at the head of HT[2]. The linked list is a slightly modified stack. The advantage of chaining is, that we can always find the slot in O(1) where the value was stored. The disadvantage is, that we have to iterate through the linked list to find the element. So the worst case is O(n), assuming the elements are uniformly distributed we can reduce it to O(N/k), where k is the number of slots, if we choose k big enough, we can even bring it down to O(1) in theory, practically this will take up too much memory.
