#include "component.h"
#include <raylib.h>
#include <stdlib.h>

#include "entity.h"

// Update components

UC_Position *UC_Position_Create(Vector2 position) {
  UC_Position *component = MemAlloc(sizeof(UC_Position));
  component->position = position;

  return component;
}
void UC_Position_Update(Entity *e) {
  // Do nothing
}

// Draw components

DC_RectangleShape *DC_RectangleShape_Create(Vector2 size, Color color) {
  DC_RectangleShape *component = MemAlloc(sizeof(DC_RectangleShape));
  component->size = size;
  component->color = color;

  return component;
}
void DC_RectangleShape_Draw(Entity *e) {
  // Check required components
  DC_RectangleShape *rectangleShapeComp = e->DComponents[CT_RECTANGLE_SHAPE];
  UC_Position *positionComp = e->UComponents[CT_POSITION];
  if (rectangleShapeComp == NULL || positionComp == NULL)
    return;

  DrawRectangleV(positionComp->position, rectangleShapeComp->size,
                 rectangleShapeComp->color);
}
