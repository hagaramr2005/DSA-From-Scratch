# 🧠 Space Complexity

> *"A fast algorithm is useless if it consumes all available memory."*

---

# Imagine You're Inside Your Computer...

Close your eyes for a second.

Imagine your computer is an enormous city.

Every program you run is a visitor entering that city.

When your Java program starts, it asks the Operating System for memory.

The Operating System replies:

> "How much memory do you need?"

Your program answers:

> "Just enough to do my job."

The amount of memory your algorithm requests while it runs is what we study in **Space Complexity**.

---

# What is Space Complexity?

Space Complexity measures **how much memory an algorithm needs while it is executing** relative to the size of the input.

Notice something important.

It is **NOT** simply the size of your input.

Instead, it describes how much **additional memory** your algorithm requires as the input grows.

---

# Why Should We Care?

Imagine two algorithms.

Algorithm A

* Takes 2 seconds.
* Uses 20 MB of memory.

Algorithm B

* Takes 2 seconds.
* Uses 10 GB of memory.

Which one would you choose?

Most developers would immediately choose Algorithm A.

Memory is a limited resource.

Running out of memory causes applications to become slow, crash, or even terminate unexpectedly.

That's why analyzing memory usage is just as important as analyzing execution time.

---

# What Counts as Memory?

Whenever your program runs, memory is consumed by different things.

```
Program Starts
       │
       ▼
Variables
       │
       ▼
Arrays
       │
       ▼
Objects
       │
       ▼
Function Calls
       │
       ▼
Recursion Stack
```

Every one of these occupies memory.

Some occupy only a few bytes.

Others may occupy millions.

---

# Memory Inside a Java Program

Whenever Java executes a program, memory is divided into two major areas.

```
                 MEMORY
                    │
        ┌───────────┴───────────┐
        │                       │
        ▼                       ▼
     Stack                   Heap
```

These two areas have completely different responsibilities.

Understanding them is the key to understanding Space Complexity.

---

# Stack Memory

The Stack stores temporary information.

Examples include

* Local variables
* Method parameters
* Function calls
* Return addresses

Think of it as a stack of books.

```
Top

main()

↓

sum()

↓

print()

Bottom
```

Whenever a method is called,

a new frame is pushed onto the Stack.

When the method finishes,

that frame disappears automatically.

Stack memory is extremely fast.

---

# Heap Memory

The Heap stores dynamically allocated objects.

Whenever you write

```java
new int[1000]
```

or

```java
new Student()
```

Java allocates memory inside the Heap.

Unlike the Stack,

objects inside the Heap remain alive until they are no longer referenced and the Garbage Collector removes them.

---

# Space Complexity Is NOT the Input Size

Consider this example.

```java
public static int sum(int[] arr)
{
    int total = 0;

    for(int i = 0; i < arr.length; i++)
    {
        total += arr[i];
    }

    return total;
}
```

The input array may contain

```
10 elements

or

10 million elements.
```

Did our algorithm create another array?

No.

Did it allocate another list?

No.

It only created

```
total

i
```

Two integer variables.

Regardless of whether the array has

10

100

1000

or one billion elements,

the algorithm always uses the same amount of additional memory.

Therefore

```
Space Complexity = O(1)
```

---

# Example 2

```java
public static int[] copy(int[] arr)
{
    int[] copy = new int[arr.length];

    for(int i = 0; i < arr.length; i++)
    {
        copy[i] = arr[i];
    }

    return copy;
}
```

Suppose

```
Input

10 elements
```

The algorithm creates

```
Another 10 elements.
```

Now suppose

```
Input

1,000,000 elements.
```

The algorithm creates

```
Another 1,000,000 elements.
```

The extra memory grows together with the input size.

Therefore

```
Space Complexity = O(n)
```

---

# Example 3

```java
int[][] matrix = new int[n][n];
```

The algorithm allocates

```
n rows

×

n columns
```

Total memory

```
n²
```

Therefore

```
Space Complexity = O(n²)
```

---

# Auxiliary Space

One of the most misunderstood concepts.

There is a difference between

```
Input Space
```

and

```
Auxiliary Space
```

Input Space

The memory already occupied by the input itself.

Example

```java
int[] arr
```

The array already exists.

We usually **do not count** it.

Auxiliary Space

Any **extra memory** created by the algorithm while solving the problem.

Examples include

* Temporary arrays
* HashMaps
* Stacks
* Queues
* New Objects
* Recursive Call Stack

When interviewers ask about Space Complexity,

they usually mean

> **Auxiliary Space Complexity.**

---

# Recursion Uses Memory Too

Many beginners think recursion only affects Time Complexity.

That's incorrect.

Every recursive call creates a new Stack Frame.

Example

```java
factorial(5)
```

Memory becomes

```
factorial(5)

↓

factorial(4)

↓

factorial(3)

↓

factorial(2)

↓

factorial(1)
```

Five function calls are stored simultaneously.

Therefore

```
Space Complexity = O(n)
```

because the recursion depth grows with **n**.

---

# In-Place Algorithms

Some algorithms modify the input directly without creating additional data structures.

Example

Bubble Sort.

It only swaps elements inside the original array.

Extra memory

```
temp

i

j
```

Only a few variables.

Regardless of the input size,

memory remains constant.

```
Space Complexity = O(1)
```

These algorithms are called

> **In-Place Algorithms.**

---

# Time vs Space

Sometimes we can save time by using more memory.

Sometimes we save memory by doing more work.

This trade-off is one of the most important ideas in Computer Science.

There is rarely a perfect algorithm.

Engineers constantly balance

* Speed
* Memory
* Simplicity

to achieve the best solution.

---

# Summary

| Complexity | Meaning                                                      |
| ---------- | ------------------------------------------------------------ |
| O(1)       | Constant extra memory                                        |
| O(log n)   | Memory grows logarithmically (e.g., recursive binary search) |
| O(n)       | Memory grows linearly with the input                         |
| O(n²)      | Memory grows quadratically (e.g., matrices)                  |

---

# Final Thought

Time Complexity answers one question:

> **"How much work does my algorithm perform?"**

Space Complexity answers another:

> **"How much memory does my algorithm need while performing that work?"**

A great algorithm is not only fast.

A great algorithm is also memory-efficient.
