#include "../include/client.h"

Client *create_client(int *IDs) {
  char *tmp = NULL;
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
    puts("Enter surname: ");
    tmp = scanString();
    cl->SURNAME = malloc(strlen(tmp) + 1);
    if (cl->SURNAME != NULL) {
      strcpy_s(cl->SURNAME, strlen(tmp) + 1, tmp);
    } else {
      perror("AN ERROR OCCURRED");
      exit(-1);
    }
    free(tmp);
  } else {
    perror("AN ERROR OCCURED");
    exit(-1);
  }
  return cl;
}

Client *create_client_fromDB(sqlite3 *db) {
  char *name = NULL;
  char *surname = NULL;
  char *zErrMsg = NULL;
  char *sql = NULL;
  Client *cl = malloc(sizeof(Client));
  cl->NAME = NULL;
  cl->SURNAME = NULL;

  puts("Please input your name: ");
  name = scanString();
  puts("Please input your surname: ");
  surname = scanString();
  sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + strlen(surname) + 1);
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE NAME LIKE '%s' AND SURNAME LIKE '%s';", name, surname);
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
  cl->SURNAME = malloc(strlen(argv[2]) + 1);
  if (cl->SURNAME != NULL) {
    strcpy_s(cl->SURNAME, strlen(argv[2]) + 1, argv[2]);
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }

  return 0;
}

void free_client(Client *client) {
  if (client->NAME != NULL) {
    free(client->NAME);
  }
  if (client->SURNAME != NULL) {
    free(client->SURNAME);
  }
  free(client);
}