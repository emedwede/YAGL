#ifndef YAGL_ALGORITHMS_HPP
#define YAGL_ALGORITHMS_HPP

#pragma once 

#include <unordered_set>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <optional>

#include "YAGL_Graph.hpp"

namespace YAGL
{

#define DEBUG_PRINT 0 

//starts a recursive depth first search at a particular node v
template <typename GraphType>
std::unordered_set<typename GraphType::key_type> 
recursive_dfs(GraphType& graph, typename GraphType::key_type v)
{
	//only need size when we're using an vector or array for the visited container
	//auto n = graph.numNodes();
	
	//Unordered set is just one way
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<typename GraphType::key_type> path;

	//run the implementation
	impl_recursive_dfs(graph, v, visited, path);
	if(DEBUG_PRINT)
	{
		std::cout << "Recursive DFS Path: ";
		for(auto v : path) std::cout << v << " ";
		std::cout << std::endl;
	}
	return visited;
}

// Time complexity of O(V+E) 
template <typename GraphType>
void impl_recursive_dfs(GraphType& graph, 
		typename GraphType::key_type v, 
		std::unordered_set<typename GraphType::key_type>& visited,
		std::vector<typename GraphType::key_type>& path)
{
	//mark the current node as found 
	visited.insert(v);
	path.push_back(v);

	// do for every edge (v, u)
	for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
	{
		typename GraphType::key_type u = *i;

		if(visited.find(u) == visited.end()) //not found we need to search it 
		{
			impl_recursive_dfs(graph, u, visited, path);
		}
	}
}

template <typename GraphType>
std::unordered_set<typename GraphType::key_type>
iterative_dfs(GraphType& graph, typename GraphType::key_type v)
{
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<typename GraphType::key_type> path;
	
	impl_iterative_dfs(graph, v, visited, path);
	if(DEBUG_PRINT)
	{
		std::cout << "Iterative DFS Path: ";
		for(auto v : path) std::cout << v << " ";
		std::cout << std::endl;
	}
	return visited;
}

template <typename GraphType>
void impl_iterative_dfs(GraphType& graph, 
		typename GraphType::key_type v,
		std::unordered_set<typename GraphType::key_type>& visited,
		std::vector<typename GraphType::key_type>& path)
{
	//create the stack for our search
	std::stack<typename GraphType::key_type> q;
	
	//push the current node to the stack 
	q.push(v);
	
	//loop until the stack is empty 
	while(!q.empty())
	{
		// pop a vertex from the stack to visit
		v = q.top();
		q.pop();
		
		//stack may contain the same vertex twice so we need 
		//too print only if not visited 
		if(visited.find(v) == visited.end())
		{
			path.push_back(v);
			visited.insert(v);
		}
		//do this for every edge (v, u)
		for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
		{
			typename GraphType::key_type u = *i;
			if(visited.find(u) == visited.end()) // not found yet
			{
				// visit it and enqueue it
				q.push(u);
			}
		}
	} 
}

template <typename GraphType>
std::unordered_set<typename GraphType::key_type>
iterative_bfs(GraphType& graph, typename GraphType::key_type v)
{
	//Unordered set is just one way
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<typename GraphType::key_type> path;

	impl_iterative_bfs(graph, v, visited, path);
	if(DEBUG_PRINT)
	{
		std::cout << "Iterative BFS Path: ";
		for(auto v : path) std::cout << v << " ";
		std::cout << std::endl;
	}
	return visited;
}

template <typename GraphType>
void impl_iterative_bfs(GraphType& graph, 
		typename GraphType::key_type v, 
		std::unordered_set<typename GraphType::key_type>& visited,
		std::vector<typename GraphType::key_type>& path)
{
	//create the queue for our search
	std::queue<typename GraphType::key_type> q;
	
	//mark the first node as found 
	visited.insert(v);

	//enqueue the first key 
	q.push(v);
	
	//loop until the queue is empty 
	while(!q.empty())
	{
		//dequeue the front node and print it 
		v = q.front();
		q.pop();
		path.push_back(v);

		//do this for every edge (v, u)
		for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
		{
			typename GraphType::key_type u = *i;
			if(visited.find(u) == visited.end()) // not found yet
			{
				// visit it and enqueue it
				visited.insert(u);
				q.push(u);
			}
		}
	} 
}

template <typename GraphType>
std::size_t connected_components(GraphType& graph)
{
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<std::vector<typename GraphType::key_type>> component_paths;

	std::size_t count = 0; //no connected components found to start
	for(auto i = graph.node_list_begin(); i != graph.node_list_end(); i++)
	{
		auto v = i->first;
		//node hasn't been visited so it must be the start of a new connected component 
		if(visited.find(v) == visited.end())
		{
			std::vector<typename GraphType::key_type> path;
			//we could use whatever search method we feel like 
			impl_iterative_bfs(graph, v, visited, path);
			component_paths.push_back(path);
			count++;
		}
	}
	if(DEBUG_PRINT)
	{
		//print paths
		for(auto path : component_paths)
		{
			std::cout << "Path: ";
			for(auto v : path)
				std::cout << v << " ";
			std::cout << std::endl;
		}
	}	
	return count;
}

template<typename GraphType>
using Mtype = std::unordered_map<typename GraphType::key_type, typename GraphType::key_type>;

template<typename GraphType>
using Ltype = std::vector<Mtype<GraphType>>;

template <typename GraphType>
Ltype<GraphType> graph_isomorphism(GraphType& g1, GraphType& g2)
{
	std::cout << "Running graph isomorphism\n";

	// let L be an empty container of dictionaries of nodes to nodes
	Ltype<GraphType> L{};

	// let M be an empty dictionary of nodes to nodes 
	Mtype<GraphType> M{};
	
	// if G1 and G2 have the same number of vertices and edges, they may be isomorphic
	if(g1.numNodes() == g2.numNodes() && g1.numEdges() == g2.numEdges())
	{
		auto v = g1.node_list_begin();
		extend_graph_isomorphism(g1, g2, M, v, L);
	}
	// return the container L 
	return L;
}

template <typename GraphType, typename NodeTypeIter>
void extend_graph_isomorphism(GraphType& g1, GraphType& g2, Mtype<GraphType> M, 
		NodeTypeIter v, Ltype<GraphType>& L )
{
	// let M' be a copy of M 
	auto M_prime = M;
	
	// get a copy of the vertices of G2
	auto node_set2 = g2.getNodeSet();
	
	// for all vertices v' of G1
	for(const auto& v_prime : g1.getNodeSetRef())
	{
		// if v' is in M' then delete M[v'] from V2
		auto& node = v_prime.second;
		if(M_prime.find(node.getKey()) != M_prime.end()) 
		{
			node_set2.erase(M[node.getKey()]);
		}
	} 

	// for all vertices w of G2 
	for(auto& w : g2.getNodeSetRef())
	{
		auto& node_w = w.second;
		auto& node_v = v->second;

		// if the labels aren't equal, not a candidate 
		if(node_v.getData().type != node_w.getData().type)
		{
			node_set2.erase(node_w.getKey());
		}
	}

	// for all vertices w in V2 
	for(auto& w : node_set2) 
	{
		// check to see if adjecencies are preserved 
		if(preserve_adjacencies(g1, g2, M_prime, v, w))
		{
			//std::cout << v->first << " -> " << w.first << "\n";
			// if so, we have a mapping
			//M_prime.insert({v->first, w.first});
			M_prime.insert_or_assign(v->first, w.first);
			// if v is the last vert of G1, then append M' to L 
			auto v_temp = v;
			v_temp++;
			if(v_temp == g1.node_list_end())
			{
				L.push_back(M_prime); 
			}
			// let v' be the next vertex after v in G1
			else 
			{
				// let v' be the next vertex after v in G1 
				auto v_prime = v; 
				v_prime++;
				extend_graph_isomorphism(g1, g2, M_prime, v_prime, L);
			}	
		}
	}
}

template <typename GraphType, typename NodeTypeIter, typename NodeType>
bool preserve_adjacencies(GraphType& g1, GraphType& g2, Mtype<GraphType>& M, NodeTypeIter& v, NodeType& w)
{
	auto node_v = v->second;
	auto node_w = w.second;

	// if the degree of the nodes aren't the same, no match
	if(g1.in_degree(node_v) != g2.in_degree(node_w) || g1.out_degree(node_v) != g2.out_degree(node_w))
	{
		//std::cout << "Mismatch of in/out degree\n";
		return false;
	}
	// for all edges coming into the vertex v in G1 
	for(auto& x : g1.in_neighbors(node_v))
	{
		// if the src vertex, x, in M and M[x] is not adjecent with w in G2, no match 
		if(M.find(x) != M.end() && !g2.adjacent(M[x], w.first))
		{
			//std::cout << "Adjacency test failed for in neighbors\n";
			return false;
		}
	}
	// for all edges coming out of the vertex v in G1
	for(auto& x : g1.out_neighbors(node_v))
	{
		// if the target vertex, x, in M and w is not adjecent with M[x] in G2, no match 
		if(M.find(x) != M.end() && !g2.adjacent(w.first, M[x]))
		{
			//std::cout << "Adjacency test failed for out neighbors\n";
			return false;
		}
	}
	//std::cout << "Adjacency test passed\n";
	// adjacency is preserved 
	return true;
}

// a dictionary of vertices to set of vertices
template <typename GraphType>
using Ctype = std::unordered_map<typename GraphType::key_type, std::unordered_set<typename GraphType::key_type>>;

template<typename GraphType>
Ltype<GraphType> subgraph_isomorphism(GraphType& g1, GraphType& g2)
{
	std::cout << "Running subgraph isomorphism\n";	
	
	// let C be an empty dictionary of vertices to sets of vertices 
	Ctype<GraphType> C{};
	
	// for all vertices in G1, build a set of candidates in G2
	for(auto& [v, node_v] : g1.getNodeSetRef())
	{
		C[v] = {};
		for(auto& [w, node_w] : g2.getNodeSetRef())
		{
			if(g1.in_degree(node_v) <= g2.in_degree(node_w) && g1.out_degree(node_v) <= g2.out_degree(node_w) 
					&& node_v.getData().type == node_w.getData().type)
			{
				C[v].insert(w);
			}
		}
	}
	
	// let L be an empty list of vertices to vertices aka list of matches 
	Ltype<GraphType> L{};
	
	// let M be an empty dictionary of vertices to vertices aka a match 
	Mtype<GraphType> M{};
	
	// let v be the iterator to the first vertex of G1 
	auto v_iter = g1.node_list_begin();	
	
	extend_subgraph_isomorphism(g1, g2, C, v_iter, M, L);

	return L;
}

template <typename GraphType, typename NodeTypeIter>
void extend_subgraph_isomorphism(GraphType& g1, GraphType& g2, 
		Ctype<GraphType> C, NodeTypeIter v_iter, Mtype<GraphType> M, Ltype<GraphType>& L)
{
	auto v = v_iter->first;
	auto node_v = v_iter->second;

	for(auto& [w, node_w] : g2.getNodeSetRef())
	{
		if(C[v].find(w) != C[v].end())
		{
			M[v] = w;
			
			Ctype<GraphType> N{};
			
			for(auto& [x, node_x] : g1.getNodeSetRef())
			{
				N[x] = C[x];
				
				if(x != v)
				{
					N[x].erase(w);
				}
			}
			for(auto& [y, node_y] : g2.getNodeSetRef())
			{
				if(y != w)
				{
					N[v].erase(y);
				}
			}
			if(refine_subgraph_isomorphism(g1, g2, N, v, w))
			{
				auto v_next = v_iter; 
				v_next++;
				if(v_next == g1.node_list_end())
				{
					L.push_back(M);
				}
				else
				{
					extend_subgraph_isomorphism(g1, g2, N, v_next, M, L);	
				}
			}
		}
	}
}

template <typename GraphType>
bool refine_subgraph_isomorphism(GraphType& g1, GraphType& g2, Ctype<GraphType>& C, 
		typename GraphType::key_type v, typename GraphType::key_type w)
{
	auto node_v = g1.findNode(v)->second; auto node_w = g2.findNode(w)->second;

	if(g1.in_degree(node_v) > g2.in_degree(node_w) || g1.out_degree(node_v) > g2.out_degree(node_w))
	{
		return false;
	}
	for(auto& x : g1.in_neighbors(v))
	{
		for(auto& [y, node_y] : g2.getNodeSetRef())
		{
			if(!g2.adjacent(y, w))
			{
				C[x].erase(y);
			}
			else
			{
				//check edge labels
			}
		}
	}
	for(auto& x : g1.out_neighbors(v))
	{
		for(auto& [y, node_y] : g2.getNodeSetRef())
		{
			if(!g2.adjacent(w, y))
			{
				C[x].erase(y);
			} 
			else
			{
				//check edge labels
			}
		}
	}

	for(auto& [x, node_x] : g1.getNodeSetRef())
	{
		if(C[x].empty())
			return false;
	}
	return true;
}

} //end namespace YAGL

#endif
