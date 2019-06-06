#include "uri.h"
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

namespace {
  std::string encimpl(std::string::value_type v) {
    if (isalnum(v))
      return std::string()+v;

    std::ostringstream enc;
    enc << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << int(static_cast<unsigned char>(v));
    return enc.str();
  }
}

std::string urlencode(const std::string& url) {
  // Find the start of the query string
  const std::string::const_iterator start = std::find(url.begin(), url.end(), '?');

  // If there isn't one there's nothing to do!
  if (start == url.end())
    return url;

  // store the modified query string
  std::string qstr;

  std::transform(start+1, url.end(),
                 // Append the transform result to qstr
                 boost::make_function_output_iterator(boost::bind(static_cast<std::string& (std::string::*)(const std::string&)>(&std::string::append),&qstr,_1)),
                 encimpl);
  return std::string(url.begin(), start+1) + qstr;
}
