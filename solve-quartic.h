
/////////////////////
// solve-quartic.h //
/////////////////////

#ifndef solve_quartic_h
#define solve_quartic_h

// The solve_quartic routine solves the generic quartic equation:
//
//     a * x^4 + b * x^3 + c * x^2 + d * x + e == 0
//
// Usage:
//
//     solve_quartic({e, d, c, b, a}, roots).

#include <complex>

void solve_quartic(const std::complex<double> coefficients[5], std::complex<double> roots[4]);

#endif // solve_quartic_h
