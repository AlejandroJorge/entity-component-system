#ifndef ENTITY_H
#define ENTITY_H

typedef enum { CT_TOTAL_UCOMPONENT_TYPES } UComponentType;
typedef enum { CT_TOTAL_DCOMPONENT_TYPES } DComponentType;

typedef void *Component;

typedef struct {
  unsigned int ID;
  Component UComponents[CT_TOTAL_UCOMPONENT_TYPES];
  Component DComponents[CT_TOTAL_DCOMPONENT_TYPES];
} Entity;

Entity *Entity_Create();
void Entity_AppendUComponent(Entity *e, Component c, UComponentType t);
void Entity_AppendDComponent(Entity *e, Component c, DComponentType t);
void Entity_Update(Entity *e);
void Entity_Draw(Entity *e);

typedef struct {
  Entity *entities;
  unsigned int amount_entities;
  unsigned int capacity_entities;
} EntitySystem;

EntitySystem *EntitySystem_Create();
void EntitySystem_AppendEntity(EntitySystem *es, Entity *e);
void EntitySystem_Update(EntitySystem *es);
void EntitySystem_Draw(EntitySystem *es);

#endif // ENTITY_H