#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

#include <adolc/adtl.h>
typedef adtl::adouble adouble;

#include "const.h"

//number of directions = 2
const size_t numDir = adtl::getNumDir();

BOOST_AUTO_TEST_SUITE( traceless_composite )


/************************************/
/* Tests for traceless mode with    */
/* custom composite functions       */
/* Author: Philipp Schuette         */
/************************************/

/* Most of the tests in this file are implemented similarly for trace
 * mode tests in traceCompositeTests.cpp.  Exhaustive descriptions of
 * test functions and derivatives can be found there.
 */

BOOST_AUTO_TEST_CASE(CompositeTrig1_Traceless)
{
  double x1 = 0.289, x2 = 1.927, out;
  adouble ax1 = x1, ax2 = x2;

  ax1.setADValue(0, 1.);
  ax2.setADValue(1, 1.);

  ax1 = adtl::sin(ax1)*adtl::sin(ax1) + adtl::cos(ax1)*adtl::cos(ax1) + ax2;

  double x1Derivative = 0.;
  double x2Derivative = 1.;

  x1 = std::sin(x1)*std::sin(x1) + std::cos(x1)*std::cos(x1) + x2;

  BOOST_TEST(ax1.getValue() == x1, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(0) == x1Derivative, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(1) == x2Derivative, tt::tolerance(tol));
}

BOOST_AUTO_TEST_CASE(CompositeTrig2_Traceless)
{
  double x1 = 1.11, x2 = 2.22, out;
  adouble ax1 = x1, ax2 = x2;

  ax1.setADValue(0, 1.);
  ax2.setADValue(1, 1.);

  ax1 = 2.*adtl::sin(adtl::cos(ax1))*adtl::exp(ax2) - 2.*adtl::sin(ax2);

  double x1Derivative = -2.*std::cos(std::cos(x1))*std::sin(x1)*std::exp(x2);
  double x2Derivative = 2.*std::sin(std::cos(x1))*std::exp(x2)
                        - 2.*std::cos(x2);

  x1 = 2.*std::sin(std::cos(x1))*std::exp(x2) - 2.*std::sin(x2);

  BOOST_TEST(ax1.getValue() == x1, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(0) == x1Derivative, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(1) == x2Derivative, tt::tolerance(tol));
}

BOOST_AUTO_TEST_CASE(CompositeTrig3_Traceless)
{
  double x1 = 0.516, x2 = 9.89, out;
  adouble ax1 = x1, ax2 = x2;

  ax1.setADValue(0, 1.);
  ax2.setADValue(1, 1.);

  ax1 = adtl::pow(adtl::sin(ax1), adtl::cos(ax1) - ax2);

  double x1Derivative = std::pow(std::sin(x1), std::cos(x1) - x2)
                        * (-std::sin(x1)*std::log(std::sin(x1))
                        + (std::cos(x1) - x2)*std::cos(x1)/std::sin(x1));
  double x2Derivative = -std::log(std::sin(x1))
                        * std::pow(std::sin(x1), std::cos(x1) - x2);

  x1 = std::pow(std::sin(x1), std::cos(x1) - x2);

  BOOST_TEST(ax1.getValue() == x1, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(0) == x1Derivative, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(1) == x2Derivative, tt::tolerance(tol));
}

BOOST_AUTO_TEST_CASE(CompositeTrig4_Traceless)
{
  double x1 = 1.56, x2 = 8.99, out;
  adouble ax1 = x1, ax2 = x2;

  ax1.setADValue(0, 1.);
  ax2.setADValue(1, 1.);

  ax1 = adtl::atan(adtl::tan(ax1))*adtl::exp(ax2);

  double x1Derivative = std::exp(x2);
  double x2Derivative = x1*std::exp(x2);

  x1 = std::atan(std::tan(x1))*std::exp(x2);

  BOOST_TEST(ax1.getValue() == x1, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(0) == x1Derivative, tt::tolerance(tol));
  BOOST_TEST(ax1.getADValue(1) == x2Derivative, tt::tolerance(tol));
}




BOOST_AUTO_TEST_SUITE_END()
