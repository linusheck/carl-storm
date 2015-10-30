#include "gtest/gtest.h"

#include <list>

#include "carl/cad/SampleSet.h"
#include "carl/util/platform.h"

#include "../Common.h"

using namespace carl;

TEST(SampleSet, BasicOperations)
{
	cad::SampleSet<Rational> s;

	auto pos = s.insert(RealAlgebraicNumberNR<Rational>::create(0));

	std::list<RealAlgebraicNumberPtr<Rational>> nums;
	nums.push_back(RealAlgebraicNumberNR<Rational>::create(1));
	nums.push_back(RealAlgebraicNumberNR<Rational>::create(2));
	s.insert(nums.begin(), nums.end());

	ASSERT_NO_THROW(s.remove(std::get<0>(pos)));
	ASSERT_FALSE(s.empty());
	ASSERT_NO_THROW(s.pop());
	ASSERT_NO_THROW(s.pop());
	ASSERT_TRUE(s.empty());
}
