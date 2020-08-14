#include "MainWindow.hh"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_saved_file_name(new QString)
    , m_downloader(new CUrlppDownloader)
{
    ui->setupUi(this);
//    this->m_file_dlg->setModal(true);
    this->ui->lineEdit_save_as->setReadOnly(true);
    this->initQtConnect();
    this->initCurlpp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initQtConnect()
{
    QObject::connect(ui->toolButton_brw, &QToolButton::clicked, \
                     this, [&] () {
        *this->m_saved_file_name = QFileDialog::getSaveFileName(this);
#ifdef Q_OS_WIN
        this->m_saved_file_name->replace('/', '\\');
#endif
        ui->lineEdit_save_as->setText(*this->m_saved_file_name);
    });

    QObject::connect(ui->pushButton_quit, &QPushButton::clicked, \
                     this, [&] () { \
        if ( QMessageBox::question(this, "Close?", "Close the window?"))
            this->close();
    });

    QObject::connect(ui->pushButton_start, &QPushButton::clicked, \
                     this, [&] () { \
        if (ui->lineEdit_url->text().isEmpty() || ui->lineEdit_save_as->text().isEmpty())
        {
            QMessageBox::critical(this, "Error", "Please check enter!");
            return ;
        }
        this->initCurlpp();

        this->m_downloader->run();
    });
}

void MainWindow::initCurlpp()
{
    std::string url = ui->lineEdit_url->text().toStdString();
    std::string file_name = ui->lineEdit_save_as->text().toStdString();
    this->m_downloader->setup(url, file_name);

    this->m_downloader->getRequset()->setOpt(curlpp::Options::WriteFunction([&] (const char *_buf, std::size_t _size, std::size_t _nmemb)
    {
        this->m_downloader->getFstream()->write(_buf, _size * _nmemb);

        return _size * _nmemb;
    }));

//    this->m_downloader->installDefaultWriteFunction();
}

// ftp://10.1.10.84/test_file.200MB.1
