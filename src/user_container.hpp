#pragma once

#include <algorithm>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class UserContainer
{
    public:
	using value_type = T;
	using allocator_type = Allocator;
	using allocator_traits = std::allocator_traits<allocator_type>;

    private:
	value_type* m_data;
	size_t m_size;
	size_t m_capacity;
	allocator_type m_allocator;

    public:
	explicit UserContainer(const allocator_type& alloc = allocator_type())
	    : m_data{nullptr}, m_size{0}, m_capacity{0}, m_allocator{alloc}
	{
	}

	UserContainer(const UserContainer& rhs) : UserContainer(rhs.m_allocator)
	{
		if (rhs.m_size > 0) {
			reserve(rhs.m_size);
			for (size_t i = 0; i < m_size; ++i) {
				allocator_traits::construct(m_allocator, m_data + i, rhs.m_data[i]);
			}
			m_size = rhs.m_size;
		}
	}

	~UserContainer()
	{
		clear();
		if (m_data != nullptr) {
			allocator_traits::deallocate(m_allocator, m_data, m_capacity);
		}
	}

	UserContainer& operator=(const UserContainer& rhs)
	{
		if (this == &rhs) {
			return *this;
		}

		clear();
		allocator_traits::deallocate(m_allocator, m_data, m_capacity);

		m_allocator = rhs.m_allocator;
		m_size = rhs.m_size;

		reserve(rhs.m_size);
		for (size_t i = 0; i < rhs.m_size; ++i) {
			allocator_traits::construct(m_allocator, m_data + i, rhs.m_data[i]);
		}
	}

	value_type& operator[](size_t pos) const { return m_data[pos]; }

	value_type& front() const
	{
		if (empty()) {
			throw std::out_of_range("UserContainer::front: container is empty");
		}
		return m_data[0];
	}

	value_type& back() const
	{
		if (empty()) {
			throw std::out_of_range("UserContainer::back: container is empty");
		}
		return m_data[m_size - 1];
	}

	bool empty() const noexcept { return m_size == 0; }
	size_t size() const noexcept { return m_size; }
	size_t capacity() const noexcept { return m_capacity; }

	void push_back(const value_type& value)
	{
		if (m_size == m_capacity) {
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);
		}

		allocator_traits::construct(m_allocator, m_data + m_size, value);
		++m_size;
	}

	void pop_back()
	{
		if (empty()) {
			throw std::out_of_range("UserContainer::pop_back: container is empty");
		}

		--m_size;
		allocator_traits::destroy(m_allocator, m_data + m_size);
	}

	void clear() noexcept
	{
		for (size_t i = 0; i < m_size; ++i) {
			allocator_traits::destroy(m_allocator, m_data + i);
		}
		m_size = 0;
	}
	void reserve(size_t new_capacity)
	{
		if (new_capacity <= m_capacity) {
			return;
		}

		value_type* new_data = allocator_traits::allocate(m_allocator, new_capacity);
		for (size_t i = 0; i < m_size; ++i) {
			allocator_traits::construct(m_allocator, new_data + i, std::move(m_data[i]));
			allocator_traits::destroy(m_allocator, m_data + i);
		}

		if (m_data != nullptr) {
			allocator_traits::deallocate(m_allocator, m_data, m_capacity);
		}

		m_data = new_data;
		m_capacity = new_capacity;
	}

	// void resize(size_t count)
	// {
	// 	if (count < m_size) {
	// 		for (size_t i = count; i < m_size; ++i) {
	// 			allocator_traits::deallocate(m_allocator, m_data + i, sizeof(value_type));
	// 		}
	// 	} else if (count > m_size) {
	// 		for (size_t i = m_size; i < count; ++i) {
	// 			allocator_traits::allocate(m_allocator, m_data + i, sizeof(value_type));
	// 		}
	// 	}

	// 	m_capacity = m_size = count;
	// }
};