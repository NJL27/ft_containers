/*==============================
=========== ft:: MAP ===========
================================

=> MEMBER TYPES
	key_type
	mapped_type
	value_type
	size_type
	difference_type
	key_compare_type
	allocator_type
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
	get_allocator
	-> ELEMENT ACCESS
		operator[]
	-> ITERATORS
		begin
		end
		rbegin
		rend
	-> CAPACITY
		empty
		size
		max_size
	-> MODIFIERS
		clear
		insert
		erase
		swap
	-> OPERATIONS
		count
		find
		equal_range
		lower_bond
		upper_bond
	-> OBSERVERS
		key_comp
		value_comp
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=

*/

// MEMBER TYPES



// MEMBER FUNCTIONS
// constructor
	explicit map( const Compare& comp, const Allocator& alloc = Allocator() ){

	}
	
	template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ){

	}
	
	map (const map& x){

	}

// deconstructor
	~map(){

	}

// operator=
	map& operator=( const map& other ){

	}

// get_allocator
	allocator_type get_allocator() const{

	}

// ELEMENT ACCESS
// operator[]
	T& operator[]( const Key& key ){

	}

// ITERATORS
// begin
	iterator begin(){

	}

	const_iterator begin() const{

	}

// end
	iterator end(){

	}
	
	const_iterator end() const{

	}

// rbegin
	reverse_iterator rbegin(){

	}

	const_reverse_iterator rbegin() const{

	}

// rend
	reverse_iterator rend(){

	}

	const_reverse_iterator rend() const{

	}

// CAPACITY
// empty
	bool empty() const{

	}

// size
	size_type size() const{

	}

// max_size
	size_type max_size() const{

	}

// MODIFIERS
// clear
	void clear(){

	}

// insert
	std::pair<iterator, bool> insert( const value_type& value ){

	}

	iterator insert( iterator hint, const value_type& value ){

	}

	template< class InputIt >
	void insert( InputIt first, InputIt last ){

	}

// erase
	void erase( iterator pos ){

	}

	void erase( iterator first, iterator last ){

	}

	size_type erase( const Key& key ){

	}

// swap
	void swap( map& other ){

	}

// OPERATIONS
// count
	size_type count( const Key& key ) const{

	}

// find
	iterator find( const Key& key ){

	}

	const_iterator find( const Key& key ) const{

	}

// equal_range
	std::pair<iterator,iterator> equal_range( const Key& key ){

	}

	std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{

	}

// lower_bound
	iterator lower_bound( const Key& key ){

	}

	const_iterator lower_bound( const Key& key ) const{

	}

// upper_bound
	iterator upper_bound( const Key& key ){

	}

	const_iterator upper_bound( const Key& key ) const{

	}

// OBSERVERS
// key_comp
	key_compare key_comp() const{

	}

// value_comp
	std::map::value_compare value_comp() const{

	}

// NON-MEMBER FUNCTIONS
	template<class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());				
	}

	template<class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return !(x == y);																		
	}

	template<class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template<class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return !(x > y);
	}

	template<class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return x > y;
	}

	template<class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& x, const ft::map<Key,T,Compare,Alloc>& y ){
		return !(x < y);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y )