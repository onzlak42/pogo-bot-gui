#include "App.h"
#include <time.h>

int main()
{
  srand(static_cast<unsigned int>(time(0)));

  App game;
  return game.Run();
}
