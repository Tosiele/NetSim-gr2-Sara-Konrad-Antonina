//
// Created by konfe on 24.01.2026.
//

#include "../include/factory.hpp"
ParsedLineData parse_line(const std::string &line) {
    ParsedLineData parsed_line;
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    std::getline(token_stream, token, delimiter);


    if (token == "LOADING_RAMP") {
        parsed_line.element_type = ElementType::RAMP;
    }
    else if (token == "WORKER") {
        parsed_line.element_type = ElementType::WORKER;
    }
    else if (token == "STOREHOUSE") {
        parsed_line.element_type = ElementType::STOREHOUSE;
    }
    else if (token == "LINK") {
        parsed_line.element_type = ElementType::LINK;
    }
    else {
        throw std::invalid_argument("No matching tag");
    }

    std::string key;
    std::string value;
    while (std::getline(token_stream, token, delimiter)) {
        std::istringstream keyval_stream(token);
        char delim = '=';
        std::getline(keyval_stream, key, delim);
        std::getline(keyval_stream, value, delimiter);
        parsed_line.parameters.emplace(key, value);
    }

    return parsed_line;
}
