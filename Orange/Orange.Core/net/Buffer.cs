using System;
using System.Collections.Generic;
using System.Text;

namespace Orange.Core.net
{
    class CBuffer
    {
        byte[] _buf;
        int _readPos;
        int _writePos;
        bool _flipped;

        public CBuffer(int capacity)
        {
            _buf = new byte[capacity];
            Clear();
        }

        void Clear()
        {
            _readPos = 0;
            _writePos = 0;
            _flipped = false;
        }

        public bool IsEmpty
        {
            get
            {
                return !_flipped && _readPos == _writePos;
            }
        }

        public bool IsFull
        {
            get
            {
                if (_flipped)
                {
                    return _readPos - _writePos == Capacity;
                }
                else
                {
                    return _writePos - _readPos == Capacity;
                }
            }
        }

        public int Capacity
        {
            get
            {
                return _buf.Length;
            }
        }

        public int UsedCapacity
        {
            get
            {
                if (_flipped)
                {
                    return Capacity + _writePos - _readPos;
                }
                else
                {
                    return _writePos - _readPos;
                }
            }
        }

        public int RemainedCapacity
        {
            get
            {
                if (_flipped)
                {
                    return _readPos - _writePos;
                }
                else
                {
                    return Capacity + _readPos - _writePos;
                }
            }
        }

        public bool Read(byte[] data, int len)
        {
            if (data == null)
                return false;
            if (len <= 0)
                return false;
            if (len > UsedCapacity)
                return false;

            Read(ref _readPos, ref _flipped, data, len);

            return true;
        }

        public bool Peek(byte[] data, int len)
        {
            if (data == null)
                return false;
            if (len <= 0)
                return false;
            if (len > UsedCapacity)
                return false;

            var readpos = _readPos;
            var flipped = _flipped;

            Read(ref readpos, ref flipped, data, len);

            return true;
        }

        bool Read(ref int readPos, ref bool flipped, byte[] data, int len)
        {
            if (flipped)
            {
                //----------_writePos---------------_readPos-----------------
                //2中情形：
                //1. 尾部足够读
                //2. 尾部不够读，先读尾部，再读头部

                if (len <= Capacity - readPos)
                {
                    Buffer.BlockCopy(_buf, readPos, data, 0, len);
                    _readPos += len;
                }
                else
                {
                    var tail = Capacity - _readPos;
                    Buffer.BlockCopy(_buf, readPos, data, 0, tail);
                    Buffer.BlockCopy(_buf, 0, data, tail, len - tail);

                    readPos = len - tail;
                    flipped = false;
                }
            }
            else
            {
                //----------_readPos---------------_writePos-----------------
                Buffer.BlockCopy(_buf, readPos, data, 0, len);
                readPos += len;
            }

            return true;
        }

        public bool Write(byte[] data, int len)
        {
            if (data == null)
                return false;
            if (len <= 0)
                return false;
            if (len > RemainedCapacity)
                return false;

            if (!_flipped)
            {
                //----------_readPos---------------_writePos-----------------
                //这里有2种情形：
                //1. 尾部足够写
                //2. 尾部不够写，先写尾部，再写头部

                if (len <= Capacity - _writePos)
                {
                    Buffer.BlockCopy(data, 0, _buf, _writePos, len);
                    _writePos += len;
                }
                else
                {
                    var tail = Capacity - _writePos;
                    Buffer.BlockCopy(data, 0, _buf, _writePos, tail);
                    Buffer.BlockCopy(data, tail, _buf, 0, len - tail);

                    _writePos = len - tail;
                    _flipped = true;
                }
            }
            else
            {
                //----------_writePos---------------_readPos-----------------

                Buffer.BlockCopy(data, 0, _buf, _writePos, len);
                _writePos += len;
            }

            return true;
        }
    }
}
