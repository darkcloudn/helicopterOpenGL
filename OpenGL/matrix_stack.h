#pragma once
#include "Angel.h";
class matrix_stack /*Khai báo lớp stack ma trận*/
{
public:
	static const int MAX = 50; /*Số phần tử tối đa của stack*/
	matrix_stack() { index = 0; } /*Constructor: Khởi gán chỉ số phần tử đầu tiên là 0*/
	void push(const mat4& matrix);
	mat4 pop();
private:
	mat4 matrices[MAX]; /*Lưu các ma trận của stack*/
	int index; /*Chỉ số truy cập phần tử đầu tiên*/
};
void matrix_stack::push(const mat4& matrix)
{
	matrices[index] = matrix;
	index++;
}
mat4 matrix_stack::pop()
{
	index--;
	return matrices[index];
}

