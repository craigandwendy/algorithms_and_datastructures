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

#### Struct

#### Singly Linked List

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
