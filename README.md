# SubplotArea
Этот учебный проект - приложение для поиска площади фигуры между 3 кривыми. Он написан на C++ в Visual Studio с использованием SFML 2.5.1.
# Подключение и использование
Для запуска проекта со стандартными кривыми, скачайте архив [Release.zip](https://github.com/KIrillPal/SubplotArea/blob/main/Release.zip) из корня проекта и запустите в нём файл Figures.exe. После ввода откроется консоль и предложит выбрать точность получения площади (Так требовалось в ТЗ). Затем можно перейти к рассмотрению графика, нажав кнопку 'Tab' и вручную развернув вкладку с графиком (Он тоже требовался в ТЗ).

В консоли высвечивается та же площадь, что должна закрашена на графике. Окно с графиками успешно растягивается.

# Структура проекта
Здесь описано, какие файлы содержатся в проекте и их предназначение в общих чертах.
### 1. Figures.cpp
Это файл, содержащий функцию main. Он отвечает за любые действия с консолью и окном. Не принимает участие в каких бы то ни было расчётах.

### 2. FloatMap.cpp и FloatMap.h
Это ядро вычислений площади. Там записаны все исходные функции и алгоритм поиска площадей для кривых.

### 3. DrawingMap.cpp и DrawingMap.h
В этом файле происходит отрисовка графиков по данным FloatMap.

# Модификация проекта
Одна из главных фишек этого проекта - универсальность. Три графика задаются формулами в файле FloatMap.cpp. 
В самом начале файла расположены функции f1, f2, f3. Меняя их, можно изменять кривые для расчёта и отображения. Также с ними нужно изменять функции d11, d12, d13, d21, d22, d23. Это функции производных первого и второго порядка. Они необходимы для определения точек перегиба функций. Функция d11 - производная 1 порядка функции f1, а d12 - производная 1 порядка f2. Аналогично с другими функциями d.

Однако существует ограничение на функции, вводимые в f. Из-за особенности реализации функции area_between функция f1 всегда должна быть верхней частью искомой фигуры. Также функции не должны пересекаться в точках, не являющихся вершинами фигуры.

# Замечания
Для запуска проекта в Visual Studio необходим доступ среды к SFML 2.5.1. Эта библиотека должна находиться по пути `D:\Program Files\SFML-2.5.1`. Чтобы выбрть другую папку для SFML, зайдите в `Проект -> C/C++ -> Общие -> Дополнитеьные каталоги включаемых файлов`, а затем измените каталог и версию на нужное. Аналогично нужно поменять данные по пути `Проект -> Компоновщик -> Общие -> Дополнитеьные каталоги библиотек`.

# Особенности проекта

Этот учебный проект был логичесим продолжением проекта [Figures](https://github.com/KIrillPal/Figures). Отображение графиков качественно улучшено благодаря использованию производной. Однако довольно неудобен способ записи функций и открытия окна с кривыми (нажать таб и вручную открыть вкладку).
