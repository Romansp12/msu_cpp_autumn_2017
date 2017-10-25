#Домашнее задание №4

Класс-матрица, тип элементов double. В конструкторе задается количество рядов и строк. Поддерживаются оперции: получить количество строк/столбцов, получить конкретный элемент, умножить на вектор (в качестве вектора использовать класс ```std::vector<double>```), умножить на число, сравнение на равенство/неравенство. В случае ошибки выхода за границы будет такая обработка ошибки: ```assert(!"index out of range")```

Сборку производить с помощью утилиты make.
```
	make
```
Запуск осуществляется с помощью
```
	./matrix
```
Пример использования класса

```
const size_t rows = 5;
const size_t cols = 3;

Matrix m(cols, rows);

m[1][2] = 5; // колонка 1, строка 2
double x = m[3][1];

m *= 3; // умножение на число

std::vector<double> v = { 1, 2, 3 };
m *= v; // умножение на вектор

Matrix m1(cols, rows);

if (m1 == m)
{
}
```
Код покрыт тестами, которые запускаются при старте программы.

