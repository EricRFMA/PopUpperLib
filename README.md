PopUpperLib - C++/Qt library to pop up annoying reminder window
Last built with Qt 5.3.0

One entry point, _PopUpperLibStart (`extern "C"`), in `popupperlib_global.h` which takes an argument `const char *` pointer to the string to display. Displays a window, which moves around every two seconds changing color.  Keeps doing that until the "Go Away" button is pressed.
