// тип памяти - динамическое
// тип элементов массива - double
// вид сортировки - по неубыванию модулей
// 1 метод сортировки - метод выбора
// 2 метод сортировки - быстрая сортировка, рекурсивная реализация
// mas_1 - элементы упорядочены 
// mas_2 - элементы упорядочены в обратном порядке
// mas_3 - элементы в случайном порядке

#include <stdio.h>
#include <time.h>   // работа с измерением времени
#include <stdlib.h> // работа с динамической память, rand()
#include <math.h>
#include <stdbool.h>

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
void selection_sort(type_arr arr[], int n, int *ch, int *comp){
    for (int i = 0; i < n-1; i++){
        int min_ind = i;
        for (int j = i+1; j < n; j++){
            if (abs(arr[j]) < abs(arr[min_ind])){
                min_ind = j;
                *comp+=1;
            }
        }
        change(&arr[i], &arr[min_ind]);
        *ch+=1;
    }
}

// просто сортировка 
void sort_q(type_arr arr[], int n){
    for (int i = 0; i < n-1; i++){
        int min_ind = i;
        for (int j = i+1; j < n; j++){
            if (arr[j] < arr[min_ind]){
                min_ind = j;
            }
        }
        change(&arr[i], &arr[min_ind]);
    }
}

// просто обратная сортировка 
void sort_rev(type_arr arr[], int n){
    for (int i = 0; i < n-1; i++){
        int min_ind = i;
        for (int j = i+1; j < n; j++){
            if (arr[j] > arr[min_ind]){
                min_ind = j;
            }
        }
        change(&arr[i], &arr[min_ind]);
    }
}


// быстрая сортировка рекурсией
void fast_sort(type_arr arr[], int n, int *ch, int *comp){
    int i = 0;
    int j = n - 1;
    int mid = n/2;

    type_arr pivot = arr [ mid ];
    do {
        while (abs(arr[i]) < abs(pivot)) {
            i++;
        }
        (*comp)++;
        while (abs(arr[j]) > abs(pivot)){
            j--;
        }
        (*comp)++;
        if (i <= j) {
            change(&arr[i], &arr[j]);
            (*ch)++;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0){
        fast_sort(arr, j + 1, *&ch, *&comp);
    }
    if (i < n) {
        fast_sort(&arr[i], n - i, *&ch, *&comp);
    }
}


// заполнение массива случайными числами в диапазоне от -32768 до 32767
void filling (type_arr a[], int n, int sd, int var){
    srand(sd);
    for (int i = 0; i < n; i++){
        a[i] =(rand())*pow(-1, (rand() % 2 ))+(rand()/10000.0);
    }
    if (var == 1){
        sort_q(a, n);
    }
    if (var == 2){
        sort_rev(a, n);
    }
}

//программа

int main() {
    printf("type of filling mas:\n");
    printf("1 - elements ordered \n");
    printf("2 - elements reversed ordered\n");
    printf("3 - elements n random order\n");
    int var;
    scanf("%d", &var);
    for(int siz = 100; siz < 101; siz+=1){

        // объявление памяти
        type_arr *arr_a = malloc (siz * sizeof(type_arr));
        type_arr *arr_b = malloc (siz * sizeof(type_arr));
        srand(time(NULL));
        int seed_numb = rand();
        //int seed_numb = 1225331222;

        // заполнение массива
        filling (arr_a, siz, seed_numb, var);
        filling(arr_b, siz, seed_numb, var);

        // переменные кол-ва сранения и смены
        int count_ch_a = 0;
        int count_ch_b = 0;
        int count_comp_a = 0;
        int count_comp_b = 0;

        // выполнение сортировок
        selection_sort(arr_a, siz, &count_ch_a, &count_comp_a);
        fast_sort(arr_b, siz, &count_ch_b, &count_comp_b);

        // вывод результатов

        bool ch = true;

        for (int i = 0; i < siz; i++){
            if (i > 0 ) {
                if (abs(arr_b[i - 1]) < abs (arr_b[i])) 
                    ch = false;
            }
            printf("[%lf] ", arr_b[i]);
        }       

        /*
        printf("\n");
        printf("arr A (selection sort)\namount of elements %d\n", siz);
        printf("changes: %d\ncompares: %d\n", count_ch_a, count_comp_a );
        printf(". _ . - . _ . - . _ . - \n");
        printf("arr B (quick sort)\namount of elements %d\n", siz);
        printf("changes: %d\ncompares: %d\n", count_ch_b, count_comp_b );
        printf("\n");
        printf("------------------------------|\n");
        */
        // очищение памяти
        free(arr_a);
        free(arr_b);
    }
    return 0;
}
