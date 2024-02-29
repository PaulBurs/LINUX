#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;


int rand_uns(int min, int max) {
unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
static std::default_random_engine e(seed);
std::uniform_int_distribution<int> d(min, max);
return d(e);
}
double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

void print_arr(int *arr,  int l)
{

    for ( int i = 0; i < l; i++)
    {
        cout << arr[i] << " " ;
    }
}

void sort_pu(int *arr, int l)
{
    for (int i=0; i<l; i++)
    for (int j=0; j<l-1; j++)
        if (arr[j]>arr[j+1])
        {
            int tmp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = tmp;
        }

}

void sort_gnom(int* arr, int l) {
    int index = 0;

    while (index < l) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}

void sort_vst(int *arr, int l)
{
    for (int i=1; i<l; i++)
    {
        int j = i - 1;
        int supp = arr[i];
        while (j >= 0 && (arr[j] > supp))
        {

            arr[j + 1] = arr[j];
            arr[j] = supp;
            j -= 1;

        }

    }

}
long long int time_pu(int *arr, int l)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (long long  i = 1; i < 1000000000; i += 1);
    sort_pu(arr, l);
    auto end = std::chrono::high_resolution_clock::now();
    auto nsec = end - start;
    return nsec.count();
}



long double time_vst(int *mas_vst, int l)
{
    long double start, finish;
    start = get_time();
    sort_vst(mas_vst, l);
    finish = get_time();
    return finish - start;
}
 long long int time_gnom(int *mas_gnom, int l)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (long long int i = 1; i < 1000000000; i += 1);
    sort_gnom(mas_gnom, l);
    auto end = std::chrono::high_resolution_clock::now();
    auto nsec = end - start;
    return nsec.count();
}

int main()
{

    ofstream f("1.csv", ios::out);
    // csv - стандартный формат для хранения данных прямым текстом.

    //int mas_pu[100000];
    //int mas_vst[100000];
    int mas_gnom[100000];


    for (int l = 1000; l<50000; l+=2000)
    {

        for (int i = l-1; i >= 0; i--)
        {
            //mas_pu[i] = rand_uns(0, 1000);
            //mas_vst[i] = rand_uns(0, 1000);
            mas_gnom[i] = rand_uns(0, 1000);

        }



        f << l
        //<< " " << time_pu(mas_pu, l)
        //<<  " " << time_vst(mas_vst, l) << " "
        << " " << time_gnom(mas_gnom, l) << " "
        //<< time_pu(mas_PU, l) << " " << time_vst(mas_VST, l) << " " << time_gnom(mas_GNOM, l)
    << endl;
    }

    return 0;

}
