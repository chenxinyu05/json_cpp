#ifndef _JSON_NUMBER_H
#define _JSON_NUMBER_H

namespace json {
class json_number : public json_var {
private:
    bool __is_decimal_;
    union {
        long long __i_;
        double __f_;
    };

public:
    json_number() noexcept : __is_decimal_(false), __i_(0) {}

    json_number(signed char __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(unsigned char __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(short __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(unsigned short __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(int __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(unsigned int __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(long __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(unsigned long __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(long long __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(unsigned long long __x) noexcept : __is_decimal_(false), __i_(__x) {}

    json_number(float __x) noexcept : __is_decimal_(true), __f_(__x) {}

    json_number(double __x) noexcept : __is_decimal_(true), __f_(__x) {}

    json_number(long double __x) noexcept : __is_decimal_(true), __f_(__x) {}

    json_number(const json_number& __x) noexcept : __is_decimal_(__x.__is_decimal_), __i_(__x.__i_) {}

    json_number(json_number&& __x) noexcept : __is_decimal_(__x.__is_decimal_), __i_(__x.__i_) {}

    virtual ~json_number() noexcept = default;

    json_number& operator=(signed char __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(unsigned char __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(short __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(unsigned short __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(int __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(unsigned int __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(long __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(unsigned long __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(long long __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(unsigned long long __x) noexcept {
        __is_decimal_ = false;
        __i_ = __x;
        return *this;
    }

    json_number& operator=(float __x) noexcept {
        __is_decimal_ = true;
        __f_ = __x;
        return *this;
    }

    json_number& operator=(double __x) noexcept {
        __is_decimal_ = true;
        __f_ = __x;
        return *this;
    }

    json_number& operator=(long double __x) noexcept {
        __is_decimal_ = true;
        __f_ = __x;
        return *this;
    }

    json_number& operator=(const json_number& __x) noexcept {
        __is_decimal_ = __x.__is_decimal_;
        __i_ = __x.__i_;
        return *this;
    }

    json_number& operator=(json_number&& __x) noexcept {
        __is_decimal_ = __x.__is_decimal_;
        __i_ = __x.__i_;
        return *this;
    }

    virtual operator signed char() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator unsigned char() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator short() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator unsigned short() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator int() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator unsigned int() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator long() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator unsigned long() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator long long() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator unsigned long long() const override {
        return __is_decimal_ ? (long long)__f_ : __i_;
    }

    virtual operator float() const override {
        return __is_decimal_ ? __f_ : (double)__i_;
    }

    virtual operator double() const override {
        return __is_decimal_ ? __f_ : (double)__i_;
    }

    virtual operator long double() const override {
        return __is_decimal_ ? __f_ : (double)__i_;
    }

    virtual bool is_number() const noexcept override {
        return true;
    }

    virtual json_var* __copy() const override {
        return new json_number(*this);
    }

    virtual json_var* __move() override {
        return new json_number(std::move(*this));
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
        size_t __n = 32;
        std::string __s(__n, '\0');
        if (__is_decimal_) {
            snprintf(&__s[0], __n, format, __f_);
        } else {
            snprintf(&__s[0], __n, "%lld", __i_);
        }
        __s.resize(strlen(__s.c_str()));
        return __s;
    }
};
} // namespace json

#endif
