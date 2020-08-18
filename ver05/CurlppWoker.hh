#ifndef CURLPPWOKER_HH
#define CURLPPWOKER_HH

#include <QObject>
#include <QDebug>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>

class CurlppWoker : public QObject
{
    Q_OBJECT

public:
    explicit CurlppWoker(QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void doWork(QString _url, QString _file_name);
};

#endif // CURLPPWOKER_HH
