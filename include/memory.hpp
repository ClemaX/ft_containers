#pragma once

namespace ft
{
	template <typename T>
	class allocator
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

		allocator();
		~allocator();

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
