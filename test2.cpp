// #define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <iostream>

int main(void)
{
    httplib::Client cli("jsonplaceholder.typicode.com");
    if (auto res = cli.Get("/todos/1")) {
    if (res->status == httplib::StatusCode::OK_200) {
      std::cout << res->body << std::endl;
    }
  } else {
    auto err = res.error();
    std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
  }
    return 0;
    
}