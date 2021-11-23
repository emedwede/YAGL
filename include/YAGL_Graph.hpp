#ifndef YAGL_GRAPH_HPP
#define YAGL_GRPAH_HPP

#pragma once 

#include <iostream> 
#include <unordered_map> 
#include <unordered_set>
#include <utility> // for pair 

#include "YAGL_Node.hpp"

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
			using edge_type = char; // TODO: remove placeholder
			
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
			using adjaceny_list_type = std::unordered_map<key_type, in_out_nbr_type>;
			using node_list_type = std::unordered_map<key_type, node_type>;

			// by default count with the largest unsigned type
			using counting_type = std::size_t;

			//TODO: define any useful iterators
			
		private:
			node_list_type node_list;
			adjaceny_list_type adjaceny_list;	

		public:
			Graph();

			Graph(const DataType placeholder);
			
			void setEdgeset(/* Needs to take in an edge set*/);
			
			void getEdgeset();
			
			void getEdge();
			
			void setEdge();

			void addEdge(/* Takes EdgeType*/);

			void removeEdge();
			
			void setNodeSet();

			void getNodeSet();

			void addNode();
			
			void removeNode();
			
			void numNodes();

			void numEdges();

			void isDirected();

			void isUndirected();
			
			friend std::ostream &operator<<<>(std::ostream& os, const Graph<KeyType, DataType>& graph);
	};
	
	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph()
	{
		std::cout << "Default graph constructor!\n";
	}

	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph(const DataType placeholder)
	{
		std::cout << "Overloaded graph const!\n";
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
	void Graph<KeyType, DataType>::addEdge()
	{

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
	void Graph<KeyType, DataType>::addNode()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::removeNode()
	{

	}

	template <typename KeyType, typename DataType>
	void Graph<KeyType, DataType>::numNodes()
	{

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
