#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <iostream>
# include "../containers/map.hpp"
# include "../other/categories.hpp"
# include "map_iterator.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&>
	class map_reverse_iterator
	{
	public:
		map_reverse_iterator();
		map_reverse_iterator(ft::s_array<typename T::type1, typename T::type2> *node);
		~map_reverse_iterator();
		map_reverse_iterator(map_reverse_iterator const &another);
		map_reverse_iterator	&operator = (map_reverse_iterator const &another);
		T				&operator * (void);
		map_reverse_iterator<T>	&operator ++ (void);
		map_reverse_iterator<T>	&operator -- (void);
		map_reverse_iterator<T>	operator ++ (int);
		map_reverse_iterator<T>	operator -- (int);
		bool		operator == (map_reverse_iterator const &another);
		bool		operator != (map_reverse_iterator const &another);
		bool		operator < (map_reverse_iterator const &another);
		bool		operator > (map_reverse_iterator const &another);
		bool		operator <= (map_reverse_iterator const &another);
		bool		operator >= (map_reverse_iterator const &another);
		map_reverse_iterator<T>	operator += (int const &value);
		map_reverse_iterator<T>	operator -= (int const &value);
		map_reverse_iterator<T>	operator + (int const &value);
		map_reverse_iterator<T>	operator - (int const &value);
		friend map_reverse_iterator<T>	operator + (int const &value, map_reverse_iterator &another)
		{
			another.pointer += value;
			return (another);
		}
		friend map_reverse_iterator<T>	operator - (int const &value, map_reverse_iterator &another)
		{
			another.pointer -= value;
			return (another);
		}
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef Pointer						pointer;
		typedef Reference					reference;
		typedef std::output_iterator_tag	iterator_category;
	private:
		ft::pair<typename T::type1, typename T::type2>	my_pair;
		s_array<typename T::type1, typename T::type2>	*node;
	};

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T, Pointer, Reference>::map_reverse_iterator() : node(NULL) {}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T, Pointer, Reference>::map_reverse_iterator(ft::s_array<typename T::type1, typename T::type2> *_node) : my_pair(_node->my_pair.first, _node->my_pair.second), node(_node) {}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T, Pointer, Reference>::~map_reverse_iterator() {}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T, Pointer, Reference>::map_reverse_iterator(map_reverse_iterator const &another)
	{
		this->node = another.node;
	}

	template <class T, class Pointer, class Reference>
	map_reverse_iterator<T, Pointer, Reference>	&ft::map_reverse_iterator<T, Pointer, Reference>::operator = (map_reverse_iterator const &another)
	{
		this->my_pair(another.my_pair);
		this->node = another.node;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	T	&ft::map_reverse_iterator<T, Pointer, Reference>::operator * ()
	{
		return (node->my_pair);
	}

	template <class T, class Pointer, class Reference>
	map_reverse_iterator<T>	&ft::map_reverse_iterator<T, Pointer, Reference>::operator ++ () 
	{
		if (node->type != T_STANDARD)
		{
			node = node->parent;
			return (*this);
		}
		if (node->left_child != NULL)
		{
			node = node->left_child;
			while (node->right_child != NULL)
				node = node->right_child;
		}
		else
		{
			ft::s_array<typename T::type1, typename T::type2> *tmp_node = node;
			while (1)
			{
				if (tmp_node->parent == NULL)
					return (*this);
				tmp_node = tmp_node->parent;
				if (tmp_node->my_pair.first < node->my_pair.first)
				{
					node = tmp_node;
					break ;
				}
			}
		}
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	map_reverse_iterator<T>	&ft::map_reverse_iterator<T, Pointer, Reference>::operator -- () 
	{
		if (node->type != T_STANDARD)
		{
			node = node->parent;
			return (*this);
		}
		if (node->right_child != NULL)
		{
			node = node->right_child;
			while (node->left_child != NULL)
				node = node->left_child;
		}
		else
		{
			ft::s_array<typename T::type1, typename T::type2> *tmp_node = node;
			while (1)
			{
				if (tmp_node->parent == NULL)
					return (*this);
				tmp_node = tmp_node->parent;
				if (tmp_node->my_pair.first > node->my_pair.first)
				{
					node = tmp_node;
					break ;
				}
			}
		}
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator ++ (int) 
	{
		map_reverse_iterator<T, Pointer, Reference>	tmp = map_reverse_iterator<T, Pointer, Reference>(*this);
		++(*this);
		return (tmp);
	}

	template <class T, class Pointer, class Reference>
	map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator -- (int) 
	{
		map_reverse_iterator<T, Pointer, Reference>	tmp = map_reverse_iterator<T, Pointer, Reference>(*this);
		--(*this);
		return (tmp);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator == (map_reverse_iterator const &another)
	{
		return (this->node == another.node);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator != (map_reverse_iterator const &another)
	{
		return (this->node != another.node);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator < (map_reverse_iterator const &another)
	{
		return (node->my_pair.first > another.my_pair.first);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator > (map_reverse_iterator const &another)
	{
		return (node->my_pair.first < another.my_pair.first);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator <= (map_reverse_iterator const &another)
	{
		return (node->my_pair.first >= another.my_pair.first);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::map_reverse_iterator<T, Pointer, Reference>::operator >= (map_reverse_iterator const &another)
	{
		return (node->my_pair.first <= another.my_pair.first);
	}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator += (int const &value)
	{
		int position = 0;
		if (value > 0)
		{
			while (position < value)
			{
				--(*this);
				position++;
			}
		}
		else
		{
			while (position > value)
			{
				++(*this);
				position--;
			}
		}
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator -= (int const &value)
	{
		int position = 0;
		if (value > 0)
		{
			while (position < value)
			{
				++(*this);
				position++;
			}
		}
		else
		{
			while (position > value)
			{
				--(*this);
				position--;
			}
		}
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator + (int const &value)
	{
		return (*this -= value);
	}

	template <class T, class Pointer, class Reference>
	ft::map_reverse_iterator<T>	ft::map_reverse_iterator<T, Pointer, Reference>::operator - (int const &value)
	{
		return (*this += value);
	}
}

#endif
