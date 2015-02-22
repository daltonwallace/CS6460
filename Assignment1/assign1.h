#ifndef ASSIGN1_H
#define ASSIGN1_H
struct elt {
  char val;
  struct elt *link;
};
enum format_t {
  OCT = 66, BIN, HEX
};

unsigned long byte_sort (unsigned long arg);
unsigned long nibble_sort (unsigned long arg);
struct elt *name_list (void);
void convert (enum format_t mode, unsigned long value);
void draw_me (void);

#endif
