#ifndef PAIR_HPP
# define PAIR_HPP

# include "lexicographical_compare.hpp"

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 type1;
		typedef T2 type2;
		pair();
		pair(T1 const &x, T2 const &y);
		template <class U1, class U2>
		pair(pair<U1,U2> const &p);
		pair	&operator = (pair const &other);
		T1		first;
		T2		second;
		bool	operator == (pair const &other);
		bool	operator != (pair const &other);
		bool	operator < (pair &other);
		bool	operator <= (pair &other);
		bool	operator > (pair &other);
		bool	operator >= (pair &other);
	};

	template <class T1, class T2>
	ft::pair<T1, T2>::pair() : first(T1()), second(T2()) {}

	template <class T1, class T2>
	ft::pair<T1, T2>::pair(T1 const &x, T2 const &y) : first(x), second(y) {}

	template <class T1, class T2>
	template <class U1, class U2>
	ft::pair<T1, T2>::pair(pair<U1, U2> const &p) : first(p.first), second(p.second) {}

	template <class T1, class T2>
	pair<T1, T2>	&ft::pair<T1, T2>::operator = (pair const &other)
	{
		first = other.first;
		second = other.second;
		return (*this);
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator == (pair const &other)
	{
		return (first == other.first
					&& second == other.second);
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator != (pair const &other)
	{
		return (!(this == other));
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator < (pair &other)
	{
		if (first < other.first)
			return (true);
		if (first > other.first)
			return (false);
		if (second < other.second)
			return (true);
		return (false);
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator <= (pair &other)
	{
		return (!(other < *this));
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator > (pair &other)
	{
		return (other < *this);
	}

	template <class T1, class T2>
	bool	ft::pair<T1, T2>::operator >= (pair &other)
	{
		return (!(*this < other));
	}

	template <class T1, class T2>
	ft::pair<const T1, T2>	make_pair(T1 t, T2 u)
	{
		return (ft::pair<const T1, T2>(t, u));
	}

}


#endif
