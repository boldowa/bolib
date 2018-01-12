/**
 * libfile.h
 */

bool fexists(const char* const);
bool direxists(const char* const);
void gettmpdir(char**);
bool makedir(const char* const);
char* getworkdir(const char* const);
char* abspath(const char* const);
long getfilesize(const char* path);

