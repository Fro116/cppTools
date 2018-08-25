#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE boost_check

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( can_build_boost )
{
  BOOST_CHECK(true);
}
