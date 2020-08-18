#ifndef CURLPPDOWNLOADER_HH
#define CURLPPDOWNLOADER_HH

#include <QObject>

#include <fstream>

class CurlppDownloader : public QObject
{
    Q_OBJECT
public:
    explicit CurlppDownloader(QObject *parent = nullptr);

    void sendStartSignal(QString _url, QString _path)
    {
        emit this->signalStartDownload(_url, _path);
    }

signals:
    void signalStartDownload(QString _url, QString _path);

public slots:
};

#endif // CURLPPDOWNLOADER_HH
