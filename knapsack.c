#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

typedef struct {
    int value;
    int weight;
} item;

int num_items;
item items[MAX_ITEMS];
int capacity;
int best_value;
int curr_value;
int curr_weight;

void knapsack(int level) {
    if(level == num_items) {
        if(curr_value > best_value) {
            best_value = curr_value;
        }
        return;
    }

    if(curr_weight + items[level].weight <= capacity) {
        curr_weight += items[level].weight;
        curr_value += items[level].value;
        knapsack(level + 1);
        curr_weight -= items[level].weight;
        curr_value -= items[level].value;
    }

    int upper_bound = curr_value;
    for(int i = level + 1; i < num_items; i++) {
        if(curr_weight + items[i].weight > capacity) {
            break;
        }
        upper_bound += items[i].value;
    }
    if(upper_bound <= best_value) {
        return;
    }

    knapsack(level + 1);
}

int main() {
    printf("Enter the number of items: ");
    scanf("%d", &num_items);

    for(int i = 0; i < num_items; i++) {
        printf("Enter the value and weight of item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    best_value = 0;
    curr_value = 0;
    curr_weight = 0;

    knapsack(0);

    printf("The optimal value is %d.\n", best_value);

    return 0;
}
