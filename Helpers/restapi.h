#ifndef RESTAPI_H
#define RESTAPI_H

#include "Helpers/string_t.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

#include "rx.h"
#include <nlohmann/json.hpp>
using nlohmann::json;

template<class T>
struct RestApiBase {
    http_client client;

    RestApiBase(const uri &base_uri) : client(base_uri) {}

    observable<string_t> getString(const string_t &url) {
        return observable<>::create<string_t>([=](subscriber<string_t> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<T> getObject(const string_t &url) {
        return observable<>::create<T>([=](subscriber<T> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    json j = json::parse(v);
                    T t = j;
                    s.on_next(t);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<T> getArray(const string_t &url) {
        return observable<>::create<T>([=](subscriber<T> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    json j = json::parse(v);
                    std::vector<T> vec = j;
                    for(const auto& t : vec)
                        s.on_next(t);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<string_t> createObject(const string_t& url, const T& obj) {
        return observable<>::create<string_t>([=](subscriber<string_t> s){
            json j = obj;
            auto s1 = j.dump();
            string_t s2(s1.begin(), s1.end());
            client
            .request(methods::POST, url, s2, _XPLATSTR("application/json"))
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<string_t> updateObject(const string_t& url, const T& obj) {
        return observable<>::create<string_t>([=](subscriber<string_t> s){
            json j = obj;
            auto s1 = j.dump();
            string_t s2(s1.begin(), s1.end());
            client
            .request(methods::PUT, url, s2, _XPLATSTR("application/json"))
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<string_t> updateObject(const string_t& url, const string_t& body) {
        return observable<>::create<string_t>([=](subscriber<string_t> s){
            client
            .request(methods::PUT, url, body, _XPLATSTR("text"))
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<string_t> deleteObject(const string_t& url) {
        return observable<>::create<string_t>([=](subscriber<string_t> s){
            client
            .request(methods::DEL, url)
            .then([](http_response response) -> pplx::task<string_t> {
                return response.extract_string();
            })
            .then([&](pplx::task<string_t> previousTask) {
                try {
                    string_t const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }
};

template<class T>
struct RestApi : RestApiBase<T> {
    RestApi() : RestApiBase<T>(_XPLATSTR("https://zwvista2.tk/lolly/api.php/records/")) {}
};

#endif // RESTAPI_H
