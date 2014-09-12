#include "popupperlib.h"
#include "PopUpper/poppyupper.h"
#include <QApplication>
#include <QThread>
#include "Runner.hpp"
#include <QtDebug>



void POPUPPERLIBSHARED_EXPORT _PopUpperLibStart(const char *label)
{
  Runner *theRunner;

  QString dialogString;

  // create QApplication
  int argc = 0;
  const QApplication *a = new QApplication(argc, nullptr);

  if (label == NULL || *label == '\0')
    dialogString = "Default label... so sad...";
  else
    dialogString = label;

  // Conect the Runner object to a new thread
  QThread* thread = new QThread;

  // OK, set up the thread and let it loose...
  theRunner = new Runner(dialogString, *a, thread);

  // This code is taken from http://qt-project.org/wiki/QThreads_general_usage
  //theRunner->moveToThread(thread);

  // "The first connect() line hooks up the error message signal from the worker
  // to an error processing function in the main thread. The second connects
  // the thread’s started() signal to the processing() slot in the worker, causing it to start."

  // Since there's no object handy that has an errorString function, punting on
  // this for now.
  // theRunner->connect(theRunner, SIGNAL(error(QString)), thread, SLOT(errorString(QString)));


  // "when the worker instance emits finished(), as we did in the example, it
  //  will signal the thread to quit, i.e. shut down. We then mark the worker
  //  instance using the same finished() signal for deletion. Finally, to prevent
  //  nasty crashes because the thread hasn’t fully shut down yet when it is
  //  deleted, we connect the finished() of the thread (not the worker!) to its own
  //  deleteLater() slot. This will cause the thread to be deleted only after it
  //  has fully shut down."

  thread->start();

  a->exec();

  qDebug() << "After QApplication exec " << (unsigned long)(void *)a << "\n";

  // We can't return until we're done, or else multiple requests could come in causing
  // pandemonium... or worse!
  while (thread->isRunning())
  {
      thread->quit();  //
  }


  delete theRunner;
  delete thread;
}

void Runner::process()
{
qDebug() << "In Runner::process '" << messageLabel << (unsigned long)(void *)this << "'\n";

  pup.setRandomColors();
  pup.setLabel(messageLabel);
  pup.moveItSomewhere();
  QObject::connect(&pup, &QDialog::finished, /* Lambda */
                   [=] () {
      qDebug() << "pup " << (unsigned long)(void *)&pup << " signalled finished\n";
  });

  pup.show();

  qDebug() << "Done processing '" << messageLabel << "'\n";
}

void POPUPPERLIBSHARED_EXPORT _PopUpperLibStop()
{
  // Here goes nothing... there's supposed to be one qApp object
  // corresponding to the one QApplication that's running.  So,
  // telling it to exit should stop the PopUppering.
  qApp->exit(0);
}

void Runner::notifyFinished()
{
    qDebug()<< "Notify finished Runner " << (unsigned long)(void *)this << "\n";
}
