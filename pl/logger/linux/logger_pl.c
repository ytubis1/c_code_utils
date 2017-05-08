// platform
#include<stdio.h>
#include <stdarg.h> 
#include <pthread.h>

// header
#include <logger_pl.h>

#define FULL_LOG_PATH "log.log"
#define MAX_LOG_PRINT_SIZE 2048
static pthread_mutex_t s_mutex;
static FILE *s_fileHandler;

void LOGGER_PL_init(int isPrintToLogFile)
{
    s_fileHandler = NULL;

	if (isPrintToLogFile)
	    s_fileHandler = fopen(FULL_LOG_PATH, "w");

	pthread_mutex_init(&s_mutex, NULL);
}

static void printToConsole(char *logMsgBuffer)
{
	printf("%s", logMsgBuffer);
}

static size_t printToLogFile(char *logMsgBuffer, size_t logMsgBufferSize)
{
    size_t ret = fwrite(logMsgBuffer, 1, logMsgBufferSize, s_fileHandler);
    fflush(s_fileHandler);
	return ret;
}

static void createLogBuffer (const char *format, va_list args)
{
	size_t stringLen = 0;
	static char msgBuf[MAX_LOG_PRINT_SIZE];
	size_t prefixLen = 0 , msgBufLen = MAX_LOG_PRINT_SIZE;
	size_t stringEnd = 0;

	stringLen = (size_t)vsnprintf(&msgBuf[prefixLen], msgBufLen, format, args);
	stringLen += prefixLen;

	if (stringLen > 0)
	{
		stringEnd = stringLen < MAX_LOG_PRINT_SIZE - 1 ? stringLen : MAX_LOG_PRINT_SIZE - 3;
		//msgBuf[stringEnd] = '\n';
		msgBuf[stringEnd + 1] = '\0';

		printToConsole(msgBuf);
		if (s_fileHandler)
			printToLogFile(msgBuf, stringEnd);

	}
}

void LOGGER_PL_log(char *format, ...)
{
	va_list args;

	pthread_mutex_lock(&s_mutex);
	va_start(args, format);
	createLogBuffer(format, args);
	va_end(args);
	pthread_mutex_unlock(&s_mutex);
}

void LOGGER_PL_term()
{
	fclose(s_fileHandler);
	s_fileHandler = NULL;
	pthread_mutex_destroy(&s_mutex);
}
