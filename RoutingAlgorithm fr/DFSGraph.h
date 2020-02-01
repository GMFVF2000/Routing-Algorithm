//
// Created by manrif on 15/11/19.
//

#ifndef ROUTINGALGORITHM_DFSTREE_H
#define ROUTINGALGORITHM_DFSTREE_H


#include <vector>
#include "Matrix.h"

class DFSGraph {

public:

    struct Vertice {
        std::string name;
        int node;
        int preOrder;
        int postOrder;
        int preNode;
        int postNode;
        int sccGroup;
    };

    class VerticeData {

    public:

        explicit VerticeData(ulong count);

        void preOrderise(int node);

        void postOrderise(int node);

        void setSCCGroup(int node, int group);

        void setPreNode(int node, int preNode);

        void setPostNode(int node, int postNode);

        const int getPreNode(int node) const;

        const bool isPreVisited(int node) const;

        const bool isPostVisited(int node) const;

        const bool isGrouped(int node) const;

        const int setupPostNodes();

        const int getLastPostNode();

        const unsigned long size() const;

        const std::vector<std::vector<DFSGraph::Vertice>> &getSCCGroups() const;

        const std::vector<DFSGraph::Vertice> &getVertices() const;

    private:

        int currentPreOrder;
        int currentPostOrder;
        std::vector<std::vector<DFSGraph::Vertice>> sccGroups;
        std::vector<DFSGraph::Vertice> vertices;
    };

    static DFSGraph of(Matrix const &adjacencyMatrix);

    const Matrix &getAdjacencyMatrix() const;

    const Matrix &getReversedMatrix() const;

    const VerticeData &getVerticeData() const;

private:

    Matrix const adjacencyMatrix;
    Matrix const reversedMatrix;
    VerticeData const vertices;

    DFSGraph(Matrix const &adjacencyMatrix, Matrix const &reversedMatrix, const VerticeData &vertices);

    static void DFSPre(Matrix const &adjacencyMatrix, VerticeData &vertices, int node);

    static void DFSPost(Matrix const &adjacencyMatrix, VerticeData &vertices, int node);

    static void SCC(Matrix const &reversedMatrix, VerticeData &vertices, int node, int group);

    static bool isRoute(Matrix const &matrix, VerticeData &vertices, int from, int to);

};


#endif //ROUTINGALGORITHM_DFSTREE_H
