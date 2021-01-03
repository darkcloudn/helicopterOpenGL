/*Chương trình chiếu sáng Blinn-Phong (Phong sua doi) cho hình lập phương đơn vị, điều khiển quay bằng phím x, y, z, X, Y, Z.*/

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/
#include "ChongChong.h"
#include "Helicopter.h"
#include "Thuyen.h"
#include "matrix_stack.h"

// remember to prototype
void generateGeometry(void);
void initGPUBuffers(void);
void shaderSetup(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

typedef vec4 point4;
typedef vec4 color4;
using namespace std;

// Số các đỉnh của các tam giác
const int NumPoints = 36;

point4 points[NumPoints]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
vec3 normals[NumPoints]; /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/

point4 vertices[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/

GLuint program;

GLfloat theta[3] = { 0, 0, 0 };
GLfloat dr = 5;

mat4 model;
GLuint model_loc;
mat4 projection;
GLuint projection_loc;
mat4 view;
GLuint view_loc;

mat4 instance;
mat4 instance_than;


void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
	vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
	vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
	vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
	vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
	vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
	vertex_colors[6] = color4(1.0, 0.5, 0.0, 1.0); // orange
	vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan
}
int Index = 0;
void quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
{
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];
	vec3 normal = normalize(cross(u, v));

	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[b]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[d]; Index++;
}
void makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/

{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
void generateGeometry(void)
{
	initCube();
	makeColorCube();
}


void initGPUBuffers(void)
{
	// Tạo một VAO - vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Tạo và khởi tạo một buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);


}

void shaderSetup(void)
{
	// Nạp các shader và sử dụng chương trình shader
	program = InitShader("vshader1.glsl", "fshader1.glsl");   // hàm InitShader khai báo trong Angel.h
	glUseProgram(program);

	// Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
	GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_vPosition);
	glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors)));

	/* Khởi tạo các tham số chiếu sáng - tô bóng*/
	point4 light_position(0.0, 0.0, 1.0, 0.0);
	color4 light_ambient(0.2, 0.2, 0.2, 1.0);
	color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
	color4 light_specular(1.0, 1.0, 1.0, 1.0);

	color4 material_ambient(1.0, 0.0, 1.0, 1.0);
	color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
	//(1.0, 0.0, 0.0, 1.0);
	//0.0f, 1.0f, 0.0f,1.0
	color4 material_specular(1.0, 0.8, 0.0, 1.0);
	float material_shininess = 100.0;

	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	model_loc = glGetUniformLocation(program, "Model");
	projection_loc = glGetUniformLocation(program, "Projection");
	view_loc = glGetUniformLocation(program, "View");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);        /* Thiết lập màu trắng là màu xóa màn hình*/
}

float xoay = 10;
float Theta[]{ -30, 45, 0 };
float Ox=0, Oy=0, Oz=0;
bool checkBay = false;
bool checkHaCanh = false;
float xx = 1.0;
int dem = 0;
float xoayAll = 5;
float xoayAllThuyen = 5;
float diChuyenThuyenOx = 0;
float diChuyenThuyenOy = 0;
float diChuyenThuyenOz = 0;

void ground() {
	instance = Translate(-1,-1,0)*Scale(3 ,0.1, 4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
}

void quay() {
	if (dem < 500) {
		xoay += 0.5;
		dem++;
	}
	else if (dem < 700) {
		xoay += 0.8;
		dem++;
	}
	else if (dem < 1000) {
		xoay += 1;
		dem++;
	}
	else if (dem < 1200) {
		xoay += 1.2;
		dem++;
	}
	else if (dem < 1500) {
		xoay += 1.5;
		dem++;
	}
	else if (dem < 2000) {
		xoay += 2;
	}
	
	if (xoay > 360) {
		xoay = -360;
	}
	glutPostRedisplay();
}
float xoayCanhQuat = 0;
void xoayCanhQuatChongChong() {
	
	if (xoayCanhQuat > 360) {
		xoayCanhQuat = -360;
	}
	xoayCanhQuat += 1;
	glutPostRedisplay();
}
void stopQuay() {
	if (dem > 2500) {
		xoay += 2;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 2300) {
		xoay += 1.7;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 2000) {
		xoay += 1.4;	
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 1700) {
		xoay += 1.1;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 1400) {
		xoay += 0.9;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 1100) {
		xoay += 0.6;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 700) {
		xoay += 0.3;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem > 500) {
		xoay += 0.1;
		if (xoay > 360) {
			xoay = -360;
		}
		dem--;
	}
	else if (dem == 0) {
		xoay = 0;
	}

	glutPostRedisplay();
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (checkBay) {
		quay();
	}
	if (checkHaCanh) {
		checkBay = false;
		stopQuay();
	}
	xoayCanhQuatChongChong();
	
	
	
	
	ChongChong chongchong = ChongChong(instance, model_loc, Translate(-2,0,-2)*model, NumPoints);
	chongchong.init(RotateZ(xoayCanhQuat));
	ChongChong chongchong1 = ChongChong(instance, model_loc, Translate(-1,0,-2)*model, NumPoints);
	chongchong1.init(RotateZ(xoayCanhQuat));
	ChongChong chongchong2 = ChongChong(instance, model_loc, Translate(0,0,-2)*model, NumPoints);
	chongchong2.init(RotateZ(xoayCanhQuat));
	ground();
	
	Helicopter helicopter = Helicopter(instance, model_loc, Translate(0,-0.5,0)*model, NumPoints);
	helicopter.init(RotateY(xoay), Translate(Ox, Oy, Oz), RotateY(xoayAll),program);



	Thuyen thuyen = Thuyen(instance, model_loc, Translate(diChuyenThuyenOx, diChuyenThuyenOy, diChuyenThuyenOz)*Translate(1.3,-0.9,1)*RotateY(xoayAllThuyen)*model, NumPoints);
	thuyen.init();
	//const vec3 viewer_pos(0.0, 0.0, 2.0);  /*Trùng với eye của camera*/
	
	
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	vec4 eye(0, 0, 3, 1);
	vec4 at(0, 0, 0, 1);
	vec4 up(0, 1, 0, 1);

	view = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
	projection = Frustum(-2, 2, -2, 2, 2, 8);


	//projection = Frustum(-1, 1, -1, 1, 1, 4);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	glViewport(0, 0, width, height);
}
float tocDoDiChuyen = 0.03;
void keyboard(unsigned char key, int x, int y)
{
	// keyboard handler

	switch (key) {
	case 033:			// 033 is Escape key octal value
		exit(1);		// quit program
		break;
	case 'x':
		model *= RotateX(dr);
		glutPostRedisplay();
		break;
	case 'X':
		model *= RotateX(-dr);
		glutPostRedisplay();
		break;
	case 'y':
		model *= RotateY(dr);
		glutPostRedisplay();
		break;
	case 'Y':
		model *= RotateY(-dr);
		glutPostRedisplay();
		break;
	case 'z':
		model *= RotateZ(dr);
		glutPostRedisplay();
		break;
	case 'Z':
		model *= RotateZ(-dr);
		glutPostRedisplay();
		break;
	///////////////////////////COntrol
	case ' ':
		checkBay = true;
		checkHaCanh = false;
		glutPostRedisplay();
		break;
	// translate
	case 'w':
		Oz -= tocDoDiChuyen;
		
		glutPostRedisplay();
		break;
	case 'p':
		checkBay = false;
		checkHaCanh = true;
		dem = 2500;
		glutPostRedisplay();
		break;
	case 'a':
		Ox -= tocDoDiChuyen;
		
		quay();
		glutPostRedisplay();
		break;
	case 's':
		Oz += tocDoDiChuyen;
		
		glutPostRedisplay();
		break;
	case 'd':
		Ox += tocDoDiChuyen;
		
		glutPostRedisplay();
		break;
	case 'q':
		if (xoayAll > 360) {
			xoayAll = -360;
		}
		xoayAll += 5;
		cout << xoayAll << endl;
		glutPostRedisplay();
		break;
	case 'e':	
		if (xoayAll < -360) {
			xoayAll = 360;
		}
		xoayAll -= 5;
		cout << xoayAll << endl;
		glutPostRedisplay();
		break;
	case '8':
		Oy += tocDoDiChuyen;
		glutPostRedisplay();
		break;
	case '2':
		Oy -= tocDoDiChuyen;
		if (Oy < 0) {
			Oy = 0;
		}
		glutPostRedisplay();
		break;
	case 'A':
		diChuyenThuyenOx -= 0.1;
		break;
	case 'D':
		diChuyenThuyenOx += 0.1;
		break;
	case 'W':
		diChuyenThuyenOz -= 0.1;
		break;
	case 'S':
		diChuyenThuyenOz += 0.1;
		break;
		
	case 'Q':
		if (xoayAllThuyen > 360) {
			xoayAllThuyen = -360;
		}
		xoayAllThuyen += 5;
		cout << xoayAll << endl;
		glutPostRedisplay();
		break;
	case 'E':
		if (xoayAllThuyen < -360) {
			xoayAllThuyen = 360;
		}
		xoayAllThuyen -= 5;
		cout << xoayAllThuyen << endl;
		glutPostRedisplay();
		break;
	}

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("A Cube is rotated by keyboard and shaded");
	glewInit();
	generateGeometry();
	initGPUBuffers();
	shaderSetup();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
