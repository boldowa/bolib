/**
 * @file libfile.c
 */
#if !isWindows
#  ifndef _XOPEN_SOURCE
#    define _XOPEN_SOURCE 500
#  endif
#endif
#include "common/types.h"
#if isWindows
#  include <windows.h>
#else
#  include <sys/stat.h>
#endif
#include <assert.h>
#include "common/Str.h"

#include "file/libfile.h"

bool fexists(const char* const path)
{
#if isWindows

	HANDLE hFile;

	hFile = CreateFile(
			path,
			GENERIC_READ, FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			NULL
			);
	if(INVALID_HANDLE_VALUE != hFile)
	{
		CloseHandle(hFile);
		return true;
	}
	return false;

#else

	struct stat sts;

	if(0 == stat(path, &sts) && S_ISREG(sts.st_mode))
	{
		return true;
	}
	return false;

#endif
}

bool direxists(const char* const path)
{
#if isWindows
	DWORD attr;

	attr = GetFileAttributes(path);
	if((attr != INVALID_FILE_ATTRIBUTES) && (0 != (attr & FILE_ATTRIBUTE_DIRECTORY)))
	{
		return true;
	}
	return false;
#else
	struct stat sts;

	if(0 == stat(path, &sts) && S_ISDIR(sts.st_mode))
	{
		return true;
	}
	return false;
#endif
}

void gettmpdir(char** sp)
{
	char* s;
#if isWindows
	s = calloc(sizeof(char), MAX_PATH);
	GetTempPath(MAX_PATH, s);
	assert(s);
#else
	s = Str_copy("/tmp/");
	assert(s);
#endif
	(*sp) = s;
}

bool makedir(const char* const path)
{
#if isWindows
	return (0 != CreateDirectory(path, NULL));
#else
	return (0 == mkdir(path, 0755));
#endif
}

char* getworkdir(const char* const basename)
{
	char* tmpdir = NULL;
	char* workdir = NULL;

	gettmpdir(&tmpdir);
	workdir = Str_concat(tmpdir, basename);
	free(tmpdir);

	if(!direxists(workdir))
	{
		if(!makedir(workdir))
		{
			free(workdir);
			return NULL;
		}
	}

	return workdir;
}

char* abspath(const char* const path)
{
	char* s;
	s = calloc(sizeof(char), MAX_PATH);
	assert(s);
#if isWindows
	if(0 == GetFullPathName(path, MAX_PATH, s, NULL))
	{
		free(s);
		return NULL;
	}
#else
	if(NULL == realpath(path, s) || MAX_PATH-1 <= strlen(s))
	{
		free(s);
		return NULL;
	}
	s[strlen(s)+1] = '\0';
	s[strlen(s)] = '/';
#endif
	return s;
}

long getfilesize(const char* path)
{
#if isWindows
	HANDLE hFile;
	DWORD dwSize;

	hFile = CreateFile(path,
		GENERIC_READ, FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(INVALID_HANDLE_VALUE == hFile) return 0;

	dwSize = GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	return (long)dwSize;
#else
	struct stat st;
	if(0 == stat(path, &st))
	{
		return st.st_size;
	}
	return 0;
#endif
}

