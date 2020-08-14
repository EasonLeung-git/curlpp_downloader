// https://bisqwit.iki.fi/jutut/kuvat/programming_examples/cpp_thread_tutorial/
//

#include <iostream>
#include <string>
#include "CUrlppDownloader.hh"

static std::string g_url = "ftp://10.1.10.84/test_file.200MB.1";

int main(int argc, char *argv[])
{
    (void) argc, (void) argv;

    CUrlppDownloader downloader;
    downloader.setup(::g_url, "test_file.200MB.1");
    downloader.installDefaultProgressFunction();
    downloader.installDefaultWriteFunction();
    downloader.run();

    std::cout << "\ndone.\n";

    return 0;
}
