#ifndef ROMSTREAM_H
#define ROMSTREAM_H

#include "singleqt_global.h"
#include <QBuffer>

namespace Single
{
    namespace Core
    {
        class RomStream : public QBuffer
        {
            Q_OBJECT
        public:
            explicit RomStream(QByteArray *array, QObject *parent = 0);
            void clearBytesAt(uint offset, uint length, char value = 0xFF);
            void clearBytes(uint length, char value = 0xFF, bool returnToBegin = true);
        signals:

        public slots:

        };
    }
}

#endif // ROMSTREAM_H
