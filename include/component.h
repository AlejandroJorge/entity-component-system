#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"
#include <raylib.h>

// Update Components

typedef struct {
  Vector2 position;
} UC_Position;

UC_Position *UC_Position_Create(Vector2 position);
void UC_Position_Update(Entity *e);

// Draw Components

typedef struct {
  Vector2 size;
  Color color;
} DC_RectangleShape;

DC_RectangleShape *DC_RectangleShape_Create(Vector2 size, Color color);
void DC_RectangleShape_Draw(Entity *e);

#endif // !COMPONENT_H