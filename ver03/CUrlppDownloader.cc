#include "CUrlppDownloader.hh"

CUrlppDownloader::CUrlppDownloader()
    : m_request(new curlpp::Easy)
    , m_save_as(new std::ofstream)
    , m_file_name(new std::string)
{
}

CUrlppDownloader::~CUrlppDownloader()
{
    delete this->m_request;
    delete this->m_save_as;
    delete this->m_file_name;
}

bool CUrlppDownloader::setup(std::string& _url, std::string _file_name, bool _no_progress, bool _follow_location)
{
    if (_url.empty() || _file_name.empty())
        return false;

    *this->m_file_name = _file_name;
    this->m_save_as = new std::ofstream(_file_name);
    this->m_request->setOpt(curlpp::Options::Url(_url));
    this->m_request->setOpt(curlpp::Options::NoProgress(_no_progress));
    this->m_request->setOpt(curlpp::Options::FollowLocation(_follow_location));

    return true;
}

bool CUrlppDownloader::installProgressBarFunction(int (*funtion) (std::size_t, std::size_t, double, double))
{
    if (funtion == nullptr)
        return false;

    this->m_request->setOpt(curlpp::Options::ProgressFunction(funtion));

    return true;
}

bool CUrlppDownloader::installWriteFunction(std::size_t (*function) (const char *, std::size_t, std::size_t))
{
    if (function == nullptr)
        return false;

    this->m_request->setOpt(curlpp::Options::WriteFunction(function));

    return true;
}

void CUrlppDownloader::run()
{
    emit this->started();
    this->m_request->perform();
    emit this->finished();
}

void CUrlppDownloader::installDefaultProgressFunction()
{
    this->m_request->setOpt(curlpp::Options::ProgressFunction([&] (std::size_t total, std::size_t done, auto...)
    {
        std::cout << "downloading : \"" << *this->m_file_name + "\" : " << done << " of " << total
                  << " bytes received (" << int(total ? done * 100. / total : 0) << "%)" << std::flush;
        std::cout << "\r" << std::flush;
        return 0;
    }));
}

void CUrlppDownloader::installDefaultWriteFunction()
{
    this->m_request->setOpt(curlpp::Options::WriteFunction([&] (const char *_buf, std::size_t _size, std::size_t _nmemb)
    {
        this->m_save_as->write(_buf, _size * _nmemb);

        return _size * _nmemb;
    }));
}

std::string CUrlppDownloader::getFileName()
{
    return *this->m_file_name;
}

std::ofstream *CUrlppDownloader::getFstream()
{
    return this->m_save_as;
}

curlpp::Easy *CUrlppDownloader::getRequset()
{
    return this->m_request;
}
