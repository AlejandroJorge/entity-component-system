#include "component.h"
#include "component_types.h"
#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

void MockEntitySystem(EntitySystem *es) {
  Entity *mockEntity = Entity_Create();
  UC_Position *positionComponent = UC_Position_Create((Vector2){150, 50});
  DC_RectangleShape *rectangleShapeComponent =
      DC_RectangleShape_Create((Vector2){60, 60}, BLUE);
  Entity_AppendUComponent(mockEntity, positionComponent, CT_POSITION);
  Entity_AppendDComponent(mockEntity, rectangleShapeComponent,
                          CT_RECTANGLE_SHAPE);
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
    ClearBackground(DARKGRAY);
    EntitySystem_Draw(es);
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
