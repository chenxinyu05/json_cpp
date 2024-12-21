#ifndef _JSON_H
#define _JSON_H

#include <string>
#include <vector>
#include <unordered_map>

namespace json {
class json_var;
class json_null;
class json_boolean;
class json_number;
class json_string;
class json_array;
class json_object;

json_var* __parse(const std::string& __s);
json_var* __parse(const char* __s, size_t __n);

int __parse(json_null* __x, const char* __s, size_t __n);
int __parse(json_boolean* __x, const char* __s, size_t __n);
int __parse(json_number* __x, const char* __s, size_t __n);
int __parse(json_string* __x, const char* __s, size_t __n);
int __parse(json_array* __x, const char* __s, size_t __n);
int __parse(json_object* __x, const char* __s, size_t __n);

bool is_whitespace(char __c) noexcept {
    return __c == ' ' || __c == '\n' || __c == '\r' || __c == '\t';
}

const char* format = "%f";
} // namespace json

#include "__json/var.h"
#include "__json/null.h"
#include "__json/boolean.h"
#include "__json/number.h"
#include "__json/string.h"
#include "__json/array.h"
#include "__json/object.h"
#include "__json/parser.h"

namespace json {
using var = json_var;
using null_t = json_null;
using boolean = json_boolean;
using number = json_number;
using string = json_string;
using array = json_array;
using object = json_object;

const null_t null;
} // namespace json

#endif
