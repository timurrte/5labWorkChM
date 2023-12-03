#include <iostream>
#include <cmath>
#include <functional>

double f(double x) {
    return (sqrt(1.1 * pow(x, 2) + 0.9)) / (1.6 + sqrt(0.8 * pow(x, 2) + 1.4));
}

double f2(double x) {
    return (cos(0.8 * x + 1)) / (1.4 + sin(0.3 * x + 0.5));
}

double integrate(std::function<double(double)> func, double min_lim, double max_lim, int n) {
    double integral = 0.0;
    double step = (max_lim - min_lim) / n;
    for (double x = min_lim; x < max_lim - step; x += step) {
        integral += step * func(x + step / 2);


    }
    return integral;
}

void method_of_rectangles(std::function<double(double)> func, double min_lim, double max_lim, int n1, int n2) {
    double a = std::abs(integrate(func, min_lim, max_lim, n1));
    double b = std::abs(integrate(func, min_lim, max_lim, n2));
    if (a > b) {
        std::swap(a, b);
    }
    std::cout << "Rectangles:\n";
    std::cout << "\t" << n1 << "\t" << a << "\t" << b << std::endl;
}

double integrate_trapezium(std::function<double(double)> func, double min_lim, double max_lim, int n) {
    double integral = 0.0;
    double step = (max_lim - min_lim) / n;
    double l = 0.0;
    for (double x = min_lim; x < max_lim - step; x += step) {
        integral += step * (func(x) + func(x + step)) / 2;
    }
    return integral;
}

void trapezium_method(std::function<double(double)> func, double min_lim, double max_lim, int n1, int n2) {
    double a = std::abs(integrate_trapezium(func, min_lim, max_lim, n1));
    double b = std::abs(integrate_trapezium(func, min_lim, max_lim, n2));
    if (a > b) {
        std::swap(a, b);
    }
    std::cout << "Trapezium:\n";
    std::cout << "\t" << n1 << "\t" << a << "\t" << b << std::endl;
}

double integrate_simpson(std::function<double(double)> func, double min_lim, double max_lim, int n) {
    double integral = 0.0;
    double step = (max_lim - min_lim) / n;
    for (double x = min_lim + step / 2; x < max_lim - step / 2; x += step) {
        integral += step / 6 * (func(x - step / 2) + 4 * func(x) + func(x + step / 2));
    }
    return integral;
}

void simpson_method(std::function<double(double)> func, double min_lim, double max_lim, int n1, int n2) {
    double a = std::abs(integrate_simpson(func, min_lim, max_lim, n1));
    double b = std::abs(integrate_simpson(func, min_lim, max_lim, n2));
    if (a > b) {
        std::swap(a, b);
    }
    std::cout << "Simpson:\n";
    std::cout << "\t" << n1 << "\t" << a << "\t" << b << std::endl;
}

int main(void) {
    int n1 = 10;
    int n2 = 20;

    std::cout << "First integral" << std::endl;
    method_of_rectangles(f, 0.6, 2.4, n1, n2);
    simpson_method(f, 0.6, 2.4, n1, n2);
    trapezium_method(f, 0.6, 2.4, n1, n2);
    simpson_method(f, 0.6, 2.4, 100, 100); // точне значення інтегралу 0.966241

    std::cout << "Second integral" << std::endl;
    method_of_rectangles(f2, 0.4, 1.4, n1, n2);
    simpson_method(f2, 0.4, 1.4, n1, n2);
    trapezium_method(f2, 0.4, 1.4, n1, n2);
    simpson_method(f2, 0.4, 1.4, 1000, 1000); // точне значення інтегралу 0.659921
}

