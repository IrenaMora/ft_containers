#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <iostream>

namespace ft
{
	template <class T>
	struct is_integral
	{
		is_integral();
		bool value;
		operator bool();
	};

	template <class T>
	is_integral<T>::is_integral()
	{
		if (typeid(T) == typeid(bool) || typeid(T) == typeid(char)
					|| typeid(T) == typeid(char16_t) || typeid(T) == typeid(char32_t )
					|| typeid(T) == typeid(wchar_t) || typeid(T) == typeid(short)
					|| typeid(T) == typeid(int) || typeid(T) == typeid(long)
					|| typeid(T) == typeid(long long))
			value = true;
		else
			value = false;
	}

	template <class T>
	is_integral<T>::operator bool()
	{
		if (typeid(T) == typeid(bool) || typeid(T) == typeid(char)
			|| typeid(T) == typeid(char16_t) || typeid(T) == typeid(char32_t )
			|| typeid(T) == typeid(wchar_t) || typeid(T) == typeid(short)
			|| typeid(T) == typeid(int) || typeid(T) == typeid(long)
			|| typeid(T) == typeid(long long))
			return (true);
		else
			return (false);
	}
}

#endif
