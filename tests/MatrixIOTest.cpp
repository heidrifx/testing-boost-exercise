#define BOOST_TEST_DYN_LINK
#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include "matrixIO.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace Eigen;

struct MatrixIOFixture {
  MatrixIOFixture()
  {
    fileName   = "testmat3.csv";
    matrixSize = 3;
    expected   = MatrixXd(3, 3);
    expected << 0.680375, 0.59688, -0.329554,
        -0.211234, 0.823295, 0.536459,
        0.566198, -0.604897, -0.444451;
  }

  std::string fileName;
  int         matrixSize;
  MatrixXd    expected;
};

BOOST_FIXTURE_TEST_SUITE(MatrixIOTests, MatrixIOFixture, *boost::unit_test::tolerance(1e-6))

BOOST_AUTO_TEST_CASE(OpenData)
{
  MatrixXd actual = matrixIO::openData(fileName, matrixSize);
  BOOST_TEST(actual.isApprox(expected));
}

BOOST_AUTO_TEST_CASE(SaveDataName)
{
  std::string saveFileName = "savedmat3.csv";
  matrixIO::saveData(saveFileName, expected);

  // Check if the saved file name is correct
  std::ifstream file(saveFileName);
  BOOST_TEST(file.is_open());
}

BOOST_AUTO_TEST_CASE(SaveDataContent)
{
  std::string saveFileName = "savedmat3.csv";
  matrixIO::saveData(saveFileName, expected);

  std::vector<std::vector<float>> actualData;
  std::string                     line;
  std::ifstream                   file(saveFileName);

  if (!file.is_open()) {
    BOOST_FAIL("Failed to open the file.");
  }

  // Read the file line by line
  while (std::getline(file, line)) {
    std::stringstream  ss(line);
    std::string        value;
    std::vector<float> row;

    while (std::getline(ss, value, ','))
      row.push_back(std::stof(value));

    actualData.push_back(row);
  }

  file.close();

  // Get the dimensions of the actual data
  const int rows = actualData.size();
  const int cols = actualData[0].size();

  // Check if the dimensions are correct
  BOOST_TEST(rows == matrixSize);
  BOOST_TEST(cols == matrixSize);

  // Prepare the actual matrix
  MatrixXd actual(rows, cols);

  // Convert the actual data to a MatrixXd
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      actual(i, j) = actualData[i][j];

  // Need to check individual elements because isApprox does not work here
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      BOOST_TEST(actual(i, j) == expected(i, j));
}

BOOST_AUTO_TEST_SUITE_END()
