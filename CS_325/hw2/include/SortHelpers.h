#include <stdint.h>

void WriteInsertionSort(uint32_t * data, const char * filename);
void WriteMergeSort(uint32_t * data, const char * filename);
void WriteStoogeSort(uint32_t * data, const char * filename);

float elapsedTime(struct timespec *start, struct timespec *stop);

void mergeSort(uint32_t * arr, uint32_t l, uint32_t r);
void insertionSort(uint32_t * arr, uint32_t n);
void stoogeSort(uint32_t * arr, uint32_t start, uint32_t end);