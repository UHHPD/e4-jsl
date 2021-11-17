#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <cmath>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }

  // read in data from file: m_siz error contents
  for (int i = 0; i < size; ++i) {
    double errors;
    file >> errors;
    m_errors.push_back(errors);
  }

  // done! close the file
  file.close();

  assertSizes();
};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }

int Data::checkCompatibility(const Data& in, int n){
  int outsiders=0;
    for (int i=0; i<m_data.size(); i++){
      if (n*sqrt(pow(error(i),2)+pow(in.error(i),2))<abs((measurement(i)-in.measurement(i))))
      {
        outsiders++;
      }
    }
    return outsiders;
  }


double Data::Average(const Data& in){

  double w1;
  double w2;

  if(checkCompatibility(in, 1)/m_data.size()<0.6827 && checkCompatibility(in, 2)/m_data.size()<0.9545 && checkCompatibility(in, 3)/m_data.size()<0.9973)
  {
    for(int i=0;i<m_data.size();i++){
      w1=1/pow(error(i),2);
      w2=1/pow(in.error(i),2);
      m_average.push_back((w1*measurement(i) + w2*in.measurement(i))/(w1+w2));
      m_average_uncertainty.push_back(sqrt(1/(w1+w2)));
    } 
  }

}

double Data::Background(int n){

  double alpha = 0.005;
  double beta = -0.00001;
  double gamma = 0.08;
  double delta = 0.015;

  for(int i=0;i<m_data.size();i++){
  m_background.push_back(alpha+beta*binCenter(i)+gamma*exp(-delta*binCenter(i)));
  }

  return m_background[n];

}

double Data::Chi (){
  double chisq=0;
  int ndf;

  for(int i=0; i<m_data.size();i++){
    chisq+=(pow(measurement(i)-Background(i),2))/(pow(error(i),2));
  }
  
  return chisq/ndf;
}