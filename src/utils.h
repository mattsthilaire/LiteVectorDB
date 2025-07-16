#include<string>
#include<vector>

#include "vector.h"


#ifndef UTILS_H
#define UTILS_H

std::vector<std::string> parse_tokens(std::string s, char delimiter = ',');
std::vector<float> strings2floats(std::vector<std::string> tokens);
Vector strings2vector(std::string input); 
std::vector<Vector> file2vectors(std::string filename);

#endif
