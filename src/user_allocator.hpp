#pragma once

#include <limits>
#include <memory>

template <typename T>
class UserAllocator
{
    public:
	using value_type = T;

	UserAllocator() noexcept = default;

	template <typename U>
	UserAllocator(const UserAllocator<U>&) noexcept
	{
	}

	~UserAllocator() noexcept = default;

	UserAllocator& operator=(const UserAllocator&) noexcept = default;
	bool operator==(const UserAllocator&) const noexcept { return true; }
	bool operator!=(const UserAllocator&) const noexcept { return false; }

	value_type* allocate(std::size_t n)
	{
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(value_type)) {
			throw std::bad_alloc();
		}

		return static_cast<value_type*>(::operator new(n * sizeof(value_type)));
	}

	void deallocate(value_type* p, std::size_t n) noexcept { ::operator delete(p, n); }
};