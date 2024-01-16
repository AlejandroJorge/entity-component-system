#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

void MockEntitySystem(EntitySystem *es) {
  Entity *mockEntity = Entity_Create();
  EntitySystem_AppendEntity(es, mockEntity);
}

int main(int argc, char *argv[]) {

  InitWindow(800, 600, "ECS in C");

  EntitySystem *es = EntitySystem_Create();

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    EntitySystem_Update(es);
    BeginDrawing();
    ClearBackground(DARKGRAY);
    EntitySystem_Draw(es);
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
