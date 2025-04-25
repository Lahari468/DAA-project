#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char code[50];
    char level[100];
    char des[100];
} bloom;

bloom b[MAX];
int c = 0;
const char* FILE_NAME = "bloom_setting.txt";

void titans_load_from_file();
void titans_bloom_storing();
void titans_bloom_create();
void titans_bloom_update();
void titans_bloom_retrieve();
void titans_bloom_delete();
void titans_quick_sort(int low, int high);
int titans_partition(int low, int high);
void titans_compare_sort_mergesort(int left, int right);
void titans_merge(int left, int mid, int right);
int titans_linear_search(int id);
int titans_compare_search_binarysearch(int id);
void titans_bloom_search();
void titans_complexity_searching();
void titans_complexity_sorting();

void titans_load_from_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("File not found or unable to open: %s\n", FILE_NAME);
        return;
    }
    c = 0;
    while (fscanf(file, "%d %49s %99s %99[^\n]", &b[c].id, b[c].code, b[c].level, b[c].des) == 4) {
        c++;
    }
    fclose(file);
}

void titans_bloom_storing() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", FILE_NAME);
        return;
    }
    for (int i = 0; i < c; i++) {
        fprintf(file, "%d %s %s %s\n", b[i].id, b[i].code, b[i].level, b[i].des);
    }
    fclose(file);
}

void titans_bloom_create() {
    if (c >= MAX) {
        printf("Bloom list is full!\n");
        return;
    }
    bloom bl;
    printf("Enter bloom ID: ");
    if (scanf("%d", &bl.id) != 1) {
        printf("Invalid input!\n");
        return;
    }
    printf("Enter bloom Code: ");
    scanf("%49s", bl.code);
    printf("Enter bloom Level: ");
    scanf(" %99[^\n]", bl.level);
    printf("Enter bloom Description: ");
    scanf(" %99[^\n]", bl.des);

    b[c++] = bl;
    titans_bloom_storing();
    printf("Bloom created successfully!\n");
}

void titans_bloom_update() {
    int id;
    printf("Enter bloom ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    for (int i = 0; i < c; i++) {
        if (b[i].id == id) {
            printf("Enter new bloom Code: ");
            scanf("%49s", b[i].code);
            printf("Enter new bloom Level: ");
            scanf(" %99[^\n]", b[i].level);
            printf("Enter new bloom Description: ");
            scanf(" %99[^\n]", b[i].des);

            titans_bloom_storing();
            printf("Bloom updated successfully!\n");
            return;
        }
    }
    printf("Bloom with ID %d not found.\n", id);
}

void titans_bloom_retrieve() {
    if (c == 0) {
        printf("No blooms available.\n");
        return;
    }
    printf("\nList of Blooms:\n");
    for (int i = 0; i < c; i++) {
        printf("ID: %d\nCode: %s\nLevel: %s\nDescription: %s\n\n",
               b[i].id, b[i].code, b[i].level, b[i].des);
    }
}

void titans_bloom_delete() {
    int id;
    printf("Enter bloom ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    for (int i = 0; i < c; i++) {
        if (b[i].id == id) {
            for (int j = i; j < c - 1; j++) {
                b[j] = b[j + 1];
            }
            c--;
            titans_bloom_storing();
            printf("Bloom deleted successfully!\n");
            return;
        }
    }
    printf("Bloom with ID %d not found.\n", id);
}

int titans_partition(int low, int high) {
    int pivot = b[high].id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (b[j].id < pivot) {
            i++;
            bloom temp = b[i];
            b[i] = b[j];
            b[j] = temp;
        }
    }
    bloom temp = b[i + 1];
    b[i + 1] = b[high];
    b[high] = temp;
    return i + 1;
}

void titans_quick_sort(int low, int high) {
    if (low < high) {
        int pivot = titans_partition(low, high);
        titans_quick_sort(low, pivot - 1);
        titans_quick_sort(pivot + 1, high);
    }
}

void titans_merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    bloom L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = b[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = b[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            b[k] = L[i];
            i++;
        } else {
            b[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        b[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        b[k] = R[j];
        j++;
        k++;
    }
}

void titans_compare_sort_mergesort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        titans_compare_sort_mergesort(left, mid);
        titans_compare_sort_mergesort(mid + 1, right);
        titans_merge(left, mid, right);
    }
}

int titans_linear_search(int id) {
    for (int i = 0; i < c; i++) {
        if (b[i].id == id) {
            return i;
        }
    }
    return -1;
}

int titans_compare_search_binarysearch(int id) {
    titans_compare_sort_mergesort(0, c - 1);
    int left = 0;
    int right = c - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (b[mid].id == id) {
            return mid;
        } else if (b[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
void titans_complexity_searching() 
{

  
        printf("Linear Search: time complexity is O(n).\n");
   
        printf("Binary Search: time complexity is O(log n).\n");
    
}

void titans_complexity_sorting() 
{
        printf("Quick Sort: time complexity is O(n^2) for worst case[when last element is chosen as pivot as the elements are already in sorted order] and O(n log n) for the average case.\n");
   
        printf("Merge Sort: time complexity is O(n log n).\n");
   
}

int main() {
    titans_load_from_file();

    int choice;
    while (1) {
        printf("\n1. Create Bloom\n2. Update Bloom\n3. Retrieve Blooms\n4. Delete Bloom\n5. Search by ID (Binary Search)\n6. Sort by ID (Merge Sort)\n7. Sort by ID (Quick Sort)\n8. Search by ID (Linear Search)\n9. Complexity of Searching\n10. Complexity of Sorting\n11. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                titans_bloom_create();
                break;
            case 2:
                titans_bloom_update();
                break;
            case 3:
                titans_bloom_retrieve();
                break;
            case 4:
                titans_bloom_delete();
                break;
            case 5: {
                int id;
                printf("Enter bloom ID to search using Binary Search: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input!\n");
                    break;
                }
                int index = titans_compare_search_binarysearch(id);
                if (index != -1) {
                    printf("Bloom found using Binary Search:\nID: %d\nCode: %s\nLevel: %s\nDescription: %s\n",
                           b[index].id, b[index].code, b[index].level, b[index].des);
                } else {
                    printf("Bloom with ID %d not found using Binary Search.\n", id);
                }
                break;
            }
            case 6:
                titans_compare_sort_mergesort(0, c - 1);
                printf("Merge Sort by ID complete. Displaying results:\n");
                titans_bloom_retrieve();
                break;
            case 7:
                titans_quick_sort(0, c - 1);
                printf("Quick Sort by ID complete. Displaying results:\n");
                titans_bloom_retrieve();
                break;
            case 8: {
                int id;
                printf("Enter bloom ID to search using Linear Search: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input!\n");
                    break;
                }
                int index = titans_linear_search(id);
                if (index != -1) {
                    printf("Bloom found using Linear Search:\nID: %d\nCode: %s\nLevel: %s\nDescription: %s\n",
                           b[index].id, b[index].code, b[index].level, b[index].des);
                } else {
                    printf("Bloom with ID %d not found using Linear Search.\n", id);
                }
                break;
            }
            case 9:
                titans_complexity_searching();
                break;
            case 10:
                titans_complexity_sorting();
                break;
            case 11:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
