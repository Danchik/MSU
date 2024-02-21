#include <stdio.h>
#include <time.h>   // работа с измерением времени
#include <stdlib.h> // работа с динамической память, rand()
#include <math.h> 

typedef int type_arr;

void change(type_arr *a, type_arr *b){ 
    type_arr tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void fast_sort(type_arr* a, int N, int *ch, int *comp) {
// На входе - массив a[], a[N] - его последний элемент.

  int i = 0, j = N-1; 		// поставить указатели на исходные места
  type_arr temp, p;

		// центральный элемент

  // процедура разделения
  do {
    while ( a[i] < p ) {i++; (*comp)++;}
    while ( a[j] > p ) {j--; (*comp)++;}

    if (i <= j) {
      temp = a[i]; a[i] = a[j]; a[j] = temp;
      i++; j--;
      (*ch)++;
    }
  } while ( i<=j );


  // рекурсивные вызовы, если есть, что сортировать 
  if ( j > 0 ) fast_sort(a, N/2, *&ch, *&comp );
  if ( N > i ) fast_sort(a+i, (N-2)/2, *&ch, *&comp);
}


int main() {
    int n = 10;
    type_arr arr_a[] = {2326, 1808, 91, 401, 637, 1319, 2195, 1260, 2311, 2032};
    for (int i = 0; i < n; i+=1){
        printf("[%d] ", arr_a[i]);
    }
    fast_sort_sort(arr_a, n);
    printf("\n");
    for (int i = 0; i < n; i+=1){
        printf("[%d] ", arr_a[i]);
    }
    
}