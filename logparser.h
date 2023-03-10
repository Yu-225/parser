#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QString>
#include <QStringList>

class LogParser
{
public:
    QStringList parseFile(const QString& filePath);
};

#endif // LOGPARSER_H
