#include <fstream>
#include <iostream>
#include<string>
#include<vector>

#include "utils.h"
#include "vector.h"
#include "vector_db.h"


int main() {

    int vector_dims;
    std::cout << "Select your vector database dimensions: ";
    std::cin >> vector_dims;

    VectorDB vectorDB(vector_dims);

    Vector v1{2, std::vector<float>({2.3, 7.6})};
    Vector v2{2, std::vector<float>({8.7, -1.6})};

    std::cout << v1.dot(v2) << std::endl;
    std::cout << v1.similarity(v2, "l2") << std::endl;
    std::cout << v1.norm() << " " << v2.norm() << std::endl;

    int choice = 0;

    while(true) {

	std::cout << "Make a VectorDB choice\n"
	    "1.) Add a vector to the DB\n" 
	    "2.) Find a vector in the DB by id\n"
	    "3.) Find the nearest vector in the DB\n" 
	    "4.) Show all vectors in DB\n"
	    "5.) Compare a vector\n"
	    "6.) Add vectors from file\n"
	    "7.) Exit" << std::endl;

	std::cin >> choice;

	switch(choice) {
	    case 1: {
		std::string input = "";
		std::cout << "Enter your number separated by a ',': "; 
		std::cin >> input;
		vectorDB.add_vector(strings2vector(input));
		break;
		}
	    case 2: {
		int id = 0;
		std::cout << "Find vector" << std::endl;
		std::cout << "Enter the id of the vector you want to find: ";
		std::cin >> id;
		vectorDB.get_vector(id);
		break;
		}
	    case 3: { 
		std::string input = "";
		std::cout << "Enter your numbers separated by a ',': ";
		std::cin >> input;
		std::vector<std::pair<int, float>> compare_results = vectorDB.similarity_search(strings2vector(input), 1);
		std::cout << compare_results[0].first << " " << compare_results[0].second << " ";
		vectorDB.get_vector(compare_results[0].first).print_values();
		break;
		}
	    case 4: {
		vectorDB.print_vectors();
		break;
		}
	    case 5: {
		std::string input = "";
		std::cout << "Enter your numbers separated by a ',': ";
		std::cin >> input;
		std::vector<std::pair<int, float>> compare_results = vectorDB.similarity_search(strings2vector(input));
		for(int i = 0; i < compare_results.size(); i++) {
		    std::cout << compare_results[i].first << " " << compare_results[i].second << " ";
		    vectorDB.get_vector(compare_results[i].first).print_values();
		}
		break;
		}
	    case 6: {
		std::string filename;
		std::cout << "Enter your filename: ";
		std::cin >> filename;
		vectorDB.add_vectors(file2vectors(filename));
		break;
		}
	    case 7:
		std::cout << "Exiting" << std::endl;
		goto end_program;
	    default:
		std::cout << "Please make a choice 1-4" << std::endl;
	}
    }

    end_program:
	return 0;
}
