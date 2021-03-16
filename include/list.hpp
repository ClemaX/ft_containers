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

		friend bool	operator==(_self& const x, _self& const y) throw()
		{ return x.node == y.node; }

		friend bool	operator!=(_self& const x, _self& const y) throw()
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

		friend bool	operator==(_self const& x, _self const& y) throw()
		{ return x.node == y.node; }

		friend bool	operator!=(_self const& x, _self const& y) throw()
		{ return x.node != y.node; }

		detail::_list_node_base*	node;
	};

	template<typename T, typename A>
	class _list_base
	{
	protected:
		typedef	typename _alloc_traits<A>::template rebind<T>::other
			T_alloc_type;
		typedef	_alloc_traits<T_alloc_type>	T_alloc_traits;
		typedef	typename T_alloc_traits::template rebind<_list_node<T> >::other
			node_alloc_type;
		typedef	_alloc_traits<node_alloc_type> node_alloc_traits;

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

		struct	_list_impl	:	public _node_alloc_type
		{
			detail::_list_node_header	node;

			_list_impl()	:	_node_alloc_type() { }
			_list_impl(const _node_alloc_type& a)	:	_node_alloc_type(a) { }
		};

		_list_impl	impl;

		size_t	get_size() const { return 0; }
		size_t	node_count() const
		{ return distance(impl.node.next, &impl.node); }

		typename node_alloc_traits::pointer	get_node()
		{ return node_alloc_traits::allocate(impl, p, 1); }

		void	put_node(typename node_alloc_traits::pointer p) throw()
		{ node_alloc_traits::deallocate(impl, p, 1); }

	public:
		typedef	A&	allocator_type;

		node_alloc_type&		get_node_allocator() throw()
		{ return impl; }

		node_alloc_type const&	get_node_allocator() const throw()
		{ return impl; }

		void	clear() throw();

		void	init() throw()
		{ this->impl.node.init(); };

		_list_base() { }

		_list_base(node_alloc_type const& a) throw()	:	impl(a) { }

		~_list_base() throw()
		{ clear(); }
	};

	template<typename T, typename A = allocator<T> >
	class	list : protected _list_base<T, A>
	{
	private:
		typedef _list_base<T, A>					base;
		typedef	typename base::T_alloc_type			T_alloc_type;
		typedef	typename base::T_alloc_traits		T_alloc_traits;
		typedef	typename base::node_alloc_type		node_alloc_type;
		typedef	typename base::node_alloc_traits	node_alloc_traits;

	public:
		typedef T											value_type;
		typedef typename T_alloc_traits::pointer			pointer;
		typedef typename T_alloc_traits::const_pointer		const_pointer;
		typedef typename T_alloc_traits::reference			reference;
		typedef typename T_alloc_traits::const_reference	const_reference;

		typedef _list_iterator<T>		iterator;
		typedef _list_const_iterator<T>	const_iterator;

		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef A						allocator_type;

	protected:
		typedef _list_node<T>			node;

		using	base::impl;
		using	base::put_node;
		using	base::get_node;
		using	base::get_node_allocator;

		node*	create_node(value_type const& value)
		{
			node*	p = this->get_node();

			try
			{
				T_alloc_type	alloc(get_node_allocator());
				alloc.construct(p->valptr(), value);
			}
			catch(...)
			{
				put_node(p);
				throw;
			}
			return p;
		}

	public:
		list() { };

		explicit list(allocator_type const& a) throw()
			:	base(node_alloc_type(a)) { }

		explicit list(size_type n, value_type const& value = value_type(),
			allocator_type const& a = allocator_type())
			:	base(node_alloc_type(a))
			{ fill_initialize(n, value); }

		list(list const& x)
			:	base(node_alloc_traits::select_on_copy(x.get_node_allocator()))
		{ initialize_dispatch(x.begin(), x.end(), false); }

		template<typename I>
		list(I first, I last, allocator_type const& a = allocator_type())
			:	base(node_alloc_type(a))
		{
			typedef	typename is_integer<I>::type	Integral;
			initialize_dispatch(first, last, Integral());
		}

		list&	operator=(list const& x);

		void	assign(size_type n, value_type const& val)
		{ fill_assign(n, val); }

		template<typename I>
		void	assign(I first, I last)
		{
			typedef	typename is_integer<I>::type	Integral;
			assign_dispatch(first, last, Integral());
		}

		allocator_type	get_allocator() const throw()
		{ return allocator_type(base::get_node_allocator()); }

		iterator	begin() const throw()
		{ return iterator(this->impl.node.next); }

		iterator	end() const throw()
		{ return iterator(this->impl.node); }

		const_iterator	end() const throw()
		{ return const_iterator(this->impl.node); }

		reverse_iterator	rbegin() throw()
		{ return reverse_iterator(end()); }

		reverse_iterator	rend() throw()
		{ return reverse_iterator(begin()); }

		// TODO: const reverse iterator
		~list();
	};
}
