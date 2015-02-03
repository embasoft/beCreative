#include "compiler.h"
#ifdef Q_OS_LINUX
    #define COMPILER_PATH "/bin/sh"
#elif Q_OS_WIN
    #define COMPILER_PATH "C:\Windows\System32\cmd.exe"
#endif

namespace beCreative
{
    namespace Utils
    {
        Compiler::Compiler(QObject *parent) : QObject(parent)
        {

        }

        Compiler::Compiler(QString compilerPath, QObject *parent)
        {
            setCompilerPath(compilerPath);
        }

        Compiler::Compiler(QString compilerPath, QString directory, QObject *parent)
        {
            setCompilerPath(compilerPath);
            setDirectory(directory);
        }

        Compiler::~Compiler()
        {

        }

        int Compiler::compile(QString input)
        {
            QProcess *exec = new QProcess(0);
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

            if (compilerPath() != "")
                env.insert("PATH", compilerPath());
            else
                return 1;

            if (directory() != "")
            {
                exec->setWorkingDirectory(directory());
            }
            else
            {
                return 2;
            }

            exec->setProcessChannelMode(QProcess::MergedChannels);
            exec->setProcessEnvironment(env);

            QStringList arguments;

            arguments << "-c";
            arguments << "arm-none-eabi-as -o " + input + ".o " + input;

            exec->start("/bin/sh", arguments);
            exec->waitForFinished();
            arguments.clear();

            arguments << "-c";
            arguments << "arm-none-eabi-objcopy -O binary " + input + ".o " + input + ".bin";
            exec->start("/bin/sh", arguments);

            return true;
        }
        QString Compiler::compilerPath() const
        {
            return _compilerPath;
        }

        void Compiler::setCompilerPath(const QString &compilerPath)
        {
            _compilerPath = compilerPath;
        }
        QString Compiler::directory() const
        {
            return _directory;
        }

        void Compiler::setDirectory(const QString &directory)
        {
            _directory = directory;
        }


    }
}
