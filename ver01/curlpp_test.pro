TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    CUrlppDownloader.hh

SOURCES += \
    CUrlppDownloader.cc \
    main.cc

INCLUDEPATH += ../curl_curlpp_lib/curl/include/
INCLUDEPATH += ../curl_curlpp_lib/curlpp/include/

message($$INCLUDEPATH)

CONFIG(debug, debug | release) {
    LIBS += -L$$PWD/../curl_curlpp_lib/curl_debug/bin/ -llibcurl-d
    LIBS += -L$$PWD/../curl_curlpp_lib/curlpp_debug/lib/ -llibcurlpp # 貌似可以不要
} else {
    LIBS += -L$$PWD/../curl_curlpp_lib/curl/bin/ -llibcurl
    LIBS += -L$$PWD/../curl_curlpp_lib/curlpp/lib/ -llibcurlpp # 貌似可以不要
}

message($$LIBS)

