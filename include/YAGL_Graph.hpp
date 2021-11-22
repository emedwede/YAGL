#ifndef YAGL_GRAPH_HPP
#define YAGL_GRPAH_HPP

#pragma once 

#include <iostream>

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
		private:

		public:
			Graph() = default;

			Graph( const DataType placeholder);
			
			
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
			
			void isDirected();

			void isUndirected();
			
			friend std::ostream &operator<<<>(std::ostream& os, const Graph<KeyType, DataType>& graph);
	};

	template <typename KeyType, typename DataType>
	Graph<KeyType, DataType>::Graph(const DataType placeholder)
	{

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
