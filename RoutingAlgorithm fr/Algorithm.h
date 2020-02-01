//
// Created by manrif on 04/11/19.
//

#ifndef ROUTINGALGORITHM_ALGORITHM_H
#define ROUTINGALGORITHM_ALGORITHM_H

#include "Matrix.h"
#include "DFSGraph.h"

namespace Algorithm {

    struct FloydWarshallResult {
        Matrix const distanceMatrix;
        Matrix const neighborMatrix;
    };

    const FloydWarshallResult FloydWarshall(Matrix &costMatrix);

    const Matrix AdjacencyMatrixOfCluster(const DFSGraph &graph);

};


#endif //ROUTINGALGORITHM_ALGORITHM_H
