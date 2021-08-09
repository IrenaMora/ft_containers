#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include "../other/categories.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&>
	class reverse_iterator
	{
	public:
		reverse_iterator();
		reverse_iterator(T &iter);
		~reverse_iterator();
		reverse_iterator(reverse_iterator const &another);
		reverse_iterator	&operator = (reverse_iterator const &another);
		T			&operator * (void);
		reverse_iterator<T>	&operator ++ (void);
		reverse_iterator<T>	&operator -- (void);
		reverse_iterator<T>	operator ++ (int);
		reverse_iterator<T>	operator -- (int);
		bool		operator == (reverse_iterator const &another);
		bool		operator != (reverse_iterator const &another);
		bool		operator < (reverse_iterator const &another);
		bool		operator > (reverse_iterator const &another);
		bool		operator <= (reverse_iterator const &another);
		bool		operator >= (reverse_iterator const &another);
		reverse_iterator<T>	operator += (int const &value);
		reverse_iterator<T>	operator -= (int const &value);
		reverse_iterator<T>	operator + (int const &value);
		reverse_iterator<T>	operator - (int const &value);
		friend reverse_iterator<T>	operator + (int const &value, reverse_iterator &another)
		{
			another.pointer += value;
			return (another);
		}
		friend reverse_iterator<T>	operator - (int const &value, reverse_iterator &another)
		{
			another.pointer -= value;
			return (another);
		}
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef Pointer						pointer;
		typedef Reference					reference;
		typedef std::output_iterator_tag	reverse_iterator_category;
	private:
		Pointer						ptr;
	};

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T, Pointer, Reference>::reverse_iterator() : ptr(NULL) {}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T, Pointer, Reference>::reverse_iterator(T &iter) : ptr(&iter) {}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T, Pointer, Reference>::~reverse_iterator() {}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T, Pointer, Reference>::reverse_iterator(reverse_iterator const &another)
	{
		this->ptr = another.ptr;
	}

	template <class T, class Pointer, class Reference>
	reverse_iterator<T, Pointer, Reference>	&ft::reverse_iterator<T, Pointer, Reference>::operator = (reverse_iterator const &another)
	{
		this->ptr = another.ptr;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	T	&ft::reverse_iterator<T, Pointer, Reference>::operator * ()
	{
		return (*ptr);
	}

	template <class T, class Pointer, class Reference>
	reverse_iterator<T>	&ft::reverse_iterator<T, Pointer, Reference>::operator ++ ()
	{
		ptr--;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	reverse_iterator<T>	&ft::reverse_iterator<T, Pointer, Reference>::operator -- ()
	{
		ptr++;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator ++ (int)
	{
		return (reverse_iterator(*ptr--));
	}

	template <class T, class Pointer, class Reference>
	reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator -- (int)
	{
		return (reverse_iterator(*ptr++));
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator == (reverse_iterator const &another)
	{
		return (ptr == another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator != (reverse_iterator const &another)
	{
		return (ptr != another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator < (reverse_iterator const &another)
	{
		return (ptr < another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator > (reverse_iterator const &another)
	{
		return (ptr > another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator <= (reverse_iterator const &another)
	{
		return (ptr <= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::reverse_iterator<T, Pointer, Reference>::operator >= (reverse_iterator const &another)
	{
		return (ptr >= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator += (int const &value)
	{
		ptr -= value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator -= (int const &value)
	{
		ptr += value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator + (int const &value)
	{
		ptr -= value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::reverse_iterator<T>	ft::reverse_iterator<T, Pointer, Reference>::operator - (int const &value)
	{
		ptr += value;
		return (*this);
	}
}

#endif
