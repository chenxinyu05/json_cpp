#ifndef _JSON_PARSER_H
#define _JSON_PARSER_H

namespace json {
json_var* __parse(const std::string& __s) {
    return __parse(__s.c_str(), __s.size());
}

json_var* __parse(const char* __s, size_t __n) {
    size_t __i = 0;
    while (__i < __n && is_whitespace(__s[__i]))
        ++__i;
    json_var* __x = nullptr;
    if (__i == __n) {
        return nullptr;
    } else if (__s[__i] == '{') {
        __x = new json_object();
    } else if (__s[__i] == '[') {
        __x = new json_array();
    } else if (__s[__i] == '\"') {
        __x = new json_string();
    } else if (isdigit(__s[__i]) || __s[__i] == '-') {
        __x = new json_number();
    } else if (__s[__i] == 't' || __s[__i] == 'f') {
        __x = new json_boolean();
    } else if (__s[__i] == 'n') {
        __x = new json_null();
    } else {
        return nullptr;
    }
    if (__x->load(__s + __i, __n - __i)) {
        delete __x;
        return nullptr;
    }
    return __x;
}

int __parse(json_null* __x, const char* __s, size_t __n) {
    if (__n < 4 || strncmp(__s, "null", 4) != 0)
        return 0;
    *__x = json_null();
    return 4;
}

int __parse(json_boolean* __x, const char* __s, size_t __n) {
    if (__n < 4)
        return 0;
    if (strncmp(__s, "true", 4) == 0) {
        *__x = true;
        return 4;
    } else if (__n >= 5 && strncmp(__s, "false", 5) == 0) {
        *__x = false;
        return 5;
    }
    return 0;
}

int __parse(json_number* __x, const char* __s, size_t __n) {
    if (__n == 0)
        return 0;
    size_t __i = 0;
    if (__s[__i] == '-') {
        ++__i;
        if (__i == __n || !isdigit(__s[__i]))
            return 0;
    }
    if (__s[__i] != '0') {
        while (__i < __n && isdigit(__s[__i]))
            ++__i;
    } else {
        ++__i;
    }
    bool __is_decimal = false;
    if (__i < __n && __s[__i] == '.') {
        __is_decimal = true;
        ++__i;
        if (__i == __n)
            return __n;
        if (!isdigit(__s[__i]))
            return __i - 1;
        while (__i < __n && isdigit(__s[__i]))
            ++__i;
    }
    if (__i < __n && (__s[__i] == 'e' || __s[__i] == 'E')) {
        __is_decimal = true;
        ++__i;
        if (__i == __n)
            return __n;
        if (__s[__i] == '+' || __s[__i] == '-') {
            ++__i;
            if (__i == __n)
                return __n;
        }
        if (!isdigit(__s[__i]))
            return __i - 1;
        while (__i < __n && isdigit(__s[__i]))
            ++__i;
    }
    if (__is_decimal) {
        *__x = strtod(__s, NULL);
    } else {
        *__x = strtoll(__s, NULL, 10);
    }
    return __i;
}

int __parse(json_string* __x, const char* __s, size_t __n) {
    if (__n == 0 || __s[0] != '\"')
        return 0;
    size_t __i = 1;
    while (__i < __n && __s[__i] != '\"') {
        if ((__s[__i] >= 0 && __s[__i] < 0x20) || __s[__i] == 0x7f)
            return __i;
        if (__s[__i] == '\\') {
            ++__i;
            if (__i == __n) {
                return __n;
            } else if (__s[__i] == '\"') {
                *__x += '\"';
            } else if (__s[__i] == '\\') {
                *__x += '\\';
            } else if (__s[__i] == '/') {
                *__x += '/';
            } else if (__s[__i] == 'b') {
                *__x += '\b';
            } else if (__s[__i] == 'f') {
                *__x += '\f';
            } else if (__s[__i] == 'n') {
                *__x += '\n';
            } else if (__s[__i] == 'r') {
                *__x += '\r';
            } else if (__s[__i] == 't') {
                *__x += '\t';
            } else if (__s[__i] == 'u') {
                char __c = 0;
                for (size_t __k = 0; __k < 4; ++__k) {
                    ++__i;
                    if (__i == __n) {
                        return __n;
                    } else if (isdigit(__s[__i])) {
                        __c += __s[__i] - '0';
                    } else if (__s[__i] >= 'a' && __s[__i] <= 'f') {
                        __c += __s[__i] - 'a';
                    } else if (__s[__i] >= 'A' && __s[__i] <= 'F') {
                        __c += __s[__i] - 'A';
                    } else {
                        return __i - __k - 2;
                    }
                    if (__k & 1) {
                        *__x += __c;
                        __c = 0;
                    } else {
                        __c <<= 4;
                    }
                }
            } else {
                return __i - 1;
            }
        } else {
            *__x += __s[__i];
        }
        ++__i;
    }
    return __i;
}

int __parse(json_array* __x, const char* __s, size_t __n) {
    if (__n == 0 || __s[0] != '[')
        return 0;
    size_t __i = 1;
    while (__i < __n && is_whitespace(__s[__i]))
        ++__i;
    if (__i == __n || __s[__i] == ']')
        return __i;
    while (true) {
        if (__s[__i] == '{') {
            json_object __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
            if (__i == __n || __s[__i] != '}')
                return __i;
            ++__i;
        } else if (__s[__i] == '[') {
            json_array __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
            if (__i == __n || __s[__i] != ']')
                return __i;
            ++__i;
        } else if (__s[__i] == '\"') {
            json_string __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
            if (__i == __n || __s[__i] != '\"')
                return __i;
            ++__i;
        } else if (isdigit(__s[__i]) || __s[__i] == '-') {
            json_number __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
        } else if (__s[__i] == 't' || __s[__i] == 'f') {
            json_boolean __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
        } else if (__s[__i] == 'n') {
            json_null __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->push_back(std::move(__v));
        } else {
            return __i - 1;
        }
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n || __s[__i] == ']')
            return __i;
        if (__s[__i] != ',')
            return 0;
        ++__i;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n)
            return __n;
    };
    return 0;
}

int __parse(json_object* __x, const char* __s, size_t __n) {
    if (__n == 0 || __s[0] != '{')
        return 0;
    size_t __i = 1;
    while (__i < __n && is_whitespace(__s[__i]))
        ++__i;
    if (__i == __n || __s[__i] == '}')
        return __i;
    while (true) {
        if (__s[__i] != '\"')
            return __i - 1;
        json_string __k;
        __i += __parse(&__k, __s + __i, __n - __i);
        if (__i == __n || __s[__i] != '\"')
            return __i;
        ++__i;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n)
            return __i;
        if (__s[__i] != ':')
            return __i - 1;
        ++__i;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n)
            return __n;
        if (__s[__i] == '{') {
            json_object __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
            if (__i == __n || __s[__i] != '}')
                return __i;
            ++__i;
        } else if (__s[__i] == '[') {
            json_array __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
            if (__i == __n || __s[__i] != ']')
                return __i;
            ++__i;
        } else if (__s[__i] == '\"') {
            json_string __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
            if (__i == __n || __s[__i] != '\"')
                return __i;
            ++__i;
        } else if (isdigit(__s[__i]) || __s[__i] == '-') {
            json_number __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
        } else if (__s[__i] == 't' || __s[__i] == 'f') {
            json_boolean __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
        } else if (__s[__i] == 'n') {
            json_null __v;
            __i += __parse(&__v, __s + __i, __n - __i);
            __x->set(__k, std::move(__v));
        } else {
            return __i - 1;
        }
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n || __s[__i] == '}')
            return __i;
        if (__s[__i] != ',')
            return 0;
        ++__i;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        if (__i == __n)
            return __n;
    }
    return 0;
}
} // namespace json

#endif
