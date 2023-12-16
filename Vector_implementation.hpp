std::ostream& operator<< (std::ostream& os, MyVector<bool>& obj)
{
	return obj.operator<<(os);	
}
//operator<<
template<typename T>
std::ostream& operator<< (std::ostream& os, MyVector<T>& vec)
{
	return vec.operator<<(os);
}
//Move assignment operator
template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& obj)
{
	if(this != &obj) {
		//copies obj to this
		v_size = obj.v_size;
		v_cap = obj.v_cap;
		if(ptr) {
			delete[] ptr;
		}
		ptr = new T [v_cap];
		//organizing deep copy
		for(int i = 0; i < v_size; ++i) {
			ptr[i] = obj[i];
		}
		// if obj.ptr isn't equal to nullptr then it deletes ptr
		if(obj.ptr) {
			delete[] obj.ptr;
		}
		//deletes the object
		obj.ptr = nullptr;
		obj.v_size = 0;
		obj.v_cap = 0;
		}

	return *this;
	
}

//Copy assignment operator
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& obj)
{
	if(this != &obj) {
		//assigning obj's content to this with deep copy 
		v_size = obj.v_size;
		v_cap = obj.v_cap;
		if(ptr) {
			delete[] ptr;
		}	
		ptr = new T[v_cap];
	
		for(int i = 0; i < v_size; ++i) {
			ptr[i] = obj.ptr[i];
		}
	}
		return *this;
}

//Subscript operator
template <typename T>
int& MyVector<T>::operator[](size_t index)
{
	//overloading  []operator to use with objects
	if(index < 0  || index >= v_size) {
	
		std::cout << "Undefined reference " << std::endl;
		exit(0);
	
	}
	return ptr[index]; 
}


//Move constructor
template <typename T>
MyVector<T>::MyVector(MyVector&& vec)
{
		v_size = vec.v_size;
		v_cap = vec.v_cap;
		ptr = vec.ptr;

		vec.v_size = 0;
		vec.v_cap = 0;
		vec.ptr = nullptr;
	
}

//Copy constructor
template <typename T>
MyVector<T>::MyVector(const MyVector& obj)
{
	v_size = obj.v_size;
	v_cap = obj.v_cap;
	ptr = new T[v_cap];

	for(int i = 0; i < v_size; ++i) {
		ptr[i] = obj.ptr[i];
	}

}
//Initializer_list constructor
template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
{
	v_size = list.size();
	v_cap = v_size;
	ptr = new T[v_cap];

	for(int i = 0; i < v_size; ++i)
	{
		ptr[i]  = *(list.begin() + i);
	}

}

// Parameterized constructor
template <typename T>
MyVector<T>::MyVector(T value, int quantity)
{
	if(quantity <= 0) {
		std::cout << "Invalid operation " << std::endl;
		exit(0);
	}
	v_size = quantity;
	v_cap = v_size;
	ptr = new T{v_cap};
	for(int i =  0; i < v_size; ++i) {
			ptr[i] = value;
	}
}

//Default constructor
template <typename T>
MyVector<T>::MyVector() 
{
    ptr = nullptr;
    v_size = 0;
    v_cap = 0;

}

//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
template <typename T>
void MyVector<T>::assign(int length, const T& val)
{
	if(length <= 0) {
			std::cout << "Length error" << std::endl;
			exit(0);
	}
	
	if(length < v_cap) {
		for (int i = 0; i < length; ++i) { 
				ptr[i] = val;
		}
		v_size = length;
		return;
	}

	if(ptr) {
		delete[] ptr;
	}
	
	allocator(length);
	for (int i = 0; i < v_cap; ++i) { 
			ptr[i] = val;
	}
	v_size = length;

}


// Emplaces a new element at the end of the vector.
// Doubles the capacity if necessary before insertion.
template <typename T>
void MyVector<T>::emplace_back(const T& val)
{							
	if(!ptr) {
		allocator();
	}

	if(v_size + 1 > v_cap) {
		reallocator();
	}

	ptr[v_size++] = val;

}
		
// Emplaces a new element at the specified position in the vector.
// Shifts existing elements by one.
template <typename T>
void MyVector<T>::emplace(const int& pos, const T& val)
{

		if(pos >= 0 && pos < v_size) {
				if(v_size + 1 <= v_cap) {
						
						for(int i = v_size; i > pos; --i) {
							ptr[i] = ptr[i - 1];
						}

						ptr[pos] = val;
						++v_size;
				
				} else {
					
						reallocator();
						emplace(pos, val);
				}
		
		} else {
				std::cout << "Segmentation fault " << std::endl;
		}

}
/*
//Function to chnage the content of the object, or to get the pointer of the object 
template <typename T>
T* MyVector<T>::cheater(T* tmp_ptr, int tmp_size, int tmp_cap)
{
	if(tmp_ptr == nullptr) {
		return ptr;
	}

	ptr = tmp_ptr;
	v_size = tmp_size;
	v_cap = tmp_cap;
	return ptr;

}

//Exchanges the content of the container by the content of obj, which is another vector object of the same type. Sizes may differ.
template <typename T>
void MyVector<T>::swap(MyVector& obj)
{
	T* tmp_ptr = obj.cheater();
	int tmp_size = obj.size();
	int tmp_cap = obj.capacity();
	ptr = obj.cheater(ptr, v_size, v_cap);
	ptr = tmp_ptr;
	v_size = tmp_size;
	v_cap = tmp_cap;
	tmp_ptr = nullptr;

}
*/

//Function that swapes the contents of two objects (2nd version)
template <typename T>
void MyVector<T>::swap(MyVector& obj)
{
	std::swap(ptr, obj.ptr);
	std::swap(v_size, obj.v_size);
	std::swap(v_cap, obj.v_cap);
}


//Removes all elements from the vector, leaving the container with a size of 0.
template <typename T>
void MyVector<T>::clear()
{
	v_size = 0;
}

//Function to insert an element at a specific index.
//The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
template <typename T>
void MyVector<T>::insert(const int& pos, const T& value)
{
	//checks if the position is valid for the vector
	if(pos >= 0 && pos <= v_size) {
		//checks if vector can hold one more element
		if(v_size + 1 <= v_cap) {
			for(int i = v_size; i >= pos; --i) {
					ptr[i] = ptr[i - 1];
				}
				ptr[pos] = value;
				 ++v_size;

		} else { 
			//reallocates new memeory as the vector couldn't hold one mor element, this doubles its capacity
			reallocator();
			insert(pos, value);
		}
				
	} else {
		std::cout << "Segmentation fault" << std::endl;
	}
}

// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
template <typename T>
T* MyVector<T>::data()
{
	if(!ptr) {
		std::cout << "Segmentation fault "<< std::endl;
		exit(0);
	}
	return ptr;
}

// Returns a reference to the last element in the vector. Calling this function on an empty container causes undefined behavior.
template <typename T>
T& MyVector<T>::back()
{
	if(!v_size) {
		std::cout << "Undefined behavior" << std::endl;
		exit(0);
	}
	return ptr[v_size - 1];
}

//Returns a reference to the first element in the vector. Calling this function on an empty container causes undefined behavior.
template <typename T>
T& MyVector<T>::front()
{
	if(v_size == 0){
		std::cout << "Undefined reference" << std::endl;
		exit(0);
	}
	return ptr[0];
} 

//Function to remove the last element in the vector, effectively reducing the container size by one. This destroys removed element.
template <typename T>
void MyVector<T>::pop_back()
{
	if(v_size) {
		--v_size;
	}
}

//Function to print vector's elements
template <typename T> 
void MyVector<T>::print()
{

	for(int i = 0; i < v_size; ++i){
		std::cout << ptr[i] << " ";
	}
	std::cout << std::endl;
}

//Function which allocates memory for the vector
template <typename T>
void MyVector<T>::allocator(int x)
{
	//if no argument is passed,this creates vector, which  capacity is 1, and size is 0.
	if(x == 0) {
		ptr = new T;
		v_cap = 1;
	} else {
		//this creates vector with x capacity and  0 size.
		ptr = new T[x];
		v_cap = x;
	}
}

//Reallocates memeory for the vector, accordingly changes its capacity
template <typename T>
void MyVector<T>::reallocator()
{		
	//doubles the capacity of the vector
	v_cap *= 2; 
	//creates new vector with doubled capacity
	T* tmp_ptr = new T[v_cap];

	//rewrites the content of this into new created vector
	for(int i = 0; i < v_size; ++i) {
		tmp_ptr[i] = ptr[i];
	}
	delete[] ptr;
	ptr = tmp_ptr;
	tmp_ptr = nullptr;
}

// Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
template <typename T>
void MyVector<T>::push_back(const T& a)
{
	//if ptr == nullptr  then allocates new memory
	if(!ptr) {
		allocator();
	}

	//if vector can't hold one more element then it reallocates its memeory, accordingly doubling the capacity
	if(v_size + 1 > v_cap) {
		reallocator();
	}
	ptr[v_size++] = a;
}

//Function that returns a reference to the element at position n in the vector.
template <typename T> 
T& MyVector<T>::at(int n) 
{
	if(( n >= v_size) || n < 0) {			//if n is not in the range of [0, v_size - 1] then print a message and exit the function 
		std::cout << "Invalid reference" << std::endl;
		exit(0);
	}
	return ptr[n];				
}

//Function that requests the container to reduce its capacity to fit its size.
template <typename T>
void MyVector<T>::shrink_to_fit()
{
	if(v_cap == v_size) {
		return;
	}
	v_cap = v_size;
	T* tptr = new T[v_size];				//reallocating memory with the size of v_size, which  means that the new vector  won't contain any extra memeory
	for(int i = 0; i < v_size; ++i) {		//rewrite  elemets of old vector into new one 
		tptr[i] = ptr[i];
	}
	delete[] ptr;
	ptr = tptr;
	tptr = nullptr;
}

//Requests that the vector capacity be at least enough to contain n elements.
template <typename T> 
void MyVector<T>::reserve(int tmp_size)
{
	//checking if the tmp_size is negativ
	if(tmp_size < 0) {
		std::cout << "Invalid size for vector" << std::endl;
		return;
	}
	//if tmp_size is greater than v_cap  then allocates new memory with the  size of tmp_size.
	if(v_cap < tmp_size){
		T* tptr = new T[tmp_size];
		for(int i = 0; i < v_size; ++i) {
			tptr[i] = ptr[i];
		}
		delete[] ptr;
		ptr = tptr;
		tptr = nullptr;

		//assigns tmp_size to capacity of vector
		v_cap = tmp_size;
	}
	
}

//Returns whether the vector is empty (i.e. whether its size is 0).
template <typename T> 
bool MyVector<T>::empty() 
{
	return v_size == 0;
}

// Function to get the current capacity of the vector
template <typename T>
size_t MyVector<T>::capacity()		
{
	return v_cap;
}

//Resizes the container so that it contains n elements.
template <typename T>
void MyVector<T>::resize(int new_size)	
{	
	if(new_size > v_cap) {				 
		v_cap = new_size;
		T* tmp = new T[v_cap];
		for(int i = 0; i < v_size; ++i) {
			tmp[i] = ptr[i];
		}
		delete[] ptr;
		ptr = tmp;
		tmp = nullptr;
	} else if(new_size > v_size) {				
		// v_size < new_size <= v_cap

			for(int i = v_size; i < new_size; ++i) {
				ptr[i] = 0;
			}
	}

	v_size = new_size;
}

// Returns the maximum number of elements that the vector can hold.
template <typename T>
size_t MyVector<T>::max_size()		
{	
	return 1073741823;
}

//Function to return the current size of the vector
template <typename T>
size_t MyVector<T>::size()			//returning size of the vector 
{
	return v_size; 
}


//////////////////////////////////////////////////////////////////////////////////BOOL_VECTOR_SPECIALIZATION//////////////////////////////////////////////////////////////////////////////////////////

//default constructor
MyVector<bool>::MyVector()
{
	ptr = nullptr;
	v_size = 0;
	v_cap = 0;
	t_cap = 0;
}

//destructor
MyVector<bool>::~MyVector()
{
	if(ptr) {
		delete[] ptr;
	}
	v_size = 0;
	v_cap = 0;
	t_cap = 0;

}

//max_size of vector
size_t MyVector<bool>::max_size()
{
	return  4294967295 ;		
}

//returns current  size of the vector
size_t MyVector<bool>::size()
{
	return v_size;
}

//returns capacity of the container
size_t MyVector<bool>::capacity()
{
	return t_cap;
}

//Checks wheter the container is empty or not
bool MyVector<bool>::empty()
{
	return v_size == 0;
}

//Requests the container to reduce its capacity to fit its size.
void MyVector<bool>::shrink_to_fit()
{
	if(v_cap == v_size) {
		return;
	}
	t_cap = v_size;
	size_t block_count = v_size % bv_size ? v_size / bv_size + 1 : v_size / bv_size ;
	size_t* tptr = new size_t[block_count];

	for(int i = 0; i < block_count; ++i) {				 
		tptr[i] = ptr[i];
	}
		
	v_cap = block_count * bv_size;
	delete[] ptr;
	ptr = tptr;
	tptr = nullptr;
}

//Allocates memory for container
void MyVector<bool>::allocator()
{
	ptr = new size_t[1];
	*ptr = 0;
	v_cap = bv_size;
	t_cap = v_cap;
}

//Reallocates memory 
void MyVector<bool>::reallocator(int size_changes)
{
	size_t* tmp;
			if(size_changes == 1 && v_size == 0){
				tmp = new size_t;
				if(v_cap == 0) {
					v_cap = bv_size;
				}
			} else if( size_changes == 1) {
				tmp = new size_t[(v_size / bv_size) + 2];
				v_cap += bv_size;
				t_cap = v_cap;
			}
	for(size_t i = 0; i < v_cap / bv_size; ++i) {
		tmp[i] = ptr[i];
	}
	delete[] ptr;
	ptr = tmp;
	tmp = nullptr;
}

//Adds a new element at the end of the vector, increases size by one
void MyVector<bool>::push_back(const bool& elem)
{
	size_t x = 1;
    if (v_size == v_cap)
    {
        v_cap = (v_cap + 63) / 64 * 64;
        size_t* tmp = new size_t[(v_cap + 63) / 64 + 1];
        for (size_t i = 0; i < v_size / 64; ++i)
        {
            tmp[i] = ptr[i];
        }
        if (ptr)
        {
            delete [] ptr;
        }

        ptr = tmp;
        tmp = nullptr;
        v_cap += 64;
    }
    if (elem)
    {
        ptr[v_size / 64] |= (x << (64 - v_size % 64));
    }
    else
    {
        ptr[v_size / 64] &= ~(x << (64 - v_size % 64));
    
	}
	t_cap = v_cap;
    ++v_size;
}

//printing the elements of the vector (blocks of size_t)
void MyVector<bool>::print() 
{
    size_t x = 1;
    for (size_t i = 0; i < v_size; ++i) 
    {
        if (i % bv_size == 0)
        {
            std::cout << " ";
        }
        std::cout << bool(ptr[i / bv_size] & (x << (bv_size - (i % bv_size))));
    }
    std::cout << std::endl;
}

//This returns a pointer to the vector's first element
size_t* MyVector<bool>::data()
{
	return this -> ptr;
}

//This requests the vector capacity to be at least enough  to conatin n elemennts
void MyVector<bool>::reserve(int new_cap)
{

	if(new_cap > v_size) {
			int real_size = new_cap % v_cap ? new_cap / v_cap + 1 : new_cap / v_cap;
			size_t* tmp = new size_t[real_size];
			if(ptr) {
				for(int i = 0; i < v_cap / bv_size; ++i) {
					tmp[i] = ptr[i];
				}
				delete[] ptr;
			}
			ptr = tmp;
			tmp = nullptr;
			v_cap = real_size * bv_size;
			t_cap = new_cap;
			
	}

}
// Resize - Change size
void MyVector<bool>::resize(size_t new_size)
{
    if (new_size > v_size)
	{
		if (new_size < 0 || new_size == v_size) {
		    return;
	    }
        if (new_size > v_cap)
        {
            size_t block_count = (new_size + 63) / 64;
            size_t* tmp = new size_t[block_count]();
            size_t old_block_count = (v_size + 63) / 64;
            if (ptr)
            {
                for (size_t i = 0; i < old_block_count; ++i)
                {
                    tmp[i] = ptr[i];
                }
                delete[] ptr;
            }
            ptr = tmp;
            v_cap = block_count * 64;
            t_cap = v_cap;

        }
}
    else if (new_size < v_size)
    {
        if ((v_size / 64) == (new_size / 64))   // in same blocks
        {
            ptr[v_size / 64] &= (-1ULL << (63 - new_size % 64));
        }
        else    // in different blocks
        {
            ptr[new_size / 64] &= (-1ULL << (63 - new_size % 64));
            for(size_t i = new_size / 64 + 1; i < v_cap / 64; ++i)
            {
				ptr[i] = 0;
			}
        }
    }

    else    //v_size < new_size <= v_cap
    {
		// changing size without changing capacity
		int i = 64  - v_size;
		int block_index  = v_size / 64;
		ptr[block_index] &= (-1ULL << i);         //0-acnum enq iren hajordox elementnery;
	}
    v_size = new_size;
}

//
void MyVector<bool>::pop_back()
{
	size_t x = 1;
    if (v_size == 0)
    {
        return;
    }
    v_size--;
    
	size_t block_index = v_size / 64;
    size_t bit_position = v_size % 64;
    size_t mask = ~(x << 64 - bit_position);
    ptr[block_index] &= mask;
}

void MyVector<bool>::clear()
{	
	if(!ptr) {
		return;
	}
		v_size = 0;
		v_cap = 0;
		t_cap = v_cap;
		delete[] ptr;
		ptr = nullptr;
}

void MyVector<bool>::swap(MyVector<bool>& obj)
{
		std::swap(this -> v_size, obj.v_size);
		std::swap(this -> v_cap, obj.v_cap);
		std::swap(this -> t_cap, obj.t_cap);
		std::swap(this -> ptr, obj.ptr);
}


MyVector<bool>::reference MyVector<bool>::operator[](size_t index)
{
	return MyVector<bool>::reference(ptr, index);
}

MyVector<bool>::reference MyVector<bool>::at(int position)
{
	if(position >= v_size || position < 0 || ptr == nullptr) 
	{
		std::cout << "Out of range"<< std::endl;
		exit(0);
	}
		return MyVector<bool>::reference(ptr, position);
}

MyVector<bool>::reference  MyVector<bool>::front()
{
	if(ptr == nullptr || v_size == 0)
	{
		std::cout << "segmentation fault" << std::endl;
	}
	return MyVector<bool>::reference(ptr, 0);
}

MyVector<bool>::reference MyVector<bool>::back()
{
	if(ptr == nullptr || v_size == 0 )
	{
		std::cout << "Segmentation fault." << std::endl;
	}
	return MyVector<bool>::reference(ptr, v_size - 1);
}

MyVector<bool>::reference::operator bool() 
{
	return flag; 
}

MyVector<bool>::reference::reference(size_t* ptr1, size_t index1):r_ptr(ptr1), index(index1)
{
	size_t x = 1;
	flag = r_ptr[index / bv_size] & (x << (bv_size - (index % bv_size)));		
}

MyVector<bool>::reference& MyVector<bool>::reference::operator= (const reference& obj)
{
	if(flag != obj.flag)
	{
		this -> r_ptr[index / bv_size] ^= (1ULL << (bv_size - (index % bv_size)));
	}
	return *this;
}
MyVector<bool>::reference& MyVector<bool>::reference::operator= (const bool& flag)
{
	if( this-> flag != flag) {
		this-> r_ptr[index / bv_size] ^= (1ULL << (bv_size - (index % bv_size)));
	}
	return *this;
}
/*
// Insert - Inserts a new element at the specified position
void MyVector<bool>::insert(size_t index, const bool& elem) 
{
    if (index > v_size) 
    {
        throw std::out_of_range("Index out of range");
    }

    if (v_size == v_cap) 
    {
		//changing the ral size of vector to have one more size_t

        v_cap = (v_cap + bv_size - 1) / bv_size * bv_size;  
        size_t* tmp = new size_t[(v_cap + bv_size - 1) / bv_size + 1];
        for (size_t i = 0; i < v_size / bv_size; ++i)
        {
            tmp[i] = ptr[i];
        }
        if (ptr)
        {
            delete [] ptr;
        }

        ptr = tmp;
        tmp = nullptr;
        v_cap += bv_size;
        t_cap= v_cap;
    }
}
*/
//Parameterized constructor
MyVector<bool>::MyVector(bool value, int quantity)
{
	v_size = quantity;
	size_t new_cap_with_bytes = quantity % bv_size ? quantity / bv_size + 1 : quantity / bv_size ;
	ptr = new size_t[new_cap_with_bytes];
	if(value) {
		size_t x = 1;
		for(int i = 0; i < v_size; ++i) {
			ptr[i / bv_size] |= x << (bv_size - (i % bv_size));
		}
	}
	v_cap = new_cap_with_bytes * bv_size;
	t_cap= v_cap;
}

// Copy constructor
MyVector<bool>::MyVector(const MyVector<bool>& obj): v_size(obj.v_size), v_cap(obj.v_cap), t_cap(obj.t_cap)
{

        int quantity = v_size % bv_size ? v_size / bv_size + 1 : v_size / bv_size;
        ptr = new size_t[quantity];
	        for (size_t i = 0; i < quantity; ++i) 
			{
				 ptr[i] = obj.ptr[i];
			}
}

// Move constructor
MyVector<bool>::MyVector(MyVector<bool>&& obj) 
{
		ptr = obj.ptr;
        v_size = obj.v_size;
        v_cap = obj.v_cap;
        t_cap = obj.t_cap;

		obj.ptr = nullptr;
        obj.v_size = 0;
        obj.v_cap = 0;
        obj.t_cap = 0;

}

MyVector<bool>::MyVector(std::initializer_list<bool> list)
{
	if(list.size())
	{
		v_size = list.size();
		t_cap = v_size;
		v_cap = (v_size % bv_size ? v_size / bv_size + 1 : v_size / bv_size) * bv_size;;
		
	}
	size_t quantity = v_size % bv_size ? v_size / bv_size + 1 : v_size / bv_size; 
	ptr = new size_t[quantity];

	int index = 0;
	for(bool value : list) {
		if(value) {
			ptr[index / bv_size] |= 1ULL << (bv_size - (index % bv_size));
		}
		++index;
	}
}

MyVector<bool>& MyVector<bool>::operator=(const MyVector<bool>& obj)
{

    if (this != &obj)
    {
		if(ptr) {
			delete[] ptr;
		}
		v_size = obj.v_size;
        v_cap = obj.v_cap;
        t_cap = obj.t_cap;

        ptr = new size_t[(v_cap + 63) / 64];
        for (size_t i = 0; i < (v_cap + 63) / 64; ++i)
        {
            ptr[i] = obj.ptr[i];
        }
    }
    return *this;
}

MyVector<bool>& MyVector<bool>::operator=(MyVector<bool>&& obj)
{
		if(this != &obj) 
		{
			if(ptr){
				delete[] ptr;
			
			}
			v_size = obj.v_size;
			v_cap = obj.v_cap;
			t_cap = obj.t_cap;
			ptr =  obj.ptr;

			obj.ptr = nullptr;
			obj.v_size  = 0;
			obj.v_cap = 0;
			obj.t_cap = 0;

		}
	return *this;
}

