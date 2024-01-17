#include "entity.h"
#include "component.h"
#include "component_types.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * [TODO] Entity ID assignment
 * */

EntitySystem entitySystem;

Entity *Entity_Create() {
  Entity *e = MemAlloc(sizeof(Entity));
  for (UComponentType i = 0; i < UCT_TOTAL_UCOMPONENT_TYPES; i++) {
    e->UComponents[i] = NULL;
  }
  for (DComponentType i = 0; i < DCT_TOTAL_DCOMPONENT_TYPES; i++) {
    e->DComponents[i] = NULL;
  }

  return e;
}
void Entity_AppendUComponent(Entity *e, Component c, UComponentType t) {
  if (e->UComponents[t] != NULL) {
    printf("[ERROR] Couldn't append UComponent of type %d to Entity with ID "
           "%d, there's already the same component\n",
           t, e->ID);
    exit(1);
  }
  e->UComponents[t] = c;
}
void Entity_AppendDComponent(Entity *e, Component c, DComponentType t) {
  if (e->DComponents[t] != NULL) {
    printf("[ERROR] Couldn't append DComponent of type %d to Entity with ID "
           "%d, there's already the same component\n",
           t, e->ID);
    exit(1);
  }
  e->DComponents[t] = c;
}
void Entity_Update(Entity *e) {
  for (UComponentType i = 0; i < UCT_TOTAL_UCOMPONENT_TYPES; i++) {
    switch (i) {
    case UCT_TRANSFORM:
      UC_Transform_Update(e);
      break;
    case UCT_MOVEMENT:
      UC_Movement_Update(e);
      break;
    case UCT_PLAYERCONTROLLABLE:
      UC_PlayerControllable_Update(e);
      break;
    case UCT_TOTAL_UCOMPONENT_TYPES:
      break;
    }
  }
}
void Entity_Draw(Entity *e) {
  for (DComponentType i = 0; i < DCT_TOTAL_DCOMPONENT_TYPES; i++) {
    switch (i) {
    case DCT_RECTANGLE_SHAPE:
      DC_RectangleShape_Draw(e);
      break;
    case DCT_SHADOW:
      DC_Shadow_Draw(e);
      break;
    case DCT_TOTAL_DCOMPONENT_TYPES:
      break;
    }
  }
}

void EntitySystem_Init() {
  entitySystem.entities = NULL;
  entitySystem.amount_entities = 0;
  entitySystem.capacity_entities = 0;
}
#define JUMPSIZE 5
void EntitySystem_AppendEntity(Entity *e) {
  if (entitySystem.amount_entities == entitySystem.capacity_entities) {
    entitySystem.entities = MemRealloc(
        entitySystem.entities,
        sizeof(Component) * (entitySystem.capacity_entities + JUMPSIZE));
    entitySystem.capacity_entities += JUMPSIZE;
  }
  entitySystem.entities[entitySystem.amount_entities] = e;
  entitySystem.amount_entities++;
}
void EntitySystem_Update() {
  for (unsigned int i = 0; i < entitySystem.amount_entities; i++) {
    Entity_Update(entitySystem.entities[i]);
  }
}
void EntitySystem_Draw() {
  for (unsigned int i = 0; i < entitySystem.amount_entities; i++) {
    Entity_Draw(entitySystem.entities[i]);
  }
}
