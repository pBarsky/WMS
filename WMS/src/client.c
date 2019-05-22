#include "../include/client.h"

Client *create_client(int *IDs) {
  char *tmp = NULL;
  char *hexDump= malloc(41);
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
    puts("Enter passwd: ");
    tmp = scanString();
    cl->PASSWD = malloc(41);
    if (cl->PASSWD != NULL) {
      //strcpy_s(cl->PASSWD, strlen(tmp) + 1, tmp);
      SHA1(binDump, tmp, strlen(tmp));
      binToHex(hexDump, binDump);
      if (hexDump != NULL) {
        strcpy_s(cl->PASSWD, strlen(hexDump) + 1, hexDump);
      }
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
  char *passwd = NULL;
  char *zErrMsg = NULL;
  char *sql = NULL;
  char *binDump = malloc(21);
  char *hexDump = malloc(41);
  Client *cl = malloc(sizeof(Client));
  if (cl != NULL) {
    cl->NAME = NULL;
    cl->PASSWD = NULL;
  }

  puts("Please input your login: ");
  name = scanString();
  puts("Please input your password: ");
  passwd = scanString();
  SHA1(binDump, passwd, strlen(passwd));
  binToHex(hexDump, binDump);
  if (hexDump != NULL) {
    sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + strlen(hexDump) + 1);
  }
  if (sql != NULL) {
    snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE NAME='%s' AND PASSWD='%s';", name, hexDump);
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
  cl->PASSWD = malloc(strlen(argv[2]) + 1);
  if (cl->PASSWD != NULL) {
    strcpy_s(cl->PASSWD, strlen(argv[2]) + 1, argv[2]);
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
  if (client->PASSWD != NULL) {
    free(client->PASSWD);
  }
  free(client);
}