/*
 * Copyright (C) 2021 magicxqq <xqq@xqq.im>. All rights reserved.
 *
 * This file is part of libaribcaption.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef ARIBCAPTION_RESULT_HPP
#define ARIBCAPTION_RESULT_HPP

#include <cassert>
#include <variant>
#include <type_traits>

namespace aribcaption {

namespace internal {

template <typename T>
struct Ok {
    static_assert(!std::is_same<T, void>::value);
public:
    T val;
};

template <typename E>
struct Err {
    static_assert(!std::is_same<E, void>::value);
public:
    E val;
};

}  // namespace internal


template <typename T, typename CleanT = std::decay_t<T>>
constexpr internal::Ok<CleanT> Ok(T&& val) {
    return internal::Ok<CleanT>{std::forward<T>(val)};
}

template <typename E, typename CleanE = std::decay_t<E>>
constexpr internal::Err<CleanE> Err(E&& val) {
    return internal::Err<CleanE>{std::forward<E>(val)};
}


template <typename T, typename E>
class [[nodiscard]] Result {
    static_assert(!std::is_same<T, void>::value);
    static_assert(!std::is_same<E, void>::value);
public:
    Result() = delete;
    ~Result() = default;

    constexpr Result(internal::Ok<T>&& ok) : variant_(std::in_place_index<0>, std::move(ok.val)) {}
    constexpr Result(const internal::Ok<T>& ok) : variant_(std::in_place_index<0>, ok.val) {}

    constexpr Result(internal::Err<E>&& err) : variant_(std::in_place_index<1>, std::move(err.val)) {}
    constexpr Result(const internal::Err<E>& err) : variant_(std::in_place_index<1>, err.val) {}

    constexpr Result(Result&&) = default;
    constexpr Result(const Result&) = default;

    Result& operator=(Result&&) = default;
    Result& operator=(const Result&) = default;
public:
    [[nodiscard]]
    constexpr bool is_ok() const {
        return variant_.index() == 0;
    }

    [[nodiscard]]
    constexpr bool is_err() const {
        return variant_.index() == 1;
    }

    //----------------------------------------------------
    // ok
    [[nodiscard]]
    constexpr T& value() & {
        assert(is_ok());
        T* val = std::get_if<0>(&variant_);
        return *val;
    }

    [[nodiscard]]
    constexpr const T& value() const& {
        assert(is_ok());
        const T* val = std::get_if<0>(&variant_);
        return *val;
    }

    [[nodiscard]]
    constexpr T&& value() && {
        assert(is_ok());
        T* val = std::get_if<0>(&variant_);
        return std::move(*val);
    }

    constexpr T& operator*() const& {
        assert(is_ok());
        const T* val = std::get_if<0>(&variant_);
        return *val;
    }

    T& operator*() & {
        assert(is_ok());
        T* val = std::get_if<0>(&variant_);
        return *val;
    }

    T&& operator*() && {
        assert(is_ok());
        T* val = std::get_if<0>(&variant_);
        return std::move(*val);
    }

    constexpr T* operator->() const {
        assert(is_ok());
        return std::get_if<0>(&variant_);
    }

    T* operator->() {
        assert(is_ok());
        return std::get_if<0>(&variant_);
    }

    //----------------------------------------------------
    // error
    [[nodiscard]]
    constexpr E& error() & {
        assert(is_err());
        E* err = std::get_if<1>(&variant_);
        return *err;
    }

    [[nodiscard]]
    constexpr const E& error() const& {
        assert(is_err());
        const E* err = std::get_if<1>(&variant_);
        return *err;
    }

    [[nodiscard]]
    constexpr E&& error() && {
        assert(is_err());
        E* err = std::get_if<1>(&variant_);
        return std::move(*err);
    }
private:
    std::variant<T, E> variant_;
};


}  // namespace aribcaption

#endif  // ARIBCAPTION_RESULT_HPP
