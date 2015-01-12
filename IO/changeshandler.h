#ifndef CHANGESHANDLER_H
#define CHANGESHANDLER_H

#include "singleqt_global.h"
#include "romstream.h"
#include <QByteArray>
#include <QList>
#include <QMutableListIterator>

namespace Single
{
    namespace Core
    {
        class ChangesHandler
        {
        public:
            ChangesHandler();
            uint addChange(QByteArray array, uint offset);
            bool removeChange(uint id);
            void setCreateBackups(bool backup);
            void setRomStream(RomStream *romstream);
            void writeChanges(bool returnToOldOffset = true);
            bool CreateBackups();
            struct Change
            {
                uint id;
                QByteArray data;
                quint64 offset;
            };
            QList<Change> Changes();
            Change Backup(uint id);
            QList<Change> Backups();
        private:
            QList<Change> _changes;
            QList<Change> _backups;
            RomStream *_romStream;
            bool _createBackups = true;
            uint _changesCount = 0;
        };
    }
}

#endif // CHANGESHANDLER_H
