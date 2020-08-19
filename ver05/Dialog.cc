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

    // for start button.
    QObject::connect(ui->pushButton_start, &QPushButton::clicked, \
                     this, [&] () {
        //! 0
        if (!this->installThread(ui->lineEdit_url, ui->lineEdit_path, \
                                 this->m_downloader_pool->at(0), \
                                 this->m_worker_pool->at(0), this->m_worker_thread_pool->at(0)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url->setText("null");
            ui->lineEdit_path->setText("null");
            this->m_worker_thread_pool->at(0)->exit();
        }

        //! 1
        if (!this->installThread(ui->lineEdit_url_2, ui->lineEdit_path_2, \
                                 this->m_downloader_pool->at(1), \
                                 this->m_worker_pool->at(1), this->m_worker_thread_pool->at(1)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_2->setText("null");
            ui->lineEdit_path_2->setText("null");
            this->m_worker_thread_pool->at(1)->exit();
        }

        //! 2
        if (!this->installThread(ui->lineEdit_url_3, ui->lineEdit_path_3, \
                                 this->m_downloader_pool->at(2), \
                                 this->m_worker_pool->at(2), this->m_worker_thread_pool->at(2)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_3->setText("null");
            ui->lineEdit_path_3->setText("null");
            this->m_worker_thread_pool->at(2)->exit();
        }

        //! 3
        if (!this->installThread(ui->lineEdit_url_4, ui->lineEdit_path_4, \
                                 this->m_downloader_pool->at(3), \
                                 this->m_worker_pool->at(3), this->m_worker_thread_pool->at(3)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_4->setText("null");
            ui->lineEdit_path_4->setText("null");
            this->m_worker_thread_pool->at(3)->exit();
        }

        //! 4
        if (!this->installThread(ui->lineEdit_url_5, ui->lineEdit_path_5, \
                                 this->m_downloader_pool->at(4), \
                                 this->m_worker_pool->at(4), this->m_worker_thread_pool->at(4)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_5->setText("null");
            ui->lineEdit_path_5->setText("null");
            this->m_worker_thread_pool->at(4)->exit();
        }

        //! 5
        if (!this->installThread(ui->lineEdit_url_6, ui->lineEdit_path_6, \
                                 this->m_downloader_pool->at(5), \
                                 this->m_worker_pool->at(5), this->m_worker_thread_pool->at(5)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_6->setText("null");
            ui->lineEdit_path_6->setText("null");
            this->m_worker_thread_pool->at(5)->exit();
        }

        //! 6
        if (!this->installThread(ui->lineEdit_url_7, ui->lineEdit_path_7, \
                                 this->m_downloader_pool->at(6), \
                                 this->m_worker_pool->at(6), this->m_worker_thread_pool->at(6)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_7->setText("null");
            ui->lineEdit_path_7->setText("null");
            this->m_worker_thread_pool->at(6)->exit();
        }

        //! 7
        if (!this->installThread(ui->lineEdit_url_8, ui->lineEdit_path_8, \
                                 this->m_downloader_pool->at(7), \
                                 this->m_worker_pool->at(7), this->m_worker_thread_pool->at(7)))
        {
            //            QMessageBox::critical(this, "Error", "something wrong!");
            ui->lineEdit_url_8->setText("null");
            ui->lineEdit_path_8->setText("null");
            this->m_worker_thread_pool->at(7)->exit();
        }
    });

    // for clear button.
    QObject::connect(ui->pushButton_clear, &QPushButton::clicked, \
                     this, [&] () {
        ui->lineEdit_url->clear();
        ui->lineEdit_url_2->clear();
        ui->lineEdit_url_3->clear();
        ui->lineEdit_url_4->clear();
        ui->lineEdit_url_5->clear();
        ui->lineEdit_url_6->clear();
        ui->lineEdit_url_7->clear();
        ui->lineEdit_url_8->clear();

        ui->lineEdit_path->clear();
        ui->lineEdit_path_2->clear();
        ui->lineEdit_path_3->clear();
        ui->lineEdit_path_4->clear();
        ui->lineEdit_path_5->clear();
        ui->lineEdit_path_6->clear();
        ui->lineEdit_path_7->clear();
        ui->lineEdit_path_8->clear();

        QMessageBox::information(this, "Tips", "Clean all inputs!");
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

    // some bug at here.
    //    QObject::connect(_worker, &CurlppWoker::finished, \
    //                     this, [&] () { \
    //        QMessageBox::information(this, "OK", _path->text() + " downloaded!"); \
    //    });

    // quit the workthread when worker object finished.
    // do not using 'deleteLater'.
    QObject::connect(_worker, &CurlppWoker::finished, \
                     _thread, &QThread::quit);

    return true;
}

