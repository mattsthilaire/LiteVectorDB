#include<map>
#include<vector>
#include<utility>
#include "vector.h"

#ifndef VECTORDB_H
#define VECTORDB_H

class VectorDB {
    private:
	int dims;
	int num_vectors;
	std::map<int, Vector> vectors;

    public:
	VectorDB() : dims(2), num_vectors(0) {};
	VectorDB(int dims) : dims(dims), num_vectors(0) {};
	VectorDB(int dims, std::vector<Vector> vectors); // this will be a constructor that's a little more involved
	Vector get_vector(int id);
	void add_vector(Vector v);
	void add_vectors(std::vector<Vector> vecs);
	void print_vectors();
	Vector dot(Vector v);
	int get_dims();
	std::vector<std::pair<int, float>> similarity_search(Vector v, int topk = 5);

};



#endif
