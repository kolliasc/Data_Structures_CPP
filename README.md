# Data Structures Project

A C++ implementation of four fundamental data structures, driven by a command file interface. Each structure supports build-from-file, insert, search, delete, and size queries.

## Data Structures Implemented

- **MinHeap** — Binary min-heap backed by a dynamic array. Supports insert, find-min, delete-min, and dynamic resizing.
- **MaxHeap** — Binary max-heap backed by a dynamic array. Supports insert, find-max, delete-max, and dynamic resizing.
- **AVL Tree** — Self-balancing binary search tree. Supports insert, search, delete, and find-min with automatic rebalancing via left/right rotations.
- **Hash Table** — Chained hash table (separate chaining with linked lists) using a modulo hash function. Supports insert and search.

## Project Structure

```
.
├── main.cpp          # Entry point — reads commands.txt, writes output.txt
├── MinHeap.h / .cpp
├── MaxHeap.h / .cpp
├── AVLTree.h / .cpp
├── HashTable.h / .cpp
├── Makefile
├── input.txt         # Sample input data (integers, one per line)
└── commands.txt      # Command file (see usage below)
```

## Building

Requires `clang++` (or change `CXX` in the Makefile to `g++`).

```bash
make
```

To build with no optimizations for debugging:

```bash
make main-debug
```

To clean compiled binaries:

```bash
make clean
```

## Usage

1. Populate `input.txt` with integers (one per line).
2. Write commands in `commands.txt` (see format below).
3. Run the program:

```bash
./main
```

Results are written to `output.txt`. After each command, the current state of all four structures is printed along with the execution time.

## Command Format

| Command | Description |
|---|---|
| `BUILD <STRUCTURE> <file>` | Build the structure from a file of integers |
| `INSERT <STRUCTURE> <n>` | Insert integer `n` |
| `FINDMIN <STRUCTURE>` | Print the minimum element (MinHeap or AVLTree) |
| `FINDMAX MAXHEAP` | Print the maximum element |
| `SEARCH <STRUCTURE> <n>` | Search for integer `n` (AVLTree or HashTable) |
| `DELETE <STRUCTURE> <n>` | Delete min (MinHeap), max (MaxHeap), or key `n` (AVLTree) |
| `GETSIZE <STRUCTURE>` | Print the number of elements |

Valid structure names: `MINHEAP`, `MAXHEAP`, `AVLTREE`, `HASHTABLE`

### Example `commands.txt`

```
BUILD MINHEAP input.txt
BUILD AVLTREE input.txt
INSERT MINHEAP 42
FINDMIN MINHEAP
SEARCH AVLTREE 10
GETSIZE AVLTREE
DELETE AVLTREE 10
```

## Notes

- The HashTable has a fixed capacity of 10 and uses chaining — no resizing is performed.
- Inserting a duplicate key into the AVL Tree is a no-op (duplicates are silently ignored).
- The `DELETE` command for `MINHEAP` and `MAXHEAP` ignores the number argument and always removes the root (min or max).
