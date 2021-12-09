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

//starts a recursive depth first search at a particular node v
template <typename GraphType>
std::unordered_set<typename GraphType::key_type> 
recursive_dfs(GraphType& graph, typename GraphType::key_type v)
{
	//only need size when we're using an vector or array for the visited container
	//auto n = graph.numNodes();
	
	//Unordered set is just one way
	std::unordered_set<typename GraphType::key_type> visited;
	
	//run the implementation
	std::cout << "Recursive DFS Path: ";
	impl_recursive_dfs(graph, v, visited);
	std::cout << std::endl;
	return visited;
}

// Time complexity of O(V+E) 
template <typename GraphType>
void impl_recursive_dfs(GraphType& graph, 
		typename GraphType::key_type v, 
		std::unordered_set<typename GraphType::key_type>& visited)
{
	//mark the current node as found 
	visited.insert(v);

	std::cout << v << " ";
	
	// do for every edge (v, u)
	for(auto i = graph.out_neighbors_begin(v); i != graph.out_neighbors_end(v); i++)
	{
		typename GraphType::key_type u = *i;

		if(visited.find(u) == visited.end()) //not found we need to search it 
		{
			impl_recursive_dfs(graph, u, visited);
		}
	}
}

template <typename GraphType>
std::unordered_set<typename GraphType::key_type>
iterative_dfs(GraphType& graph, typename GraphType::key_type v)
{
	std::unordered_set<typename GraphType::key_type> visited;

	std::cout << "Iterative DFS Path: ";
	impl_iterative_dfs(graph, v, visited);
	std::cout << std::endl;

	return visited;
}

template <typename GraphType>
void impl_iterative_dfs(GraphType& graph, 
		typename GraphType::key_type v,
		std::unordered_set<typename GraphType::key_type>& visited)
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
			std::cout << v << " ";
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
	
	std::cout << "Iterative BFS Path: ";
	impl_iterative_bfs(graph, v, visited);
	std::cout << std::endl;
	return visited;
}

template <typename GraphType>
void impl_iterative_bfs(GraphType& graph, 
		typename GraphType::key_type v, 
		std::unordered_set<typename GraphType::key_type>& visited)
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
		std::cout << v << " ";
		
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

} //end namespace YAGL

#endif
