#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int H; // "пустой набор H", возможно что-то другое имеется ввиду

class ABC
{
    unsigned int _abcBits[2]; // Приватный массив из пары целых чисел без знака

public:

    // В 0 числе массива сохраняется весь латинский алфавит
    // В 1 числе массива сохраняются заглавные буквы из строки-аргумента
    ABC(std::string str)
    {
        // Выставляем все биты числа в 1. int - 4 байта или 32 бита, получается записываем 32 еденицы
        _abcBits[0] = ~0;
        // Сдвигаем биты на шесть позиций вправо. Получаем вначале шесть нулей, а все остальные еденицы
        _abcBits[0] >>= 6;
        // Выставляем все биты в 1.
        _abcBits[1] = 0;
        for (int i = 0; str[i] != '\0'; i++) // Пробегаемся по всей строке
        {
            if (str[i] >= 'A' && str[i] <= 'Z') // Если текущий символ - заглавная буква
            {
                // Первый бит будет символизировать - 'A', 26 бит - 'Z'.
                // В правой части выражения после символа | в случае с 'A' получаем число в двоичной системе 0x00...0001
                // В случае с Z - 0x0000001000...00 (последние 6 битов лишние, 26ой бит - 1, остальные нули)
                // Оператор | добавляет в переменную алфавита еще одну еденицу, в нужной позиции (| - оператор сложения)
                _abcBits[1] = _abcBits[1] | (1 << (str[i] - 'A'));
            }
        }
    }

    // Перегрузка оператора ()
    // Вычисляет расстояние Хэмминга и возвращает результат
    operator H() const
    {
        int count = 0, last_x, last_y;
        int x = _abcBits[0], y = _abcBits[1];

        while(x > 0 || y > 0)
        {
            last_x = x & 1; // Проверяем последний бит,
            last_y = y & 1; // если там еденица, то вернется 1, если 0, то 0
            if (last_x != last_y)   // Соответственно увеличиваем счетчик если последние биты чисел разные
                count++;            // Выше сдвигали исходный алфавит на 6 позиций вправо, что бы 
                                    // неиспользуемые 6 битов не увеличили здесь счетчик
            x = x >> 1; // Удаляем последний бит,
            y = y >> 1; // что бы выше можно было рассмотреть следующий
        }
        return count;
    }

    // Перегрузка оператора &. Маскирует переменную с заглавными буквами
    unsigned int operator&()
    {
        return _abcBits[1];
    }

    // Дружественная перегрузка оператора <<. Обеспечивает вывод вычислений
    // Но не выводит "операнды расчетной формулы", не совсем понятно что это и в каком виде выводить
    // Используем здесь обе перегрузки. В результате в переменной instance не ссылка на экземпляр
    // класса, а число int, хранящее заданный набор заглавных букв
    friend std::ostream	&operator<<( std::ostream &ostr, ABC &instance )
    {
        // Здесь перегрузка оператора (), кастует число с набором букв в количество
        // отсутствующих заглавных букв
        ostr << (H)instance;
        return ostr;
    }
    
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid input" << std::endl;
        return -1;
    }

    ABC a(argv[1]);
    std::cout << a << std::endl;
    return 0;
}