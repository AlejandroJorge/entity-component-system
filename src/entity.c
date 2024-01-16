#include "entity.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * [TODO] Entity ID assignment
 * [TODO] UComponents mux
 * [TODO] DComponents mux
 * */

Entity *Entity_Create() {
  Entity *e = MemAlloc(sizeof(Entity));
  for (unsigned int i = 0; i < CT_TOTAL_UCOMPONENT_TYPES; i++) {
    e->UComponents[i] = NULL;
  }
  for (unsigned int i = 0; i < CT_TOTAL_DCOMPONENT_TYPES; i++) {
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
  for (unsigned int i = 0; i < CT_TOTAL_UCOMPONENT_TYPES; i++) {
    switch (i) {}
  }
}
void Entity_Draw(Entity *e) {
  for (unsigned int i = 0; i < CT_TOTAL_DCOMPONENT_TYPES; i++) {
    switch (i) {}
  }
}

EntitySystem *EntitySystem_Create() {
  EntitySystem *es = MemAlloc(sizeof(EntitySystem));
  es->entities = NULL;
  es->amount_entities = 0;
  es->capacity_entities = 0;

  return es;
}
#define JUMPSIZE 5
void EntitySystem_AppendEntity(EntitySystem *es, Entity *e) {
  if (es->amount_entities == es->capacity_entities) {
    es->entities = MemRealloc(
        es->entities, sizeof(Component) * (es->capacity_entities + JUMPSIZE));
    es->capacity_entities += JUMPSIZE;
  }
  es->entities[es->amount_entities] = *e;
  es->amount_entities++;

  MemFree(e);
  e = es->entities + es->amount_entities - 1;
}
void EntitySystem_Update(EntitySystem *es) {
  for (unsigned int i = 0; i < es->amount_entities; i++) {
    Entity_Update(&es->entities[i]);
  }
}
void EntitySystem_Draw(EntitySystem *es) {
  for (unsigned int i = 0; i < es->amount_entities; i++) {
    Entity_Draw(&es->entities[i]);
  }
}
