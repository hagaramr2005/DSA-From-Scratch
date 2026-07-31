# Hash Tables

## 1. Introduction

A **Hash Table** is a data structure that supports the dictionary operations `INSERT`, `SEARCH`, and `DELETE` by using a **hash function** to compute the position where an element should be stored, instead of using the key itself as the index. It solves the core weakness of direct-address tables: the need to allocate a table as large as the entire universe of possible keys, even when only a small number of those keys are actually used.

A hash table generalizes the simpler notion of an ordinary array. Instead of using the key as an array index directly, the array index is **computed from the key**.

---

## 2. From Direct-Address Tables to Hash Tables

As explained in [`01-Direct-Address-Tables.md`](./01-Direct-Address-Tables.md), a direct-address table stores an element with key `k` at index `k`, requiring a table of size `|U|`, where `U` is the universe of all possible keys.

This becomes inefficient when:

- The universe `U` is very large or unbounded, making a table of size `|U|` impractical or impossible to allocate.
- The set of keys actually stored, `K`, is much smaller than `U`, meaning most of the table would sit unused.

A hash table addresses this by reducing the storage requirement to be proportional to the number of keys actually stored, rather than the size of the entire key universe — while still aiming to keep search, insert, and delete operations fast on average.

---

## 3. Hash Table Structure

The basic conceptual flow of a hash table is:

```
Key
 ↓
Hashing
 ↓
Table Position
 ↓
Stored Element
```

Instead of the key becoming the index directly (as in direct addressing), the key is passed through a **hash function** `h`, which produces an index within the bounds of a much smaller table.

```
h : U → {0, 1, ..., m-1}
```

Here, `m` is the size of the hash table, and `m` is typically much smaller than `|U|`. An element with key `k` is said to **hash** to slot `h(k)`, and `h(k)` is called the **hash value** of key `k`.

---

## 4. Basic Example

Consider storing the following key-value pairs, where names are keys and ages are values:

```
Ahmed → 20
Mona  → 22
Ali   → 19
```

Conceptually, each key (`"Ahmed"`, `"Mona"`, `"Ali"`) is passed through a hash function, which produces a table position for that key. The corresponding value is then stored at that position.

```
"Ahmed"  →  Hashing  →  Index 4  →  stores 20
"Mona"   →  Hashing  →  Index 1  →  stores 22
"Ali"    →  Hashing  →  Index 7  →  stores 19
```

The exact mechanism used to turn a key like `"Ahmed"` into a table index is the responsibility of the hash function, which is covered separately in [`03-Hash-Functions.md`](./03-Hash-Functions.md). At this stage, it is enough to understand that hashing is the process that determines *where* a key-value pair is stored.

---

## 5. Hash Table Operations

| Operation | Description | Average Case |
|---|---|---|
| Search | Compute `h(k)` and look for the element with key `k` at that position | `O(1)` |
| Insert | Compute `h(k)` and place the new element at that position | `O(1)` |
| Delete | Compute `h(k)`, locate the element, and remove it | `O(1)` |

**Search:** To search for an element with key `k`, the hash table computes `h(k)` and looks at the corresponding position to find the element.

**Insert:** To insert an element with key `k`, the hash table computes `h(k)` and places the element at that position.

**Delete:** To delete an element, the hash table computes `h(k)` to locate it, and then removes it from that position.

**Important distinction:** These `O(1)` figures are **average-case** performance, under reasonable assumptions about how well the hash function distributes keys across the table. In the worst case — for example, if many keys happen to map to the same position — performance can degrade. Searching for an element in a hash table can take as long as searching through a linked list, `Θ(n)` time, in the worst case. The reasons behind this worst-case behavior, and how it is managed, are discussed in [`04-Collisions.md`](./04-Collisions.md).

---

## 6. Hash Tables vs Direct-Address Tables

| Aspect | Direct-Address Table | Hash Table |
|---|---|---|
| Key space | Requires the key universe `U` to be small enough to allocate a full table | Works well even when `U` is very large |
| Memory usage | Proportional to `|U|` (the entire key universe) | Proportional to the number of keys actually stored |
| Access mechanism | Key is used directly as the array index | Key is passed through a hash function to compute the index |
| Advantages | Simple, guaranteed `O(1)` in every case (worst case included) | Much lower memory usage; still `O(1)` on average |
| Limitations | Impractical or impossible for large or unbounded key universes | Two different keys may map to the same position (a collision), which must be resolved |

A hash table trades the *guaranteed* worst-case performance of direct addressing for significantly reduced memory usage, while keeping performance close to constant time on average.

---

## 7. Hashing Idea

The fundamental idea behind hashing is mapping keys from a potentially large universe into positions in a much smaller table:

```
Key
 ↓
Hashing mechanism
 ↓
Index
 ↓
Table
```

Because the key universe `U` is larger than the table size `m`, it is guaranteed that at least two keys will end up computing the same index. How exactly a hash function is designed to minimize this, and what makes a hash function "good," is covered in detail in [`03-Hash-Functions.md`](./03-Hash-Functions.md).

---

## 8. Collisions

Because the hash function maps a large key universe into a smaller table, it is possible — and unavoidable in general — for two different keys to map to the same table position. This is called a **collision**.

**Example:**

```
Key A → Index 3
Key B → Index 3
```

Both `Key A` and `Key B` hash to the same index, `3`. This creates a problem: if both elements are meant to be stored, the table needs a way to hold more than one element at the same position without one overwriting the other.

This document does not cover how collisions are resolved. That is addressed in:

- [`04-Collisions.md`](./04-Collisions.md)
- [`05-Open-Addressing.md`](./05-Open-Addressing.md)

---

## 9. HashMap and HashSet

Two common structures built on top of the hash table idea are `HashMap` and `HashSet`, which differ in what they store:

**`HashMap`: Key → Value**

A `HashMap` stores a mapping from a key to an associated value.

```python
student = {
    "Ahmed": 20,
    "Mona": 22
}
```

Here, each name (key) maps to an age (value). Looking up `student["Ahmed"]` retrieves `20`.

**`HashSet`: Element → Membership**

A `HashSet` stores only elements themselves, with no associated value — its purpose is to answer "is this element present?"

```python
seen = {10, 20, 30}
```

Checking `20 in seen` answers whether `20` has already been recorded, without storing any additional data attached to it.

**When each is useful:**

- Use a `HashMap` when you need to associate a key with some value (e.g., a name with an age, a word with a count).
- Use a `HashSet` when you only care whether an element exists or has been seen, with no extra data needed.

---

## 10. Hash Tables in Problem Solving

Hash tables are important in coding problems because they allow operations that would otherwise require scanning through data (`O(n)`) to instead run in `O(1)` on average. Several recurring patterns rely on this:

**Fast Lookup**
Instead of checking whether a value exists by scanning a list, a hash table allows checking membership directly.
*Example:* Checking if a number exists in a collection of seen numbers.
*Why hashing helps:* Membership checks become average `O(1)` instead of `O(n)`.

**Duplicate Detection**
Tracking elements that have already been encountered to detect repeats.
*Example:* Determining whether any value in a list appears more than once.
*Why hashing helps:* A `HashSet` can record "seen" elements and check for repeats in constant average time.

**Frequency Counting**
Counting how many times each element occurs.
*Example:* Counting how many times each character appears in a string.
*Why hashing helps:* A `HashMap` can map each element to a running count, updated in constant average time per element.

**Key → Value Mapping**
Associating one piece of data with another for quick retrieval.
*Example:* Mapping a student's name to their age, as in the `student` example above.
*Why hashing helps:* Retrieving the value for a given key avoids searching through a list of pairs.

**Tracking Previously Seen Elements**
Remembering which elements have already been processed while iterating through data.
*Example:* Recording which indices or values have already been visited.
*Why hashing helps:* A `HashSet` provides constant-time average lookups to check "have I seen this before?"

**Complement Lookup**
Looking for a value that would "complete" a condition together with the current value.
*Example:* Given a number, checking whether its complement relative to a target has already been seen.
*Why hashing helps:* Instead of searching the rest of the data for the complement, a hash table allows checking for it in constant average time.

---

## 11. Recognizing Hashing Problems

The following checklist reflects common signals that a hash-based structure (`HashMap` or `HashSet`) may help:

- "If I need to know whether I've seen this element before..." → `HashSet`
- "If I need to count how many times something appears..." → `HashMap`
- "If I need to map one thing to another..." → `HashMap`
- "If I need fast membership checking..." → `HashSet`
- "If I need fast lookup of a complement..." → `HashSet` / `HashMap`

These are **patterns to consider**, not strict rules that every problem must follow. Not every problem involving lookups or counting requires a hash table, but these signals are a useful starting point when analyzing a new problem.

---

## 12. Python Examples

### HashMap — Frequency Counting

```python
freq = {}

for num in nums:
    freq[num] = freq.get(num, 0) + 1
    # freq.get(num, 0) returns the current count, or 0 if num hasn't been seen yet
    # each update is an average O(1) operation
```

### HashSet — Duplicate Detection

```python
seen = set()

for num in nums:
    if num in seen:
        # num has already been encountered — a duplicate
        print("Duplicate found:", num)
    seen.add(num)
    # membership check and insertion are both average O(1)
```

### HashMap — Key → Value Lookup

```python
student = {
    "Ahmed": 20,
    "Mona": 22
}

age = student.get("Ahmed")
# retrieves 20 directly, without scanning through the dictionary
```

---

## 13. Complexity Summary

| Operation | Average Case | Notes |
|---|---|---|
| Search | `O(1)` | Assumes a well-distributed hash function and controlled load factor |
| Insert | `O(1)` | Same assumption as above |
| Delete | `O(1)` | Same assumption as above |
| Worst Case (any operation) | `O(n)` | Occurs when many keys collide, as discussed in `04-Collisions.md` |

The `O(1)` average-case performance depends on the hash function distributing keys well across the table — a topic explored fully in [`03-Hash-Functions.md`](./03-Hash-Functions.md).

---

## 14. Key Takeaways

- A hash table computes the storage position of a key using a hash function, rather than using the key directly as an index.
- This reduces memory usage to be proportional to the number of stored keys, rather than the size of the entire key universe.
- Search, Insert, and Delete are `O(1)` on **average**, but can degrade to `O(n)` in the worst case due to collisions.
- Because the key universe is generally larger than the table size, collisions — two keys mapping to the same position — are unavoidable in general.
- `HashMap` stores key-value pairs, while `HashSet` stores elements for membership checking only.
- Many common problem-solving patterns (fast lookup, duplicate detection, frequency counting, complement lookup) rely directly on hash table behavior.

---

## 15. Quick Revision

```
Hash Table       = A structure that maps keys to table positions using a hash function
Hashing          = The process of computing an index from a key
Collision        = When two different keys map to the same index
HashMap          = Stores Key → Value pairs
HashSet          = Stores elements for membership checking only
Average Case     = O(1) for Search, Insert, and Delete
Worst Case       = O(n), caused by collisions
Next topic       = Hash Functions
```

---

## 16. Questions to Test Understanding

1. What problem does a hash table solve that a direct-address table cannot solve efficiently?
2. What is the role of the hash function in a hash table?
3. Why is average-case `O(1)` different from worst-case performance?
4. What is the difference between a `HashMap` and a `HashSet`?
5. Why are collisions unavoidable in general?

<details>
<summary>Answers</summary>

1. A hash table avoids the need to allocate a table as large as the entire key universe. It maps keys into a much smaller table using a hash function, so memory usage is proportional to the number of stored elements rather than the number of possible keys.
2. The hash function computes the table position (index) for a given key, replacing the direct use of the key as an index in direct-address tables.
3. Average-case `O(1)` assumes the hash function distributes keys well across the table. In the worst case, many keys may collide into the same position, causing operations to degrade toward `O(n)`, similar to searching a linked list.
4. A `HashMap` stores a key mapped to an associated value (`Key → Value`), while a `HashSet` stores only elements themselves, used purely to check membership (`Element → Membership`).
5. Because the universe of possible keys is generally larger than the number of available table positions, it is mathematically guaranteed that at least two keys will map to the same position.

</details>

---

## 17. Navigation

Previous:
[Direct-Address Tables](01-Direct-Address-Tables.md)

Next:
[Hash Functions](03-Hash-Functions.md)
