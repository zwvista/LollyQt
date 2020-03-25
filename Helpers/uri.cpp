#include "uri.h"
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

namespace {
  std::wstring encimpl(std::wstring::value_type v) {
    if (isalnum(v))
      return std::wstring()+v;

    std::wostringstream enc;
    enc << '%' << std::setw(2) << std::setfill(L'0') << std::hex << std::uppercase << int(static_cast<unsigned char>(v));
    return enc.str();
  }
}

std::wstring urlencode(const std::wstring& url) {
  // Find the start of the query wstring
  const std::wstring::const_iterator start = std::find(url.begin(), url.end(), '?');

  // If there isn't one there's nothing to do!
  if (start == url.end())
    return url;

  // store the modified query wstring
  std::wstring qstr;

  std::transform(start+1, url.end(),
                 // Append the transform result to qstr
                 boost::make_function_output_iterator(boost::bind(static_cast<std::wstring& (std::wstring::*)(const std::wstring&)>(&std::wstring::append),&qstr,_1)),
                 encimpl);
  return std::wstring(url.begin(), start+1) + qstr;
}
