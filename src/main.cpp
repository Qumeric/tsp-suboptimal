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


#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
int main(int argc, char *argv[]) {
    using std::cout;
    using std::endl;
    if (argc == 1) {
        std::cout << "Usage: ./tsp <number-of-points>" << std::endl;
        return 0;
    }

    size_t n = std::stoi(argv[1]);

    Graph g(n);

    ISolver *bruteForce = new BruteforceSolver(g);
    ISolver *annealingSolver = new AnnealingSolver(g);
    ISolver *closestNeighbourSolver = new ClosestNeighbourSolver(g);
    ISolver *twoOptimalSolver = new TwoOptimalSolver(g);
    ISolver *antSolver = new AntSolver(g);
    ISolver *branchAndBoundSolver = new BranchAndBoundSolver(g);


    cout << "Brute force have found this answer: " << bruteForce->solve() << endl;
    cout << "Annealing imitation have found this answer: " << annealingSolver->solve() << endl;
    cout << "Closest neighbor have found this answer: " << closestNeighbourSolver->solve() << endl;
    cout << "2-OPT greedy solution have found this answer: " << twoOptimalSolver->solve() << endl;
    cout << "Ant algorithm have found this answer: " << antSolver->solve() << endl;
    cout << "Branch and bound have found this answer: " << branchAndBoundSolver->solve() << endl;

    cout << "Brute force len: " << bruteForce->getPath().size() << endl;
    cout << "Annealing imitation len: " << annealingSolver->getPath().size() << endl;
    cout << "Closest neighbor len: " << closestNeighbourSolver->getPath().size() << endl;
    cout << "2-OPT greedy solution len: " << twoOptimalSolver->getPath().size() << endl;
    cout << "Ant algorithm len: " << antSolver->getPath().size() << endl;
    cout << "Branch and bound len: " << branchAndBoundSolver->getPath().size() << endl;
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

#pragma clang diagnostic pop
