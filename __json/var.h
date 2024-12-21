#ifndef _JSON_VAR_H
#define _JSON_VAR_H

namespace json {
class json_var {
public:
    json_var() noexcept = default;

    json_var(const json_var& __x) noexcept = default;

    json_var(json_var&& __x) noexcept = default;

    virtual ~json_var() noexcept = default;

protected:
    json_var& operator=(const json_var& __x) noexcept = default;

    json_var& operator=(json_var&& __x) noexcept = default;

public:
    virtual operator bool() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator signed char() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator unsigned char() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator short() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator unsigned short() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator int() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator unsigned int() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator long() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator unsigned long() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator long long() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator unsigned long long() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator float() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator double() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator long double() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual operator std::string() const {
        throw std::runtime_error("json_var: bad cast");
    }

    virtual bool is_null() const noexcept {
        return false;
    }

    virtual bool is_boolean() const noexcept {
        return false;
    }

    virtual bool is_number() const noexcept {
        return false;
    }

    virtual bool is_string() const noexcept {
        return false;
    }

    virtual bool is_array() const noexcept {
        return false;
    }

    virtual bool is_object() const noexcept {
        return false;
    }

    virtual json_var* __copy() const = 0;

    virtual json_var* __move() = 0;

    virtual int load(const char* __s, size_t __n) = 0;

    virtual int load(const std::string& __s) = 0;

    virtual std::string dump() const = 0;
};
} // namespace json

#endif
