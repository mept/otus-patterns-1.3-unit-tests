#include <iostream>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>
#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

vector<double> solve(double a, double b, double c)
{
    double d, x1, x2;
    vector<double> result;
    const double epsilon = 0.001;

    // Проверяем, что на вход подаётся число
    if (std::isnan(a)) throw runtime_error("Аргумент 'a' должен быть числом");
    if (std::isnan(b)) throw runtime_error("Аргумент 'b' должен быть числом");
    if (std::isnan(c)) throw runtime_error("Аргумент 'c' должен быть числом");

    // Сравниваем "a" с эпсилоном, если модуль от "a" меньше - считаем нулём
    if (fabs(a) < epsilon) throw runtime_error("Аргумент 'a' не может быть равен 0");

    d = b * b - 4 * a * c;
    cout << "Дискриминант: " << d << endl;

    if (fabs(d) < epsilon) // Сравниваем дискриминант с эпсилоном, если модуль от дискриминанта меньше - считаем нулём
    {
        x1 = -(b / (2 * a));
        cout << "x1 = x2 = " << x1 << endl;

        result.push_back(x1);
    }
    else if (d < 0)
    {
        cout << "D < 0, корней уравнения не существует" << endl;
    }
    else if (d > 0)
    {
        x1 = ((-b) + sqrt(d)) / (2 * a);
        x2 = ((-b) - sqrt(d)) / (2 * a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;

        result.push_back(x1);
        result.push_back(x2);
    }
    
    return result;
}

// тесты

TEST_CASE("3. тест, который проверяет, что для уравнения x^2+1 = 0 корней нет (возвращается пустой массив)") {
    cout << "Выполнение теста №3..." << endl;
    vector<double> expected = {};
    CHECK( solve(1, 0, 1) == expected );
    cout << endl;
}

TEST_CASE("5. Написать тест, который проверяет, что для уравнения x^2-1 = 0 есть два корня кратности 1 (x1=1, x2=-1)") {
    cout << "Выполнение теста №5..." << endl;
    vector<double> expected = {1, -1};
    CHECK( solve(1, 0, -1) == expected );
    cout << endl;
}

TEST_CASE("7. Написать тест, который проверяет, что для уравнения x^2+2x+1 = 0 есть один корень кратности 2 (x1= x2 = -1)") {
    cout << "Выполнение теста №7..." << endl;
    vector<double> expected = {-1.00005};
    CHECK( solve(1, 2.0001, 1) == expected );
    cout << endl;
}

TEST_CASE("9. Написать тест, который проверяет, что коэффициент a не может быть равен 0. В этом случае solve выбрасывает исключение") {
    cout << "Выполнение теста №9..." << endl;
    CHECK_THROWS_WITH(solve(0, 1, 1), "Аргумент 'a' не может быть равен 0");
    cout << endl;
}

TEST_CASE("13. Написать тест с использованием не числовых значений на все коэффициенты. solve должен выбрасывать исключение") {
    cout << "Выполнение теста №13..." << endl;
    CHECK_THROWS_WITH(solve(NAN, 1, 1), "Аргумент 'a' должен быть числом");
    CHECK_THROWS_WITH(solve(1, NAN, 1), "Аргумент 'b' должен быть числом");
    CHECK_THROWS_WITH(solve(1, 1, NAN), "Аргумент 'c' должен быть числом");
    cout << endl;
}