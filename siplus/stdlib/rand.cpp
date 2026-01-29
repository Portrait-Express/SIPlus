#include "siplus/data.h"
#include "siplus/types/float.h"
#include "siplus/types/integer.h"
#include "siplus/types/string.h"
#include "siplus/util.h"
#include "siplus/stl/functions/rand.h"
#include <random>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

template<std::uniform_random_bit_generator T>
T get_rand_engine() {
    std::random_device rd;
    return T{rd()};
}

template<std::unsigned_integral UInt = uint64_t, 
    std::uniform_random_bit_generator E = std::mt19937>
UInt rand() {
    static E engine = get_rand_engine<E>();
    static std::uniform_int_distribution<UInt> dist(
            std::numeric_limits<UInt>::min(),
            std::numeric_limits<UInt>::max());
    return dist(engine);
}

struct rand_impl : text::ValueRetriever {
    rand_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> begin,
        std::shared_ptr<text::ValueRetriever> end,
        std::shared_ptr<text::ValueRetriever> seed
    ) : context_(context), begin_(begin), end_(end), seed_(seed) {}

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> begin_;
    std::shared_ptr<text::ValueRetriever> end_;
    std::shared_ptr<text::ValueRetriever> seed_;
};

struct rand_str_impl : text::ValueRetriever {
    rand_str_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> characters,
        std::shared_ptr<text::ValueRetriever> length
    ) : context_(context), characters_(characters), length_(length) {}

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> characters_;
    std::shared_ptr<text::ValueRetriever> length_;
};

} /* anonymous */

std::shared_ptr<text::ValueRetriever> rand_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [begin, end, seed] = util::get_parameters_first_parent<0, 3>(parent, parameters);
    return std::make_shared<rand_impl>(context_, begin, end, seed);
}

UnknownDataTypeContainer 
rand_impl::retrieve(InvocationContext& container) const {
    auto ctx = context_.lock();

    unsigned long seed;
    if(seed_) {
        seed = ctx->convert<types::IntegerType>(seed_->retrieve(container)).as<types::IntegerType>();
    } else {
        seed = std::random_device{}();
    }

    if(!begin_) {
        std::mt19937 engine{seed};
        std::uniform_real_distribution<double> dist{0, 1};
        return make_data<types::FloatType>(dist(engine));
    } else {
        auto begin = ctx->convert<types::IntegerType>(begin_->retrieve(container)).as<types::IntegerType>();
        auto end = ctx->convert<types::IntegerType>(end_->retrieve(container)).as<types::IntegerType>();

        std::mt19937 engine{seed};
        std::uniform_int_distribution<long> dist{begin, end};
        auto ret = dist(engine);

        return make_data<types::IntegerType>(ret);
    }
}

std::shared_ptr<text::ValueRetriever> rand_str_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [ characters, length ] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<rand_str_impl>(context_, characters, length);
}

UnknownDataTypeContainer 
rand_str_impl::retrieve(InvocationContext& value) const {
    auto ctx = context_.lock();
    auto characters = ctx->convert<types::StringType>(characters_->retrieve(value)).as<types::StringType>();
    auto length = ctx->convert<types::IntegerType>(length_->retrieve(value)).as<types::IntegerType>();

    std::string str{};
    str.resize(length, ' ');

    std::mt19937 engine = std::mt19937{std::random_device{}()};
    std::uniform_int_distribution<uint64_t> dist(0, characters.length() - 1);

    for(int i = 0; i < length; i++) {
        size_t idx = dist(engine);
        str[i] = characters[idx];
    }

    return make_data<types::StringType>(str);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
