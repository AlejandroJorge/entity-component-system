#include "component.h"
#include "component_types.h"
#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

void MockEntitySystem() {
  Entity *mockEntity = Entity_Create();
  UC_Position *positionComponent = UC_Position_Create((Vector2){150, 50});
  Entity_AppendUComponent(mockEntity, positionComponent, UCT_POSITION);
  UC_Size *sizeComponent = UC_Size_Create((Vector2){200, 200});
  Entity_AppendUComponent(mockEntity, sizeComponent, UCT_SIZE);
  DC_RectangleShape *rectangleShapeComponent = DC_RectangleShape_Create(BLUE);
  Entity_AppendDComponent(mockEntity, rectangleShapeComponent,
                          DCT_RECTANGLE_SHAPE);
  DC_Shadow *shadowComp = DC_Shadow_Create((Vector2){10, 10}, BLACK);
  Entity_AppendDComponent(mockEntity, shadowComp, DCT_SHADOW);
  UC_Movement *movementComp = UC_Movement_Create();
  Entity_AppendUComponent(mockEntity, movementComp, UCT_MOVEMENT);
  UC_PlayerControllable *playerControllableComp =
      UC_PlayerControllable_Create();
  Entity_AppendUComponent(mockEntity, playerControllableComp,
                          UCT_PLAYERCONTROLLABLE);

  EntitySystem_AppendEntity(mockEntity);
}

int main(int argc, char *argv[]) {

  InitWindow(800, 600, "ECS in C");
  EntitySystem_Init();
  MockEntitySystem();

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    EntitySystem_Update();
    BeginDrawing();
    DrawFPS(15, 15);
    ClearBackground(DARKGRAY);
    EntitySystem_Draw();
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
