#pragma once

#include <vector>
#include <iostream>
//#include <windows.h>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/isomorphism.hpp>
#include <algorithm>
#include "GraphNode.h"

class MainGraph
{
	public:
		MainGraph(std::string graph_path);
		void print_tops_degrees();
		void print_aliquot_edges();
		void incidence_matrix();
		std::vector<std::string> get_names();

	private:
		void build_addition();
		void build_non_isomorphic();
		std::pair<int, int> graph_parser(std::string graph_line);
		void build_tops(std::vector<std::pair<int, int>> parsed);
		void aliquot_additional();
		bool check_incidence(std::pair<int, int> edge, int top_num);
		void graphviz_current(int graph_version);
		int VERTEX_COUNT{-1};
		std::string current_graph_filename{};
		std::string last_graph_filename{};
		std::string addition_graph_filename{};

		int aliquot_edges{};
		std::vector<std::pair<int, int>> edges;
		std::vector<std::pair<int, int>> noniso_edges;
		std::vector<std::pair<int, int>> addition_edges;
		std::map<int, std::vector<int>> tops; // contains top number and vector with connected tops
		std::vector<GraphNode> nodes;

};

