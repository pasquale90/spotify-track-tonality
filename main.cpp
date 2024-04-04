#include <iostream>
#include <string>
#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

std::string update_result(std::string client_id,std::string secret_id, std::string redirect_uri) {
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive

// Translate Python Code?
    // py::module_ spotipy = py::module_::import("spotipy");
    // py::print(spotipy.attr("path"));

// Run Python Code...
    // Import module
    py::module_ spotifey = py::module_::import("pymain");
    py::object result = spotifey.attr("main")(client_id,secret_id,redirect_uri);
    return result.cast<std::string>();
}

int main(){

    // credentials    
    std::string client_id="YOUR_CLIENT_ID";
    std::string secret_id="YOUR_SECRET_ID";
    std::string redirect_uri="YOUR_REDIRECT_URI";

    std::string final_result = update_result(client_id, secret_id, redirect_uri);
    std::cout<<"Result (C++) :\n"<<final_result<<std::endl;
    return 0;
}