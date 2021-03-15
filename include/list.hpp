#pragma once

#include <memory.hpp>
#include <iterator.hpp>

namespace ft
{
	namespace detail
	{
		struct	_list_node_base
		{
			_list_node_base*	next;
			_list_node_base*	prev;

			static void swap(_list_node_base& x, _list_node_base& y) throw();
			void		transfer(_list_node_base* const first,
				_list_node_base* const last) throw();
			void		reverse() throw();
			void		unhook() throw();
		};

		struct	_list_node_header	:	public _list_node_base
		{
			_list_node_header() throw()
			{ next = prev = this; }

		private:
			_list_node_base*	base()
			{ return this; }
		};
	}

	template<typename T>
	struct _list_node	:	public detail::_list_node_base
	{
		T	data;
		T*			valptr() { return static_cast<T*>&data; };
		T const*	valptr() const { return static_cast<T const*>&data; };
	};

	/**
	 * @brief A list::iterator.
	 *
	 * @tparam T	The list's data type.
	 */
	template<typename T>
	struct	_list_iterator
	{
		typedef	_list_iterator<T>	_self;
		typedef	_list_node<T>		_node;

		typedef	ptrdiff_t					difference_type;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef	T							value_type;
		typedef	T*							pointer;
		typedef	T&							reference;

		_list_iterator() throw()
			: node() { }

		explicit _list_iterator(detail::_list_node_base* x) throw()
			: node(x) { }

		_self _const_cast() const throw()
		{ return *this; }

		reference	operator*() const throw()
		{ return *static_cast<node*>(node)->valptr(); }

		pointer		operator->() const throw()
		{ return static_cast<node*>(node)->valptr(); }

		_self&		operator++() throw()
		{
			node = node->next;
			return *this;
		}

		_self		operator++(int) throw()
		{
			_self	previous = *this;
			node = node->next;
			return previous;
		}

		_self&		operator--() throw()
		{
			node = node->prev;
			return *this;
		}

		_self&		operator--(int) throw()
		{
			_self	previous = *this;
			node = node->prev;
			return previous;
		}

		friend bool	operator==(const _self& x, const _self& y) throw()
		{ return x.node == y.node; }

		friend bool	operator!=(const _self& x, const _self& y) throw()
		{ return x.node != y.node; }

		detail::_list_node_base*	node;
	};

	/**
	 * @brief A list::const_iterator
	 *
	 * @tparam T	The list's data-type.
	 */
	template<typename T>
	struct	_list_const_iterator
	{
		typedef _list_const_iterator<T>	_self;
		typedef const _list_node<T>		_node;
		typedef _list_iterator			iterator;

		typedef	ptrdiff_t					difference_type;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef	T							value_type;
		typedef	T*							pointer;
		typedef	T&							reference;

		_list_const_iterator() throw()
		: _node() { }

		explicit _list_iterator(detail::_list_node_base const* x) throw()
			: _node(x) { }

		_list_const_iterator(iterator const& x) throw()
			: _node(x._node) { }

		_self _const_cast() const throw()
		{ return iterator(const_cast<detail::_list_node_base*>(this)); }

		reference	operator*() const throw()
		{ return *static_cast<node*>(node)->valptr(); }

		pointer		operator->() const throw()
		{ return static_cast<node*>(node)->valptr(); }

		_self&		operator++() throw()
		{
			node = node->next;
			return *this;
		}

		_self		operator++(int) throw()
		{
			_self	previous = *this;
			node = node->next;
			return previous;
		}

		_self&		operator--() throw()
		{
			node = node->prev;
			return *this;
		}

		_self&		operator--(int) throw()
		{
			_self	previous = *this;
			node = node->prev;
			return previous;
		}

		friend bool	operator==(const _self& x, const _self& y) throw()
		{ return x.node == y.node; }

		friend bool	operator!=(const _self& x, const _self& y) throw()
		{ return x.node != y.node; }

		detail::_list_node_base*	node;
	};


	template<typename T, typename A>
	class _list_base
	{
	protected:
		// TODO: Allocator traits typedef
		//typedef
		static size_t	distance(const detail::_list_node_base* first,
			const detail::_list_node_base* last)
		{
			size_t n = 0;
			while (first != last)
			{
				first = first->next;
				++n;
			}
			return n;
		}
	};

	template<typename T, typename A = allocator<T> >
	class	list : protected _list_base<T, A>
	{
	private:
		typedef _list_base<T, A>	_base;
		// TODO: Allocator traits typedef

	public:
		typedef T	value_type;
		// TODO: Pointer and reference types
		typedef _list_iterator<T>		iterator;
		typedef _list_const_iterator<T>	const_iterator;
		// TODO: Reverse iterator types
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef A						allocator_type;

		list();
		~list();
	};
}
