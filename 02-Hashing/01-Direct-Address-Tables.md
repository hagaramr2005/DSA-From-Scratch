# Direct-Address Tables

A **Direct-address table** is the simplest possible way to implement a dynamic set that supports `INSERT`, `SEARCH`, and `DELETE`. It works by using the key of an element as the actual index into an array. It is called "direct-address" because the key **directly** addresses a position in the table — there is no computation or transformation between the key and the location where the element is stored.

Direct-address tables solve a very specific problem: when the universe of possible keys is small enough, you can allocate one array slot for every possible key and access any element in constant time. This idea is the starting point for understanding why Hash Tables exist at all.

---

## 1. The Basic Idea

The core idea can be summarized as a direct relationship:

```
Key → Array Index → Stored Data
```

If an element's key is `k`, that element is stored at position `k` in the array — no intermediate step is involved.

**Example — a small key universe:**

```
Keys: 0, 1, 2, 3, 4, 5
```

Each of these keys corresponds exactly to one position in an array of size 6. Key `3` belongs at index `3`, key `5` belongs at index `5`, and so on.

**ASCII visualization:**

```
Index:   0     1     2     3     4     5
        +-----+-----+-----+-----+-----+-----+
Table:  | NIL | NIL | NIL | NIL | NIL | NIL |
        +-----+-----+-----+-----+-----+-----+
```

Every slot corresponds to a key in the universe. A slot holds an element if that key is currently in the set, or `NIL` if it is not.

---

## 2. How It Works

A direct-address table is represented as an array `T[0 : m-1]`, where the universe of keys is `U = {0, 1, ..., m-1}`.

- Each **slot** (position) in the array corresponds to exactly one key in `U`.
- To access the element with key `k`, you simply look at `T[k]`.
- **If a key exists** in the set, `T[k]` points to (or stores) the element with that key.
- **If a key does not exist** in the set, `T[k]` is `NIL`.

There is no searching involved — the key tells you exactly where to look.

**Example:** With keys drawn from `U = {0, 1, ..., 9}`, if the set currently stored is `K = {2, 3, 5, 8}`, then:

```
Index:   0     1     2     3     4     5     6     7     8     9
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
Table:  | NIL | NIL |  x  |  x  | NIL |  x  | NIL | NIL |  x  | NIL |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
```

Slots `2`, `3`, `5`, and `8` hold elements; all other slots are `NIL`.

---

## 3. Example

Consider a table of size `m = 10`, so the key universe is `U = {0, 1, ..., 9}`.

**Before insertion:**

```
Index:   0     1     2     3     4     5     6     7     8     9
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
Table:  | NIL | NIL | NIL | NIL | NIL | NIL | NIL | NIL | NIL | NIL |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
```

**Operations performed:**

1. Insert an element with key `2`.
2. Insert an element with key `5`.
3. Insert an element with key `8`.

**After insertion:**

```
Index:   0     1     2     3     4     5     6     7     8     9
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
Table:  | NIL | NIL |  x  | NIL | NIL |  x  | NIL | NIL |  x  | NIL |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
```

Each insertion places the element directly at the index matching its key — no other slots are touched or examined.

---

## 4. Operations

Direct-address tables support three basic dictionary operations:

- **Search:** Look up `T[k]` directly to see if an element with key `k` is stored.
- **Insert:** Place the element at `T[k]`, where `k` is the element's key.
- **Delete:** Set `T[k]` to `NIL`.

| Operation | Idea | Time Complexity |
|---|---|---|
| Search | Access `T[k]` directly and return it | `O(1)` |
| Insert | Set `T[x.key] = x` | `O(1)` |
| Delete | Set `T[x.key] = NIL` | `O(1)` |

Each operation involves a single array access — no traversal, no comparison against other elements.

---

## 5. Why Direct Addressing Can Be Fast

The speed of direct addressing comes from **avoiding search entirely**.

- In a structure like a linked list, finding an element means examining elements one by one until a match is found (or the list ends).
- In a direct-address table, the key itself tells you exactly which array position to access — there is no need to compare the key against anything else.

This is the same reason an ordinary array offers `O(1)` access time for any index: direct addressing simply extends that idea so that the array index *is* the key.

---

## 6. The Main Limitation

The major limitation of direct-address tables is that **the universe of possible keys can be far larger than the number of elements actually stored.**

**Example:**

Suppose the possible keys range over:

```
0 ... 1,000,000
```

but the set only actually stores:

```
10, 500, 900
```

To use direct addressing, you would need to allocate an array of size 1,000,001 — even though only 3 elements are ever stored. Almost the entire table would sit empty (`NIL`), wasting a huge amount of memory relative to what is actually needed.

If the universe `U` is very large — or its size is not known in advance — allocating a table of size `|U|` may be impractical, or even impossible given available memory.

This limitation is exactly what motivates the next topic: **Hash Tables**, which reduce the storage requirement toward the number of elements actually stored, rather than the size of the entire key universe.

---

## 7. Direct-Address Table vs Normal Array

A direct-address table is not a new data structure in a structural sense — it is a particular *way of using* an array, where the key itself determines the position of an element.

| Aspect | Normal Array | Direct-Address Table |
|---|---|---|
| Index meaning | Index is usually an arbitrary position (e.g., order of insertion) | Index is the key itself |
| Access pattern | May require searching to find a specific value | Element with key `k` is found directly at position `k` |
| Empty slots | Not a defined concept | Represented explicitly as `NIL` |
| Size requirement | Sized based on number of elements needed | Sized based on the entire key universe `|U|` |

The essential difference is conceptual: in a direct-address table, **the key determines where the data lives**, rather than the data being placed at an arbitrary position and searched for later.

---

## 8. Direct-Address Table vs Hash Table

Direct addressing and hashing are closely related, but differ in one key way:

- **Direct addressing** uses the key **directly** as the array index: element with key `k` goes into slot `k`.
- **Hash Tables** use a **hash function** to compute an index from the key, mapping a potentially large key universe into a much smaller table.

Direct addressing works well only when the key universe is small enough to allocate a full table for it. Hash Tables remove this restriction by computing a smaller index from the key, rather than using the key as the index itself.

The details of how hash functions compute this mapping, and how collisions between keys are handled, are covered in:

- [`02-Hash-Tables.md`](./02-Hash-Tables.md)
- [`03-Hash-Functions.md`](./03-Hash-Functions.md)

---

## 9. Problem-Solving Perspective

Direct addressing is not usually presented as a named "pattern" in coding interviews, but the underlying idea shows up constantly in a simplified form: **using a small integer key directly as an array index instead of using a hash table.**

The relevant thought process is:

> "If my keys are small integers from a manageable, known range, can I use the key directly as an index instead of using a `HashMap`?"

**Example:** If you need to track which digits `0–9` have appeared in a sequence of numbers, you can use a fixed array of size 10 and index it directly with the digit itself, rather than reaching for a hash-based structure.

This is essentially direct addressing applied at a small scale, and it is often faster and simpler than using a general-purpose hash table when the key range is small and known in advance.

---

## 10. Example in Python

The following is a simple, educational demonstration of direct addressing — **not** a production-ready implementation.

```python
# A direct-address table implemented as a Python list.
# The key universe is assumed to be {0, 1, ..., m-1}.

m = 10  # size of the table = size of the key universe
table = [None] * m  # None represents an empty slot (NIL)

def insert(table, key, value):
    # The key is used directly as the index.
    table[key] = value

def search(table, key):
    # Direct access using the key as the index.
    return table[key]

def delete(table, key):
    # Reset the slot to empty (NIL).
    table[key] = None

# --- Demonstration ---

insert(table, 2, "A")
insert(table, 5, "B")
insert(table, 8, "C")

print(search(table, 5))   # "B" - found directly at index 5
print(search(table, 3))   # None - slot is empty

delete(table, 5)
print(search(table, 5))   # None - element removed
```

Each operation touches exactly one array position, directly determined by the key — no searching or comparison is required.

---

## 11. Complexity

| Aspect | Complexity | Assumption |
|---|---|---|
| Search | `O(1)` | Key is a valid index within the table |
| Insert | `O(1)` | Key is a valid index within the table |
| Delete | `O(1)` | Key is a valid index within the table |
| Space | `O(|U|)` | Table must be sized to cover the entire key universe `U`, regardless of how many elements are actually stored |

The time complexity of all operations is constant, but this comes at the cost of space complexity being tied to the size of the key universe rather than the number of elements actually stored.

---

## 12. Key Takeaways

- A direct-address table stores an element with key `k` at index `k` in an array — the key **is** the index.
- Search, Insert, and Delete all run in `O(1)` time because each operation is a single array access.
- The main cost of this speed is space: the table must be as large as the entire key universe `|U|`, not just the number of stored elements.
- When the set of actual keys `K` is much smaller than the universe `U`, most of the table sits unused, wasting memory.
- Direct addressing is impractical (or impossible) when `|U|` is very large or unbounded.
- This limitation directly motivates Hash Tables, which reduce storage to be proportional to the number of stored elements rather than the size of the key universe.

---

## 13. Quick Revision

```
Direct-address table = An array where each key maps to exactly one index
Key                   = The value used directly as the array index
Index                 = The exact position in the array where the element is stored
Main advantage        = O(1) Search, Insert, and Delete
Main limitation       = Requires a table as large as the entire key universe |U|
Next topic            = Hash Tables
```

---

## 14. Questions to Test Understanding

1. Why is it called a Direct-address table?
2. How does a key determine the location of an element in the table?
3. Why can Direct-address tables waste memory?
4. When is Direct addressing practical to use?
5. How does this idea motivate the need for Hash Tables?

<details>
<summary>Answers</summary>

1. It is called "direct-address" because the key is used **directly** as the array index, with no transformation or computation between the key and its storage location.
2. The key value itself is the index — element with key `k` is stored at (or retrieved from) position `T[k]` in the array.
3. Because the table must be sized to cover the entire key universe `U`, even if only a small number of the possible keys are actually used, leaving most slots as unused `NIL` entries.
4. Direct addressing is practical when the universe of possible keys `U` is small enough that allocating an array of size `|U|` is feasible in memory.
5. Since direct addressing becomes impractical when `|U|` is very large relative to the number of stored elements, it motivates Hash Tables, which use a hash function to map a large key universe into a much smaller table, keeping storage proportional to the number of elements actually stored.

</details>

---

## 15. Navigation

Previous:
[Hashing & Hash Tables](README.md)

Next:
[Hash Tables](02-Hash-Tables.md)
