#ifndef YAGL_NODE_H
#define YAGL_NODE_H

#pragma once 

#include <iostream>

namespace YAGL
{
	template <typename KeyType, typename DataType>
	class Node;

	template <typename KeyType, typename DataType>
	std::ostream& operator<<(std::ostream& os, const Node<KeyType, DataType>& node);

	template <typename KeyType, typename DataType>
	class Node
	{
		public:
			using data_type = DataType;
			using key_type = KeyType;
			
			Node(const KeyType, const DataType& data);
			~Node() = default;

			const KeyType& getKey() const;
			DataType& getData();

			bool operator==(const Node<KeyType, DataType>& b) const;
			bool operator<(const Node<KeyType, DataType>& b) const;

			friend std::ostream &operator<<<>(std::ostream &os, const Node<KeyType, DataType>& node);

		private:
			KeyType key;
			DataType data;	
	};

	template <typename KeyType, typename DataType>
	Node<KeyType, DataType>::Node(const KeyType k, const DataType& d)
	: key(k), data(d) //TODO: possibly make it a move
	{
		
	}

	template <typename KeyType, typename DataType>
	const KeyType& Node<KeyType, DataType>::getKey() const
	{
		return key;
	}

	template <typename KeyType, typename DataType>
	DataType& Node<KeyType, DataType>::getData() 
	{
		return data;
	}

	template <typename KeyType, typename DataType>
	bool Node<KeyType, DataType>::operator==(const Node<KeyType, DataType>& b) const
	{
		return (this->key == b.key && this-> data == b.data);
	}
	
	template <typename KeyType, typename DataType>
	std::ostream &operator<<(std::ostream &os, const Node<KeyType, DataType>& node)
	{
		os << "Node: {\n"
			 << "\tKey:\t" << node.key << "\n"
			 << "\tData:\t" << node.data << "\n"
			 << "}\n";
		return os;
	}

} //end namespace YAGL

#endif
