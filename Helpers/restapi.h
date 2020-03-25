#ifndef RESTAPI_H
#define RESTAPI_H

#define _TURN_OFF_PLATFORM_STRING
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

    observable<std::wstring> getString(const std::wstring &url) {
        return observable<>::create<std::wstring>([=](subscriber<std::wstring> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<T> getObject(const std::wstring &url) {
        return observable<>::create<T>([=](subscriber<T> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
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

    observable<T> getArray(const std::wstring &url) {
        return observable<>::create<T>([=](subscriber<T> s){
            client
            .request(methods::GET, url)
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
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

    observable<std::wstring> createObject(const std::wstring& url, const T& obj) {
        return observable<>::create<std::wstring>([=](subscriber<std::wstring> s){
            json j = obj;
            client
            .request(methods::POST, url, j.dump(), L"application/json")
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<std::wstring> updateObject(const std::wstring& url, const T& obj) {
        return observable<>::create<std::wstring>([=](subscriber<std::wstring> s){
            json j = obj;
            client
            .request(methods::PUT, url, j.dump(), L"application/json")
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<std::wstring> updateObject(const std::wstring& url, const std::wstring& body) {
        return observable<>::create<std::wstring>([=](subscriber<std::wstring> s){
            client
            .request(methods::PUT, url, body, L"text")
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
                    s.on_next(v);
                    s.on_completed();
                } catch (http_exception const&) {
                    s.on_error(std::current_exception());
                }
            })
            .wait();
        });
    }

    observable<std::wstring> deleteObject(const std::wstring& url) {
        return observable<>::create<std::wstring>([=](subscriber<std::wstring> s){
            client
            .request(methods::DEL, url)
            .then([](http_response response) -> pplx::task<std::wstring> {
                return response.extract_string();
            })
            .then([&](pplx::task<std::wstring> previousTask) {
                try {
                    std::wstring const & v = previousTask.get();
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
    RestApi() : RestApiBase<T>(L"https://zwvista2.tk/lolly/api.php/records/") {}
};

#endif // RESTAPI_H
