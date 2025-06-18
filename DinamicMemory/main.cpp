#include<iostream>
using namespace std;

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[], int& n, const int value);
int* push_front(int arr[], int& n, const int value);

int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);

int** push_row_back(int** arr,int& rows, const int cols);

void push_col_back(int** arr, const int rows, int& cols);
//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2



void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение: "; cin >> value;

	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;

#endif // DYNAMIC_MEMORY_1

	int rows;
	int cols;
	cout << "Введите колисчество строк: "; cin >> rows;
	cout << "Введите колисчество элементов строки: "; cin >> cols;


	//////////////////////////////////////////////////////////
	///    Объявление двумерного динамического массива     ///
	//////////////////////////////////////////////////////////

	//1) создаем массив указателей:
	int** arr = new int* [rows];

	//2) выделяем память под строки:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}

    ///////////////////////////////////////////////////////////////
	
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	for (int i = 0; i < rows; i++)arr[i][cols - 1] = rand() % 1000;
	Print(arr, rows, cols);
	

	///////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	////    удаление двумерного динамического массива     ////
	//////////////////////////////////////////////////////////

	//1) сначала удаляются строки двумерного массива:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) только теперь можно удалить массив указателей
	delete[] arr;


}
	
void FillRand(int arr[], const int n, int minRand, int maxRand)
{

	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand-minRand) +minRand;

	}

}
void FillRand(int** arr, const int rows, const int cols, int minRand, int maxRand)
{
for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand - minRand) + minRand;
		}
	}
}

void Print(int arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0;i < n;i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << "\t";
		}
	     cout << endl;
	}
	cout << endl;
}

int* push_back(int arr[], int& n, const int value)
{
	//1) создаем буферный массив нужного размера
	int* buffer = new int[n + 1];

	//2) копируем все элементы из исходного массива в буферный
	for (int i = 0;i < n;i++)
	{
		buffer[i] = arr[i];
	}

	//3) удаляем исходный массив
	delete[] arr;

	//4) подменяем адрес исходного массива адресом нового массива
	arr = buffer;
	buffer = nullptr;

	//5) только после всего вышенаписанного в массиве arr появляется элемент
	//   в который можно сохранить добавляемое значениеж
	arr[n] = value;

	//6) после добавления элемента в массив, количество его элементов 
	//   увеличивается на 1
	n++;

	//7) Mission complete - значение добавлено.
	return arr;
}
int* push_front(int arr[], int& n, const int value)
{
	//1) 
	int* buffer = new int[n + 1];
	//2)
	for (int i = 0;i < n;i++)
	{
		buffer[i+1] = arr[i];
	}
	//3)
	delete[] arr;

	//4)
	buffer[0] = value;

	//5)
	n++;

	return buffer;
}

int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int** push_row_back(int** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей нужного размера:
	int** buffer = new int* [rows + 1];

	//2) Копируем адреса строк в новый массив
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив указателей
	delete[]arr;
	

	//4) Добавляем добавляемую строку
	buffer[rows] = new int[cols] {};

	//5) после добавления строки, количество строк увеличивается на 1:
	rows++;

	//6)  Возвращаем новый массив
	return buffer;
}

void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) создаем буферную строку нужного размера
		int* buffer = new int[cols + 1] {};
		//2) копируем элементы из исходной строки в буферную
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		//3) удаляем исходную строку
		delete[] arr[i];
		//подменяем адрес исходной строки адресом новой строки
		arr[i] = buffer;

	}
	cols++;
}