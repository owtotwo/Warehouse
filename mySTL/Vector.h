// Reimplementation of the vector in stl
//
// -----------------------------------------------------------------
// i.e.
// #include <iostream>
// #include "Vector.h"
//
// int main() {
// stl::vector<int> arr1(10);
// stl::vector<char> arr2(10, 0);
// stl::vector<char> arr3(arr2);
// stl::vector<char> arr4(arr2.begin() + 1, arr2.end() - 1);
//
// for (int i = 0; i < arr.size(); i++)
// 	arr1[i] = i + 1;
//
// arr1.push_back(11);
// arr1.erase(arr1.begin() + 1, arr1.begin() + 5);
// arr1.insert(arr1.end() - 1, 99);
//
// std::cout << "Output : ";
// stl::vector<int>::iterator it;
// for (it = arr1.begin(); it != arr1.end(); it++)
// 	std::cout << *it << ' ';
// std::cout << '\n';
//
// return 0;
// }
//
// /* Output : 1 6 7 8 9 10 99 11 */
//
// -----------------------------------------------------------------
// PS : it does not implement the reverse_iterator so that it can't
// 	call the 'rbegin()' or 'rend()' and any function with rele-
// 	vant to the reverse iterator.
// -----------------------------------------------------------------

#pragma

#include <cstring>

namespace stl {
	// stl::vector
	template <typename T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;

		
	
	// ****************************************

		// default ctor
		vector<T>() : start(NULL), finish(NULL), end_of_storage(NULL) {}
		// copy ctor
		vector<T>(const vector& pt) {
			const int Ssize = pt.size();
			start = new T[Ssize];
			finish = start + Ssize;
			end_of_storage = finish;
			memcpy(start, pt.begin(), Ssize * sizeof(T));
		}
		// size init
		vector<T>(const size_type& n) {
			start = new T[n];
			finish = start + n;
			end_of_storage = finish;
		}

		vector<T>(const size_type& n, const_reference value) {
			start = new T[n];
			finish = start + n;
			end_of_storage = finish;
			iterator it = start;
			while (it != finish) {
				*it = value;
				it++;
			}
		}

		~vector<T>() {delete[] start;}	// destroyer

		iterator begin() {return start;}
		const_iterator begin() const {return start;}
		iterator end() {return finish;}
		const_iterator end() const {return finish;}
		reference back() {return *(end() - 1);}
		reference front() {return *begin();}

		size_type size() const {return finish - start;}
		size_type capacity() const {return end_of_storage - start;}
		size_type max_size() const {return MAX_CAPACITY_SIZE;}

		reference operator[](const size_type& index) {
			return *(start + index);
		}
		const_reference operator[](const size_type& index) const {
			return *(start + index);
		}



		bool empty() {return finish == start;}
		void clear() {finish = start;}

		void reserve(const size_type &n) {
			if (n <= capacity()) return;
			if (n > MAX_CAPACITY_SIZE) 
				throw "The allocated size is greater than the MAX_CAPACITY_SIZE";
			iterator tmp = new T[n];
			size_type size_tmp = size();

			memcpy(tmp, start, size_tmp * sizeof(T));

			delete[] start;
			start = tmp;
			finish = tmp + size_tmp;
			end_of_storage = start + n;
		}

		void assign(const_iterator left, const_iterator right) {
			size_type n = right - left;
			if (n > capacity()) {
				delete[] start;
				start = new T[n];
			}
			memcpy(start, left, n);
			finish = start + n;
			end_of_storage = finish;
		}

		void assign(const size_type &n, const_reference value) {
			if (n > capacity()) {
				delete[] start;
				start = new T[n];
			}
			for (size_type i = 0; i < n; i++) {
				*(start + i) = value;
			}
			finish = start + n;
			end_of_storage = finish;
		}

		void push_back(const_reference value) {
			if (finish == end_of_storage) {
				size_type tmp = capacity() ? (capacity() * 2) : 1;
				reserve(tmp);
			}
			*finish = value;
			++finish;
		}

		void pop_back() {
			if (empty()) return;
			--finish;
		}

		void insert(const iterator& it, const_reference value) {
			if (finish == end_of_storage) {
				reserve(capacity() * 2);
			}
			memcpy(it + 1, it, (finish - it) * sizeof(T));
			*it = value;		
		}

		iterator erase(const iterator& left, const iterator& right) {
			if (right < left) 
				throw "The right argument should greater than the left.";
			if (left >= finish) return finish;
			iterator r = right, l = left;
			if (right > finish) r = finish;
			memcpy(l, r, (finish - r) * sizeof(T));
			finish -= r - l;
			return l;
		}

		iterator erase(const iterator& pos) {
			return erase(pos, pos + 1);
		}

		vector<T>& operator=(const vector& pt) {
			assign(pt.begin(), pt.end());
			return *this;
		}

		void set(const_iterator st, const_iterator fi, const_iterator eos) {
			start = st, finish = fi, end_of_storage = eos;
		}

		void swap(vector& value) {
			iterator t1 = start, t2 = finish, t3 = end_of_storage;

			start = value.begin();
			finish = value.end();
			end_of_storage = start + value.capacity();

			value.set(t1, t2, t3);
		}

	protected:
		iterator start;		// begin();
		iterator finish;	// end();
		iterator end_of_storage;	// capacity();

		static const size_type MAX_CAPACITY_SIZE;
	};

	// static const value initailized
	template <typename T>
	typename vector<T>::size_type const vector<T>::MAX_CAPACITY_SIZE = -1;
};

