#include "../include/sql_manager.h"

void sql_init(sqlite3 *db) {
  char *zErrMsg = 0;
  sqlite3_exec(db, CREATETABLE, default_callback, 0, &zErrMsg);
  if (zErrMsg != NULL)
    printf("%s\n", zErrMsg);
}

int default_callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("|| %10s = %12s|| \n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int client_callback(void *data, int argc, char **argv, char **azColName) {
  printf("||ID: %4s\tName: %12s\tSurname: %12s||\n", argv[0], argv[1], argv[2]);
  return 0;
}

int fetchIDs(int *data, int argc, char **argv, char **azColName) {
  data[0] = stringToInt(argv[0]);
  data[1] = stringToInt(argv[1]);
  return 0;
}

void sql_addClient(sqlite3 *db, Client *cl) {
  char *sql = malloc(strlen(INSERTCLIENT) + strlen(cl->NAME) + strlen(cl->SURNAME) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(
        sql, strlen(sql),
        "INSERT INTO CLIENTS (ID, NAME, SURNAME) VALUES(%d, \'%s\', \'%s\');", cl->ID, cl->NAME, cl->SURNAME);
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

// void sql_updateClient(sqlite3* db, Client* cl) {
//  char* sql = malloc(strlen(UPDATECLIENT) + intLen(cl->ID) + 1);
//  char *zErrMsg, *newName, *newSurname;
//  puts("Please enter new name for the client.");
//  newName = scanString();
//  puts("Please enter new surname for the client");
//  newSurname = scanString();
//
//  if (sql != NULL) {
//    snprintf(sql, strlen(sql),
//             "UPDATE CLIENTS SET NAME='%s', SURNAME='%s' WHERE ID=%d;", newName, newSurname, cl->ID);
//  } else {
//    perror("AN ERROR OCCURRED");
//    exit(-1);
//  }
//  sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
//  if (zErrMsg) {
//    puts(zErrMsg);
//  }
//  sqlite3_free(zErrMsg);
//  free(sql);
//}

//void sql_showClient(sqlite3 *db, Client *cl) {
//  char *sql = malloc(strlen(SHOWCLIENT) + intLen(cl->ID) + 1);
//  char *zErrMsg;
//  if (sql != NULL) {
//    snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE ID=%d;", cl->ID);
//  } else {
//    perror("AN ERROR OCCURRED");
//    exit(-1);
//  }
//  sqlite3_exec(db, sql, client_callback, 0, &zErrMsg);
//  if (zErrMsg) {
//    puts(zErrMsg);
//  }
//  sqlite3_free(zErrMsg);
//  free(sql);
//}

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

void sql_removeItem(sqlite3 *db, char* name, Client* cl) {
  char *sql = malloc(strlen(REMOVEITEM) + strlen(name) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE NAME LIKE '%s' AND CLIENT_ID=%d;", name, cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
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
  sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
  free(sql);
}

//void sql_showItem(sqlite3 *db, Item *it) {
//  char *sql = malloc(strlen(SHOWITEM) + intLen(it->ID) + 1);
//  char *zErrMsg;
//  if (sql != NULL) {
//    snprintf(sql, strlen(sql), "SELET * FROM ITEM WHERE ID=%d;", it->ID);
//  } else {
//    perror("AN ERROR OCCURRED");
//    exit(-1);
//  }
//  sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
//  if (zErrMsg) {
//    puts(zErrMsg);
//  }
//  sqlite3_free(zErrMsg);
//  free(sql);
//}

void sql_setLastIDs(sqlite3 *db, int *IDs) {
  char *zErrMsg;
  sqlite3_exec(db, "SELECT LAST_CLIENT_ID, LAST_ITEM_ID FROM UTILITY;", fetchIDs, IDs, &zErrMsg);
  if (zErrMsg) {
    puts(zErrMsg);
  }
  sqlite3_free(zErrMsg);
}

//void sql_showAllItems(sqlite3 *db) {
//  char *zErrMsg;
//  int success = 0;
//  sqlite3_exec(db, SHOWALLCLIENTS, default_callback, 0, &zErrMsg);
//  if (zErrMsg) {
//    puts(zErrMsg);
//  }
//  sqlite3_free(zErrMsg);
//}

void sql_showAllItemsOfClient(sqlite3 *db, Client *cl) {
  char *sql = malloc(strlen(SHOWALLITEMSOFCLIENT) + intLen(cl->ID) + 1);
  char *zErrMsg;
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE CLIENT_ID=%d;", cl->ID);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
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
}
