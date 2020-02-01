#include <iostream>
#include "Matrix.h"
#include "Algorithm.h"
#include "DFSGraph.h"
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

const std::string file(const std::string &fileName) {
    return "/home/manrif/Desktop/Master/RoutingAlgorithm/Examples/" + fileName;
}

void drawLine() {
    std::cout << std::endl;
    for (int i = 0; i < 60; ++i) {
        std::cout << "=";
    }
    std::cout << std::endl << std::endl;
}

int main() {

    /****************** Question 1: Routing table ****************/

    Matrix costMatrix = Matrix::fromFile(file("cost"));

    std::cout << "Q1) Applying FloydWarshall algorithm on the cost matrix below." << std::endl << std::endl;

    std::cout << "Source cost matrix :" << std::endl << std::endl;
    std::cout << costMatrix << std::endl;

    Algorithm::FloydWarshallResult floydWarshall = Algorithm::FloydWarshall(costMatrix);

    std::cout << "Distance table of the cost matrix :" << std::endl << std::endl;
    std::cout << floydWarshall.distanceMatrix << std::endl;

    std::cout << "Routing table of the cost matrix :" << std::endl << std::endl;
    std::cout << floydWarshall.neighborMatrix;

    drawLine();
    /****************** Question 2: Cluster search ****************/

    Matrix adjacencyMatrix = Matrix::fromFile(file("adjacency"));

    std::cout << "Q2) Search of clusters with adjacency matrix below:" << std::endl << std::endl;

    DFSGraph graph = DFSGraph::of(adjacencyMatrix);

    std::cout << "Source adjacency matrix:" << std::endl << std::endl;
    std::cout << graph.getAdjacencyMatrix() << std::endl;

    std::cout << "DFS preOrders and postOrders results :" << std::endl << std::endl;

    const DFSGraph::VerticeData &verticeData = graph.getVerticeData();

    for (DFSGraph::Vertice const &vertice : verticeData.getVertices()) {
        std::cout <<
            "Node " + vertice.name +
            ": PreOrder = " + std::to_string(vertice.preOrder) +
            ", PostOrder = " + std::to_string(vertice.postOrder)
            << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Reversed matrix for SCC (clusters) calculation :" << std::endl << std::endl;

    std::cout << graph.getReversedMatrix() << std::endl;

    std::cout << "SCC (clusters) results (based on PostOrders and reversed matrix) :" << std::endl << std::endl;

    std::vector<std::vector<DFSGraph::Vertice>> const &sccGroups = verticeData.getSCCGroups();
    std::vector<DFSGraph::Vertice> sccGroup;
    for (int i = 0; i < sccGroups.size(); ++i) {
        sccGroup = sccGroups[i];
        sort(sccGroup.begin(), sccGroup.end(), [](const auto &leftVertice, const auto &rightVertice){
            return leftVertice.node < rightVertice.node;
        });
        std::cout << "SCC[" +  std::to_string(i + 1) + "] : {";
        for (int j = 0; j < sccGroup.size(); ++j) {
            std::cout << sccGroup[j].name + (j != sccGroup.size() - 1 ? ", " : "");
        }
        std::cout << "}" << std::endl;
    }

    drawLine();
    /****************** Question 3: Adjacency Matrix of Clusters ****************/

    std::cout << "Q3) Adjacency Matrix Of Cluster :" << std::endl;

    std::cout << "(Running DFS like Q2)." << std::endl << std::endl;

    Matrix adjacencyMatrixOfCluster = Algorithm::AdjacencyMatrixOfCluster(graph);
    std::cout << adjacencyMatrixOfCluster << std::endl;

    return 0;
}