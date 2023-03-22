#ifndef YAGL_ALGORITHMS_HPP
#define YAGL_ALGORITHMS_HPP

#pragma once 

#include <unordered_set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <optional>

#include "YAGL_Graph.hpp"

namespace YAGL
{

#define DEBUG_PRINT 0 

template <typename GraphType, typename NodeSet>
GraphType induced_subgraph(GraphType& graph, NodeSet& inducing_set)
{
	GraphType subgraph;
	
	//first add all of the inducing nodes to the subgraph 
	for(const auto& u : inducing_set)
	{
		auto node_u = graph.findNode(u)->second;
		subgraph.addNode(node_u);
	}
	//next for every node only add an edge if adjecent
	for(const auto& u : inducing_set)
	{
		for(const auto& v : graph.out_neighbors(u))
		{
			if(subgraph.findNode(v) != subgraph.node_list_end())
				subgraph.addEdge(u, v);
		}
	}
	return subgraph;
}
//starts a recursive depth first search at a particular node v
template <typename GraphType>
std::unordered_set<typename GraphType::key_type> 
recursive_dfs(GraphType& graph, typename GraphType::key_type v, std::size_t max_depth = 0)
{
	//only need size when we're using an vector or array for the visited container
	//auto n = graph.numNodes();
	
	//Unordered set is just one way
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<typename GraphType::key_type> path;
	//a max depth of zero means search with no limit
	std::size_t cur_depth = 0;
	//run the implementation
	impl_recursive_dfs(graph, v, visited, path, cur_depth, max_depth);
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
		std::vector<typename GraphType::key_type>& path,
		std::size_t cur_depth = 0,
		std::size_t max_depth = 0)
{	
	if(DEBUG_PRINT)
	{
		std::cout << "max_depth " << max_depth << "\n";
		std::cout << "cur_depth " << cur_depth << "\n";
	}

	//mark the current node as found 
	visited.insert(v);
	path.push_back(v);
	cur_depth++;
	if(cur_depth == max_depth)
		return;
	//else
		//cur_depth++;

	// do for every edge (v, u)
	for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
	{
		typename GraphType::key_type u = *i;

		if(visited.find(u) == visited.end()) //not found we need to search it 
		{
			impl_recursive_dfs(graph, u, visited, path, cur_depth, max_depth);
		}
	}
}

//starts a recursive depth first search at a particular node v
template <typename GraphType>
auto recursive_dfs2(GraphType& graph, typename GraphType::key_type v, std::size_t max_depth = 0)
{
	//only need size when we're using an vector or array for the visited container
	//auto n = graph.numNodes();
	
	//Unordered set is just one way
	std::unordered_set<typename GraphType::key_type> visited;
	std::vector<std::pair<typename GraphType::key_type, std::size_t>> path;
	//a max depth of zero means search with no limit
	std::size_t cur_depth = 0;
	//run the implementation
	impl_recursive_dfs2(graph, v, visited, path, cur_depth, max_depth);
	if(DEBUG_PRINT)
	{
		std::cout << "Recursive DFS Path ({ vertex, depth }): ";
		for(auto v : path) std::cout << "{ " << v.first << ", " << v.second << " } ";
		std::cout << std::endl;
	}
	return path;
}

// Time complexity of O(V+E) 
template <typename GraphType>
void impl_recursive_dfs2(GraphType& graph, 
		typename GraphType::key_type v, 
		std::unordered_set<typename GraphType::key_type>& visited,
		std::vector<std::pair<typename GraphType::key_type, std::size_t>>& path,
		std::size_t cur_depth = 0,
		std::size_t max_depth = 0)
{	
	if(DEBUG_PRINT)
	{
		std::cout << "max_depth " << max_depth << "\n";
		std::cout << "cur_depth " << cur_depth << "\n";
	}

	//mark the current node as found 
	visited.insert(v);
	path.push_back({v, cur_depth});
	cur_depth++;
	if(cur_depth == max_depth)
		return;
	//else
		//cur_depth++;

	// do for every edge (v, u)
	for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
	{
		typename GraphType::key_type u = *i;

		if(visited.find(u) == visited.end()) //not found we need to search it 
		{
			impl_recursive_dfs2(graph, u, visited, path, cur_depth, max_depth);
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
using Mtype = std::map<typename GraphType::key_type, typename GraphType::key_type>;

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

template<typename KeyType>
struct FlatNode
{
    KeyType key;
    KeyType parent;
    std::vector<int> children;
};

template <typename KeyType>
struct FlatNTree
{
    std::vector<FlatNode<KeyType>> nodes;
    std::vector<int> index;
		
    //empty root node
    FlatNTree(KeyType key)
    { 
				//self looping parent
        nodes.push_back({key, key, {}});
        build_preorder_index();
    }

    void add_node(KeyType key, KeyType parent_key)
    {
        auto index = nodes.size();
        auto k = find_node(key);
        if(k != -1)
        {
            std::cout << "Error, node already exists and can't be added\n";
        }
        auto p = find_node(parent_key);
        if(p == -1)
        {
            std::cout << "Error parent does not exist, node cannot be added\n";
            return;
        }
        nodes.push_back({key, parent_key, {}});
        nodes[find_node(parent_key)].children.push_back(index);
        build_preorder_index();
    }
    
    int find_node(KeyType key)
    {
        for(int i = 0; i < nodes.size(); i++)
            if(nodes[i].key == key)
                return i;
        return -1;
    }

    void preorder_index(int node_index, int& order_index) 
    {
        index[order_index] = node_index;
        
        FlatNode<KeyType>& node = nodes[node_index];

        for(int child_index : node.children)
        {
            order_index++;
            preorder_index(child_index, order_index);
        }

    }

    void build_preorder_index()
    {
        //resize the old preorder index 
        index.resize(nodes.size());
        
        //start at the beginning for index and nodes 
        int order_index = 0;
        int node_index = 0;
        
        preorder_index(node_index, order_index);
    }

    auto begin() { return index.begin(); }
    auto end() { return index.end(); }
   	
		KeyType indexed_key(int i) { return nodes[index[i]].key; }
		KeyType indexed_parent(int i) { return nodes[index[i]].parent; }

    void print_preorder()
    {
        std::cout << "Preorder: ";
        for(auto& i : index)
            std::cout << "{ key: " << nodes[i].key << ", " << " parent: " << nodes[i].parent << " } ";
        std::cout << "\n";
    }
};


template <typename GraphType>
Ltype<GraphType> subgraph_isomorphism2(GraphType& g1, GraphType& g2)
{
	std::cout << "Running subgraph isomorphism\n";

	// let L be an empty container of dictionaries of nodes to nodes
	Ltype<GraphType> L{};

	// let M be an empty dictionary of nodes to nodes 
	Mtype<GraphType> M{};
	Mtype<GraphType> M_inverse{};	
	//find a dfs orderding for g1 
	auto path = recursive_dfs2(g1, g1.node_list_begin()->first);
	
	if(path.size() == 0) return L;

	//build a tree for the preorder traversal
	FlatNTree<typename GraphType::key_type> rst(path[0].first);
	if(path.size() > 1)
	{
		for(auto i = 1; i < path.size(); i++)
		{
			//parent is node of previous depth 
			typename GraphType::key_type parent; 
			
			for(auto j = i-1; j >= 0; j--)
			{
				if(path[i].second == (path[j].second + 1))
				{
					parent = path[j].first;
					break;
				}
				else 
					parent = path[0].first;
			}
			rst.add_node(path[i].first, parent);
		}
	}
	
	//set v to be the first item in the total orderding of the dfs tree
	int idx = 0;
	auto v = g1.findNode(rst.indexed_key(idx));
	
	//if g1 has more nodes than g2, can't be a subgraph, but equal we'll let it slide
	//same with edges
	if(g1.numNodes() > g2.numNodes() || g1.numEdges() > g2.numEdges())
		return L;

	//all nodes are potential candidates for the first ordered vertex of g1
	for(auto& n : g2.getNodeSetRef())
	{
		//TODO: fix the wierd pointer issue caused by this in preserve_adjacencies2 
		auto w = g2.findNode(n.first); //my janky fix, but makes no sense since we iter g2
		auto& node_w = w->second;
		auto& node_v = v->second;

		//if labels are different not a candidate 
		if(node_v.getData().type == node_w.getData().type)
		{
			//if the degree of v is greater than w, also not a candidate 
			if(preserve_adjacencies2(g1, g2, M, v, w))	
			{
				M.insert_or_assign(v->first, w->first);	
				M_inverse.insert_or_assign(w->first, v->first);
				
				if(idx+1 == rst.index.size())
				{
					L.push_back(M);
				}
				else 
				{
					int idx_next = idx+1;
					auto v_prime = g1.findNode(rst.indexed_key(idx_next));
					extend_subgraph_isomorphism2(g1, g2, M, M_inverse, idx_next, v_prime, L, rst);
					M.erase(v->first);
					M_inverse.erase(w->first);
				}
			}
		}
	}

	// return the container L 
	return L;
}

template <typename GraphType, typename NodeTypeIter>
void extend_subgraph_isomorphism2(GraphType& g1, GraphType& g2, Mtype<GraphType>& M, Mtype<GraphType>& M_inverse, 
		int idx, NodeTypeIter v, Ltype<GraphType>& L, FlatNTree<typename GraphType::key_type>& rst)
{
	//the starting candidates are anything connected to the node w, of node
	//v mapped to w of the previous depth that we haven't visited
	//aka successor of node of previous depth that we haven't visited
	auto parent = g2.findNode(M[rst.indexed_parent(idx)]);
	auto& node_candidates = g2.out_neighbors(parent->first);

	for(auto& c : node_candidates)
	{
		// if w is in M_inverse then skip since we've already been there
		if(M_inverse.find(c) != M_inverse.end()) 
			continue;
		
		//check the type
		auto w = g2.findNode(c);
		auto& node_w = w->second;
		auto& node_v = v->second;
	
		// if the types aren't the same skip
		if(node_v.getData().type != node_w.getData().type)
			continue;
	
		// check to see if adjecencies are preserved 
		if(preserve_adjacencies2(g1, g2, M, v, w))
		{
			M.insert_or_assign(v->first, c);
			M_inverse.insert_or_assign(c, v->first);

			// if v is the last vertex the rst, then append M to L 
			if(idx+1 == rst.index.size())
			{
				L.push_back(M); 
				M.erase(v->first);
				M_inverse.erase(c);
			}
			// let v' be the next vertex after v in G1
			else 
			{
				int idx_next = idx+1;
				auto v_prime = g1.findNode(rst.indexed_key(idx_next));
				extend_subgraph_isomorphism2(g1, g2, M, M_inverse, idx_next, v_prime, L, rst);
				//erase from matches on the unwind
				M.erase(v->first);
				M_inverse.erase(c);
			}	
		}
	}
}

template <typename GraphType, typename NodeTypeIter>
bool preserve_adjacencies2(GraphType& g1, GraphType& g2, Mtype<GraphType>& M, NodeTypeIter& v, NodeTypeIter& w)
{
	auto node_v = v->second;
	auto node_w = w->second;

	// if the degree of the nodes aren't the same, no match
	if(g1.in_degree(node_v) > g2.in_degree(node_w) || g1.out_degree(node_v) > g2.out_degree(node_w))
	{
		//std::cout << "Mismatch of in/out degree\n";
		return false;
	}
	// for all edges coming into the vertex v in G1 
	for(auto& x : g1.in_neighbors(node_v))
	{
		// if the src vertex, x, in M and M[x] is not adjecent with w in G2, no match 
		if(M.find(x) != M.end() && !g2.adjacent(M[x], w->first))
		{
			//std::cout << "Adjacency test failed for in neighbors\n";
			return false;
		}
	}
	// for all edges coming out of the vertex v in G1
	for(auto& x : g1.out_neighbors(node_v))
	{
		// if the target vertex, x, in M and w is not adjecent with M[x] in G2, no match 
		if(M.find(x) != M.end() && !g2.adjacent(w->first, M[x]))
		{
			//std::cout << "Adjacency test failed for out neighbors\n";
			return false;
		}
	}
	//std::cout << "Adjacency test passed\n";
	// adjacency is preserved 
	return true;
}



} //end namespace YAGL



#endif
