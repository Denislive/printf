#include "main.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * print_string - Print a string.
 * @args: The va_list that contains the string to print.
 *
 * Return: The number of characters printed.
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = "(null)";

	int printed_chars = 0;
	char current_char;

	while ((current_char = *str++))
	{
		_putchar(current_char);
		printed_chars++;
	}
	return (printed_chars);
}

/**
 * print_integer - Print an integer.
 * @args: The va_list that contains the integer to print.
 *
 * Return: The number of characters printed.
 */
int print_integer(va_list args)
{
	int num = va_arg(args, int);
	int temp = num;
	int digits = 0;

	if (num == 0)
	{
		_putchar('0');
		return (1);
	}
	else if (num < 0)
	{
		_putchar('-');
		num *= -1;
		temp *= -1;
		digits++;
	}

	int divisor = 1;
	int j;

	for (j = 1; j < digits; j++)
		divisor *= 10;

	int printed_chars = 0;

	while (divisor != 0)
	{
		_putchar((num / divisor) + '0');
		printed_chars++;
		num %= divisor;
		divisor /= 10;
	}

	return (printed_chars);
}

/**
 * _printf - Produces output according to a format.
 * @format: The character string containing zero or more directives.
 * @...: Optional arguments to be printed according to the format.
 *
 * Return: The number of characters printed (excluding the null byte),
 * or -1 if the format is NULL.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;

	va_start(args, format);

	if (format == NULL)
		return (-1);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					printed_chars += print_char(args);
					break;
				case 's':
					printed_chars += print_string(args);
					break;
				case 'd':
				case 'i':
					printed_chars += print_integer(args);
					break;
				case '%':
					_putchar('%');
					printed_chars++;
					break;
				default:
					_putchar('%');
					_putchar(*format);
					printed_chars += 2;
					break;
			}
		}
		else
		{
			_putchar(*format);
			printed_chars++;
		}
		format++;
	}

	va_end(args);

	return (printed_chars);
}
