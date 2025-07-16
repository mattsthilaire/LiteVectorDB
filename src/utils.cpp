#include<fstream>
#include<string>
#include<vector>

#include "utils.h"
#include "vector.h"

std::vector<std::string> parse_tokens(std::string s, char delimiter) {
    
    std::vector<std::string> tokens;
    std::string curr = "";
    for(int i = 0; i < s.size(); i++) {
	if(s[i] == ',') {
	    tokens.push_back(curr);
	    curr = "";
	} else {
	    curr += s[i];
	}
    }

    // if a comma ends the line, we ignore the next element...at our own peril
    if(curr == "") {
	return tokens;
    }

    // in the case that we have some left over string to add
    tokens.push_back(curr);

    return tokens;
}

std::vector<float> strings2floats(std::vector<std::string> tokens) {
    
    std::vector<float> floats;
    for(int i = 0; i < tokens.size(); i++) {
	floats.push_back(std::stof(tokens[i]));
    }

    return floats;
}

Vector strings2vector(std::string input) {
    std::vector<std::string> string_tokens = parse_tokens(input);
    std::vector<float> floats = strings2floats(string_tokens);

    return Vector(floats.size(), floats);
}

std::vector<Vector> file2vectors(std::string filename) {
    std::ifstream input_file(filename);

    std::string line;
    std::vector<Vector> vectors;
    while(std::getline(input_file, line)) {
	vectors.push_back(strings2vector(line));
    }

    return vectors;
}
