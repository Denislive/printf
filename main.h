#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

/**
 * struct conversion_specifier - Struct for conversion specifiers
 * @specifier: The conversion specifier (e.g., "c", "s", "%")
 * @function: The corresponding function to handle the specifier
 */
typedef struct conversion_specifier
{
	char *specifier;
	int (*function)(va_list);
} convert_func_t;

int _putchar(char c);
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int _printf(const char *format, ...);

#endif /* MAIN_H */
