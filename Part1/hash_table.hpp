#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Node {
    std::string key;
    int value;
    Node* prev;
    Node* next;
    Node(std::string k, int v);
};

class FixedHashTable {
private:
    std::vector<std::pair<std::string, int>> table;
    std::vector<bool> occupied;
    Node* head;
    Node* tail;
    std::unordered_map<std::string, Node*> node_map;

    std::string clean_word(const std::string& word);
    std::pair<std::string, unsigned int> get_ckey_index(const std::string& key);

    // commented for debug/presentation
    // static constexpr unsigned int TABLE_SIZE = 20011;

    // Counters for testing and optimalization
    unsigned int insert_counter = 0;
    unsigned int index_occupied_counter = 0;
    unsigned int index_occupied_extra_steps_counter = 0;

public:
    FixedHashTable();
    void insert(const std::string& key, int value);
    void remove(const std::string& key);
    int get(const std::string& key);
    std::pair<std::string, int> get_last();
    std::pair<std::string, int> get_first();
    // for debug/presentation, delete it and uncomment the above one when not needed anymore
    static constexpr unsigned int TABLE_SIZE = 20011;

    // Counters for testing and optimalization
    unsigned int get_insert_count() const { return insert_counter; }
    unsigned int get_index_occupied_count() const { return index_occupied_counter; }
    unsigned int get_index_occupied_extra_steps() const { return index_occupied_extra_steps_counter; }
};