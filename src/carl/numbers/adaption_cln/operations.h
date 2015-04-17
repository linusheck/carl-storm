/** 
 * @file   adaption_cln/operations.h
 * @ingroup cln
 * @author Gereon Kremer <gereon.kremer@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * 
 * @warning This file should never be included directly but only via operations.h
 * 
 */
#pragma once
#include "../../util/platform.h"
#include <cassert>
#include <limits>
#include <cmath>
#include <sstream>
#include <vector>
#include "typetraits.h"
#include "boost/algorithm/string.hpp"
#include "../constants.h"
#include "../operations.h"

namespace carl {

inline bool isZero(const cln::cl_I& n) {
	return zerop(n);
}	
	
inline bool isZero(const cln::cl_RA& n) {
	return zerop(n);
}

inline bool isOne(const cln::cl_I& n) {
	return n == carl::constant_one<cln::cl_I>().get();
}	
	
inline bool isOne(const cln::cl_RA& n) {
	return n  == carl::constant_one<cln::cl_RA>().get();
}

inline bool isPositive(const cln::cl_I& n) {
	return n > carl::constant_zero<cln::cl_RA>().get();
}	
	
inline bool isPositive(const cln::cl_RA& n) {
	return n > carl::constant_zero<cln::cl_RA>().get();
}

inline bool isNegative(const cln::cl_I& n) {
	return n < carl::constant_zero<cln::cl_RA>().get();
}	
	
inline bool isNegative(const cln::cl_RA& n) {
	return n < carl::constant_zero<cln::cl_RA>().get();
}
	
/**
 * Extract the numerator from a fraction.
 * @param n Fraction.
 * @return Numerator.
 */
inline cln::cl_I getNum(const cln::cl_RA& n) {
	return cln::numerator(n);
}

/**
 * Extract the denominator from a fraction.
 * @param n Fraction.
 * @return Denominator.
 */
inline cln::cl_I getDenom(const cln::cl_RA& n) {
	return cln::denominator(n);
}

/**
 * Check if a number is integral.
 * As cln::cl_I are always integral, this method returns true.
 * @param An integer.
 * @return true.
 */
inline bool isInteger(const cln::cl_I&) {
	return true;
}

/**
 * Check if a fraction is integral.
 * @param n A fraction.
 * @return true.
 */
inline bool isInteger(const cln::cl_RA& n) {
	return getDenom(n) == (cln::cl_I)(1);
}

/**
 * Get the bit size of the representation of a integer.
 * @param n An integer.
 * @return Bit size of n.
 */
inline std::size_t bitsize(const cln::cl_I& n) {
	return cln::integer_length(n);
}
/**
 * Get the bit size of the representation of a fraction.
 * @param n A fraction.
 * @return Bit size of n.
 */
inline std::size_t bitsize(const cln::cl_RA& n) {
	return cln::integer_length(getNum(n)) + cln::integer_length(getDenom(n));
}

/**
 * Converts the given fraction to a double.
 * @param n A fraction.
 * @return Double.
 */
inline double toDouble(const cln::cl_RA& n) {
	return cln::double_approx(n);
}
/**
 * Converts the given integer to a double.
 * @param n An integer.
 * @return Double.
 */
inline double toDouble(const cln::cl_I& n) {
	return cln::double_approx(n);
}

template<typename Integer>
inline Integer toInt(const cln::cl_I& n);
template<typename Integer>
inline Integer toInt(const cln::cl_RA& n);

/**
 * Convert a cln integer to an int.
 * @param n An integer.
 * @return n as int.
 */
template<>
inline int toInt<int>(const cln::cl_I& n) {
    assert(n <= std::numeric_limits<int>::max());
    assert(n >= std::numeric_limits<int>::min());
    return cln::cl_I_to_int(n);
}

/**
 * Convert a cln integer to a longint.
 * @param n An integer.
 * @return n as long int.
 */
template<>
inline long int toInt<long int>(const cln::cl_I& n) {
    assert(n <= std::numeric_limits<long int>::max());
    assert(n >= std::numeric_limits<long int>::min());
    return cln::cl_I_to_long(n);
}
template<>
inline std::size_t toInt<std::size_t>(const cln::cl_I& n) {
    assert(n <= std::numeric_limits<std::size_t>::max());
    assert(n >= std::numeric_limits<std::size_t>::min());
    return cln::cl_I_to_ulong(n);
}

/**
 * Convert a fraction to an integer.
 * This method assert, that the given fraction is an integer, i.e. that the denominator is one.
 * @param n A fraction.
 * @return An integer.
 */
template<>
inline cln::cl_I toInt<cln::cl_I>(const cln::cl_RA& n) {
	assert(isInteger(n));
	return getNum(n);
}

/**
 * Convert a fraction to an unsigned.
 * @param n A fraction.
 * @return n as unsigned.
 */
template<>
inline std::size_t toInt<std::size_t>(const cln::cl_RA& n) {
	return toInt<std::size_t>(toInt<cln::cl_I>(n));
}

/**
 * Convert a cln fraction to a cln long float.
 * @param n A fraction.
 * @return n as cln::cl_LF.
 */
inline cln::cl_LF toLF(const cln::cl_RA& n) {
	return cln::cl_R_to_LF(n, std::max(cln::integer_length(cln::numerator(n)), cln::integer_length(cln::denominator(n))));
}

template<typename T>
inline T rationalize(double n);

template<typename T>
inline T rationalize(float n);

template<typename T>
inline T rationalize(int n);

template<typename T>
inline T rationalize(size_t n);

template<typename T>
inline T rationalize(const std::string& n);

template<typename T>
inline T rationalize(const PreventConversion<cln::cl_RA>&);

template<typename T>
inline T rationalize(const PreventConversion<mpq_class>&);

static const cln::cl_RA ONE_DIVIDED_BY_10_TO_THE_POWER_OF_23 = cln::cl_RA(1)/cln::expt(cln::cl_RA(10), 23);
static const cln::cl_RA ONE_DIVIDED_BY_10_TO_THE_POWER_OF_52 = cln::cl_RA(1)/cln::expt(cln::cl_RA(10), 52);

template<>
cln::cl_RA rationalize<cln::cl_RA>(double n);

template<>
cln::cl_RA rationalize<cln::cl_RA>(float n);

template<>
inline cln::cl_RA rationalize<cln::cl_RA>(size_t n) {
	return cln::cl_RA(n);
}

template<>
inline cln::cl_RA rationalize<cln::cl_RA>(int n) {
	return cln::cl_RA(n);
}

template<>
cln::cl_RA rationalize<cln::cl_RA>(const std::string& inputstring);

template<>
cln::cl_RA rationalize<cln::cl_RA>(const PreventConversion<mpq_class>& n);

template<>
inline cln::cl_RA rationalize<cln::cl_RA>(const PreventConversion<cln::cl_RA>& n) {
	return n;
}

/**
 * Get absolute value of an integer.
 * @param n An integer.
 * @return \f$|n|\f$.
 */
inline cln::cl_I abs(const cln::cl_I& n) {
	return cln::abs(n);
}

/**
 * Get absolute value of a fraction.
 * @param n A fraction.
 * @return \f$|n|\f$.
 */
inline cln::cl_RA abs(const cln::cl_RA& n) {
	return cln::abs(n);
}

/**
 * Round down a fraction.
 * @param n A fraction.
 * @return \f$\lfloor n \rfloor\f$.
 */
inline cln::cl_I floor(const cln::cl_RA& n) {
	return cln::floor1(n);
}

/**
 * Round down an integer.
 * @param n An integer.
 * @return \f$\lfloor n \rfloor\f$.
 */
inline cln::cl_I floor(const cln::cl_I& n) {
	return n;
}

/**
 * Round up a fraction.
 * @param n A fraction.
 * @return \f$\lceil n \rceil\f$.
 */
inline cln::cl_I ceil(const cln::cl_RA& n) {
	return cln::ceiling1(n);
}

/**
 * Round up an integer.
 * @param n An integer.
 * @return \f$\lceil n \rceil\f$.
 */
inline cln::cl_I ceil(const cln::cl_I& n) {
	return n;
}

/**
 * Calculate the greatest common divisor of two integers.
 * @param a First argument.
 * @param b Second argument.
 * @return Gcd of a and b.
 */
inline cln::cl_I gcd(const cln::cl_I& a, const cln::cl_I& b) {
	return cln::gcd(a,b);
}

/**
 * Calculate the greatest common divisor of two integers.
 * Stores the result in the first argument.
 * @param a First argument.
 * @param b Second argument.
 * @return Updated a.
 */
inline cln::cl_I& gcd_assign(cln::cl_I& a, const cln::cl_I& b) {
    a = cln::gcd(a,b);
	return a;
}

inline void divide(const cln::cl_I& dividend, const cln::cl_I& divisor, cln::cl_I& quotient, cln::cl_I& remainder) {
	cln::cl_I_div_t res = cln::floor2(dividend, divisor);
    quotient = res.quotient;
    remainder = res.remainder;
}

/**
 * Calculate the greatest common divisor of two fractions.
 * Stores the result in the first argument.
 * Asserts that the arguments are integral.
 * @param a First argument.
 * @param b Second argument.
 * @return Updated a.
 */
inline cln::cl_RA& gcd_assign(cln::cl_RA& a, const cln::cl_RA& b) {
	a = cln::gcd(carl::getNum(a),carl::getNum(b)) / cln::lcm(carl::getDenom(a),carl::getDenom(b));
	return a;
}

/**
 * Calculate the greatest common divisor of two fractions.
 * Asserts that the arguments are integral.
 * @param a First argument.
 * @param b Second argument.
 * @return Gcd of a and b.
 */
inline cln::cl_RA gcd(const cln::cl_RA& a, const cln::cl_RA& b) {
	return cln::gcd(carl::getNum(a),carl::getNum(b)) / cln::lcm(carl::getDenom(a),carl::getDenom(b));
}

/**
 * Calculate the least common multiple of two integers.
 * @param a First argument.
 * @param b Second argument.
 * @return Lcm of a and b.
 */
inline cln::cl_I lcm(const cln::cl_I& a, const cln::cl_I& b) {
	return cln::lcm(a,b);
}

/**
 * Calculate the least common multiple of two fractions.
 * Asserts that the arguments are integral.
 * @param a First argument.
 * @param b Second argument.
 * @return Lcm of a and b.
 */
inline cln::cl_RA lcm(const cln::cl_RA& a, const cln::cl_RA& b) {
    assert( carl::isInteger( a ) );
    assert( carl::isInteger( b ) );
	return cln::lcm(carl::getNum(a),carl::getNum(b));
}

/**
 * Calculate the power of some fraction to some positive integer.
 * @param n Basis.
 * @param e Exponent.
 * @return \f$n^e\f$
 */
template<>
inline cln::cl_RA pow(const cln::cl_RA& n, std::size_t e) {
	return cln::expt(n, (int)e);
}

/**
 * Calculate the square root of a fraction if possible.
 * 
 * @param a The fraction to calculate the square root for.
 * @param b A reference to the rational, in which the result is stored.
 * @return true, if the number to calculate the square root for is a square;
 *         false, otherwise.
 */
bool sqrtp(const cln::cl_RA& a, cln::cl_RA& b);

/**
 * Calculate the square root of a fraction.
 * 
 * If we are able to find a an \f$x\f$ such that \f$x\f$ is the exact root of \f$a\f$, \f$(x,x)\f$ is returned.
 * If we can not find such a number (note that such a number might not even exist), \f$(x,y)\f$ is returned with \f$ x < \sqrt{a} < y \f$.
 * Note that we try to find bounds that are very close to the actual square root. If a small representation is more important than a small interval, sqrt_fast should be used.
 * @param a A fraction.
 * @return Interval containing the square root of a.
 */
std::pair<cln::cl_RA, cln::cl_RA> sqrt(const cln::cl_RA& a);

/**
 * Compute square root in a fast but less precise way.
 * Use cln::sqrt() to obtain an approximation. If the result is rational, i.e. the result is exact, use this result.
 * Otherwise use the nearest integers as bounds on the square root.
 * @param a Some number.
 * @return [x,x] if sqrt(a) = x is rational, otherwise [y,z] for y,z integer and y < sqrt(a) < z. 
 */
std::pair<cln::cl_RA, cln::cl_RA> sqrt_fast(const cln::cl_RA& a);

/**
 * Calculate the remainder of the integer division.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$a \% b\f$.
 */
inline cln::cl_I mod(const cln::cl_I& a, const cln::cl_I& b) {
	return cln::rem(a, b);
}

/**
 * Divide two fractions.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_RA div(const cln::cl_RA& a, const cln::cl_RA& b) {
	return (a / b);
}

/**
 * Divide two integers.
 * Asserts that the remainder is zero.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_I div(const cln::cl_I& a, const cln::cl_I& b) {
	assert(cln::mod(a, b) == 0);
	return cln::exquo(a, b);
}

/**
 * Divide two fractions.
 * Stores the result in the first argument.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_RA& div_assign(cln::cl_RA& a, const cln::cl_RA& b) {
    a /= b;
	return a;
}

/**
 * Divide two integers.
 * Asserts that the remainder is zero.
 * Stores the result in the first argument.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_I& div_assign(cln::cl_I& a, const cln::cl_I& b) {
	assert(cln::mod(a,b) == 0);
	a = cln::exquo(a, b);
    return a;
}

/**
 * Divide two fractions.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_RA quotient(const cln::cl_RA& a, const cln::cl_RA& b)
{
	return a / b;
}
/**
 * Divide two integers.
 * Discards the remainder of the division.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_I quotient(const cln::cl_I& a, const cln::cl_I& b)
{
	return cln::exquo(a - cln::rem(a, b), b);
}


/**
 * Calculate the remainder of the integer division.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$a \% b\f$.
 */
inline cln::cl_I remainder(const cln::cl_I& a, const cln::cl_I& b) {
	return cln::rem(a, b);
}


/**
 * Divide two integers.
 * Discards the remainder of the division.
 * @param a First argument.
 * @param b Second argument.
 * @return \f$ a / b \f$.
 */
inline cln::cl_I operator/(const cln::cl_I& a, const cln::cl_I& b)
{
	return quotient(a,b);
}
inline cln::cl_I operator/(const cln::cl_I& lhs, const int& rhs) {
	return lhs / cln::cl_I(rhs);
}

std::string toString(const cln::cl_RA& _number, bool _infix);

std::string toString(const cln::cl_I& _number, bool _infix);

}
