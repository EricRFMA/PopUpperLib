#ifndef RUNNER_HPP
#define RUNNER_HPP
#include <QObject>
#include <QThread>
#include "../PopUpper/poppyupper.h"
#include <QTDebug>
class Runner : public QObject
{
  Q_OBJECT
  // This just overrides the process method to setup and run the PopUpper code in the library
  // The caller of this routine should be able to return and leave the PopUpper running.
  // This method will wait for the thread to finish, because returning from this method ends the thread
public:
  Runner(const QString label, const QApplication &a, QThread *thread)
  {
    thisQApp = &a;
    messageLabel = label;
    connect(thread, SIGNAL(started()), this, SLOT(process()));
    connect(thread, SIGNAL(finished()), this, SLOT(notifyFinished()));
  }

  ~Runner()
  {
      qDebug() << "Runner destructor called " << (unsigned long)(void *)this << "\n";
  }

public slots:
  void process();
  void notifyFinished();

signals:
  void finished();
  void error(QString err);

private:
  QString messageLabel;
  const QApplication *thisQApp;
  PoppyUpper pup;

};


#endif // RUNNER_HPP
