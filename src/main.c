#include "component.h"
#include "component_types.h"
#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

void AddMockComponent() {
  Entity *mockEntity = Entity_Create();
  UC_Transform *transformComponent =
      UC_Transform_Create((Vector2){0, 0}, (Vector2){50, 50}, 1);
  Entity_AppendUComponent(mockEntity, transformComponent, UCT_TRANSFORM);
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

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    EntitySystem_Update();

    if (IsKeyDown(KEY_SPACE)) {
      AddMockComponent();
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);
    EntitySystem_Draw();
    DrawFPS(15, 15);
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
