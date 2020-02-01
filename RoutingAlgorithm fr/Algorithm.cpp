//
// Created by manrif on 04/11/19.
//

#include <iostream>
#include "Algorithm.h"
#include "DFSGraph.h"

Algorithm::FloydWarshallResult const Algorithm::FloydWarshall(Matrix &costMatrix) {

    if (!costMatrix.isSquare()) {
        std::cout << "Cannot apply Floyd Warshall with non-square Matrix";
        exit(1);
    }

    Matrix distanceMatrix = Matrix(costMatrix.ySize(), costMatrix.xSize(), 50000);
    Matrix neighborMatrix = Matrix(costMatrix.ySize(), costMatrix.xSize(), 0);

    ulong len = costMatrix.ySize();
    int cost;

    for (int y = 0; y < len; y++) {
        for (int x = 0; x < len; x++) {
            if (y != x && (cost = costMatrix.get(x, y)) != 0) {
                distanceMatrix.set(x, y, cost);
            }
        }
    }

    int distance;

    for (int k = 0; k < len; ++k) {
        for (int y = 0; y < len; ++y) {
            for (int x = 0; x < len; ++x) {
                if (y == x) {
                    distanceMatrix.set(y, x, 0);
                } else if (distanceMatrix.get(y, x) > (distance = distanceMatrix.get(y, k) + distanceMatrix.get(k, x))) {
                    distanceMatrix.set(y, x, distance);
                    neighborMatrix.set(y, x, k);
                }
            }
        }
    }

    Matrix::PrintTransformation toInfinite = {50000, "∞"};
    distanceMatrix.applyPrintTransformation(toInfinite);
    neighborMatrix.applyPrintTransformation(toInfinite);

    return Algorithm::FloydWarshallResult {distanceMatrix, neighborMatrix};
}

const Matrix Algorithm::AdjacencyMatrixOfCluster(const DFSGraph &graph) {

    std::vector<std::vector<DFSGraph::Vertice>> const &sccGroups = graph.getVerticeData().getSCCGroups();

    ulong len = sccGroups.size();
    Matrix clusterMatrix(len);

    std::vector<DFSGraph::Vertice> sccGroupA, sccGroupB;
    int links;

    for (int y = 0; y < len; y++) {
        for (int x = 0; x < len; x++) {
            if (x == y) {
                continue;
            }

            links = 0;
            sccGroupA = sccGroups[y];
            sccGroupB = sccGroups[x];

            for (DFSGraph::Vertice const &verticeA: sccGroupA) {
                for (DFSGraph::Vertice const &verticeB: sccGroupB) {
                    if (graph.getReversedMatrix().get(verticeA.node, verticeB.node)) {
                        links++;
                    }
                }
            }

            clusterMatrix.set(y, x, links);
        }
    }

    return clusterMatrix;
}

