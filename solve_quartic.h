
///////////////
// quartic.h //
///////////////

// The solve_quartic routine solves the generic quartic equation:
//
//     a * x^4 + b * x^3 + c * x^2 + d * x + e == 0
//
// Usage:
//
//   solve_quartic<float>({e, d, c, b, a}, roots). (NOT RECOMMENDED --- VERY BAD PRECISION!)
//
//     - or -
//
//   solve_quartic<double>({e, d, c, b, a}, roots).
//
//     - or -
//
//   solve_quartic<long double>({e, d, c, b, a}, roots).

#include <complex>

template <typename real_type>
std::complex<real_type> complex_sqrt(const std::complex<real_type> & z)
{
    return pow(z, real_type(1) / real_type(2));
}

template <typename real_type>
std::complex<real_type> complex_cbrt(const std::complex<real_type> & z)
{
    return pow(z, real_type(1) / real_type(3));
}

template <typename real_type>
void solve_quartic(const std::complex<real_type> coefficients[5], std::complex<real_type> roots[4])
{
    // The algorithm below was derived by solving the quartic in Mathematica, and simplifying the resulting expression by hand.

    const std::complex<real_type> a = coefficients[4];
    const std::complex<real_type> b = coefficients[3] / a;
    const std::complex<real_type> c = coefficients[2] / a;
    const std::complex<real_type> d = coefficients[1] / a;
    const std::complex<real_type> e = coefficients[0] / a;

    const std::complex<real_type> Q1 = c * c - real_type(3) * b * d + real_type(12) * e;
    const std::complex<real_type> Q2 = real_type(2) * c * c * c - real_type(9) * b * c * d + real_type(27) * d * d + real_type(27) * b * b * e - real_type(72) * c * e;
    const std::complex<real_type> Q3 = real_type(8) * b * c - real_type(16) * d - real_type(2) * b * b * b;
    const std::complex<real_type> Q4 = real_type(3) * b * b - real_type(8) * c;

    const std::complex<real_type> Q5 = complex_cbrt(Q2 / real_type(2) + complex_sqrt(Q2 * Q2 / real_type(4) - Q1 * Q1 * Q1));
    const std::complex<real_type> Q6 = (Q1 / Q5 + Q5) / real_type(3);
    const std::complex<real_type> Q7 = real_type(2) * complex_sqrt(Q4 / real_type(12) + Q6);

    roots[0] = (-b - Q7 - complex_sqrt(real_type(4) * Q4 / real_type(6) - real_type(4) * Q6 - Q3 / Q7)) / real_type(4);
    roots[1] = (-b - Q7 + complex_sqrt(real_type(4) * Q4 / real_type(6) - real_type(4) * Q6 - Q3 / Q7)) / real_type(4);
    roots[2] = (-b + Q7 - complex_sqrt(real_type(4) * Q4 / real_type(6) - real_type(4) * Q6 + Q3 / Q7)) / real_type(4);
    roots[3] = (-b + Q7 + complex_sqrt(real_type(4) * Q4 / real_type(6) - real_type(4) * Q6 + Q3 / Q7)) / real_type(4);
}
