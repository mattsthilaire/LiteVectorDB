#include<string>
#include<vector>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
	int dim;
	std::vector<float> values;

    public:
	Vector(): dim(0) {};
	Vector(int dim) : dim(dim) {};
	Vector(int dim, std::vector<float> values) : dim(dim), values(values) {};

	int get_dim();
	std::vector<float> get_values(); 
	float norm();
	float dot(Vector v);
	void print_values();
	float cosine_similarity(Vector v);
	float l2_distance(Vector v);
	float similarity(Vector v, std::string method = "l2");
};

#endif
