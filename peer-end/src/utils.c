#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Function to log errors to a file :-
void log_error(const char *message){
  FILE *log_file = fopen("error_log.txt", "a");
  if(log_file == NULL){
    perror("Failed to Open Log File");
    return;
  } 
  fprintf(log_file, "Error : %s\n", message);
  fclose(log_file);
}

// Function to handle errors and terminate the program :-
void handle_error(const char *message){
  log_error(message); // Log the error to file :-
  fprintf(stderr, "Error: %s\n", message); // Print error to stderr :-
  exit(EXIT_FAILURE); // Exit the program with failure status 
}

// Function to safely Allocate memory :-
void *safe_malloc(size_t size){
  void *ptr = malloc(size);
  if(ptr == NULL){
    handle_error("Memory Allocation failed");
  }
  return ptr;
}
