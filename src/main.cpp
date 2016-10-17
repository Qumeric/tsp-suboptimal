#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <Graph.h>
#include <ISolver.h>
#include <BruteforceSolver.h>
#include <AnnealingSolver.h>
#include <ClosestNeighbourSolver.h>
#include <TwoOptimalSolver.h>
#include <AntSolver.h>
#include <BranchAndBoundSolver.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Usage: ./tsp <number-of-points>" << std::endl;
        return 0;
    }

    size_t n = std::stoi(argv[1]);

    Graph g(n);

    ISolver *bruteForce = new BruteforceSolver;
    ISolver *annealingSolver = new AnnealingSolver;
    ISolver *closestNeighbourSolver = new ClosestNeighbourSolver;
    ISolver *twoOptimalSolver = new TwoOptimalSolver;
    ISolver *antSolver = new AntSolver;
    ISolver *branchAndBoundSolver = new BranchAndBoundSolver;


    std::cout << "Brute force have found this answer: " << bruteForce->solve(g) << std::endl;
    std::cout << "Annealing imitation have found this answer: " << annealingSolver->solve(g) << endl;
    std::cout << "Closest neighbor have found this answer: " << closestNeighbourSolver->solve(g) << endl;
    std::cout << "2-OPT greedy solution have found this answer: " << twoOptimalSolver->solve(g) << endl;
    std::cout << "Ant algorithm have found this answer: " << antSolver->solve(g) << endl;
    std::cout << "Branch and bound have found this answer: " << branchAndBoundSolver->solve(g) << endl;
    //fout.open("graph.txt");
    /*if (argc > 2) {
        ALPHA = stof(argv[2]);
        BETA = stof(argv[3]);
        Q = stof(argv[4]);
        FORGET = stof(argv[5]);
        MAX_PHEROMONE_INIT = stof(argv[6]);
    }

    get_mst(graph, INITIAL_VERTEX, n);
    if (argc<=2) {
    } else {
        cout << solve_ant(graph, n) << endl;
    }
     */
}
