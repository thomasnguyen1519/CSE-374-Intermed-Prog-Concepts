/*
 * Interface to rational number type
 * CSE 374, 17wi, HP
 */

#ifndef RATIONAL_H
#define RATIONAL_H

class Rational {
 public:
  // constructors:

  // Construct Rational 0/1
  Rational();

  // Construct Rational n/1
  Rational(int n);

  // Construct Rational n/d
  Rational(int n, int d);

  // member functions that do not modify this are marked as const to
  // document that they only read this but do not change it.

  // accessors: return the numerator and denominator of this Rational.
  // Results are in lowest terms (i.e., for rational r, r.n() and r.d()
  // have no common integer divisors greater than 1).
  int n() const;
  int d() const;

  // arithmetic: return a new Rational that results from combining
  // this Rational with another.  Neither operand is changed.

  // = this + other
  Rational plus(Rational other) const;

  // = this - other
  Rational minus(Rational other) const;

  // = this * other
  Rational times(Rational other) const;

  // = this / other
  Rational div(Rational other) const;


 private:
  // Representation of a Rational: num/denom
  // No attempt is made to detect a denominator of 0 as an error
  int num;
  int denom; 

};

#endif
