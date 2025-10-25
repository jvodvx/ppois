#include "gtest/gtest.h"
#include "vector.h"
#include <sstream>
#include <cmath>
#include <limits>


TEST(VectorTest, ParameterizedConstructor) {
    vector v(1.5, 2.5, 3.5);
    EXPECT_DOUBLE_EQ(v.getX(), 1.5);
    EXPECT_DOUBLE_EQ(v.getY(), 2.5);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.5);
}

TEST(VectorTest, LengthCalculation) {
    vector v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.len(), 5);
}

TEST(VectorTest, AdditionOperator) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);
    vector result = v1 + v2;
    EXPECT_DOUBLE_EQ(result.getX(), 5);
    EXPECT_DOUBLE_EQ(result.getY(), 7);
    EXPECT_DOUBLE_EQ(result.getZ(), 9);
}

TEST(VectorTest, AdditionAssignmentOperator) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1.getX(), 5);
    EXPECT_DOUBLE_EQ(v1.getY(), 7);
    EXPECT_DOUBLE_EQ(v1.getZ(), 9);
}

TEST(VectorTest, UnaryMinusOperator) {
    vector v(1, -2, 3);
    vector result = -v;
    EXPECT_DOUBLE_EQ(result.getX(), -1);
    EXPECT_DOUBLE_EQ(result.getY(), 2);
    EXPECT_DOUBLE_EQ(result.getZ(), -3);
}

TEST(VectorTest, SubtractionOperator) {
    vector v1(5, 7, 9);
    vector v2(4, 5, 6);
    vector result = v1 - v2;
    EXPECT_DOUBLE_EQ(result.getX(), 1);
    EXPECT_DOUBLE_EQ(result.getY(), 2);
    EXPECT_DOUBLE_EQ(result.getZ(), 3);
}

TEST(VectorTest, CrossProduct) {
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    vector result = v1 * v2;
    EXPECT_DOUBLE_EQ(result.getX(), 0);
    EXPECT_DOUBLE_EQ(result.getY(), 0);
    EXPECT_DOUBLE_EQ(result.getZ(), 1);
}

TEST(VectorTest, ScalarMultiplication) {
    vector v(1, 2, 3);
    vector result = v * 2.5;
    EXPECT_DOUBLE_EQ(result.getX(), 2.5);
    EXPECT_DOUBLE_EQ(result.getY(), 5.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 7.5);
}

TEST(VectorTest, DivisionOperator) {
    vector v1(10, 20, 30);
    vector v2(2, 4, 5);
    vector result = v1 / v2;
    EXPECT_DOUBLE_EQ(result.getX(), 5);
    EXPECT_DOUBLE_EQ(result.getY(), 5);
    EXPECT_DOUBLE_EQ(result.getZ(), 6);
}

TEST(VectorTest, DotProductAndAngle) {
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    double cosine = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cosine, 0);
}

TEST(VectorTest, ComparisonOperators) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);
    vector v3(1, 2, 3);

    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_TRUE(v1 == v3);
    EXPECT_TRUE(v1 != v2);
}

TEST(VectorTest, StreamOutput) {
    vector v(1.5, 2.5, 3.5);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "(1.5, 2.5, 3.5)");
}

TEST(VectorTest, StreamInput) {
    vector v;
    std::stringstream ss("1.5 2.5 3.5");
    ss >> v;
    EXPECT_DOUBLE_EQ(v.getX(), 1.5);
    EXPECT_DOUBLE_EQ(v.getY(), 2.5);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.5);
}

TEST(VectorTest, EdgeCases) {
    vector v1(0, 0, 0);
    vector v2(1, 1, 1);

    // Test division by zero
    vector v3(1, 1, 1);
    vector zero(0, 0, 0);
    vector divResult = v3 / zero;
    EXPECT_TRUE(std::isinf(divResult.getX()) && std::isinf(divResult.getY()) && std::isinf(divResult.getZ()));
}

TEST(VectorTest, DefaultConstructor) {
    vector v;
    EXPECT_DOUBLE_EQ(v.getX(), 0);
    EXPECT_DOUBLE_EQ(v.getY(), 0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0);
}

TEST(VectorTest, SubtractionAssignmentOperator) {
    vector v1(5, 7, 9);
    vector v2(4, 5, 6);
    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1.getX(), 1);
    EXPECT_DOUBLE_EQ(v1.getY(), 2);
    EXPECT_DOUBLE_EQ(v1.getZ(), 3);
}

TEST(VectorTest, CrossProductAssignment) {
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    v1 *= v2;
    EXPECT_DOUBLE_EQ(v1.getX(), 0);
    EXPECT_DOUBLE_EQ(v1.getY(), 0);
    EXPECT_DOUBLE_EQ(v1.getZ(), 1);
}

TEST(VectorTest, ScalarMultiplicationAssignment) {
    vector v(1, 2, 3);
    v *= 2.5;
    EXPECT_DOUBLE_EQ(v.getX(), 2.5);
    EXPECT_DOUBLE_EQ(v.getY(), 5.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 7.5);
}

TEST(VectorTest, DivisionAssignmentOperator) {
    vector v1(10, 20, 30);
    vector v2(2, 4, 5);
    v1 /= v2;
    EXPECT_DOUBLE_EQ(v1.getX(), 5);
    EXPECT_DOUBLE_EQ(v1.getY(), 5);
    EXPECT_DOUBLE_EQ(v1.getZ(), 6);
}

TEST(VectorTest, DotProductParallelVectors) {
    vector v1(1, 0, 0);
    vector v2(2, 0, 0);
    double cosine = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cosine, 1.0);
}

TEST(VectorTest, DotProductOppositeVectors) {
    vector v1(1, 0, 0);
    vector v2(-1, 0, 0);
    double cosine = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cosine, -1.0);
}

TEST(VectorTest, DotProductArbitraryVectors) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);
    double expected = (1 * 4 + 2 * 5 + 3 * 6) / (sqrt(1 + 4 + 9) * sqrt(16 + 25 + 36));
    double cosine = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cosine, expected);
}

TEST(VectorTest, ComparisonOperatorsWithEqualVectors) {
    vector v1(1, 2, 3);
    vector v2(1, 2, 3);

    EXPECT_FALSE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
}

TEST(VectorTest, ComparisonOperatorsWithDifferentVectors) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);

    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
}

TEST(VectorTest, ScalarMultiplicationFromRight) {
    vector v(1, 2, 3);
    vector result = 2.5 * v;
    EXPECT_DOUBLE_EQ(result.getX(), 2.5);
    EXPECT_DOUBLE_EQ(result.getY(), 5.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 7.5);
}

TEST(VectorTest, EdgeCaseZeroVector) {
    vector zero(0, 0, 0);
    vector v(1, 2, 3);

    // Длина нулевого вектора
    EXPECT_DOUBLE_EQ(zero.len(), 0);

    // Сравнение с нулевым вектором
    EXPECT_TRUE(zero < v);
    EXPECT_TRUE(zero <= v);
    EXPECT_FALSE(zero > v);
    EXPECT_FALSE(zero >= v);

    // Скалярное произведение с нулевым вектором
    double cosine = zero ^ v;
    EXPECT_TRUE(std::isnan(cosine)); // деление на ноль даст NaN
}

TEST(VectorTest, NormalizationEdgeCases) {
    vector zero(0, 0, 0);
    vector v(3, 4, 0);

    // Скалярное произведение с нормализацией
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    double cosine = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cosine, 0);

    // Скалярное произведение с самим собой
    cosine = v1 ^ v1;
    EXPECT_DOUBLE_EQ(cosine, 1.0);
}

TEST(VectorTest, CombinedOperations) {
    vector v1(1, 2, 3);
    vector v2(4, 5, 6);
    vector v3(2, 1, 0);

    // Комбинированные операции
    vector result = (v1 + v2) * 2.0 - v3;
    EXPECT_DOUBLE_EQ(result.getX(), 8);  // (1+4)*2 - 2 = 10-2=8
    EXPECT_DOUBLE_EQ(result.getY(), 13); // (2+5)*2 - 1 = 14-1=13? Проверим: (2+5)=7*2=14-1=13
    EXPECT_DOUBLE_EQ(result.getZ(), 18); // (3+6)*2 - 0 = 18
}

TEST(VectorTest, ChainOperations) {
    vector v1(1, 1, 1);
    vector v2(2, 2, 2);
    vector v3(3, 3, 3);

    v1 += v2 += v3;
    EXPECT_DOUBLE_EQ(v1.getX(), 6);
    EXPECT_DOUBLE_EQ(v1.getY(), 6);
    EXPECT_DOUBLE_EQ(v1.getZ(), 6);
}

TEST(VectorTest, SelfOperations) {
    vector v(1, 2, 3);

    // Операции с самим собой
    v += v;
    EXPECT_DOUBLE_EQ(v.getX(), 2);
    EXPECT_DOUBLE_EQ(v.getY(), 4);
    EXPECT_DOUBLE_EQ(v.getZ(), 6);

    vector v2 = v - v;
    EXPECT_DOUBLE_EQ(v2.getX(), 0);
    EXPECT_DOUBLE_EQ(v2.getY(), 0);
    EXPECT_DOUBLE_EQ(v2.getZ(), 0);
}

TEST(VectorTest, CrossProductProperties) {
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    vector v3(0, 0, 1);

    // Антикоммутативность: a × b = - (b × a)
    vector cross1 = v1 * v2;
    vector cross2 = v2 * v1;
    EXPECT_TRUE(cross1 == -cross2);

    // Векторное произведение ортогонально исходным векторам
    double dot1 = cross1 ^ v1;
    double dot2 = cross1 ^ v2;
    EXPECT_DOUBLE_EQ(dot1, 0);
    EXPECT_DOUBLE_EQ(dot2, 0);
}

TEST(VectorTest, FloatingPointPrecision) {
    vector v1(0.1, 0.2, 0.3);
    vector v2(0.4, 0.5, 0.6);

    // Тестирование с плавающей точкой
    vector sum = v1 + v2;
    EXPECT_NEAR(sum.getX(), 0.5, 1e-10);
    EXPECT_NEAR(sum.getY(), 0.7, 1e-10);
    EXPECT_NEAR(sum.getZ(), 0.9, 1e-10);

    // Умножение и деление
    vector scaled = v1 * 10.0;
    EXPECT_NEAR(scaled.getX(), 1.0, 1e-10);
    EXPECT_NEAR(scaled.getY(), 2.0, 1e-10);
    EXPECT_NEAR(scaled.getZ(), 3.0, 1e-10);
}

TEST(VectorTest, Normalization) {
    vector v(3, 4, 0);
    double length = v.len();

    // Проверка длины
    EXPECT_DOUBLE_EQ(length, 5);

    // Нормализованный вектор
    vector normalized = v / vector(length, length, length);
    EXPECT_DOUBLE_EQ(normalized.len(), 1.0);
}

TEST(VectorTest, OrthogonalVectors) {
    vector v1(1, 0, 0);
    vector v2(0, 1, 0);
    vector v3(0, 0, 1);

    // Ортогональные векторы должны иметь скалярное произведение 0
    EXPECT_DOUBLE_EQ(v1 ^ v2, 0);
    EXPECT_DOUBLE_EQ(v1 ^ v3, 0);
    EXPECT_DOUBLE_EQ(v2 ^ v3, 0);

    // Векторное произведение ортогональных векторов
    vector cross = v1 * v2;
    EXPECT_TRUE(cross == v3 || cross == -v3);
}

TEST(VectorTest, AssignmentChain) {
    vector a(1, 2, 3);
    vector b(4, 5, 6);
    vector c(7, 8, 9);

    // Цепочка присваиваний
    a = b = c;
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(b == c);
}

TEST(VectorTest, MixedTypeOperations) {
    vector v(1, 2, 3);

    // Различные скалярные значения
    vector result1 = v * 2;
    vector result2 = v * 0.5;
    vector result3 = v * -1;

    EXPECT_DOUBLE_EQ(result1.getX(), 2);
    EXPECT_DOUBLE_EQ(result2.getX(), 0.5);
    EXPECT_DOUBLE_EQ(result3.getX(), -1);
}

TEST(VectorTest, EdgeCaseVectors) {
    // Векторы с очень большими значениями
    vector large(1e10, 2e10, 3e10);
    EXPECT_NEAR(large.len(), sqrt(1e20 + 4e20 + 9e20), 1e5);

    // Векторы с очень маленькими значениями
    vector small(1e-10, 2e-10, 3e-10);
    EXPECT_NEAR(small.len(), sqrt(1e-20 + 4e-20 + 9e-20), 1e-15);

    // Смешанные знаки
    vector mixed(1, -2, 3);
    EXPECT_DOUBLE_EQ(mixed.len(), sqrt(1 + 4 + 9));
}

TEST(VectorTest, CopyBehavior) {
    vector original(1, 2, 3);
    vector copy = original;

    // Проверка, что копирование работает правильно
    EXPECT_TRUE(original == copy);

    // Изменение копии не должно влиять на оригинал
    copy += vector(1, 1, 1);
    EXPECT_FALSE(original == copy);
    EXPECT_DOUBLE_EQ(original.getX(), 1);
    EXPECT_DOUBLE_EQ(copy.getX(), 2);
}

TEST(VectorTest, MathematicalProperties) {
    vector a(1, 2, 3);
    vector b(4, 5, 6);
    vector c(7, 8, 9);

    // Дистрибутивность: a × (b + c) = a × b + a × c
    vector left = a * (b + c);
    vector right = a * b + a * c;
    EXPECT_TRUE(left == right);

    // Скалярное произведение коммутативно: a · b = b · a
    double dot1 = a ^ b;
    double dot2 = b ^ a;
    EXPECT_DOUBLE_EQ(dot1, dot2);
}

TEST(VectorTest, ExceptionalCases) {
    vector zero(0, 0, 0);
    vector v(1, 2, 3);

    // Деление на очень маленькое число
    vector tiny(1e-308, 1e-308, 1e-308);
    if (tiny.getX() != 0) { // избегаем деления на 0
        vector division = v / tiny;
        EXPECT_TRUE(std::isinf(division.getX()) || std::isinf(division.getY()) || std::isinf(division.getZ()));
    }

    // Векторное произведение с нулевым вектором
    vector cross = zero * v;
    EXPECT_DOUBLE_EQ(cross.getX(), 0);
    EXPECT_DOUBLE_EQ(cross.getY(), 0);
    EXPECT_DOUBLE_EQ(cross.getZ(), 0);

    // Скалярное произведение с нулевым вектором
    double dot = zero ^ v;
    EXPECT_TRUE(std::isnan(dot)); // Должно быть NaN из-за деления на 0
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}