#pragma once

#include <cstddef>

#include <exception.hpp>

namespace ft
{
	class BadArrayNewLengthException	:	public exception
	{ char const*	what() throw() { return "Array size exceeds max size!"; } };

	class BadAllocationException		:	public exception
	{ char const*	what() throw() { return "Allocation failed!"; } };

	template<typename T>
	class new_allocator
	{
	public:
		typedef std::size_t		size_type;
		typedef	std::ptrdiff_t	difference_type;
		typedef T*				pointer;
		typedef T const*		const_pointer;
		typedef T&				reference;
		typedef	T const&		const_reference;
		typedef T				value_type;

		template<typename O>
		struct rebind
		{ typedef new_allocator<O> other; };

		new_allocator() throw() { }

		new_allocator(new_allocator const&) { }

		template<typename T>
		new_allocator(new_allocator<T> const&) { }

		~new_allocator() { }

		pointer			address(reference x) const throw()
		{ return &x; }

		const_pointer	address(const_reference x) const throw()
		{ return &x; }

		T*				allocate(size_type n,
			const void* = static_cast<const void*>(0))
		{
			if (n <= max_size())
			{
				if (n > size_type(-1) / sizeof(T))
					throw BadArrayNewLengthException();
				throw BadAllocationException();
			}
		}

		void			deallocate(T* p, size_type)
		{ ::operator delete(p); }

		size_type		max_size() const throw()
		{
#if __PTRDIFF_MAX__ < __SIZE_MAX__
			return std::size_t(__PTRDIFF_MAX__) / sizeof(T);
#else
			return std::size_t(-1) / sizeof(T);
#endif
		}

		void			construct(pointer p, T const& value)
		{ ::new(static_cast<void*>p) T(value); }

		void			destroy(pointer p)
		{ p->~T(); }

		template<typename U>
		friend bool	operator==(const new_allocator&, const new_allocator<U>&)
		{ return true; };

		template<typename U>
		friend bool	operator!=(const new_allocator&, const new_allocator<U>&)
		{ return false; };
	};

	/**
	* Destroy a range of objects using the supplied allocator.
	*/
	template<typename It, typename A>
	void destroy(It first, It last, A& alloc)
	{ for (; first != last; ++first) alloc.destroy(&*first); }

	template<typename It, typename AT>
	inline void destroy(It first, It last, allocator<AT>&)
	{ destroy(first, last); }


	template <>
	class allocator<void>
	{
	public:
		typedef void			value_type;
		typedef std::size_t		size_type;
		typedef	std::ptrdiff_t	difference_type;
		typedef void*			pointer;
		typedef void const*		const_pointer;

		template <typename O>
		struct rebind { typedef allocator<O> other; };
	};

	template <typename T>
	class allocator	:	public new_allocator<T>
	{
	public:
		typedef T				value_type;
		typedef std::size_t		size_type;
		typedef	std::ptrdiff_t	difference_type;
		typedef T*				pointer;
		typedef T const*		const_pointer;
		typedef T&				reference;
		typedef	T const&		const_reference;

		template <typename O>
		struct rebind { typedef allocator<O> other; };

		allocator() throw() { }

		allocator(allocator const& other) throw()
			:	new_allocator<T>(other) { }

		template <typename O>
		allocator(allocator<O> const&) throw() { }

		~allocator() throw() { }

		friend bool operator==(allocator const&, allocator const&) const throw()
		{ return true; }

		friend bool operator==(allocator const&, allocator const&) const throw()
		{ return false; }

		template <typename Ta, typename Tb>
		inline bool operator==(allocator<Ta> const&, allocator<Tb> const&)
			const throw()
		{ return true; }

		template <typename Ta, typename Tb>
		inline bool operator!=(allocator<Ta> const&, allocator<Tb> const&)
			const throw()
		{ return false; }

		template<typename T>
		class allocator<const T>
		{
		public:
			typedef T	value_type;
			template<typename U>
			allocator(allocator<U> const&) { }
		}

		// TODO: Other template constructors

		/**
		 * @brief Returns the address of a given reference.
		 *
		 * @param x	Reference to object.
		 * @return pointer	A pointer to the object.
		 */
		pointer			address(reference x) const;

		/**
		 * @brief Returns the address of a given reference.
		 *
		 * @param x	Reference to object.
		 * @return pointer	A pointer to the object.
		 */
		const_pointer	address(const_reference x) const;

		/**
		 * @brief Allocate a block of storage
		 *
		 * Attempts to allocate a block of storage with a size large enough to
		 * contain `n` elements of member type value_type, but they are not
		 * constructed.
		 *
		 * @param n		Number of elements to be allocated.
		 * @param hint	Either 0 or a value previously obtained by another call
		 * to allocate and not yet freed with deallocate. When it is not 0, this
		 * value may be used to improve performance by allocating a nearby
		 * block.
		 * @return pointer	A pointer to the initial element in the block of
		 * storage
		 */
		pointer	allocate(size_type n, allocator<void>::const_pointer hint=0);

		/**
		 * @brief Release block of storage.
		 *
		 * @param p	Pointer to a block of storage previously allocated with
		 * `allocator::allocate`.
		 * @param n	Number of elements allocated on the call to
		 * `allocator::allocate` for this block of storage.
		 */
		void	deallocate(pointer p, size_type n);

		size_type	max_size() const throw();

		/**
		 * @brief Construct an object on the location pointed by p.
		 *
		 * @param p	Pointer to a location with enough storage space to contain
		 * an element of type value_type.
		 * @param val
		 */
		void	construct(pointer p, const_reference val);
	};
}
