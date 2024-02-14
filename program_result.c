// тип памяти - динамическое
// тип элементов массива - double
// вид сортировки - по неубыванию модулей 
// 1 метод сортировки - метод выбора 
// 2 метод сортировки - быстрая сортировка, рекурсивная реализация  

#include <stdio.h>
#include <time.h>   // работа с измерением времени
#include <stdlib.h> // работа с динамической память, rand()
#include <math.h> 

// объявление типа элементов массива
typedef double type_arr;


// смена двух элементов массива:
void change(type_arr *a, type_arr *b){ 
    type_arr tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// сортировка методом выбора 
void selection_sort(type_arr arr[], int n){
    for (int i = 0; i < n-1; i++){
        int min_ind = i;
        for (int j = i+1; j < n; j++){
            if (abs(arr[j]) < abs(arr[min_ind])){
                min_ind = j;
            }
        }
        change(&arr[i], &arr[min_ind]);
    }
}

// быстрая сортировка рекурсией 
void fast_sort(type_arr arr[], int n){
    int i = 0;
    int j = n - 1;
    int mid = n/2;
    do {
        while (abs(arr[i]) < abs(arr[mid])) {
            i++;
        }
        while (abs(arr[j]) > abs(arr[mid])){
            j--;
        }
        if (i <= j) {
            change(&arr[i], &arr[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0){
        fast_sort(arr, j + 1);
    }
    if (i < n) {
        fast_sort(&arr[i], n - i );
    }
}


// заполнение массива случайными числами в диапазоне от -32768 до 32767
void filling (type_arr a[], int n, int sd){
    srand(sd);
    for (int i = 0; i < n; i++){
        a[i] =(rand()/1)*pow(-1, (rand() % 2 ))+(rand()/10000.0);
        //a[i] = ((double)rand() / RAND_MAX)*RAND_MAX;
    }
}


int main() {
    
    clock_t t_a, t_b;
    for(int siz = 100; siz < 101; siz+=500){
        srand(time(NULL));
        // объявление памяти 
        type_arr *arr_a = malloc (siz * sizeof(type_arr)); 
        type_arr *arr_b = malloc (siz * sizeof(type_arr));
        int seed_numb = rand();

        // заполнение массива
        filling (arr_a, siz, seed_numb);
        filling(arr_b, siz, seed_numb);
        
        // переменные кол-ва сранения и смены
        int count_ch_a = 0;
        int count_ch_b = 0;
        int count_comp_a = 0;
        int count_comp_b = 0;

        // выполнение сортировок
        t_a = clock();
        selection_sort(arr_a, siz);
        t_a = clock() - t_a;
        double ta = ((double)(t_a))/CLOCKS_PER_SEC; // в секундах
        t_b = clock();
        fast_sort(arr_b, siz);
        t_b = clock() - t_b;
        double tb = (double)(t_b)/CLOCKS_PER_SEC;

        // вывод массива
        printf("arr a\n");
        for (int i = 0; i < siz; i++){
            printf("%15lf\n ", arr_a[i]);
        }
        // вывод результатов
        printf("time arr a - %f\n", ta);
        //printf("changes: %d\n, compares: %d\n", count_ch_a, count_comp_a);
        printf("\n");

        // вывод массива
        printf("arr b\n");
        for (int i = 0; i < siz; i++){
            printf("%15lf\n ", arr_b[i]);
        }
        // вывод результатов
        printf("time arr b - %f\n", tb);
        //printf("changes: %d\n, compares: %d\n", count_ch_b, count_comp_b );
        printf("\n");

        // очищение памяти
        free(arr_a);
        free(arr_b);
    }
    return 0;
}

