  /*
     Thomas Nguyen
     December 5, 2017
     CSE 374
     Homework 7: Rational

     This is the implemetation of the Rational object. Clients can do simple
     arithmetic operations with Rationals.
  */

#include "rational.h"

  static int gcd(int n, int d);

  /*
     Constructs a new Rational to the specified integer params in the form
     of a fraction. If the denominator is negative then the numerator
     assumes the negative sign and the denominator becomes positive.
     Generally, Rationals will be in the form: n / d.

     Params
         n: int to set the Rational numerator to
         d: int to set the Rational denominator to
  */
  Rational::Rational(int n, int d) {
      int pos_n = (n >= 0) ? n : -n;
      int pos_d = (d >= 0) ? d : -d;
      int factor = gcd(pos_n, pos_d);
      this->num = (d >= 0) ? n / factor : -n / factor;
      this->denom = pos_d / factor;
  }

  /*
      Default contructor that initializes a new Rational to 0/1.
  */
  Rational::Rational() {
      Rational(0);
  }

  /*
      Constructs a new Rational to a specified integer value.

      Params
          n: int to set the Rational value to as n/1
  */
  Rational::Rational(int n) {
      Rational(n, 1);
  }

  /*
      Returns the numerator of the Rational. Does not alter Rational's members.

      Returns
          int: copy of the Rational object's numerator
  */
  int Rational::n() const {
      int copy = num;
      return copy;
  }

  /*
      Returns the denominator of the Rational. Will never be negative.
      Does not alter Rational's members.

      Returns
          int: copy of the Rational object's denominator.
  */
  int Rational::d() const {
      int copy = denom;
      return copy;
  }

  /*
      Adds this Rational with the provided Rational and returns a new
      Rational representing the sum.

      Params
          other: Rational to be multiplied with

      Returns
          Rational: a new Rational representing the sum of the Rationals
                    being added
  */
  Rational Rational::plus(Rational other) const {
      int sum_numer = this->num * other.denom + this->denom * other.num;
      int sum_denom = this->denom * other.denom;
      return Rational(sum_numer, sum_denom);
  }

  /*
      Subtracts the provided Rational from this Rational and returns a new
      Rational representing the result.

      Params
          other: Rational to be subtracted

      Returns
          Rational: a new Rational representing the result of the Rationals
                    being subtracted
  */
  Rational Rational::minus(Rational other) const {
      int sub_numer = this->num * other.denom - this->denom * other.num;
      int sub_denom = this->denom * other.denom;
      return Rational(sub_numer, sub_denom);
  }

  /*
      Multiplies this Rational with the provided Rational and returns a new
      Rational representing the result.

      Params
          other: Rational to be multiplied with

      Returns
          Rational: a new Rational representing the resultant of the Rationals
                    being multipled
  */
  Rational Rational::times(Rational other) const {
      int times_numer = this->num * other.num;
      int times_denom = this->denom * other.denom;
      return Rational(times_numer, times_denom);
  }

  /*
      Divides this Rational by the provided Rational and returns a new
      Rational representing the result.

      Params
          other: Rational to be divisor of the division operation

      Returns
          Rational: a new Rational representing the quotient of the Rationals
                    being divided
  */
  Rational Rational::div(Rational other) const {
      int div_numer = this->num * other.denom;
      int div_denom = this->denom * other.num;
      return Rational(div_numer, div_denom);
  }

  /*
      Recursively finds the greatest common multiple of two numbers with the
      Euclidean algorithm.

      Params
          n: first int to be considered in the gcd algorithm
          m: second int to be considered in the gcd algorithm

      Returns
          int: the determined greatest common multiple
  */
  static int gcd(int n, int d) {
      return d == 0 ? n : gcd(d, n % d);
  }
