
/////////////////////
// test-quartic.cc //
/////////////////////

#include <algorithm>
#include <complex>
#include <iostream>
#include <random>

#include "solve-quartic.h"

using namespace std;

static bool compare(const std::complex<double> & a, const std::complex<double> & b)
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

static void test_quartic(const unsigned num_testcases, const double error_threshold)
{
    mt19937 gen(0);
    uniform_real_distribution<> dis(-10.0, +10.0);

    cout << "Running " << num_testcases << " test cases. Only errors larger than " << error_threshold << " are shown:" << endl;

    for (unsigned i = 0; i < num_testcases; ++i)
    {
        const std::complex<double> a = std::complex<double>(dis(gen), dis(gen));

        std::complex<double> r[4] = {
            std::complex<double>(dis(gen), dis(gen)),
            std::complex<double>(dis(gen), dis(gen)),
            std::complex<double>(dis(gen), dis(gen)),
            std::complex<double>(dis(gen), dis(gen))
        };

        const std::complex<double> b = -a * (r[0] + r[1] + r[2] + r[3]);
        const std::complex<double> c = +a * (r[0] * r[1] + r[0] * r[2] + r[1] * r[2] + r[0] * r[3] + r[1] * r[3] + r[2] * r[3]);
        const std::complex<double> d = -a * (r[0] * r[1] * r[2] + r[0] * r[1] * r[3] + r[0] * r[2] * r[3] + r[1] * r[2] * r[3]);
        const std::complex<double> e = +a * (r[0] * r[1] * r[2] * r[3]);

        // Quartic equation as list of coefficients.

        const std::complex<double> coefficients[5] = {e, d, c, b, a};

        // Solve it.

        std::complex<double> s[4];

        solve_quartic(coefficients, s);

        // Sort r and s, to make them comparable.

        sort(begin(r), end(r), compare);
        sort(begin(s), end(s), compare);

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
    test_quartic(1000000, 1e-8);

    return 0;
}
