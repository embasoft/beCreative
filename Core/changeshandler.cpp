#include "changeshandler.h"
#include <QDebug>

namespace beCreative
{
    namespace Core
    {
        ChangesHandler::ChangesHandler()
        {
        }

        ChangesHandler::ChangesHandler(RomStream *romstream)
        {
            if (romstream)
                _romStream = romstream;
        }

        uint ChangesHandler::addChange(QByteArray array, uint offset)
        {
            Change change = {_changesCount, array, offset};
            _changes.append(change);
            if (_createBackups)
            {
                Change backup;
                _romStream->open(QIODevice::ReadWrite);

                backup.id = _changesCount;
                backup.data = _romStream->read(array.size());
                backup.offset = offset;
                _backups.append(backup);

                _romStream->close();
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
        
        bool ChangesHandler::writeChanges(bool returnToOldOffset)
        {
            if (_romStream)
            {
                _romStream->open(QIODevice::ReadWrite);
                uint oldOffset = _romStream->pos();

                foreach(Change change, _changes)
                {
                    _romStream->seek(change.offset);
                    _romStream->write(change.data);
                }

                if (returnToOldOffset)
                    _romStream->seek(oldOffset);

                _romStream->close();

                return true;
            }
            else
            {
                return false;
            }
        }

        bool ChangesHandler::CreateBackups()
        {
            return _createBackups;
        }

        QList<ChangesHandler::Change> ChangesHandler::Changes()
        {
            return _changes;
        }
        
        // The backup id is the same as the one of the change
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
