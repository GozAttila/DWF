#include <iostream>
#include <sstream>
#include "hash_table.hpp"
#include "utils.hpp"

const std::string URL = "https://www.gutenberg.org/files/98/98-0.txt";

int main() {

    std::cout << "Running...\n";

    FixedHashTable hashTable;
    
    std::string download_text = download_url(URL);
    
    if (download_text.empty()) {
        std::cerr << "Download error!" << std::endl;
        return 1;
    }

    std::istringstream iss(download_text);
    std::string word;
    int word_count = 0;

    while (iss >> word) {
        hashTable.insert(word, ++word_count);

        if (iss.eof()) {
            std::cout << "EOF" << std::endl;
            break;
        }

        if (iss.fail()) {
            std::cerr << "File reading error!" << std::endl;
            break;
        }
    }

    std::cout << "After a while...\n";
    
    // Counters for testing and optimalization
    std::cout << "Hash table size: " << FixedHashTable::TABLE_SIZE << std::endl;
    std::cout << "Number of words: " << word_count << "\n";
    std::cout << "Number of insert() calls: " << hashTable.get_insert_count() << "\n"; //must be the same as word_count
    std::cout << "Number of index collisions: " << hashTable.get_index_occupied_count() << "\n";
    std::cout << "Number of extra steps in insert() with insert: " << hashTable.get_index_occupied_extra_steps() << "\n";

    // Tests
    std::cout << "First inserted: " << hashTable.get_first().first << "\n";
    std::cout << "Last inserted: " << hashTable.get_last().first << "\n";
    
    std::cout << "Press a key to close the window..." << std::endl;
    std::cin.get();

    return 0;
}