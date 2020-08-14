// https://bisqwit.iki.fi/jutut/kuvat/programming_examples/cpp_thread_tutorial/
//

#include <iostream>
#include <string>
#include <thread>
#include "CUrlppDownloader.hh"

static std::string g_url_root = "ftp://10.1.10.84/"; // test_file.200MB.1";

void downloader_func(std::string _url, std::string _file_name)
{
    CUrlppDownloader downloader;
    downloader.setup(_url, _file_name);
    downloader.installDefaultProgressFunction();
    downloader.installDefaultWriteFunction();
    downloader.run();
}

int main(int argc, char *argv[])
{
    (void) argc, (void) argv;

    std::thread t1(downloader_func, g_url_root + "test_file.200MB.1", "test_file.200MB.1");
    std::thread t2(downloader_func, g_url_root + "test_file.200MB.2", "test_file.200MB.2");

    t1.join();
    t2.join();

    std::cout << "\ndone.\n";

    return 0;
}
