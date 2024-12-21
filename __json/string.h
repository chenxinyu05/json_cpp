#ifndef _JSON_STRING_H
#define _JSON_STRING_H

namespace json {
class json_string : public json_var {
private:
    std::string __str_;

public:
    json_string() noexcept = default;

    json_string(const char* __s) : __str_(__s) {}

    json_string(const char* __s, size_t __n) : __str_(__s, __n) {}

    json_string(const std::string& __s) : __str_(__s) {}

    json_string(std::string&& __s) noexcept : __str_(std::move(__s)) {}

    json_string(const json_string& __x) : __str_(__x.__str_) {}

    json_string(json_string&& __x) noexcept : __str_(std::move(__x.__str_)) {}

    virtual ~json_string() noexcept = default;

    json_string& operator=(const char* __s) {
        __str_ = __s;
        return *this;
    }

    json_string& operator=(const std::string& __s) {
        __str_ = __s;
        return *this;
    }

    json_string& operator=(std::string&& __s) noexcept {
        __str_ = std::move(__s);
        return *this;
    }

    json_string& operator=(const json_string& __x) {
        __str_ = __x.__str_;
        return *this;
    }

    json_string& operator=(json_string&& __x) noexcept {
        __str_ = std::move(__x.__str_);
        return *this;
    }

    friend bool operator==(const json_string& __x, const json_string& __y) noexcept {
        return __x.__str_ == __y.__str_;
    }

    virtual operator std::string() const override {
        return __str_;
    }

    virtual bool is_string() const noexcept override {
        return true;
    }

    json_string& operator+=(char __c) {
        __str_ += __c;
        return *this;
    }

    json_string& operator+=(const char* __s) {
        __str_ += __s;
        return *this;
    }

    json_string& operator+=(const std::string& __s) {
        __str_ += __s;
        return *this;
    }

    json_string& operator+=(const json_string& __x) {
        __str_ += __x.__str_;
        return *this;
    }

    void push_back(char __c) {
        __str_.push_back(__c);
    }

    void pop_back() {
        __str_.pop_back();
    }

    char& operator[](size_t __n) noexcept {
        return __str_[__n];
    }

    const char& operator[](size_t __n) const {
        return __str_[__n];
    }

    char& at(size_t __n) {
        if (__n >= size())
            throw std::runtime_error("json_string: out of range");
        return __str_.at(__n);
    }

    const char& at(size_t __n) const {
        if (__n >= size())
            throw std::runtime_error("json_string: out of range");
        return __str_.at(__n);
    }

    char& front() noexcept {
        return __str_.front();
    }

    const char& front() const noexcept {
        return __str_.front();
    }

    char& back() noexcept {
        return __str_.back();
    }

    const char& back() const noexcept {
        return __str_.back();
    }

    bool empty() const noexcept {
        return __str_.empty();
    }

    size_t size() const noexcept {
        return __str_.size();
    }

    size_t length() const noexcept {
        return __str_.length();
    }

    void clear() noexcept {
        return __str_.clear();
    }

    const char* c_str() const noexcept {
        return __str_.c_str();
    }

    const std::string& str() const noexcept {
        return __str_;
    }

    virtual json_var* __copy() const override {
        return new json_string(*this);
    }

    virtual json_var* __move() override {
        return new json_string(std::move(*this));
    }

    virtual int load(const char* __s, size_t __n) override {
        size_t __i = 0;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        int __t = __parse(this, __s + __i, __n - __i);
        if (__t == 0)
            return -1;
        __i += __t;
        if (__i == __n || __s[__i] != '\"')
            return __i;
        ++__i;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        return __i == __n ? 0 : __i;
    }

    virtual int load(const std::string& __s) override {
        return load(__s.c_str(), __s.size());
    }

    virtual std::string dump() const override {
        std::string __s;
        __s += '\"';
        for (char __c : __str_) {
            if (__c == '\"') {
                __s += "\\\"";
            } else if (__c == '\\') {
                __s += "\\\\";
            } else if (__c == '\b') {
                __s += "\\b";
            } else if (__c == '\f') {
                __s += "\\f";
            } else if (__c == '\n') {
                __s += "\\n";
            } else if (__c == '\r') {
                __s += "\\r";
            } else if (__c == '\t') {
                __s += "\\t";
            } else if ((__c >= 0 && __c < 0x20) || __c == 0x7f) {
                __s += "\\u00";
                int __t = (__c >> 4) & 0xf;
                __s += __t < 10 ? '0' + __t : 'a' + __t - 10;
                __t = __c & 0xf;
                __s += __t < 10 ? '0' + __t : 'a' + __t - 10;
            } else {
                __s += __c;
            }
        }
        __s += '\"';
        return __s;
    };
};
} // namespace json

#endif
