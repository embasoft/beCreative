#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "becreative_global.h"
#include <QDebug>

namespace beCreative
{
    namespace Utils
    {
        class ErrorHandler : public QObject
        {
        Q_OBJECT

        public:
            explicit ErrorHandler(QObject *parent = 0);
            ~ErrorHandler();

            int addError(int id, QString type, QString description);
            bool removeError(int id);

            struct Error
            {
                int id;
                QString type;
                QString description;
            };

            QList<ErrorHandler::Error> errors() const;
            void setErrors(const QList<Error> &errors);

            int errorCount() const;
            void setErrorCount(int errorCount);

        private:
            QList<Error> _errors;
            int _errorCount;
        signals:

        public slots:
        };
    }
}

#endif // ERRORHANDLER_H
