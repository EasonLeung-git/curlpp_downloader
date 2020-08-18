#include "Dialog.hh"
#include "ui_Dialog.h"

// ftp://10.1.10.84/test_file.50MB.1

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_downloader_pool(new std::array<CurlppDownloader *, 8>)
    , m_worker_pool(new std::array<CurlppWoker *, 8>)
    , m_worker_thread_pool(new std::array<QThread *, 8>)
{
    ui->setupUi(this);

    // init 8 threads.
    // init 8 wokers.
    // init 8 downloaders.
    for (std::size_t i = 0; i < 8; i++)
    {
        this->m_worker_thread_pool->at(i) = new QThread;
        this->m_worker_pool->at(i) = new CurlppWoker;
        this->m_downloader_pool->at(i) = new CurlppDownloader;
    }

    this->setWindowTitle("Curlpp multithreads");
    this->setFixedSize(680, 350);

    // banding CurlppDownloader and CurlppWorker.
    for (std::size_t i = 0; i < 8; i++)
    {
        QObject::connect(this->m_downloader_pool->at(i), &CurlppDownloader::signalStartDownload, \
                         this->m_worker_pool->at(i), &CurlppWoker::doWork);
    }

    // for quit button.
    QObject::connect(ui->pushButton_quit, &QPushButton::clicked, \
                     this, &Dialog::close);

    QObject::connect(ui->pushButton_start, &QPushButton::clicked, \
                     this, [&] () {
        if (!this->installThread(ui->lineEdit_url, ui->lineEdit_path, \
                                 this->m_downloader_pool->at(0), \
                                 this->m_worker_pool->at(0), this->m_worker_thread_pool->at(0)))
        {
            QMessageBox::critical(this, "Error", "something wrong!");
            this->m_worker_thread_pool->at(0)->quit();
        }
    });

    // for start button.
    // quit the workthread when worker object finished.
    // do not using 'deleteLater'.
//    QObject::connect(this->m_worker, &CurlppWoker::finished, \
//                     this->m_worker_thread->at(0), &QThread::quit);

//    QObject::connect(ui->pushButton_start, &QPushButton::clicked, \
//                     this, [&] () {
////        for (std::size_t i = 0; i < 8; i++)
////        {
////            if ()
////        }
//        // move worker to new thread.
//        this->m_worker->moveToThread(this->m_worker_thread->at(0));
//        // start worker thread.
//        this->m_worker_thread->at(0)->start();
//        // get url and file path.
//        // send url and file path to CurlppDownloader.
//        this->m_downloader->sendStartSignal(ui->lineEdit_url->text(), ui->lineEdit_path->text());
//        // make an tips.
////        QMessageBox::information(this, "INFO", ui->lineEdit_url->text() + "\n" + ui->lineEdit_path->text());
//    });
//    QObject::connect(this->m_worker, &CurlppWoker::finished, \
//                     this, [&] () { QMessageBox::information(this, "OK", ui->lineEdit_path->text() + " downloaded!"); });
}

Dialog::~Dialog()
{
    delete this->m_downloader_pool;
    delete this->m_worker_pool;
    delete this->m_worker_thread_pool;
    delete ui;
}

bool Dialog::installThread(QLineEdit *_url, QLineEdit *_path, CurlppDownloader *_downloader, CurlppWoker *_worker, QThread *_thread)
{
    if (_url->text().isEmpty() || _path->text().isEmpty())
        return false;
    _worker->moveToThread(_thread);
    _thread->start();
    _downloader->sendStartSignal(_url->text(), _path->text());

    QObject::connect(_worker, &CurlppWoker::finished, \
                     this, [&] () { \
        QMessageBox::information(this, "OK", _path->text() + " downloaded!"); \
    });

    // quit the workthread when worker object finished.
    // do not using 'deleteLater'.
    QObject::connect(_worker, &CurlppWoker::finished, \
                     _thread, &QThread::quit);

    return true;
}

