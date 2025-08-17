#pragma once

#include <cstdlib>
#include <limits>
#include <list>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

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

	[[nodiscard]] value_type* allocate(std::size_t n)
	{
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(value_type)) {
			throw std::bad_alloc();
		}

		return static_cast<value_type*>(::operator new(n * sizeof(value_type)));
	}

	void deallocate(value_type* p, std::size_t n) noexcept { ::operator delete(p, n); }
};

template <typename T>
class PoolAllocator
{
    public:
	using value_type = T;
	using pointer = T*;

    private:
	struct FreeList {
		FreeList* next;
	};

	std::vector<uint8_t*> m_memory_blocks{};
	FreeList* m_freelist = nullptr;

	static constexpr size_t BlockSize = 1024;

    public:
	PoolAllocator() noexcept = default;

	PoolAllocator(const PoolAllocator& other) = delete;

	PoolAllocator(PoolAllocator&& other) noexcept
	    : m_memory_blocks(std::exchange(other.m_memory_blocks, {})),
	      m_freelist(std::exchange(other.m_freelist, nullptr))
	{
	}

	PoolAllocator& operator=(const PoolAllocator&) noexcept = delete;
	PoolAllocator& operator=(PoolAllocator&& other) noexcept
	{
		if (this != &other) {
			for (char* block : m_memory_blocks) {
				::operator delete(static_cast<void*>(block));
			}
			m_memory_blocks.clear();

			m_memory_blocks = std::exchange(other.m_memory_blocks, {});
			m_freelist = std::exchange(other.m_freelist, nullptr);
		}
		return *this;
	}

	bool operator==(const PoolAllocator&) const noexcept { return true; }
	bool operator!=(const PoolAllocator&) const noexcept { return false; }

	~PoolAllocator() noexcept
	{
		for (auto block : m_memory_blocks) {
			::operator delete(static_cast<void*>(block));
		}

		::operator delete(static_cast<void*>(m_freelist));
	}

	[[nodiscard]] pointer allocate(size_t n)
	{
		if (n != 1) {
			return static_cast<pointer>(::operator new(n * sizeof(value_type)));
		}

		if (m_freelist) {
			pointer result = reinterpret_cast<pointer>(m_freelist);
			m_freelist = m_freelist->next;
			return result;
		}

		allocate_new_block();
		return allocate(n);
	}

	void deallocate(pointer p, size_t n) noexcept
	{
		if (n != 1 || p == nullptr) {
			::operator delete(static_cast<void*>(p));
			return;
		}

		FreeList* node = reinterpret_cast<FreeList*>(p);
		node->next = m_freelist;
		m_freelist = node;
	}

    private:
	void allocate_new_block()
	{
		constexpr size_t aligned_size = std::max(sizeof(T), alignof(std::max_align_t));
		constexpr size_t elements_count = BlockSize / aligned_size;

		uint8_t* new_block = static_cast<uint8_t*>(::operator new(BlockSize));
		m_memory_blocks.emplace_back(new_block);

		m_freelist = reinterpret_cast<FreeList*>(new_block);
		FreeList* current = m_freelist;

		for (size_t i = 0; i < elements_count - 1; ++i) {
			uint8_t* next = new_block + (i + 1) * aligned_size;
			current->next = reinterpret_cast<FreeList*>(next);
			current = current->next;
		}

		current->next = nullptr;
	}
};