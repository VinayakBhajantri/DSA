#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char* key;
    int value;
    bool isOccupied;
} Entry;

typedef struct HashTable {
    Entry* table;
    int size;
} HashTable;

int hash1(const char* key, int size) {
    int hash = 0;
    int len = strlen(key);

    for (int i = 0; i < len; i++) {
        hash = (31 * hash + key[i]) % size;
    }

    return hash;
}

int hash2(const char* key, int size) {
    int hash = 0;
    int len = strlen(key);

    for (int i = 0; i < len; i++) {
        hash = (37 * hash + key[i]) % size;
    }

    return (hash % (size - 1)) + 1;
}

void initHashTable(HashTable* ht, int size) {
    ht->table = (Entry*)malloc(size * sizeof(Entry));
    ht->size = size;

    for (int i = 0; i < size; i++) {
        ht->table[i].key = NULL;
        ht->table[i].isOccupied = false;
    }
}

void insert(HashTable* ht, const char* key, int value) {
    int hashVal = hash1(key, ht->size);
    int stepSize = hash2(key, ht->size);
    int i = 0;

    while (ht->table[hashVal].isOccupied) {
        if (strcmp(ht->table[hashVal].key, key) == 0) {
            // Update existing key's value
            ht->table[hashVal].value = value;
            return;
        }

        i++;
        hashVal = (hashVal + (i * stepSize)) % ht->size;
    }

    // Insert new key-value pair
    ht->table[hashVal].key = strdup(key);
    ht->table[hashVal].value = value;
    ht->table[hashVal].isOccupied = true;
}

int search(HashTable* ht, const char* key) {
    int hashVal = hash1(key, ht->size);
    int stepSize = hash2(key, ht->size);
    int i = 0;

    while (ht->table[hashVal].isOccupied) {
        if (strcmp(ht->table[hashVal].key, key) == 0) {
            return ht->table[hashVal].value;
        }

        i++;
        hashVal = (hashVal + (i * stepSize)) % ht->size;
    }

    // Key not found
    return -1;
}

void deleteKey(HashTable* ht, const char* key) {
    int hashVal = hash1(key, ht->size);
    int stepSize = hash2(key, ht->size);
    int i = 0;

    while (ht->table[hashVal].isOccupied) {
        if (strcmp(ht->table[hashVal].key, key) == 0) {
            ht->table[hashVal].key = NULL;
            ht->table[hashVal].isOccupied = false;
            return;
        }

        i++;
        hashVal = (hashVal + (i * stepSize)) % ht->size;
    }
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i].isOccupied) {
            printf("Key: %s, Value: %d\n", ht->table[i].key, ht->table[i].value);
        }
    }
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i].isOccupied) {
            free(ht->table[i].key);
        }
    }
    free(ht->table);
}

int main() {
    HashTable ht;
    initHashTable(&ht, TABLE_SIZE);

    insert(&ht, "apple", 10);
    insert(&ht, "banana", 20);
    insert(&ht, "orange", 30);

    printf("Search 'apple': %d\n", search(&ht, "apple"));
    printf("Search 'banana': %d\n", search(&ht, "banana"));
    printf("Search 'orange': %d\n", search(&ht, "orange"));
    printf("Search 'grape': %d\n", search(&ht, "grape"));

    deleteKey(&ht, "banana");

    printf("\nAfter deleting 'banana':\n");
    printHashTable(&ht);

    freeHashTable(&ht);
}


