#include "../include/sql_manager.h"

void sql_init(sqlite3 *db) {
  char *zErrMsg = 0;
  sqlite3_exec(db, CREATETABLE, NULL, 0, &zErrMsg);
  if (zErrMsg != NULL)
    printf("%s\n", zErrMsg);
}

int default_callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  for (i = 1; i < argc; i++) {
    printf("|| %10s = %12s|| \n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n\n");
  return 0;
}

int item_list_callback(ItemList *data, int argc, char **argv, char **azColname) {
  int i;
  Item *it = malloc(sizeof(Item));
  Item **oldList;
  if (it == NULL) {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  it->ID = stringToInt(argv[0]);
  it->NAME = malloc(strlen(argv[1]) + 1);
  if (it->NAME == NULL) {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  strcpy_s(it->NAME, strlen(argv[1]) + 1, argv[1]);
  it->QUANTITY = stringToInt(argv[2]);
  it->CLIENT_ID = stringToInt(argv[3]);
  data->size++;
  oldList = data->list;
  data->list = realloc(data->list, data->size + sizeof(Item));
  if (data->list == NULL) {
    for (i = 0; i < data->size - 1; i++) {
      free_item(oldList[i]);
    }
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  data->list[data->size - 1] = it;
  return 0;
}

int item_callback(void *data, int argc, char **argv, char **azColName) {
  printf("|| %10s = %12s|| \n", azColName[1], argv[1] ? argv[1] : "NULL");
  printf("|| %10s = %12s|| \n", azColName[2], argv[2] ? argv[2] : "NULL");
  printf("\n\n");
  return 0;
}

int client_callback(void *data, int argc, char **argv, char **azColName) {
  printf("||ID: %4s\tName: %12s||\n", argv[0], argv[1]);
  return 0;
}

int fetchIDs(int *data, int argc, char **argv, char **azColName) {
  data[0] = stringToInt(argv[0]);
  data[1] = stringToInt(argv[1]);
  return 0;
}

void sql_addClient(sqlite3 *db, Client *cl) {
  char *sql = malloc(strlen(INSERTCLIENT) + strlen(cl->NAME) + intLen(cl->PASSWD) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(
        sql, strlen(sql),
        "INSERT INTO CLIENTS (ID, NAME, PASSWD) VALUES(%d, \'%s\', %d);", cl->ID, cl->NAME, cl->PASSWD);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_removeClient(sqlite3 *db, Client *cl) {
  char *sql = malloc(strlen(REMOVECLIENT) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "DELETE FROM CLIENTS WHERE ID=%d;", cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_showAllClients(sqlite3 *db) {
  char *zErrMsg;
  sqlite3_exec(db, SHOWALLCLIENTS, client_callback, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
}

void sql_addItem(sqlite3 *db, Item *it, Client *cl) {
  char *sql = malloc(strlen(INSERTITEM) + intLen(it->ID) + strlen(it->NAME) + intLen(it->QUANTITY) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "INSERT INTO ITEMS (ID, NAME, QUANTITY, CLIENT_ID) VALUES(%d, '%s', %d, %d);", it->ID, it->NAME, it->QUANTITY, cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_removeItem(sqlite3 *db, char *name, Client *cl) {
  char *sql = malloc(strlen(REMOVEITEM) + strlen(name) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE NAME='%s' AND CLIENT_ID=%d;", name, cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_updateItem(sqlite3 *db, Item *it) {
  char *sql = malloc(strlen(UPDATEITEM) + intLen(it->ID) + intLen(it->QUANTITY) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "UPDATE ITEMS SET QUANTITY=%d WHERE ID=%d;", it->QUANTITY, it->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  free(sql);
  sqlite3_free(zErrMsg);
}

void sql_removeAllItems(sqlite3 *db, Client *cl) {
  char *sql = malloc(strlen(REMOVEALLITEMS) + intLen(cl->ID) + 1);
  char *zErrMsg;

  if (sql != NULL) {
    snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE CLIENT_ID=%d;", cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_showItem(sqlite3 *db, Client *cl, char *name) {
  char *sql = malloc(strlen(SHOWITEM) + strlen(name) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE NAME LIKE '%s' AND CLIENT_ID=%d;", name, cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, item_callback, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_setLastIDs(sqlite3 *db, int *IDs) {
  char *zErrMsg;
  sqlite3_exec(db, "SELECT LAST_CLIENT_ID, LAST_ITEM_ID FROM UTILITY;", fetchIDs, IDs, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
}

void sql_showAllItemsOfClient(sqlite3 *db, Client *cl, ItemList *items) {
  char *sql = malloc(strlen(SHOWALLITEMSOFCLIENT) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE CLIENT_ID=%d;", cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, item_list_callback, items, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

void sql_dump_lastIDs(sqlite3 *db, int *IDs) {
  char *zErrMsg;
  char *sql = malloc(strlen(DUMPLASTIDS) + intLen(IDs[0]) + intLen(IDs[1]));
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "UPDATE UTILITY SET LAST_CLIENT_ID=%d, LAST_ITEM_ID=%d", IDs[0], IDs[1]);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
}
