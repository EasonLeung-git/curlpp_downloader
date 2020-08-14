#ifndef CURLPPDOWNLOADER_HH
#define CURLPPDOWNLOADER_HH

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include <QObject>

class CUrlppDownloader : public QObject
{
    Q_OBJECT

public:
    CUrlppDownloader();
    ~CUrlppDownloader();

    bool setup(std::string& _url, std::string _file_name, bool _no_progress = false, bool _follow_location = true);
    bool installProgressBarFunction(int (*funtion) (std::size_t _total, std::size_t _done, double _a, double _b));
    bool installWriteFunction(std::size_t (*function) (const char *_buf, std::size_t _size, std::size_t _nmembe));
    void run();

    void installDefaultProgressFunction();
    void installDefaultWriteFunction();

    std::string getFileName();
    std::ofstream *getFstream();
    curlpp::Easy *getRequset();

signals:
    void started();
    void finished();

private:
    curlpp::Easy *m_request;
    std::ofstream *m_save_as;
    std::string *m_file_name;
};

#endif // CURLPPDOWNLOADER_HH
