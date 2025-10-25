#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include "gtest/gtest.h"        

#include <iostream>

class vector {
private:
    double x, y, z;

public:
    vector();
    vector(double x, double y, double z);

    // Получение координат
    double getX() const;
    double getY() const;
    double getZ() const;

    // Основные операции
    double len() const;

    // Операторы
    vector operator+(const vector& v) const;
    vector& operator+=(const vector& v);
    vector operator-() const;
    vector operator-(const vector& v) const;
    vector& operator-=(const vector& v);
    vector operator*(const vector& v) const;
    vector& operator*=(const vector& v);
    vector operator*(double n) const;
    vector& operator*=(double n);
    vector operator/(const vector& v) const;
    vector& operator/=(const vector& v);
    double operator^(const vector& v) const;
    friend vector operator*(double n, const vector& v);

    // Операторы сравнения
    bool operator>(const vector& v) const;
    bool operator>=(const vector& v) const;
    bool operator<(const vector& v) const;
    bool operator<=(const vector& v) const;
    bool operator==(const vector& v) const;
    bool operator!=(const vector& v) const;

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const vector& v);
    friend std::istream& operator>>(std::istream& is, vector& v);
};


#endif