#ifndef POPPYUPPER_H
#define POPPYUPPER_H

#include <QDialog>
#include <QTimer>
#include <QTimerEvent>
#include <QWidget>
#include <QApplication>

//! \file
//! Declaration of the PoppyUpper object, the main UI object of the application

namespace Ui {
  class PoppyUpper;
}

//! Derived Qt class that represents the dialog box that will scamper across the screen
class PoppyUpper : public QDialog
{
  Q_OBJECT
  
public:
  explicit PoppyUpper(QWidget *parent = 0);
  ~PoppyUpper();
  
  void moveItSomewhere();
  void setLabel(const QString &);
  void setRandomColors();

  //! This event fires periodically to trigger the movement of the dialog box
  //!
  //!
  //! Moving the dialog box consists of four steps:
  //!   * Hide the window
  //!   * Pick a random place to put it
  //!   * Change the colors (forground and background)
  //!   * Force the window to the front (we WANT to be pesky!)
  //!   * Show the window again
  void timerEvent(QTimerEvent *event)
  {
    if (event->timerId() == timeMe.timerId())
      {
        hide();
        moveItSomewhere();
        setRandomColors();

        // Force us to the front!  Yes, it's rude, but it's the way it has to be!
        setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint |  Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
        show();
      }
    else
      QWidget::timerEvent(event);
  }


private:
  std::unique_ptr<Ui::PoppyUpper> ui;
  QBasicTimer timeMe;


public slots:
  void goAwayClicked();
};

#endif // POPPYUPPER_H
