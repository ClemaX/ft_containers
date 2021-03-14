#pragma once

#include <memory.hpp>

namespace ft
{
	template<typename T, typename A = allocator<T> >
	class list
	{
	private:

	public:
		list();
		~list();
	};

	template<typename T, typename A>
	list<T, A>::list()
	{
	}

	template<typename T, typename A>
	list<T, A>::~list()
	{
	}
}
