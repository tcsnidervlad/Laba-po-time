#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define MAX_SIZE 100000
#define ARRAY_SIZE(a) sizeof(a) / sizeof (a[0])


#define TIME_TEST(testCode, time) { \
 clock_t start_time = clock() ; \
 testCode \
 clock_t end_time = clock() ;\
 clock_t sort_time = end_time - start_time ; \
 time = (double) sort_time / CLOCKS_PER_SEC ; \
 }


bool test_bit(int x, int k) {
    return x & 1 << k;
}

void radixSort(int *a, size_t size) {
    int b[MAX_SIZE];
    int n0;
    int n1;
    for (int k = 0; k < 256; k++) {
        n0 = n1 = 0;
        for (int i = 0; i < size; i++) {
            if (test_bit(a[i], k))
                n1++;
            else
                n0++;
        }
        int j0 = 0;
        int j1 = n0;
        for (int i = 0; i < size; i++) {
            if (test_bit(a[i], k)) {
                b[j1++] = a[i];
            } else
                b[j0++] = a[i];

        }
        for (int i = 0; i < size; i++) {
            a[i] = b[i];
        }

    }
}


void generateRandomArray() {
    int a[MAX_SIZE];
    for (size_t i = 0; i < MAX_SIZE; i++) {
        a[i] = rand();
    }
}

void outputArray_(int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void selectionSort(int *a, const size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
}

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
}


void combsort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

void shellSort(int *a, size_t size) {
    int i, j, step;
    int tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++) {
            tmp = a[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
}


long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            swap(&a[i], &a[minIndex]);
    }

    return nComps;
}

long long getInsertionSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t && nComps++) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return nComps;
}

long long getBubbleSortNComps(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 0; nComps++ && i < size - 1; i++) {
        for (size_t j = size - 1; nComps++ && j > i; j--) {
            if (++nComps && a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
        }
    }
    return nComps;
}

long long getCombsortNComps(int *a, const size_t size) {
    long long nComps = 0;
    size_t step = size;
    int swapped = 1;
    while (nComps++ && step > 1 || swapped) {
        if (nComps++ && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j) {
            nComps++;
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
        }
    }
    return nComps;
}

long long getshellSortNComps(int *a, size_t size) {
    int i, j, step;
    int tmp;
    long long nComps = 0;
    for (step = size / 2; ++nComps && step > 0; step /= 2)
        for (i = step; ++nComps && i < size; i++) {
            tmp = a[i];
            for (j = i; nComps++ && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
    return nComps;
}

long long getRadixSortNComps(int *a, size_t size) {
    int b[MAX_SIZE];
    int n0;
    int n1;
    long long nComps = 0;
    for (int k = 0; nComps++ && k < 256; k++) {
        n0 = n1 = 0;
        for (int i = 0; nComps++ && i < size; i++) {
            if (nComps++ && test_bit(a[i], k))
                n1++;
            else
                n0++;
        }
        int j0 = 0;
        int j1 = n0;
        for (int i = 0; nComps++ && i < size; i++) {
            if (nComps++ && test_bit(a[i], k)) {
                b[j1++] = a[i];
            } else
                b[j0++] = a[i];

        }
        for (int i = 0; i < size; i++) {
            a[i] = b[i];
        }

    }
    return nComps;
}




void generateOrderedArray() {
    int a[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        a[i] = i;
    }
    selectionSort(a, MAX_SIZE);
}

void reverse(int *a, int n) {
    for (int i = 0; i < n / 2; i++) {
        swap(&a[i], &a[n - 1 - i]);
    }
}


void generateOrderedBackwards() {
    int a[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        a[i] = i;
    }
    selectionSort(a, MAX_SIZE);
    reverse(a, MAX_SIZE);
    outputArray_(a, MAX_SIZE);
}

void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}


int isOrdered(int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] > a[i + 1])
            return 0;
    }
    return 1;
}


typedef struct SortFunc {
    void (*sort )(int *a, size_t n); // указатель на функцию
    // сортировки
    char name[64]; // имя сортировки,
    // используемое при выводе
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate )(int *a, size_t n); // указатель на функцию
    // генерации последоват.
    char name[64]; // имя генератора,
    // используемое при выводе
} GeneratingFunc;

double getTime() {
    clock_t start_time = clock();
    // фрагмент кода
    // время которого измеряется
    clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

void checkTime(void (*sortFunc )(int *, size_t),
               void (*generateFunc )(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", ++runCounter);
    printf(" Name : %s\n", experimentName);
    double time;
    TIME_TEST ({
                   sortFunc(innerBuffer, size);
               }, time);
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time : %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./Data/%s.csv", "Data");
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}


void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
            {combsort,      "combsort"},
            {shellSort,     "shellSort"},
            {radixSort,     "radixSort"},
            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     " ordered "},
            {generateOrderedBackwards, " orderedBackwards "}
    };
    const unsigned CASES_N = ARRAY_SIZE
                             (generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}


int main() {
    int a[4] = {1, 6, 7, 3};
    long long result = getInsertionSortNComp(a, 4);
    printf("%lld", result);


    return 0;
}
