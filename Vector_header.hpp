#ifndef VECTOR_HEADER_HPP
#define VECTOR_HEADER_HPP
size_t bv_size = sizeof(size_t) * 8;

template <typename T>
class MyVector {
	private:
		T* ptr;
		size_t v_size;
		size_t v_cap;
		T* cheater(T* tmp_ptr = nullptr, int tmp_size = 0, int tmp_cap = 0);

	public: 
		MyVector();
		MyVector(T, int);
		MyVector(std::initializer_list<T>);
		MyVector(const MyVector&);
		MyVector(MyVector&&);
		~MyVector()
		{
			if(ptr) {
					delete[] ptr;
			}
			v_size = 0;
			v_cap = 0;
		}
		
		size_t max_size();
		size_t size();
		void resize(int);
		size_t capacity();
		bool empty();
		void reserve(int);
		void shrink_to_fit();
		void allocator(int x = 0);
		void reallocator();
		void print();
		T& at(int);
		T& front();
		T& back();
		T* data();
		void assign(int, const T&);
		void push_back(const T&);
		void pop_back();
		void insert(const int&, const T&);
		void clear();
		void swap(MyVector&);
		void emplace(const int&, const T&);
		void emplace_back(const T&);
		int& operator[](size_t);
		MyVector& operator= (const MyVector&);
		MyVector& operator= (MyVector&&);
		std::ostream& operator<< (std::ostream& os)
		{
//			os << '{ ';
			for(int i = 0; i < v_size; ++i) {
				os << ptr[i] << " ";
			}
//			os << '}';
			return os;
		}
};


template<>
class MyVector<bool> {
	private:
		size_t* ptr;
		size_t v_size;
		size_t v_cap;
		size_t t_cap;
	
	public:
		MyVector();
		MyVector(bool value, int quantity);
		MyVector(const MyVector<bool>&);
		MyVector(MyVector<bool>&&);
		MyVector(std::initializer_list<bool>);
		~MyVector();


		size_t max_size();
		size_t size();
		size_t capacity();
		bool empty();
		void shrink_to_fit();
		void allocator();
		void reallocator(int size_changes = 1);
		void push_back(const bool&);
		void print();
		size_t* data();
		void reserve();
		void resize(size_t);
	//	void insert(size_t, const bool&);
		void reserve(int);
		void pop_back();
		void clear();
		void swap(MyVector<bool>&);

	class reference {
		public: 
			reference (size_t* ptr1, size_t index1);
			reference(const reference& obj);
			reference (reference&& obj);
			reference& operator= (const reference& obj);
			reference& operator= (const bool& flag);

			operator bool();
		private:
			size_t* r_ptr;
			size_t index;
			bool flag;
	};

	reference at(int);
	reference front();
	reference back();

	reference operator[](size_t index);
	MyVector& operator= (const MyVector& obj);
	MyVector& operator= (MyVector&& obj);
	std::ostream& operator<< (std::ostream& os)
	{
		for(size_t i = 0; i < v_size; ++i) {
			os << (ptr[i / bv_size] & (1ULL << (bv_size  -  (i % bv_size))));
		}
		return os;
	}
};

#include "Vector_implementation.hpp"

#endif //VECTOR_HEADER_HPP
