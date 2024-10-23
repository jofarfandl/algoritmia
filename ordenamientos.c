#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void aux(long int* x, long int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partition (long int arr[],long int low,long int high) 
{
  int pivot = arr[high]; 
  int i = (low - 1);
  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      aux(&arr[i], &arr[j]);
    }
  }
  aux(&arr[i + 1], &arr[high]);
  return (i + 1);
}

// Bubble sort
void bubbleSort(long int a[], long int n) 
{
  for (long int i = 0; i < n - 1; i++) {
    for (long int j = 0; j < n - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        aux(&a[j], &a[j + 1]); 
      }
    }
  }
}

// Selection sort
void selectionSort(long int arr[], long int n) 
{
  long int i, j, midx;
  for (i = 0; i < n - 1; i++) {
    midx = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[midx])
        midx = j;
    aux(&arr[midx], &arr[i]);
  }
}

// Insertion sort
void insertionSort(long int arr[], long int n)
{
  long int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

// Shell sort
void shellSort(long int arr[], long int n)
{
  for (int gap = n/2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) { 
      int temp = arr[i];
      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
        arr[j] = arr[j - gap];
      arr[j] = temp;
    }
  }
}

// Quick sort
void quickSort(long int arr[], long int low, long int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int main() 
{
  long int num = 10;
  int i = 0;
  double time1[10], time2[10], time3[10], time4[10], time5[10];
  printf("Tamanio,         Selection,    Bubble,    Insertion,    Shell\n");
  // Performs 5 iterations
  while (i++ < 5) {
    long int a[num], b[num], c[num], d[num], e[num];
    for (int i = 0; i < num; i++) {
      long int num = rand() % num + 1;
      a[i] = num;
      b[i] = num;
      c[i] = num;
      d[i] = num;
      e[num] = num;
    }
    clock_t start, end;
    start = clock();    // Selection sort
    selectionSort(a, num);
    end = clock();
    time1[i] = ((double)(end - start));

    start = clock();    // Bubble sort
    bubbleSort(b, num);
    end = clock();
    time2[i] = ((double)(end - start));

    start = clock();// Insertion sort
    insertionSort(c, num);
    end = clock();
    time3[i] = ((double)(end - start));

    start = clock();// Shell sort
    shellSort(d, num);
    end = clock();
    time4[i] = ((double)(end - start));
  
    printf("%li arreglos,\t %lis, %lis, %lis, %lis,\n",num,(long int)time1[i],(long int)time2[i],(long int)time3[i],(long int)time4[i]);
    num = num * 10;
  }
  return 0;
}