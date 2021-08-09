#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iostream>

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typename Iter::difference_type			difference_type;
		typename Iter::value_type				value_type;
		typename Iter::pointer					pointer;
		typename Iter::pointer					*reference;
 		typename Iter::iterator_category		iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		std::ptrdiff_t				difference_type;
		T							value_type;
		T							*pointer;
		T							&reference;
		std::output_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<T const *>
	{
		std::ptrdiff_t				difference_type;
		T							value_type;
		T							*pointer;
		T							&reference;
		std::output_iterator_tag	iterator_category;
	};
}

#endif
