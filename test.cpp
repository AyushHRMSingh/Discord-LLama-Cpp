#include <httplib.h>
#include <iostream>

int main(void)
{
    httplib::Server svr;
    httplib::Client cli("localhost", 8080);
    svr.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
        std::string id = req.get_param_value("id");
        res.set_content("id=" + id, "text/plain");
    });
    svr.listen("0.0.0.0", 8080);
    return 0;
    
}