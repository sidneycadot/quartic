
////////////////
// quartic.cc //
////////////////

// This program demonstrates how to solve the generic quartic equation:
//
//     a * x^4 + b * x^3 + c * x^2 + d * x + e == 0
//
// Solution is done as: solve_quartic({e, d, c, b, a}, roots).

#include <algorithm>
#include <complex>
#include <iostream>
#include <random>

#include "solve_quartic.h"

using namespace std;

template <typename real_type>
static bool compare(const std::complex<real_type> & a, const std::complex<real_type> & b)
{
    if (real(a) < real(b))
    {
        return true;
    }

    if (real(a) > real(b))
    {
        return false;
    }

    if (imag(a) < imag(b))
    {
        return true;
    }

    return false;
}

template <typename real_type>
static void test_quartic(const char * real_type_name, const unsigned num_testcases, const double error_threshold)
{
    mt19937 gen(0);
    uniform_real_distribution<> dis(-10.0, +10.0);

    cout << "Running " << num_testcases << " test cases. Base type: " << real_type_name << ". Only errors larger than " << error_threshold << " are shown:" << endl;

    for (unsigned i = 0; i < num_testcases; ++i)
    {
        const std::complex<real_type> a = std::complex<real_type>(dis(gen), dis(gen));

        std::complex<real_type> r[4] = {
            std::complex<real_type>(dis(gen), dis(gen)),
            std::complex<real_type>(dis(gen), dis(gen)),
            std::complex<real_type>(dis(gen), dis(gen)),
            std::complex<real_type>(dis(gen), dis(gen))
        };

        const std::complex<real_type> b = -a * (r[0] + r[1] + r[2] + r[3]);
        const std::complex<real_type> c = +a * (r[0] * r[1] + r[0] * r[2] + r[1] * r[2] + r[0] * r[3] + r[1] * r[3] + r[2] * r[3]);
        const std::complex<real_type> d = -a * (r[0] * r[1] * r[2] + r[0] * r[1] * r[3] + r[0] * r[2] * r[3] + r[1] * r[2] * r[3]);
        const std::complex<real_type> e = +a * (r[0] * r[1] * r[2] * r[3]);

        // Quartic equation as list of coefficients.

        const std::complex<real_type> coefficients[5] = {e, d, c, b, a};

        // Solve it.

        std::complex<real_type> s[4];

        solve_quartic(coefficients, s);

        // Sort r and s, to make them comparable.

        sort(r, r + 4, compare<real_type>);
        sort(s, s + 4, compare<real_type>);

        // Calculate the error.

        const double total_error = sqrt(norm(r[0] - s[0]) + norm(r[1] - s[1]) + norm(r[2] - s[2]) + norm(r[3] - s[3]));

        if (total_error >= error_threshold)
        {
            cout << "    Testcase " << i << " has total error " << total_error << endl;
        }
    }

    cout << "done." << endl;
}

int main()
{
    // Precision with floats is generally horrific.
    test_quartic<float>("float", 10000, 1e-1);

    //Precision with doubles is adequate.
    test_quartic<double>("double", 1000000, 1e-8);

    //Precision with long doubles is good.
    test_quartic<long double>("long double", 1000000, 1e-12);

    return 0;
}
