#pragma once
#include <exception>
#include <string>

class SimulationException : public std::exception {
private:
    std::string message;
public:
    explicit SimulationException(const std::string& msg) : message(msg) {}
    
    // Surcharge de la méthode what() pour afficher le message
    const char* what() const noexcept override {
        return message.c_str();
    }
};