#include "component.h"
#include <raylib.h>
#include <stdlib.h>

#include "component_types.h"
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

UC_Size *UC_Size_Create(Vector2 size) {
  UC_Size *component = MemAlloc(sizeof(UC_Size));
  component->size = size;

  return component;
}
void UC_Size_Update(Entity *e) {
  // Do nothing
}

// Draw components

DC_RectangleShape *DC_RectangleShape_Create(Color color) {
  DC_RectangleShape *component = MemAlloc(sizeof(DC_RectangleShape));
  component->color = color;

  return component;
}
void DC_RectangleShape_Draw(Entity *e) {
  // Check required components
  DC_RectangleShape *rectangleShapeComp = e->DComponents[DCT_RECTANGLE_SHAPE];
  UC_Position *positionComp = e->UComponents[UCT_POSITION];
  UC_Size *sizeComp = e->UComponents[UCT_SIZE];
  if (rectangleShapeComp == NULL || positionComp == NULL || sizeComp == NULL)
    return;

  DrawRectangleV(positionComp->position, sizeComp->size,
                 rectangleShapeComp->color);
}
