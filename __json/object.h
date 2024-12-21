#ifndef _JSON_OBJECT_H
#define _JSON_OBJECT_H

namespace json {
class json_object : public json_var {
private:
    std::unordered_map<std::string, json_var*> __map_;

public:
    json_object() noexcept = default;

    json_object(const json_object& __x) : __map_(__x.__map_) {
        for (auto& __i : __map_)
            __i.second = __i.second->__copy();
    }

    json_object(json_object&& __x) noexcept : __map_(std::move(__x.__map_)) {}

    virtual ~json_object() noexcept {
        clear();
    }

    json_object& operator=(const json_object& __x) = delete;

    json_object& operator=(json_object&& __x) noexcept = delete;

    virtual bool is_object() const noexcept override {
        return true;
    }

    void set(const std::string& __k, bool __x) {
        delete __map_[__k];
        __map_[__k] = new json_boolean(__x);
    }

    void set(const std::string& __k, signed char __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, unsigned char __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, short __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, unsigned short __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, int __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, unsigned int __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, long __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, unsigned long __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, long long __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, unsigned long long __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, float __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, double __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, long double __x) {
        delete __map_[__k];
        __map_[__k] = new json_number(__x);
    }

    void set(const std::string& __k, const char* __s) {
        delete __map_[__k];
        __map_[__k] = new json_string(__s);
    }

    void set(const std::string& __k, const std::string& __s) {
        delete __map_[__k];
        __map_[__k] = new json_string(__s);
    }

    void set(const std::string& __k, std::string&& __s) {
        delete __map_[__k];
        __map_[__k] = new json_string(std::move(__s));
    }

    void set(const std::string& __k, const json_var& __x) {
        delete __map_[__k];
        __map_[__k] = __x.__copy();
    }

    void set(const std::string& __k, json_var&& __x) {
        delete __map_[__k];
        __map_[__k] = __x.__move();
    }

    size_t erase(const std::string& __k) {
        if (!count(__k))
            return 0;
        delete __map_[__k];
        return __map_.erase(__k);
    }

    json_var& operator[](const std::string& __k) {
        return *__map_[__k];
    }

    json_var& operator[](const char* __k) {
        return *__map_[__k];
    }

    size_t size() const noexcept {
        return __map_.size();
    }

    bool empty() const noexcept {
        return __map_.empty();
    }

    size_t count(const std::string& __k) const {
        return __map_.count(__k);
    }

    std::vector<std::string> keys() const {
        std::vector<std::string> __vec_;
        for (const auto& __i : __map_)
            __vec_.push_back(__i.first);
        return __vec_;
    }

    void clear() noexcept {
        for (auto& __i : __map_)
            delete __i.second;
        __map_.clear();
    }

    virtual json_var* __copy() const override {
        return new json_object(*this);
    }

    virtual json_var* __move() override {
        return new json_object(std::move(*this));
    }

    virtual int load(const char* __s, size_t __n) override {
        size_t __i = 0;
        while (__i < __n && is_whitespace(__s[__i]))
            ++__i;
        int __t = __parse(this, __s + __i, __n - __i);
        if (__t == 0)
            return -1;
        __i += __t;
        if (__i == __n || __s[__i] != '}')
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
        __s += "{";
        for (auto& __i : __map_) {
            if (!__i.second)
                continue;
            if (__s != "{")
                __s += ", ";
            __s += json_string(__i.first).dump();
            __s += ": ";
            __s += __i.second->dump();
        }
        __s += "}";
        return __s;
    }
};
} // namespace json

#endif
