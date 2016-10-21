#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <Graph.h>
#include <ISolver.h>
#include <BruteforceSolver.h>
#include <AnnealingSolver.h>
#include <TwoOptimalSolver.h>
#include <ClosestNeighbourSolver.h>
#include <AntSolver.h>
#include <BranchAndBoundSolver.h>
#include <Helpers.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"

TEST_CASE("Check if returned length really matches returned path's length", "[wtf]") {
    using std::cout;
    using std::endl;

    Graph g(12);

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
    REQUIRE(bruteForce->getPath().size() == Helpers::calc_length(g, bruteForce->getPath()));
    REQUIRE(annealingSolver->getPath().size() == Helpers::calc_length(g, annealingSolver->getPath()));
    REQUIRE(closestNeighbourSolver->getPath().size() == Helpers::calc_length(g, closestNeighbourSolver->getPath()));
    REQUIRE(twoOptimalSolver->getPath().size() == Helpers::calc_length(g, twoOptimalSolver->getPath()));
    REQUIRE(antSolver->getPath().size() == Helpers::calc_length(g, antSolver->getPath()));
    REQUIRE(branchAndBoundSolver->getPath().size() == Helpers::calc_length(g, branchAndBoundSolver->getPath()));
}

#pragma clang diagnostic pop