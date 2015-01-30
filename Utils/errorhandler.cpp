#include "errorhandler.h"
namespace beCreative
{
    namespace Utils
    {
        ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
        {
            _errorCount = 0;
        }

        ErrorHandler::~ErrorHandler()
        {

        }

        int ErrorHandler::addError(int id, QString type, QString description)
        {
            Error error = {id, type, description};
            _errors.append(error);

            return _errorCount++;
        }

        bool ErrorHandler::removeError(int id)
        {
            QMutableListIterator<Error> i(_errors);
            while(i.hasNext())
            {
                if (i.next().id == id)
                {
                    i.remove();
                    return true;
                }
            }

            return false;
        }
        QList<ErrorHandler::Error> ErrorHandler::errors() const
        {
            return _errors;
        }

        void ErrorHandler::setErrors(const QList<Error> &errors)
        {
            _errors = errors;
        }
        int ErrorHandler::errorCount() const
        {
            return _errorCount;
        }

        void ErrorHandler::setErrorCount(int errorCount)
        {
            _errorCount = errorCount;
        }


    }
}

