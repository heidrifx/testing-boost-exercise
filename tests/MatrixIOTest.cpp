#define BOOST_TEST_DYN_LINK
#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include "MatrixIO.hpp"

using namespace Eigen;

struct MatrixIOFixture {
  MatrixIOFixture()
  {
    fileName = "testmat3.csv";
    matrixSize = 3;
    expected = MatrixXd(3, 3);
    expected <<  0.680375,  0.59688,  -0.329554,
                -0.211234,  0.823295,  0.536459,
                 0.566198, -0.604897, -0.444451;
  }

  std::string fileName;
  int matrixSize;
  MatrixXd expected;
};

BOOST_FIXTURE_TEST_SUITE(MatrixIOTests, MatrixIOFixture, *boost::unit_test::tolerance(1e-12))

BOOST_AUTO_TEST_CASE(OpenData)
{
    MatrixXd actual = matrixIO::openData(fileName, matrixSize);
    BOOST_TEST(actual.isApprox(expected));
}

BOOST_AUTO_TEST_SUITE_END()
