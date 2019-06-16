#include "../include/client.h"

Client *create_client(int *IDs) {
  char *tmp = NULL;
  char *hexDump = malloc(41);
  char *binDump = malloc(21);
  Client *cl = malloc(sizeof(Client)); // memory for client
  int success = 0;
  if (cl != NULL) {
    cl->ID = IDs[0]++;
    puts("Enter name: ");
    tmp = scanString();
    cl->NAME = malloc(strlen(tmp) + 1); // memory for clients name
    if (cl->NAME != NULL) {
      strcpy_s(cl->NAME, strlen(tmp) + 1, tmp);
    } else {
      perror("AN ERROR OCCURRED");
      exit(-1);
    }
    free(tmp);
    puts("Enter password: ");
    tmp = scanString();
    cl->PASSWD = hashPassword(tmp);
    free(tmp);
  } else {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  return cl;
}

Client *create_client_fromDB(sqlite3 *db) {
  char *name = NULL;
  char *password = NULL;
  char *zErrMsg = NULL;
  char *sql = NULL;
  int hash = 0;
  Client *cl = malloc(sizeof(Client));
  if (cl != NULL) {
    cl->NAME = NULL;
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }

  puts("Please input your login: ");
  name = scanString();
  puts("Please input your password: ");
  password = scanString();
  hash = hashPassword(password);
  free(password);
  sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + intLen(hash) + 1);
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE NAME='%s' AND PASSWD=%d;", name, hash);
  } else {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  sqlite3_exec(db, sql, client_creation_callback, cl, &zErrMsg);
  return cl;
}

int client_creation_callback(Client *cl, int argc, char **argv, char **azColName) {
  cl->ID = stringToInt(argv[0]);
  cl->NAME = malloc(strlen(argv[1]) + 1);
  if (cl->NAME != NULL) {
    strcpy_s(cl->NAME, strlen(argv[1]) + 1, argv[1]);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  cl->PASSWD = stringToInt(argv[2]);
  return 0;
}

void free_client(Client *client) {
  if (client->NAME != NULL) {
    free(client->NAME);
  }
  free(client);
}