#define CATCH_CONFIG_MAIN
#include "matrix.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Different types") {
    using dm = matrix<double>;
    const auto dminst = dm();
    using im = matrix<int>;
    const auto iminst = im();
    using uim = matrix<unsigned int>;
    const auto uiminst = uim();
    using fm = matrix<float>;
    const auto fminst = fm();
    using bm = matrix<bool>;
    const auto bminst = bm();
}
TEST_CASE("Creating Matrices") {

    matrix<double> m;
    REQUIRE(m.rows() == 0);
    REQUIRE(m.cols() == 0);
    matrix<double> p(7, 9);
    REQUIRE(p.rows() == 7);
    REQUIRE(p.cols() == 9);

    for (int i = 0; i < 7; ++i) {
        REQUIRE(p[i] == std::vector<double>(9, 0));
    }
    for (int i = 0; i < 9; ++i) {
        REQUIRE(p.column(i) == std::vector<double>(7, 0));
    }
}

TEST_CASE("Assigning Values") {
    auto m = matrix<double>::identity(6);

    for (int i = 0; i < 6; i++) {
        for (int c = 0; c < 6; c++) {
            REQUIRE(m[i][c] == (i == c ? 1.0 : 0.0));
        }
    }

    m.fill(4);
    for (int i = 0; i < 6; i++) {
        for (int c = 0; c < 6; c++) {
            REQUIRE(m[i][c] == 4);
        }
    }
}

TEST_CASE("Multiplication") {
    auto m = matrix<double>::identity(6);
    auto r = m * 3;

    for (int i = 0; i < 6; i++) {
        for (int c = 0; c < 6; c++) {
            REQUIRE(r[i][c] == (i == c ? 3.0 : 0.0));
        }
    }

    m = matrix<double>(2, 1);
    r = matrix<double>(1, 2);
    m[1][0] = 1;
    r[0][0] = 2;
    r[0][1] = 3;
    auto p = m * r;
    REQUIRE(p.cols() == 2);
    REQUIRE(p.rows() == 2);
    REQUIRE(p[0][0] == 0);
    REQUIRE(p[0][1] == 0);
    REQUIRE(p[1][0] == 2);
    REQUIRE(p[1][1] == 3);

    bool except = false;
    try {
        matrix<double>::identity(7) * m;
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);

    m = matrix<double>::identity(6);
    m *= 3;
    for (int i = 0; i < 6; i++) {
        for (int c = 0; c < 6; c++) {
            REQUIRE(m[i][c] == (i == c ? 3.0 : 0.0));
        }
    }

    m = matrix<double>(2, 1);
    r = matrix<double>(1, 2);
    m[1][0] = 1;
    r[0][0] = 2;
    r[0][1] = 3;
    m *= r;
    REQUIRE(m.cols() == 2);
    REQUIRE(m.rows() == 2);
    REQUIRE(m[0][0] == 0);
    REQUIRE(m[0][1] == 0);
    REQUIRE(m[1][0] == 2);
    REQUIRE(m[1][1] == 3);
}

TEST_CASE("Addition") {
    auto m = matrix<double>::identity(3);
    auto l = matrix<double>::identity(3);
    auto r = m + l;

    REQUIRE(r.cols() == 3);
    REQUIRE(r.rows() == 3);
    for (int i = 0; i < 3; i++) {
        for (int c = 0; c < 3; c++) {
            REQUIRE(r[i][c] == (i == c ? 2.0 : 0.0));
        }
    }

    std::vector<double> row(3, 9.0);
    l.add_row(row);
    bool except = false;
    try {
        r = l + m;
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);

    m += r;
    for (int i = 0; i < 3; i++) {
        for (int c = 0; c < 3; c++) {
            REQUIRE(m[i][c] == (i == c ? 3.0 : 0.0));
        }
    }
}

TEST_CASE("Subtraction") {
    auto m = matrix<double>::identity(3);
    auto l = matrix<double>::identity(3);
    auto r = m - l;

    REQUIRE(r.cols() == 3);
    REQUIRE(r.rows() == 3);
    for (int i = 0; i < 3; i++) {
        for (int c = 0; c < 3; c++) {
            REQUIRE(r[i][c] == 0.0);
        }
    }

    std::vector<double> row(3, 9.0);
    l.add_row(row);
    bool except = false;
    try {
        r = l - m;
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);

    r = matrix<double>(3, 3);
    r.fill(2);
    m -= r;
    for (int i = 0; i < 3; i++) {
        for (int c = 0; c < 3; c++) {
            REQUIRE(m[i][c] == (i == c ? -1 : -2));
        }
    }
}

TEST_CASE("Transpose") {
    matrix<double> m(2, 1);
    m[0][0] = 1;
    m[1][0] = 0;
    const auto t = m.transpose();
    REQUIRE(t.rows() == 1);
    REQUIRE(t.cols() == 2);
    REQUIRE(t[0][1] == 0);
    REQUIRE(t[0][0] == 1);
}

TEST_CASE("Determinant") {
    matrix<double> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 1;
    m[1][1] = 5;
    // ab-dc
    REQUIRE(m.determinant() == 3);

    matrix<double> r(4, 3);
    r.fill(2);
    bool except = false;
    try {
        r.determinant();
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);

    std::vector<double> a = {6, 1, 1};
    std::vector<double> b = {4, -2, 5};
    std::vector<double> c = {2, 8, 7};
    std::vector<std::vector<double>> vec = {a, b, c};

    matrix<double> d(vec);
    REQUIRE(d.determinant() == -306.0);
}

TEST_CASE("Inverse") {
    std::vector<std::vector<double>> vec = {{3, 3.5}, {3.2, 3.6}};
    matrix<double> m(vec);
    auto im = m.inverse();
    REQUIRE(im[0][0] <= -8.9);
    REQUIRE(im[0][0] >= -9.0);
    REQUIRE(im[0][1] >= 8.65);
    REQUIRE(im[0][1] <= 8.85);
    REQUIRE(im[1][0] <= 8.1);
    REQUIRE(im[1][0] >= 7.9);
    REQUIRE(im[1][1] >= -7.6);
    REQUIRE(im[1][1] <= -7.4);

    bool except = false;
    m = matrix<double>(2, 2);
    m[0][0] = 2;
    m[1][1] = 2;
    m[0][1] = 1;
    m[1][0] = 4;
    try {
        m.inverse();
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);
}

TEST_CASE("Equality") {
    auto m = matrix<double>::identity(2);
    REQUIRE(m == matrix<double>::identity(2));
    m[0][0] = 7;
    REQUIRE(m != matrix<double>::identity(2));
    std::vector<double> v = {5, 6};
    m.add_row(v);
    REQUIRE(m != matrix<double>::identity(2));
}

TEST_CASE("Add Row") {
    auto m = matrix<double>::identity(2);
    bool except = false;
    std::vector<double> v = {1, 2};
    try {
        m.add_row(v);
        REQUIRE(m.rows() == 3);
        REQUIRE(m.cols() == 2);
        m.add_col(v);
    } catch (matrix_exception &e) {
        except = true;
    }
    REQUIRE(except);
}
