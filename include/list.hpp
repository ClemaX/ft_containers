#pragma once

#include <memory.hpp>

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

	template<typename T>
	struct	_list_iterator
	{
		typedef	_list_iterator<T>	_self;
		typedef	_list_node<T>		_node;

		typedef	ptrdiff_t	difference_type;
		// TODO: Bidirectional iterator tag typedef
		typedef	T			value_type;
		typedef	T*			pointer;
		typedef	T&			reference;

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

	template<typename T>
	struct	_list_const_iterator
	{
		typedef _list_const_iterator<T>	_self;
		typedef const _list_node<T>		_node;
		typedef _list_iterator			iterator;

		typedef	ptrdiff_t	difference_type;
		// TODO: Bidirectional iterator tag typedef
		typedef	T			value_type;
		typedef	T*			pointer;
		typedef	T&			reference;

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
	class	list
	{
	private:

	public:
		list();
		~list();
	};
}
