#include "Scene.hpp"
#include "NotPaint.hpp"

int main(int argc, char* argv[]) {
  play_scene<NotPaint>(argc, argv, "NotPaint");
}
