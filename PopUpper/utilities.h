#ifndef UTILITIES_H
#define UTILITIES_H
#include <random>
#include <QDateTime>

//! \file utilities.h
//! Contains generally used utility classes, Randoid, in particular

using namespace std;

//! Utility class for static general utility functions
class Utilities
{
public:
  Utilities();
};

//! Random number generator object, wraps uniform_int_distribution and default_random_engine
class Randoid
{
public:
  //! Creates the random number generator object
  //!
  //! Distributed between [a, b] inclusive, as integers
  Randoid(unsigned int low, unsigned int high) : dist(low, high)
  {
    // use time as random seed. currentMSecsSinceEpoch returns a q64int... might get truncation warning on some platforms
    engine.seed(QDateTime::currentMSecsSinceEpoch());
  }

  //! Returns an unsigned int from this object's random number generator
  unsigned int getRand()
  {
    return dist(engine);
  }

  //! One-shot get a random number function
  //!
  //! Creates a local random_engine object for a one-shot generation of a single
  //! random number
  static unsigned int getRand(unsigned int low, unsigned int high)
  {
    uniform_int_distribution<unsigned> dist(low,high);
    default_random_engine engine;
    engine.seed(QDateTime::currentMSecsSinceEpoch());
    return dist(engine);
  }

private:
  uniform_int_distribution<unsigned> dist;
  default_random_engine engine;
};

#endif // UTILITIES_H
