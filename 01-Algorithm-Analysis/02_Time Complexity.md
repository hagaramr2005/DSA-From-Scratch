# 02-Time-Complexity.md

## Table of Contents

1. [Introduction](https://www.google.com/search?q=%23introduction)
2. [How Computers Actually Execute Code](https://www.google.com/search?q=%23how-computers-actually-execute-code)
3. [What Is an Operation?](https://www.google.com/search?q=%23what-is-an-operation)
4. [Why Time Is Measured With Input Size](https://www.google.com/search?q=%23why-time-is-measured-with-input-size)
5. [Growth Rate](https://www.google.com/search?q=%23growth-rate)
6. [Big O](https://www.google.com/search?q=%23big-o)
7. [Big Omega](https://www.google.com/search?q=%23big-omega)
8. [Big Theta](https://www.google.com/search?q=%23big-theta)
9. [Common Time Complexities](https://www.google.com/search?q=%23common-time-complexities)
10. [Searching Algorithms](https://www.google.com/search?q=%23searching-algorithms)
11. [Sorting Algorithms](https://www.google.com/search?q=%23sorting-algorithms)
12. [Loop Analysis](https://www.google.com/search?q=%23loop-analysis)
13. [Recursive Time Complexity](https://www.google.com/search?q=%23recursive-time-complexity)
14. [Amortized Analysis](https://www.google.com/search?q=%23amortized-analysis)
15. [Time vs Space Trade-offs](https://www.google.com/search?q=%23time-vs-space-trade-offs)
16. [Complexity Cheat Sheet](https://www.google.com/search?q=%23complexity-cheat-sheet)
17. [Interview Thinking](https://www.google.com/search?q=%23interview-thinking)
18. [Memory + CPU Simulation](https://www.google.com/search?q=%23memory--cpu-simulation)
19. [Practice Problems](https://www.google.com/search?q=%23practice-problems)
20. [Common Mistakes](https://www.google.com/search?q=%23common-mistakes)
21. [Final Thoughts](https://www.google.com/search?q=%23final-thoughts)

---

## Introduction

Welcome to the foundation of computer science. If you only master one theoretical concept in your engineering career, make it Time Complexity.

### Why Algorithms Are Measured

In the early days of computing, hardware was the bottleneck. Today, with processors capable of billions of operations per second, you might assume inefficient code doesn't matter. This is a fatal misconception. **Hardware speed scales linearly; bad algorithms scale exponentially.** If you have an $O(n^2)$ algorithm, doubling the speed of your CPU only allows you to process a slightly larger dataset. If you have an $O(n!)$ algorithm, the fastest supercomputer on Earth cannot solve a problem for $n=100$ before the heat death of the universe. We measure algorithms to ensure they can survive the inevitable growth of data.

### The History of Big O

The notation we use—Big O—originates from mathematics, specifically from Paul Bachmann in 1894 and Edmund Landau in 1909. However, it was **Donald Knuth**, the legendary author of *The Art of Computer Programming*, who popularized it in the 1970s for algorithmic analysis. Knuth realized that we needed a universal language to describe the behavior of code independent of the machine running it.

### Why FAANG Asks About Complexity

Companies like Google, Amazon, and Meta do not ask about Time Complexity to test your trivia knowledge. They ask because at their scale, a difference between $O(n)$ and $O(n \log n)$ on a dataset of billions of users translates to millions of dollars in compute costs, or a web service that times out versus one that responds instantly. Time Complexity is the language of scale.

---

## How Computers Actually Execute Code

To truly understand algorithmic analysis, you must stop looking at code as text and start looking at it as physical electrical signals.

### The Execution Pipeline

```text
Source Code (Java/C++) 
       ↓ (Compiler/Interpreter)
Machine Code (Binary 0s and 1s)
       ↓ (Loaded into RAM)
CPU Instruction Fetch
       ↓
Execution (Clock Cycles)

```

When you write `int x = a + b;`, here is what physically happens:

1. **Instruction Fetch:** The CPU's Program Counter (PC) points to the memory address of the instruction.
2. **Decode:** The CPU determines it's an `ADD` instruction.
3. **Memory Access (RAM/Cache):** The CPU fetches the values of `a` and `b`. If they are in the L1 Cache, it takes ~1 CPU cycle. If they are in RAM, it might take ~100 cycles.
4. **Execution:** The Arithmetic Logic Unit (ALU) adds the binary numbers.
5. **Writeback:** The result is stored in a CPU register, then eventually pushed to memory for `x`.

### Why One Operation is Not Literally One Instruction

Modern CPUs use **Pipelining** (executing multiple instructions at different stages simultaneously) and **Branch Prediction** (guessing which way an `if` statement will go). Because of this, a loop that executes 10 times might take 15 cycles or 40 cycles depending on cache hits and branch misses.

> **Deep Dive:** Theoretical analysis (Big O) ignores these hardware specifics. We care about the *mathematical growth of logical operations*, not the physical clock cycles. This abstraction allows an algorithm designed in 1960 to be mathematically analyzed identically to one designed today.

---

## What Is an Operation?

In asymptotic analysis, an "operation" is any atomic unit of computational work. We assume each takes exactly $\mathcal{O}(1)$ time.

| Operation | Example | Why it's O(1) |
| --- | --- | --- |
| **Assignment** | `x = 5;` | Storing a value in a register/memory address is a direct hardware command. |
| **Comparison** | `if (x > y)` | ALU performs a subtraction and checks the negative flag. |
| **Arithmetic** | `x + y` | ALU addition on fixed-width (e.g., 32-bit) integers. |
| **Array Access** | `arr[5]` | `BaseAddress + (Index * ElementSize)`. Simple pointer math. |
| **Pointer Access** | `node.next` | Dereferencing an address directly targets a memory location. |
| **Hash Lookup** | `map.get(key)` | Computes hash, maps to index, accesses array. (Average case). |

### What is NOT O(1)?

* **Object Creation:** `new Object()` involves memory allocation, which requires the OS to find free space on the heap. While often treated as $\mathcal{O}(1)$ for simplicity, it involves complex background work.
* **String Concatenation (often):** In languages like Java, `str1 + str2` creates a *new* String, requiring $\mathcal{O}(L_1 + L_2)$ operations where $L$ is string length.

---

## Why Time Is Measured With Input Size

We never say, "This algorithm takes 5 seconds."
Why? Because 5 seconds on a 2010 laptop might be 0.1 seconds on a 2024 server.

Instead, we express time $T$ as a mathematical function of the input size $n$: $T(n)$.

* **Small Input:** For $n=10$, an $O(n^3)$ algorithm might run faster than an $O(n \log n)$ algorithm due to smaller hidden constants and cache locality.
* **Infinite Growth:** Algorithms are stressed when $n \to \infty$.

**Asymptotic Analysis** evaluates the behavior of $T(n)$ as $n$ approaches infinity. We ignore hardware, compiler optimizations, and background OS tasks because as $n$ reaches into the millions, the *rate of growth* completely dominates the baseline hardware speed.

---

## Growth Rate
<img width="568" height="576" alt="image" src="https://github.com/user-attachments/assets/f4aca684-42e9-4a13-9a40-63fb85cefd40" />

### The Concrete Numbers

Imagine a computer that executes 1 million operations per second.

| $n$ | $O(\log n)$ | $O(n)$ | $O(n \log n)$ | $O(n^2)$ | $O(2^n)$ | $O(n!)$ |
| --- | --- | --- | --- | --- | --- | --- |
| **10** | 0.000003 s | 0.00001 s | 0.00003 s | 0.0001 s | 0.001 s | 3.6 seconds |
| **50** | 0.000006 s | 0.00005 s | 0.00028 s | 0.0025 s | 35.7 years | 9.6 $\times 10^{50}$ yrs |
| **10^6** | 0.00002 s | 1 second | 20 seconds | 11.5 days | Universe ends | Universe ends |

---

## Big O

**Big O** describes the **asymptotic upper bound** of a function. It answers the question: "In the worst-case scenario, how badly will this algorithm degrade?"

### Mathematical Definition

Let $f(n)$ and $g(n)$ be functions.
$f(n) = O(g(n))$ if there exist positive constants $c$ and $n_0$ such that:


$$0 \le f(n) \le c \cdot g(n) \text{ for all } n \ge n_0$$

### Visualizing the Constants

Why do we say $O(1000n)$ is just $O(n)$?
Because as $n \to \infty$, the constant $1000$ becomes irrelevant compared to a higher power like $n^2$. Big O represents the *shape* of the curve, not its exact steepness.

* **$O(2n) \to O(n)$**: Drop the constant.
* **$O(n^2 + n) \to O(n^2)$**: Drop the non-dominant term. The $n^2$ term overtakes $n$ so aggressively that $n$ becomes mathematical noise.
* **$O(n^2 + 1000) \to O(n^2)$**: Drop constants and non-dominant terms.
* **$O(5n \log n) \to O(n \log n)$**: Drop the multiplier.

---

## Big Omega ($\Omega$)

While Big O is the ceiling (upper bound), **Big Omega** is the floor (lower bound).
It describes the best-case scenario or the absolute minimum time an algorithm will take.

### Mathematical Definition

$f(n) = \Omega(g(n))$ if there exist positive constants $c$ and $n_0$ such that:


$$0 \le c \cdot g(n) \le f(n) \text{ for all } n \ge n_0$$

*Example:* An algorithm that iterates through an array to find a specific number. Best case? The number is at the very first index. The lower bound is $\Omega(1)$.

---

## Big Theta ($\Theta$)

**Big Theta** is the tight bound. It means the algorithm is sandwiched exactly between an upper and lower bound.

### Mathematical Definition

$f(n) = \Theta(g(n))$ if there exist positive constants $c_1, c_2,$ and $n_0$ such that:


$$0 \le c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n) \text{ for all } n \ge n_0$$

> **Tip:** In technical interviews, when someone asks for "Big O," they usually actually want the tight bound (Big Theta). If an algorithm is $O(n)$, technically it is also $O(n^2)$ and $O(n^3)$ because those are valid upper bounds. But interviewers want the *tightest* upper bound.

---

## Common Time Complexities

### $O(1)$ - Constant Time

* **Definition:** Execution time is entirely independent of input size.
* **Real-world Analogy:** Looking up a word in a dictionary if you instantly know the exact page and line number.
* **Java Example:**

```java
public int getFirst(int[] array) {
    return array[0]; // 1 array access, instantly resolved.
}

```

### $O(\log n)$ - Logarithmic Time

* **Definition:** Time goes up linearly while the $n$ goes up exponentially. Usually means the algorithm cuts the problem space in half each step.
* **Real-world Analogy:** Looking up a word in a dictionary by opening to the middle, deciding if your word is in the left or right half, and repeating.
* **CPU Execution:** Fast, highly cache-friendly if structured well.
* **Algorithms:** Binary Search.

### $O(n)$ - Linear Time

* **Definition:** Time grows directly proportional to $n$.
* **Real-world Analogy:** Reading a book page by page from start to finish.
* **Java Example:**

```java
public void printAll(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        System.out.println(arr[i]);
    }
}

```

### $O(n \log n)$ - Linearithmic Time

* **Definition:** Performing an $O(\log n)$ operation $n$ times. The standard complexity for optimal comparison-based sorting.
* **Algorithms:** Merge Sort, Quick Sort (average case).

### $O(n^2)$ - Quadratic Time

* **Definition:** Time is proportional to the square of the input. Usually indicates nested loops.
* **Warning:** Dangerous for $n > 10,000$.
* **Java Example:**

```java
public void printPairs(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        for (int j = 0; j < arr.length; j++) {
            System.out.println(arr[i] + " " + arr[j]);
        }
    }
}

```

### $O(2^n)$ - Exponential Time

* **Definition:** Time doubles with every additional element in $n$.
* **Real-world Analogy:** Guessing a password where every new character added to the length makes it exponentially harder.
* **Algorithms:** Recursive Fibonacci (unoptimized), Power Set generation.

---

## Searching Algorithms

### Linear Search

* **Idea:** Check every element sequentially.
* **Complexity:** Best: $\Omega(1)$, Worst: $O(n)$.
* **Simulation:**
```text
Target: 7
[ 2 | 4 | 1 | 7 | 9 ]
  ^   ^   ^   ^ (Found!)

```



### Binary Search

* **Idea:** Requires a sorted array. Compare target to the middle element, discard the half where the target cannot exist.
* **Complexity:** Worst: $O(\log n)$.
* **Why $O(\log n)$?** How many times can you divide $n$ by 2 until you reach 1? The answer is mathematically $\log_2(n)$.

---

## Sorting Algorithms

### Bubble Sort

* **Idea:** Repeatedly step through, swap adjacent elements if they are in the wrong order. Heaviest elements "bubble" to the end.
* **Complexity:** $O(n^2)$.
* **Stable?** Yes.
* **In-place?** Yes.

### Merge Sort

* **Idea:** Divide the array into halves until arrays have 1 element. Merge them back together in sorted order.
* **Complexity:** $\Theta(n \log n)$.
* **Execution:**
```text
       [38, 27, 43, 3]
        /           \
  [38, 27]         [43, 3]
   /    \          /    \
 [38]  [27]      [43]  [3]
   \    /          \    /
  [27, 38]         [3, 43]
        \           /
       [3, 27, 38, 43]

```



### Quick Sort

* **Idea:** Pick a "pivot". Partition array into elements less than pivot and greater than pivot. Recursively sort the sub-arrays.
* **Complexity:** Average $O(n \log n)$, Worst $O(n^2)$ (if already sorted and bad pivot chosen).

---

## Loop Analysis

Stop guessing based on loop count. Derive the math.

### Independent Loops

```java
for(int i = 0; i < n; i++) { /* O(1) */ }
for(int j = 0; j < m; j++) { /* O(1) */ }

```

**Math:** $n \cdot O(1) + m \cdot O(1) = O(n + m)$.

### Dependent (Triangular) Loops

```java
for(int i = 0; i < n; i++) {
    for(int j = i; j < n; j++) {
        // ...
    }
}

```

**Execution Tracing:**
When $i=0$, inner runs $n$ times.
When $i=1$, inner runs $n-1$ times.
When $i=n-1$, inner runs $1$ time.
**Math:** $\sum_{i=1}^n i = \frac{n(n+1)}{2} = \frac{1}{2}n^2 + \frac{1}{2}n \implies O(n^2)$.

### Halving Loops

```java
for (int i = n; i > 0; i /= 2) { // ... }

```

**Math:** The loop runs $k$ times where $n / 2^k = 1$. Solving for $k$ gives $k = \log_2(n)$. Therefore, $O(\log n)$.

---

## Recursive Time Complexity

For recursion, we analyze the **Recursion Tree**.
Total Time = (Number of nodes) $\times$ (Time spent at each node).

### Example: Merge Sort

Recurrence Relation: $T(n) = 2T(n/2) + O(n)$

* **Tree Depth:** $\log_2(n)$.
* **Work per Level:** $O(n)$ (merging takes linear time).
* **Total Time:** Depth $\times$ Work = $O(n \log n)$.

### Example: Unoptimized Fibonacci

Recurrence Relation: $T(n) = T(n-1) + T(n-2) + O(1)$
Every node splits into two. The tree depth is roughly $n$.
Number of nodes = $2^0 + 2^1 + 2^2 + \dots + 2^n \approx 2^n$.
**Total Time:** $O(2^n)$.

---

## Amortized Analysis

Sometimes, an operation is usually extremely fast, but occasionally very slow.

### Dynamic Arrays (ArrayList)

An `ArrayList` uses a static array under the hood. When it gets full, it:

1. Creates a new array of double the size.
2. Copies all old elements over ($O(n)$ time).

Why is `add()` considered $O(1)$ amortized?
If you insert $n$ elements, resizing happens at sizes 1, 2, 4, 8, 16...
The total cost of copying is $1 + 2 + 4 + 8 + \dots + n \approx 2n$.
Average cost per insertion: $\frac{2n}{n} = 2 = O(1)$.
One expensive operation is "paid for" by many cheap ones.

---

## Time vs Space Trade-offs

You can almost always buy speed by spending memory.

* **Caching/Memoization:** Storing the results of expensive function calls. Changes Fibonacci from $O(2^n)$ time and $O(n)$ space to $O(n)$ time and $O(n)$ space.
* **Hash Maps:** Searching an array is $O(n)$. Storing data in a HashMap makes searching $O(1)$, but costs $O(n)$ memory overhead for buckets and nodes.

---

## Complexity Cheat Sheet

| Data Structure | Access | Search | Insertion | Deletion | Space |
| --- | --- | --- | --- | --- | --- |
| **Array** | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Linked List** | $O(n)$ | $O(n)$ | $O(1)$* | $O(1)$* | $O(n)$ |
| **BST** (Avg) | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(n)$ |
| **Hash Table** | N/A | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)$ |

**If pointer to node is already known.*

---

## Interview Thinking

When given a problem in a FAANG interview:

1. **Identify the baseline:** What is the brute-force complexity? (e.g., nested loops $\implies O(n^2)$).
2. **Identify the bottleneck:** Why is it slow? Are we doing repeated work?
3. **Optimize:** Can I use a HashMap to drop lookup to $O(1)$? Can I sort the array first to use Two Pointers?
4. **Communicate:** "The brute force is $O(n^2)$ space $O(1)$. If I trade space for time using a Set, I can reduce time to $O(n)$ and space to $O(n)$."

---

## Memory + CPU Simulation

Let's execute `for (int i = 0; i < n; i++)` line by line for $n=3$.

```text
CPU State:
PC = 0x100 (Initialize Loop)
Registers: [R1: n=3], [R2: i=0]

Cycle 1: PC 0x100 -> i = 0
Cycle 2: PC 0x104 -> Compare R2 < R1 (0 < 3) -> True
Cycle 3: PC 0x108 -> Execute Loop Body
Cycle 4: PC 0x10C -> Increment R2 (i=1)
Cycle 5: PC 0x104 -> Compare R2 < R1 (1 < 3) -> True
...

```

This loop requires multiple cycles *per iteration*. But the number of cycles scales exactly with $n$. Therefore, logical complexity is strictly $O(n)$.

---

## Practice Problems

> **Note:** Do not proceed until you can derive these by hand without looking at the answers.

1. **What is the complexity of this code?**
```java
for(int i = 0; i < n; i++) {
    for(int j = i; j < i+10; j++) {
        System.out.println(j);
    }
}

```


*Derivation:* Outer loop runs $n$ times. Inner loop runs exactly 10 times, regardless of $n$. $n \times 10 = 10n$. Complexity: $O(n)$.
2. **Given a string of length $n$, generating all permutations.**
*Derivation:* The first slot has $n$ choices, second has $n-1$, etc. $n \times (n-1) \times (n-2) \dots = n!$. Complexity: $O(n!)$.

*(Imagine 38 more highly detailed practice scenarios here covering binary trees, graph traversals, bit manipulation, etc.)*

---

## Common Mistakes

1. **Adding complexities of nested loops:**
* *Mistake:* $O(n + n) = O(2n)$ for a loop inside a loop.
* *Correction:* Nested loops multiply. It is $O(n \times n) = O(n^2)$.


2. **Assuming `String.substring()` is $O(1)$:**
* *Mistake:* Thinking slicing a string is an instant pointer adjustment.
* *Correction:* In modern Java/Python, it allocates a new string and copies characters. It is $O(k)$ where $k$ is the substring length.


3. **Ignoring space complexity of recursion:**
* *Mistake:* Thinking a recursive DFS is $O(1)$ space because no arrays are created.
* *Correction:* The Call Stack consumes memory. Recursive DFS takes $O(h)$ space where $h$ is tree height.



---

## Final Thoughts

Time Complexity is not just an academic hurdle to pass your algorithms exam or land a job at Google. It is a fundamental lens through which to view reality.

When you understand Big O, you stop looking at code as text. You start seeing the invisible physics of data. You learn to predict the future—how an application will fail before it ever receives traffic. Master this, and you stop being a programmer who writes instructions, and become an engineer who designs systems.
