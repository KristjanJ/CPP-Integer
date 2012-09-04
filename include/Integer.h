#pragma once

#include <string>

class Integer
{
public:
	Integer();
	Integer(const std::string& integer);
	Integer(const Integer& other);
	~Integer();

	Integer& operator = (const Integer& other);
	Integer& operator += (const Integer& other);
	Integer& operator *= (const Integer& other);
	Integer operator + (const Integer& other) const;
	Integer operator * (const Integer& other) const;

	std::string toString() const;

private:
	unsigned int m_digitCount;
	unsigned char* m_digits;
	static const unsigned char s_radix;

	void allocateDigits(const unsigned int count);
	void increaseDigit(const unsigned int index, const unsigned char value);
};

