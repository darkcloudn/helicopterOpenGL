#pragma once
#include "Angel.h";
typedef vec4 point4;
typedef vec4 color4;
class Thuyen
{
private:
	mat4 instance;
	GLuint model_loc;
	mat4 model;
	int NumPoints;
	mat4 instance_boat;

public:
	Thuyen() {

	}
	Thuyen(mat4 instance, GLuint model_loc, mat4 model, int NumPoints) {
		this->instance = instance;
		this->model = model;
		this->model_loc = model_loc;
		this->NumPoints = NumPoints;
	}

	void init() {
		boat();

	}

	void than() {
		instance = Scale(1.2, 0.2, 0.7);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}
	void dau() {
		instance = Scale(0.15, 0.15, 0.7);
		mat4 translate = Translate(-0.6, 0, 0) * RotateZ(45);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * translate * instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
	}

	void cube(GLfloat w, GLfloat h, GLfloat d)
	{
		instance = Scale(w, h, d);
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance_boat * instance);
		glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	}
	void boat() {
		instance_boat = Identity();

		// body
		cube(1, .2, .61);


		//upper bodies
		instance_boat = Translate(0.03, 0.12, 0);
		cube(.9, .07, .45);


		instance_boat = Translate(0.05, .18, 0);
		cube(.8, .05, .4);

		// smoke
		cube(.1, .5, .1);

		instance_boat = Translate(0.3, 0.23, 0);
		cube(.1, .6, .1);

		// head
		instance_boat = Translate(-0.5, 0, 0) * RotateZ(45);
		cube(0.14, 0.14, 0.6);

		// tail
		instance_boat = Translate(0.5, 0, 0) * RotateZ(45);
		cube(0.14, 0.14, 0.6);


		// cover
		instance_boat = Translate(0, .10, -0.275);
		cube(1, .15, .05);

		instance_boat = Translate(0, .10, 0.275);
		cube(1, .15, .05);



	}


	

};

