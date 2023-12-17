#include <algorithm>
#include <bits/ranges_base.h>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include <functional>
#include <chrono>
#include <queue>
#include <stdexcept>

struct path;
struct node {
	// vectors are not final on initialization -> see generateGraph()
	const std::string name;
	std::vector<path*> paths;

	// needed for dijkstra's / partially for bfs, requires resetting if reusing graph
	path* source_path;
	int dist_to_start;
	bool visited;
	std::vector<path*> getRoute();

	node(std::string name) : name(name), paths({}), source_path(nullptr), dist_to_start(0), visited(false) {};
	~node();
};

struct path {
	const int weight;
	std::vector<std::string> lines;
	node* source;
	node* target;

	bool operator>(const path& x) const {
		return this->source->dist_to_start + this->weight > x.source->dist_to_start + x.weight;
	};

	path(int weight, node* source, node* target) : weight(weight), lines({}), source(source), target(target) {};
};

enum algorithm {
	dijkstra,
	bfs,
};

std::unordered_map<std::string, node*> generateGraph(const std::string file_path);
void resetGraph(std::unordered_map<std::string, node*> nodes);
std::vector<path*> find_dijkstra(std::unordered_map<std::string, node*>& stations, const std::string start, const std::string end);
std::vector<path*>& calcChanges(std::vector<path*>& route); // brute force -> probably inefficent
std::vector<path*> find_bfs(std::unordered_map<std::string, node*>& stations, const std::string start, const std::string end);

template<typename Return_type, typename... Args>
Return_type stopwatch(long& time_nanosec, Return_type (*func)(Args...), Args&&... args);
template<typename... Args>
void stopwatch(long& time_nanosec, void (*func)(Args...), Args&&... args);
template<typename Return_type>
Return_type stopwatch(long& time_nanosec, Return_type (*func)());
void stopwatch(long& time_nanosec, void (*func)());

int main(int argc, char const *argv[])
{
	assert(argc == 4 || argc == 5);

	if (false) { // start equal to end
		std::cout << "Start is equal to end!" << std::endl;
	};

	const algorithm algorithm = static_cast<enum algorithm>(argc > 4 ? atoi(argv[4]) : 0);

	std::vector<path*> (*search_func)(std::unordered_map<std::string, node*>&, const std::string, const std::string);
	std::string algorithm_str;
	switch (algorithm) {
		case dijkstra:
			search_func = find_dijkstra;
			algorithm_str = "Dijkstra's algorithm";
			break;
		case bfs:
			search_func = find_bfs;
			algorithm_str = "Breadth-first search";
			break;
	}

	// std::chrono::system_clock::time_point = long
	long generation_t;
	std::unordered_map<std::string, node*> stations = stopwatch(generation_t, generateGraph, std::string(argv[1]));

	try {

		long search_t;
		std::vector<path*> route = stopwatch(search_t, search_func, stations, std::string(argv[2]), std::string(argv[3]));

		long changes_t;
		if (route.empty()) {
			changes_t = 0;
			std::cout << "Could not find a path from " << argv[2] << " to " << argv[3] << std::endl;
		} else {
			std::vector<path*> lines_calculated = stopwatch(changes_t, calcChanges, route);

			std::cout << "Using " << algorithm_str << ":" << std::endl << std::endl;

			int distance = 0;
			for ( auto& path : route ) {
				distance += path->weight;
			}

			// assert due to last minute changes
			assert(algorithm == bfs || route.back()->target->dist_to_start == distance);

			std::cout << "Quickest path from " << argv[2] << " to " << argv[3] << " (" << distance << " distance): " << argv[2];
			for ( const auto& path : lines_calculated ) {
				std::cout << " - " << path->lines.at(0) << " - " << path->target->name;
			}
			std::cout << std::endl;
		}

		std::cout << std::fixed << std::setprecision(3);
		std::cout << "Runtime: " << static_cast<double>(generation_t) / 1e6 << "ms to generate the graph";
		std::cout << ", " << static_cast<double>(search_t) / 1e6 << "ms to find the route";
		if (changes_t != 0) {
			std::cout << ", " << static_cast<double>(changes_t) / 1e6 << "ms to calculate changes";
		}
		std::cout << "." << std::endl;

	} catch (const std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}

	//resetGraph(stations);
/*
	std::cout << std::endl;

	try {

		long search_t;
		std::vector<path*> route = stopwatch(search_t, find_bfs, stations, std::string(argv[2]), std::string(argv[3]));

		long changes_t;
		if (route.empty()) {
			changes_t = 0;
			std::cout << "Could not find a path from " << argv[2] << " to " << argv[3] << std::endl;
		} else {
			std::vector<path*> lines_calculated = stopwatch(changes_t, calcChanges, route);

			std::cout << "Breadth First Search Algorithm:" << std::endl << std::endl;

			int distance = 0;
			for ( auto& path : route ) {
				distance += path->weight;
			}

			std::cout << "Quickest path from " << argv[2] << " to " << argv[3] << " (" << distance << " distance): " << argv[2];
			for ( const auto& path : lines_calculated ) {
				std::cout << " - " << path->lines.at(0) << " - " << path->target->name;
			}
			std::cout << std::endl;
		}

		std::cout << std::fixed << std::setprecision(3);
		std::cout << "Runtime: " << static_cast<double>(search_t) / 1e6 << "ms to find the route";
		if (changes_t != 0) {
			std::cout << ", " << static_cast<double>(changes_t) / 1e6 << "ms to calculate changes";
		}
		std::cout << "." << std::endl;

	} catch (const std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}
*/
	for ( auto& station : stations ) {
		delete station.second;
	}

	return 0;
}

std::vector<path*> find_dijkstra(std::unordered_map<std::string, node*>& stations, const std::string start, const std::string end) {
	node* starting_node = stations[start];
	node* end_node = stations[end];

	if (starting_node == nullptr)
		throw std::invalid_argument(start + ": could not find station");
	if (end_node == nullptr)
		throw std::invalid_argument(end + ": could not find station");

	std::priority_queue<path*, std::vector<path*>, decltype([](const auto& left, const auto& right) {
		return *left > *right;
	})> paths;
	starting_node->dist_to_start = 0;
	starting_node->visited = true;

	for ( auto path : starting_node->paths ) {
		paths.push(path);
	}

	while (!paths.empty()) {
		path* path_to_next = paths.top();
		paths.pop();
		node* next_station = path_to_next->target;

		if (next_station->visited == true)
			continue;

		next_station->source_path = path_to_next;
		next_station->dist_to_start = path_to_next->source->dist_to_start + path_to_next->weight;
		next_station->visited = true;

		if (next_station == end_node)
			break;

		for ( auto path : next_station->paths ) {
			if (path->target->visited == false) {
				paths.push(path);
			}
		}
	}

	return end_node->getRoute();
}

std::vector<path*>& calcChanges(std::vector<path*>& route) {
	int changes_canditate = -1;
	std::vector<std::string> canditate;
	std::vector<std::vector<std::string>::iterator> lines_iterators;
	for ( auto& path : route ) {
		lines_iterators.emplace_back(path->lines.begin());
	}

	unsigned long last_choice;
	for (long i = static_cast<long>(route.size()) - 1; i >= 0; i--) {
		if (route.at(static_cast<unsigned long>(i))->lines.size() > 1) {
			last_choice = static_cast<unsigned long>(i);
			break;
		}

		last_choice = static_cast<unsigned long>(i);
	}

	auto increase = [&lines_iterators, &route, &last_choice]() {
		for (unsigned long i = 0; i <= last_choice; i++) {
			if (i > 0)
				lines_iterators.at(i-1) = route.at(i-1)->lines.begin();
			(lines_iterators.at(i))++;
			if (lines_iterators.at(i) == route.at(i)->lines.end()) {
				continue;
			}
			break;
		}
	};

	for (; lines_iterators.at(last_choice) != route.at(last_choice)->lines.end(); increase()) {
		int changes = 0;
		for ( auto it = lines_iterators.begin(); it+1 < lines_iterators.end(); it++) {
			if (**it != **(it+1))
				changes++;
		}
		if (changes_canditate == -1 || changes < changes_canditate) {
			changes_canditate = changes;
			canditate.clear();
			for ( auto& line_it : lines_iterators ) {
				canditate.push_back(*line_it);
			}
		}
	}

	for (unsigned long i = 0; i < route.size(); i++) {
		route.at(i)->lines.erase(std::remove_if(route.at(i)->lines.begin(), route.at(i)->lines.end(), [i, &canditate](auto& x) {
			return x != canditate.at(i);
		}), route.at(i)->lines.end());
	}

	return route;
}

std::unordered_map<std::string, node*> generateGraph(const std::string file_path) {
	std::unordered_map<std::string, node*> stations;
	std::vector<std::string> lines;

	std::string line;
	std::ifstream input(file_path);
	for( std::string line; getline( input, line ); ) {
		// multithreading?
		lines.emplace_back(line);
	}

	// questionable coding style
	auto get_station = [&stations](const std::string name) {
		auto i = stations.empty() ? stations.end() : stations.find(name);
		auto new_station = [&]() {
			stations[name] = new node(name);
			return stations[name];
		};
		return i == stations.end() ? new_station() : i->second;
	};

	for ( auto& line : lines ) {
		std::istringstream iss(line);
		std::string line_name;
		iss >> line_name;

		// remove the colon from the line name
		line_name = line_name.substr(0, line_name.length() - 1);

		std::string station;
		std::string next_station;
		int distance;

		auto add_line = [&distance, &line_name](node* a, node* b) {
			auto new_path = [&distance](node* a, node* b) {
				a->paths.emplace_back(new path(distance, a, b));
				return a->paths.back();
			};

			auto get_path = [&distance, &new_path](node* a, node* b) {
				auto i = a->paths.empty() ? a->paths.end() : std::find_if(a->paths.begin(), a->paths.end(), [&b, &distance](const auto& x) {
					return x->target == b && x->weight == distance;
				});
				return i == a->paths.end() ? new_path(a, b) : *i ;
			};

			for ( auto& path : { get_path(a, b), get_path(b, a) } ) {
				path->lines.push_back(line_name);
				// no need to verify if line already added since no circular lines
			}
		};

		iss >> std::quoted(station);

		while (iss >> distance >> std::quoted(next_station)) {
			add_line(get_station(station), get_station(next_station));
			station = next_station;
		}
	}

	return stations;
}

node::~node() {
	for ( auto& path : this->paths ) {
		delete path;
	}
}

std::vector<path*> node::getRoute() {
	if (this->source_path == nullptr)
		return {};
	auto route = this->source_path->source->getRoute();
	route.push_back(this->source_path);
	return route;
}

template<typename Return_type, typename... Args>
Return_type stopwatch(long& time_nanosec, Return_type (*func)(Args...), Args&&... args)
{
	auto start_t = std::chrono::high_resolution_clock::now();
	Return_type return_value = func(std::forward<Args>(args)...);
	time_nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start_t).count();
	return return_value;
}

template<typename... Args>
void stopwatch(long& time_nanosec, void (*func)(Args...), Args&&... args)
{
	auto start_t = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	time_nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start_t).count();
	return;
}

template<typename Return_type>
Return_type stopwatch(long& time_nanosec, Return_type (*func)())
{
	auto start_t = std::chrono::high_resolution_clock::now();
	Return_type return_value = func();
	time_nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start_t).count();
	return return_value;
}

void stopwatch(long& time_nanosec, void (*func)())
{
	auto start_t = std::chrono::high_resolution_clock::now();
	func();
	time_nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start_t).count();
	return;
}

std::vector<path*> find_bfs(std::unordered_map<std::string, node*>& stations, const std::string start, const std::string end) {
	node* starting_node = stations[start];
	node* end_node = stations[end];

	if (starting_node == nullptr) throw std::invalid_argument(start + ": could not find station");

	if (end_node == nullptr) throw std::invalid_argument(end + ": could not find station");

	std::queue<path*> paths;
	starting_node->dist_to_start = 0;
	starting_node->visited = true;

	for ( auto path : starting_node->paths ) paths.push(path);

	while (!paths.empty()) {
		path* path_to_next = paths.front();
		paths.pop();
		node* next_station = path_to_next->target;

		if (next_station->visited) continue;

		next_station->source_path = path_to_next;
		next_station->visited = true;

		if (next_station == end_node) break;

		for ( auto path : next_station->paths ) {
			if (!path->target->visited ) paths.push(path);
		}
	}

	return end_node->getRoute();
}

void resetGraph(std::unordered_map<std::string, node*> nodes) {
	for(auto& node : nodes) {
		node.second->visited = false;
		node.second->dist_to_start = 0;
		node.second->source_path = nullptr;
	}
}