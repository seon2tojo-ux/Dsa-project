# Package Sorting: Merge Sort vs Quick Sort

## Problem

A logistics company receives the following package weights:

`20, 15, 20, 10, 15, 20, 25, 10`

Each package has a unique ID.

| Original Position | Package ID | Weight |
|---:|---|---:|
| 1 | P1 | 20 |
| 2 | P2 | 15 |
| 3 | P3 | 20 |
| 4 | P4 | 10 |
| 5 | P5 | 15 |
| 6 | P6 | 20 |
| 7 | P7 | 25 |
| 8 | P8 | 10 |

The project implements **Merge Sort** and **Quick Sort**, records important intermediate steps, checks stability using package IDs, and compares the two algorithms.

## Files

```text
package-sorting/
├── main.c
├── README.md
├── sample_input.txt
├── sample_output.txt
├── intermediate_steps.txt
├── Makefile
└── .gitignore
```

## How to compile and run

### Linux / macOS

```bash
gcc -Wall -Wextra -std=c11 main.c -o package_sort
./package_sort
```

### Windows (MinGW)

```bash
gcc -Wall -Wextra -std=c11 main.c -o package_sort.exe
package_sort.exe
```

Or use:

```bash
make
./package_sort
```

## Sample input

```text
8
20 P1
15 P2
20 P3
10 P4
15 P5
20 P6
25 P7
10 P8
```

## Stable sorting

A sorting algorithm is **stable** when equal values keep their original relative order.

Original equal-weight groups:

- Weight 10: `P4 -> P8`
- Weight 15: `P2 -> P5`
- Weight 20: `P1 -> P3 -> P6`

The stable sorted result is:

```text
(P4,10) (P8,10) (P2,15) (P5,15) (P1,20) (P3,20) (P6,20) (P7,25)
```

The Merge Sort implementation in `main.c` uses:

```c
if (a[i].weight <= a[j].weight)
```

When two weights are equal, the item from the left half is selected first. Therefore, this implementation is stable.

The ordinary in-place Quick Sort implementation does **not guarantee stability**. It can move equal-weight packages across each other during partitioning.

## Important intermediate steps

### Merge Sort

The main merge stages for the given input are:

```text
Initial:
20 15 20 10 15 20 25 10

Split:
[20 15 20 10] [15 20 25 10]
[20 15] [20 10] [15 20] [25 10]

Sorted small groups:
[15 20] [10 20] [15 20] [10 25]

Merge:
[10 15 20 20] [10 15 20 25]

Final:
[10 10 15 15 20 20 20 25]
```

With IDs preserved:

```text
(P4,10) (P8,10) (P2,15) (P5,15)
(P1,20) (P3,20) (P6,20) (P7,25)
```

### Quick Sort

This implementation uses the **last element as the pivot**.

For the original input, the first partition uses:

```text
Pivot = P8(10)
```

The program prints every partition, so the exact intermediate sequence can be observed by running the program.

Important point: Quick Sort's intermediate arrangement depends on the partition scheme and pivot choice. Different valid Quick Sort implementations can produce different intermediate steps.

## Comparison

| Feature | Merge Sort | Quick Sort |
|---|---|---|
| Duplicate values | Handles duplicates correctly | Handles duplicates correctly |
| Stability | **Stable in this implementation** | **Not stable in this implementation** |
| Best/Average time | O(n log n) | O(n log n) average |
| Worst-case time | O(n log n) | O(n²) |
| Extra space | O(n) | O(log n) average recursion stack; O(n) worst-case stack |
| Main idea | Divide, sort halves, merge | Partition around a pivot |
| Original order of equal weights | Preserved | Not guaranteed |

## Number of comparisons

The program counts element comparisons performed by each implementation.

For the given input, the exact count printed by the program depends on the precise implementation in `main.c`. This is useful because comparison counts can differ between valid implementations of the same sorting algorithm.

For theoretical analysis:

- Merge Sort performs O(n log n) comparisons.
- Quick Sort performs O(n log n) comparisons on average.
- Quick Sort can perform O(n²) comparisons in the worst case.

## Analysis of duplicate values

Both algorithms can sort duplicate weights such as:

```text
10, 10
15, 15
20, 20, 20
```

The important difference is **what happens to their package IDs**.

Example:

```text
Before:
P1(20), P3(20), P6(20)
```

A stable sort must produce:

```text
P1(20), P3(20), P6(20)
```

The IDs must remain in the same relative order.

## Conclusion

When maintaining the original order of equal-weight packages is important, a **stable Merge Sort implementation** is appropriate because it guarantees stability while keeping O(n log n) time complexity.

This does not mean Quick Sort cannot be adapted to be stable. A stable Quick Sort can be designed, but the ordinary in-place Quick Sort used in this project does not provide that guarantee.

## Learning objectives

After completing this project, you should be able to:

1. Implement Merge Sort in C.
2. Implement Quick Sort in C.
3. Trace important intermediate sorting steps.
4. Understand duplicate values.
5. Understand sorting stability.
6. Count comparisons.
7. Compare time and space complexity.
8. Verify stability using package IDs.
