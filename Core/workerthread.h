#ifndef WorkerThread_H
#define WorkerThread_H

#include "becreative_global.h"
#include <QThread>
#include "rom.h"
#include <QList>

namespace beCreative
{
    namespace Core
    {
        class WorkerThread : public QThread
        {
            Q_OBJECT
            void run() Q_DECL_OVERRIDE;

            signals:
            void resultReady(QList<int> *li);

            public:
            WorkerThread(Rom *rom, int minimum);
            ~WorkerThread();

            int minimumBytes() const;
            void setMinimumBytes(int minimumBytes);

            Rom *rom() const;
            void setRom(Rom *rom);

        private:
            Rom *_rom;
            int _minimumBytes;
        };
    }
}
#endif // WorkerThread_H
