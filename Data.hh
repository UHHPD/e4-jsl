#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>

class Data {
 public:
  Data(const std::string& filename);
  int checkCompatibility(const Data& in, int n);
  double Average(const Data& in);
  double Average_Four(const Data& b, const Data& c, const Data& d);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return (m_bins[i]+m_bins[i+1])/2; }
  double binLow(int i) const { return m_bins[i]; }
  double binHigh(int i) const { return m_bins[i+1]; }
  double error(int i) const { return m_errors[i]; }
  double average(int i) const { return m_average[i];}
  double average_uncertainty(int i) const { return m_average_uncertainty[i]; }
  double Background(int n);
  double Chi();
  std::vector<double> Backgroundcompatibility(int n);
  double average_Four(int i) const {return m_average_four[i];}

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_errors;
  std::vector<double> m_average;
  std::vector<double> m_average_uncertainty;
  std::vector<double> m_background;
  std::vector<double> m_average_four;
  std::vector<double> m_average_uncertainty_four;
};

#endif
