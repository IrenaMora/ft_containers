#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "../other/pair.hpp"
# include "../iterators/map_iterator.hpp"
# include "../iterators/map_const_iterator.hpp"
# include "../iterators/map_reverse_iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
	        class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef		map_iterator< ft::pair<const Key, T> > iterator;
		typedef		map_const_iterator< ft::pair<const Key, T> > const_iterator;
		typedef		map_reverse_iterator< ft::pair<const Key, T> > reverse_iterator;
		typedef		Compare key_compare;
		typedef		Compare value_compare;
		map();
		~map();
		map(map &another);
		map	&operator = (map &another);
		Allocator	get_allocator(void) const;
		T			&at(Key const &key) const;
		T			&operator [] (Key const &key);
		iterator	begin();
		iterator	end();
		const_iterator	cbegin() const;
		const_iterator	cend() const;
		reverse_iterator	rbegin();
		reverse_iterator	rend();
		bool		empty(void) const;
		size_t		size(void) const;
		size_t		max_size(void) const;
		void		clear(void);
		ft::pair<iterator, bool> insert(ft::pair<const Key, T> const &value);
		template <class InputIt>
		void		insert(InputIt first, InputIt last);
		size_t		erase(Key const &key);
		void		erase(iterator first, iterator last);
		void		erase(iterator pos);
		void		swap(map<Key, T, Compare, Allocator> &other);
		size_t		count(Key const &key) const;
		iterator	find(Key const &key);
		ft::pair<iterator, iterator>	equal_range(Key const &key);
		iterator	lower_bound(Key const &key);
		iterator	upper_bound(Key const &key);
		key_compare	key_comp(void) const;
		value_compare	value_comp(void) const;
		bool	operator == (map<Key, T, Compare, Allocator> &rhs);
		bool	operator != (map<Key, T, Compare, Allocator> &rhs);
		bool	operator < (map<Key, T, Compare, Allocator> &rhs);
		bool	operator <= (map<Key, T, Compare, Allocator> &rhs);
		bool	operator > (map<Key, T, Compare, Allocator> &rhs);
		bool	operator >= (map<Key, T, Compare, Allocator> &rhs);
	protected:
		s_array<const Key, T>	*node_begin;
		s_array<const Key, T>	*node_end;
		s_array<const Key, T>	*arr;
		size_t			value_size;
		Allocator 		alloc;
		Compare			compare;
		ft::s_array<const Key, T>	*create_child(ft::pair<const Key, T> const &value,
							   ft::s_array<const Key, T> *parent,
							   ft::s_array<const Key, T> *left_child,
							   ft::s_array<const Key, T> *right_child);
		void	delete_deep(s_array<const Key, T> *current);
		void	copy_deep(s_array<const Key, T> *current,
						  ft::map<Key, T, Compare, Allocator> *to);
		void	del_current_begin_end(ft::s_array<const Key, T> *current);
		void	delete_begin_end();
		void	set_begin_end();
	};

	template <class Key, class T, class Compare, class Allocator>
	ft::map<Key, T, Compare, Allocator>::map() : arr(NULL), value_size(0)
	{
		typename decltype(alloc)::template rebind< s_array<const Key, T> >::other real_alloc;
		node_begin = real_alloc.allocate(1);
		new (node_begin) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_BEGIN);
		node_end = real_alloc.allocate(1);
		new (node_end) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_END);
		node_begin->parent = NULL;
		node_begin->right_child = NULL;
		node_begin->left_child = NULL;
		node_end->parent = NULL;
		node_end->right_child = NULL;
		node_end->left_child = NULL;
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::delete_deep(s_array<const Key, T> *current)
	{
		if (current == NULL)
			return;
		if (current->left_child != NULL)
			delete_deep(current->left_child);
		if (current->right_child != NULL)
			delete_deep(current->right_child);
		if (current->type == T_STANDARD)
			delete (current);
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::map<Key, T, Compare, Allocator>::~map()
	{
		if (arr != NULL)
			delete_deep(arr);
		if (node_begin != NULL)
			delete (node_begin);
		if (node_end != NULL)
			delete (node_end);
		arr = NULL;
		value_size = 0;
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::copy_deep(s_array<const Key, T> *current,
														   ft::map<Key, T, Compare, Allocator> *to)
	{
		if (current->left_child != NULL)
			copy_deep(current->left_child, to);
		if (current->right_child != NULL)
			copy_deep(current->right_child, to);
		to->insert(ft::pair<const Key, T>(current->my_pair.first, current->my_pair.second));
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::map<Key, T, Compare, Allocator>::map(map &another) : arr(NULL), value_size(0)
	{
		typename decltype(alloc)::template rebind< s_array<const Key, T> >::other real_alloc;
		node_begin = real_alloc.allocate(1);
		new (node_begin) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_BEGIN);
		node_end = real_alloc.allocate(1);
		new (node_end) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_END);
		node_begin->parent = NULL;
		node_begin->right_child = NULL;
		node_begin->left_child = NULL;
		node_end->parent = NULL;
		node_end->right_child = NULL;
		node_end->left_child = NULL;
		another.delete_begin_end();
		if (another.size() == 0)
			return ;
		this->clear();
		copy_deep(another.arr, this);
		value_size = another.size();
		another.set_begin_end();
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::map<Key, T, Compare, Allocator> &ft::map<Key, T, Compare, Allocator>::operator = (map &another)
	{
		typename decltype(alloc)::template rebind< s_array<const Key, T> >::other real_alloc;
		node_begin = real_alloc.allocate(1);
		new (node_begin) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_BEGIN);
		node_end = real_alloc.allocate(1);
		new (node_end) ft::s_array<const Key, T>(ft::make_pair(Key(), T()), T_END);
		node_begin->parent = NULL;
		node_begin->right_child = NULL;
		node_begin->left_child = NULL;
		node_end->parent = NULL;
		node_end->right_child = NULL;
		node_end->left_child = NULL;
		another.delete_begin_end();
		if (another.size() == 0)
			return (*this);
		this->clear();
		copy_deep(another.arr, this);
		value_size = another.size();
		another.set_begin_end();
		return (*this);
	}

	template <class Key, class T, class Compare, class Allocator>
	Allocator	ft::map<Key, T, Compare, Allocator>::get_allocator() const
	{
		return (alloc);
	}

	template <class Key, class T, class Compare, class Allocator>
	T	&ft::map<Key, T, Compare, Allocator>::at(Key const &key) const
	{
		s_array<const Key, T>	*current = arr;

		if (size() == 0)
			throw (std::out_of_range("Not found"));
		while (1)
		{
			if (compare(current->my_pair.first, key))
			{
				if (current->right_child == NULL)
					throw (std::out_of_range("Not found"));
				else
					current = current->right_child;
			}
			else if (compare(key, current->my_pair.first))
			{
				if (current->left_child == NULL)
					throw (std::out_of_range("Not found"));
				else
					current = current->left_child;
			}
			else
				return (current->my_pair.second);
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	T	&ft::map<Key, T, Compare, Allocator>::operator [] (Key const &key)
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		try
		{
			return (at(key));
		}
		catch (std::out_of_range)
		{
			iterator	iter_pair = insert(ft::pair<const Key, T>(key, T())).first;
			return ((*iter_pair).second);
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::iterator ft::map<Key, T, Compare, Allocator>::begin()
	{
		if (size() == 0 || arr == NULL)
			return (iterator(node_begin));
		ft::s_array<const Key, T>	*current = arr;
		while (current->left_child != NULL && current->left_child->type == T_STANDARD)
			current = current->left_child;
		return (iterator(current));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::iterator ft::map<Key, T, Compare, Allocator>::end()
	{
		if (size() == 0 || arr == NULL)
			return (iterator(node_end));
		return (iterator(node_end));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::const_iterator ft::map<Key, T, Compare, Allocator>::cbegin() const
	{
		if (size() == 0 || arr == NULL)
			return (const_iterator(node_begin));
		ft::s_array<const Key, T>	*current = arr;
		while (current->left_child != NULL && current->left_child->type == T_STANDARD)
			current = current->left_child;
		return (const_iterator(current));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::const_iterator ft::map<Key, T, Compare, Allocator>::cend() const
	{
		if (size() == 0 || arr == NULL)
			return (const_iterator(node_end));
		return (const_iterator(node_end));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::reverse_iterator ft::map<Key, T, Compare, Allocator>::rbegin()
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		ft::s_array<const Key, T>	*current = arr;
		while (current->right_child != NULL && current->right_child->type == T_STANDARD)
			current = current->right_child;
		return (reverse_iterator(current));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::reverse_iterator ft::map<Key, T, Compare, Allocator>::rend()
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		return (reverse_iterator(node_begin));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::empty() const
	{
		return (value_size == 0);
	}

	template <class Key, class T, class Compare, class Allocator>
	size_t	ft::map<Key, T, Compare, Allocator>::size() const
	{
		return (value_size);
	}

	template <class Key, class T, class Compare, class Allocator>
	size_t	ft::map<Key, T, Compare, Allocator>::max_size() const
	{
		return (alloc.max_size() / 2);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::clear()
	{
		delete_deep(arr);
		arr = NULL;
		value_size = 0;
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::s_array<const Key, T>	*ft::map<Key, T, Compare, Allocator>::create_child(ft::pair<const Key, T> const &value,
															ft::s_array<const Key, T> *parent,
															ft::s_array<const Key, T> *left_child,
															ft::s_array<const Key, T> *right_child)
	{
		typename decltype(alloc)::template rebind< s_array<const Key, T> >::other real_alloc;
		ft::s_array<const Key, T>	*new_array = real_alloc.allocate(1);
		new (new_array) ft::s_array<const Key, T>(value);
		new_array->parent = parent;
		new_array->left_child = left_child;
		new_array->right_child = right_child;
		return (new_array);
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool> ft::map<Key, T, Compare, Allocator>::insert(ft::pair<const Key, T> const &value)
	{
		delete_begin_end();
		if (value_size == 0)
		{
			arr = create_child(value, NULL, NULL, NULL);
			value_size++;
			set_begin_end();
			return (ft::make_pair(iterator(arr), true));
		}
		else
		{
			s_array<const Key, T>	*current = arr;
			while (1)
			{
				if (compare(current->my_pair.first, value.first))
				{
					if (current->right_child == NULL)
					{
						current->right_child = create_child(value, current, NULL, NULL);
						value_size++;
						set_begin_end();
						return (ft::pair<iterator, bool>(iterator(current->right_child), true));
					}
					else
						current = current->right_child;
				}
				else if (compare(value.first, current->my_pair.first))
				{
					if (current->left_child == NULL)
					{
						current->left_child = create_child(value, current, NULL, NULL);
						value_size++;
						set_begin_end();
						return (ft::pair<iterator, bool>(iterator(current->left_child), true));
					}
					else
					{
						current = current->left_child;
					}
				}
				else
				{
					set_begin_end();
					return (ft::pair<iterator, bool>(iterator(current), false));
				}
			}
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	template <class InputIt>
	void		ft::map<Key, T, Compare, Allocator>::insert(InputIt first, InputIt last)
	{
		while (first != last)
		{
			insert(ft::make_pair((*first).first, (*first).second));
			first++;
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	size_t	ft::map<Key, T, Compare, Allocator>::count(Key const &key) const
	{
		try
		{
			at(key);
			return (1);
		}
		catch (std::out_of_range)
		{
			return (0);
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::iterator ft::map<Key, T, Compare, Allocator>::find(Key const &key)
	{
		s_array<const Key, T>	*current = arr;

		if (size() == 0)
		{
			return (end());
		}
		while (1)
		{
			if (compare(current->my_pair.first, key))
			{
				if (current->right_child == NULL)
				{
					return (end());
				}
				else
					current = current->right_child;
			}
			else if (compare(key, current->my_pair.first))
			{
				if (current->left_child == NULL)
				{
					return (end());
				}
				else
					current = current->left_child;
			}
			else
			{
				return (iterator(current));
			}
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::del_current_begin_end(ft::s_array<const Key, T> *current)
	{
		if (current == NULL || (current->right_child == NULL && current->left_child == NULL))
			return ;
		del_current_begin_end(current->right_child);
		del_current_begin_end(current->left_child);
		if (current->right_child != NULL && current->right_child->type != T_STANDARD)
			current->right_child = NULL;
		if (current->left_child != NULL && current->left_child->type != T_STANDARD)
			current->left_child = NULL;
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::delete_begin_end()
	{
		if (size() == 0 || arr == NULL)
			return ;
		ft::s_array<const Key, T>	*current = arr;
		del_current_begin_end(current);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::set_begin_end()
	{
		if (node_begin == NULL && node_end == NULL)
			return ;
		if (size() == 0 || arr == NULL)
			return ;
		ft::s_array<const Key, T>	*header1 = arr;
		ft::s_array<const Key, T>	*header2 = arr;

		if (header1 != NULL)
		{
			while (header1->right_child != NULL)
				header1 = header1->right_child;
			header1->right_child = node_end;
			node_end->parent = header1;
		}
		if (header2 != NULL)
		{
			while (header2->left_child != NULL)
				header2 = header2->left_child;
			header2->left_child = node_begin;
			node_begin->parent = header2;
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	size_t	ft::map<Key, T, Compare, Allocator>::erase(Key const &key)
	{
		s_array<const Key, T>	*current = arr;

		delete_begin_end();
		if (size() == 0)
		{
			set_begin_end();
			return (0);
		}
		while (1)
		{
			if (compare(current->my_pair.first, key))
			{
				if (current->right_child == NULL)
				{
					set_begin_end();
					return (0);
				}
				else
					current = current->right_child;
			}
			else if (compare(key, current->my_pair.first))
			{
				if (current->left_child == NULL)
				{
					set_begin_end();
					return (0);
				}
				else
					current = current->left_child;
			}
			else
			{
				value_size--;
				s_array<const Key, T>	*for_delete = current;
				s_array<const Key, T>	*replace;
				if (current->left_child != NULL && current->right_child != NULL && current->parent == NULL)
				{
					replace = current->right_child;
					while (replace->left_child != NULL)
						replace = replace->left_child;
					if (replace->right_child != NULL && replace->parent->left_child == replace)
					{
						replace->parent->left_child = replace->right_child;
						replace->right_child->parent = replace->parent;
					}
					else if (replace->parent->left_child == replace)
						replace->parent->left_child = NULL;
					arr = replace;
					arr->left_child = current->left_child;
					if (current->right_child != replace)
					{
						arr->right_child = current->right_child;
						arr->right_child->parent = arr;
					}
					replace->left_child->parent = arr;
				}
				else if (current->left_child != NULL && current->right_child != NULL)
				{
					replace = current->right_child;
					while (replace->left_child != NULL)
						replace = replace->left_child;
					if (replace->right_child != NULL && replace->parent->left_child == replace)
					{
						replace->parent->left_child = replace->right_child;
						replace->right_child->parent = replace->parent;
					}
					else if (replace->parent->left_child == replace)
						replace->parent->left_child = NULL;
					if (current->parent->right_child == current)
						current->parent->right_child = replace;
					else
						current->parent->left_child = replace;
					replace->parent = current->parent;
					replace->left_child = current->left_child;
					replace->left_child->parent = replace;
				}
				else if (current->right_child != NULL)
				{
					replace = current->right_child;
					if (current->parent == NULL)
					{
						arr = replace;
						replace->parent = NULL;
					}
					else if (current->parent->right_child == current)
					{
						current->parent->right_child = replace;
						replace->parent = current->parent;
					}
					else
					{
						current->parent->left_child = replace;
						replace->parent = current->parent;
					}
				}
				else if (current->left_child != NULL)
				{
					replace = current->left_child;
					if (current->parent == NULL)
					{
						arr = replace;
						replace->parent = NULL;
					}
					else if (current->parent->left_child == current)
					{
						current->parent->left_child = replace;
						replace->parent = current->parent;
					}
					else
					{
						current->parent->right_child = replace;
						replace->parent = current->parent;
					}
				}
				else if (current->right_child == NULL && current->left_child == NULL)
				{
					if (current->parent == NULL)
						arr = NULL;
					else if (current->parent->right_child == current)
						current->parent->right_child = NULL;
					else
						current->parent->left_child = NULL;
				}
				delete (for_delete);
				set_begin_end();
				return (1);
			}
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::erase(ft::map<Key, T, Compare, Allocator>::iterator first,
													   ft::map<Key, T, Compare, Allocator>::iterator last)
	{
		while (first != last)
		{
			erase(first);
			first++;
		}
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::erase(ft::map<Key, T, Compare, Allocator>::iterator pos)
	{
		erase((*pos).first);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::swap(map<Key, T, Compare, Allocator> &other)
	{
		arr = other.arr;
		node_begin = other.node_begin;
		node_end = other.node_end;
		value_size = other.value_size;
		compare = other.compare;

		other.arr = NULL;
		other.node_begin = NULL;
		other.node_end = NULL;
		other.value_size = 0;
	}

	template <class Key, class T, class Compare, class Allocator>
	ft::pair<typename  ft::map<Key, T, Compare, Allocator>::iterator, typename ft::map<Key, T, Compare, Allocator>::iterator>	ft::map<Key, T, Compare, Allocator>::equal_range(Key const &key)
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::iterator	ft::map<Key, T, Compare, Allocator>::lower_bound(Key const &key)
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		iterator	first = begin();
		iterator	last = end();

		while (first != last)
		{
			if ((*first).first >= key)
				return (first);
			first++;
		}
		return (last);
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::iterator	ft::map<Key, T, Compare, Allocator>::upper_bound(Key const &key)
	{
		if (size() == 0 || arr == NULL)
			throw (std::exception());
		iterator	first = begin();
		iterator	last = end();

		while (first != last)
		{
			if ((*first).first > key)
				return (first);
			first++;
		}
		return (last);
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::key_compare ft::map<Key, T, Compare, Allocator>::key_comp() const
	{
		return (compare);
	}

	template <class Key, class T, class Compare, class Allocator>
	typename ft::map<Key, T, Compare, Allocator>::key_compare ft::map<Key, T, Compare, Allocator>::value_comp() const
	{
		return (compare);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator == (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		if (size() != rhs.size())
			return (false);
		iterator	first_this = begin();
		iterator	end_this = end();
		iterator	first_another = rhs.begin();
		while (first_this != end_this)
		{
			if ((*first_this).second != (*first_another).second)
				return (false);
			first_this++;
			first_another++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator != (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(*this == rhs));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator < (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		if (rhs.size() == 0 && size() == 0)
			return (false);
		if (rhs.size() == 0)
			return (true);
		if (size() == 0)
			return (false);
		iterator	first1 = begin();
		iterator	last1 = end();
		iterator	first2 = rhs.begin();
		iterator	last2 = rhs.end();
		while (first1 != last1 && first2 != last2)
		{
			if ((*first1).second <= (*first2).second)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator > (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		if (rhs.size() == 0 && size() == 0)
			return (false);
		if (rhs.size() == 0)
			return (false);
		if (size() == 0)
			return (true);
		iterator	first1 = begin();
		iterator	last1 = end();
		iterator	first2 = rhs.begin();
		iterator	last2 = rhs.end();
		while (first1 != last1 && first2 != last2)
		{
			if ((*first1).second < (*first2).second)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator <= (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		if (rhs.size() == 0 && size() == 0)
			return (true);
		if (rhs.size() == 0)
			return (true);
		if (size() == 0)
			return (false);
		iterator	first1 = begin();
		iterator	last1 = end();
		iterator	first2 = rhs.begin();
		iterator	last2 = rhs.end();
		while (first1 != last1 && first2 != last2)
		{
			if ((*first1).second <= (*first2).second)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	ft::map<Key, T, Compare, Allocator>::operator >= (ft::map<Key, T, Compare, Allocator> &rhs)
	{
		if (rhs.size() == 0 && size() == 0)
			return (true);
		if (rhs.size() == 0)
			return (false);
		if (size() == 0)
			return (true);
		iterator	first1 = begin();
		iterator	last1 = end();
		iterator	first2 = rhs.begin();
		iterator	last2 = rhs.end();
		while (first1 != last1 && first2 != last2)
		{
			if ((*first1).second > (*first2).second)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	swap(ft::map<Key, T, Compare, Allocator> &lhs, ft::map<Key, T, Compare, Allocator> &rhs)
	{
		ft::map<Key, T, Compare, Allocator> lhs_tmp = lhs;
		lhs = std::move(rhs);
		rhs = std::move(lhs);
	}
}

#endif
