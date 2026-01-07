#include "siplus/text/data.h"
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

    virtual text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

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

    virtual text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

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

text::UnknownDataTypeContainer 
rand_impl::retrieve(InvocationContext& container) const {
    auto ctx = context_.lock();

    unsigned long seed;
    if(seed_) {
        seed = ctx->convert<long>(seed_->retrieve(container)).as<long>();
    } else {
        seed = std::random_device{}();
    }

    if(!begin_) {
        std::mt19937 engine{seed};
        std::uniform_real_distribution<double> dist{0, 1};
        return text::make_data(dist(engine));
    } else {
        auto begin = ctx->convert<long>(begin_->retrieve(container)).as<long>();
        auto end = ctx->convert<long>(end_->retrieve(container)).as<long>();

        std::mt19937 engine{seed};
        std::uniform_int_distribution<long> dist{begin, end};
        auto ret = dist(engine);

        return text::make_data(ret);
    }
}

std::shared_ptr<text::ValueRetriever> rand_str_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [ characters, length ] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<rand_str_impl>(context_, characters, length);
}

text::UnknownDataTypeContainer 
rand_str_impl::retrieve(InvocationContext& value) const {
    auto ctx = context_.lock();
    auto characters = ctx->convert<std::string>(characters_->retrieve(value)).as<std::string>();
    auto length = ctx->convert<long>(length_->retrieve(value)).as<long>();

    std::string str{};
    str.resize(length, ' ');

    std::mt19937 engine = std::mt19937{std::random_device{}()};
    std::uniform_int_distribution<uint64_t> dist(0, characters.length() - 1);

    for(int i = 0; i < length; i++) {
        size_t idx = dist(engine);
        str[i] = characters[idx];
    }

    return text::make_data(str);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
