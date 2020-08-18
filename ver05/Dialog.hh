#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QMessageBox>
#include <QThread>
#include <array>
#include <QLineEdit>

#include "CurlppDownloader.hh"
#include "CurlppWoker.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    std::array<CurlppDownloader *, 8> *m_downloader_pool;
    std::array<CurlppWoker *, 8> *m_worker_pool;
    // worker thread pool.
    std::array<QThread *, 8> *m_worker_thread_pool;

    bool installThread(QLineEdit *_url, QLineEdit *_path, CurlppDownloader *_downloader, CurlppWoker *_worker, QThread *_thread);
};
#endif // DIALOG_HH
