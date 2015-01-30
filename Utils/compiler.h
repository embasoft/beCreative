#ifndef COMPILER_H
#define COMPILER_H

#include "becreative_global.h"
#include <QProcess>
#include <QDebug>

namespace beCreative
{
    namespace Utils
    {
        class Compiler : public QObject
        {
            Q_OBJECT

            public:
            explicit Compiler(QObject *parent = 0);
            explicit Compiler(QString compilerPath, QObject *parent = 0);
            explicit Compiler(QString compilerPath, QString directory, QObject *parent = 0);
            ~Compiler();
            int compile(QString input);

            QString compilerPath() const;
            void setCompilerPath(const QString &compilerPath);

            QString directory() const;
            void setDirectory(const QString &directory);

        private:
            QString _compilerPath;
            QString _directory;
        signals:

        public slots:
        };
    }
}

#endif // COMPILER_H
