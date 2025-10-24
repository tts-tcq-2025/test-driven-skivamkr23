#include "StringCalculator.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool HasCustomDelimiter(const std::string& input) {
  return input.rfind("//", 0) == 0 && input.find('\n') != std::string::npos;
}

std::string ParseDelimiterSpec(const std::string& spec) {
  if (spec.size() >= 2 && spec.front() == '[' && spec.back() == ']') {
    return spec.substr(1, spec.size() - 2);
  }
  return spec;
}

std::string ExtractDelimiter(std::string& input) {
  if (!HasCustomDelimiter(input)) return ",";

  size_t newline_pos = input.find('\n');
  std::string delimiter_spec = input.substr(2, newline_pos - 2);
  input = input.substr(newline_pos + 1);
  return ParseDelimiterSpec(delimiter_spec);
}

std::string NormalizeDelimiters(const std::string& input,
                                const std::string& delimiter) {
  std::string result = input;
  std::replace(result.begin(), result.end(), '\n', ',');
  size_t pos = 0;
  while ((pos = result.find(delimiter)) != std::string::npos) {
    result.replace(pos, delimiter.length(), ",");
  }
  return result;
}

int SumTokens(const std::string& input) {
  std::stringstream ss(input);
  std::string token;
  int sum = 0;
  std::vector<int> negatives;

  while (std::getline(ss, token, ',')) {
    if (token.empty()) {
      throw std::runtime_error("Invalid input format: empty token");
    }

    int num = std::stoi(token);
    if (num < 0) {
      negatives.push_back(num);
    } else if (num <= 1000) {
      sum += num;
    }
  }

  if (!negatives.empty()) {
    std::ostringstream err;
    err << "negatives not allowed:";
    for (size_t i = 0; i < negatives.size(); ++i) {
      err << " " << negatives[i];
      if (i < negatives.size() - 1) err << ",";
    }
    throw std::runtime_error(err.str());
  }

  return sum;
}

}  // namespace

int StringCalculator::Add(const std::string& numbers) {
  if (numbers.empty()) return 0;

  std::string input = numbers;
  std::string delimiter = ExtractDelimiter(input);
  std::string normalized = NormalizeDelimiters(input, delimiter);
  return SumTokens(normalized);
}