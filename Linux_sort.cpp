#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <time.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <fstream>

void sleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}

const int len_mas = 250;

const int M = 150;// высота игрового пол€
const int N = 250;// ширина игрового пол€

int ts = 5;
int ts_window = 5;
int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void paint(int* arr, int l, sf::RenderWindow* window, int f) {
    window->clear();
    for (int item = 0; item < l; item++) {
        sf::RectangleShape rect(sf::Vector2f(ts, -ts * arr[item]));
        rect.setPosition(sf::Vector2f(ts * item, ts * 150));
        if (item == f) rect.setFillColor(sf::Color(255, 0, 0));
        else rect.setFillColor(sf::Color(255, 255, 255));
        window->draw(rect);
    }
}

void sort_pu(int* arr, int l, sf::RenderWindow* window)
{
    for (int i = 0; i < l; i++)
    {        
        for (int j = 0; j < l - 1; j++) {
            int f = i;
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                f = j;
            }
            paint(arr, l, window, i);
        }
        window->display();
    }
}

void sort_gnom(int* arr, int l, sf::RenderWindow* window) {
    int index = 0;

    while (index < l) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            std::swap(arr[index], arr[index - 1]);
            index--;
        }
        int f = index;
        paint(arr, l, window, f);
        window->display();
    }
}

void sort_vst(int* arr, int l, sf::RenderWindow* window)
{
    for (int i = 1; i < l; i++)
    {
        int j = i - 1;
        int supp = arr[i];
        while (j >= 0 && (arr[j] > supp))
        {

            arr[j + 1] = arr[j];
            arr[j] = supp;
            j -= 1;
            int f = i;
            paint(arr, l, window, f);            
        }
        window->display();
    }
    paint(arr, l, window, 0);
    window->display();
}

void heapify(int* arr, int n, int i, sf::RenderWindow* window)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if ((l < n) && (arr[l] > arr[largest])) {
        largest = l;
    }
    if ((r < n) && (arr[r] > arr[largest])) {
        largest = r;
    }
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, window);
    }
}

void sort_heapSort(int* arr, int n, sf::RenderWindow* window)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, window);
        paint(arr, n, window, i);
        window->display();
        sleep(10);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, window);
        paint(arr, n, window, i);
        window->display();
        sleep(10);
    }
}

void sort_speedBubble(int* arr, int n, sf::RenderWindow* window) {
    int tmp, k;
    int step = n - 1;
    while (n > 1) {
        step /= 1.247;
        if (step < 1) {
            step = 1;
        }
        k = 0;
        for (int i = 0; i + step < n; i++) {
            if (arr[i] > arr[i + step]) {
                tmp = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = tmp;
                k = i;
                paint(arr, n, window, i);
                window->display();
                sleep(10);
            }
        }
        if (step == 1) {
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
    std::swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void sort_quickSort(int* arr, int start, int end, sf::RenderWindow* window)
{
    if (start >= end) {
        return;
    }
    paint(arr, len_mas, window, start);
    window->display();
    sleep(20);
    int p = partition(arr, start, end);
    
    sort_quickSort(arr, start, p - 1, window);
    sort_quickSort(arr, p + 1, end, window);
}

int main()
{
    srand(time(0));
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(N * ts_window, M * ts_window), "SORTIROVKA");

    
    int mas[len_mas];
    for (int i = 0; i < len_mas; i++)
        mas[i] = rand_uns(0, 120);

    while (window.isOpen())
    {
        // ѕолучаем врем€, прошедшее с начала отсчета, и конвертируем его в секунды
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                // тогда закрываем его
                window.close();
        }

        

        // –исуем на кадре
        /*for (int i = 0; i < len_mas; i++) {
            sf::RectangleShape rect(sf::Vector2f(ts, -ts * mas[i]));
            rect.setPosition(sf::Vector2f(ts * i, ts * 150));
            rect.setFillColor(sf::Color(150, 50, 250));
            window.draw(rect);
        }
        window.display();*/
        window.clear();
        //sort_pu(mas, len_mas, &window);
        //sort_gnom(mas, len_mas, &window);
        //sort_vst(mas, len_mas, &window);
        //sort_heapSort(mas, len_mas, &window);
        //sort_speedBubble(mas, len_mas, &window);
        sort_quickSort(mas, 0, len_mas - 1, &window);
        paint(mas, len_mas, &window, 0);
        window.display();
        sleep(5000);
    }

return 0;
}