#include <iostream>
#include <stack>


class node {
public:

	node( int data ) :data_( data ) {}

	void add( int data ) {

		if ( data > data_ ) {
			if ( right_child_ == nullptr ) {
				right_child_ = new node( data );
				right_child_->parent = ( this );
			}
			else
				right_child_->add( data );
		}
		else if ( data < data_ ) {
			if ( left_child_ == nullptr ) {
				left_child_ = new node( data );
				left_child_->parent = this;
			}
			else
				left_child_->add( data );
		}
	}

	int get_data() {
		return data_;
	}

	bool has_left() {
		return left_child_ != nullptr;
	}

	bool has_right() {
		return right_child_ != nullptr;
	}

	~node() {
		delete left_child_;
		delete right_child_;
	}

private:
	int data_;

	node* parent = nullptr;
	node* left_child_ = nullptr;
	node* right_child_ = nullptr;

	node* most_left_node( std::stack<node*>& parents ) {
		if ( this->has_left() ) {
			parents.push( this );
			return this->left_child_->most_left_node( parents );
		}
		return this;
	}

	friend std::ostream& operator<<( std::ostream& os, node& n );
	friend class binary_search_tree;
	friend class bst_iterator;
};

std::ostream& operator<<( std::ostream& os, node& n ) {
	os << n.data_;
	return os;
}

class bst_iterator {
	using iterator_category = std::forward_iterator_tag;
	using reference = node&;
	using pointer = node*;
	using value_type = node;
	using difference_type = ptrdiff_t;
public:
	bst_iterator() = default;
	bst_iterator( pointer it ) :it_( it ) {}

	void set_parent( std::stack<pointer>& p ) {
		parents_ = &p;
	}

	bst_iterator& operator++() {
		if ( it_->has_right() ) {
			it_ = it_->right_child_->most_left_node( *parents_ );
		}
		else if ( !parents_->empty() ) {
			it_ = parents_->top();
			parents_->pop();
		}
		else
			it_ = nullptr;

		return *this;
	}

	bst_iterator operator++( int ) {
		auto temp = *this;
		++*this;
		return temp;
	}

	pointer operator->() {
		return it_;
	}

	reference operator*() {
		return *it_;
	}

	bool operator==( const bst_iterator& it ) {
		return it_ == it.it_;
	}

	bool operator!=( const bst_iterator& it ) {
		return !( *this == it );
	}

private:

	std::stack<node*>* parents_ = nullptr;
	pointer it_ = nullptr;
};

class binary_search_tree {
public:
	using iterator = bst_iterator;

	binary_search_tree( int data ) :root_( new node( data ) ) {};

	void add( int data ) {
		root_->add( data );
	}

	bst_iterator begin() {
		bst_iterator it = root_->most_left_node( parents_ );
		it.set_parent( parents_ );
		return it;
	}

	bst_iterator end() {
		return {};
	}

	~binary_search_tree() {
		delete root_;
	}

private:
	std::stack<node*> parents_;
	node* root_;
};


#define input 0

int main() {
	
#if !input
	binary_search_tree tree( 5 );

	tree.add( 3 );
	tree.add( 1 );
	tree.add( 2 );
	tree.add( 4 );
	tree.add( 7 );
	tree.add( 6 );
	tree.add( 8 );
	tree.add( 9 );
#else
	int num;
	int i = 0;
	std::cout << i << " - ";
	++i;
	std::cin >> num;

	binary_search_tree tree( num );

	std::cout << i << " - ";
	++i;
	while ( std::cin >> num ) {
		tree.add( num );
		std::cout << i << " - ";
		++i;
	}
	std::cout << std::endl << std::endl;
#endif

	for (auto& x : tree) {
		std::cout << x << std::endl;
	}
	

}
