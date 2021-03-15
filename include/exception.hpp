#pragma once

namespace ft
{
	class exception
	{
	public:
		exception() throw() {};
		exception(exception const& other) throw() { };
		virtual ~exception() {};

		virtual char const*	what() throw() = 0;

		virtual exception&	operator=(exception const&) = 0;
	};
}
