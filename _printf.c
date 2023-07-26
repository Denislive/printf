#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/**
 * print_char - Print a character.
 * @args: The va_list that contains the character to print.
 *
 * Return: The number of characters printed (always 1).
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);

	_putchar(c);
	return (1);
}

/**
 * print_string - Print a string.
 * @args: The va_list that contains the string to print.
 *
 * Return: The number of characters printed.
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);
	int printed_chars = 0;
	char current_char;

	if (str == NULL)
		str = "(null)";

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
	int digits = 0;
	int divisor = 1;
	int j;
	int printed_chars = 0;

	if (num == 0)
	{
		_putchar('0');
		return (1);
	}
	else if (num < 0)
	{
		_putchar('-');
		num *= -1;
		digits++;
	}


	for (j = 1; j < digits; j++)
		divisor *= 10;


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
 * print_binary - Print an unsigned integer in binary format.
 * @args: The va_list that contains the integer to print in binary.
 *
 * Return: The number of characters printed.
 */
int print_binary(va_list args)
{
    unsigned int num = va_arg(args, unsigned int);
    int printed_chars = 0;
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    int found_one = 0;

    while (mask > 0)
    {
        if (num & mask || found_one)
        {
            _putchar((num & mask) ? '1' : '0');
            printed_chars++;
            found_one = 1;
        }
        mask >>= 1;
    }

    if (!found_one)
    {
        _putchar('0');
        printed_chars++;
    }

    return (printed_chars);
}

/**
 * print_unsigned_integer - Print an unsigned integer.
 * @args: The va_list that contains the unsigned integer to print.
 * @base: The base to be used for printing (e.g., 10 for decimal).
 * @uppercase: Flag to indicate if the output should be uppercase (X).
 *
 * Return: The number of characters printed.
 */
int print_unsigned_integer(va_list args, int base, int uppercase)
{
    unsigned int num = va_arg(args, unsigned int);
    unsigned int temp = num;
    int digits = 0;
    int divisor = 1;
    int j;
    int printed_chars = 0;

    if (num == 0)
    {
        _putchar('0');
        return (1);
    }

    while (temp != 0)
    {
        temp /= base;
        digits++;
    }

    for (j = 1; j < digits; j++)
        divisor *= base;

    while (divisor != 0)
    {
        int digit = num / divisor;
        if (digit < 10)
            _putchar(digit + '0');
        else
            _putchar((digit - 10) + (uppercase ? 'A' : 'a'));

        printed_chars++;
        num %= divisor;
        divisor /= base;
    }

    return (printed_chars);
}

/*
 *_printf - Produces output according to a format.
 * @format: The character string containing zero or more directives.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	char *str;
	int num, temp, digits, divisor, j;

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
					_putchar(va_arg(args, int));
					printed_chars++;
					break;
				case 's':
					str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";
					while (*str)
					{
						_putchar(*str);
						printed_chars++;
						str++;
					}
					break;
				case 'd':
				case 'u':
					printed_chars += print_unsigned_integer(args, 10, 0);
					break;
				case 'o':
					printed_chars += print_unsigned_integer(args, 8, 0);
					break;
				case 'x':
					printed_chars += print_unsigned_integer(args, 16, 0);
					break;
				case 'X':
					printed_chars += print_unsigned_integer(args, 16, 1);
					break;
				case 'b':
					printed_chars += print_binary(args);
					break;
				case 'i':
					num = va_arg(args, int);
					temp = num;
					digits = 0;

					if (num == 0)
					{
						_putchar('0');
						printed_chars++;
					}
					else if (num < 0)
					{
						_putchar('-');
						printed_chars++;
						num *= -1;
						temp *= -1;
					}

					while (temp != 0)
					{
						temp /= 10;
						digits++;
					}

					divisor = 1;
					for (j = 1; j < digits; j++)
						divisor *= 10;

					while (divisor != 0)
					{
						_putchar((num / divisor) + '0');
						printed_chars++;
						num %= divisor;
						divisor /= 10;
					}
					break;
				case '%':
					format++;
					if (*format == '\0')
					{
						write(1, "%", 1);
						printed_chars++;
						break;
					}
					write(1, "%", 1);
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
