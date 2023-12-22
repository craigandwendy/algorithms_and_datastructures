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
|     C      |  0x00003  | 0x00004 |
|     D      |  0x00004  |Occupied |
|     E      |  0x00005  | 0x00005 |
|     F      |  0x00006  |Occupied |
|     G      |  0x00007  | 0x00009 |
|     H      |  0x00008  |Occupied |
|     I      |  0x00009  | 0x00010 |
|     J      |  0x00010  |    5    |

Here we cannot define an array of size greater 1. Our machine tries to find consecutive free memory, which does not exist, but the pointer will not face these problems. As a reader you might ask yourself: ,,Ok, we created a kind of chain, but our chain only contains one single value!''. Yes, this is totally correct. In the next chapter, we will introduce ("a tool") how we can have such a chain, where we can store at any address additional values.


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

The question came up: How can we store along our chain of pointers additional values, such that we create a kind of dynamic array. Well the answer in quite easy, why don't we define our own datastructure? This is the central concept of structs. Let's have a look at the code and how one can imagine this inside our memory. From now own we will not use the term chain of pointers but stick to linked list.

```
struct Node {
  int value;  // along our linked list we want to save integers
  struct Node *next;  // this is how we can go to the next value
}

void main() {
  int N = 5;  // our linked list has length 5
  int i;

  struct Node *head = Null;  // every linked list has a head, this is the entry point of our list
  struct Node *temp = head;  // we create a temp variable that starts at head
  
  for (i=0;i<N;i++) {
    temp->next->value = i;  // the value of temp->next equals to i
    temp = temp->next;      // now we move temp to the next pointer, etc.
  }
  
}
```

The reader might ask, what are we actually doing here. No worries, we will look at it more in detail in the next section. It is important to get the concept of structs.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    -    |0x00003 |
|            |  0x00002  |Occupied |
|            |  0x00003  |    0    |0x00004 |
|            |  0x00004  |Occupied |
|            |  0x00005  |    1    |0x00005 |
|            |  0x00006  |Occupied |
|            |  0x00007  |    2    |0x00009 |
|            |  0x00008  |Occupied |
|            |  0x00009  |    3    |0x00010 |
|            |  0x00010  |    4    |  Null  |

By using structs we can create our own data structure. In the code we call it Node. Every Node that we insert in our linked list, has a value and a pointer pointing to the next value (=it contains the address where the next value is saved). Once the process is finished it is not possible to access a value in O(1), we cannot do something like this arr[3], but we have to iterate through our linked list, starting at the head, this is one tradeoff between arrays and linked lists.

What is important: we have seen that using structs we can create our own datastructure, this enables us to create a chain of pointers, where we can store at every address along the chain additional values.

#### Singly Linked List

In the previous section we have seen what structs are, and how we can use them. In this section, we will restruture the code from above and show how the linked list is actually created.

```
struct Node {
  int value;  // along our linked list we want to save integers
  struct Node *next;  // this is how we can go to the next value
}

void create_linked_list(struct node* head, int N) {
  struct Node *temp = head;  // we create a temp variable that starts at head
  for (i=0;i<N;i++) {
    temp->next->value = i;  // the value of temp->next equals to i
    temp = temp->next;      // now we move temp to the next pointer, etc.
  }
}

void main() {
  int N = 3;  // our linked list has length 3
  int i;

  struct Node *head = Null;  // every linked list has a head, this is the entry point of our list

  create_linked_list(head, N);
  
}
```

Inside main() we defined a Node head. head is nothing else than a variable that will work as our entry point for our linked list. We don't really care about the address of the other nodes, as we simply do not need them, to get access to our linked list, but it is important to have an entry point, the entry point must never change, else we might not be able to reach our linked list.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    -    |        |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |         |        |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|            |  0x00010  |         |        |

This is how our memory looks like before calling create_linked_list(). When we call create_linked_list() the following is happening. At the beginning we defined a temporary pointer equal to head.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    -    |        |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |         |        |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|    temp    |  0x00010  | 0x00001 |        |

In the very first iteration, our machine is looking for free memory that can be populated with some value.

|  Variable  |  Address  |  Value  |  Next  |
|  --------  |  -------  |  -----  |  ----  |
|    head    |  0x00001  |    -    |        |
|            |  0x00002  |Occupied |        |
|            |  0x00003  |         |        |
|            |  0x00004  |Occupied |        |
|            |  0x00005  |         |        |
|            |  0x00006  |Occupied |        |
|            |  0x00007  |         |        |
|            |  0x00008  |Occupied |        |
|            |  0x00009  |         |        |
|    temp    |  0x00010  | 0x00001 |        |


#### Doubly Linked List


## Stack


## Queue


## Trees

#### Binary-Tree

#### D-Ary-Tree

#### Red-Black-Tree

#### Further Variants


## Hash Tables

#### Chaining

#### Open Addressing
