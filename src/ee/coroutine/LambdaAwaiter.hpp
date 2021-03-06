#ifndef EE_X_LAMBDA_AWAITER_HPP
#define EE_X_LAMBDA_AWAITER_HPP

#include <experimental/coroutine>
#include <functional>
#include <vector>

#include "ee/CoroutineFwd.hpp"

namespace ee {
namespace coroutine {
template <class Result>
struct LambdaAwaiter {
public:
    using Resolve = std::function<void(Result result)>;
    using Function = std::function<void(const Resolve& resolve)>;

    explicit LambdaAwaiter(const Function& f)
        : f_(f)
        , invoked_(false)
        , ready_(false) {}

    LambdaAwaiter(const LambdaAwaiter&) = delete;

    LambdaAwaiter(LambdaAwaiter&& other)
        : f_(std::exchange(other.f_, nullptr))
        , invoked_(std::exchange(other.invoked_, false))
        , ready_(std::exchange(other.ready_, false))
        , result_(std::exchange(other.result_, Result()))
        , handles_(std::exchange(other.handles_, {})) {}

    void await_suspend(std::experimental::coroutine_handle<> handle) {
        handles_.push_back(handle);
        if (invoked_) {
            // Waiting.
        } else {
            invoked_ = true;
            f_([this, handle](Result result) mutable {
                ready_ = true;
                result_ = result;
                for (auto&& handle : handles_) {
                    handle.resume();
                }
            });
        }
    }

    bool await_ready() { //
        return ready_;
    }

    Result await_resume() { //
        return result_;
    }

private:
    Function f_;
    bool invoked_;
    bool ready_;
    Result result_;
    std::vector<std::experimental::coroutine_handle<>> handles_;
};

template <>
struct LambdaAwaiter<void> {
    using Resolve = std::function<void()>;
    using Function = std::function<void(const Resolve& resolve)>;

    explicit LambdaAwaiter(const Function& f)
        : f_(f)
        , invoked_(false)
        , ready_(false) {}

    LambdaAwaiter(const LambdaAwaiter&) = delete;

    LambdaAwaiter(LambdaAwaiter&& other)
        : f_(std::exchange(other.f_, nullptr))
        , invoked_(std::exchange(other.invoked_, false))
        , ready_(std::exchange(other.ready_, false))
        , handles_(std::exchange(other.handles_, {})) {
        int x = 1;
    }

    ~LambdaAwaiter() { //
        int x = 1;
    }

    void await_suspend(std::experimental::coroutine_handle<> handle) {
        handles_.push_back(handle);
        if (invoked_) {
            // Waiting.
        } else {
            invoked_ = true;
            f_([this]() mutable {
                ready_ = true;
                for (auto&& handle : handles_) {
                    handle.resume();
                }
            });
        }
    }

    bool await_ready() { //
        return ready_;
    }

    void await_resume() {}

private:
    Function f_;
    bool invoked_;
    bool ready_;
    std::vector<std::experimental::coroutine_handle<>> handles_;
};
} // namespace coroutine
} // namespace ee

#endif // EE_X_LAMBDA_AWAITER_HPP
