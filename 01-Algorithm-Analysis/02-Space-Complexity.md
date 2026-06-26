# 🧠 Space Complexity

> *"An algorithm must be seen to be believed."* — Donald Knuth

---

## Table of Contents

1. [Introduction](#introduction)
2. [How Programs Really Run](#how-programs-really-run)
3. [What is RAM?](#what-is-ram)
4. [Memory Layout](#memory-layout)
5. [Stack Memory](#stack-memory)
6. [Heap Memory](#heap-memory)
7. [Primitive Variables vs Objects](#primitive-variables-vs-objects)
8. [Garbage Collection](#garbage-collection)
9. [What is Space Complexity?](#what-is-space-complexity)
10. [Types of Space Complexity](#types-of-space-complexity)
11. [Memory Simulation](#memory-simulation)
12. [Common Mistakes](#common-mistakes)
13. [Interview Thinking](#interview-thinking)
14. [Cheat Sheet](#cheat-sheet)
15. [Practice Problems](#practice-problems)
16. [Final Thought](#final-thought)

---

## Introduction

Imagine you are moving into a new apartment. You care about two things: how quickly you can unpack your boxes, and whether everything actually fits inside the rooms. A fast unpacker who arrives with a truck full of furniture and nowhere to put it has not solved the problem — they have created a new one.

Algorithms work the same way.

When we study algorithms, we usually begin with **time complexity**: how many steps does this algorithm need? That is the unpacking speed. But there is a second question that is equally important and far too often ignored until something goes catastrophically wrong in production: **how much memory does this algorithm consume?**

Memory is not infinite. A laptop running a Java application might have 8 or 16 gigabytes of RAM, but that memory is shared with the operating system, the browser, the editor, and dozens of background processes. The memory your program is actually allowed to use is a fraction of what the machine physically contains. When your algorithm exceeds that budget, the operating system does not politely ask it to stop — it terminates the program abruptly, or starts evicting memory to disk in a process so slow it can make a fast algorithm feel like it is running underwater.

Real-world disasters have happened because engineers underestimated memory. Servers have crashed under load not because the CPU was saturated, but because each request silently allocated megabytes of objects that were never released quickly enough. Mobile apps have been rejected from app stores because they consumed too much RAM on low-end devices. Video games have stuttered not from slow code but from the garbage collector pausing execution to clean up the heap.

Speed and space are two dimensions of the same problem. A great engineer thinks about both.

There is also a practical, career-level reason to care about this. Technical interviews at top software companies routinely ask for the space complexity of your solution. Saying "O(n) time" without mentioning space signals to the interviewer that you have an incomplete mental model. The strongest candidates can articulate both dimensions fluently, explain where the memory is actually being consumed, and often propose a trade-off between the two.

This chapter will take you from the physical reality of RAM all the way to analyzing algorithms the way a senior engineer or a technical interviewer would. We will start at the foundation — how a Java program actually runs — and build every concept on top of that foundation until space complexity feels not like a formula to memorize, but like a natural way of reading code.

---

## How Programs Really Run

Before we can talk about memory, we need to understand the journey a program takes from the text you write to the instructions a CPU executes. Most beginners think of this as a black box. We are going to open it.

When you write Java code in a file like `Main.java`, you have written something that a human can read but a computer cannot execute directly. The CPU speaks in machine code — raw binary instructions specific to its architecture. Java code is nowhere near that level. There is a whole chain of transformation that happens every time you hit "run."

```
Your Java Source Code   (Main.java)
          │
          ▼
      Java Compiler      (javac)
          │
          ▼
        Bytecode          (Main.class)
          │
          ▼
  Java Virtual Machine   (JVM)
          │
          ▼
    Operating System
          │
          ▼
          RAM
          │
          ▼
          CPU
```

Let us walk through each step.

**Java Source Code** is what you write. It is human-readable text that expresses your intent — loops, variables, method calls, conditions.

**The Java Compiler (`javac`)** translates your source code into **bytecode**, stored in `.class` files. Bytecode is not machine code. It is a set of instructions designed for an imaginary, platform-neutral machine — the Java Virtual Machine.

**The JVM** is a program that reads bytecode and translates it into actual machine instructions for the real CPU it is running on. This is why Java is "write once, run anywhere": the same `.class` file runs on Windows, macOS, and Linux because each platform has its own JVM that handles the final translation.

**The Operating System** acts as a gatekeeper. The JVM does not directly control RAM. Instead, it asks the operating system — Windows, macOS, Linux — for memory. The OS grants regions of memory to the JVM process, and the JVM manages those regions internally.

**RAM (Random Access Memory)** is where your program actually lives while it runs. Every variable, every object, every string, every method call occupies a piece of RAM. We will spend most of this chapter here.

**The CPU** reads instructions from RAM, executes them, and writes results back to RAM. It is blindingly fast, but it can only work on what is already loaded into memory.

This pipeline explains something important: memory consumption is not just about the data your algorithm processes. It includes the overhead of method calls, the instructions themselves, the JVM's internal bookkeeping, and much more. When we analyze space complexity, we focus specifically on the memory your algorithm's own logic consumes — but understanding the full picture helps you reason about the system holistically.

---

## What is RAM?

Let us build an intuition for RAM before we discuss how programs use it.

Think of RAM as a massive row of numbered mailboxes — millions or billions of them, depending on how much memory your computer has. Each mailbox holds exactly one byte (eight bits). Every mailbox has a unique address, starting from 0 and counting up.

```
Address:  0    1    2    3    4    5    6    7    ...
        ┌────┬────┬────┬────┬────┬────┬────┬────┬─────┐
        │    │    │    │    │    │    │    │    │ ... │
        └────┴────┴────┴────┴────┴────┴────┴────┴─────┘
```

When your program needs to store an integer, it asks the operating system for four consecutive mailboxes (since Java's `int` is 32 bits = 4 bytes). The OS responds with an address, and from that moment on, those four mailboxes belong to your integer for as long as the variable exists.

RAM has one superpower that makes it different from storage (like a hard drive): any mailbox can be accessed in the same amount of time, regardless of its address. You can jump directly to address 4,000,000 as fast as you can read address 7. This is what "random access" means — the access time is random in the sense that it does not depend on where in memory you look.

This is relevant to us because algorithms that access memory in predictable, sequential patterns tend to be faster in practice (due to CPU cache behavior), while algorithms that scatter their memory accesses pay a hidden performance cost that Big-O notation does not capture.

Programs do not request individual bytes one at a time. The JVM requests large regions of memory from the OS upfront, and then manages those regions internally. These regions are divided into distinct areas — some for your method calls, some for your objects — and understanding that division is the key to understanding space complexity.

---

## Memory Layout

When the JVM runs your program, it divides its allocated memory into several distinct regions. Two of them are what every developer must understand deeply: the **Stack** and the **Heap**.

```
  JVM Memory Layout
  ─────────────────────────────────────────────────────
  │                                                   │
  │   Stack                        Heap               │
  │  ┌──────────────┐         ┌──────────────────┐    │
  │  │ Frame 3      │         │  Object C        │    │
  │  │  local vars  │         │  Object A        │    │
  │  ├──────────────┤         │  Object B        │    │
  │  │ Frame 2      │         │  String "hello"  │    │
  │  │  local vars  │         │  int[] array     │    │
  │  ├──────────────┤         │                  │    │
  │  │ Frame 1      │         │  (grows freely)  │    │
  │  │  local vars  │         └──────────────────┘    │
  │  └──────────────┘                                 │
  │  (grows downward)                                 │
  │                                                   │
  │   (Other regions: Method Area, PC Registers...)   │
  └───────────────────────────────────────────────────┘
```

The **Stack** is the region where method calls and local variables live. It is organized, compact, and managed automatically. When you call a method, memory is pushed onto the stack. When the method returns, that memory is instantly reclaimed.

The **Heap** is the region where objects, arrays, and strings live. It is large, flexible, and managed by the garbage collector. Objects on the heap persist until nothing in the program refers to them anymore.

We will explore each region in detail now.

---

## Stack Memory

Picture a stack of trays in a cafeteria. You can only add a new tray to the top, and you can only remove the top tray. That is the exact structure of stack memory — **Last In, First Out (LIFO)**.

Every time your program calls a method, the JVM creates a **stack frame** for that method and pushes it onto the top of the stack. The frame contains:

- All **local variables** declared inside the method
- The **parameters** passed to the method
- The **return address** — where execution should resume when the method finishes
- Intermediate computation results

When the method returns, its frame is popped off the stack and all that memory is instantly released. No cleanup code runs. No garbage collector intervenes. The stack pointer simply moves back to where it was before.

This is why the stack is so fast: allocating and deallocating memory on the stack is a single operation — move a pointer.

Let us trace through a simple example:

```java
public class Example {
    public static void main(String[] args) {
        int result = add(3, 5);
        System.out.println(result);
    }

    public static int add(int a, int b) {
        int sum = a + b;
        return sum;
    }
}
```

**Step 1: `main` is called**

```
Stack
┌──────────────────────────┐  ← Top of stack
│  Frame: main             │
│  ┌────────────────────┐  │
│  │ args = (reference) │  │
│  │ result = ?         │  │
│  └────────────────────┘  │
└──────────────────────────┘
```

**Step 2: `add(3, 5)` is called**

```
Stack
┌──────────────────────────┐  ← Top of stack
│  Frame: add              │
│  ┌────────────────────┐  │
│  │ a = 3              │  │
│  │ b = 5              │  │
│  │ sum = ?            │  │
│  └────────────────────┘  │
├──────────────────────────┤
│  Frame: main             │
│  ┌────────────────────┐  │
│  │ args = (reference) │  │
│  │ result = ?         │  │
│  └────────────────────┘  │
└──────────────────────────┘
```

**Step 3: `sum = a + b` executes, `add` returns**

```
Stack
┌──────────────────────────┐  ← Frame: add is GONE
│  Frame: main             │
│  ┌────────────────────┐  │
│  │ args = (reference) │  │
│  │ result = 8         │  │  ← return value captured
│  └────────────────────┘  │
└──────────────────────────┘
```

The memory that `add`'s frame occupied is instantly reclaimed the moment `add` returns. The stack has a fixed maximum size (you can configure it with JVM flags), and if you exceed it — for example, by calling methods recursively without a base case — you get the famously named `StackOverflowError`.

This is also why **recursion has space implications that iteration does not**: each recursive call adds a new frame to the stack. A recursion that is 10,000 levels deep has 10,000 frames on the stack simultaneously.

---

## Heap Memory

The Heap is the opposite of the Stack in almost every way. Where the Stack is rigid and automatic, the Heap is flexible and manually managed (with the garbage collector doing the cleanup work on your behalf in Java).

Every time you use the `new` keyword in Java, memory is allocated on the Heap.

```java
int[] numbers = new int[5];
String greeting = new String("hello");
ArrayList<Integer> list = new ArrayList<>();
```

In each of these cases:

- The **variable** (`numbers`, `greeting`, `list`) lives on the Stack
- The **actual data** (the array, the string characters, the list internals) lives on the Heap

The variable on the Stack does not hold the data itself. It holds a **reference** — an address that points to where the data lives in the Heap. This distinction is fundamental.

```
Stack                        Heap
┌─────────────────┐         ┌──────────────────────────┐
│ Frame: main     │         │                          │
│ ┌─────────────┐ │         │  Address 1004:           │
│ │ numbers ────┼─┼────────►│  [0, 0, 0, 0, 0]        │
│ │  (ref:1004) │ │         │                          │
│ │             │ │         │  Address 2048:           │
│ │ greeting ───┼─┼────────►│  "hello"                 │
│ │  (ref:2048) │ │         │                          │
│ └─────────────┘ │         └──────────────────────────┘
└─────────────────┘
```

The arrow represents the reference. When you write `numbers[0] = 42`, Java follows the reference to address 1004 and writes 42 into the first slot of the array in the Heap.

This indirection has a profound implication for space complexity. When you pass an array to a method, you are not copying the entire array — you are copying the reference. The reference itself is tiny (typically 4 or 8 bytes). The array still lives in one place in the Heap, and both the caller and the callee can see it through their references.

```java
public static void fill(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        arr[i] = i * 2;
    }
}
```

Calling `fill(numbers)` does not double the memory usage of the array. Only a small reference is added to the Stack. This is why large arrays and objects can be passed to methods efficiently — but it is also why methods can unexpectedly modify data you did not intend them to change.

The Heap is larger than the Stack and grows dynamically. Objects can be allocated and can reference other objects, forming complex graphs of interconnected data. This flexibility comes with a cost: the Heap requires a garbage collector to reclaim memory from objects that are no longer needed.

---

## Primitive Variables vs Objects

Java has two categories of data, and they have entirely different relationships with memory.

**Primitive types** store their value directly. They are:

| Type      | Size    | Example value |
|-----------|---------|---------------|
| `byte`    | 1 byte  | `127`         |
| `short`   | 2 bytes | `32000`       |
| `int`     | 4 bytes | `42`          |
| `long`    | 8 bytes | `9999999999L` |
| `float`   | 4 bytes | `3.14f`       |
| `double`  | 8 bytes | `3.14159`     |
| `char`    | 2 bytes | `'A'`         |
| `boolean` | 1 byte  | `true`        |

When you declare `int x = 42` inside a method, the value `42` is stored directly inside the Stack frame. There is no Heap involvement. The variable and its value are one and the same thing.

```
Stack Frame
┌──────────────┐
│ x = 42       │  ← value stored directly here
│ y = true     │  ← value stored directly here
│ z = 3.14     │  ← value stored directly here
└──────────────┘
```

**Reference types** (everything else) behave differently. When you declare an object, the Stack frame holds only a reference — a memory address pointing to the actual object data in the Heap.

```java
int x = 42;                     // primitive → value on Stack
int[] arr = new int[]{1,2,3};   // reference → Stack holds address, data on Heap
String name = "Alice";          // reference → Stack holds address, data on Heap
StringBuilder sb = new StringBuilder();  // reference → Stack holds address, data on Heap
```

```
Stack Frame                 Heap
┌────────────────┐         ┌─────────────────────┐
│ x    =  42     │         │                     │
│ arr  → ────────┼────────►│  [1, 2, 3]          │
│ name → ────────┼────────►│  "Alice"            │
│ sb   → ────────┼────────►│  StringBuilder obj  │
└────────────────┘         └─────────────────────┘
```

This distinction matters deeply for space complexity because:

1. A method with only primitive local variables uses only Stack memory proportional to the number of those variables — no Heap allocation.
2. A method that creates objects, arrays, or strings allocates memory on the Heap, and that memory may outlive the method call itself.
3. When you pass a primitive to a method, a copy is made. When you pass a reference type, only the reference is copied — the Heap object is shared.

Understanding this division makes it possible to look at a piece of code and immediately identify where memory is being consumed and whether that memory is on the Stack (fast, automatic, limited) or the Heap (larger, flexible, requires collection).

---

## Garbage Collection

The Heap can grow large, but it is not infinite. Objects that are no longer needed must eventually be removed so their memory can be reused. In languages like C and C++, this is the programmer's responsibility — you allocate memory, and you free it manually. Forgetting to free memory causes **memory leaks**, one of the most destructive bugs in systems programming.

Java removes this burden from the programmer by providing a **Garbage Collector (GC)** — a background process that automatically identifies and removes objects that your program can no longer use.

The GC's core question is: **can this object be reached from anywhere in the running program?**

An object is **reachable** if there is a chain of references from some active part of your program that leads to it. An object is **unreachable** — and therefore eligible for collection — when no such chain exists.

```
Before:                          After reassignment:

Stack                            Stack
┌───────────────┐               ┌───────────────┐
│ list → ───────┼──►[1,2,3]    │ list → ───────┼──► [4,5,6]  (new object)
└───────────────┘               └───────────────┘
                                                  
                                [1,2,3] ← UNREACHABLE
                                         (eligible for GC)
```

When you write:

```java
int[] list = new int[]{1, 2, 3};
list = new int[]{4, 5, 6};      // list now points to a new array
```

The original array `[1, 2, 3]` is still sitting in the Heap, but nothing points to it anymore. The GC will eventually discover this and reclaim that memory.

The garbage collector runs periodically, not instantaneously. This means that between when an object becomes unreachable and when the GC reclaims its memory, that memory is still occupied. In space complexity analysis, we typically assume the GC runs when needed, but in real-world performance work, GC pauses and GC pressure are important considerations.

What this means for us: **creating many short-lived objects in a tight loop is not "free" from a memory perspective**, even if each individual object is small. They accumulate in the Heap faster than the GC can collect them. Good algorithm design considers object creation, not just variable declaration.

---

## What is Space Complexity?

We have built the foundation. Now we can define the concept properly.

**Space complexity** is a measure of how much memory an algorithm uses as a function of its input size. It answers the question: as the input grows, how does my algorithm's memory consumption grow?

But there is an important subtlety here, and most explanations gloss over it: **should we count the memory used by the input itself?**

Consider a function that takes an array of `n` integers and returns its maximum value. The array occupies `n` slots of memory. But that memory was going to exist regardless of which algorithm you chose — you were given that data. The question we really care about is: **how much extra memory does your algorithm need, above and beyond what it was given?**

This extra memory is called **Auxiliary Space**.

```
Total Space = Input Space + Auxiliary Space
Space Complexity (as typically used) = Auxiliary Space
```

When an interviewer asks "what is the space complexity of your solution?", they almost always mean: how much additional memory does your algorithm allocate? The input is assumed to already exist.

There are contexts where total space matters — for instance, when you are deciding whether you can even afford to load the input into memory. But for algorithm analysis, **we measure auxiliary space**.

This makes intuitive sense. A sorting algorithm that rearranges elements within the original array without creating new arrays is fundamentally different from one that creates a copy of the array to work on. The first uses O(1) auxiliary space; the second uses O(n) auxiliary space. Even though both receive the same input, one is far more memory-efficient.

Space complexity, like time complexity, is expressed using **Big-O notation**, which describes the asymptotic behavior — how the space requirement grows as the input size `n` approaches infinity, ignoring constant factors and lower-order terms.

---

## Types of Space Complexity

### O(1) — Constant Space

An algorithm uses **O(1) auxiliary space** when the amount of extra memory it uses does not depend on the size of the input at all. No matter how large the array you pass in, the algorithm uses the same fixed amount of additional memory.

**Intuition:** Imagine reading through a thousand-page book and keeping only one sticky note to track your place. The number of sticky notes does not grow with the size of the book.

**Java Example:**

```java
public static int findMax(int[] arr) {
    int max = arr[0];           // One extra integer on the Stack
    for (int i = 1; i < arr.length; i++) {
        if (arr[i] > max) {
            max = arr[i];       // Still just one extra integer
        }
    }
    return max;
}
```

This method declares exactly two local variables (`max` and `i`) regardless of whether `arr` has 10 elements or 10 million. The extra memory is fixed.

**Memory growth:**

```
Input size:   10        1,000      1,000,000
Extra memory: 8 bytes   8 bytes    8 bytes
              (max + i) (max + i)  (max + i)
```

**Visualization:**

```
n = 10:        [extra: ■]
n = 1000:      [extra: ■]
n = 1,000,000: [extra: ■]
                         ← always the same, regardless of input
```

---

### O(log n) — Logarithmic Space

An algorithm uses **O(log n) auxiliary space** when the extra memory it uses grows proportionally to the logarithm of the input size. This most commonly appears in recursive algorithms that divide the problem in half at each step.

**Intuition:** Binary search on a sorted array of 1,000,000 elements needs roughly 20 steps (since 2²⁰ ≈ 1,000,000). If implemented recursively, it creates roughly 20 stack frames simultaneously. Doubling the input to 2,000,000 requires only one more step — 21 frames. The memory grows incredibly slowly.

**Java Example:**

```java
public static int binarySearch(int[] arr, int target, int low, int high) {
    if (low > high) return -1;

    int mid = low + (high - low) / 2;    // One extra int per frame

    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearch(arr, target, mid + 1, high);
    else return binarySearch(arr, target, low, mid - 1);
}
```

Each recursive call adds one Stack frame with a few integer variables. The depth of recursion is O(log n).

**Memory growth:**

```
n = 8:         3 frames deep (2³ = 8)
n = 16:        4 frames deep
n = 1,024:     10 frames deep
n = 1,048,576: 20 frames deep
```

**Visualization:**

```
Stack at deepest point (n = 16):
┌──────────────────────┐
│ binarySearch [0,15]  │
├──────────────────────┤
│ binarySearch [8,15]  │
├──────────────────────┤
│ binarySearch [8,11]  │
├──────────────────────┤
│ binarySearch [8,9]   │  ← 4 frames for 16 elements
└──────────────────────┘
```

---

### O(n) — Linear Space

An algorithm uses **O(n) auxiliary space** when the extra memory it uses grows in direct proportion to the input size. If you double the input, you roughly double the extra memory.

**Intuition:** Copying a list of names onto a new sheet of paper. The more names there are, the more paper you use.

**Java Example:**

```java
public static int[] copyArray(int[] arr) {
    int[] copy = new int[arr.length];    // n extra integers in Heap
    for (int i = 0; i < arr.length; i++) {
        copy[i] = arr[i];
    }
    return copy;
}
```

For an input of size `n`, this creates a new array of size `n` in the Heap. The auxiliary space is directly proportional to `n`.

Another classic example: recursive algorithms where each level of recursion stores meaningful data.

```java
public static int[] range(int n) {
    if (n == 0) return new int[]{};
    int[] result = new int[n];
    for (int i = 0; i < n; i++) result[i] = i;
    return result;
}
```

**Memory growth:**

```
n = 10:    10 extra integers  = 40 bytes
n = 100:   100 extra integers = 400 bytes
n = 1000:  1000 extra integers = 4,000 bytes
```

**Visualization:**

```
n = 4:  [■][■][■][■]
n = 8:  [■][■][■][■][■][■][■][■]
n = 16: [■][■][■][■][■][■][■][■][■][■][■][■][■][■][■][■]
         ↑ memory grows linearly with input size
```

---

### O(n²) — Quadratic Space

An algorithm uses **O(n²) auxiliary space** when the extra memory grows proportionally to the square of the input size. This most commonly appears when an algorithm needs to store a two-dimensional grid or matrix whose dimensions both scale with `n`.

**Intuition:** If you are creating a seating chart where every one of `n` guests can interact with every other guest, you need `n × n` rows — a table that grows quadratically.

**Java Example:**

```java
public static int[][] buildAdjacencyMatrix(int n) {
    int[][] matrix = new int[n][n];    // n * n integers in Heap
    // ... fill the matrix
    return matrix;
}
```

For `n = 100`, this creates 10,000 integers. For `n = 1,000`, this creates 1,000,000 integers. The memory explodes.

**Memory growth:**

```
n = 10:   10 × 10   = 100   integers
n = 100:  100 × 100 = 10,000 integers
n = 1000: 1000 × 1000 = 1,000,000 integers
```

**Visualization:**

```
n = 3:      n = 4:        n = 5:
■ ■ ■       ■ ■ ■ ■       ■ ■ ■ ■ ■
■ ■ ■       ■ ■ ■ ■       ■ ■ ■ ■ ■
■ ■ ■       ■ ■ ■ ■       ■ ■ ■ ■ ■
(9 cells)   ■ ■ ■ ■       ■ ■ ■ ■ ■
            (16 cells)    ■ ■ ■ ■ ■
                          (25 cells)
```

Each step adds not just a row and a column — it adds an entirely new row and column of the new size. The growth is explosive.

---

## Memory Simulation

This section is where everything comes together. We will trace through algorithms line by line, drawing the Stack and Heap after each significant step, exactly like a debugger would show you.

---

### Simulation 1: Reversing an Array (O(n) Space)

```java
public static int[] reverse(int[] arr) {
    int n = arr.length;
    int[] result = new int[n];
    for (int i = 0; i < n; i++) {
        result[n - 1 - i] = arr[i];
    }
    return result;
}
```

We call `reverse(new int[]{1, 2, 3})`.

---

**After `int n = arr.length;`**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverse          │    │                      │
│ ┌─────────────────────┐ │    │ [0x100]: {1, 2, 3}   │ ← input (existed before call)
│ │ arr  → 0x100        │ │    │                      │
│ │ n    = 3            │ │    │                      │
│ │ result = ?          │ │    │                      │
│ │ i    = ?            │ │    │                      │
│ └─────────────────────┘ │    └──────────────────────┘
└─────────────────────────┘
```

---

**After `int[] result = new int[n];`**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverse          │    │ [0x100]: {1, 2, 3}   │
│ ┌─────────────────────┐ │    │                      │
│ │ arr    → 0x100      │ │    │ [0x200]: {0, 0, 0}   │ ← NEW allocation (auxiliary)
│ │ n      = 3          │ │    │                      │
│ │ result → 0x200      │ │    │                      │
│ │ i      = ?          │ │    └──────────────────────┘
│ └─────────────────────┘ │
└─────────────────────────┘
```

Here is where auxiliary space appears: `result` is a new array in the Heap. This is the memory our algorithm adds beyond the input.

---

**After loop iteration i=0: `result[2] = arr[0]`**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverse          │    │ [0x100]: {1, 2, 3}   │
│ ┌─────────────────────┐ │    │                      │
│ │ arr    → 0x100      │ │    │ [0x200]: {0, 0, 1}   │ ← index 2 set to 1
│ │ n      = 3          │ │    │                      │
│ │ result → 0x200      │ │    └──────────────────────┘
│ │ i      = 0          │ │
│ └─────────────────────┘ │
└─────────────────────────┘
```

---

**After loop iteration i=1: `result[1] = arr[1]`**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverse          │    │ [0x100]: {1, 2, 3}   │
│ ┌─────────────────────┐ │    │                      │
│ │ arr    → 0x100      │ │    │ [0x200]: {0, 2, 1}   │ ← index 1 set to 2
│ │ n      = 3          │ │    │                      │
│ │ result → 0x200      │ │    └──────────────────────┘
│ │ i      = 1          │ │
│ └─────────────────────┘ │
└─────────────────────────┘
```

---

**After loop iteration i=2: `result[0] = arr[2]`**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverse          │    │ [0x100]: {1, 2, 3}   │
│ ┌─────────────────────┐ │    │                      │
│ │ arr    → 0x100      │ │    │ [0x200]: {3, 2, 1}   │ ← complete!
│ │ n      = 3          │ │    │                      │
│ │ result → 0x200      │ │    └──────────────────────┘
│ │ i      = 2          │ │
│ └─────────────────────┘ │
└─────────────────────────┘
```

---

**After `return result;` — frame is popped**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: caller           │    │ [0x100]: {1, 2, 3}   │
│ ┌─────────────────────┐ │    │                      │
│ │ ... → 0x200         │ │    │ [0x200]: {3, 2, 1}   │ ← returned to caller
│ └─────────────────────┘ │    │                      │
└─────────────────────────┘    └──────────────────────┘
```

The `reverse` frame is gone. The result array lives on because the caller holds a reference to it. **Auxiliary space used: O(n)** — exactly the size of `result`.

---

### Simulation 2: Factorial with Recursion (O(n) Stack Space)

```java
public static int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

We call `factorial(4)`.

---

**Calling `factorial(4)` → calls `factorial(3)` → calls `factorial(2)` → calls `factorial(1)`**

```
Stack (at deepest point)
┌──────────────────────────────┐  ← Top
│ Frame: factorial(1)          │
│  n = 1                       │
│  [will return 1]             │
├──────────────────────────────┤
│ Frame: factorial(2)          │
│  n = 2                       │
│  [waiting for factorial(1)]  │
├──────────────────────────────┤
│ Frame: factorial(3)          │
│  n = 3                       │
│  [waiting for factorial(2)]  │
├──────────────────────────────┤
│ Frame: factorial(4)          │
│  n = 4                       │
│  [waiting for factorial(3)]  │
├──────────────────────────────┤
│ Frame: main                  │
└──────────────────────────────┘
```

At the deepest point, there are `n` frames on the Stack simultaneously. Each frame holds one integer (`n`). The stack depth grows linearly with the input — this is **O(n) auxiliary space** consumed entirely on the Stack, with no Heap involvement.

**Unwinding:**

```
factorial(1) returns 1
  → factorial(2) computes 2 * 1 = 2, returns 2
    → factorial(3) computes 3 * 2 = 6, returns 6
      → factorial(4) computes 4 * 6 = 24, returns 24
```

After each return, the top frame is popped. The Stack shrinks back to just `main`.

---

### Simulation 3: Constant Space In-Place Swap (O(1) Space)

```java
public static void reverseInPlace(int[] arr) {
    int left = 0;
    int right = arr.length - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}
```

We call `reverseInPlace(new int[]{1, 2, 3, 4})`.

**After method entry:**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverseInPlace   │    │ [0x100]: {1, 2, 3, 4}│
│ ┌─────────────────────┐ │    └──────────────────────┘
│ │ arr   → 0x100       │ │
│ │ left  = 0           │ │  ← only these three
│ │ right = 3           │ │     extra variables exist
│ │ temp  = ?           │ │     regardless of arr size
│ └─────────────────────┘ │
└─────────────────────────┘
```

**After first swap (left=0, right=3):**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverseInPlace   │    │ [0x100]: {4, 2, 3, 1}│ ← modified in place
│ ┌─────────────────────┐ │    └──────────────────────┘
│ │ arr   → 0x100       │ │
│ │ left  = 1           │ │
│ │ right = 2           │ │
│ │ temp  = 1           │ │
│ └─────────────────────┘ │
└─────────────────────────┘
```

**After second swap (left=1, right=2):**

```
Stack                           Heap
┌─────────────────────────┐    ┌──────────────────────┐
│ Frame: reverseInPlace   │    │ [0x100]: {4, 3, 2, 1}│ ← fully reversed
│ ┌─────────────────────┐ │    └──────────────────────┘
│ │ arr   → 0x100       │ │
│ │ left  = 2           │ │
│ │ right = 1           │ │
│ │ temp  = 2           │ │
│ └─────────────────────┘ │
└─────────────────────────┘
```

No new Heap memory was created at any point. The three variables `left`, `right`, and `temp` on the Stack are constant regardless of the array size. **Auxiliary space: O(1).**

---

## Common Mistakes

Learning space complexity is as much about unlearning misconceptions as it is about acquiring knowledge. Here are the mistakes that appear most frequently.

---

**Mistake 1: Counting the Input as Auxiliary Space**

A very common error is to look at a function that takes an `int[]` of size `n` and immediately say "this uses O(n) space." But the array was already allocated before the function was called. If the function does not create any additional data structures, its auxiliary space may well be O(1).

The question to ask is: *what did this algorithm create?* Not: *what was it given?*

---

**Mistake 2: Ignoring Recursion**

Iterative and recursive solutions can have different space complexities even when they compute the same result. An iterative loop that sums an array uses O(1) auxiliary space. A naive recursive sum uses O(n) space because it builds a call stack n frames deep before it can begin returning.

Whenever you see recursion, immediately ask: *how deep can the call stack get, and what does each frame contain?*

---

**Mistake 3: Thinking Every Variable Adds Complexity**

Variables that are declared inside a loop do not create more space with each iteration. Each time the loop body runs, the same Stack slot is reused.

```java
for (int i = 0; i < n; i++) {
    int temp = arr[i] * 2;    // same Stack slot reused each iteration
    // ...
}
```

This loop uses O(1) space for `temp`, not O(n), even though the loop runs `n` times. The variable `temp` does not accumulate — it is overwritten every iteration.

The space is O(n) only if you are *storing* results in a growing data structure:

```java
List<Integer> results = new ArrayList<>();
for (int i = 0; i < n; i++) {
    results.add(arr[i] * 2);    // list GROWS with each iteration → O(n)
}
```

---

**Mistake 4: Confusing Stack and Heap**

Beginners sometimes believe that Stack space is "free" and only Heap allocations count for space complexity. This is false. Stack memory is also finite, and deep recursion *will* overflow it. A recursive algorithm with O(n) call depth has O(n) auxiliary space whether or not it touches the Heap.

Conversely, some beginners panic about every `new` keyword. A single `new int[1]` regardless of `n` is still O(1) space.

---

**Mistake 5: Not Considering String Operations**

In Java, strings are immutable objects on the Heap. String concatenation inside a loop creates a new String object with every iteration:

```java
String result = "";
for (int i = 0; i < n; i++) {
    result = result + words[i];    // creates a NEW String object each time → O(n²) total!
}
```

This is both a time and space problem. Each concatenation creates a string one character longer than the last, and the old string is left for the garbage collector. Use `StringBuilder` instead.

---

## Interview Thinking

Technical interviewers do not just want to hear the correct Big-O answer — they want to see your thinking process. Here is how senior engineers approach space complexity during interviews.

---

**Step 1: Identify the algorithm's auxiliary data structures**

Scan the code for:
- Array or list declarations: `new int[n]`, `new ArrayList<>()`
- Map or set declarations: `new HashMap<>()`, `new HashSet<>()`
- Queue or stack declarations: `new LinkedList<>()`, `new Stack<>()`
- String builders: `new StringBuilder()`

Each of these is a potential O(n) or worse contributor.

---

**Step 2: Check for recursion**

If the method calls itself, ask:
- What is the maximum depth of recursion?
- What does each stack frame contain (just a few integers, or a reference to a data structure)?

Recursion depth × frame size = stack space consumed.

---

**Step 3: Separate input from auxiliary**

Always distinguish: "this variable holds the input" versus "this variable was created by my algorithm."

A classic interview setup is to ask for a solution that is "in-place" — meaning O(1) auxiliary space. If you recognize that the interviewer is asking for in-place, you immediately know you cannot create new arrays sized proportionally to `n`.

---

**Step 4: Consider the return value**

Some algorithms build their answer into a new data structure and return it. The returned structure counts as auxiliary space, even if you are returning it to the caller. If a method returns a new array of size `n`, its auxiliary space is O(n).

---

**Step 5: State your answer with confidence and reasoning**

Do not just blurt out "O(n)." Say:

> *"The auxiliary space is O(n) because I create a new array of size n to store intermediate results. The input array itself does not count toward the auxiliary space. The stack frames from the loop are constant, so they do not affect the asymptotic complexity."*

This tells the interviewer you understand *why*, not just *what*.

---

**Quick identification patterns:**

| What you see in code                            | Space implication                 |
|-------------------------------------------------|-----------------------------------|
| A few `int` or `boolean` variables              | O(1) contribution                 |
| A new array/list of size `n`                    | O(n) contribution                 |
| A 2D array of size `n × n`                      | O(n²) contribution                |
| Recursion `n` levels deep                       | O(n) Stack contribution           |
| Recursion that halves the problem               | O(log n) Stack contribution       |
| String concatenation in a loop                  | Hidden O(n²) space                |
| StringBuilder in a loop (appending n chars)     | O(n) Heap contribution            |

---

## Cheat Sheet

| Complexity | Name        | What causes it                                 | Example                           |
|------------|-------------|------------------------------------------------|-----------------------------------|
| O(1)       | Constant    | Fixed number of variables, no new structures   | Finding max in array (iterative)  |
| O(log n)   | Logarithmic | Recursive halving, log-depth call stack        | Binary search (recursive)         |
| O(n)       | Linear      | New array/list of size n; n-deep recursion     | Array copy; recursive factorial   |
| O(n log n) | Linearithmic| Merge sort's merge step with recursion depth   | Merge Sort                        |
| O(n²)      | Quadratic   | 2D array of size n × n                        | Adjacency matrix; nested n-lists  |

| Concept               | Key point                                                     |
|-----------------------|---------------------------------------------------------------|
| Auxiliary Space       | Extra memory beyond the input                                 |
| Stack Space           | Stack frames from method calls (especially recursion)         |
| Heap Space            | Objects, arrays, strings created with `new`                   |
| In-place              | O(1) auxiliary space — modifies input without new structures  |
| Reference vs. Value   | Primitives live on Stack; Objects live on Heap                |
| GC Eligibility        | Objects with no references become eligible for collection     |
| Recursion depth       | Every recursive call adds one Stack frame                     |

---

## Practice Problems

Work through these problems in order. They are designed to build your intuition progressively. Do not look for solutions until you have made a genuine attempt.

---

**Level 1 — Beginner**

**Problem 1.**
What is the auxiliary space complexity of the following method? Justify your answer by identifying every piece of extra memory it uses.

```java
public static boolean isPalindrome(String s) {
    int left = 0;
    int right = s.length() - 1;
    while (left < right) {
        if (s.charAt(left) != s.charAt(right)) return false;
        left++;
        right--;
    }
    return true;
}
```

**Problem 2.**
A method takes an array and returns a new array containing only the even numbers. If the input has `n` elements, what is the worst-case auxiliary space complexity? What is the best case? Under what conditions does each occur?

**Problem 3.**
Two engineers are debating how to sum all elements in an array. Engineer A uses a `for` loop. Engineer B uses recursion. Both produce the correct answer. Compare the space complexity of their two approaches and explain why they differ.

---

**Level 2 — Intermediate**

**Problem 4.**
Consider a recursive method that computes the Fibonacci number at position `n` by making two recursive calls: `fib(n-1)` and `fib(n-2)`. Analyze its space complexity. Hint: draw the recursion tree and think about the maximum number of simultaneous active stack frames.

**Problem 5.**
You are given the following method. Analyze its space complexity carefully, paying attention to the `StringBuilder`.

```java
public static String joinWithCommas(String[] words) {
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < words.length; i++) {
        sb.append(words[i]);
        if (i < words.length - 1) sb.append(", ");
    }
    return sb.toString();
}
```

**Problem 6.**
A method takes a 2D matrix of size `m × n` and creates a transposed copy (rows become columns). What is its auxiliary space complexity in terms of `m` and `n`? Is it possible to transpose a square matrix in O(1) auxiliary space?

---

**Level 3 — Advanced**

**Problem 7.**
Merge Sort creates auxiliary arrays during the merge step. Analyze the total auxiliary space used by Merge Sort when sorting an array of `n` elements. Consider the recursion depth and the arrays created at each level. What is the overall auxiliary space complexity?

**Problem 8.**
Two solutions exist for checking if a linked list has a cycle. Solution A uses a `HashSet` to record visited nodes. Solution B uses two pointers (Floyd's algorithm). Compare their auxiliary space complexities, then consider: are there situations where the higher-space solution might be preferable in practice?

**Problem 9.**
Design an algorithm that takes an unsorted array of `n` integers and returns all pairs that sum to a target value `k`. Your first solution can use any auxiliary space. Then, challenge yourself: can you reduce the auxiliary space to O(1)? What trade-off must you accept to achieve this?

**Problem 10 (Open-ended).**
You are building a cache that stores the last `k` results of an expensive computation. The computation is called with a string key and returns an integer. Design a solution and analyze both its time complexity per lookup and its auxiliary space complexity in terms of `k` and the average key length.

---

## Final Thought

When you first encounter space complexity, it can feel like an afterthought — a secondary concern tacked onto the "real" analysis of time. But the deeper you go into software engineering, the more you realize that memory is often the binding constraint.

Time and space are not independent. They trade off against each other in beautiful and sometimes surprising ways. A hash table makes lookups O(1) in time by using O(n) extra space. A recursive algorithm is often elegantly simple in code but secretly allocates an entire call stack. An in-place algorithm uses no extra space but may be harder to implement and harder to parallelize.

The engineers who build systems that scale — the databases handling billions of rows, the models running on embedded devices, the real-time engines processing millions of events per second — are the ones who have internalized both dimensions. They do not just ask "is this fast enough?" They ask "does this fit?" And they know how to reason about both questions with equal precision.

You have now built the foundation to do exactly that. You understand where memory lives, how Java manages it, and how to measure the memory footprint of an algorithm as rigorously as you measure its speed.

The chapters ahead will introduce new data structures and algorithms. With each one, make it a habit: after you understand what it does and how fast it runs, ask yourself — *where does the memory go?* Draw the Stack. Draw the Heap. Follow the references. Count the frames.

That habit, practiced consistently, is what separates a programmer who writes code from an engineer who truly understands it.
