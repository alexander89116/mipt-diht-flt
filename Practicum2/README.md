# Практикум №2. Теория формальных языков

## [Задание. Вариант 2](https://github.com/alexander89116/flt_mipt/blob/master/Practicum2/Practicum2_tasks.pdf)

Построить анализатор для грамматик с помощью [алгоритма Эрли.](https://github.com/alexander89116/flt_mipt/blob/master/Practicum2/earley.h)

## Запуск анализатора

Собираем анализатор
```
g++ main.cpp -o analyzer
```
Далее на вход подаём грамматику со стартовым символом 'A' и слово в таком формате:
```
6
A-Aa
D-cD
A-AAb
A-C
C-Dd
D-
cdcdcccdbbaaa
```

## [Запуск тестов](https://github.com/alexander89116/flt_mipt/blob/master/Practicum2/run_tests.sh)
```
bash run_tests.sh
```
- Test 0-3 --- грамматики из условия
- Test 4-5 --- ПСП
- Test 6-7 --- палиндромы
- Test 8-9 --- алгебраические выражения

Всего 10 тестов. Результаты тестирования выглядят так (для грамматики моего варианта):
```
Test 0:
6
A-Aa
D-cD
A-AAb
A-C
C-Dd
D-
cdcdcccdbbaaa
correct
Test result: Ok

Test 1:
6
A-Aa
D-cD
A-AAb
A-C
C-Dd
D-
acdcccdba
incorrect
Test result: Ok
```
