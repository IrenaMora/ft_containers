#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include "../iterators/iterator.hpp"
# include "../iterators/const_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../other/lexicographical_compare.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		vector();
		~vector();
		vector(vector const &another);
		vector	&operator = (vector const &another);
		void	assign(size_t count, const T &value);
		Allocator	get_allocator(void) const;
		T		at(size_t pos) const;
		T		&operator [] (int const &index);
		T		&front(void);
		T		&back(void);
		T		*data(void);
		const T	*data(void) const;
		iterator<T>	begin();
		iterator<T>	end();
		const_iterator<T>	cbegin() const;
		const_iterator<T>	cend() const;
		reverse_iterator<T>	rbegin();
		reverse_iterator<T>	rend();
		bool	empty(void) const;
		size_t	size(void) const;
		size_t	max_size(void) const;
		void	reserve(size_t new_cap);
		size_t	capacity(void) const;
		void	clear(void);
		iterator<T>	insert(iterator<T> pos, T const &value);
		void		insert(iterator<T> pos, size_t count, T const &value);
		template <class InputIt>
		void		insert(iterator<T> pos, InputIt first, InputIt last);
		iterator<T>	erase(iterator<T> pos);
		iterator<T>	erase(iterator<T> first, iterator<T> last);
		void	push_back(T const &value);
		void	pop_back(void);
		void	resize(size_t count, T value = T());
		void	swap(vector &other);
		bool	operator == (vector const &another);
		bool	operator != (vector const &another);
		bool	operator < (vector &another);
		bool	operator <= (vector &another);
		bool	operator > (vector &another);
		bool	operator >= (vector &another);
		typedef iterator<T>	iterator;
		typedef const_iterator<T>	const_iterator;
		typedef reverse_iterator<T>	reverse_iterator;
	protected:
		Allocator alloc;
		T		*arr;
		size_t	value_size;
		size_t	value_capacity;
	private:
		static bool	comp_less(T &a, T &b);
		static bool	comp_lesseql(T &a, T &b);
		static bool	comp_greater(T &a, T &b);
		static bool	comp_greatereql(T &a, T &b);
	};

	template < class T, class Allocator>
	ft::vector<T, Allocator>::vector() : arr(NULL), value_size(0), value_capacity(0) {}

	template <class T, class Allocator>
	ft::vector<T, Allocator>::~vector()
	{
		std::allocator<T> my_alloc;
		my_alloc.deallocate(arr, size());
	}

	template <class T, class Allocator>
	ft::vector<T, Allocator>::vector(vector const &another) : arr(NULL), value_size(0), value_capacity(0)
	{
		size_t				position = 0;
		value_size = another.size();
		value_capacity = another.capacity();
		alloc.deallocate(arr, size());
		arr = alloc.allocate(capacity());
		while (position < size())
		{
			new (arr + position) T(another.at(position));
			position++;
		}
	}

	template <class T, class Allocator>
	vector<T, Allocator> &ft::vector<T, Allocator>::operator = (vector const &another)
	{
		size_t				position = 0;
		value_size = another.size();
		value_capacity = another.capacity();
		alloc.deallocate(arr, size());
		arr = alloc.allocate(capacity());
		while (position < size())
		{
			new (arr + position) T(another.at(position));
			position++;
		}
		return (*this);
	}


	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::assign(size_t count, T const &value)
	{
		size_t	position = 0;

		if (count == 0)
			return ;
		if (capacity() == 0)
			reserve(1);
		while (capacity() < count)
			reserve(capacity() * 2);
		while (position < count)
		{
			arr[position] = value;
			position++;
		}
		position = count;
		while (size() >= position)
		{
			(arr + position)->~T();
			value_size--;
			position++;
		}
		if (size() < count)
			value_size = count;
	}

	template <class T, class Allocator>
	Allocator	ft::vector<T, Allocator>::get_allocator() const
	{
		return (alloc);
	}

	template <class T, class Allocator>
	T	ft::vector<T, Allocator>::at(size_t pos) const
	{
		if (pos >= size())
			throw (std::out_of_range(""));
		return (arr[pos]);
	}

	template <class T, class Allocator>
	T	&ft::vector<T, Allocator>::operator [] (int const &index)
	{
		return (arr[index]);
	}

	template <class T, class Allocator>
	T	&ft::vector<T, Allocator>::front()
	{
		return (arr[0]);
	}

	template <class T, class Allocator>
	T	&ft::vector<T, Allocator>::back()
	{
		return (arr[size() - 1]);
	}

	template <class T, class Allocator>
	T	*ft::vector<T, Allocator>::data()
	{
		return (arr);
	}

	template <class T, class Allocator>
	const T	*ft::vector<T, Allocator>::data() const
	{
		return (arr);
	}

	template <class T, class Allocator>
	iterator<T>	ft::vector<T, Allocator>::begin()
	{
		return (iterator(front()));
	}

	template <class T, class Allocator>
	iterator<T>	ft::vector<T, Allocator>::end()
	{
		if (size() == 0)
			return (begin());
		return (iterator(arr[size()]));
	}

	template <class T, class Allocator>
	const_iterator<T>	ft::vector<T, Allocator>::cbegin() const
	{
		return (const_iterator(arr[0]));
	}

	template <class T, class Allocator>
	const_iterator<T>	ft::vector<T, Allocator>::cend() const
	{
		if (size() == 0)
			return (cbegin());
		return (const_iterator(arr[size()]));
	}

	template <class T, class Allocator>
	reverse_iterator<T>	ft::vector<T, Allocator>::rbegin()
	{
		if (size() == 0)
			return (reverse_iterator(arr[0]));
		return (reverse_iterator(arr[size() - 1]));
	}

	template <class T, class Allocator>
	reverse_iterator<T>	ft::vector<T, Allocator>::rend()
	{
		if (size() == 0)
			return (reverse_iterator(arr[0]));
		return (reverse_iterator(arr[-1]));
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::empty() const
	{
		if (value_size == 0)
			return (true);
		return (false);
	}

	template <class T, class Allocator>
	size_t	ft::vector<T, Allocator>::size() const
	{
		return (value_size);
	}

	template <class T, class Allocator>
	size_t	ft::vector<T, Allocator>::max_size() const
	{
		return (alloc.max_size());
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::reserve(size_t new_cap)
	{
		size_t					position = 0;

		if (new_cap <= value_capacity)
			return ;
		T	*new_arr;
		new_arr = alloc.allocate(new_cap);
		while (position < size())
		{
			new (new_arr + position) T(arr[position]);
			position++;
		}
		position = 0;
		while (position < size())
		{
			arr[position].~T();
			position++;
		}
		alloc.deallocate(arr, size());
		arr = new_arr;
		value_capacity = new_cap;
	}

	template <class T, class Allocator>
	size_t	ft::vector<T, Allocator>::capacity() const
	{
		return (value_capacity);
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::clear()
	{
		int last_capacity = capacity();

		alloc.deallocate(arr, size());
		arr = alloc.allocate(last_capacity);
		value_size = 0;
	}

	template <class T, class Allocator>
	iterator<T>	ft::vector<T, Allocator>::insert(iterator pos, T const &value)
	{
		int	id = std::addressof(*pos) - std::addressof(*begin());
		int	elements = std::addressof(*end()) - std::addressof(*pos);

		if (capacity() == 0)
			reserve(1);
		if (size() + 1 >= capacity())
			reserve(capacity() * 2);
		std::memmove(arr + id + 1, arr + id, sizeof(*arr) * (elements));
		arr[id] = T(value);
		value_size++;
		return (iterator(arr[id]));
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::insert(iterator pos, size_t count, T const &value)
	{
		int	id_start = std::addressof(*pos) - std::addressof(*begin());
		int	elements = std::addressof(*end()) - std::addressof(*pos);

		if (capacity() == 0)
			reserve(count);
		while (size() + count >= capacity())
			reserve(capacity() * 2);
		std::memmove(arr + id_start + count, arr + id_start, sizeof(*arr) * (elements));
		size_t	position = 0;
		position = 0;
		while (position < count)
			arr[id_start + position++] = T(value);
		value_size += count;
	}

	template <class T, class Allocator>
	template <class InputIt>
	void	ft::vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
	{
		size_t	count = std::addressof(*last) - std::addressof(*first);
		int	id_start = std::addressof(*pos) - std::addressof(*begin());
		int	elements = std::addressof(*end()) - std::addressof(*pos);

		if (capacity() == 0)
			reserve(count);
		while (size() + count >= capacity())
			reserve(capacity() * 2);
		std::memmove(arr + id_start + count, arr + id_start, sizeof(*arr) * (elements));
		size_t	position = 0;
		while (position < count)
			arr[id_start + position++] = T(*first++);
		value_size += count;
	}

	template <class T, class Allocator>
	iterator<T>	ft::vector<T, Allocator>::erase(iterator pos)
	{
		int id = std::addressof(*pos) - std::addressof(*begin());
		int elements = std::addressof(*end()) - std::addressof(*pos);

		(arr + id)->~T();
		std::memmove(arr + id, arr + id + 1, sizeof(*arr) * (elements + 1));
		if (pos >= begin() && pos < end())
			value_size--;
		if (size() == 0)
			return (begin());
		return (pos);
	}

	template <class T, class Allocator>
	iterator<T>	ft::vector<T, Allocator>::erase(iterator first, iterator last)
	{
		size_t	position = 0;
		size_t	count = std::addressof(*last) - std::addressof(*first);
		int id = std::addressof(*first) - std::addressof(*begin());
		int elements = std::addressof(*end()) - std::addressof(*first);

		while (position < count)
			(arr + id + position++)->~T();
		std::memmove(arr + id, arr + id + count, sizeof(*arr) * (elements + count));
		value_size -= count;
		return (first);
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::push_back(T const &value)
	{
		if (capacity() == 0)
			reserve(1);
		else if (size() >= capacity())
			reserve(capacity() * 2);
		arr[size()] = T(value);
		value_size++;
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::pop_back()
	{
		erase(end() - 1);
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::resize(size_t count, T value)
	{
		size_t	lst_size = size();
		if (size() < count)
		{
			reserve(count);
			while (lst_size < count)
			{
				new (arr + lst_size) T(value);
				lst_size++;
			}
		}
		else if (size() > count)
		{
			while (lst_size > count)
				lst_size--;
		}
		value_size = count;
	}

	template <class T, class Allocator>
	void	ft::vector<T, Allocator>::swap(vector &other)
	{
		alloc.deallocate(arr, size());
		arr = other.data();
		value_size = other.size();
		value_capacity = other.capacity();
		other.arr = NULL;
		other.value_size = 0;
		other.value_capacity = 0;
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator == (vector const &another)
	{
		size_t	position = 0;

		if (size() != another.size())
			return (false);
		while (position < size())
		{
			if (at(position) != another.at(position))
				return (false);
			position++;
		}
		return (true);
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator != (vector const &another)
	{
		return (!(*this == another));
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::comp_less(T &a, T &b)
	{
		return (a < b);
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::comp_lesseql(T &a, T &b)
	{
		return (a <= b);
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::comp_greater(T &a, T &b)
	{
		return (a > b);
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::comp_greatereql(T &a, T &b)
	{
		return (a >= b);
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator < (vector &another)
	{
		return (ft::lexicographical_compare(begin(), end(),
										another.begin(), another.end(), this->comp_less));
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator <= (vector &another)
	{
		return (ft::lexicographical_compare(begin(), end(),
											another.begin(), another.end(), this->comp_lesseql));
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator > (vector &another)
	{
		return (ft::lexicographical_compare(begin(), end(),
											another.begin(), another.end(), this->comp_greater));
	}

	template <class T, class Allocator>
	bool	ft::vector<T, Allocator>::operator >= (vector &another)
	{
		return (ft::lexicographical_compare(begin(), end(),
											another.begin(), another.end(), this->comp_greatereql));
	}

	template <class T, class Allocator>
	void	swap(ft::vector<T, Allocator> &lhs, ft::map<T, Allocator> &rhs)
	{
		ft::vector<T, Allocator> lhs_tmp = lhs;
		lhs = std::move(rhs);
		rhs = std::move(lhs);
	}
}

#endif
