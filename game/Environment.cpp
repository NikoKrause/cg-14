#include "Environment.hpp"

void Environment::draw(Mat4f viewMat, Mat4f projMat)
{

	m_program.prime([&](HotProgram& hotprog)
	{

		viewMat.setColumn(3, Vec4f(0,0,0,1));
		Mat4f mat;
		mat.setToIdentity();
		mat.setDiagonal(Vec4f(2,2,2,1));
		
		hotprog.uniform["u_transform"] = projMat * viewMat;
		hotprog.uniform["u_light"] = 1.0f;
		hotprog.draw(m_sphere, PrimitiveType::TriangleStrip);

	});

}

void Environment::init()
{

	VShader vs;
	vs.compile(loadShaderFromFile("shader/Environment.vsh"));
	FShader fs;
	fs.compile(loadShaderFromFile("shader/Environment.fsh"));

  // create program and link the two shaders
	m_program.create(vs, fs);

  m_sphere.create(3 + 3, 8, 14);
  m_sphere.prime<Vec3f, Vec3f>([](HotVertexSeq<Vec3f, Vec3f>& hot)
  {

  	hot.vertex[0].set(Vec3f(-1, -1, 1), Vec3f(1,1,1));
  	hot.vertex[1].set(Vec3f(1, -1, 1), Vec3f(1,1,1));
  	hot.vertex[2].set(Vec3f(-1, 1, 1) , Vec3f(0,0,1));
  	hot.vertex[3].set(Vec3f(1, 1, 1), Vec3f(0,0,1));
  	hot.vertex[4].set(Vec3f(-1, -1, -1), Vec3f(1,1,1));
  	hot.vertex[5].set(Vec3f(1, -1, -1), Vec3f(1,1,1));
  	hot.vertex[6].set(Vec3f(-1, 1, -1), Vec3f(0,0,1));
  	hot.vertex[7].set(Vec3f(1, 1, -1), Vec3f(0,0,1));

  	hot.index[0] = 0;
  	hot.index[1] = 1;
  	hot.index[2] = 2;
  	hot.index[3] = 3;
  	hot.index[4] = 7;
  	hot.index[5] = 1;
  	hot.index[6] = 5;
  	hot.index[7] = 4;
  	hot.index[8] = 7;
  	hot.index[9] = 6;
  	hot.index[10] = 2;
  	hot.index[11] = 4;
  	hot.index[12] = 0;
  	hot.index[13] = 1;

  });

}

