#include <iostream>
#include "Vector_header.hpp"

int main()
{
	MyVector<int> vec;
	
	//checking max_size
	std::cout << "Max_size of the vector is: ";
	std::cout << vec.max_size() << std::endl;

	//checking size of vector
	std::cout << "Current size of the vector is: ";
	std::cout << vec.size() << std::endl;

	vec.push_back(5);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(1);
	std::cout << "After pushing some elemnts into the vector Vec is: ";
	std::cout << vec << std::endl;

	std::cout << "After changing the first element ";
	vec.at(0) = 7;
	std::cout << "Vec is " << vec << std::endl;

	MyVector<int> vec2;
	vec2.push_back(1);
	vec2.push_back(2);
	vec2.push_back(2);
	vec2.push_back(2);
	vec2.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);
	std::cout << "Vec2 is " << vec2 << std::endl;

	//using copy assignment 
	vec = vec2;
	MyVector<int> v;
	vec2.assign(6, 100);
	std::cout <<"Vec2 is: " << vec2 << std::endl;
	std::cout << "The capacity of Vec2 is: " << vec2.capacity() << std::endl;

	std::cout << "Vec is " << vec << std::endl;
	std::cout << "Vec2 is " << vec2 << std::endl;
	//swap
	vec.swap(vec2);
	std::cout << "After swaping two containers:";
	std::cout << "Vec is " << vec << std::endl;
	std::cout << "Vec2 is " << vec2 << std::endl;

	std::cout << vec << std::endl;
	MyVector<int> vec3{1,2,3, 9, 8};
	std::cout << vec3 << std::endl;
	MyVector<int> vec5(vec3);
	std::cout << "Vec5 is "  << vec5 << std::endl;
	std::cout << "Creating Vec6  with move constructor: ";
	MyVector<int> vec6(std::move(vec5));
	std::cout << vec6 << std::endl;
	std::cout << vec5 << std::endl;
	
	//Getting the first element by Data 
	std::cout << "Getting the first element of the Vec with Data: ";
	int* p = vec.data();
	std::cout << *p << std::endl;

	std::cout << std::endl;
	std::cout << "Working with Bool Vector" << std::endl;

	std::cout << "Pushing some element into the vector: ";
		MyVector<bool> boolv;
		for(int i = 0; i < 13 ; ++i) {
			boolv.push_back(1);
		}	
		//push
		boolv.push_back(0);
		boolv.push_back(1);
		boolv.push_back(0);
		boolv.push_back(1);
		boolv.push_back(1);
		boolv.push_back(1);
		boolv.push_back(1);
		boolv.push_back(1);
		boolv.push_back(0);
		//print
		boolv.print();
	
		//popping elements
		std::cout << "Popping 7 elements from the vector: ";
		boolv.pop_back();
		boolv.pop_back();
		boolv.pop_back();
		boolv.pop_back();
		boolv.pop_back();
		boolv.pop_back();
		boolv.pop_back();
		boolv.print();


		std::cout <<"Size of the vector is: " <<  boolv.size() << std::endl;
		std::cout << "Capacity of th evector is: " << boolv.capacity() << std::endl;
		
		//resize
		boolv.resize(35); 
		std::cout << "After resizing the vcetor, it's size is: " << boolv.size() << std::endl;
		std::cout << "Capacity is: " << boolv.capacity() << std::endl;
		boolv.print();

		//reserve
		boolv.reserve(125);
		std::cout << "After reserving capacity is: " <<  boolv.capacity() << std::endl;
		boolv.print();
		
		//printing some  elements 
		std::cout << "Vect[0] is: " << boolv[0] << std::endl;
		std::cout << "Vect[1] is: " << boolv[1] << std::endl;
		std::cout << "Vect[14] is: " << boolv[14] << std::endl;
		std::cout << "Vect[19] is: " << boolv[19] << std::endl;
		std::cout << "Vect[25] is: " << boolv[25] << std::endl;
		std::cout <<"Current size is: " <<  boolv.size() << std::endl;
		boolv.resize(30);
		std::cout << "After resizing Vec is: " ;
		boolv.print();

		//assigning  elemets by assignmemt operator
		std::cout << "Assigning the first element of the vector: ";
		boolv[0] = 1;
		boolv.print();
		//Use of initilaizer_list constructor
		std::cout << "Creating new Vecc with initializer list: "; 
		MyVector<bool> vecc{1,1,0};
		//Copy counstructor
		MyVector<bool> vecc2(vecc);
		//Parameterizedconstructor
		MyVector<bool> vecc3(1, 10);
		//copy assignment
		vecc3 = vecc;
		vecc3.print();
		std::cout << "Using assignment operator: ";
		vecc2.print();
		

}
