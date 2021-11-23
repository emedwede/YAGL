#ifndef YAGL_GRAPH_HPP
#define YAGL_GRPAH_HPP

#pragma once 

#include <iostream> 
#include <unordered_map> 
#include <unordered_set>
#include <utility> // for pair 

#include "YAGL_Node.hpp"
#include "YAGL_Edge.hpp"

namespace YAGL 
{

	template <typename KeyType, typename DataType>
	class Graph;

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, const Graph<KeyType, DataType> &graph);
	
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
			adjacency_list_type adjaceny_list;	
			
			bool undirected;

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

			void removeEdge();
			
			void setNodeSet();

			void getNodeSet();

			void addNode(const Node<KeyType, DataType>& node);
			
			void removeNode(const Node<KeyType, DataType>& node);
			
			node_iterator findNode(KeyType k);

			counting_type numNodes();

			void numEdges();

			void isDirected();

			void isUndirected();
			
			friend std::ostream &operator<<<>(std::ostream& os, const Graph<KeyType, DataType>& graph);
	};
	
	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph()
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
		return adjaceny_list.begin();	
	}

	template <typename KeyType, typename DataType>
	typename Graph<KeyType, DataType>::adjacency_iterator Graph<KeyType, DataType>::adjacency_list_end()
	{
		return adjaceny_list.end();	
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
		return adjaceny_list.find(node.getKey())->second.first; 
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
		return adjaceny_list.find(node.getData())->second.second;
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
	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::removeEdge()
	{

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
		adjaceny_list[node.getKey()]; //TODO: is there a better way to default initialize
	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::removeNode(const Node<KeyType, DataType>& node)
	{
		node_list.erase(node.getKey());
		adjaceny_list.erase(node.getKey());
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
	void Graph<KeyType, DataType>::numEdges()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::isDirected()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::isUndirected()
	{

	}

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, const Graph<KeyType, DataType>& graph)
	{
		os << "Graph: {\n" 
			 << "\tEmpty Graph Class\n"
			 << "}\n";
		return os;
	}



} // end namespace YAGL

#endif
