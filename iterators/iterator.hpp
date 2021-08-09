#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include "../other/categories.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&>
	class iterator
	{
	public:
		iterator();
		iterator(T &iter);
		~iterator();
		iterator(iterator const &another);
		iterator	&operator = (iterator const &another);
		T			&operator * (void);
		iterator<T>	&operator ++ (void);
		iterator<T>	&operator -- (void);
		iterator<T>	operator ++ (int);
		iterator<T>	operator -- (int);
		bool		operator == (iterator const &another);
		bool		operator != (iterator const &another);
		bool		operator < (iterator const &another);
		bool		operator > (iterator const &another);
		bool		operator <= (iterator const &another);
		bool		operator >= (iterator const &another);
		iterator<T>	operator += (int const &value);
		iterator<T>	operator -= (int const &value);
		iterator<T>	operator + (int const &value);
		iterator<T>	operator - (int const &value);
		friend iterator<T>	operator + (int const &value, iterator &another)
		{
			another.pointer += value;
			return (another);
		}
		friend iterator<T>	operator - (int const &value, iterator &another)
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
		Pointer						ptr;
	};

	template <class T, class Pointer, class Reference>
	ft::iterator<T, Pointer, Reference>::iterator() : ptr(NULL) {}

	template <class T, class Pointer, class Reference>
	ft::iterator<T, Pointer, Reference>::iterator(T &iter) : ptr(&iter) {}

	template <class T, class Pointer, class Reference>
	ft::iterator<T, Pointer, Reference>::~iterator() {}

	template <class T, class Pointer, class Reference>
	ft::iterator<T, Pointer, Reference>::iterator(iterator const &another)
	{
		this->ptr = another.ptr;
	}

	template <class T, class Pointer, class Reference>
	iterator<T, Pointer, Reference>	&ft::iterator<T, Pointer, Reference>::operator = (iterator const &another)
	{
		this->ptr = another.ptr;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	T	&ft::iterator<T, Pointer, Reference>::operator * ()
	{
		return (*ptr);
	}

	template <class T, class Pointer, class Reference>
	iterator<T>	&ft::iterator<T, Pointer, Reference>::operator ++ ()
	{
		ptr++;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	iterator<T>	&ft::iterator<T, Pointer, Reference>::operator -- ()
	{
		ptr--;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	iterator<T>	ft::iterator<T, Pointer, Reference>::operator ++ (int)
	{
		return (iterator(*ptr++));
	}

	template <class T, class Pointer, class Reference>
	iterator<T>	ft::iterator<T, Pointer, Reference>::operator -- (int)
	{
		return (iterator(*ptr--));
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator == (iterator const &another)
	{
		return (ptr == another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator != (iterator const &another)
	{
		return (ptr != another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator < (iterator const &another)
	{
		return (ptr < another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator > (iterator const &another)
	{
		return (ptr > another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator <= (iterator const &another)
	{
		return (ptr <= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::iterator<T, Pointer, Reference>::operator >= (iterator const &another)
	{
		return (ptr >= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	ft::iterator<T>	ft::iterator<T, Pointer, Reference>::operator += (int const &value)
	{
		ptr += value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::iterator<T>	ft::iterator<T, Pointer, Reference>::operator -= (int const &value)
	{
		ptr -= value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::iterator<T>	ft::iterator<T, Pointer, Reference>::operator + (int const &value)
	{
		ptr += value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::iterator<T>	ft::iterator<T, Pointer, Reference>::operator - (int const &value)
	{
		ptr -= value;
		return (*this);
	}
}

#endif
