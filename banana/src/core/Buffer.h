//////////////////////////////////////////////////////////////////////////
///
///
///
/// Author      : kerryhe
///
///
///
///
///
///
/// Copyright © : All rights reserved
///
//////////////////////////////////////////////////////////////////////////


#ifndef _h_buffer_h_
#define _h_buffer_h_

#include <vector>

class CBuffer
{
public:
	explicit CBuffer(int capacity);
	CBuffer(const CBuffer&) = delete;
	CBuffer& operator=(const CBuffer&) = delete;

public:
	bool IsEmpty(void) const;
	bool IsFull(void) const;
	size_t UsedCapacity(void) const;
	size_t RemainedCapacity(void) const;
	size_t Capacity(void) const;

public:
	bool Peek(char* data, size_t len);
	bool Read(char* data, size_t len);
	bool Write(const char* data, size_t len);
private:
	bool Read(size_t& readPos, bool& flipped, char* data, size_t len);

private:
	char* begin()
	{
		return &*_buf.begin();
	}

private:
	size_t _readPos;
	size_t _writePos;
	bool _flipped;
	std::vector<char> _buf;
};


#endif // !_h_buffer_h_

