#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;

double get_time() {
return std::chrono::duration_cast<std::chrono::microseconds>
(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int rand_uns(int min, int max) {
unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
static std::default_random_engine e(seed);
std::uniform_int_distribution<int> d(min, max);
return d(e);
}


void print_arr(int *arr,  int l)
{

    for ( int i = 0; i < l; i++)
    {
        cout << arr[i] << " " ;
    }
}

void heapify(int* array, int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if ((l < n) && (array[l] > array[largest])){
        largest = l;
    }
    if ((r < n) && (array[r] > array[largest])){
        largest = r;
    }
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

void heapSort(int* array, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
    for (int i=n-1; i>=0; i--)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}
void speedBubbleSort(int* array, int n) {
    int tmp, k;
 int step = n - 1;
 while(n > 1) {
  step /= 1.247;
  if (step < 1){
            step = 1;
        }
  k = 0;
  for (int i = 0; i + step < n; i++) {
   if(array[i] > array[i + step]) {
    tmp = array[i];
    array[i] = array[i + step];
    array[i + step] = tmp;
    k = i;
   }
  }
  if (step == 1){
   n = k + 1;
  }
 }
}
int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{
    if (start >= end) {
        return;
    }
    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}


long double time_heapSort(int *mas_pu, int l)
{
    long double start, finish;
    start = get_time();
    heapSort(mas_pu, l);
    finish = get_time();
    return finish - start;
}


long long int time_speed(int *mas_gnom, int l)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (long long int i = 1; i < 1000000000; i += 1);
    speedBubbleSort(mas_gnom, l);
    auto end = std::chrono::high_resolution_clock::now();
    auto nsec = end - start;
    return nsec.count();
}

long double time_quickSort(int *mas_gnom, int l)
{
     long double start, finish;
    start = get_time();
    quickSort(mas_gnom, l-1, 0);
    finish = get_time();
    return finish - start;
}

int main()
{

    ofstream f("2.csv", ios::out);
    // csv - стандартный формат для хранения данных прямым текстом.

    //int mas_pu[1000000];
    int mas_vst[100000];
    //int mas_gnom[1000000];


    for (int l = 1000; l<80000; l+=1000)
    {

        for (long long int i = l-1; i >= 0; i--)
        {
            //mas_pu[i] = rand_uns(0,1000);
            mas_vst[i] = rand_uns(0,1000);
            //mas_gnom[i] = rand_uns(0,1000);

        }



        f << l //<< " " << time_heapSort(mas_pu, l)
        <<  " " << time_speed(mas_vst, l)
        //<<
         //" " << time_quickSort(mas_gnom, l) << " "
        //<< time_pu(mas_PU, l) << " " << time_vst(mas_VST, l) << " " << time_gnom(mas_GNOM, l)
    << endl;
    }

    return 0;

}
