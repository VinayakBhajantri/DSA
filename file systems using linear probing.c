#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILES 10
#define FILE_NAME_SIZE 20

typedef struct File {
    char name[FILE_NAME_SIZE];
    int size;
    bool isOccupied;
} File;

typedef struct FileSystem {
    File files[MAX_FILES];
} FileSystem;

void initFileSystem(FileSystem* fs) {
    for (int i = 0; i < MAX_FILES; i++) {
        fs->files[i].isOccupied = false;
    }
}

int findNextAvailableIndex(FileSystem* fs, int start) {
    for (int i = start; i < MAX_FILES; i++) {
        if (!fs->files[i].isOccupied) {
            return i;
        }
    }

    for (int i = 0; i < start; i++) {
        if (!fs->files[i].isOccupied) {
            return i;
        }
    }

    return -1; // No available index
}

bool createFile(FileSystem* fs, const char* name, int size) {
    if (size <= 0) {
        return false;
    }

    int index = findNextAvailableIndex(fs, 0);
    if (index == -1) {
        printf("File system is full. Cannot create file.\n");
        return false;
    }

    strncpy(fs->files[index].name, name, FILE_NAME_SIZE);
    fs->files[index].size = size;
    fs->files[index].isOccupied = true;

    printf("File created: %s\n", name);

    return true;
}

bool deleteFile(FileSystem* fs, const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->files[i].isOccupied && strcmp(fs->files[i].name, name) == 0) {
            fs->files[i].isOccupied = false;
            printf("File deleted: %s\n", name);
            return true;
        }
    }

    printf("File not found: %s\n", name);
    return false;
}

void printFileSystem(FileSystem* fs) {
    printf("File System Contents:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->files[i].isOccupied) {
            printf("File: %s, Size: %d\n", fs->files[i].name, fs->files[i].size);
        }
    }
}

int main() {
    FileSystem fs;
    initFileSystem(&fs);

    createFile(&fs, "file1.txt", 100);
    createFile(&fs, "file2.txt", 200);
    createFile(&fs, "file3.txt", 150);

    printFileSystem(&fs);

    deleteFile(&fs, "file2.txt");
    deleteFile(&fs, "file4.txt");

    printFileSystem(&fs);

    return 0;
}

