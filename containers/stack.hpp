#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack : protected ft::vector<T>
	{
	public:
		stack();
		~stack();
		stack(stack const &another);
		stack<T>	&operator = (stack const &another);
		T		&top(void);
		T const	&top(void) const;
		bool	empty(void) const;
		size_t	size(void) const;
		void	push(T const &value);
		void	pop(void);
		bool	operator == (stack const &another);
		bool	operator != (stack const &another);
		bool	operator < (stack &another);
		bool	operator <= (stack &another);
		bool	operator > (stack &another);
		bool	operator >= (stack &another);
	protected:
		Container container;
	};

	template <class T, class Container>
	ft::stack<T, Container>::stack() {}

	template <class T, class Container>
	ft::stack<T, Container>::~stack() {}

	template <class T, class Container>
	ft::stack<T, Container>::stack(stack const &another)
	{
		container = Container(another.container);
	}

	template <class T, class Container>
	ft::stack<T>	&ft::stack<T, Container>::operator = (stack const &another)
	{
		container = Container(another.container);
		return (*this);
	}

	template <class T, class Container>
	T		&ft::stack<T, Container>::top()
	{
		return (container.back());
	}

	template <class T, class Container>
	T const	&ft::stack<T, Container>::top() const
	{
		return (container.back());
	}

	template <class T, class Container>
	bool	ft::stack<T, Container>::empty() const
	{
		return (container.empty());
	}

	template <class T, class Container>
	size_t	ft::stack<T, Container>::size() const
	{
		return (container.size());
	}

	template <class T, class Container>
	void	ft::stack<T, Container>::push(T const &value)
	{
		container.push_back(value);
	}

	template <class T, class Container>
	void	ft::stack<T, Container>::pop()
	{
		if (container.size() == 0)
			return ;
		container.resize(size() - 1, T());
	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator == (stack const &another)
	{
		return (container == another.container);
	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator != (stack const &another)
	{
		return (container != another.container);

	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator < (stack &another)
	{
		return (container < another.container);
	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator <= (stack &another)
	{
		return (container <= another.container);
	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator > (stack &another)
	{
		return (container > another.container);
	}

	template <class T, class Allocator>
	bool	ft::stack<T, Allocator>::operator >= (stack &another)
	{
		return (container >= another.container);
	}
}

#endif
