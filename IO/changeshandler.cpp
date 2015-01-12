#include "changeshandler.h"

namespace Single
{
    namespace Core
    {
        ChangesHandler::ChangesHandler()
        {
        }

        uint ChangesHandler::addChange(QByteArray array, uint offset)
        {
            Change change = {_changesCount, array, offset};
            _changes.append(change);
            if (_createBackups)
            {
                Change backup;
                backup.id = _changesCount;
                backup.data = _romStream->read(array.size());
                backup.offset = offset;
            }
            return _changesCount++;
        }

        bool ChangesHandler::removeChange(uint id)
        {
            QMutableListIterator<Change> i(_changes);
            while (i.hasNext())
            {
                if (i.next().id == id)
                {
                    i.remove();
                    return true;
                }
            }
            return false;
        }

        void ChangesHandler::setCreateBackups(bool backup)
        {
            _createBackups = backup;
        }

        void ChangesHandler::setRomStream(RomStream *romstream)
        {
            _romStream = romstream;
        }
        
        void ChangesHandler::writeChanges(bool returnToOldOffset)
        {
            uint oldOffset = _romStream->pos();
            foreach(Change change, _changes)
            {
                _romStream->seek(change.offset);
                _romStream->write(change.data);
            }
            if (returnToOldOffset)
                _romStream->seek(oldOffset);
        }

        bool ChangesHandler::CreateBackups()
        {
            return _createBackups;
        }

        QList<ChangesHandler::Change> ChangesHandler::Changes()
        {
            return _changes;
        }
        
        ChangesHandler::Change ChangesHandler::Backup(uint id)
        {
            return _backups.at(id);
        }
        
        QList<ChangesHandler::Change> ChangesHandler::Backups()
        {
            return _backups;
        }
    }
}
