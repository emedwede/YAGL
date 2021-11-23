#ifndef YAGL_EDGE_HPP
#define YAGL_EDGE_HPP

#pragma once

#include <utility>

#include "YAGL_Node.hpp"

namespace YAGL
{
	template <typename KeyType, typename DataType>
	class Edge;

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, const Edge<KeyType, DataType>& edge);

	template <typename KeyType, typename DataType>
	class Edge 
	{
		public:
			using key_type = KeyType;
			using data_type = DataType;
			using edge_type = std::pair<const Node<KeyType, DataType>*, const Node<KeyType, DataType>*>;

		private:
			KeyType key;
			std::pair<const Node<KeyType, DataType>*, const Node<KeyType, DataType>*> node_pair;

		public:
			Edge(KeyType k, Node<KeyType, DataType>& node_a, Node<KeyType, DataType>& node_b);
			
			const KeyType& getKey() const;
			const std::pair<const Node<KeyType, DataType>*, const Node<KeyType, DataType>*>& getNodePair() const;

			bool operator==(const Edge<KeyType, DataType>& b) const;
			bool operator<(const Edge<KeyType, DataType>& b) const;

			friend std::ostream& operator<<<>(std::ostream& os, const Edge<KeyType, DataType>& edge);
	};

	template <typename KeyType, typename DataType>
	Edge<KeyType, DataType>::Edge(KeyType k, Node<KeyType, DataType>& node_a, Node<KeyType, DataType>& node_b)
	: key(k), node_pair(&node_a, &node_b)
	{

	}
	
	template <typename KeyType, typename DataType>
	const KeyType& Edge<KeyType, DataType>::getKey() const
	{
		return key;
	}

	template <typename KeyType, typename DataType>
	const std::pair<const Node<KeyType, DataType>*, const Node<KeyType, DataType>*>&  
	Edge<KeyType, DataType>::getNodePair() const
	{
		return node_pair;
	}

	template <typename KeyType, typename DataType>
	bool Edge<KeyType, DataType>::operator==(const Edge<KeyType, DataType>& b) const
	{
		return (this->key == b.key && this->node_pair == b.node_pair);
	}
	
	template <typename KeyType, typename DataType>
	bool Edge<KeyType, DataType>::operator<(const Edge<KeyType, DataType>& b) const 
	{
		return ( this->key < b.key );
	}
	
	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, const Edge<KeyType, DataType>& edge) 
	{
		os << "Edge is a node pair: {\n"
			 << "\tNode ID One: " << edge.node_pair.first->getKey() << "\n"
			 << "\tNode ID Two: " << edge.node_pair.second->getKey() << "\n"
			 << "}\n";

			 return os;
	}
} // ending namespace YAGL

#endif
