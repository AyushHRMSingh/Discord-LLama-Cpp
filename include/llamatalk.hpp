#include <httplib.h>
#include <iostream>
#include <json.hpp>
#include <unordered_map>
using json = nlohmann::json;

class LLamaTalk {
    public:
        LLamaTalk() = default;
        LLamaTalk(const std::string& url, int port) : cli(url, port) {
            // cli.set_connection_timeout(std::chrono::minutes(10));
            // cli.set_keep_alive(true);
            cli.set_read_timeout(std::chrono::minutes(5));
        };
        std::unordered_map<std::string, std::string> get_models() {
            if (auto res = cli.Get("/api/tags")) {
                if (res->status == httplib::StatusCode::OK_200) {
                    json modellist = json::parse(res->body);
                    std::unordered_map<std::string, std::string> modelmap;
                    for (int i = 0; i < modellist["models"].size(); i++) {
                        modelmap[modellist["models"].at(i)["name"].get<std::string>()] = modellist["models"].at(i)["model"].get<std::string>();
                    }
                    return modelmap;
                }
            } else {
                auto err = res.error();
                std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
            }
            return {};
        };

        std::string chat(std::string modelname, std::string prompt) {
            std::string jsonbody = "{ \"model\" : \""+modelname+"\", \"prompt\" : \""+prompt+"\", \"stream\" : false, \"num_predict\" : 25}";
            bool success = false;
            while (!success) {
                if (auto res = cli.Post("/api/generate", jsonbody, "application/json")) {
                    if (res->status == httplib::StatusCode::OK_200) {
                        json response = json::parse(res->body);
                        success = true;
                        return response["response"];
                    } else {
                        std::cout << "error code: "<<res->status<< std::endl;
                        std::cout << "error : "<<res->body<< std::endl;
                    }
                } else {
                    auto err = res.error();
                    std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
                }
            }
                return "Errored out";
            };
    private:
        httplib::Client cli;
        httplib::Params params;
};