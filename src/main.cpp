#include <stdlib.h>
#include <windows.h>

import std;
import std.compat;
import GameOfLife;
import Utils;

int main(int argc, char **argv) {

  GameOfLife::Utils::setLogFile("tmp.log");
  auto var = GameOfLife::World::Create(GameOfLife::Utils::Position(10, 10));

  var->SetLife(GameOfLife::Utils::Position(4, 4), true);
  var->SetLife(GameOfLife::Utils::Position(4, 5), true);
  var->SetLife(GameOfLife::Utils::Position(5, 4), true);

  var->SetLife(GameOfLife::Utils::Position(7, 7), true);
  var->SetLife(GameOfLife::Utils::Position(7, 6), true);
  var->SetLife(GameOfLife::Utils::Position(6, 7), true);
  while (true) {
    system("cls");
    std::cout << var->ExportToString() << std::endl;
    var->Update();
    Sleep(500);
  }

  return 0;
}
