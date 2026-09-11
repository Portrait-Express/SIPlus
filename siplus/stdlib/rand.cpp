#include <random>

#include "siplus/util.hxx"
#include "siplus/stl/functions/rand.hxx"

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

struct rand_impl : ValueRetriever {
    rand_impl(
        std::shared_ptr<ValueRetriever> begin,
        std::shared_ptr<ValueRetriever> end
    ) : begin_(begin), end_(end) {}

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> begin_;
    std::shared_ptr<ValueRetriever> end_;
};

struct rand_str_impl : ValueRetriever {
    rand_str_impl(
        std::shared_ptr<ValueRetriever> characters,
        std::shared_ptr<ValueRetriever> length
    ) : characters_(characters), length_(length) {}

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> characters_;
    std::shared_ptr<ValueRetriever> length_;
};

} /* anonymous */

std::shared_ptr<ValueRetriever> rand_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [begin, end] = util::get_parameters_first_parent<0, 2>(parent, parameters);

    if(begin && !end) {
        throw std::runtime_error{"Must specify both begin and end, only begin was specified"};
    }

    return std::make_shared<rand_impl>(begin, end);
}

UnknownDataTypeContainer 
rand_impl::retrieve(InvocationContext& container) const {

    std::mt19937::result_type seed = std::random_device{}();

    if(!begin_) {
        std::mt19937 engine{seed};
        std::uniform_real_distribution<double> dist{0, 1};
        return make_data<types::FloatType>(dist(engine));
    } else {
        auto begin = begin_->retrieve(container).convert<types::IntegerType>().as<types::IntegerType>();
        auto end = end_->retrieve(container).convert<types::IntegerType>().as<types::IntegerType>();

        std::mt19937 engine{seed};
        std::uniform_int_distribution<int64_t> dist{begin, end};
        auto ret = dist(engine);

        return make_data<types::IntegerType>(ret);
    }
}

std::shared_ptr<ValueRetriever> rand_str_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [ characters, length ] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<rand_str_impl>(characters, length);
}

UnknownDataTypeContainer 
rand_str_impl::retrieve(InvocationContext& value) const {
    auto characters = characters_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto length = length_->retrieve(value).convert<types::IntegerType>().as<types::IntegerType>();

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
