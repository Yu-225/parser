#include "logparser.h"
#include <QFile>
#include <QTextStream>

QStringList LogParser::parseFile(const QString& filePath)
{
    QStringList errorLines;

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.contains("ERROR", Qt::CaseInsensitive) || line.contains("WARN", Qt::CaseInsensitive)) {
                errorLines << line;
            }
        }
        file.close();
    }

    return errorLines;
}
