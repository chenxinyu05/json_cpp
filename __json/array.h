#ifndef _JSON_ARRAY_H
#define _JSON_ARRAY_H

namespace json {
class json_array : public json_var {
private:
    std::vector<json_var*> __vec_;

public:
    json_array() noexcept = default;

    json_array(const json_array& __x) : __vec_(__x.__vec_) {
        for (auto& __i : __vec_)
            __i = __i->__copy();
    }

    json_array(json_array&& __x) noexcept : __vec_(std::move(__x.__vec_)) {}

    virtual ~json_array() noexcept {
        clear();
    }

    json_array& operator=(const json_array& __x) = delete;

    json_array& operator=(json_array&& __x) noexcept = delete;

    virtual bool is_array() const noexcept override {
        return true;
    }

    void push_back(bool __x) {
        __vec_.emplace_back(new json_boolean(__x));
    }

    void push_back(signed char __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(unsigned char __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(short __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(unsigned short __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(int __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(unsigned int __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(long __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(unsigned long __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(long long __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(unsigned long long __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(float __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(double __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(long double __x) {
        __vec_.emplace_back(new json_number(__x));
    }

    void push_back(const char* __s) {
        __vec_.emplace_back(new json_string(__s));
    }

    void push_back(const std::string& __s) {
        __vec_.emplace_back(new json_string(__s));
    }

    void push_back(std::string&& __s) {
        __vec_.emplace_back(new json_string(std::move(__s)));
    }

    void push_back(const json_var& __x) {
        __vec_.emplace_back(__x.__copy());
    }

    void push_back(json_var&& __x) {
        __vec_.emplace_back(__x.__move());
    }

    void pop_back() {
        delete __vec_.back();
        __vec_.pop_back();
    }

    void set(size_t __n, bool __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_boolean(__x);
    }

    void set(size_t __n, signed char __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, unsigned char __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, short __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, unsigned short __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, int __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, unsigned int __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, long __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, unsigned long __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, long long __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, unsigned long long __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, float __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, double __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, long double __x) {
        delete __vec_[__n];
        __vec_[__n] = new json_number(__x);
    }

    void set(size_t __n, const char* __s) {
        delete __vec_[__n];
        __vec_[__n] = new json_string(__s);
    }

    void set(size_t __n, const std::string& __s) {
        delete __vec_[__n];
        __vec_[__n] = new json_string(__s);
    }

    void set(size_t __n, std::string&& __s) {
        delete __vec_[__n];
        __vec_[__n] = new json_string(std::move(__s));
    }

    void set(size_t __n, const json_var& __x) {
        delete __vec_[__n];
        __vec_[__n] = __x.__copy();
    }

    void set(size_t __n, json_var&& __x) {
        delete __vec_[__n];
        __vec_[__n] = __x.__move();
    }

    json_var& operator[](size_t __n) noexcept {
        return *__vec_[__n];
    }

    const json_var& operator[](size_t __n) const noexcept {
        return *__vec_[__n];
    }

    json_var& front() noexcept {
        return *__vec_.front();
    }

    const json_var& front() const noexcept {
        return *__vec_.front();
    }

    json_var& back() noexcept {
        return *__vec_.back();
    }

    const json_var& back() const noexcept {
        return *__vec_.back();
    }

    bool empty() const noexcept {
        return __vec_.empty();
    }

    size_t size() const noexcept {
        return __vec_.size();
    }

    void clear() noexcept {
        for (json_var* __x : __vec_)
            delete __x;
        __vec_.clear();
    }

    virtual json_var* __copy() const override {
        return new json_array(*this);
    }

    virtual json_var* __move() override {
        return new json_array(std::move(*this));
    }

    virtual int load(const char* __s, size_t __n) override {
        size_t __i = 0;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        int __t = __parse(this, __s + __i, __n - __i);
        if (__t == 0)
            return -1;
        __i += __t;
        if (__i == __n || __s[__i] != ']')
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
        __s += "[";
        size_t __n = size();
        for (size_t __i = 0; __i < __n; ++__i) {
            if (__i > 0)
                __s += ", ";
            __s += __vec_[__i]->dump();
        }
        __s += "]";
        return __s;
    }
};
} // namespace json

#endif
