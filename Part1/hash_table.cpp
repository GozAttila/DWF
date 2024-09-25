#include "hash_table.hpp"
#include "murmur_hash.hpp"
#include <cctype>
#include <algorithm>
//debug
#include <iostream>

Node::Node(std::string k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}

FixedHashTable::FixedHashTable() : table(TABLE_SIZE, {"", -1}), occupied(TABLE_SIZE, false), head(nullptr), tail(nullptr) {}

std::string FixedHashTable::clean_word(const std::string& word) {
    std::string clean;
    for (char c : word) {
        if (std::isalnum(c) || c == '\'') {
            clean += std::tolower(c);
        }
    }
    return clean;
}

std::pair<std::string, unsigned int> FixedHashTable::get_ckey_index(const std::string& key) {
    std::string cleaned_key = clean_word(key);
    uint32_t hash_value = murmur_hash3(cleaned_key.c_str(), cleaned_key.size(), 0);
    unsigned int index = hash_value % TABLE_SIZE;
    return std::make_pair(cleaned_key, index);
}

void FixedHashTable::insert(const std::string& key, int value) {
    auto [cleaned_key, index] = get_ckey_index(key);

    // Counters for testing and optimalization
    insert_counter++;
    bool has_collided = false;
    unsigned int steps = 0;

    while (occupied[index]) {
        if (table[index].first == cleaned_key) {
            table[index].second = value;

            Node* existingNode = node_map[cleaned_key];

            if (existingNode->prev) {
                existingNode->prev->next = existingNode->next;
            }
            if (existingNode->next) {
                existingNode->next->prev = existingNode->prev;
            }
            if (existingNode == head) {
                head = existingNode->next;
            }
            if (existingNode == tail) {
                tail = existingNode->prev;
            }

            existingNode->next = nullptr;
            existingNode->prev = tail;

            if (tail) {
                tail->next = existingNode;
            }
            tail = existingNode;

            if (!head) {
                head = existingNode;
            }

            return;
        }

        index = (index + 1) % TABLE_SIZE;
        
        // Counters for testing and optimalization
        steps++;
        has_collided = true;
        
        if (steps >= TABLE_SIZE) {
            std::cerr << "Probably infinite cycle..." << std::endl;
            return;
        }        
    }

    occupied[index] = true;
    table[index] = { cleaned_key, value };

    Node* newNode = new Node(cleaned_key, value);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    node_map[cleaned_key] = newNode;

    // Counters for testing and optimalization
    if (has_collided) {
        index_occupied_counter++;
    }
    index_occupied_extra_steps_counter += steps;
}

void FixedHashTable::remove(const std::string& key) {
    auto [cleaned_key, index] = get_ckey_index(key);

    while (occupied[index]) {
        if (table[index].first == cleaned_key) {            
            occupied[index] = false;
            table[index] = {"", -1};
            
            Node* node_to_remove = node_map[cleaned_key];

            if (node_to_remove->prev) {
                node_to_remove->prev->next = node_to_remove->next;
            }
            if (node_to_remove->next) {
                node_to_remove->next->prev = node_to_remove->prev;
            }
            if (node_to_remove == head) {
                head = node_to_remove->next;
            }
            if (node_to_remove == tail) {
                tail = node_to_remove->prev;
            }

            delete node_to_remove;
            node_map.erase(cleaned_key);

            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
}

int FixedHashTable::get(const std::string& key) {
    auto [cleaned_key, index] = get_ckey_index(key);

    while (occupied[index]) {
        if (table[index].first == cleaned_key) {
            return table[index].second;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    return -1;
}

std::pair<std::string, int> FixedHashTable::get_last() {
    return tail ? std::make_pair(tail->key, tail->value) : std::make_pair("", -1);
}

std::pair<std::string, int> FixedHashTable::get_first() {
    return head ? std::make_pair(head->key, head->value) : std::make_pair("", -1);
}