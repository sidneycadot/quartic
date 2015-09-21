
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

using namespace std;

typedef complex<double> complex_double;

static complex_double complex_sqrt(const complex_double z)
{
    return pow(z, 1.0 / 2.0);
}

static complex_double complex_cbrt(const complex_double z)
{
    return pow(z, 1.0 / 3.0);
}

void solve_quartic(const complex_double coefficients[5], complex_double roots[4])
{
    // The algorithm below was derived by solving the quartic in Mathematica, and simplifying the resulting expression by hand.

    const complex_double a = coefficients[4];
    const complex_double b = coefficients[3] / a;
    const complex_double c = coefficients[2] / a;
    const complex_double d = coefficients[1] / a;
    const complex_double e = coefficients[0] / a;

    const complex_double Z1 = c * c - 3. * b * d + 12. * e;
    const complex_double Z2 = 2. * c * c * c - 9. * b * c * d + 27. * d * d + 27. * b * b * e - 72. * c * e;
    const complex_double Z3 = 8. * b * c - 16. * d - 2. * b * b * b;
    const complex_double Z4 = 3. * b * b - 8. * c;

    const complex_double Z5 = complex_cbrt(Z2 / 2. + complex_sqrt(Z2 * Z2 /4. - Z1 * Z1 * Z1));
    const complex_double Z6 = (Z1/Z5 + Z5) / 3.;
    const complex_double Z7 = 2. * complex_sqrt(Z4 / 12. + Z6);

    roots[0] = (-b - Z7 - complex_sqrt(4. *Z4 /6. - 4. *Z6 - Z3 / Z7)) / 4.;
    roots[1] = (-b - Z7 + complex_sqrt(4. *Z4 /6. - 4. *Z6 - Z3 / Z7)) / 4.;
    roots[2] = (-b + Z7 - complex_sqrt(4. *Z4 /6. - 4. *Z6 + Z3 / Z7)) / 4.;
    roots[3] = (-b + Z7 + complex_sqrt(4. *Z4 /6. - 4. *Z6 + Z3 / Z7)) / 4.;
}

bool compare(const complex_double & a, const complex_double & b)
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

int main()
{
    mt19937 gen(0);
    uniform_real_distribution<> dis(-10.0, +10.0);

    unsigned const testcases = 100000;
    const double error_threshold = 1e-9;

    cout << "Running " << testcases << " test cases. Only errors larger than " << error_threshold << " are shown:" << endl;
    
    for (unsigned i = 0; i < testcases; ++i)
    {
        complex_double a = complex_double(dis(gen), dis(gen));

        complex_double r[4] = {
            complex_double(dis(gen), dis(gen)),
            complex_double(dis(gen), dis(gen)),
            complex_double(dis(gen), dis(gen)),
            complex_double(dis(gen), dis(gen))
        };

        complex_double b = -a * (r[0] + r[1] + r[2] + r[3]);
        complex_double c = +a * (r[0] * r[1] + r[0] * r[2] + r[1] * r[2] + r[0] * r[3] + r[1] * r[3] + r[2] * r[3]);
        complex_double d = -a * (r[0] * r[1] * r[2] + r[0] * r[1] * r[3] + r[0] * r[2] * r[3] + r[1] * r[2] * r[3]);
        complex_double e = +a * (r[0] * r[1] * r[2] * r[3]);

        // quartic equation as list of coefficients

        complex_double coefficients[5] = {e, d, c, b, a};

        // solve it

        complex_double s[4];

        solve_quartic(coefficients, s);

        // sort r and s, to make them comparable.

        sort(r, r + 4, compare);
        sort(s, s + 4, compare);

        // calculate the error

        double total_error = sqrt(norm(r[0] - s[0]) + norm(r[1] - s[1]) + norm(r[2] - s[2]) + norm(r[3] - s[3]));

        if (total_error >= error_threshold)
        {
            cout << "    Testcase " << i << " has total error " << total_error << endl;
        }
    }

    cout << "Done/" << endl;

    return 0;
}
