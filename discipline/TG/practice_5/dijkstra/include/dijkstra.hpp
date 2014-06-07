#ifndef DIJKSTRA
#define DIJKSTRA

#include <cstddef>
#include <vector>

#include <graph.hpp>

std::vector<Path> get_shortest_paths(Graph& graph, const size_t from);

#endif
