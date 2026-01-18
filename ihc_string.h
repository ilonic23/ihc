/*
* ihc_string.h - v0.1 - ilonic23 2026
* This is a single-header-file implementing a string as a vector and not an array.
* To use, #define this *once* in a source file: IHC_STRING_IMPLEMENTATION
* Then #include "ihc_string.h"
* 
* TABLE OF CONTENTS:
* Table of contents - line 7
* Compile-time options - line 13
* Documentation - line 22
* Credits - line
*
* COMPILE-TIME OPTIONS:
* 
* #define IHCSTRING_NO_SHORT_NAMES - by default the names of the functions (macros) are
*                                    named without a prefix, defining this will add the prefix 'ihc_'
* #define IHC_STRING_CAP           - set the default string capacity when initializing the string.
*                                    default value: 8
* #define ihc_realloc and ihc_free - if you have better memory allocation, you can set these functions.
*                                    their interface should be like the default functions from stdlib.
* 
* DOCUMENTATION:
*
* ihc_string_new()                                      - initializes a string and returns ihc_string_t pointer to it.
* ihc_string_from_cstr(const char *str)                 - initializes a string from a default C string and returns ihc_string_t pointer to it.
*                                                         str - pointer to the C string
* ihc_string_to_cstr(const ihc_string_t *string)        - converts an ihc_string_t to a default C string and returns a pointer to it.
*                                                         string - pointer to an ihc_string_t
* ihc_string_push(ihc_string_t *string, char c)         - pushes a character to the end of the string. returns new length or -1 if failed.
*                                                         string - pointer to an ihc_string_t to push to.
*                                                         c - character to push
* ihc_string_get(ihc_string_t *string, size_t index)    - get a character from the string by index. returns the character and '\0' if failed.
*                                                         string - pointer to an ihc_string_t.
*                                                         index  - the index where to get the character at.
* ihc_string_pop(ihc_string_t *string)                  - pop a character from the end of the string. returns the character and '\0' if failed.
*                                                         string - pointer to an ihc_string_t.
* ihc_string_delete(ihc_string_t *string, size_t index) - remove a character from the string by an index. Doesn't change the capacity.
*                                                         string - pointer to an ihc_string_t.
*                                                         index - the index to delete the character at.
* ihc_string_len(ihc_string_t *string)                  - returns the string's length.
*                                                         string - pointer to an ihc_string_t.
* ihc_string_capacity(ihc_string_t *string)             - returns the string's capacity.
*                                                         string - pointer to an ihc_string_t.
* 
*/

#ifndef IHC_STRING_H
#define IHC_STRING_H


#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#ifndef IHCSTRING_NO_SHORT_NAMES
typedef struct IHC_String string_t;

#define string_new       ihc_string_new
#define string_from_cstr ihc_string_from_cstr
#define string_to_cstr   ihc_string_to_cstr
#define string_push      ihc_string_push
#define string_get       ihc_string_get
#define string_pop       ihc_string_pop
#define string_delete    ihc_string_delete
#define string_len       ihc_string_len
#define string_capacity  ihc_string_capacity
#else
typedef struct IHC_String ihc_string_t;
#endif // IHCSTRING_NO_SHORT_NAMES

struct IHC_String *ihc_string_new();
struct IHC_String *ihc_string_from_cstr(const char *str);
char *ihc_string_to_cstr(const struct IHC_String *string);
int ihc_string_push(struct IHC_String *string, char c);
unsigned char ihc_string_get(struct IHC_String *string, size_t index);
unsigned char ihc_string_pop(struct IHC_String *string);
void ihc_string_delete(struct IHC_String *string, size_t index);
size_t ihc_string_len(const struct IHC_String *string);
size_t ihc_string_capacity(const struct IHC_String *string);

#ifndef IHC_STRING_CAP
#define IHC_STRING_CAP 8
#endif // IHC_STRING_CAP

#if defined(ihc_realloc) && !defined(ihc_free) || defined(ihc_free) && !defined(ihc_realloc)
#error "Both ihc_realloc and ihc_free should be set."
#endif

#if !defined(ihc_realloc) && !defined(ihc_free)
#include "stdlib.h"
#define ihc_realloc realloc
#define ihc_free free
#endif

#ifdef __cplusplus
}
#endif

#endif // IHC_STRING_H

#ifdef IHC_STRING_IMPLEMENTATION

#include "string.h"

struct IHC_String {
    unsigned char *str;
    size_t len;
    size_t capacity;
};

struct IHC_String *ihc_string_new() {
    struct IHC_String *string = (struct IHC_String *)ihc_realloc(NULL, sizeof(struct IHC_String));
    if (!string) return NULL;

    string->str = (unsigned char *)ihc_realloc(NULL, IHC_STRING_CAP);
    if (!string->str) {
        ihc_free(string);
        return NULL;
    }

    string->capacity = IHC_STRING_CAP;
    string->len = 0;
    return string;
}

struct IHC_String *ihc_string_from_cstr(const char *str) {
    struct IHC_String *string = ihc_string_new();
    if (!string) return NULL;
    while (*str)
        if (ihc_string_push(string, *str++) == -1) return NULL;
    return string;
}

char *ihc_string_to_cstr(const struct IHC_String *string) {
    if (!string) return NULL;
    char *result = (char *)ihc_realloc(NULL, string->len + 1);
    if (!result) return NULL;
    memcpy(result, string->str, string->len);
    result[string->len] = '\0';
    return result;
}

int ihc_string_push(struct IHC_String *string, char c) {
    if (!string) return -1;

    if (string->len + 1 == string->capacity) {
        size_t new_cap = string->capacity * 2;
        string->str = (unsigned char *)ihc_realloc(string->str, new_cap);
        if (!string->str) return -1;
        string->capacity = new_cap;
    }

    string->str[string->len++] = c;
    return string->len;
}

unsigned char ihc_string_get(struct IHC_String *string, size_t index) {
    if (!string) return 0;
    if (index >= string->len) return 0;

    return string->str[index];
}

unsigned char ihc_string_pop(struct IHC_String *string) {
    unsigned char result = ihc_string_get(string, string->len - 1);
    // If we get an error, we don't want to pop the char,
    // but only return an error character
    if (result == 0) return 0;
    string->len--;
    return result;
}

void ihc_string_delete(struct IHC_String *string, size_t index) {
    if (!string) return;
    if (index >= string->len) return;

    string->str[index] = 0;
    for (size_t i = index; i < string->len - 1; i++) {
        string->str[i] = string->str[i + 1];
    }
    string->len--;
}

size_t ihc_string_len(const struct IHC_String *string) {
    return string->len;
}

size_t ihc_string_capacity(const struct IHC_String *string) {
    return string->capacity;
}

#endif // IHC_STRING_IMPLEMENTATION
