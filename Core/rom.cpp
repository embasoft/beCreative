#include "rom.h"
#include <QDebug>

namespace beCreative
{
    namespace Core
    {
        Rom::Rom(QString path)
        {
            if (!load(path))
                qDebug() << "Couldn't load rom file";
        }

        Rom::~Rom()
        {
            _romStream = NULL;
            _file = NULL;
            _rawData.clear();
        }

        bool Rom::load(QString path)
        {
            // Open the File
            // If an error occurs, the method aborts
            _file = new QFile(path);
            if (!_file->open(QIODevice::ReadWrite))
                return false;
            // Read all bytes into a byte array
            _rawData = _file->readAll();
            // Close the filestream and work from now only in memory
            _file->close();
            // Point to the stream in memory
            _romStream = new RomStream(&_rawData);

            return true;
        }

        void Rom::jumpToOffset(uint offset)
        {
            _romStream->seek(offset);
        }

        void Rom::openStream(QIODevice::OpenMode openMode)
        {
            _romStream->open(openMode);
        }

        bool Rom::atEnd()
        {
            return _romStream->atEnd();
        }

        void Rom::closeStream()
        {
            _romStream->close();
        }

        int Rom::size()
        {
            return _romStream->size();
        }

        int Rom::pos()
        {
            return _romStream->pos();
        }

        char Rom::readByte()
        {
            char *output = new char[1];

            if (_romStream)
            {
                _romStream->read(output, 1);
                //qDebug() << QString::number(*output);
            }

            return *output;
        }

        QByteArray Rom::readBytes(uint length)
        {
            QByteArray output;

            if (_romStream)
            {
                char *temp = new char[length];
                _romStream->read(temp, length);
                output.append(temp, length);
            }

            return output;
        }

        int Rom::readFreeBytesAtOffset(int offset)
        {
            openStream(QIODevice::ReadOnly);
            _romStream->seek(offset);

            int freeBytes = 0;
            while (!atEnd())
            {
                char byte = readByte();
                if (byte == -1)
                {
                    char nextByte = readByte();
                    while (nextByte == -1)
                    {
                        freeBytes++;
                        nextByte = readByte();
                    }
                }
            }
            return freeBytes;
        }

        /*
         * Return a list filled with offsets of space with n >= int minimum free space
         */
        QList<int> Rom::readFreeSpaceOffsets(int minimum)
        {
            openStream(QIODevice::ReadOnly);

            QList<int> output;
            int freeBytes = 0;
            while (!atEnd())
            {
                char byte = readByte();
                if (byte == -1)
                {
                    int count = 1;
                    char nextByte = readByte();
                    while (nextByte == -1)
                    {
                        count++;
                        nextByte = readByte();
                    }
                    if (count >= minimum)
                    {
                        output.append(pos()  - count - 1);
                        freeBytes += count;
                    }
                }
            }

            closeStream();

            return output;
        }

        QString Rom::readString(uint length)
        {
            QString output;

            if (_romStream)
            {
                char *temp = 0;
                _romStream->read(temp, length);
                output = temp;
            }

            return output;
        }

        quint16 Rom::readHalfWord()
        {
            return readBytes(2).toUShort();
        }

        quint32 Rom::readWord()
        {
            return readBytes(4).toUInt();
        }
        RomStream *Rom::romStream()
        {
            return _romStream;
        }


        bool Rom::write(QString path)
        {
            // Open the File
            // If an error occurs, the method aborts
            if (_romStream)
            {
                QFile file(path);
                if (!file.open(QIODevice::ReadWrite))
                    return false;

                // Jump to file begin and write byte array
                file.seek(0);
                file.write(_rawData);

                // Close all streams and clear the byte array
                file.close();

                return true;
            }
            return false;
        }
    }
}
