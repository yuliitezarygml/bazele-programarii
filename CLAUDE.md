# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ programming fundamentals repository ("bazele programarii" = programming basics in Romanian) containing lab exercises organized by topic. The code demonstrates fundamental data structures and algorithms concepts with extensive Romanian comments for educational purposes.

## Project Structure

- `bp2-lab1/` - Lab 1: Array manipulation and recursion exercises
- `bp2-lab2/` - Lab 2: Singly linked list implementations (student/employee records)
- `bp2-lab3/` - Lab 3: Dynamic data structures and game simulations
- `bp2-lab4/` - Lab 4: Binary Search Trees (BST) with comprehensive operations
- Each lab directory contains:
  - `.cpp` source files with exercise solutions
  - `.exe` compiled Windows executables (legacy)
  - `output/` subdirectories with additional executables
  - `.pdf` files with exercise descriptions (lab 2, 3, and 4)
  - `ОБЪЯСНЕНИЕ.md` files with detailed Russian explanations (lab 3 and 4)

## Build System

The project uses CMake with C++14 standard. Each exercise is built as a separate executable since they all contain their own `main()` functions.

### Building all exercises with CMake

```bash
# Configure and build all exercises
cmake -B build
cmake --build build

# Or using the existing cmake-build-debug directory
cd cmake-build-debug
cmake ..
make
```

This creates the following executables in the build directory:
- `bp2_lab1_ex16` - Array splitting (even/odd)
- `bp2_lab2_ex16` - Student list with min/max and sorting
- `bp2_lab2_ex17` - Student list with position search and name lookup
- `bp2_lab2_ex18` - Student list sorted by average grade
- `bp2_lab3_ex7` - Stack-based sorting algorithm
- `bp2_lab3_ex10` - Doubly linked list inventory management system
- `bp2_lab3_ex14` - "Red Goose" card game simulation
- `bp2_lab4_ex8` - BST with sum of all nodes
- `bp2_lab4_ex15` - BST with leaf node counting
- `bp2_lab4_ex20` - Complete BST management system

### Building specific exercises

```bash
# Build only one exercise
cmake --build build --target bp2_lab2_ex16
```

### Compiling individual exercises without CMake

Each exercise can be compiled independently with g++:

```bash
# General pattern
g++ -std=c++14 -o output_name "path/to/source.cpp"

# Examples
g++ -std=c++14 -o ex16 "bp2-lab1/Bp 2-Lab-1-ex-16.cpp"
g++ -std=c++14 -o ex16 bp2-lab2/Bp2-Lab2-ex16.cpp
g++ -std=c++14 -o ex14 bp2-lab3/Bp2-Lab3-ex14.cpp
```

Note: File paths contain spaces in lab1, so use quotes when compiling.

### Running exercises

```bash
# From build directory
./bp2_lab1_ex16
./bp2_lab2_ex16
./bp2_lab3_ex14

# Or if compiled manually
./ex16
./ex14
```

## Code Architecture

### Lab 1: Array Processing with Recursion
- **Pattern**: Read array → process with recursive function → display results
- **Key technique**: Tail recursion for array traversal and filtering
- **Example**: `Bp 2-Lab-1-ex-16.cpp` splits arrays into even/odd elements using recursion

### Lab 2: Singly Linked Lists
- **Pattern**: Manual linked list implementation with struct nodes
- **Common structure**:
  ```cpp
  struct nod {
      // Data fields (nume, medie, adresa, varsta, etc.)
      nod *urm;  // Pointer to next node
  };
  ```
- **Standard operations**:
  - `adauga_nod()` - Create first node
  - `adauga_ultim()` - Append to end
  - `afisare()` - Display all nodes
  - `sorteaza_descrescator()` - Bubble sort (descending)
  - Search and filter operations
- **Data models**: Student records (ex16, ex18), Employee records (ex17)

### Lab 3: Advanced Data Structures
Lab 3 demonstrates both procedural and object-oriented approaches:

**Procedural style (ex14)**: Queue-based game simulation
- **Pattern**: Queue implementation using linked lists for game/process simulation
- **Key operations**:
  - `adauga_sfarsit()` - Enqueue at tail
  - `scoate_primul()` - Dequeue from head
  - `muta_masa_la_pachet()` - Transfer entire queue
- **Example**: `Bp2-Lab3-ex14.cpp` implements "Red Goose" card game with two player queues and a table queue

**Object-oriented style (ex7, ex10)**: Modern C++ with classes
- **ex7**: Stack-based sorting using two stacks
  - Class-based `Stiva` (stack) implementation
  - Insertion sort algorithm using stack transfers
  - Maintains sorted order (descending from top)
- **ex10**: Doubly linked list inventory system
  - Class-based `Lista_articol` with sentinel nodes (`sant1`, `sant2`)
  - Encapsulated `Articol` class with getters/setters
  - CRUD operations: add (sorted by code), delete, search, modify
  - Stock management: `intrareStoc()` (receive), `iesireStoc()` (sell/consume)
  - Bidirectional traversal: `afisare()` forward, `afisareInversa()` backward
  - Auto-deletion when stock reaches zero

### Lab 4: Binary Search Trees (BST)
Lab 4 focuses on binary search tree implementations with comprehensive operations:

**Core BST properties:**
- Left subtree values < node value < right subtree values
- Average O(log n) search, insert, delete operations
- Inorder traversal produces sorted sequence

**Implemented exercises:**
- **ex8**: Sum of all nodes in BST
  - Recursive tree traversal
  - Accumulation of node values
- **ex10**: Leaf node counting
  - Identifies nodes without children
  - Counts internal vs leaf nodes
  - Calculates tree height
- **ex20**: Complete BST management system (comprehensive)
  - Insert, delete (3 cases: leaf, one child, two children), search
  - Multiple traversals: inorder, preorder, postorder, level-order
  - Tree statistics: height, node count, min/max values
  - Balance verification (height difference ≤ 1)
  - Interactive menu-driven interface

**Key BST operations:**
- **Insertion**: Recursive placement maintaining BST property
- **Deletion**: Three cases handled:
  1. Leaf node - simple removal
  2. One child - replace with child
  3. Two children - replace with inorder successor (min of right subtree)
- **Traversals**:
  - Inorder (left-root-right): sorted output
  - Preorder (root-left-right): tree structure copy
  - Postorder (left-right-root): tree deletion
  - Level-order (BFS): breadth-first using queue

## Language and Comments

All code contains extensive Romanian comments explaining logic line-by-line. Variable names and output messages are in Romanian:
- `nume` = name
- `medie` = average/grade
- `adresa` = address
- `varsta` = age
- `grupa` = group
- `nota` = grade/mark
- `prim` = first
- `ultim` = last
- `urm` = next (next pointer)
- `stiva` = stack
- `varf` = top (of stack)
- `sant1/sant2` = sentinel nodes (doubly linked list boundaries)
- `cod` = code/ID
- `stoc` = stock/inventory
- `pret` = price
- `articol` = article/item
- `arbore` = tree
- `nod` = node
- `radacina` = root
- `frunza` = leaf
- `inaltime` = height
- `echilibrat` = balanced

## Development Notes

- The codebase uses VLA (Variable Length Arrays) which is a GCC extension, not standard C++
- No external dependencies beyond standard library (`<iostream>`, `<string>`, `<climits>`)
- Code style: K&R bracing, descriptive function names, extensive inline comments
- All exercises are self-contained programs with `main()` functions - each must be built as a separate executable
- Input is interactive via `cin`, output via `cout`
- The CMakeLists.txt creates separate executables for each exercise to avoid multiple `main()` definition conflicts
- Lab 3 shows evolution from procedural (struct-based) to object-oriented (class-based) programming patterns
- Newer exercises (ex7, ex10) use modern C++ features: classes, encapsulation, constructors/destructors, operator overloading
