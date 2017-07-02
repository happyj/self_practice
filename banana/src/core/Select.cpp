#include "Select.h"
#include "Const.h"



namespace Banana
{
    namespace Net
    {
        //-----------------------------------------------------------------

        CSelect::CSelect()
        {
            FD_ZERO(&_read_fds);
            FD_ZERO(&_write_fds);
            FD_ZERO(&_error_fds);
        }
        CSelect::~CSelect()
        {

        }

        //-----------------------------------------------------------------

        bool CSelect::Register(int fd, int events)
        {
            if (FD_ISSET(fd, &_read_fds) || FD_ISSET(fd, &_write_fds) || FD_ISSET(fd, &_error_fds))
                return false;

            if (events & static_cast<int>(EventType::eEventType_Read))
                FD_SET(fd, &_read_fds);
            if (events & static_cast<int>(EventType::eEventType_Write))
                FD_SET(fd, &_write_fds);
            if (events & static_cast<int>(EventType::eEventType_Error))
                FD_SET(fd, &_error_fds);

            return true;
        }

        bool CSelect::Unregister(int fd)
        {
            FD_CLR(fd, &_read_fds);
            FD_CLR(fd, &_write_fds);
            FD_CLR(fd, &_error_fds);

            return true;
        }

        bool CSelect::Modify(int fd, int events)
        {
            Unregister(fd);
            Register(fd, events);

            return true;
        }

        int CSelect::Poll(int microSeconds)
        {
            _fds.clear();

            struct timeval t;
            t.tv_sec = 0;
            t.tv_usec = microSeconds;

            fd_set read_fds = _read_fds;
            fd_set write_fds = _write_fds;
            fd_set error_fds = _error_fds;

            int count = ::select(0, &read_fds, &write_fds, &error_fds, &t);
            if (count == 0)
            {
                return 0;
            }

            if (count == -1)
            {
                return -1;
            }

            for (auto& e : read_fds.fd_array)
            {
                if (FD_ISSET(e, &read_fds))
                {
                    _fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Read);
                }
            }

            for (auto& e : write_fds.fd_array)
            {
                if (FD_ISSET(e, &write_fds))
                {
                    _fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Write);
                }
            }

            for (auto& e : error_fds.fd_array)
            {
                if (FD_ISSET(e, &error_fds))
                {
                    _fds[e] = GetValue(e) | static_cast<int>(EventType::eEventType_Error);
                }
            }


            return count;
        }

        //-----------------------------------------------------------------

    }
}

