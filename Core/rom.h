#ifndef ROM_H
#define ROM_H

#include "becreative_global.h"
#include <QFile>
#include <QList>
#include "romstream.h"

namespace beCreative
{
    namespace Core
    {
        class Rom : public QObject
        {
            Q_OBJECT
        public:
            Rom(QString path);
            ~Rom();

            // File depending methods
            bool write(QString path);
            bool load(QString path);

            // Stream manipulation methods
            bool atEnd();
            void closeStream();
            void jumpToOffset(uint offset);
            void openStream(QIODevice::OpenMode openMode);
            int size();
            int pos();

            // Data reading methods
            char readByte();
            QByteArray readBytes(uint length = 1);
            int readFreeBytesAtOffset(int offset);
            QList<int> readFreeSpaceOffsets(int minimum);
            QString readString(uint length);
            quint16 readHalfWord();
            quint32 readWord();
            RomStream *romStream();

        private:
            RomStream *_romStream;
            QByteArray _rawData;
            QFile *_file;
        };
    }
}

#endif // ROM_H
