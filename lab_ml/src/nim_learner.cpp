/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    if(startingTokens == 0) {
      return;
    }
    g_.insertVertex("p1-"+std::to_string(startingTokens));
    g_.insertVertex("p2-"+std::to_string(startingTokens));
    g_.insertVertex("p1-"+std::to_string(startingTokens -1));
      g_.insertVertex("p2-"+std::to_string(startingTokens -1));
      g_.insertEdge("p1-"+ std::to_string(startingTokens), "p2-" + std::to_string(startingTokens - 1));
      g_.insertEdge("p2-"+ std::to_string(startingTokens), "p1-" + std::to_string(startingTokens - 1));
      g_.setEdgeWeight("p1-"+ std::to_string(startingTokens), "p2-" + std::to_string(startingTokens - 1),0);
      g_.setEdgeWeight("p2-"+ std::to_string(startingTokens), "p1-" + std::to_string(startingTokens - 1),0);
    for(unsigned i = 1; i <= startingTokens; i++) {
      g_.insertVertex("p1-"+std::to_string(startingTokens - i));
      g_.insertVertex("p2-"+std::to_string(startingTokens - i));
      g_.insertEdge("p1-"+ std::to_string(startingTokens - i + 1), "p2-" + std::to_string(startingTokens - i));
      g_.insertEdge("p2-"+ std::to_string(startingTokens - i + 1), "p1-" + std::to_string(startingTokens - i));
      g_.setEdgeWeight("p1-"+ std::to_string(startingTokens - i + 1), "p2-" + std::to_string(startingTokens - i),0);
      g_.setEdgeWeight("p2-"+ std::to_string(startingTokens - i + 1), "p1-" + std::to_string(startingTokens - i),0);
      g_.insertEdge("p1-"+ std::to_string(startingTokens - i + 2), "p2-" + std::to_string(startingTokens - i));
      g_.insertEdge("p2-"+ std::to_string(startingTokens - i + 2), "p1-" + std::to_string(startingTokens - i));
      g_.setEdgeWeight("p1-"+ std::to_string(startingTokens - i + 2), "p2-" + std::to_string(startingTokens - i),0);
      g_.setEdgeWeight("p2-"+ std::to_string(startingTokens - i + 2), "p1-" + std::to_string(startingTokens - i),0);
    }
    startingVertex_ = "p1-" + std::to_string(startingTokens);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
Vertex curr1 = startingVertex_;
Vertex curr2 = startingVertex_;
 while(curr1 != "p1-0" && curr1 != "p2-0") {
  if(curr1 == "p1-1" || curr2 == "p2-1") {
    curr2 = g_.getAdjacent(curr1)[0];
    path.push_back(g_.getEdge(curr1, curr2));
    curr1 = curr2;
    return path;
  }
  int random = rand() % 2;
  if(random == 0) {
    curr2 = g_.getAdjacent(curr1)[0];
    path.push_back(g_.getEdge(curr1, curr2));
    curr1 = curr2;
  }
  if(random == 1) {
    curr2 = g_.getAdjacent(curr1)[1];
    path.push_back(g_.getEdge(curr1, curr2));
    curr1 = curr2;
  }
 }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 if(path[path.size()-1].dest == "p1-0") {
  for(unsigned i = 0; i < path.size();i++) {
    if(i % 2 == 0) {
      g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) - 1);
    }  else {
      g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) + 1);
    }
  }
 }
  if(path[path.size()-1].dest == "p2-0") {
  for(unsigned i = 0; i < path.size();i++) {
    if(i % 2 == 0) {
      g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) + 1);
    }  else {
      g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) - 1);
    }
  }
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
