#ifndef _JSON_NULL_H
#define _JSON_NULL_H

namespace json {
class json_null : public json_var {
public:
    json_null() noexcept = default;

    json_null(const json_null& __x) noexcept = default;

    json_null(json_null&& __x) noexcept = default;

    virtual ~json_null() noexcept = default;

    json_null& operator=(const json_null& __x) noexcept = default;

    json_null& operator=(json_null&& __x) noexcept = default;

    virtual bool is_null() const noexcept override {
        return true;
    }

    virtual json_var* __copy() const override {
        return new json_null(*this);
    }

    virtual json_var* __move() override {
        return new json_null(std::move(*this));
    }

    virtual int load(const char* __s, size_t __n) override {
        size_t __i = 0;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        int __t = __parse(this, __s + __i, __n - __i);
        if (__t == 0)
            return -1;
        __i += __t;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        return __i == __n ? 0 : __i;
    }

    virtual int load(const std::string& __s) override {
        return load(__s.c_str(), __s.size());
    }

    virtual std::string dump() const override {
        return "null";
    }
};
} // namespace json

#endif
