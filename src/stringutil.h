#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_STRING
#include <string.h>
#endif

struct String {
  char* value;
  size_t capacity;
  size_t length;
};

void StringInit(struct String *s, size_t initial_capacity) {
  s->value = calloc(initial_capacity, sizeof(char));
  s->capacity = initial_capacity;
  s->length = 0;
}

void StringDeinit(struct String *s) {
  free(s->value);
  s->value = NULL;
  s->capacity = 0;
  s->length = 0;
}

void StringAppend(struct String *s, char c) {
  if (s->length + 1 >= s->capacity - 1) {
    while (s->length + 1 >= s->capacity - 1) {
      s->capacity <<= 1;
    }
    s->value = realloc(s->value, s->capacity);
    memset(s->value + s->length, '\0', s->capacity - s->length);
  }
  s->value[s->length] = c;
  s->length += 1;
}

void StringRemove(struct String *s) {
  if (s->length > 0) {
    s->length -= 1;
    s->value[s->length] = '\0';
  }
}

void StringRemoveAt(struct String *s, size_t index) {
  if (s->length > index) {
    for (size_t i = index; i < s->length; i++) {
      s->value[i] = s->value[i + 1];
    }
    s->length -= 1;
    s->value[s->length] = '\0';
  }
}

struct StringList {
  struct String* items;
  size_t capacity;
  size_t length;
};

void StringListInit(struct StringList *sl, size_t initial_capacity) {
  sl->items = (struct String*) malloc(sizeof(struct String) * initial_capacity);
  sl->capacity = initial_capacity;
  sl->length = 0;
  for (size_t i = 0; i < initial_capacity; i++) {
    StringInit(&sl->items[i], 1);
  }
}

void StringListDeinit(struct StringList *sl) {
  for (size_t i = 0; i < sl->length; i++) {
    StringDeinit(&sl->items[i]);
  }
  free(sl->items);
  sl->items = NULL;
  sl->capacity = 0;
  sl->length = 0;
}

void StringListAppend(struct StringList *sl, struct String *s) {
  if (sl->length + 1 >= sl->capacity - 1) {
    while (sl->length + 1 >= sl->capacity - 1) {
      sl->capacity <<= 1;
    }
    sl->items = (struct String*) realloc(sl->items, sizeof(struct String) * sl->capacity);
  }
  sl->items[sl->length] = *s;
  sl->length += 1;
}

void StringListRemove(struct StringList *sl) {
  if (sl->length > 0) {
    sl->length -= 1;
    StringDeinit(&sl->items[sl->length]);
  }
}

#endif
