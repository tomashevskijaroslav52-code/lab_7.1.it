#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. Функція виділення пам'яті для динамічної матриці
int** CreateMatrix(int rowCount, int colCount)
{
    int** Z = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        Z[i] = new int[colCount];
    }
    return Z;
}

// 2. Функція звільнення пам'яті матриці
void DeleteMatrix(int** Z, int rowCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        delete[] Z[i];
    }
    delete[] Z;
}

// 3. Формування матриці генератором випадкових чисел у заданому діапазоні
void Create(int** Z, int rowCount, int colCount, int Low, int High)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            Z[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// 4. Виведення матриці на екран
void Print(int** Z, int rowCount, int colCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            cout << setw(5) << Z[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// 5. Перестановка стовпчиків матриці за спаданням (Descending order)
void SortColumns(int** Z, int rowCount, int colCount)
{
    for (int j0 = 0; j0 < colCount - 1; j0++)
    {
        for (int j1 = 0; j1 < colCount - j0 - 1; j1++)
        {
            bool needSwap = false;

            // Порівнюємо елементи першого рядка (рядок 0) за спаданням
            if (Z[0][j1] < Z[0][j1 + 1])
            {
                needSwap = true;
            }
            else if (Z[0][j1] == Z[0][j1 + 1])
            {
                // Якщо елементи першого рядка рівні, порівнюємо другий рядок (рядок 1)
                if (Z[1][j1] < Z[1][j1 + 1])
                {
                    needSwap = true;
                }
                else if (Z[1][j1] == Z[1][j1 + 1])
                {
                    // Якщо елементи першого і другого рядків рівні, порівнюємо третій рядок (рядок 2)
                    if (Z[2][j1] < Z[2][j1 + 1])
                    {
                        needSwap = true;
                    }
                }
            }

            // Якщо потрібно — міняємо цілі стовпчики місцями
            if (needSwap)
            {
                for (int i = 0; i < rowCount; i++)
                {
                    int temp = Z[i][j1];
                    Z[i][j1] = Z[i][j1 + 1];
                    Z[i][j1 + 1] = temp;
                }
            }
        }
    }
}

// 6. Обчислення кількості (k), суми (S) елементів за критерієм та заміна їх нулями
void Calc(int** Z, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            // Критерій Варіанта 15: елемент додатний (> 0) або непарний (Z[i][j] % 2 != 0)
            if (Z[i][j] > 0 || Z[i][j] % 2 != 0)
            {
                S += Z[i][j];
                k++;
                Z[i][j] = 0; // заміна нулями
            }
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int rowCount = 8;
    int colCount = 6;
    int Low = -34;
    int High = 26;

    // Створення матриці
    int** Z = CreateMatrix(rowCount, colCount);

    // Заповнення та виведення початкової матриці
    Create(Z, rowCount, colCount, Low, High);
    cout << "Initial matrix Z (8x6):" << endl;
    Print(Z, rowCount, colCount);

    // 1. Опрацювання за критерієм (підрахунок суми, кількості та занулення)
    int S = 0;
    int k = 0;
    Calc(Z, rowCount, colCount, S, k);

    cout << "Results for criteria (positive or odd elements):" << endl;
    cout << "S = " << S << endl;
    cout << "k = " << k << endl << endl;

    cout << "Matrix after replacing criteria elements with zeros:" << endl;
    Print(Z, rowCount, colCount);

    // 2. Сортування (перестановка) стовпчиків модифікованої матриці
    SortColumns(Z, rowCount, colCount);

    cout << "Matrix after sorting columns (descending order by rows 0, then 1, then 2):" << endl;
    Print(Z, rowCount, colCount);

    // Звільнення пам'яті
    DeleteMatrix(Z, rowCount);

    return 0;
}
