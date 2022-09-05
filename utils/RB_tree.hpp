/*====================================
============ ft:: RB_TREE ============
======================================

A red black tree is a self balanced binary search tree
The additional bit is the color (either red or black)
Therefore no path is twice as long as any other path

Rules for a Red Black Tree:
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NULL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to
   descendant leaves contain the same number of black nodes.

RB-Tree insertion:
Case 1. if tree is empty create new node as root node with color black
Case 2. if tree is not empty create new node as leaf node with color red
Case 3. if parent of newnode is black then exit
Case 4. if parent of newnode is red then check the color of parents sibling of newnode
		I. if color is black or null then do suitable rotation & recolor
		II. if color is red then recolor & also check 
			if parents parent of newnode is not root node, then recolor it & recheck

RB-Tree deletion:
	Case 1. if node to delete is red -> delete it
	Case 2. if root is double black -> remove double black & make it single black
	Case 3. if double black's sibling is black & both children are black 
			-> remove double black
			-> make parent black
				i. if parent is red it becomes black
				ii. if parent is black it becomes double black
			-> make sibling red
		-> if double black still exists apply other cases!
	Case 4. if double black's sibling is red
			-> swap colors of parent & it's sibling
			-> rotate parent in double black direction
			-> reapply cases
	Case 5. double black's sibling is black, 
			siblings child who is far from double black is black
			but near child to double black is red
			-> swap color of double black's sibling & siblings child who is near to double black
			-> rotate sibling in opposite direction to double black
			-> apply case 6.
	Case 6. double black's sibling is black, far children is red
			-> swap color of parent & sibling
			-> rotate parent in double black direction
			-> remove double black
			-> change color of red child to black
	
*/

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <limits>

#include "algorithm.hpp"
#include "utility.hpp"
#include "tree_iterator.hpp"

namespace ft {

enum color { black = false, red = true };

template <class T>
struct node {
    typedef T                       value_type;
    typedef value_type             *pointer;
    typedef node<value_type>       *node_pointer;
    typedef const node<value_type> *const_node_pointer;

    node(pointer _key, node *_parent = NULL, node *_left = NULL, node *_right = NULL, color _col = black, bool _is_leaf = false)
        : key(_key), parent(_parent), left(_left), right(_right), color(_col), is_leaf(_is_leaf) {}

    pointer      key;
    node_pointer parent;
    node_pointer left;
    node_pointer right;
    color        color;
    bool         is_leaf;
};

template <class Pair, class Key, class T, class Compare, class Alloc>
class red_black_tree {
   public:
    typedef Key                                                     key_type;
    typedef T                                                       mapped_type;
    typedef Pair                                                    value_type;
    typedef Compare                                                 key_compare;
    typedef Alloc                                                   allocator_type;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef ft::node<value_type>                                    node;
    typedef typename allocator_type::template rebind<node>::other   allocator_type_node;
    typedef typename ft::node<value_type>::node_pointer             node_pointer;
    typedef typename ft::node<value_type>::const_node_pointer       const_node_pointer;
    typedef typename allocator_type_node::reference                 node_reference;
    typedef ft::tree_iterator<node_pointer, value_type>             iterator;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
    typedef typename allocator_type::difference_type                difference_type;
    typedef typename allocator_type::size_type                      size_type;

    red_black_tree(const key_compare &comp, const allocator_type &alloc_value) : _root(NULL), _alloc_value(alloc_value), _alloc_node(alloc_value), _comp(comp), _size(0) {
        _create_null();
        _create_head();
        _root = _null;
        _most_left = _head;
        _root->parent = _head;
        _head->left = _root;
    }

    red_black_tree(const red_black_tree &other) : _root(NULL), _alloc_value(other._alloc_value), _alloc_node(other._alloc_node), _comp(other._comp), _size(0) {
        _create_null();
        _create_head();
        _root = _clone(other._root, _head);
        if (_root != _null) {
            _most_left = tree_min(_root);
        } else {
            _most_left = _head;
        }
        _head->left = _root;
    }

    ~red_black_tree() {
        clear();
        _erase_node(_null);
        _erase_node(_head);
    }

    red_black_tree &operator=(const red_black_tree &other) {
        if (this != &other) {
            if (size() > 0 && _root != _null)
                clear();
            _root = _clone(other._root, _head);
            if (_root != _null) {
                _most_left = tree_min(_root);
            } else {
                _most_left = _head;
            }
            _head->left = _root;
            _size = other._size;
        }
        return (*this);
    }

    iterator begin() { return _most_left; }

    const_iterator begin() const { return _most_left; }

    iterator end() { return _head; }

    const_iterator end() const { return _head; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool empty() const { return _size == 0 ? true : false; }

    size_type size() const { return (_size); }

    size_type max_size() const {
        size_type alloc_max = this->_alloc_node.max_size();
        size_type numeric_max = std::numeric_limits<difference_type>::max();
        return alloc_max < numeric_max ? alloc_max : numeric_max;
    }

    mapped_type &operator[](const key_type &k) {
        return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
    }

    mapped_type &at(const key_type &k) {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _null || (needle == _root && _is_unequal(k, *_root->key)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    const mapped_type &at(const key_type &k) const {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _null || (needle == _root && _is_unequal(k, *_root->key)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    node_pointer search(node_pointer search_node, const value_type &key) const {
        if (search_node == _null || _is_equal(*search_node->key, key))
            return (search_node);
        if (_is_less(key, *search_node->key))
            return (search(search_node->left, key));
        else
            return (search(search_node->right, key));
    }

    template <class T1>
    node_pointer iterative_search(node_pointer search_node, const T1 &key) const {
        while (search_node != _null && _is_unequal(key, *search_node->key)) {
            if (_is_less(key, *search_node->key))
                search_node = search_node->left;
            else
                search_node = search_node->right;
        }
        if (search_node == _null)
            return (_root);
        return (search_node);
    }

    node_pointer successor(node_pointer suc_node) {
        if (suc_node->right != _null)
            return (min(suc_node->right));
        node_pointer *parent_node = suc_node->parent;
        while (parent_node != NULL && suc_node == parent_node->right) {
            suc_node = parent_node;
            parent_node = parent_node->parent;
        }
    }

    void left_rotate(node_pointer rotate_node) {
        node_pointer new_node = rotate_node->right;
        rotate_node->right = new_node->left;
        if (new_node->left != _null)
            new_node->left->parent = rotate_node;
        new_node->parent = rotate_node->parent;
        if (rotate_node->parent == _head) {
            _root = new_node;
            _head->left = _root;
        } else if (rotate_node == rotate_node->parent->left)
            rotate_node->parent->left = new_node;
        else
            rotate_node->parent->right = new_node;
        new_node->left = rotate_node;
        rotate_node->parent = new_node;
    }

    void right_rotate(node_pointer rotate_node) {
        node_pointer new_node = rotate_node->left;
        rotate_node->left = new_node->right;
        if (new_node->right != _null)
            new_node->right->parent = rotate_node;
        new_node->parent = rotate_node->parent;
        if (rotate_node->parent == _head) {
            _root = new_node;
            _head->left = _root;
        } else if (rotate_node == rotate_node->parent->right)
            rotate_node->parent->right = new_node;
        else
            rotate_node->parent->left = new_node;
        new_node->right = rotate_node;
        rotate_node->parent = new_node;
    }

    ft::pair<iterator, bool> insert(const value_type &val) {
        if (_root != _null && _is_equal(*_root->key, val))
            return (ft::make_pair<iterator, bool>(iterator(_root), false));
        node_pointer needle = iterative_search(_root, val);
        if (needle != _root && needle != _null)
            return (ft::make_pair<iterator, bool>(iterator(needle), false));

        node_pointer created_node = _create_node(val);
        node_pointer head_node = _head;
        node_pointer root_node = _root;
        while (root_node != _null) {
            head_node = root_node;
            if (_is_less(*created_node->key, *root_node->key))
                root_node = root_node->left;
            else
                root_node = root_node->right;
        }
        created_node->parent = head_node;
        if (head_node == _head) {
            _root = created_node;
            _root->parent = _head;
            _head->left = _root;
            _most_left = created_node;
        } else if (_is_less(*created_node->key, *head_node->key)) {
            head_node->left = created_node;
            if (_most_left == head_node)
                _most_left = created_node;
        } else
            head_node->right = created_node;
        created_node->left = _null;
        created_node->right = _null;
        created_node->color = red;
        _insert_fix(created_node);
        return (ft::make_pair<iterator, bool>(iterator(created_node), true));
    }

    iterator insert(const_iterator position, const value_type &val) {
        (void)position;
        return (insert(val)).first;
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    template <class T1, class T2>
    void transplant(T1 u, T2 v) {
        if (u->parent == _head) {
            _root = v;
            _head->left = _root;
        } else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void erase(node_pointer to_erase_node) {
        node_pointer origin_node = to_erase_node;
        node_pointer tmp_node;
        color        origin_node_color = origin_node->color;
        if (to_erase_node->left == _null) {
            tmp_node = to_erase_node->right;
            transplant(to_erase_node, to_erase_node->right);
        } else if (to_erase_node->right == _null) {
            tmp_node = to_erase_node->left;
            transplant(to_erase_node, to_erase_node->left);
        } else {
            origin_node = tree_min(to_erase_node->right);
            origin_node_color = origin_node->color;
            tmp_node = origin_node->right;
            if (origin_node->parent == to_erase_node)
                tmp_node->parent = origin_node;
            else {
                transplant(origin_node, origin_node->right);
                origin_node->right = to_erase_node->right;
                origin_node->right->parent = origin_node;
            }
            transplant(to_erase_node, origin_node);
            origin_node->left = to_erase_node->left;
            origin_node->left->parent = origin_node;
            origin_node->color = to_erase_node->color;
        }
        if (to_erase_node == _most_left) {
            if (to_erase_node->right == _null)
                _most_left = _most_left->parent;
            else
                _most_left = tree_min(_most_left->right);
        }
        if (origin_node_color == black)
            _erase_fix(tmp_node);
        _erase_node(to_erase_node);
    }

    void clear() {
        _clear(_root);
        _root = _null;
        _root->parent = _head;
        _most_left = _head;
    };

    void swap(red_black_tree &other) {
        if (this != &other) {
            node_pointer        tmp_root = other._root;
            node_pointer        tmp_null = other._null;
            node_pointer        tmp_head = other._head;
            node_pointer        tmp_most_left = other._most_left;
            allocator_type      tmp_alloc_value = other._alloc_value;
            allocator_type_node tmp_alloc_node = other._alloc_node;
            size_type           tmp_size = other._size;

            other._root = _root;
            other._null = _null;
            other._head = _head;
            other._most_left = _most_left;
            other._alloc_value = _alloc_value;
            other._alloc_node = _alloc_node;
            other._size = _size;
            _root = tmp_root;
            _null = tmp_null;
            _head = tmp_head;
            _most_left = tmp_most_left;
            _alloc_value = tmp_alloc_value;
            _alloc_node = tmp_alloc_node;
            _size = tmp_size;
        }
    }

    iterator find(const key_type &key) {
        node_pointer n = iterative_search(_root, key);
        if (n == _root && _root != _null && _is_equal(*_root->key, key))
            return iterator(_root);
        else if (n == _root) {
            return end();
        } else
            return iterator(n);
    }

    const_iterator find(const key_type &key) const {
        node_pointer n = iterative_search(_root, key);
        if (n == _root && _root != _null && _is_equal(*_root->key, key))
            return const_iterator(_root);
        else if (n == _root)
            return const_iterator(end());
        else
            return const_iterator(n);
    }

    iterator lower_bound(const key_type &key) {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (n != _null) {
            if (!_is_less(*n->key, key)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator lower_bound(const key_type &key) const {
        const_node_pointer result = end().base();
        node_pointer       n = _root;
        while (n != _null) {
            if (!_is_less(*n->key, key)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return const_iterator(result);
    }

    iterator upper_bound(const key_type &key) {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (n != _null) {
            if (_is_less(key, *n->key)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator upper_bound(const key_type &key) const {
        const_node_pointer result = end().base();
        node_pointer       n = _root;
        while (n != _null) {
            if (_is_less(key, *n->key)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return const_iterator(result);
    }

    ft::pair<iterator, iterator> equal_range(const key_type &key) {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    allocator_type get_allocator() const { return _alloc_value; }

   private:
    node_pointer        _root;
    node_pointer        _null;
    node_pointer        _most_left;
    node_pointer        _head;
    allocator_type      _alloc_value;
    allocator_type_node _alloc_node;
    key_compare         _comp;
    size_type           _size;

    node_pointer _create_node(const value_type &value) {
        pointer cpy = _alloc_value.allocate(1);
        _alloc_value.construct(cpy, value_type(value));
        node_pointer n = _alloc_node.allocate(1);
        _alloc_node.construct(n, node(cpy, NULL, NULL, NULL));
        _size++;

        return n;
    }

    node_pointer _copy_node(const value_type &value, color &rb) {
        pointer cpy = _alloc_value.allocate(1);
        _alloc_value.construct(cpy, value_type(value));
        node_pointer n = _alloc_node.allocate(1);
        _alloc_node.construct(n, node(cpy, NULL, NULL, NULL, rb));
        _size++;

        return n;
    }

   void _create_null() {
        pointer null_val = _alloc_value.allocate(1);
        _alloc_value.construct(null_val, value_type());
        _null = _alloc_node.allocate(1);
        _alloc_node.construct(_null, node(null_val, NULL, NULL, NULL, black, true));
    }

    void _create_head() {
        _head = _alloc_node.allocate(1);
        _alloc_node.construct(_head, node(NULL, _root, _null, _null, black, false));
    }

    void _erase_node(node_pointer node_to_erase) {
        if (node_to_erase) {
            if (node_to_erase->key) {
                _alloc_value.destroy(node_to_erase->key);
                _alloc_value.deallocate(node_to_erase->key, 1);
            }
            _alloc_node.destroy(node_to_erase);
            _alloc_node.deallocate(node_to_erase, 1);
            _size--;
        }
    }

    void _clear(node_pointer node_to_clear) {
        if (node_to_clear != _null) {
            _clear(node_to_clear->left);
            _clear(node_to_clear->right);
            _erase_node(node_to_clear);
        }
    }

    node_pointer _clone(const node_pointer node_to_clone, const node_pointer parent) {
        node_pointer cpy = _null;
        if (!node_to_clone->is_leaf) {
            cpy = _copy_node(*(node_to_clone->key), node_to_clone->color);
            cpy->parent = parent;
            cpy->left = _clone(node_to_clone->left, cpy);
            cpy->right = _clone(node_to_clone->right, cpy);
        }
        return (cpy);
    }

    template <class T1, class T2>
    bool _is_equal(const T1 &x, const T2 &y) const {
        return (!_comp(x, y) && !_comp(y, x));
    }

    template <class T1, class T2>
    bool _is_unequal(const T1 &x, const T2 &y) const {
        return !(_is_equal(x, y));
    }

    template <class T1, class T2>
    bool _is_less(const T1 &x, const T2 &y) const {
        return (_comp(x, y));
    }

    void _erase_fix(node_pointer to_erase_node) {
        while (to_erase_node != _root && to_erase_node->color == black) {
            if (to_erase_node == to_erase_node->parent->left) {
                node_pointer new_node = to_erase_node->parent->right;
                if (new_node->color == red) {
                    new_node->color = black;
                    to_erase_node->parent->color = red;
                    left_rotate(to_erase_node->parent);
                    new_node = to_erase_node->parent->right;
                }
                if (new_node->left->color == black && new_node->right->color == black) {
                    new_node->color = red;
                    to_erase_node = to_erase_node->parent;
                } else {
                    if (new_node->right->color == black) {
                        new_node->left->color = black;
                        new_node->color = red;
                        right_rotate(new_node);
                        new_node = to_erase_node->parent->right;
                    }
                    new_node->color = to_erase_node->parent->color;
                    to_erase_node->parent->color = black;
                    new_node->right->color = black;
                    left_rotate(to_erase_node->parent);
                    to_erase_node = _root;
                }
            } else {
                node_pointer new_node = to_erase_node->parent->left;
                if (new_node->color == red) {
                    new_node->color = black;
                    to_erase_node->parent->color = red;
                    right_rotate(to_erase_node->parent);
                    new_node = to_erase_node->parent->left;
                }
                if (new_node->right->color == black && new_node->left->color == black) {
                    new_node->color = red;
                    to_erase_node = to_erase_node->parent;
                } else {
                    if (new_node->left->color == black) {
                        new_node->right->color = black;
                        new_node->color = red;
                        left_rotate(new_node);
                        new_node = to_erase_node->parent->left;
                    }
                    new_node->color = to_erase_node->parent->color;
                    to_erase_node->parent->color = black;
                    new_node->left->color = black;
                    right_rotate(to_erase_node->parent);
                    to_erase_node = _root;
                }
            }
        }
        to_erase_node->color = black;
    }

    void _insert_fix(node_pointer input_node) {
        while (input_node->parent->color == red) {
            if (input_node->parent == input_node->parent->parent->left) {
                node_pointer new_node = input_node->parent->parent->right;
                if (new_node ->color == red) {
                    input_node->parent->color = black;
                    new_node ->color = black;
                    input_node->parent->parent->color = red;
                    input_node = input_node->parent->parent;
                } else {
                    if (input_node == input_node->parent->right) {
                        input_node = input_node->parent;
                        left_rotate(input_node);
                    }
                    input_node->parent->color = black;
                    input_node->parent->parent->color = red;
                    right_rotate(input_node->parent->parent);
                }
            } else {
                node_pointer new_node  = input_node->parent->parent->left;
                if (new_node ->color == red) {
                    input_node->parent->color = black;
                    new_node ->color = black;
                    input_node->parent->parent->color = red;
                    input_node = input_node->parent->parent;
                } else {
                    if (input_node == input_node->parent->left) {
                        input_node = input_node->parent;
                        right_rotate(input_node);
                    }
                    input_node->parent->color = black;
                    input_node->parent->parent->color = red;
                    left_rotate(input_node->parent->parent);
                }
            }
        }
        _root->color = black;
    }
};

template <class T>
node<T> *tree_min(node<T> *x) {
    while (!x->left->is_leaf)
        x = x->left;
    return (x);
}

template <class T>
node<T> *tree_max(node<T> *x) {
    while (!x->right->is_leaf)
        x = x->right;
    return (x);
}

}

#endif