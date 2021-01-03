#pragma once
#include "Angel.h";
typedef vec4 point4;
typedef vec4 color4;
class ChongChong
{
private:
	mat4 instance;
	GLuint model_loc;
	mat4 model;
	int NumPoints;
	
public :
	ChongChong() {

	}
	ChongChong(mat4 instance, GLuint model_loc, mat4 model, int NumPoints ) {
		this->instance = instance;
		this->model = model;
		this->model_loc = model_loc;
		this->NumPoints = NumPoints;

	}
	void init(mat4 quay) {
		tru(instance, model_loc, model, NumPoints);
		loi(instance, model_loc, model, NumPoints);
		canh1(instance, model_loc, model, NumPoints, quay);
		canh2(instance, model_loc, model, NumPoints, quay);
		canh3(instance, model_loc, model, NumPoints, quay);
	}
	void tru(mat4 instance, GLuint model_loc, mat4 model, int NumPoints) {
		instance = Scale(0.1f, 2.0f, 0.1f);
		mat4 translate = Translate(0, 0.0, 0.0);// *RotateZ(90);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*translate*instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	void loi(mat4 instance, GLuint model_loc, mat4 model, int NumPoints) {
		instance = Scale(0.05f, 0.05f, 0.3f);
		mat4 translate = Translate(0, 1.025, 0.0);// *RotateZ(90);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*translate*instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	void canh1(mat4 instance, GLuint model_loc, mat4 model, int NumPoints, mat4 quay) {
		instance = Scale(0.1f, 0.7f, 0.05f);
		mat4 translate = Translate(0, 1.35, 0.18F)*Translate(0, -0.35, 0)*quay*Translate(0,0.35,0);//  *RotateZ(90);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*translate*instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	void canh2(mat4 instance, GLuint model_loc, mat4 model, int NumPoints, mat4 quay) {
		instance = Scale(0.1f, 0.7f, 0.05f);
		mat4 translate = Translate(0, 1.0, 0.09f)*quay*RotateZ(130)*Translate(0, 0.35f, 0.09f);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*translate*instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	void canh3(mat4 instance, GLuint model_loc, mat4 model, int NumPoints , mat4 quay) {
		instance = Scale(0.1f, 0.7f, 0.05f);
		mat4 translate = Translate(0, 1.0, 0.09f)*quay*RotateZ(-130)*Translate(0, 0.35f, 0.09f);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*translate*instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	

};

