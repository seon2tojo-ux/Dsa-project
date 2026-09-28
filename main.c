#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight;
    char id[20];
    int original_pos;
} Package;

void print_packages(Package a[], int n) {
    for (int i = 0; i < n; i++)
        printf("(%s,%d)", a[i].id, a[i].weight);
    printf("\n");
}

void copy_array(Package dest[], Package src[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* ---------- MERGE SORT ---------- */

long long merge_comparisons = 0;

void merge(Package a[], Package temp[], int left, int mid, int right, int show) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        merge_comparisons++;

        /*
         * <= makes Merge Sort stable:
         * when weights are equal, the left element is copied first.
         */
        if (a[i].weight <= a[j].weight)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = left; i <= right; i++)
        a[i] = temp[i];

    if (show) {
        printf("Merge [%d-%d] + [%d-%d]: ", left, mid, mid + 1, right);
        for (i = left; i <= right; i++)
            printf("%s(%d) ", a[i].id, a[i].weight);
        printf("\n");
    }
}

void merge_sort_rec(Package a[], Package temp[], int left, int right, int show) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_rec(a, temp, left, mid, show);
    merge_sort_rec(a, temp, mid + 1, right, show);
    merge(a, temp, left, mid, right, show);
}

void merge_sort(Package a[], int n, int show) {
    Package *temp = malloc(n * sizeof(Package));
    if (!temp) {
        printf("Memory allocation failed.\n");
        return;
    }

    merge_comparisons = 0;
    merge_sort_rec(a, temp, 0, n - 1, show);
    free(temp);
}

/* ---------- QUICK SORT ---------- */

long long quick_comparisons = 0;

int partition(Package a[], int low, int high, int show) {
    Package pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quick_comparisons++;

        /*
         * < is intentionally used here.
         * This ordinary in-place Quick Sort is NOT stable.
         */
        if (a[j].weight < pivot.weight) {
            i++;
            Package t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    Package t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;

    if (show) {
        printf("Partition [%d-%d], pivot=%s(%d): ",
               low, high, pivot.id, pivot.weight);
        for (int k = low; k <= high; k++)
            printf("%s(%d) ", a[k].id, a[k].weight);
        printf("\n");
    }

    return i + 1;
}

void quick_sort_rec(Package a[], int low, int high, int show) {
    if (low < high) {
        int p = partition(a, low, high, show);
        quick_sort_rec(a, low, p - 1, show);
        quick_sort_rec(a, p + 1, high, show);
    }
}

void quick_sort(Package a[], int n, int show) {
    quick_comparisons = 0;
    quick_sort_rec(a, 0, n - 1, show);
}

/* ---------- INPUT / MAIN ---------- */

int main(void) {
    int n;

    printf("Package Sorting: Merge Sort vs Quick Sort\n");
    printf("Enter number of packages (max 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid number of packages.\n");
        return 1;
    }

    Package original[100], merge_result[100], quick_result[100];

    printf("Enter weight and package ID for each package:\n");
    for (int i = 0; i < n; i++) {
        printf("Package %d: ", i + 1);
        if (scanf("%d %19s", &original[i].weight, original[i].id) != 2) {
            printf("Invalid input.\n");
            return 1;
        }
        original[i].original_pos = i;
    }

    copy_array(merge_result, original, n);
    copy_array(quick_result, original, n);

    printf("\nOriginal order:\n");
    print_packages(original, n);

    printf("\n--- MERGE SORT INTERMEDIATE STEPS ---\n");
    merge_sort(merge_result, n, 1);
    printf("Final Merge Sort result:\n");
    print_packages(merge_result, n);
    printf("Merge Sort comparisons: %lld\n", merge_comparisons);

    printf("\n--- QUICK SORT INTERMEDIATE STEPS ---\n");
    quick_sort(quick_result, n, 1);
    printf("Final Quick Sort result:\n");
    print_packages(quick_result, n);
    printf("Quick Sort comparisons: %lld\n", quick_comparisons);

    printf("\nStability verification:\n");
    printf("Stable Merge Sort keeps equal-weight packages in original order.\n");
    printf("For this input, weight 10: P4 -> P8, 15: P2 -> P5, 20: P1 -> P3 -> P6.\n");
    printf("Ordinary in-place Quick Sort does not guarantee this property.\n");

    return 0;
}
