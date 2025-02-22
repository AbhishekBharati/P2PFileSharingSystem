#ifndef UTILS_H
#define UTILS_H

// Function Declarations :-
void log_error(const char *message); // Logs error to a file
void handle_error(const char *message); // Logs error and terminates the Program
void *safe_malloc(size_t size); // Safely Allocates the Memory                                

#endif //UTILS_H
