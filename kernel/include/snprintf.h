/**
 * @author (c) Eyal Rozenberg <eyalroz1@gmx.com>
 *             2021, Haifa, Palestine/Israel
 * @author (c) Marco Paland (info@paland.com)
 *             2014-2019, PALANDesign Hannover, Germany
 *
 * @note Others have made smaller contributions to this file: see the
 * contributors page at https://github.com/eyalroz/printf/graphs/contributors
 * or ask one of the authors.
 *
 * @brief Small stand-alone implementation of the printf family of functions
 * (`(v)printf`, `(v)s(n)printf` etc., geared towards use on embedded systems with
 * a very limited resources.
 *
 * @note the implementations are thread-safe; re-entrant; use no functions from
 * the standard library; and do not dynamically allocate any memory.
 *
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FILE_SNPRINTF_H
#define FILE_SNPRINTF_H

#include <stdarg.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
# define ATTR_PRINTF(one_based_format_index, first_arg) \
__attribute__((format(__printf__, (one_based_format_index), (first_arg))))
# define ATTR_VPRINTF(one_based_format_index) ATTR_PRINTF(one_based_format_index, 0)
#else
# define ATTR_PRINTF(one_based_format_index, first_arg)
# define ATTR_VPRINTF(one_based_format_index)
#endif

#ifdef PRINTF_ALIAS_STANDARD_FUNCTION_NAMES
# define printf    printf_
# define sprintf   sprintf_
# define vsprintf  vsprintf_
# define snprintf  snprintf_
# define vsnprintf vsnprintf_
# define vprintf   vprintf_
#endif




/**
 * Tiny sprintf/vsprintf implementation
 * Due to security reasons (buffer overflow) YOU SHOULD CONSIDER USING (V)SNPRINTF INSTEAD!
 * @param buffer A pointer to the buffer where to store the formatted string. MUST be big enough to store the output!
 * @param format A string that specifies the format of the output
 * @param va A value identifying a variable arguments list
 * @return The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 */
int  sprintf_(char* buffer, const char* format, ...) ATTR_PRINTF(2, 3);
int vsprintf_(char* buffer, const char* format, va_list va) ATTR_VPRINTF(2);


/**
 * Tiny snprintf/vsnprintf implementation
 * @param buffer A pointer to the buffer where to store the formatted string
 * @param count The maximum number of characters to store in the buffer, including a terminating null character
 * @param format A string that specifies the format of the output
 * @param va A value identifying a variable arguments list
 * @return The number of characters that COULD have been written into the buffer, not counting the terminating
 *         null character. A value equal or larger than count indicates truncation. Only when the returned value
 *         is non-negative and less than count, the string has been completely written.
 */
int  snprintf_(char* buffer, size_t count, const char* format, ...) ATTR_PRINTF(3, 4);
int vsnprintf_(char* buffer, size_t count, const char* format, va_list va) ATTR_VPRINTF(3);


/**
 * printf/vprintf with output function
 * You may use this as dynamic alternative to printf() with its fixed _putchar() output
 * @param out An output function which takes one character and an argument pointer
 * @param arg An argument pointer for user data passed to output function
 * @param format A string that specifies the format of the output
 * @param va A value identifying a variable arguments list
 * @return The number of characters that are sent to the output function, not counting the terminating null character
 */
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...) ATTR_PRINTF(3, 4);
int vfctprintf(void (*out)(char character, void* arg), void* arg, const char* format, va_list va) ATTR_VPRINTF(3);

#define sprintf sprintf_
#define vsprintf vsprintf_
#define snprintf snprintf_
#define vsnprintf vsnprintf_

#ifdef __cplusplus
}
#endif

#endif  /* FILE_SNPRINTF_H */