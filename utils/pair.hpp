#ifndef __PAIR_HPP__
#define __PAIR_HPP__
#include <utility>

namespace ft
{
	template <class T1, class T2>
	struct pair
	{

		// member types
		typedef T1 first_type;
		typedef T2 second_type;

		// member varaibles
		first_type first;
		second_type second;

		// member functions
		pair(){};

		pair(const pair<T1, T2> &pr) : first(pr.first), second(pr.second)
		{
			*this = pr;
		};

		pair(const first_type &a, const second_type &b)
		{
			this->first = a;
			this->second = b;
		}

		pair &operator=(const pair &pr)
		{
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return *this;
		}

	};

	// relational operators for pair

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}

};

#endif