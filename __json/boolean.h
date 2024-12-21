#ifndef _JSON_BOOLEAN_H
#define _JSON_BOOLEAN_H

namespace json {
class json_boolean : public json_var {
private:
    bool __x_;

public:
    json_boolean() noexcept = default;

    json_boolean(bool __x) noexcept : __x_(__x) {}

    json_boolean(const json_boolean& __x) noexcept = default;

    json_boolean(json_boolean&& __x) noexcept = default;

    virtual ~json_boolean() noexcept = default;

    json_boolean& operator=(bool __x) noexcept {
        __x_ = __x;
        return *this;
    }

    json_boolean& operator=(const json_boolean& __x) noexcept = default;

    json_boolean& operator=(json_boolean&& __x) noexcept = default;

    virtual operator bool() const override {
        return __x_;
    }

    virtual bool is_boolean() const noexcept override {
        return true;
    }

    virtual json_var* __copy() const override {
        return new json_boolean(*this);
    }

    virtual json_var* __move() override {
        return new json_boolean(std::move(*this));
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
        return __x_ ? "true" : "false";
    };
};
} // namespace json

#endif
