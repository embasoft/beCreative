#include "romstream.h"

namespace Single
{
    namespace Core
    {
        RomStream::RomStream(QByteArray *array, QObject *parent) : QBuffer(array, parent)
        {

        }

        void RomStream::clearBytesAt(uint offset, uint length, char value)
        {
            uint oldOffset = pos();
            seek(offset);
            for (int i = 0; i < length; i++)
            {
                write(&value);
            }
            seek(oldOffset);
        }

        void RomStream::clearBytes(uint length, char value, bool returnToBegin)
        {
            uint oldOffset = pos();
            for (int i = 0; i < length; i++)
            {
                write(&value);
            }
            if (returnToBegin)
                seek(oldOffset);
        }
    }
}
