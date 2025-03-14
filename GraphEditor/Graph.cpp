#include "MainGraph.h"

MainGraph::MainGraph(std::string graph_path)
{

	std::ifstream fs{};
	
	std::vector<std::pair<int, int>> temp_parsed{};

	fs.open(graph_path);
	std::string line{};
	while (std::getline(fs, line)) {

		edges.emplace_back(graph_parser(line));

	}
	current_graph_filename = "current.dot";
	last_graph_filename = "non_iso.dot";
	addition_graph_filename = "add_graph.dot";
	graphviz_current(0);
	build_tops(edges);
	build_non_isomorphic();
	graphviz_current(1);
	build_addition();
	graphviz_current(2);

	

}

void MainGraph::print_tops_degrees()
{

	std::cout << "\n****TOPS DEGREES****\n" << std::endl;

	for (auto top : tops)
		std::cout << top.first << " : " << top.second.size() << std::endl;

	std::cout << "\n*******************" << std::endl;

}

void MainGraph::print_aliquot_edges()
{

	std::cout << "\nAliquot edges quantity: " << aliquot_edges << std::endl;
	std::cout << std::endl;

}

void MainGraph::build_addition()
{

	std::vector<std::pair<int, int>> temp{};

	for(size_t i{1}; i < tops.size(); i++)
		for (size_t j{1}; j <= VERTEX_COUNT; j++) {

			if (std::find(tops[i].begin(), tops[i].end(), j) == tops[i].end() &&
				std::find(tops[j].begin(), tops[j].end(), i) == tops[j].end() &&
				std::find(temp.begin(), temp.end(), std::pair<int,int>{i, j}) == temp.end() &&
				std::find(temp.begin(), temp.end(), std::pair<int, int>{j, i}) == temp.end() &&
				i != j) {
				addition_edges.emplace_back(std::pair<int, int>(i, j));
				temp.emplace_back(std::pair<int, int>(i, j));
			}
		}

}

void MainGraph::build_non_isomorphic()
{
	noniso_edges = edges; // Копируем исходные рёбра
	int vertexCount = 0;

	// Находим максимальную вершину, чтобы знать, какие вершины у нас есть
	for (const auto& edge : edges) {
		vertexCount = std::max(vertexCount, std::max(edge.first, edge.second));
	}

	// Хранит уже существующие рёбра в множестве для быстрой проверки
	std::set<std::pair<int, int>> existingEdges(noniso_edges.begin(), noniso_edges.end());

	// Перебираем все возможные пары вершин
	for (int u = 1; u <= vertexCount; ++u) {
		for (int v = u + 1; v <= vertexCount; ++v) {
			std::pair<int, int> edge = { u, v };

			// Если такого ребра нет в оригинальных рёбрах, заменяем одно существующее
			if (existingEdges.find(edge) == existingEdges.end() &&
				existingEdges.find(std::make_pair(v, u)) == existingEdges.end()) {
				// Заменяем первое ребро на новое
				noniso_edges[0] = edge;
				return; // Выходим, как только нашли замену
			}
		}
	}

	// Если не удалось найти подходящую пару, можно добавить обработку
}

std::pair<int, int> MainGraph::graph_parser(std::string graph_line)
{

	std::stringstream ss{};
	std::pair<int, int> parsed_pair{};
	for (size_t i{}; i < graph_line.length(); i++) {

		if (graph_line[i] == ',') {
			parsed_pair.first = std::stoi(ss.str());
			ss.str("");
			continue;
		}

		ss << graph_line[i];

	}
	
	parsed_pair.second = std::stoi(ss.str());
	if (parsed_pair.first > VERTEX_COUNT)
		VERTEX_COUNT = parsed_pair.first;
	else if(parsed_pair.second > VERTEX_COUNT)
		VERTEX_COUNT = parsed_pair.second;
	return parsed_pair;

}

void MainGraph::build_tops(std::vector<std::pair<int, int>> parsed)
{

	for (auto pair : parsed) {
		
		if (tops.find(pair.first) == tops.end())
			tops.emplace(pair.first, std::vector<int>{});
		
		auto temp{ tops[pair.first].size() };
		tops[pair.first].emplace_back(pair.second);
		if (temp == tops[pair.first].size())
			aliquot_edges++;

	}

	aliquot_additional();

}

void MainGraph::aliquot_additional()
{

	for (auto pair : tops) {

		for (auto num : tops[pair.first])
			if (std::find(tops[num].begin(), tops[num].end(), pair.first) != tops[num].end())
				aliquot_edges++;

	}

}

void MainGraph::incidence_matrix()
{

	std::cout << "****CURRENT EDGES****\n" << std::endl;

	for (unsigned i{}; i < edges.size(); i++)
		std::cout << i << ". " << edges[i].first << " - " << edges[i].second << "\n";

	std::cout << "\n*********************" << std::endl;
	std::cout << "\n**INCIDENCE MATRIX**\n" << std::endl;


	std::stringstream ss{};
	ss << "  ";
	for (unsigned i{}; i < edges.size(); i++)
		ss << i << " ";
	std::cout << ss.str() << std::endl;

	for (unsigned i{1}; i <= tops.size(); i++) {
		ss.str("");
		ss << i;
		ss << " ";

		for (unsigned j{}; j < edges.size(); j++) {

			ss << check_incidence(edges[j], i) ? 1 : 0;
			ss << " ";

		}

		std::cout << ss.str() << std::endl;

	}

}

std::vector<std::string> MainGraph::get_names()
{
	return std::vector<std::string>{current_graph_filename, last_graph_filename, addition_graph_filename};
}

bool MainGraph::check_incidence(std::pair<int, int> edge, int top_num)
{

	return (edge.first == top_num || edge.second == top_num);

}

void MainGraph::graphviz_current(int graph_version)
{

	using Graph = boost::adjacency_list<
		boost::vecS,
		boost::vecS,
		boost::undirectedS,
		boost::property< boost::vertex_color_t, boost::default_color_type >,
		boost::property< boost::edge_weight_t, double >
	>;

	std::vector<std::pair<int, int>> edges_to_build;
	std::string file_to_write;
	switch (graph_version) {

		case 0:
			edges_to_build = edges;
			file_to_write = current_graph_filename;
			break;
		case 1:
			edges_to_build = noniso_edges;
			file_to_write = last_graph_filename;
			break;
		case 2:
			edges_to_build = addition_edges;
			file_to_write = addition_graph_filename;
			break;
		default:
			break;
		

	}


	std::vector<double> weights(edges_to_build.size());
	std::fill(weights.begin(), weights.end(), 1.0);

	Graph graph(edges_to_build.begin(), edges_to_build.end(), weights.begin(), VERTEX_COUNT);

	std::ofstream ofs(file_to_write);

	//boost::write_graphviz_dp(ofs, graph, dp); - for weights in graph

	boost::write_graphviz(ofs, graph);
	/*
	std::stringstream ss;
	ss << "dot -Tpng -odia.png " << filename;
	auto prepared_save_way = ss.str();
	auto str{ prepared_save_way.c_str() };
	system(str);
	*/
}
