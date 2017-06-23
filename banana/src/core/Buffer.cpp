#include "Buffer.h"


//-----------------------------------------------------------------

CBuffer::CBuffer(int capacity)
    : _readPos(0)
    , _writePos(0)
    , _flipped(false)
    , _buf(capacity)
{

}

//-----------------------------------------------------------------

bool CBuffer::IsEmpty(void) const
{
    return !_flipped && _readPos == _writePos;
}
bool CBuffer::IsFull(void) const
{
    if (!_flipped)
        return _writePos - _readPos == Capacity();
    else
        return _writePos == _readPos;
}
size_t CBuffer::UsedCapacity(void) const
{
    if (!_flipped)
        return _writePos - _readPos;
    else
        return Capacity() - _readPos + _writePos;
}
size_t CBuffer::RemainedCapacity(void) const
{
    return Capacity() - UsedCapacity();
}
size_t CBuffer::Capacity(void) const
{
    return _buf.capacity();
}

//-----------------------------------------------------------------

bool CBuffer::Peek(char* data, size_t len)
{
    if (data == nullptr)
        return false;
    if (len <= 0)
        return false;
	if (len > UsedCapacity())
		return false;

	size_t readPos = _readPos;
	bool flipped = _flipped;

    return Read(readPos, flipped, data, len);
}
bool CBuffer::Read(char* data, size_t len)
{
	if (data == nullptr)
		return false;
	if (len <= 0)
		return false;
	if (len > UsedCapacity())
		return false;

	return Read(_readPos, _flipped, data, len);
}
bool CBuffer::Read(size_t& readPos, bool& flipped, char* data, size_t len)
{
	if (!_flipped)
	{
		::memcpy(data, begin() + readPos, len);
		readPos += len;
	}
	else
	{
		if (len <= readPos)
		{
			::memcpy(data, begin() + _readPos, len);
			readPos += len;
		}
		else
		{
			size_t tail = Capacity() - _readPos;
			::memcpy(data, begin() + _readPos, tail);
			::memcpy(data + tail, begin(), len - tail);
			readPos = len - tail;
			flipped = false;
		}
	}

	return true;
}
bool CBuffer::Write(const char* data, size_t len)
{
    if (data == nullptr)
        return false;
    if (len > RemainedCapacity())
        return false;

	if (!_flipped)
	{
		if (len <= Capacity() - _writePos)
		{
			std::copy(data, data + len, _buf.begin() + _writePos);
			_writePos += len;
		}
		else
		{
			size_t tail = Capacity() - _writePos;
			std::copy(data, data + tail, _buf.begin() + _writePos);
			std::copy(data + tail, data + len, _buf.begin());
			_writePos = len - tail;
			_flipped = true;
		}
	}
	else
	{
		std::copy(data, data + len, _buf.begin() + _writePos);
		_writePos += len;
	}

    return true;
}

//-----------------------------------------------------------------

