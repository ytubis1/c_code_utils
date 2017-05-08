#ifndef __LOGGER_PL__
#define __LOGGER_PL__

#ifdef __cplusplus
extern "C"
{
#endif

	// handle global file for the object, no need to context
void LOGGER_PL_init();
void LOGGER_PL_log(char *format, ...);
void LOGGER_PL_term();

#ifdef __cplusplus
}
#endif

#endif // __LOGGER_PL__
