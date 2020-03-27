#include "uri.h"
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

namespace {
  string_t encimpl(string_t::value_type v) {
    if (isalnum(v))
      return string_t()+v;

    std::wostringstream enc;
    enc << '%' << std::setw(2) << std::setfill(L'0') << std::hex << std::uppercase << int(static_cast<unsigned char>(v));
    return enc.str();
  }
}

string_t urlencode(const string_t& url) {
  // Find the start of the query string_t
  const string_t::const_iterator start = std::find(url.begin(), url.end(), '?');

  // If there isn't one there's nothing to do!
  if (start == url.end())
    return url;

  // store the modified query string_t
  string_t qstr;

  std::transform(start+1, url.end(),
                 // Append the transform result to qstr
                 boost::make_function_output_iterator(boost::bind(static_cast<string_t& (string_t::*)(const string_t&)>(&string_t::append),&qstr,_1)),
                 encimpl);
  return string_t(url.begin(), start+1) + qstr;
}
