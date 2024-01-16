#include "component.h"
#include "component_types.h"
#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

void MockEntitySystem(EntitySystem *es) {
  Entity *mockEntity = Entity_Create();
  UC_Position *positionComponent = UC_Position_Create((Vector2){150, 50});
  UC_Size *sizeComponent = UC_Size_Create((Vector2){80, 80});
  DC_RectangleShape *rectangleShapeComponent = DC_RectangleShape_Create(BLUE);
  Entity_AppendUComponent(mockEntity, positionComponent, UCT_POSITION);
  Entity_AppendUComponent(mockEntity, sizeComponent, UCT_SIZE);
  Entity_AppendDComponent(mockEntity, rectangleShapeComponent,
                          DCT_RECTANGLE_SHAPE);
  EntitySystem_AppendEntity(es, mockEntity);
}

int main(int argc, char *argv[]) {

  InitWindow(800, 600, "ECS in C");

  EntitySystem *es = EntitySystem_Create();
  MockEntitySystem(es);

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    EntitySystem_Update(es);
    BeginDrawing();
    DrawFPS(15, 15);
    ClearBackground(DARKGRAY);
    EntitySystem_Draw(es);
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
