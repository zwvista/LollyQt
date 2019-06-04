#ifndef OPTIONAL2JSON_H
#define OPTIONAL2JSON_H

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

// partial specialization (full specialization works too)
namespace nlohmann {
    template <typename T>
    struct adl_serializer<boost::optional<T>> {
        static void to_json(json& j, const boost::optional<T>& opt) {
            if (opt == boost::none) {
                j = nullptr;
            } else {
              j = *opt; // this will call adl_serializer<T>::to_json which will
                        // find the free function to_json in T's namespace!
            }
        }

        static void from_json(const json& j, boost::optional<T>& opt) {
            if (j.is_null()) {
                opt = boost::none;
            } else {
                opt = j.get<T>(); // same as above, but with
                                  // adl_serializer<T>::from_json
            }
        }
    };
}

#endif // OPTIONAL2JSON_H
