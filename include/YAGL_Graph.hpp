#ifndef YAGL_GRAPH_HPP
#define YAGL_GRPAH_HPP

#pragma once 

#include <iostream> 
#include <unordered_map> 
#include <unordered_set>
#include <utility> // for pair 
#include <algorithm> // for the min_element

#include "YAGL_Node.hpp"
#include "YAGL_Edge.hpp"

namespace YAGL 
{

	template <typename KeyType, typename DataType>
	class Graph;

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, Graph<KeyType, DataType> &graph);
	
	//TODO: should functions be virtual?
	template <typename KeyType, typename DataType>
	class Graph
	{
		// define types and iterators publicly
		public:
			using key_type = KeyType;
			using data_type = DataType;
			using node_type = Node<key_type, data_type>;
			using edge_type = Edge<key_type, data_type>;
			
			// Motivation: unordered_set allows for amortized time
			// 						 constant looup, and ensures keys are unique
			//
			// NOTE: 			 key_types should be hashable and comparable
			// 						 and provide this if not available by default
			using node_set_type = std::unordered_set<key_type>;
			using edge_set_type = std::unordered_set<key_type>;
			
			// Motivation: easy way to find what goes in and what comes out 
			using in_out_nbr_type = std::pair<node_set_type, node_set_type>;
			
			// Motivation: simliar to the node and edge_set types
			using adjacency_list_type = std::unordered_map<key_type, in_out_nbr_type>;
			using node_list_type = std::unordered_map<key_type, node_type>;
			using edge_list_type = std::unordered_multimap<key_type, edge_type>;

			// by default count with the containers size_type
			using counting_type = typename node_list_type::size_type;

			//TODO: define any useful iterators
			using node_iterator = typename node_list_type::iterator;
			using const_node_iterator = typename node_list_type::const_iterator;

			using edge_iterator = typename edge_list_type::iterator;
			using const_edge_iterator = typename edge_list_type::const_iterator;
			
			using adjacency_iterator = typename adjacency_list_type::iterator;
			using const_adjacency_iterator = typename adjacency_list_type::const_iterator;
			
			using node_set_nbr_iterator = typename node_set_type::iterator;
			using const_node_set_nbr_iterator = typename node_set_type::const_iterator;

		private:
			node_list_type node_list;
			edge_list_type edge_list;
			adjacency_list_type adjacency_list;	
			
			bool undirected;
			counting_type num_edges;

		public:
			Graph();

			Graph(const DataType placeholder);
			
			node_iterator node_list_begin();
			node_iterator node_list_end();

			edge_iterator edge_list_begin();
			edge_iterator edge_list_end();

			adjacency_iterator adjacency_list_begin();
			adjacency_iterator adjacency_list_end();
			
			node_set_nbr_iterator out_neighbors_begin(const Node<KeyType, DataType>& node);
			node_set_nbr_iterator out_neighbors_end(const Node<KeyType, DataType>& node);

			node_set_nbr_iterator in_neighbors_begin(const Node<KeyType, DataType>& node);
			node_set_nbr_iterator in_neighbors_end(const Node<KeyType, DataType>& node);
			
			node_set_type& out_neighbors(const Node<KeyType, DataType>& node);
			node_set_type& in_neighbors(const Node<KeyType, DataType>& node);

			void setEdgeset(/* Needs to take in an edge set*/);
			
			void getEdgeset();
			
			void getEdge();
			
			void setEdge();

			void addEdge(const Node<KeyType, DataType>& node_a, const Node<KeyType, DataType>& node_b);

			void removeEdge(const Node<KeyType, DataType>& node_a, const Node<KeyType, DataType>& node_b);
			
			void setNodeSet();

			void getNodeSet();

			void addNode(const Node<KeyType, DataType>& node);
			
			void removeNode(const Node<KeyType, DataType>& node);
			
			node_iterator findNode(KeyType k);

			counting_type numNodes();

			counting_type numEdges();
			
			counting_type in_degree(const Node<KeyType, DataType>& node);
			
			counting_type out_degree(const Node<KeyType, DataType>& node);

			counting_type degree(const Node<KeyType, DataType>& node);
			
			counting_type min_degree();
			
			counting_type max_degree();

			double avg_degree();

			bool isDirected();

			bool isUndirected();
			
			friend std::ostream &operator<<<>(std::ostream& os, Graph<KeyType, DataType>& graph);
	};
	
	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph() : undirected(true), num_edges(0)
	{
		std::cout << "Default graph constructor!\n";

		//node_list.reserve(20'000'000);
	}

	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph(const DataType placeholder)
	{
		std::cout << "Overloaded graph const!\n";
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_iterator Graph<KeyType, DataType>::node_list_begin()
	{
		return node_list.begin();		
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_iterator Graph<KeyType, DataType>::node_list_end()
	{
		return node_list.end();	
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::edge_iterator Graph<KeyType, DataType>::edge_list_begin()
	{
		return edge_list.begin();	
	}

template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::edge_iterator Graph<KeyType, DataType>::edge_list_end()
	{
		return edge_list.end();	
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::adjacency_iterator Graph<KeyType, DataType>::adjacency_list_begin()
	{
		return adjacency_list.begin();	
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::adjacency_iterator Graph<KeyType, DataType>::adjacency_list_end()
	{
		return adjacency_list.end();	
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_nbr_iterator 
	Graph<KeyType, DataType>::out_neighbors_begin(const Node<KeyType, DataType> &node)
	{
		return out_neighbors(node).begin();
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_nbr_iterator
	Graph<KeyType, DataType>::out_neighbors_end(const Node<KeyType, DataType> &node)
	{
		return out_neighbors(node).end();
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_type& 
	Graph<KeyType, DataType>::out_neighbors(const Node<KeyType, DataType> &node)
	{
		return adjacency_list.find(node.getKey())->second.first; 
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_nbr_iterator 
	Graph<KeyType, DataType>::in_neighbors_begin(const Node<KeyType, DataType> &node)
	{
		return in_neighbors(node).begin();
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_nbr_iterator
	Graph<KeyType, DataType>::in_neighbors_end(const Node<KeyType, DataType> &node)
	{
		return in_neighbors(node).end();
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_set_type&
	Graph<KeyType, DataType>::in_neighbors(const Node<KeyType, DataType> &node)
	{
		return adjacency_list.find(node.getKey())->second.second;
	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::setEdgeset()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::getEdgeset()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::getEdge()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::setEdge()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::addEdge(const Node<KeyType, DataType>& node_a,
																				 const Node<KeyType, DataType>& node_b)
	{
		//we don't do any constraint checks for self-directed edges 
		auto iter_a = findNode(node_a.getKey());
		if(iter_a == node_list_end())
		{
			addNode(node_a);
		}

		auto iter_b = findNode(node_b.getKey());
		if(iter_b == node_list_end())
		{
			addNode(node_b);
		}
		
		auto old_size_a = out_neighbors(node_a).size();
		auto old_size_b = out_neighbors(node_b).size();

		out_neighbors(node_a).insert(node_b.getKey());
		in_neighbors(node_a).insert(node_b.getKey());

		out_neighbors(node_b).insert(node_a.getKey());
		in_neighbors(node_b).insert(node_a.getKey());

		auto new_size_a = out_neighbors(node_a).size();
		auto new_size_b = out_neighbors(node_b).size();
		
		if(new_size_a > old_size_a && new_size_b > old_size_b) 
		{
			num_edges++;
		}

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::removeEdge(const Node<KeyType, DataType>& node_a,
																						const Node<KeyType, DataType>& node_b)
	{
		//we don't do any constraint checks for self-directed edges 
		auto iter_a = findNode(node_a.getKey());
		if(iter_a == node_list_end())
		{
			return; //cannot remove what does not exist
		}

		auto iter_b = findNode(node_b.getKey());
		if(iter_b == node_list_end())
		{
			return; //cannot remove what does not exist
		}
		
		auto old_size_a = out_neighbors(node_a).size();
		auto old_size_b = out_neighbors(node_b).size();

		out_neighbors(node_a).erase(node_b.getKey());
		in_neighbors(node_a).erase(node_b.getKey());

		out_neighbors(node_b).erase(node_a.getKey());
		in_neighbors(node_b).erase(node_a.getKey());

		auto new_size_a = out_neighbors(node_a).size();
		auto new_size_b = out_neighbors(node_b).size();
		
		if(new_size_a < old_size_a && new_size_b < old_size_b) 
		{
			num_edges--;
		}
	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::setNodeSet()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::getNodeSet()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::addNode(const Node<KeyType, DataType>& node)
	{
		//node_list.insert({node.getKey(), node});
		node_list.insert_or_assign(node.getKey(), node);
		adjacency_list[node.getKey()]; //TODO: is there a better way to default initialize
	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::removeNode(const Node<KeyType, DataType>& node)
	{
		node_list.erase(node.getKey());

		//TODO: add removal of edges pointing to it
		adjacency_list.erase(node.getKey());
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::node_iterator Graph<KeyType, DataType>::findNode(KeyType k)
	{
			return node_list.find(k);
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type Graph<KeyType, DataType>::numNodes()
	{
		return node_list.size(); 
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type Graph<KeyType, DataType>::numEdges()
	{
		return num_edges;
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type 
	Graph<KeyType, DataType>::in_degree(const Node<KeyType, DataType> &node) 
	{
		return in_neighbors(node).size();
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type 
	Graph<KeyType, DataType>::out_degree(const Node<KeyType, DataType> &node) 
	{
		return out_neighbors(node).size();
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type 
	Graph<KeyType, DataType>::degree(const Node<KeyType, DataType> &node) 
	{
		return out_neighbors(node).size();
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type 
	Graph<KeyType, DataType>::min_degree() 
	{
		//same as std::min_element
		auto first = adjacency_list_begin();
		auto last = adjacency_list_end();
		
		if(first == last) return 0;
		
		auto smallest = first;

		for(; first != last; ++first)
		{
			if(first->second.first.size() < smallest->second.first.size())
			{
				smallest = first;
			}
		}

		return smallest->second.first.size();
	}
	
	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::counting_type 
	Graph<KeyType, DataType>::max_degree() 
	{
		//same as std::max_element
		auto first = adjacency_list_begin();
		auto last = adjacency_list_end();
		
		if(first == last) return 0;
		
		auto largest = first;

		for(; first != last; ++first)
		{
			if(first->second.first.size() > largest->second.first.size())
			{
				largest = first;
			}
		}

		return largest->second.first.size();
	}
	
	template <typename KeyType, typename DataType>
	double Graph<KeyType, DataType>::avg_degree() 
	{
		auto first = adjacency_list_begin();
		auto last = adjacency_list_end();
		
		if(first == last) return 0;
		
		double sum = 0;

		for(; first != last; ++first)
		{
			sum += first->second.first.size();
		}
		
		sum /= numNodes();
		
		return sum;
	}
	

	template <typename KeyType, typename DataType>
	bool Graph<KeyType, DataType>::isDirected()
	{
		return !undirected;
	}

	template <typename KeyType, typename DataType>
	bool Graph<KeyType, DataType>::isUndirected()
	{
		return undirected;
	}

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, Graph<KeyType, DataType>& graph)
	{
		os << "Current Graph Info: {\n" 
			 << "\tUndirected: " << graph.isUndirected() << "\n"
			 << "\t# of Nodes: " << graph.numNodes() << "\n"
			 << "\t# of Edges: " << graph.numEdges() << "\n"
			 << "\tMin Degree: " << graph.min_degree() << "\n"
			 << "\tMax Degree: " << graph.max_degree() << "\n"
			 << "\tAvg Degree: " << graph.avg_degree() << "\n"
			 << "}\n";
		return os;
	}



} // end namespace YAGL

#endif
