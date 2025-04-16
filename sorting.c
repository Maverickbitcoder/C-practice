#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 100
#define DELAY 150000
#define MIN_MERGE 32

// Utility functions
void clearScreen() {
    printf("\033[2J\033[1;1H");
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    usleep(DELAY);
}

void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

// Sorting Algorithms
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                clearScreen(); printArray(arr, n);
            }
}
// Gnome Sort
void gnomeSort(int arr[], int n) {
    int pos = 0;
    while (pos < n) {
        if (pos == 0 || arr[pos] >= arr[pos-1]) {
            pos++;
        } else {
            swap(&arr[pos], &arr[pos-1]);
            pos--;
            clearScreen(); printArray(arr, n);
        }
    }
}

// Cycle Sort
void cycleSort(int arr[], int n) {
    for (int start = 0; start < n-1; start++) {
        int item = arr[start];
        int pos = start;
        
        for (int i = start+1; i < n; i++)
            if (arr[i] < item) pos++;
        
        if (pos == start) continue;
        
        while (item == arr[pos]) pos++;
        swap(&item, &arr[pos]);
        clearScreen(); printArray(arr, n);
        
        while (pos != start) {
            pos = start;
            for (int i = start+1; i < n; i++)
                if (arr[i] < item) pos++;
            
            while (item == arr[pos]) pos++;
            swap(&item, &arr[pos]);
            clearScreen(); printArray(arr, n);
        }
    }
}

// Cocktail Shaker Sort
void cocktailShakerSort(int arr[], int n) {
    bool swapped = true;
    int start = 0, end = n-1;
    
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i+1]) {
                swap(&arr[i], &arr[i+1]);
                swapped = true;
                clearScreen(); printArray(arr, n);
            }
        }
        
        if (!swapped) break;
        end--;
        
        swapped = false;
        for (int i = end-1; i >= start; i--) {
            if (arr[i] > arr[i+1]) {
                swap(&arr[i], &arr[i+1]);
                swapped = true;
                clearScreen(); printArray(arr, n);
            }
        }
        start++;
    }
}

// Pancake Sort utilities
void flip(int arr[], int i, int n) {
    int start = 0;
    while (start < i) {
        swap(&arr[start], &arr[i]);
        start++;
        i--;
    }
    clearScreen(); printArray(arr, n);
}

void pancakeSort(int arr[], int n) {
    for (int curr_size = n; curr_size > 1; curr_size--) {
        int mi = 0;
        for (int i = 0; i < curr_size; i++)
            if (arr[i] > arr[mi]) mi = i;
        
        if (mi != curr_size-1) {
            flip(arr, mi, n);
            flip(arr, curr_size-1, n);
        }
    }
}

// Bogo Sort utilities
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        if (arr[i] > arr[i+1]) return false;
    return true;
}

void shuffle(int arr[], int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

void bogoSort(int arr[], int n) {
    srand(time(NULL));
    while (!isSorted(arr, n)) {
        shuffle(arr, n);
        clearScreen(); printArray(arr, n);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
            clearScreen(); printArray(arr, n);
        }
        arr[j+1] = key;
        clearScreen(); printArray(arr, n);
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min]) min = j;
        if (min != i) {
            swap(&arr[i], &arr[min]);
            clearScreen(); printArray(arr, n);
        }
    }
}

void merge(int arr[], int l, int m, int r, int size) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    clearScreen(); printArray(arr, size);
}

void mergeSort(int arr[], int l, int r, int size) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m, size);
        mergeSort(arr, m+1, r, size);
        merge(arr, l, m, r, size);
    }
}

int partition(int arr[], int low, int high, int size) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot) {
            swap(&arr[++i], &arr[j]);
            clearScreen(); printArray(arr, size);
        }
    swap(&arr[i+1], &arr[high]);
    clearScreen(); printArray(arr, size);
    return i+1;
}

void quickSort(int arr[], int low, int high, int size) {
    if (low < high) {
        int pi = partition(arr, low, high, size);
        quickSort(arr, low, pi - 1, size);
        quickSort(arr, pi + 1, high, size);
    }
}

void countingSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    
    int count[max+1];
    for (int i = 0; i <= max; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i]]++;
    
    int idx = 0;
    for (int i = 0; i <= max; i++)
        while (count[i]--) {
            arr[idx++] = i;
            clearScreen(); printArray(arr, n);
        }
}

void heapify(int arr[], int n, int i) {
    int largest = i, left = 2*i+1, right = 2*i+2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        clearScreen(); printArray(arr, n);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        clearScreen(); printArray(arr, n);
        heapify(arr, i, 0);
    }
}

void countingSortForRadix(int arr[], int n, int exp) {
    int output[n], count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        clearScreen(); printArray(arr, n);
    }
}

void radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    
    for (int exp = 1; max/exp > 0; exp *= 10)
        countingSortForRadix(arr, n, exp);
}

void bucketSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    
    int buckets = 10;
    int *b[buckets], sizes[buckets];
    for (int i = 0; i < buckets; i++) {
        b[i] = malloc(n * sizeof(int));
        sizes[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * buckets) / (max + 1);
        b[idx][sizes[idx]++] = arr[i];
    }
    
    int index = 0;
    for (int i = 0; i < buckets; i++) {
        insertionSort(b[i], sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            arr[index++] = b[i][j];
            clearScreen(); printArray(arr, n);
        }
        free(b[i]);
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
                clearScreen(); printArray(arr, n);
            }
            arr[j] = temp;
            clearScreen(); printArray(arr, n);
        }
    }
}

void insertionSortTim(int arr[], int left, int right) {
    for (int i = left+1; i <= right; i++) {
        int key = arr[i], j = i-1;
        while (j >= left && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
            clearScreen(); printArray(arr, right+1);
        }
        arr[j+1] = key;
        clearScreen(); printArray(arr, right+1);
    }
}

void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += MIN_MERGE)
        insertionSortTim(arr, i, (i+MIN_MERGE-1 < n-1) ? i+MIN_MERGE-1 : n-1);
    
    for (int size = MIN_MERGE; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2*size) {
            int mid = left + size - 1;
            int right = (left + 2*size - 1 < n-1) ? left + 2*size -1 : n-1;
            if (mid < right) merge(arr, left, mid, right, n);
        }
    }
}

void combSort(int arr[], int n) {
    int gap = n;
    bool swapped = true;
    
    while (gap > 1 || swapped) {
        gap = (gap*10)/13;
        if (gap < 1) gap = 1;
        
        swapped = false;
        for (int i = 0; i < n-gap; i++) {
            if (arr[i] > arr[i+gap]) {
                swap(&arr[i], &arr[i+gap]);
                swapped = true;
                clearScreen(); printArray(arr, n);
            }
        }
    }
}

void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) to[i] = from[i];
}

int main() {
    int n, arr[MAX], original[MAX], choice;
    
    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX) {
        printf("Invalid number of elements.\n");
        return 1;
    }
    
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &original[i]);
    
    do {
        copyArray(original, arr, n);
        printf("\nChoose Sorting Algorithm:\n");
        printf(" 1. Bubble Sort\n 2. Merge Sort\n 3. Quick Sort\n");
        printf(" 4. Counting Sort\n 5. Insertion Sort\n 6. Selection Sort\n");
        printf(" 7. Heap Sort\n 8. Radix Sort\n 9. Bucket Sort\n");
        printf("10. Shell Sort\n11. Tim Sort\n12. Comb Sort\n");
        printf("13. Gnome Sort\n14. Cycle Sort\n15. Cocktail Sort\n");
        printf("16. Pancake Sort\n17. Bogo Sort\n 0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Goodbye!\n");
            return 0;
        }
        
        clock_t start = clock();
        switch (choice) {
            case 1: bubbleSort(arr, n); break;
            case 2: mergeSort(arr, 0, n-1, n); break;
            case 3: quickSort(arr, 0, n-1, n); break;
            case 4: countingSort(arr, n); break;
            case 5: insertionSort(arr, n); break;
            case 6: selectionSort(arr, n); break;
            case 7: heapSort(arr, n); break;
            case 8: radixSort(arr, n); break;
            case 9: bucketSort(arr, n); break;
            case 10: shellSort(arr, n); break;
            case 11: timSort(arr, n); break;
            case 12: combSort(arr, n); break;
            case 13: gnomeSort(arr, n); break;
            case 14: cycleSort(arr, n); break;
            case 15: cocktailShakerSort(arr, n); break;
            case 16: pancakeSort(arr, n); break;
            case 17: bogoSort(arr, n); break;
            default: printf("Invalid choice.\n"); continue;
        }
        clock_t end = clock();
        
        printf("\nSorted Array:\n");
        printArray(arr, n);
        printf("Time taken: %.5f seconds\n", (double)(end - start)/CLOCKS_PER_SEC);
    } while (1);
    
    return 0;
}
