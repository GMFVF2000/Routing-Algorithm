//
// Created by manrif on 15/11/19.
//

#include <iostream>
#include <sstream>
#include "DFSGraph.h"

DFSGraph::VerticeData::VerticeData(ulong count): currentPreOrder(0), currentPostOrder(0) {
    vertices = std::vector<Vertice>(static_cast<unsigned long>(count));
    sccGroups = std::vector<std::vector<DFSGraph::Vertice>>();

    for (int i = 0; i < count; ++i) {
        vertices[i] = Vertice{std::to_string(i + 1), i, 0, 0, 0, 0};
    }
}

void DFSGraph::VerticeData::preOrderise(const int node) {
    vertices[node].preOrder = ++currentPreOrder;
}

void DFSGraph::VerticeData::postOrderise(const int node) {
    vertices[node].postOrder = ++currentPostOrder;
}

void DFSGraph::VerticeData::setSCCGroup(const int node, const int group) {
    vertices[node].sccGroup = group;
    if (group > sccGroups.size()) {
        while (sccGroups.size() < group) {
            sccGroups.emplace_back();
        }
    }
    sccGroups[group - 1].push_back(vertices[node]);
}

void DFSGraph::VerticeData::setPreNode(const int node, const int preNode) {
    vertices[node].preNode = preNode;
}

void DFSGraph::VerticeData::setPostNode(const int node, const int postNode) {
    vertices[node].postNode = postNode;
}

const bool DFSGraph::VerticeData::isPreVisited(const int node) const {
    return vertices[node].preOrder > 0;
}

const bool DFSGraph::VerticeData::isPostVisited(const int node) const {
    return vertices[node].postOrder > 0;
}

const bool DFSGraph::VerticeData::isGrouped(const int node) const {
    return vertices[node].sccGroup > 0;
}

const unsigned long DFSGraph::VerticeData::size() const {
    return vertices.size();
}

const int DFSGraph::VerticeData::getPreNode(const int node) const {
    return vertices[node].preNode;
}

DFSGraph::DFSGraph(Matrix const &adjacencyMatrix, Matrix const &reversedMatrix, const DFSGraph::VerticeData &vertices)
    :  adjacencyMatrix(adjacencyMatrix), reversedMatrix(reversedMatrix), vertices(vertices) {

}

const int DFSGraph::VerticeData::setupPostNodes() {
    for (DFSGraph::Vertice const &i: vertices) {
        setPostNode(i.node, i.postOrder);
    }
    return getLastPostNode();
}

const int DFSGraph::VerticeData::getLastPostNode() {
    int lastPostNode = 0;
    int max = 0;
    for (DFSGraph::Vertice const &i: vertices) {
        if (i.postNode > max) {
            max = i.postNode;
            lastPostNode = i.node;
        }
    }
    return lastPostNode;
}

const std::vector<std::vector<DFSGraph::Vertice>> &DFSGraph::VerticeData::getSCCGroups() const {
    return sccGroups;
}

const std::vector<DFSGraph::Vertice> &DFSGraph::VerticeData::getVertices() const {
    return vertices;
}

DFSGraph DFSGraph::of(Matrix const &adjacencyMatrix) {
    if (!adjacencyMatrix.isSquare()) {
        std::cout << "Cannot apply DFS with non-square Matrix";
        exit(1);
    }

    VerticeData vertices = VerticeData(adjacencyMatrix.ySize());
    DFSPre(adjacencyMatrix, vertices, 0);
    Matrix reversedMatrix = adjacencyMatrix.swap();
    const int lastPostNode = vertices.setupPostNodes();
    SCC(reversedMatrix, vertices, lastPostNode, 1);

    return {adjacencyMatrix, reversedMatrix, vertices};
}

void DFSGraph::DFSPre(Matrix const &adjacencyMatrix, VerticeData &vertices, int node) {
    vertices.preOrderise(node);

    bool found;
    for (int i = node; i < vertices.size(); i++) {

        found = false;

        for (int j = 0; j < vertices.size(); j++) {
            if (isRoute(adjacencyMatrix, vertices, i, j)) {
                found = true;
                vertices.setPreNode(j, i);
                DFSPre(adjacencyMatrix, vertices, j);
            }
        }

        if (!found) {
            DFSPost(adjacencyMatrix, vertices, i);
            return;
        }
    }
}

void DFSGraph::DFSPost(Matrix const &adjacencyMatrix, DFSGraph::VerticeData &vertices, int node) {
    if (vertices.isPostVisited(node)) {
        return;
    }
    vertices.postOrderise(node);

    bool found = false;
    int j = 0;
    int previousNode = vertices.getPreNode(node);

    while (!found && j < vertices.size()) {
        found = isRoute(adjacencyMatrix, vertices, previousNode, j);
        j++;
    }

    if (!found) {
        DFSPost(adjacencyMatrix, vertices, previousNode);
    }
}

void DFSGraph::SCC(Matrix const &reversedMatrix, DFSGraph::VerticeData &vertices, const int node, const int group) {
    if (vertices.isGrouped(node)) {
        return;
    }
    vertices.setSCCGroup(node, group);
    vertices.setPostNode(node, 0);

    bool found = false;

    for (int i = 0; i < vertices.size(); i++) {
        if (i != node && !vertices.isGrouped(i) && reversedMatrix.get(node, i)) {
            found = true;
            SCC(reversedMatrix, vertices, i, group);
        }
    }

    if (!found) {
        SCC(reversedMatrix, vertices, vertices.getLastPostNode(), group + 1);
    }
}

bool DFSGraph::isRoute(Matrix const &matrix, DFSGraph::VerticeData &vertices, int from, int to) {
    return from != to && !vertices.isPreVisited(to) && matrix.get(from, to) == 1;
}

const Matrix &DFSGraph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

const Matrix &DFSGraph::getReversedMatrix() const {
    return reversedMatrix;
}

const DFSGraph::VerticeData &DFSGraph::getVerticeData() const {
    return vertices;
}
