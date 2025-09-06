import argparse
import random

def main(args):
    
    with open(args.filename, "w") as f:

        for _ in range(args.num_vectors):
            vec = [str(random.random()) for _ in range(args.dims)]
            f.write(",".join(vec) + "\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            prog="Make Vectors", 
            description="Make vectors for DB",
            epilog="Vector creater for C++ code")
    parser.add_argument("filename")
    parser.add_argument("--dims", type=int, help="VectorDB dimensions")
    parser.add_argument("--num_vectors", type=int, help="Number of vectors to create")
    args = parser.parse_args()
    main(args)
