#include "../include/menu.h"
int main(int argc, char* argv[]) {
  sqlite3* db;
  Client* cl = malloc(sizeof(Client*));
  char* zErrMsg = 0;
  int rc;
  int lastIDs[2] = {0};
  char finished = 0;

  rc = sqlite3_open("test.db", &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return 0;
  } else {
    fprintf(stderr, "Opened database successfully\n");
  }
  sql_init(db);
  sql_setLastIDs(db, lastIDs);
  drawEntryMenu();
  getChoiceEntry(db, &cl, lastIDs);
  do {
    drawMenu();
    finished = getChoice(db, &cl, lastIDs);
  } while (finished == 0);
  if (cl != NULL)
  {
      free_client(cl);
  }
  else
  {
      perror("AN ERROR OCCURRED");
      exit(-1);
  }
  sql_dump_lastIDs(db, lastIDs);
  sqlite3_close(db);
  system("pause");
  return 0;
}