/*=================================
=========== ft:: VECTOR ===========
===================================

=> MEMBER TYPES
	value_type
	allocator_type
	size_type
	difference_type
	reference
	const_reference
	pointer
	const_pointer
	iterator
	const_iterator
	reverse_iterator
	const_reverse_iterator
=> MEMBER FUNCTIONS
	(constructor)
	(deconstructor)
	operator=
	assign
	get_allocator
	-> ELEMENT ACCESS
		at
		operator[]
		front
		back
		data
	-> ITERATORS
		begin
		end
		rbegin
		rend
	-> CAPACITY
		empty
		size
		max_size
		reverse
		capacity
	-> MODIFIERS
		clear
		insert
		erase
		push_back
		pop_back
		resize
		swap
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=

*/

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft{

	template <class T, class Alloc = std::allocator<T> >														//vector line 20
	class vector{																								//vector line 21
	public:
		typedef T                                        		value_type;					
    	typedef Alloc		                               		allocator_type;									//vector line 25
    	typedef typename allocator_type::reference       		reference;										//vector line 26
    	typedef typename allocator_type::const_reference 		const_reference;								//vector line 27
    	typedef typename allocator_type::size_type       		size_type;										//vector line 30
    	typedef typename allocator_type::difference_type 		difference_type;								//vector line 31
    	typedef typename allocator_type::pointer         		pointer;										//vector line 32
    	typedef typename allocator_type::const_pointer   		const_pointer;									//vector line 33
    	typedef pointer 										iterator;										//vector line 334
    	typedef const_pointer 									const_iterator;									//vector line 335
    	typedef typename ft::reverse_iterator<iterator>         reverse_iterator;								//vector line 34
    	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;							//vector line 35

	private:
		allocator_type	_alloc;																					//vector line 61/185
		pointer			_vector;																					//vector line 342
		size_type		_size;																				//vector line 343
		size_type		_cap;																				//vector line 344

		void reallocate(size_type size){
			pointer tmp = _alloc.allocate(size);
			size_type i = 0;
			for (; i < size; ++i)
				_alloc.construct(&tmp[i], _vector[i])
			~vector();
			_size = i;
			_cap = size;
			_vector = tmp;
		}

		size_type get_new_cap() const{
		size_type new_cap;
		size_type cap = capacity();
		if (empty())
			new_cap = 1;
		else if (cap < 128)
			new_cap = cap * 2;
		else
			new_cap = cap + cap / 2;
		return new_cap;
		}
	}

	public:
	// ================= CPP-Reference ====================
	// Member functions
	// Constructor
		// vector() : _vector(0), _size(0), _cap(0) {
		// 	_vector = _alloc.allocate(_cap);
		// }

		explicit vector( const Allocator& alloc ) : _alloc(alloc), _size(0), _cap(0) {
			_vector = _alloc.allocate(_cap);
		}

		explicit vector( size_type count, const T& value = T(), const Allocator& alloc 
						= Allocator()) : _alloc(alloc), _size(count), _cap(count){
			_vector = _alloc.allocate(_cap);

			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(&_vector[i], value);
			
		}
		template< class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type = 0){
			_cap = ft::distance(first, last);
			_size = _cap;
			_vector = _alloc.allocate(_cap);

			for (size_type pos = 0; first != last; pos++, first++)
				_alloc.construct(&_vector[pos], *first]);
		}

		vector( const vector& other ) : _alloc(other._alloc), _size(other._size), _cap(other._cap){
			_vector = _alloc.allocate(_cap);

			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(&_vector[i], other._vector[i]);
		}
	
	// Deconstructor
		~vector(){
			clear();
			_alloc.deallocate(_vector, _cap);
		}

	// Operator=
		vector& operator=( const vector& other ){
			if (*this == other)
				return *this;
			this->clear();
			assign(other.begin(), other.end());
			return *this;
		}

	// Assign
		void assign( size_type count, const T& value ){
			resize(count);
			for (size_type i = 0; i < _size; i++){
				_alloc.destroy(&_vector[i]);
				_alloc.construct(&_vector[i], value);
			}
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last, 
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type = 0 ){
			typename ft::iterator_traits<InputIt>::difference_type diff = ft::distance(first, last);

			resize(diff);
			for (size_type i = 0; i < _size; i++, first++){
				_alloc.destroy(&_vector[i]);
				_alloc.construct(&_vector[i], *first);
			}
		}

	// Get_allocator
		allocator_type get_allocator() const{ return _alloc; }

	// Element access
	// at
		reference at( size_type pos ){
			
			if (pos < 0 || pos >= _size)
				throw std::out_of_range("Vector index is out of range!\n");
			return _vector[pos];
		}

		const_reference at( size_type pos ) const{
			if (pos < 0 || pos >= _size)
				throw std::out_of_range("Vector index is out of range!\n");
			return _vector[pos];
		}

	// operator[]
		reference operator[]( size_type pos ){ return _vector[pos]; }

		const_reference operator[]( size_type pos ) const{ return _vector[pos]; }

	// front
		reference front(){ return _vector[0]; }
		const_reference front() const{ return _vector[0]; }

	// back
		reference back(){ return _vector[_size - 1]; }
		const_reference back() const{ return _vector[_size - 1]; }

	// Iterators
	// begin
		iterator begin(){ return iterator(_vector); }
		const_iterator begin() const{ return const_iterator(_vector); }

	// end
		iterator end(){ return iterator(_vector[_size]); }
		const_iterator end() const{ return const_iterator(_vector[_size]);  }

	// rbegin
		reverse_iterator rbegin(){ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const{ return const_reverse_iterator(end()); }

	// rend
		reverse_iterator rend(){ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	// Capacity
	// empty
		bool empty() const{ return _size == 0; }
	
	// size
		size_type size() const{ return _size; }

	// max_size
		size_type max_size() const { return _alloc.max_size(); }

	// reserve
		void reserve( size_type new_cap ){
			if (new_cap > _cap)
				reallocate(new_cap);
		}

	// capacity
		size_type capacity() const { return _cap; }

	// Modifiers
	// clear
		void clear(){
			for (; _size > 0; --_size)
				_alloc.destroy(&_vector[_size - 1]);
		}

	// insert
		iterator insert( iterator pos, const T& value ){
			typename iterator::difference_type diff = ft::distance(begin(), pos);
			resize(++_size);

			value_type tmp1 = value;
			value_type tmp2;

			for (value_type tmp = static_cast<value_type>(diff); tmp < static_cast<typename iterator::difference_type>(_size) ; tmp++){
				tmp2 = _vector[tmp];
				_vector[tmp] = tmp1;
				tmp1 = tmp2;
			}
			return &_vector[diff];
		}

		void insert( iterator pos, size_type count, const T& value ){
			typename iterator::difference_type diff = ft::distance(iterator(_vector), pos);
			resize(_size + count);
			ft::vector<value_type> tmp;
			for (size_type i = diff; i < _size; i++)
				tmp.push_back(_vector[i]);
			cound += diff;
			for (; diff < static_cast<typename iterator::difference_type>(count) ; diff++)
				_vector[diff] = *value;
			for (size_type i = 0; i < tmp.size(); i++, diff++)
				_vector[diff] = tmp[i];
		}

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last,
		 			typename ft::enable_if<!::ft::is_integral<InputIt>::value>::type = 0){
			
			typename iterator::difference_type diff = ft::distance(iterator(_vector), pos);
			typename iterator::difference_type n = ft::distance(first, last);
			resize(_size + n);
			ft::vector<value_type> tmp;
			for (size_type i = diff; i < _size; i++)
				tmp.push_back(_vector[i]);
			for (; first != last; diff++, first++)
				_vector[diff] = *first;
			for (size_type i = 0; i < tmp.size(); i++, diff++)
				_vector[diff] = tmp[i];
		}

	// erase
		iterator erase( iterator pos ){
			iterator pos1 = pos;

			pos1++;
			for (iterator cop = pos; cop != end(); cop++, pos1++)
				if (pos1 != end())
					*cop = *pos1;
			_size--;
			return pos;
		}

		iterator erase( iterator first, iterator last ){
			typename iterator::difference_type diff = ft::distance(first, last);

			for (iterator it1 = first, it2 = last; it2 != end(); it2++, it1++)
				*it1 = *it2;
			_size = _size - diff;
			return first;
		}

	// push_back
		void push_back( const T& value ){
			if (capacity() <= size())
				reallocate(get_new_cap());
			_alloc.construct(_size, value);
			++_size;
		}

	// pop_back
		void pop_back(){
			if (empty())
				return ;
			_alloc.destroy(&back());
			_size--;
		}

	// resize
		void resize( size_type count, T value = T() ){
			if (count == size())
				return ;
			else if (count > size()){
				if (n > capacity())
					reallocate(n);
				while (size() != n)
					_alloc.construct(_size++, value);
				return ;
			}
			else if (count < size()){
				for (size_type i = size(); i > count; i--)
					_alloc.destroy(--_size);
			}
		}

	// swap
		void swap( vector& other ){

			pointer buf = other._vector;
			size_type sizebuf = other._size;
			size_type capbuf = other._cap;
			other._vector = _vector;
			other._size = _size;
			other._cap = _cap;
			_vector = buf;
			_size = sizebuf;
			_cap = capbuf;

			// std::swap(first(), other.first());			
			// std::swap(second(), other.second());
			// std::swap(_size(), other._size());			
			// std::swap(_cap(), other._cap());
			// std::swap(_vector(), other._vector());			
			// std::swap(_alloc(), other._alloc());	
		}

	// Non-member functions
	// operators
		template< class T, class Alloc >
		bool operator==( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());				// vector line 3338
		}

		template< class T, class Alloc >
		bool operator!=( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return !(x == y);																		
		}

		template< class T, class Alloc >
		bool operator<( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		template< class T, class Alloc >
		bool operator<=( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return !(x > y);
		}

		template< class T, class Alloc >
		bool operator>( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return x > y;
		}

		template< class T, class Alloc >
		bool operator>=( const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y ){
			return !(x < y);
		}


	};

}

#endif
