#include<iostream>
using namespace std;

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T**& arr, const int rows, const int cols = 0);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void FillRand(double** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
template<typename T> void Print(T arr[], const int n);
template<typename T> void Print(T** arr, const int rows, const int cols);

template<typename T> T* push_back(T arr[], int& n, const T value);
template<typename T> T* push_front(T arr[], int& n, const T value);
template<typename T> T* insert(T arr[], int& n, const T value, const int index);

template<typename T> T* pop_back(T arr[], int& n);
template<typename T> T* pop_front(T arr[], int& n);

template<typename T> T** push_row_back(T** arr, int& rows, const int cols);
template<typename T> T** push_row_front(T** arr, int& rows, const int cols);              //сделала самостоятельно
template<typename T> T** insert_row(T** arr, int& rows, const int cols, const int index); 

//pop_row_back
//pop_row_front
//erase_row

template<typename T>void push_col_back(T** arr, const int rows, int& cols);
template<typename T>void push_col_front(T** arr, const int rows, int& cols);                                //сделала самостоятельно


//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

#define DATATYPE double
typedef int DataType;


void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	DataType* arr = new DataType[n];

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "Введите добавляемое значение: "; cin >> value;

	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	//arr = insert(arr, n, value, index);
	//Print(arr, n);
	Print(arr = insert(arr, n, value, index), n);


	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;

#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите колисчество строк: "; cin >> rows;
	cout << "Введите колисчество элементов строки: "; cin >> cols;

	DataType** arr = Allocate<int>(rows, cols);



	///////////////////////////////////////////////////////////////

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 1000);
	Print(arr, rows, cols);



	push_col_back(arr, rows, cols);
	for (int i = 0; i < rows; i++)arr[i][cols - 1] = rand() % 1000;
	Print(arr, rows, cols);

	push_col_front(arr, rows, cols);
	for (int i = 0;i < rows;i++)arr[i][0] = rand() % 1000;
	Print(arr, rows, cols);



	int index;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	//////////////////////////////////////////////////////////

	Clear(arr, rows, cols);

#endif // DYNAMIC_MEMORY_2

}

template<typename T>T** Allocate(const int rows, const int cols)
{
	//////////////////////////////////////////////////////////
	///    Объявление двумерного динамического массива     ///
	//////////////////////////////////////////////////////////

	//1) создаем массив указателей:
	T** arr = new T * [rows];

	//2) выделяем память под строки:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}
	return arr;
}
template<typename T>void Clear(T**& arr, const int rows, const int cols)
{
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

	//3) зануляем указатель на массив
	arr = nullptr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{

	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;

	}

}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		arr[i] /= 100;
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
void FillRand(double** arr, const int rows, const int cols, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double(rand() % (maxRand - minRand) + minRand) / 100;
		}
	}
}

template<typename T> void Print(T arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0;i < n;i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

template<typename T> void Print(T** arr, const int rows, const int cols)
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

template<typename T> T* push_back(T arr[], int& n, const T value)
{
	//1) создаем буферный массив нужного размера
	T* buffer = new T[n + 1];

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
template<typename T> T* push_front(T arr[], int& n, const T value)
{
	//1) 
	T* buffer = new T[n + 1];
	//2)
	for (int i = 0;i < n;i++)
	{
		buffer[i + 1] = arr[i];
	}
	//3)
	delete[] arr;

	//4)
	buffer[0] = value;

	//5)
	n++;

	return buffer;
}

template<typename T> T* insert(T arr[], int& n, const T value, const int index)
{
	T* buffer = new T[n + 1]{};
	for (int i = 0; i < n; i++)buffer[i < index ? i : i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template<typename T>T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей нужного размера:
	T** buffer = new T* [rows + 1];

	//2) Копируем адреса строк в новый массив
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив указателей
	delete[]arr;


	//4) Добавляем добавляемую строку
	buffer[rows] = new T[cols]{};

	//5) после добавления строки, количество строк увеличивается на 1:
	rows++;

	//6)  Возвращаем новый массив
	return buffer;
}
template<typename T> T** push_row_front(T** arr, int& rows, const int cols)
{
	T** buffer = new T* [rows + 1];
	for (int i = 0; i < rows; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = new T[cols] {};
	rows++;
	return buffer;
}

template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index)
{
	if (index<0 || index >rows)
	{
		cout << "Error: Out of range exception" << endl;
		return arr;
	}
	T** buffer = new T * [rows + 1] {};
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[index] = new T[cols]{};
	rows++;
	return buffer;
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) создаем буферную строку нужного размера
		T* buffer = new T[cols + 1]{};
		//2) копируем элементы из исходной строки в буферную
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		//3) удаляем исходную строку
		delete[] arr[i];
		//подменяем адрес исходной строки адресом новой строки
		arr[i] = buffer;

	}
	cols++;
}
template<typename T> void push_col_front(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j + 1] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}