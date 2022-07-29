/*==================================
============ ft:: STACK ============
====================================

=> MEMBER TYPES
	container_type
	value_type
	size_type
	reference
	const_reference
=> MEMBER FUNCTIONS
	(constructor)
	(deconstructor)
	operator=
	-> ELEMENT ACCESS
		top
	-> CAPACITY
		empty
		size
	-> MODIFIERS
		push
		pop
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=
*/

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

// #include <stack>
#include "iterator.hpp"
#include "vector"

namespace ft{

	template <class T, class Container = std::vector<T> >										//stack line 20
	class stack{																		//stack line 21
	public:
			typedef Container                                container_type;			//stack line 23
    		typedef typename container_type::value_type      value_type;				//stack line 24
    		typedef typename container_type::reference       reference;					//stack line 25
    		typedef typename container_type::const_reference const_reference;			//stack line 26
    		typedef typename container_type::size_type       size_type;					//stack line 27

	protected:
    		container_type c;
	
	public:
			// stack() {}																	//stack line 34
			virtual ~stack() {}															//stack line 35
			explicit stack(const Container& cont = Container()) : c(cont) {}			//stack line 155
			stack(const stack& q) : c(q.c) {}											//stack line 133
			stack& operator=(const stack& q) {c = q.c; return *this;}					//stack line 136


			bool empty() const {return c.empty();}										//stack line 191
			size_type size() const {return c.size();}									//stack line 193
			reference top() {return c.back();}											//stack line 195
			const_reference top() const {return c.back();}								//stack line 197
			void push(const value_type v) {c.push_back(v);}								//stack line 200
			void pop() {c.pop_back();}													//stack line 217

			template <class T1, class C1>												//stack line 227
			friend bool operator==(const stack<T1, C1>& x, const stack<T1, C1>& y);		//stack line 223

			template <class T1, class C1>												//stack line 232
			friend bool operator< (const stack<T1, C1>& x, const stack<T1, C1>& y);		//stack line 235
	};

	template <class Tp, class Container>												//stack line 254
	bool operator==(const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 257
	    return x.c == y.c;																//stack line 259
	}

	template <class Tp, class Container>												//stack line 262
	bool operator< (const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 265
	    return x.c < y.c;																//stack line 267
	}

	template <class Tp, class Container>												//stack line 270
	bool operator!=(const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 273
	    return !(x == y);																//stack line 275
	}

	template <class Tp, class Container>												//stack line 278
	bool operator> (const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 281
	    return x > y;																	//stack line 283
	}

	template <class Tp, class Container>												//stack line 287
	bool operator>=(const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 289
	    return !(x < y);																//stack line 291
	}

	template <class Tp, class Container>												//stack line 294
	bool operator<=(const stack<Tp, Container>& x, const stack<Tp, Container>& y){		//stack line 297
	    return !(x > y);																//stack line 299
	}

}

#endif
