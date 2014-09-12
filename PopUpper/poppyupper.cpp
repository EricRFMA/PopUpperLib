#include "poppyupper.h"
#include "ui_poppyupper.h"
#include "utilities.h"
#include "CSScolor.h"

#include <QtDebug>
#include <QScreen>
#include <QRect>
#include <QLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QPushButton>

//! \file poppyupper.cpp
//! Contains definitions for class PoppyUpper, which manipulates the dialog box that's hopping around
//! the screen.

//! Constructor for the primary object for this application. Takes the standard Qt parent object argument
PoppyUpper::PoppyUpper(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PoppyUpper)
{
  ui->setupUi(this);
  timeMe.start(3000, this);  // wait for three seconds, then move and recolor
}

PoppyUpper::~PoppyUpper()
{
  ui.reset();  // Since this is a unique_ptr, this is how you release it.  No destructor for it
}

//! Set the label (text) in the wandering dialog box.  Takes care of sizing the dialog so the text will
//! fit
//! Also has to create & position the "OK" button
void PoppyUpper::setLabel(const QString &theLabel)
{
  // create a new label, and resize everything to fit
  QVBoxLayout *layout = new QVBoxLayout;
  QLabel *myLabel = new QLabel(theLabel, this);
  QPushButton *goAway = new QPushButton("Go Away!", this);

  goAway->setAutoDefault(true);
  connect(goAway, &QPushButton::clicked,
          this, &PoppyUpper::goAwayClicked);

  layout->addWidget(myLabel);
  layout->addWidget(goAway);
  layout->setSpacing(10);  // make some elbow room
  setLayout(layout);
  adjustSize();
}

//! Picks random colors for foreground and backgound on the dialog box.  Tries to pick contrasting colors
//! so the text remains visible.
void PoppyUpper::setRandomColors()
{
  // pick random foreground/background colors (but not the same foreground and background!)
  // color vector has CSScolors.size() elements, so indexes are zero to size()-1
  Randoid colorRandThing(0, CSSColors.size() - 1);

  unsigned int bgInd = colorRandThing.getRand();
  QString backgroundColorStr = CSSColors[bgInd];

  unsigned int textInd = colorRandThing.getRand();
  QString textColorStr = CSSColors[textInd];

  // Make sure they're not the same and have suitable contrast
  // we'll try using the lightness value from the HSL representation of the color,
  // and make sure they differ by at least 125
  QColor bgColor(backgroundColorStr);
  QColor txtColor(textColorStr);

  while (abs(bgColor.lightness() - txtColor.lightness()) < 125)
  {
      textInd = colorRandThing.getRand();
      textColorStr = CSSColors[textInd];
      txtColor = QColor(textColorStr);
  }

  QPalette thePalette;

  thePalette.setColor(QPalette::Window, backgroundColorStr);
  thePalette.setColor(QPalette::WindowText, textColorStr);
  thePalette.setColor(QPalette::Text, textColorStr);

  setPalette(thePalette);

}

//! Pick a random place on the screen to move the dialog.  This is supposed to work on multiple monitors
//! but I've only been able to test it with two.
void PoppyUpper::moveItSomewhere()
{
  // get the desktop object so we can get geometry to figure out where this will land
  QDesktopWidget  *theDesktop = QApplication::desktop();

  // Pick from any number of screens!
  unsigned int screens = theDesktop->screenCount();
  unsigned int whichScreen = Randoid::getRand(0, screens - 1);  // screens start at zero

  const QRect screenGeometry = theDesktop->availableGeometry(whichScreen);
  const QRect dialogGeometry = this->geometry();

  bool positioned = false;

  //! Pick a random point on the screen
  QRect newRect;
  Randoid screenRandThingX(screenGeometry.topLeft().x(), screenGeometry.topRight().x());
  Randoid screenRandThingY(screenGeometry.topLeft().y(), screenGeometry.bottomLeft().y());

  //! \todo This loop can probably be eliminated and replaced with some calculation that would choose random coordinates
  //! such that the dialog doesn't get clipped by an edge of the screen
  do
    {
      // pick a point on the screen... this will be the top left point
      QPoint newLocation(screenRandThingX.getRand(),
                           screenRandThingY.getRand());

      qDebug() << "newLocation " << newLocation;

      // Now figure out the bottom right point for the new QRect
      QPoint bottomRight(newLocation.x() + dialogGeometry.width() - 1,
                         newLocation.y() + dialogGeometry.height() - 1);

      // Now create a QRect that represents the dialog at this position
      newRect = QRect(newLocation, bottomRight);

      qDebug() << "newRect " << newRect;

      // Now, if this new rectangle is completely contained within the screen geometry, we're done!
      positioned = screenGeometry.contains(newRect, true);

      // If not, we try again
    } while (!positioned);

  qDebug() << "Old location: " << dialogGeometry;
  qDebug() << "New location: " << newRect;

  setGeometry(newRect);
}

void PoppyUpper::goAwayClicked()
{
    qDebug("goAwayClicked has been clicked");
    timeMe.stop();
    this->close();
}
