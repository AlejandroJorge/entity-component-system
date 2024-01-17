#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"
#include <raylib.h>

// ==============================================================================
// Update Components
// ==============================================================================

typedef struct {
  Vector2 position;
  Vector2 localSize;
  float scale;
} UC_Transform;

UC_Transform *UC_Transform_Create(Vector2 position, Vector2 localSize,
                                  float scale);
void UC_Transform_Update(Entity *e);

typedef struct {
  Vector2 velocity;
  Vector2 acceleration;
} UC_Movement;

UC_Movement *UC_Movement_Create();
void UC_Movement_Update(Entity *e);

typedef enum {
  PCS_RIGHT,
  PCS_LEFT,
  PCS_UP,
  PCS_DOWN,
  PCS_IDLE
} PlayerControllableState;

typedef struct {
  PlayerControllableState state;
  unsigned int counter;
} UC_PlayerControllable;

UC_PlayerControllable *UC_PlayerControllable_Create();
void UC_PlayerControllable_Update(Entity *e);

// ==============================================================================
// Draw Components
// ==============================================================================

typedef struct {
  Color color;
} DC_RectangleShape;

DC_RectangleShape *DC_RectangleShape_Create(Color color);
void DC_RectangleShape_Draw(Entity *e);

typedef struct {
  Color color;
  Vector2 size;
} DC_Shadow;

DC_Shadow *DC_Shadow_Create(Vector2 size, Color color);
void DC_Shadow_Draw(Entity *e);

#endif // !COMPONENT_H
