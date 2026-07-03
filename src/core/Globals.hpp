#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "Scene.hpp"

enum class Mode { SELECT, DRAW_POINT, DRAW_LINE, DRAW_POLYLINE, DRAW_POLYGON };

inline Scene scene;
inline int windowWidth = 800;
inline int windowHeight = 600;
inline Mode currentMode = Mode::DRAW_POINT;

#endif
