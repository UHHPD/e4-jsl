#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T> bool testEqual(const std::string &name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a; // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()>> tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}

int main() {
  using namespace std;

  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create an object which holds data of experiment A
  Data datA("exp_A");
  Data datB("exp_B");
  Data datC("exp_C");
  Data datD("exp_D");

  // here is the data from experiment A
  cout << "bin 27: from " << datA.binLow(27) << " to " << datA.binHigh(27)
       << endl;
  cout << "measurement of experiment A in bin 27: " << datA.measurement(27)
       << endl;

  // here is the data from experiment B
  cout << "measurement of experiment B in bin 27: " << datB.measurement(27)
       << endl;

  // here is the data from experiment C
  cout << "measurement of experiment C in bin 27: " << datC.measurement(27)
       << endl;

  // here is the data from experiment D
  cout << "measurement of experiment D in bin 27: " << datD.measurement(27)
       << endl;

  cout << "check for compatibility for bin 27 of sample A and B: "
       << datB.measurement(27) - datA.measurement(27) << " < "
       << sqrt(pow(datB.error(27), 2) + pow(datA.error(27), 2)) << endl;

  cout << "check for compatibility of sample A and B: "
       << datA.checkCompatibility(datB, 2) << endl;
  
  cout << "check for compatibility of sample C and A: "
       << datC.checkCompatibility(datA, 2) << endl;

  cout << "check for compatibility of sample C and B: "
       << datC.checkCompatibility(datB, 2) << endl;   

  cout << "check for compatibility of sample C and D: "
       << datC.checkCompatibility(datD, 2) << endl;       

  datA.Average(datB);

  cout << "4th entry of data set A and B averaged: " << datA.average(3) << endl;

  //cout << "Test " << datB.Background(3) << endl;
  //cout << "Test " << datA.Background(3) << endl;
  // print 2a to console:
  int stddev;

  //--------------------------------------------------

  cout << "-------------------------------" << endl;

  cout << "Values for Data Set A:" << endl;

  stddev = 2;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set A: { ";

  for (int i = 0; i < datA.Backgroundcompatibility(stddev).size(); i++) {
    cout << datA.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datA.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  stddev = 3;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set A: { ";
  for (int i = 0; i < datA.Backgroundcompatibility(stddev).size(); i++) {
    cout << datA.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datA.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  cout << "The Chi squared / ndf value for Data Set A is: " << datA.Chi()
       << endl;

  cout << "-------------------------------" << endl;

  //-----------------------------

  cout << "Values for Data Set B:" << endl;

  stddev = 2;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set B: { ";

  for (int i = 0; i < datB.Backgroundcompatibility(stddev).size(); i++) {
    cout << datB.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datB.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  stddev = 3;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set B: { ";
  for (int i = 0; i < datB.Backgroundcompatibility(stddev).size(); i++) {
    cout << datB.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datB.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  cout << "The Chi squared / ndf value for Data Set B is: " << datB.Chi()
       << endl;

  cout << "-------------------------------" << endl;

  //-----------------------------

  cout << "Values for Data Set C:" << endl;

  stddev = 2;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set C: { ";

  for (int i = 0; i < datC.Backgroundcompatibility(stddev).size(); i++) {
    cout << datC.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datC.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  stddev = 3;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set C: { ";
  for (int i = 0; i < datC.Backgroundcompatibility(stddev).size(); i++) {
    cout << datC.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datC.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  cout << "The Chi squared / ndf value for Data Set C is: " << datC.Chi()
       << endl;

  cout << "-------------------------------" << endl;
  //-----------------------------

  cout << "Values for Data Set D:" << endl;

  stddev = 2;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set D: { ";

  for (int i = 0; i < datD.Backgroundcompatibility(stddev).size(); i++) {
    cout << datD.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datD.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  stddev = 3;

  cout << "outsiders for " << stddev
       << " Standard Deviation(s) in data set D: { ";
  for (int i = 0; i < datD.Backgroundcompatibility(stddev).size(); i++) {
    cout << datD.Backgroundcompatibility(stddev)[i] << " ";
  }
  cout << "}" << endl;

  cout << "This means there are " << datD.Backgroundcompatibility(stddev).size()
       << " Outsider(s) in " << stddev << " Standard Deviation(s)." << endl;

  cout << "The Chi squared / ndf value for Data Set D is: " << datD.Chi()
       << endl;

  cout << "-------------------------------" << endl;
  
cout << "The Chi squared / ndf value of the combined Dataset is: " << datA.Average_Four(datB,datC,datD) << endl;

//The Value of Chi squared / ndf of the combined Dataset was calculated to 1.49072 by us. We expedcted a value around 1, because Combining multiple measurments should normaly lead to a increased agreement between the combined Data and the model.

//We have an idea where this might come from:

//Between the values M=150 and M=200 GeV the measured values are well above the fit. Their error could add up to increase the Chi squared / ndf value.

//A Combination of a Dataset with itself (4 times) led to the expected values of the combined Data as well as the uncertainty and the Chi squared / ndf, which is why we don't see an obvious problem in the code.

  return 0;
}
