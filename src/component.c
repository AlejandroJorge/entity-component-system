#include "component.h"
#include <raylib.h>
#include <raymath.h>
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

UC_Movement *UC_Movement_Create() {
  UC_Movement *component = MemAlloc(sizeof(UC_Movement));
  component->velocity = (Vector2){0, 0};
  component->acceleration = (Vector2){0, 0};

  return component;
}
void UC_Movement_Update(Entity *e) {
  // Check requirements
  UC_Movement *movementComp = e->UComponents[UCT_MOVEMENT];
  UC_Position *positionComp = e->UComponents[UCT_POSITION];
  if (movementComp == NULL || positionComp == NULL)
    return;

  float deltaTime = GetFrameTime();
  positionComp->position =
      Vector2Add(movementComp->velocity, positionComp->position);
  movementComp->velocity =
      Vector2Add(movementComp->acceleration, movementComp->velocity);
}

UC_PlayerControllable *UC_PlayerControllable_Create() {
  UC_PlayerControllable *component = MemAlloc(sizeof(UC_PlayerControllable));
  component->state = PCS_IDLE;
  component->counter = 0;

  return component;
}
void UC_PlayerControllable_Update(Entity *e) {
  // Check requirements
  UC_PlayerControllable *playerControllableComp =
      e->UComponents[UCT_PLAYERCONTROLLABLE];
  UC_Position *positionComp = e->UComponents[UCT_POSITION];
  UC_Movement *movementComp = e->UComponents[UCT_MOVEMENT];
  if (playerControllableComp == NULL || positionComp == NULL ||
      movementComp == NULL)
    return;

#define MOVEMENTFREQ 5
  if (playerControllableComp->counter >= MOVEMENTFREQ) {
    playerControllableComp->counter = 0;
    playerControllableComp->state = PCS_IDLE;
    movementComp->velocity = (Vector2){0, 0};
  }

  switch (playerControllableComp->state) {
  case PCS_IDLE:
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
      playerControllableComp->state = PCS_UP;
    } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
      playerControllableComp->state = PCS_DOWN;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
      playerControllableComp->state = PCS_RIGHT;
    } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
      playerControllableComp->state = PCS_LEFT;
    }
    break;
#define MOVESPEED 5
  case PCS_LEFT:
    movementComp->velocity.x = MOVESPEED;
    break;
  case PCS_RIGHT:
    movementComp->velocity.x = MOVESPEED * -1;
    break;
  case PCS_UP:
    movementComp->velocity.y = MOVESPEED;
    break;
  case PCS_DOWN:
    movementComp->velocity.y = MOVESPEED * -1;
    break;
  }

  if (playerControllableComp->state != PCS_IDLE)
    playerControllableComp->counter++;
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

DC_Shadow *DC_Shadow_Create(Vector2 size, Color color) {
  DC_Shadow *component = MemAlloc(sizeof(DC_Shadow));
  component->size = size;
  component->color = color;

  return component;
}
void DC_Shadow_Draw(Entity *e) {
  // Check required components
  DC_Shadow *shadowComp = e->DComponents[DCT_SHADOW];
  DC_RectangleShape *rectangleShapeComp = e->DComponents[DCT_RECTANGLE_SHAPE];
  UC_Position *positionComp = e->UComponents[UCT_POSITION];
  UC_Size *sizeComp = e->UComponents[UCT_SIZE];
  if (shadowComp == NULL || rectangleShapeComp == NULL ||
      positionComp == NULL || sizeComp == NULL)
    return;

  Vector2 shadowPosition = {positionComp->position.x - shadowComp->size.x,
                            positionComp->position.y + shadowComp->size.y};
  DrawRectangleV(shadowPosition, sizeComp->size, shadowComp->color);
}
