#pragma once

#include <iterator>
#include <algorithm>

struct DefaultStep
{
	static constexpr int value = 1;
};

template<class V> class DefaultCompare
{
public:
	static bool Compare(const V& a, const V& b)
	{
		return a < b;
	}
};

template<class V, typename Step = DefaultStep, typename Compare = DefaultCompare<V>> class range
{
	V left;
	V right;
public:
	class Iterator : public std::iterator<std::bidirectional_iterator_tag, V, V>
	{
		V value;
	public:
		Iterator(V val) : value(val) {}
		Iterator(const Iterator& i) : value(i.value) {}

		V operator*() { return value; }
		Iterator operator++() { value += Step::value; return *this; }
		Iterator operator++(int) { Iterator i = *this; value += Step::value; return i; }
		Iterator operator--() { value -= Step::value; return *this; }
		Iterator operator--(int) { Iterator i = *this; value -= Step::value; return i; }
		bool operator!=(const Iterator& i) const
		{
			return Compare::Compare(value, i.value);
		}
		bool operator==(const Iterator& i) const
		{
			return !((*this) != i);
		}
	};

	range(const range& r) : left(r.left, r.right) {}
	range(V l, V r) : left(l), right(r) {}

	Iterator begin() const
	{
		return Iterator(left);
	}

	Iterator end() const
	{
		return Iterator(right);
	}

	template<class C> C convert() const
	{ 
		return C(begin(), end());
	}

	range operator&(const range& r) const
	{
		/*constexpr*/ if ( std::is_same<Step, DefaultStep>() )
		{
			return range(std::max(r.left, left), std::min(r.right, right));
		}

		return range(0, 0);
	}
};