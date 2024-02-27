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
            ++(*comp);
            if ((abs(arr[j]) < abs(arr[min_ind]))){
                min_ind = j;
            }
        }
        if (i != min_ind) {
            change(&arr[i], &arr[min_ind]);
            *ch+=1;
        }
        
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
        while ((++(*comp)) && (abs(arr[i]) < abs(pivot))) {
            i++;
        }
        while ((++(*comp)) && (abs(arr[j]) > abs(pivot))){
            j--;
        }
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


// заполнение массива 
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

// среднее значение элементов в массиве
float sred(int a[], int y)
{
    int s = 0;
    for (int i = 0; i < y; i+=1)
    {
        s+=a[i];
    }
    float sr = (float)s / y;
    return sr;
}

//программа

int main() {
    printf("type of filling mas:\n");
    printf("1 - elements ordered \n");
    printf("2 - elements reversed ordered\n");
    printf("3 - elements n random order\n");
    int var;
    scanf("%d", &var);
    // int y = 100;
    int siz = 7; // размер нашего массива
    int siz2 = 1; // количество прогонов для нахождения среднего

    // создание массивов для подсчета среднего количества сравнений и смен
    int arr_ch_a[siz2] = {};
    int arr_ch_b[siz2] = {};
    int arr_comp_a[siz2] = {};
    int arr_comp_b[siz2] = {};

    // цикла для проверок массивов 
    for(int y = 0; y < siz2 ; y+=1)
    {
        // объявление памяти
        type_arr *arr_a = malloc (siz * sizeof(type_arr));
        type_arr *arr_b = malloc (siz * sizeof(type_arr));
        type_arr *arr_c = malloc (siz * sizeof(type_arr));

        //srand(time(NULL));
        //srand(1);
        int seed_numb = rand();
        //int seed_numb = 1225331222;

        // заполнение массива
        filling (arr_a, siz, seed_numb, var);
        filling(arr_b, siz, seed_numb, var);
        filling(arr_c, siz, seed_numb, var);

        // переменные кол-ва сранения и смены
        int count_ch_a = 0;
        int count_ch_b = 0;
        int count_comp_a = 0;
        int count_comp_b = 0;

        // выполнение сортировок
        selection_sort(arr_a, siz, &count_ch_a, &count_comp_a);
        fast_sort(arr_b, siz, &count_ch_b, &count_comp_b);

        // занесение элементов в массив средних значений
        arr_ch_a[y] = count_ch_a;
        arr_ch_b[y] = count_ch_b;
        arr_comp_a[y] = count_comp_a;
        arr_comp_b[y] = count_comp_b;

        // вывод результатов
        /*printf("\n");
        printf("arr A (selection sort)\namount of elements %d\n", siz);
        printf("changes: %d\ncompares: %d\n", count_ch_a, count_comp_a );
        printf(". _ . - . _ . - . _ . - \n");
        printf("arr B (quick sort)\namount of elements %d\n", siz);
        printf("changes: %d\ncompares: %d\n", count_ch_b, count_comp_b );
        printf("\n");
        printf("------------------------------|\n");*/
        //printf("\n%d\n",siz/y);

        /*
        printf("\n");
        printf("\tSort:\t     Selection         Quick\n");
        printf("\tchanges: %10d\t %10d\n\tcompares: %10d\t%11d\n",count_ch_a,count_ch_b,count_comp_a, count_comp_b);
        */

        // очищение памяти
        free(arr_a);
        free(arr_b);
        free(arr_c);

    }

    // подсчет средних значений
    printf("\n\nSelection sort: chang: %f\t comp: %f", sred(arr_ch_a, siz2), sred(arr_comp_a, siz2));
    printf("\nQuick sort: chang: %f\t comp: %f", sred(arr_ch_b, siz2), sred(arr_comp_b, siz2));
    printf("\n\n");
    return 0;
}
