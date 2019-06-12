#ifndef FLATTENED_H
#define FLATTENED_H

// https://stackoverflow.com/questions/44508979/boost-range-adaptor-flattened

#include <boost/range/adaptors.hpp>
#include <boost/range/iterator_range.hpp>

template <typename OuterIterator> class flattening_iterator
{
public:
    using outer_iterator = OuterIterator;
    using inner_iterator = typename OuterIterator::value_type::iterator;

    using iterator_category = std::forward_iterator_tag;
    using value_type = typename inner_iterator::value_type;
    using difference_type = typename inner_iterator::difference_type;
    using pointer = typename inner_iterator::pointer;
    using reference = typename inner_iterator::reference;

    flattening_iterator()
    {
    }
    flattening_iterator(outer_iterator it)
        : outer_it_(it)
        , outer_end_(it)
    {
    }
    flattening_iterator(outer_iterator it, outer_iterator end)
        : outer_it_(it)
        , outer_end_(end)
    {
        if (outer_it_ == outer_end_)
        {
            return;
        }

        inner_it_ = outer_it_->begin();
        advance_past_empty_inner_containers();
    }

    reference operator*() const
    {
        return *inner_it_;
    }
    pointer operator->() const
    {
        return &*inner_it_;
    }

    flattening_iterator& operator++()
    {
        ++inner_it_;
        if (inner_it_ == outer_it_->end())
            advance_past_empty_inner_containers();
        return *this;
    }

    flattening_iterator operator++(int)
    {
        flattening_iterator it(*this);
        ++*this;
        return it;
    }

    friend bool operator==(const flattening_iterator& a, const flattening_iterator& b)
    {
        if (a.outer_it_ != b.outer_it_)
            return false;

        if (a.outer_it_ != a.outer_end_ && b.outer_it_ != b.outer_end_ && a.inner_it_ != b.inner_it_)
            return false;

        return true;
    }

    friend bool operator!=(const flattening_iterator& a, const flattening_iterator& b)
    {
        return !(a == b);
    }

private:
    void advance_past_empty_inner_containers()
    {
        while (outer_it_ != outer_end_ && inner_it_ == outer_it_->end())
        {
            ++outer_it_;
            if (outer_it_ != outer_end_)
                inner_it_ = outer_it_->begin();
        }
    }

    outer_iterator outer_it_;
    outer_iterator outer_end_;
    inner_iterator inner_it_;
};

template <typename Iterator> flattening_iterator<Iterator> flatten(Iterator it)
{
    return flattening_iterator<Iterator>(it, it);
}

template <typename Iterator> flattening_iterator<Iterator> flatten(Iterator first, Iterator last)
{
    return flattening_iterator<Iterator>(first, last);
}

template <typename R>
struct flat_range : boost::iterator_range<flattening_iterator<typename boost::range_iterator<R>::type>>
{
public:
    using iterator = flattening_iterator<typename boost::range_iterator<R>::type>;

private:
    using base = boost::iterator_range<iterator>;

public:
    flat_range(R& r)
        : base(iterator(boost::begin(r), boost::end(r)), iterator(boost::end(r)))
    {
    }
};

namespace flatten_detail
{
    struct flat_forwarder
    {
    };
};

template <class R> inline flat_range<R> operator|(R&& r, flatten_detail::flat_forwarder)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::SinglePassRangeConcept<R>));

    return flat_range<R>(r);
}

template <class R> inline flat_range<const R> operator|(const R& r, flatten_detail::flat_forwarder)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::SinglePassRangeConcept<const R>));

    return flat_range<const R>(r);
}

namespace
{
    const flatten_detail::flat_forwarder flattened = flatten_detail::flat_forwarder();
}

#endif // FLATTENED_H
