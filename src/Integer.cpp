#include "Integer.h"

#include <algorithm>

Integer::Integer()
{
	m_digitCount = 1;
	m_digits = new unsigned char[m_digitCount]();
}

Integer::Integer(const std::string& integer)
{
	const std::size_t integerLength = integer.length();
	const bool valid = (integerLength == 1 || integerLength > 1 && integer[0] != '0') && std::all_of(integer.cbegin(), integer.cend(), [] (const char element) -> bool { return element >= '0' && element <= '9'; });

	if (valid)
	{
		m_digitCount = integerLength;
		m_digits = new unsigned char[m_digitCount]();
		std::transform(integer.crbegin(), integer.crend(), m_digits, [] (const char element) -> unsigned char { return element - 48; });
	}
	else
	{
		m_digitCount = 1;
		m_digits = new unsigned char[m_digitCount];
	}
}

Integer::Integer(const Integer& other)
{
	m_digitCount = other.m_digitCount;
	m_digits = new unsigned char[m_digitCount]();
	std::copy(other.m_digits, other.m_digits + m_digitCount, m_digits);
}

Integer::~Integer()
{
	delete[] m_digits; m_digits = nullptr;
}

Integer& Integer::operator = (const Integer& other)
{
	if (this != &other)
	{
		delete[] m_digits; m_digits = nullptr;
		m_digitCount = other.m_digitCount;
		m_digits = new unsigned char[m_digitCount]();
		std::copy(other.m_digits, other.m_digits + m_digitCount, m_digits);
	}

	return *this;
}

Integer& Integer::operator += (const Integer& other)
{
	Integer integer(*this);

	for (unsigned int i = 0; i < other.m_digitCount; ++i)
	{
		integer.increaseDigit(i, other.m_digits[i]);
	}

	*this = integer;
	return *this;
}

Integer& Integer::operator *= (const Integer& other)
{
	Integer integer;

	for (unsigned int i = 0; i < m_digitCount; ++i)
	{
		for (unsigned int j = 0; j < other.m_digitCount; ++j)
		{
			const unsigned char product = m_digits[i] * other.m_digits[j];
			integer.increaseDigit(i + j, product);
		}
	}

	*this = integer;
	return *this;
}

Integer Integer::operator + (const Integer& other) const
{
	Integer integer(*this);

	for (unsigned int i = 0; i < other.m_digitCount; ++i)
	{
		integer.increaseDigit(i, other.m_digits[i]);
	}

	return integer;
}

Integer Integer::operator * (const Integer& other) const
{
	Integer integer;

	for (unsigned int i = 0; i < m_digitCount; ++i)
	{
		for (unsigned int j = 0; j < other.m_digitCount; ++j)
		{
			const unsigned char product = m_digits[i] * other.m_digits[j];
			integer.increaseDigit(i + j, product);
		}
	}

	return integer;
}

void Integer::allocateDigits(const unsigned int count)
{
	unsigned char* const digits = new unsigned char[m_digitCount + count]();
	std::copy(m_digits, m_digits + m_digitCount, digits);
	delete[] m_digits; m_digits = nullptr;
	m_digitCount += count;
	m_digits = digits;
}

void Integer::increaseDigit(const unsigned int index, const unsigned char value)
{
	unsigned int mutableIndex = index;
	unsigned char mutableValue = value;

	for ( ; mutableValue > 0; ++mutableIndex)
	{
		if (mutableIndex >= m_digitCount)
		{
			allocateDigits(mutableIndex - m_digitCount + 1);
		}

		const unsigned char sum = m_digits[mutableIndex] + mutableValue;
		m_digits[mutableIndex] = sum % s_radix;
		mutableValue = sum / s_radix;
	}
}

std::string Integer::toString() const
{
	std::string stringRepresentation(m_digitCount, '0');
	std::transform(m_digits, m_digits + m_digitCount, stringRepresentation.rbegin(), [] (const unsigned char element) -> char { return element + 48; });

	return stringRepresentation;
}

const unsigned char Integer::s_radix = 10;
