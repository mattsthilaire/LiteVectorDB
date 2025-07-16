#include<iostream>
#include<cmath>
#include<map>
#include<stdexcept>
#include<vector>
#include "vector.h"

int Vector::get_dim() {
    return this->dim; // no need to use this->dim since we're in the vector namespace in the function definition
}

std::vector<float> Vector::get_values() {
    return this->values;
}

void Vector::print_values() {

    std::cout << "[";
    for(int i = 0; i < values.size(); i++) {
	if(i < values.size() - 1) {
	    std::cout << values[i] << ",";
	} else {
	    std::cout << values[i] << "]" << std::endl;
	}
    }
}

float Vector::dot(Vector v) {
    if (v.get_dim() != this->dim) {
	throw std::runtime_error("Vectors must have same dimensions");
    }

    float dot_product = 0.0f;

    for(int i = 0; i < v.get_dim(); i++) {
	dot_product += (v.get_values()[i] * this->values[i]);
    }

    return dot_product;
}

// does the vector norm of a...vector
float Vector::norm() {
    
    float sum = 0.0f;
    for(int i = 0; i < this->get_dim(); i++) {
	sum += (this->values[i] * this->values[i]);
    }

    return std::sqrt(sum);
}

float Vector::cosine_similarity(Vector v) {
    return this->dot(v) / (this->norm() * v.norm());
}

float Vector::l2_distance(Vector v) {

    float sum = 0.0f;
    for(int i = 0; i < v.get_dim(); i++) {
	sum += powf((this->values[i] - v.get_values()[i]), 2);
    }

    return std::sqrt(sum);
}

float Vector::similarity(Vector v, std::string method) {

    std::map<std::string, int> m = {
	{"l2", 1}, 
	{"cosine", 2}
    };
    int choice = m.count(method);

    switch(choice) {
	case 1:
	    return this->l2_distance(v);
	case 2:
	    return this->cosine_similarity(v);
	default:
	    throw std::runtime_error("Distance method not supported");
    }
}

