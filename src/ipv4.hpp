#pragma once

#include <array>
#include <sstream>
#include <string>

class ipv4_addr;
unsigned int ipv4_to_uint(const ipv4_addr& ip);

class ipv4_addr
{
    public:
	ipv4_addr(const std::string& str)
	{
		std::stringstream ss(str);
		std::string segment;
		std::array<unsigned int, 4> tmp_octets;
		int octet;

		for (size_t i = 0; i < m_octets.size(); ++i) {
			if (!std::getline(ss, segment, '.')) {
				throw std::runtime_error("Invalid IPv4 address format: " + str);
			}

			try {
				octet = std::stoi(segment);
				if (octet < 0 || octet > 255) {
					throw std::runtime_error("Octet out of range: " + segment);
				}

				tmp_octets[i] = octet;
			} catch (const std::exception& e) {
				throw std::runtime_error("octet conversion error: " + segment);
			}
		}

		if (ss.peek() != EOF) {
			throw std::runtime_error("Invalid IPv4 address format: " + str);
		}

		m_ip_str = str;
		m_octets = std::move(tmp_octets);
	}

	~ipv4_addr() = default;

	const unsigned int& operator[](size_t index) const { return m_octets[index]; }

	bool operator>(const ipv4_addr& rhs) const { return ipv4_to_uint(*this) > ipv4_to_uint(rhs); }

	bool operator<(const ipv4_addr& rhs) const { return ipv4_to_uint(*this) < ipv4_to_uint(rhs); }

	friend std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj);

	std::string to_string() const { return m_ip_str; }

    private:
	std::string m_ip_str = "";
	std::array<unsigned int, 4> m_octets = {};
};

std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj)
{
	os << obj.m_ip_str;
	return os;
}

unsigned int ipv4_to_uint(const ipv4_addr& ip)
{
	const unsigned int shift = 8;
	unsigned int ip_val = 0;

	for (size_t i = 0; i < 4; ++i) {
		ip_val = (ip_val << shift) | ip[i];
	}

	return ip_val;
}