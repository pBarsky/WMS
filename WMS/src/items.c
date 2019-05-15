#include "../include/items.h"

Item *create_item(Client *cl, int *IDs) {
  char *tmp = NULL;
  Item *item = malloc(sizeof(Item)); // memory for client
  if (item != NULL) {
    item->ID = IDs[1]++;
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }

  puts("Enter item name: ");
  tmp = scanString();
  item->NAME = malloc(strlen(tmp) + 1); // memory for clients name
  if (item->NAME != NULL) {
    strcpy_s(item->NAME, strlen(tmp) + 1, tmp);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  free(tmp);
  puts("Enter item quantity: ");
  item->QUANTITY = scanInt();
  item->CLIENT_ID = cl->ID;
  return item;
}

Item *create_item_fromDB(sqlite3 *db, Client *cl, char *name) {
  char *zErrMsg = NULL;
  char *sql = NULL;
  Item *it = malloc(sizeof(Item));
  sql = malloc(strlen(SEARCHITEM) + strlen(name) + intLen(cl->ID) + 1);
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE NAME LIKE '%s' AND CLIENT_ID=%d;", name, cl->ID);
  } else {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  sqlite3_exec(db, sql, item_creation_callback, it, &zErrMsg);
  return it;
}

int item_creation_callback(Item *it, int argc, char **argv, char **azColName) {
  it->ID = stringToInt(argv[0]);
  it->NAME = malloc(strlen(argv[1]) + 1);
  if (it->NAME != NULL) {
    strcpy_s(it->NAME, strlen(argv[1]) + 1, argv[1]);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  it->QUANTITY = stringToInt(argv[2]);
  it->CLIENT_ID = stringToInt(argv[3]);
  return 0;
}

void free_item(Item *item) {
  if (item->NAME != NULL) {
    free(item->NAME);
  }
  free(item);
}