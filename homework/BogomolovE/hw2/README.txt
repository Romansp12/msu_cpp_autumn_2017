==============================================
Работу выполнили Богомолов Эмиль, группа BD-11
==============================================

В этом проекте реализована программа вычисляющая выражение содержащае арифметические операции над целыми числами. 

Детали реализации:

1) Шаг алгоритма состоит во взятии токена, который определяет следующую элементарную часть в введенном выражении. Это может быть число, либо арифметическая операция,
либо специальный символ
2) Получив очередной токен, методом рекурсивного спуска вычисляется промежуточное значение выражения. Рекурсивный спуск осуществляется в три этапаЖ
	1. Определние выражения со сложением/вычитанием: expr = term | expr + term | expr - term
	2. Определние выражения со умножением/делением: term = prim | term * prim | term / prim
	3. Определение числа: prim = number | -number  
	(В проекте это осуществляется функцией atoi(), позволяющей получить целое число с места некоторого указателя. 
	Для этого на всех этапах работы рекурсивного спуска пердаём в функции указатель на начало считанного токена prev)
3) Новые токены извлекаются до момента достижения окончания строки, либо до нахождения недопустимого символа.


