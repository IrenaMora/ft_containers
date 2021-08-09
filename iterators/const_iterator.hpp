#ifndef CONST_ITERATOR_HPP
# define CONST_ITERATOR_HPP

# include <iostream>
# include "../other/categories.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&>
	class const_iterator
	{
	public:
		const_iterator();
		const_iterator(T &iter);
		~const_iterator();
		const_iterator(const_iterator const &another);
		const_iterator	&operator = (const_iterator const &another);
		T			&operator * (void) const;
		const_iterator<T>	&operator ++ (void);
		const_iterator<T>	&operator -- (void);
		const_iterator<T>	operator ++ (int);
		const_iterator<T>	operator -- (int);
		bool		operator == (const_iterator const &another);
		bool		operator != (const_iterator const &another);
		bool		operator < (const_iterator const &another);
		bool		operator > (const_iterator const &another);
		bool		operator <= (const_iterator const &another);
		bool		operator >= (const_iterator const &another);
		const_iterator<T>	operator += (int const &value);
		const_iterator<T>	operator -= (int const &value);
		const_iterator<T>	operator + (int const &value);
		const_iterator<T>	operator - (int const &value);
		friend const_iterator<T>	operator + (int const &value, const_iterator &another)
		{
			another.pointer += value;
			return (another);
		}
		friend const_iterator<T>	operator - (int const &value, const_iterator &another)
		{
			another.pointer -= value;
			return (another);
		}
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef Pointer						pointer;
		typedef Reference					reference;
		typedef std::output_iterator_tag	const_iterator_category;
	private:
		Pointer						ptr;
	};

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T, Pointer, Reference>::const_iterator() : ptr(NULL) {}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T, Pointer, Reference>::const_iterator(T &iter) : ptr(&iter) {}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T, Pointer, Reference>::~const_iterator() {}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T, Pointer, Reference>::const_iterator(const_iterator const &another)
	{
		this->ptr = another.ptr;
	}

	template <class T, class Pointer, class Reference>
	const_iterator<T, Pointer, Reference>	&ft::const_iterator<T, Pointer, Reference>::operator = (const_iterator const &another)
	{
		this->ptr = another.ptr;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	T	&ft::const_iterator<T, Pointer, Reference>::operator * () const
	{
		return (*ptr);
	}

	template <class T, class Pointer, class Reference>
	const_iterator<T>	&ft::const_iterator<T, Pointer, Reference>::operator ++ ()
	{
		ptr++;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	const_iterator<T>	&ft::const_iterator<T, Pointer, Reference>::operator -- ()
	{
		ptr--;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator ++ (int)
	{
		return (const_iterator(*ptr++));
	}

	template <class T, class Pointer, class Reference>
	const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator -- (int)
	{
		return (const_iterator(*ptr--));
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator == (const_iterator const &another)
	{
		return (ptr == another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator != (const_iterator const &another)
	{
		return (ptr != another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator < (const_iterator const &another)
	{
		return (ptr < another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator > (const_iterator const &another)
	{
		return (ptr > another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator <= (const_iterator const &another)
	{
		return (ptr <= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	bool	ft::const_iterator<T, Pointer, Reference>::operator >= (const_iterator const &another)
	{
		return (ptr >= another.ptr);
	}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator += (int const &value)
	{
		ptr += value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator -= (int const &value)
	{
		ptr -= value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator + (int const &value)
	{
		ptr += value;
		return (*this);
	}

	template <class T, class Pointer, class Reference>
	ft::const_iterator<T>	ft::const_iterator<T, Pointer, Reference>::operator - (int const &value)
	{
		ptr -= value;
		return (*this);
	}
}

#endif
