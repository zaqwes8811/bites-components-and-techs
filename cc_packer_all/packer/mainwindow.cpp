#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

#include <openssl/bn.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/objects.h>

#include <QtConcurrent/QtConcurrent>
#include <QDebug>

//#include <tarlib/tarlib.h>

//#include <

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_observer, SIGNAL(finished()), this, SLOT(onFinish()));
}

void extract1(std::string const &filename, std::string const &destination)
{
   // create tar file with path and read mode
  //tarlib::tarFile tarf(filename, tarlib::tarModeRead);

   // extract to folder
   //tarf.extract(destination);
    std::string s;
}

void call() {

}

// http://ynonperek.com/course/qt/threads.html
// http://doc.qt.io/qt-5/threads-reentrancy.html
// http://doc.qt.io/qt-4.8/qtconcurrentmap.html#concurrent-map-reduce
//
// 0. Make message
// 1. eventExec() - не блокируем полностью
// 2. parallel all
//
// Split work -
// http://stackoverflow.com/questions/18962056/how-to-split-a-qlist-at-position-n-to-a-new-qlist
void MainWindow::OnClick() {
    extract1("test.tar", "tmp");

    std::vector<int> in;

    QFuture<void> future = QtConcurrent::run(call);
    m_observer.setFuture(future);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFinish() {
  qDebug() << "Done";
}



int spc_verify(unsigned char *msg, unsigned int mlen, unsigned char *sig,
unsigned int siglen, RSA *r)
{
    unsigned char hash[20];
    BN_CTX
    *c;
    int
    ret;
    if (!(c = BN_CTX_new( ))) return 0;
    if (!SHA1(msg, mlen, hash) || !RSA_blinding_on(r, c)) {
        BN_CTX_free(c);
        return 0;
    }
    ret = RSA_verify(NID_sha1, hash, 20, sig, siglen, r);
    RSA_blinding_off(r);
    BN_CTX_free(c);
    return ret;
}
