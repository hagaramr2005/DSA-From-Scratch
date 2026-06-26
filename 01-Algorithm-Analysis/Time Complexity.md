# ⏳ Time Complexity

> *"An efficient algorithm is not the one that runs fast on your laptop today, but the one that still runs efficiently when the input grows a thousand times larger."*

---

# What is Time Complexity?

Time Complexity is one of the most fundamental concepts in Computer Science.

Despite its name, **Time Complexity does NOT measure time.**

It does not tell us:

- How many milliseconds an algorithm takes.
- How many seconds it runs.
- How fast your computer is.

Instead, it answers a much more important question.

> **How does the amount of work performed by an algorithm grow as the input size increases?**

In other words,

Time Complexity measures the **growth rate** of an algorithm.

---

# Why don't we measure execution time?

Imagine the following scenario.

You and your friend wrote exactly the same Java program.

### Your computer

```
Intel Core i3
8 GB RAM
Execution Time = 180 ms
```

### Your friend's computer

```
Intel Core i9
32 GB RAM
Execution Time = 35 ms
```

Now ask yourself...

Which algorithm is better?

The answer is

**Neither.**

Both algorithms are identical.

The only difference is the hardware.

If we measured algorithms using seconds,

the result would change depending on

- Processor speed
- RAM size
- Operating System
- Compiler optimization
- Background applications
- CPU temperature
- Battery mode

These factors have nothing to do with the quality of the algorithm itself.

Computer Scientists needed a universal way to compare algorithms.

That's where Time Complexity was born.

---

# The Main Idea

Instead of asking

```
How many seconds does this algorithm take?
```

we ask

```
How many operations does this algorithm perform?
```

As the input grows,

does the number of operations

- stay constant?
- grow linearly?
- grow quadratically?
- grow exponentially?

This relationship is called

## Time Complexity

---

# Understanding the Input Size

Every algorithm receives an input.

Example

```java
int[] numbers = new int[n];
```

The variable

```
n
```

represents the number of elements.

If

```
n = 10
```

the algorithm works with ten elements.

If

```
n = 1,000
```

it processes one thousand elements.

If

```
n = 10,000,000
```

it processes ten million elements.

As **n** increases,

the algorithm performs more work.

Time Complexity describes **how fast that work grows**.

---

# Example

```java
for(int i = 0; i < n; i++)
{
    System.out.println(i);
}
```

Let's analyze every operation.

Initialization

```java
i = 0;
```

Performed once.

Comparison

```java
i < n
```

Performed approximately **n** times.

Increment

```java
i++
```

Performed **n** times.

Print

```java
System.out.println(i);
```

Performed **n** times.

Total work

```
1 + n + n + n

≈ 3n + 1
```

In Big-O,

constants do not matter.

```
O(3n + 1)

↓

O(n)
```

---

# Why do we ignore constants?

Suppose we have two algorithms.

Algorithm A

```
5n
```

Algorithm B

```
100n
```

Algorithm C

```
n²
```

At first,

Algorithm B looks terrible.

But let's test them.

Suppose

```
n = 1,000,000
```

Algorithm A

```
5 × 1,000,000

=

5,000,000 operations
```

Algorithm B

```
100 × 1,000,000

=

100,000,000 operations
```

Algorithm C

```
1,000,000²

=

1,000,000,000,000 operations
```

Notice something amazing.

The difference between

```
5n

and

100n
```

is much smaller than the difference between

```
n

and

n²
```

Big-O only cares about

**how the algorithm grows**.

Not about small constant differences.

---

# What is Big-O?

Big-O is a mathematical notation used to describe the **upper bound** of an algorithm's running time.

It tells us

> **The maximum amount of work an algorithm may perform as the input grows.**

Example

Linear Search

Best Case

```
Find the element immediately.

1 comparison.
```

Worst Case

```
Search the entire array.

n comparisons.
```

Therefore,

```
Time Complexity = O(n)
```

---

# Why do we focus on the Worst Case?

Imagine you're developing

- Google Search
- Facebook
- Instagram
- Amazon

Millions of users use your system.

You cannot design your algorithm assuming

"Users will always search for the first element."

Instead,

you prepare for

the slowest possible scenario.

That's why Big-O almost always refers to

**Worst Case Complexity**.

---

# Time Complexity is about Scalability

Imagine two algorithms.

Algorithm A

```
O(n)
```

Algorithm B

```
O(n²)
```

If

```
n = 10
```

Algorithm A

```
10 operations
```

Algorithm B

```
100 operations
```

Not a huge difference.

But now,

```
n = 1,000,000
```

Algorithm A

```
1,000,000 operations
```

Algorithm B

```
1,000,000,000,000 operations
```

One million

vs

One trillion.

This is why choosing the correct algorithm matters.

---

# The Real Goal

Time Complexity helps us answer one question.

> **If my input becomes 10 times larger... 100 times larger... or one million times larger... will my algorithm still be practical?**

That is why Time Complexity is one of the most important topics in Computer Science.

It is not about writing code that is fast today.

It is about writing code that continues to be fast tomorrow.
