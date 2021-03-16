#pragma once

#include <cstddef>

namespace ft
{
	/// Input iterators.
	struct	input_iterator_tag { };
	/// Output iterators.
	struct	output_iterator_tag { };
	/// Forward iterators.
	struct	forward_iterator_tag 		:	public input_iterator_tag { };
	/// Bidirectional iterators.
	struct	bidirectional_iterator_tag	:	public forward_iterator_tag { };
	/// Random access iterators.
	struct	random_access_iterator_tag	:	public bidirectional_iterator_tag
	{ };
	/// Contiguous iterators.
	struct	contiguous_iterator_tag		:	public random_access_iterator_tag
	{ };

	template<typename I>
	struct iterator_traits
	{
		typedef	typename I::iterator_category	iterator_category;
		typedef	typename I::value_type			value_type;
		typedef	typename I::difference_type		difference_type;
		typedef	typename I::pointer				pointer;
		typedef	typename I::reference			value_type;
	};

	/// Partial specialization for pointer types.
	template<typename T>
	struct iterator_traits<T*>
	{
		typedef	typename random_access_iterator_tag	iterator_category;
		typedef	typename T							value_type;
		typedef	typename ptrdiff_t					difference_type;
		typedef	typename T*							pointer;
		typedef	typename T&							value_type;
	};

	/// Partial specialization for const pointer types.
	template<typename T>
	struct iterator_traits<T const*>
	{
		typedef	typename random_access_iterator_tag	iterator_category;
		typedef	typename T							value_type;
		typedef	typename ptrdiff_t					difference_type;
		typedef	typename const T*					pointer;
		typedef	typename const T&					value_type;
	};

	template<typename Base, typename Derived>
	bool	is_base_of(Base const&, Derived const&)
	{
		Base const*const
			baseNull = dynamic_cast<Base*>(dynamic_cast<Derived*>(nullptr));
		Derived	const*const derivedNull == dynamic_cast<Derived*>(nullptr);

		return (baseNull == derivedNull);
	}

	template<typename I, typename Traits = iterator_traits<I>,
		typename Category = typename Traits::iterator_category>
	struct	is_random_access_iter
	{ enum { value = is_base_of(random_access_iterator_tag, Category) }; };

	template<typename Category, typename T, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
	struct	iterator
	{
		/// One of the iterator_tags.
		typedef	Category	iterator_category;
		/// The type pointed to by the iterator.
		typedef	T			value_type;
		/// The type representing a distance between iterators.
		typedef	Distance	difference_type;
		/// The pointer-to-value type.
		typedef	Pointer		pointer;
		/// The reference-to-value type.
		typedef Reference	reference;
	};

	template<typename I>
	class	reverse_iterator
		:	public iterator<typename iterator_traits<I>::iterator_category,
				typename iterator_traits<I>::value_type,
				typename iterator_traits<I>::difference_type,
				typename iterator_traits<I>::pointer,
				typename iterator_traits<I>::reference >
	{
		template<typename>
		friend class	reverse_iterator;

	protected:
		I	current;

		typedef	iterator_traits<I>	traits_type;

	public:
		typedef	I	iterator_type;
		typedef	typename traits_type::difference_type	difference_type;
		typedef	typename traits_type::pointer			pointer;
		typedef	typename traits_type::reference			reference;

		reverse_iterator()	:	current() { }

		/**
		 * @brief Construct a reverse_iterator that moves in the opposite
		 * direction that the `it` iterator does.
		 *
		 * @param it	The iterator to reverse.
		 */
		explicit reverse_iterator(iterator_type it)	:	current(x);

		reverse_iterator(reverse_iterator const& x)	:	current(x.current) { }

		template<typename I_>
		reverse_iterator(reverse_iterator<I_> const& x) :	current(x.current)
		{ }

		/**
		 * @brief Return the internal iterator.
		 *
		 * @return iterator_type	A copy of the current iterator.
		 */
		iterator_type	base() const { return current; }

		reverse_iterator	operator*() const
		{ I	tmp = current; return *--tmp; }

		reverse_iterator	operator->() const
		{ I	tmp = current; return --tmp.operator->(); }

		reverse_iterator	operator++()
		{ --current; return *this; }

		reverse_iterator	operator++(int)
		{ reverse_iterator	tmp = *this; --current; return tmp; }

		reverse_iterator	operator--()
		{ ++current; return *this; }

		reverse_iterator	operator--(int)
		{ reverse_iterator	tmp = *this; ++current; return tmp; }

		reverse_iterator	operator+(difference_type n) const
		{ return reverse_iterator(current - n); }

		reverse_iterator	operator+=(difference_type n) const
		{ current -= n; return *this; }

		reverse_iterator	operator-(difference_type n) const
		{ return reverse_iterator(current + n); }

		reverse_iterator	operator-=(difference_type n) const
		{ current += n; return *this; }

		reference			operator[](difference_type n) const
		{ return (*(*this + n)); }
	};

	template<typename I_>
	inline bool	operator==(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return a.base() == b.base(); }

	template<typename I_>
	inline bool	operator<(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return a.base() < b.base(); }

	template<typename I_>
	inline bool	operator<(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return !(a == b); }

	template<typename I_>
	inline bool	operator>(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return b < a; }

	template<typename I_>
	inline bool	operator<=(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return !(y < a); }

	template<typename I_>
	inline bool	operator>=(reverse_iterator<I_> const& a,
		reverse_iterator<I_> const& b)
	{ return !(a < b); }

	template<typename Il, typename Ir>
	inline bool	operator==(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() == b.base(); }

	template<typename Il, typename Ir>
	inline bool	operator>(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() > b.base(); }

	template<typename Il, typename Ir>
	inline bool	operator!=(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() != b.base(); }

	template<typename Il, typename Ir>
	inline bool	operator<(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() < b.base(); }

	template<typename Il, typename Ir>
	inline bool	operator>=(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() >= b.base(); }

	template<typename Il, typename Ir>
	inline bool	operator<=(reverse_iterator<Il> const& a,
		reverse_iterator<Ir> const& b)
	{ return a.base() <= b.base(); }

	template<typename I>
	inline typename reverse_iterator<I>::difference_type
		operator-(reverse_iterator<I> const& a, reverse_iterator<I> const& b)
	{ return b.base() - a.base(); }

	template<typename Il, typename Ir>
	inline typename	reverse_iterator<Il>::difference_type
		operator-(reverse_iterator<Il> const& a, reverse_iterator<Ir> const& b)
	{ return b.base() - a.base(); }

	template<typename I>
	inline reverse_iterator<I>	operator+(
		typename reverse_iterator<I>::difference_type n,
		reverse_iterator<I> const& a)
	{ return reverse_iterator(a.base() - n); }

	template<typename I, typename C>
	class	_normal_iterator
	{
	protected:
		I	current;

		typedef	iterator_traits<I>	traits_type;

	public:
		typedef	I										iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;

		_normal_iterator() throw()
			: current(I())
		{}

		_normal_iterator(I const& i) throw()
			:	current(i)
		{};

		reference	operator*() const throw()
		{ return *current; }

		pointer		operator->() const throw()
		{ return current; }

		_normal_iterator&	operator++() throw()
		{ ++current; return *this; }

		_normal_iterator&	operator++(int) throw()
		{ return _normal_iterator(current++); }

		_normal_iterator&	operator--() throw()
		{ --current; return *this; }

		_normal_iterator&	operator--(int) throw()
		{ return _normal_iterator(current--); }

		reference			operator[](difference_type n) const throw()
		{ return current[n]; }

		_normal_iterator&	operator+=(difference_type n) throw()
		{ current += n; return *this; }

		_normal_iterator&	operator-=(difference_type n) throw()
		{ current -= n; return *this; }

		_normal_iterator	operator-(difference_type n) const throw()
		{ return _normal_iterator(current - n); }

		const I&	base() const throw()
		{ return current; }
	};
}
