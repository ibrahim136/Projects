#include <iostream>
using namespace std;

struct ArrayNode {
	int data;
	int index;
	ArrayNode* next = nullptr;
	ArrayNode* prev = nullptr;
	ArrayNode(int data,int index) : data(data) ,index(index){}
	ArrayNode() = delete;
};

class ArrayLinkedList {
private:
	ArrayNode* head = nullptr,*tail = nullptr;
	int length = 0;
	int Array_length;
	ArrayNode* embed_after(ArrayNode* before, int data, int index) {
		ArrayNode* after = before->next;
		ArrayNode* middle = new ArrayNode(data, index);
		link(before, middle);
		if (after) {
			link(middle, after);
		}
		else {
			tail = middle;
		}
		return middle;
	}
	ArrayNode* find_and_edit(int index, bool create_if_not_exists) {
		ArrayNode* curr = head;
		while (curr->next && curr->next->index < index) {
			curr = curr->next;
		}
		bool founded = curr->next && curr->next->index == index;
		if (founded) {
			return curr->next;
		}
		else if (create_if_not_exists) {
			return embed_after(curr, 0, index);
		}
		return nullptr;
	}
	void link(ArrayNode* node1, ArrayNode* node2) {
		node1->next = node2;
		node2->prev = node1;
	}
	int get_data(int index) {
		ArrayNode* node = find_and_edit(index, false);
		if (node) {
			return node->data;
		}
		else {
			return 0;
		}
	}
public:
	int row_index;
	ArrayLinkedList* next = nullptr;
	ArrayLinkedList* prev = nullptr;
	ArrayLinkedList() = delete;
	ArrayLinkedList(int Array_length) : Array_length(Array_length){
		head = tail = new ArrayNode(0, -1);
		length++;
	}
	ArrayLinkedList(int Array_length,int row_index) : Array_length(Array_length),row_index(row_index) {
		head = tail = new ArrayNode(0, -1);
		length++;
	}
	~ArrayLinkedList() {
		for (ArrayNode* curr = head; curr;) {
			ArrayNode* temp = curr;
			curr = curr->next;
			delete temp;
		}
		cout << "All nodes have been destructed\n\n";
	}
	void set_value(int data,int index) {
		if (index +1 > Array_length) {
			cout << "index exceeded length of array";
			return;
		}
		find_and_edit(index, true)->data = data;
		length++;
	}
	void print_array() const{
		ArrayNode* curr = head->next;
		for (int i{ 0 }; i < Array_length; i++) {
			if (curr && curr->index == i) {
				cout << curr->data << " ";
				curr = curr->next;
			}
			else {
				cout << "0 ";
			}
		}
	}
	void print_array_reversed() const {
		ArrayNode* curr = tail;
		for (int i{ Array_length -1 }; i > -1; i--) {
			if (curr && curr->index == i) {
				cout << curr->data << " ";
				curr = curr->prev;
			}
			else {
				cout << "0 ";
			}
		}
	}
	void print_array_nonzero() const {
		for (ArrayNode* curr = head->next; curr; curr = curr->next) {
			cout << curr->data << " ";
		}
		cout << " \n\n";
	}
	void add(ArrayLinkedList& other) {
		if (Array_length != other.Array_length) {
			cout << "Lengths of the 2 arrays are not equal";
			return;
		}
		for (ArrayNode* curr_other = other.head->next; curr_other; curr_other = curr_other->next) {
			set_value(get_data(curr_other->index) + curr_other->data, curr_other->index);
		}
	}
};


class SparseMatrix {
private:
	int Array_rows, cols;
	int rows = 0;
	ArrayLinkedList* head = nullptr,* tail = nullptr;
	void link(ArrayLinkedList* list1, ArrayLinkedList* list2) {
		if (list1) {
			list1->next = list2;
		}
		if (list2) {
			list2->prev = list1;
		}
		return;
	}
	ArrayLinkedList* embed_after(ArrayLinkedList * before,int row_index) {
		ArrayLinkedList* middle = new ArrayLinkedList(cols, row_index);
		ArrayLinkedList* after = before->next;
		link(before, middle);
		if (after) {
			link(middle, after);
		}
		else {
			tail = middle;
		}
		return middle;
	}
	ArrayLinkedList* get_ArrayLinked_list(int row_index,bool create_if_not_existed) {
		ArrayLinkedList* curr = head;
		while (curr->next && curr->next->row_index < row_index) {
			curr = curr->next;
		}
		bool founded = curr->next && curr->next->row_index == row_index;
		if (founded) {
			return curr->next;
		}
		if (create_if_not_existed) {
			return embed_after(curr,row_index);
		}
		return nullptr;
	}
public:
	SparseMatrix() = delete;
	SparseMatrix(int Array_rows, int cols) :Array_rows(Array_rows), cols(cols) {
		head = tail = new ArrayLinkedList(cols,-1);
	}
	void set_value(int data, int row_index, int col_index) {
		if (row_index + 1 > Array_rows || col_index + 1 > cols) {
			cout << "Index error\n\n";
			return;
		}
		get_ArrayLinked_list(row_index, true)->set_value(data, col_index);
		rows++;
	}
	void print_matrix() {
		cout << "Print Matrix: " << Array_rows << " x " << cols << endl;
		ArrayLinkedList* curr_row = head->next;
		for (int i{ 0 }; i < Array_rows; i++) {
			if (curr_row && curr_row->row_index == i) {
				curr_row->print_array();
				curr_row = curr_row->next;
			}
			else {
				for (int j{ 0 }; j < cols; j++) {
					cout << "0 ";
				}
			}
			cout << endl;
		}
	}
	void print_matrix_nonzero() {
		cout << "Print Matrix: " << Array_rows << " x " << cols << endl;
		for (ArrayLinkedList* curr_row = head->next; curr_row; curr_row = curr_row->next) {
			curr_row->print_array_nonzero();
		}
	}
	void add(SparseMatrix other) {
		for (ArrayLinkedList* curr_row_other = other.head->next; curr_row_other; curr_row_other = curr_row_other->next) {
			get_ArrayLinked_list(curr_row_other->row_index, true)->add(*curr_row_other);
		}
	}

};

int main() {
	/*
	
	ArrayLinkedList array(10);
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	array.print_array();

	ArrayLinkedList array2(10);
	array2.set_value(1, 4);
	array2.set_value(3, 7);
	array2.set_value(4, 6);

	array2.print_array();

	array.add(array2);

	array.print_array();

	array.print_array_reversed();

	*/

	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print_matrix_nonzero();
	cout << endl;
	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat2.print_matrix_nonzero();
	cout << endl;
	mat.add(mat2);
	mat.print_matrix_nonzero();

	
}