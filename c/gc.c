#include "frame.h"
#include "memory_allocator.h"
#include "printf.h"

static void walk_address(void * address);

static void walk_object(struct objectref * objectref)
{
  if (objectref->tag.mark != 0)
    return;
  objectref->tag.mark = 1;

  for (int i = 0; i < objectref->class_entry->instance_fields_count; i++) {
    void * address = objectref->aref[i];
    walk_address(address);
  }
}

static void walk_ref_array(struct arrayref * arrayref)
{
  if (arrayref->tag.mark != 0)
    return;
  arrayref->tag.mark = 1;

  if (arrayref->class_entry == nullptr) {
    // this is an array of arrayrefs
    for (int i = 0; i < arrayref->length; i++) {
      if (arrayref->aref[i] != nullptr) {
        walk_ref_array(arrayref->aref[i]);
      }
    }
  } else {
    // this is an array of objectrefs
    for (int i = 0; i < arrayref->length; i++) {
      if (arrayref->oref[i] != nullptr) {
        walk_object(arrayref->oref[i]);
      }
    }
  }
}

static void walk_prim_array(struct arrayref * arrayref)
{
  if (arrayref->tag.mark != 0)
    return;
  arrayref->tag.mark = 1;
}

static void walk_address(void * address)
{
  if (address == nullptr)
    return;

  if (!memory_is_allocated(address))
    return;

  struct tag * tag = (struct tag *)address;

  if (tag->type == TAG_TYPE_OBJECT) {
    walk_object((struct objectref *)address);
  } else if (tag->type == TAG_TYPE_REF_ARRAY) {
    walk_ref_array((struct arrayref *)address);
  } else if (tag->type == TAG_TYPE_PRIM_ARRAY) {
    walk_prim_array((struct arrayref *)address);
  } else {
    assert(false);
  }
}

static void walk_frame(struct frame * frame)
{
  int num_local_variables = frame->code_attribute->max_locals;
  int num_stack_variables = frame->operand_stack_ix;

  for (int i = 0; i < num_local_variables; i++) {
    void * address = (void *)frame->local_variable[i];
    walk_address(address);
  }

  for (int i = 0; i < num_stack_variables; i++) {
    void * address = (void *)frame->operand_stack[i];
    walk_address(address);
  }
}

static void walk_static_fields(struct class_entry * class_entry)
{
  for (int i = 0; i < class_entry->static_fields_count; i++) {
    void * address = (void *)class_entry->static_fields[i];
    walk_address(address);
  }
}

static void walk_string_attributes(struct class_entry * class_entry)
{
  struct class_file * class_file = class_entry->class_file;
  for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
    struct constant * constant = &class_file->constant_pool[i];
    if (constant->tag != CONSTANT_String)
      continue;

    struct objectref * objectref = class_entry->attribute_entry[i].string_objectref;
    if (objectref != nullptr) {
      walk_object(objectref);
    }
  }
}

static void walk_class_hash_table_entry(struct hash_table_entry * entry)
{
  if (entry->key == nullptr)
    return;

  struct class_entry * class_entry = (struct class_entry *)entry->value;
  assert(class_entry != nullptr);
  walk_static_fields(class_entry);

  walk_string_attributes(class_entry);

  if (entry->next != nullptr)
    walk_class_hash_table_entry(entry->next);
}

static void walk_class_hash_table(int length, struct hash_table_entry * entry)
{
  for (int i = 0; i < length; i++)
    walk_class_hash_table_entry(&entry[i]);
}

static void walk_vm(struct vm * vm)
{
  walk_class_hash_table(vm->class_hash_table.length,
                        vm->class_hash_table.entry);

  for (int i = 0; i < vm->frame_stack.ix; i++) {
    walk_frame(&vm->frame_stack.frame[i]);
  }
}

void gc_mark(struct vm * vm)
{
  walk_vm(vm);
}

static void sweep_address(void * address)
{
  struct tag * tag = (struct tag *)address;
  //printf("%p mark: %d\n", address, tag->mark);
  int mark = tag->mark;
  tag->mark = 0;
  if (mark == 0) {
    memory_free(address);
  }
}

void gc_sweep()
{
  memory_iterate_allocated(sweep_address);
}

void memory_print_free_list();

void gc_run(struct vm * vm)
{
  gc_mark(vm);
  gc_sweep();
  //memory_print_free_list();
}
