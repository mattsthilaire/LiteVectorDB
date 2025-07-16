#include<functional>
#include<iostream>
#include<immintrin.h>
#include<queue>
#include<stdexcept>
#include<vector>
#include<utility>
#include "vector.h"
#include "vector_db.h"

// struct for comparing id's in the vector DB
struct CompareSearch {
    float score;
    int id;

    bool operator<(const CompareSearch& other) const {
	return score < other.score;
    }
};

VectorDB::VectorDB(int dims, std::vector<Vector> vectors) : dims(dims), num_vectors(0) {

    if(dims <= 0) {
	throw std::runtime_error("Vector dimensions must be greater than 0");
    }
    for(int i = 0; i < vectors.size(); i++) {
	
	// check to ensure all vectors passed have the same size
	if(dims != vectors[i].get_dim()) {
	    throw std::runtime_error("Vectors passed do not have the same size.");
	}

	this->vectors.insert({this->num_vectors, vectors[i]});
	this->num_vectors += 1;
    }
}

Vector VectorDB::get_vector(int id) {
    if(this->vectors.find(id) == this->vectors.end()) {
	throw std::runtime_error("Key does not exist in DB.");
    }
    return this->vectors[id];
}

int VectorDB::get_dims() {
    return this->dims;
}

void VectorDB::add_vector(Vector v) {

    if(v.get_dim() != this->dims) {
	throw(std::runtime_error("Vector length doesn't equal vector DB dims"));
    }

    this->vectors.insert({this->num_vectors, v});
    this->num_vectors += 1;
}

void VectorDB::add_vectors(std::vector<Vector> vecs) {
    for(Vector v : vecs) {
	this->add_vector(v);
    }
}

void VectorDB::print_vectors() {
    for(int i = 0; i < this->num_vectors; i++) {
	std::cout << "id: " << i << " , ";
	this->vectors[i].print_values();
    }
}

// iterative search for top 5 closest vectors
std::vector<std::pair<int, float>> VectorDB::similarity_search(Vector v, int topk) {
    std::priority_queue<CompareSearch> results;

    for(int i = 0; i < this->num_vectors; i++) {
	float score = v.similarity(Vector(this->vectors[i]));
	results.push({score, i});

	// Evict from queue if larger than the topk
	if(results.size() > topk) {
	    results.pop();
	}
    }

    std::vector<std::pair<int, float>> vec_results;
    while(!results.empty()) {
	CompareSearch tmp = results.top();
	results.pop();
	vec_results.push_back({tmp.id, tmp.score});
    }

    return vec_results;
}
