# ALGODAT Coding assignment 2 - Treecheck

### Language

Options:
 - Python: easy language, both familiar, but not sure how linked lists work
 - C: already familiar, even with linked lists from 1st semester, complex/limited
 - C++: more functionalities/STL/etc., currently learning, but not quite familiar with linked lists yet

### Functions / Tasks

1. Basic IO for reading file
2. Creating tree from file
3. Checking balance
4. Search tree for single key
5. Search tree for subtree

### Effort estimates

| Task | Expected | Actual |
|------|----------|--------|
|  01  |  1:00 h  | 1:10 h |
|  02  |  1:30 h  |    0   |
|  03  |  1:00 h  | 1:05 h |
|  04  |  0:30 h  | 1:00 h |
|  05  |  0:30 h  | 0:50 h |

1h extra to revert unnecessary code

### Runtime analysis

Basic search is just binary search
O(n) = log n

Searching a subtree
O(n) = k log n

k is the amount of keys in the subtree

Inserting in tree - binary search
O(n) = log n

Creating a tree
O(n) = (log n)^2 ≈ n