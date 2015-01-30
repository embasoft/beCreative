#include "workerthread.h"
#include <QDebug>

namespace beCreative
{
namespace Core
{
void WorkerThread::run()
{
    rom()->openStream(QIODevice::ReadOnly);

    QList<int> output;
    int freeBytes = 0;
    while (!rom()->atEnd())
    {
        char byte = rom()->readByte();
        if (byte == -1)
        {
            int count = 1;
            char nextByte = rom()->readByte();
            while (nextByte == -1)
            {
                count++;
                nextByte = rom()->readByte();
            }
            if (count >= minimumBytes())
            {
                output.append(rom()->pos()  - count - 1);
                freeBytes += count;
            }
        }
    }

    rom()->closeStream();

    typedef QList<int> OffsetList;
    qRegisterMetaType<OffsetList>("OffsetList");
    qDebug() << QString::number(output.size());
    emit resultReady(&output);
}

WorkerThread::WorkerThread(Rom * rom, int minimum)
{
    setRom(rom);
    setMinimumBytes(minimum);
}

WorkerThread::~WorkerThread()
{

}
int WorkerThread::minimumBytes() const
{
    return _minimumBytes;
}

void WorkerThread::setMinimumBytes(int minimumBytes)
{
    _minimumBytes = minimumBytes;
}

Rom *WorkerThread::rom() const
{
    return _rom;
}

void WorkerThread::setRom(Rom *rom)
{
    _rom = rom;
}
}
}

