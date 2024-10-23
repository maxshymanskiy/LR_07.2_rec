#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo);
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int N, int colNo);
void PrintRows(int** a, const int N, int rowNo);
int SearchMinInRowRecursive(int* row, const int N, int colNo, int minIndex);
void SwapMinWithSecondaryDiagonal(int** a, const int N, int rowNo);

int main()
{
    srand((unsigned)time(NULL));

    int N;
    cout << "N = "; cin >> N;

    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];

    int Low = 0, High = 9;

    // Створення та виведення матриці
    CreateRows(a, N, Low, High, 0);
    PrintRows(a, N, 0);

    // Обмін мінімальних елементів із побічною діагоналлю
    SwapMinWithSecondaryDiagonal(a, N, 0);

    cout << "Modified matrix:" << endl;
    PrintRows(a, N, 0);

    // Очищення пам'яті
    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Рекурсивно створює один рядок матриці
void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

// Рекурсивно створює всі рядки матриці
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, Low, High, rowNo + 1);
}

// Рекурсивно виводить один рядок матриці
void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

// Рекурсивно виводить всі рядки матриці
void PrintRows(int** a, const int N, int rowNo)
{
    PrintRow(a, rowNo, N, 0);
    if (rowNo < N - 1)
        PrintRows(a, N, rowNo + 1);
    else
        cout << endl;
}

// Рекурсивно шукає індекс мінімального елемента в рядку
int SearchMinInRowRecursive(int* row, const int N, int colNo, int minIndex)
{
    if (row[colNo] < row[minIndex])
        minIndex = colNo;
    if (colNo < N - 1)
        return SearchMinInRowRecursive(row, N, colNo + 1, minIndex);
    else
        return minIndex;
}

// Рекурсивно міняє мінімальні елементи з елементами на побічній діагоналі
void SwapMinWithSecondaryDiagonal(int** a, const int N, int rowNo)
{
    if (rowNo < N) {
        int minIndex = SearchMinInRowRecursive(a[rowNo], N, 0, 0);
        int secondaryDiagIndex = N - 1 - rowNo;

        if (minIndex != secondaryDiagIndex) {
            int temp = a[rowNo][minIndex];
            a[rowNo][minIndex] = a[rowNo][secondaryDiagIndex];
            a[rowNo][secondaryDiagIndex] = temp;
        }

        // Рекурсивно переходимо до наступного рядка
        SwapMinWithSecondaryDiagonal(a, N, rowNo + 1);
    }
}
