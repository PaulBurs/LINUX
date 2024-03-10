#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <time.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void sleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}

const int len_mas = 250;
const int len_spiral = 1500;
const int len_cord = 200;
const int len_pol = 100;
const int len_dino = 320;
const int str_dino = 20;

const int M = 160;// высота игрового пол€
const int N = 240;// ширина игрового пол€

const int ts = 5;
const int ts_window = 5;

void randSort(int* m, int size)
{
    int buf;
    int pos, pos2;
    for (int i = 0; i < rand() % 50 + size; i++)
    {
        pos = rand() % size;
        pos2 = rand() % size;
        int buf = m[pos];
        m[pos] = m[pos2];
        m[pos2] = buf;
    }
}

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void paint_spiral(int* arr, int l, sf::RenderWindow* window) {
    window->clear();
    for (int i = 0; i < l; i++) {
        sf::CircleShape shape(2);
        shape.setPosition(sf::Vector2f(ts * N / 2 + 0.5 * arr[i] * cos(i / 3.14 * 360), ts * M / 2 + 0.5 * arr[i] * sin(arr[i] / 3.14 * 360)));
        shape.setFillColor(sf::Color(255, 0, 0));
        window->draw(shape);
    }
}

void paint(int* arr, int l, sf::RenderWindow* window, int f) {
    
    for (int item = 0; item < l; item++) {
        sf::RectangleShape rect(sf::Vector2f(ts, -ts * arr[item]));
        rect.setPosition(sf::Vector2f(ts * item, ts * 150));
        if (item == f) rect.setFillColor(sf::Color(255, 0, 0));
        else rect.setFillColor(sf::Color(255, 255, 255));
        window->draw(rect);
    }
}

void paint_cord(int* arr, int l, sf::RenderWindow* window, sf::VertexArray cord) {
    window->clear();
    for (int i = 0; i < cord.getVertexCount(); i++) {
        if (arr[i] - i == 0) {
            cord[i].position = sf::Vector2f(ts * 20 + ts * i, ts * M / 2);
        }
        else {
            cord[i].position = sf::Vector2f(ts * N / 2 + 0.5 * arr[i] * cos(i / 3.14 * 360), ts * M / 2 + arr[i] * sin(arr[i] / 3.14 * 360));
        }
        window->draw(cord);
    }
}

void sort_pu(int* arr, int l, sf::RenderWindow* window)
{
    for (int i = 0; i < l; i++)
    {
        window->clear();
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
        //sleep(0);
        window->display();
    }
}

void sort_vst(int* arr, int l, sf::RenderWindow* window, sf::VertexArray cord)
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
            paint_cord(arr, l, window, cord);
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

void sort_heapSort(int* arr, int n, sf::RenderWindow* window, sf::VertexArray cord)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, window);
        paint_cord(arr, n, window, cord);
        window->display();
        sleep(50);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, window);
        paint_cord(arr, n, window, cord);
        window->display();
        sleep(50);
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
                paint_dino(arr, n, window);
                //window->display();
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
    //paint(arr, len_mas, window, start);
    paint_spiral(arr, len_spiral, window);
    window->display();
    int p = partition(arr, start, end);
    sleep(5);
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
        mas[i] = i;

    //int spiral[len_spiral];
    //for (int i = 0; i < len_spiral; i++)
    //    spiral[i] = i;
    //randSort(spiral, len_spiral);

    //int fiber[len_cord];
    //for (int i = 0; i < len_cord; i++)
    //    fiber[i] = i;
    //randSort(fiber, len_cord);


    
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


        window.clear();

        sort_pu(mas, len_mas, &window);
        //sort_gnom(mas, len_mas, &window);
        //sleep(1000);
        //sort_vst(mas, len_mas, &window, cord);
        //sort_heapSort(mas, len_mas, &window, cord);
        //sleep(1000);
        //sort_speedBubble(mas, len_mas, &window);
        //sort_quickSort(spiral, 0, len_spiral - 1, &window);
        //sleep(5000);
        //paint_spiral(spiral, len_spiral, &window);
                

        window.display();
    }

    return 0;
}