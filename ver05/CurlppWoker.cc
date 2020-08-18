#include "CurlppWoker.hh"

CurlppWoker::CurlppWoker(QObject *parent) : QObject(parent)
{
}

void CurlppWoker::doWork(QString _url, QString _file_name)
{
    if (_file_name.isEmpty() || _url.isEmpty())
    {
        emit this->finished();
        return ;
    }

    curlpp::Easy *handle = new curlpp::Easy;
    handle->setOpt(curlpp::Options::Url(_url.toStdString()));
    handle->setOpt(curlpp::Options::NoProgress(false));
    handle->setOpt(curlpp::Options::FollowLocation(true));

    std::ofstream *fs = new std::ofstream(_file_name.toStdString());
    handle->setOpt(curlpp::Options::WriteFunction([&] (const char *_p, std::size_t _size, std::size_t _nmb)
    {
        fs->write(_p, _size * _nmb);

        return _size * _nmb;
    }));
//    handle->setOpt(curlpp::Options::ProgressFunction());

    handle->perform();
    fs->close();
    emit this->finished();
}
