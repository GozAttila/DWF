# Part 1: Data Structures and Algorithms

Instead of using a local file, I chose to download the data directly in the code for reusability across different files or sites. I assumed the downloaded data was text, so I stored it in a string and created a stream from it, allowing me to loop through it word by word. I used the `insert()` function for each word, assigning the current word count as the value and using the word itself as the key (as requested).

I used the MurmurHash3 function to populate the hash table because of its speed and suitability for medium to high data loads. I consider this file to be of medium size.

### The parts of the hash table:
- A vector to store key-value pairs (word - count).
- A boolean vector to track whether each index is occupied (for reusability after `remove()`).
- A doubly linked list for O(1) `get_last()` and `get_first()` operations.

### Functions:
- `insert()`, `remove()`, `get()`
  These functions operate with O(1) complexity in the absence of collisions, but in the worst case (if the hash table is too small), complexity can increase to O(N) due to linear probing. A properly sized hash table is necessary for optimal performance. The logic is similar for all three functions: calculate the index, and try to insert, remove, or get the value at that index. If the keys do not match, the index is incremented and the process is repeated. 
  - In `remove()` and `get()`, once the correct key is found, the value is either returned (`get()`) or the entry is removed (`remove()`).
  - If `get()` finds no match, it returns -1.
  - In `insert()`, the key is first checked for a match; if it matches, the value is updated. If not, it moves to the next index. Both `remove()` and `insert()` also update the doubly linked list.

- `get_last()`, `get_first()`
  These functions retrieve the tail or head value of the doubly linked list.

### Table size checks:
- Table size: 10007 -> Infinite loop, insufficient table size.
- Table size: 11003 -> Works with many collisions, occasional infinite loop error.
- Table size: 12007 -> Works with many collisions, no infinite loop errors.
- Table size: 13001 -> Works with many collisions, no errors; collisions/table size = 35%.
- Table size: 14009 -> Works with many collisions, no errors; collisions/table size = 31%.
- Table size: 15013 -> Works with many collisions, no errors; collisions/table size = 27%.
- Table size: 16001 -> Works with many collisions, no errors; collisions/table size = 24%.
- Table size: 20011 -> Works with many collisions, no errors; collisions/table size = 15%.

Currently, the table size is set to 20011, as I am unsure of the precise requirement for it.

### Counters:
The counters are still functioning, though they are not essential for normal operation. They are included for demonstration purposes. Additionally, there is a test for `get_first()` and `get_last()`, which is also for presentation purposes.

The table size is defined as a constant. It should be in the private block, but for presentation purposes, it is currently in the public block.
