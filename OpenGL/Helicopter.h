#pragma once
#include "Angel.h";
#include "matrix_stack.h"
typedef vec4 point4;
typedef vec4 color4;
class Helicopter
{
private:
	mat4 instance;
	GLuint model_loc;
	mat4 model;
	int NumPoints;
	matrix_stack mvStack;
public:

	Helicopter() {
		
	}
	Helicopter(mat4 instance, GLuint model_loc, mat4 model, int NumPoints) {
		this->instance = instance;
		this->model = model;
		this->model_loc = model_loc;
		this->NumPoints = NumPoints;

	}
	void init(mat4 rotateCanhQuat,mat4 diChuyen,mat4 quay,GLuint program) {
		
		than(diChuyen, quay);
		than1(diChuyen, quay);
		than2(diChuyen, quay);
		dau(diChuyen, quay);	
		cang(diChuyen, quay);
		cang1(diChuyen, quay);
		cangdoc(diChuyen, quay);
		cangdoc1(diChuyen, quay);
		cangdoc3(diChuyen, quay);
		cangdoc4(diChuyen, quay);
		duoi(diChuyen, quay);
		duoi1(diChuyen, quay);
		duoi2(diChuyen, quay);
		canhquat(rotateCanhQuat, diChuyen, quay);
		tru(diChuyen, quay);	
	}

	
	void than(mat4 diChuyen,mat4 quay) {

		mvStack.push(model);
		instance = Scale(1, 0.5, 0.5);
		model *= diChuyen * quay*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glColor3f(1.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}
	void than1(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Translate(0.0,-0.1,0.3)*Scale(0.75, 0.1, 0.1);
		model *= diChuyen * quay*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}
	void than2(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Translate(0.0, -0.1, -0.3)*Scale(0.75, 0.1, 0.1);
		model *= diChuyen * quay*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}
	void dau(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.35355339059, 0.35355339059, 0.5);
		mat4 translate = Translate(-0.5, 0, 0)*RotateZ(45);
		model *= diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}

	void cangdoc(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.3, 0.05, 0.05);
		mat4 translate = Translate(0.2, -0.30, 0.15);
		mat4 rotate = RotateZ(90);
		model *= *diChuyen*quay*translate*rotate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}
	void cangdoc1(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.3, 0.05, 0.05);
		mat4 translate = Translate(0.2, -0.30, -0.15);
		mat4 rotate = RotateZ(90);
		model *= diChuyen * quay*translate*rotate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints); 
		model = mvStack.pop();

	}
	void cangdoc3(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.3, 0.05, 0.05);
		mat4 translate = Translate(-0.2, -0.30, 0.15);
		mat4 rotate = RotateZ(90);
		model *= diChuyen*quay*translate*rotate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);   
		model = mvStack.pop();
	}
	void cangdoc4(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.3, 0.05, 0.05);
		mat4 translate = Translate(-0.2, -0.30, -0.15);
		mat4 rotate = RotateZ(90);
		model *= diChuyen * quay*translate*rotate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();

	}

	void cang(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.7, 0.05, 0.05);
		mat4 translate = Translate(0, -0.45, 0.15);
		model *= diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints); 
		model = mvStack.pop();
	}
	void cang1(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.7, 0.05, 0.05);
		mat4 translate = Translate(0, -0.45, -0.15);
		model *= diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints); 
		model = mvStack.pop();
	}
	void duoi(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(1, 0.1, 0.1);
		mat4 translate = Translate(1, -0.05, 0.0);
		model*=diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints); 
		model = mvStack.pop();
	}
	void duoi1(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.3, 0.1, 0.05);
		mat4 translate = Translate(1.5, 0.05, 0.0)*RotateZ(70);
		model *= diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);  
		model = mvStack.pop();
	}
	void duoi2(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.2, 0.1, 0.05);
		mat4 translate = Translate(1.5, -0.1, 0.0)*RotateZ(-70);
		model*=diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints); 
		model = mvStack.pop();
	}

	void canhquat1(mat4 rotate, mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(2, 0.1, 0.03);
		mat4 translate = Translate(0, 0.5, 0.0)*rotate*RotateX(90)*RotateZ(90);
		model*=diChuyen*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    
		model = mvStack.pop();

	}
	void canhquat2(mat4 rotate, mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(2, 0.1, 0.03);
		mat4 translate = Translate(0, 0.5, 0.0)*rotate*RotateX(90)*RotateZ(35);
		model *= diChuyen*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);   
		model = mvStack.pop();

	}
	void canhquat3(mat4 rotate, mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(2, 0.1, 0.03);
		mat4 translate = Translate(0, 0.5, 0.0)*rotate*RotateX(90)*RotateZ(-35);
		model *=diChuyen*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    
		model = mvStack.pop();

	}

	void tru1(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.5, 0.25, 0.25);
		mat4 translate = Translate(0, 0.25, 0.0);//*RotateZ(-35);
		model*=diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);   
		model = mvStack.pop();
	}
	void tru2(mat4 diChuyen, mat4 quay) {
		mvStack.push(model);
		instance = Scale(0.2, 0.07, 0.07);
		mat4 translate = Translate(0, 0.4, 0.0)*RotateZ(90);
		model*=diChuyen*quay*translate*instance;
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);   
		model = mvStack.pop();
	}
	void tru(mat4 diChuyen, mat4 quay) {
		tru1(diChuyen, quay);
		tru2(diChuyen, quay);
	}
	void canhquat(mat4 rotate, mat4 diChuyen, mat4 quay) {
		canhquat1(rotate, diChuyen, quay);
		canhquat2(rotate, diChuyen, quay);
		canhquat3(rotate, diChuyen, quay);
	}
	
};

