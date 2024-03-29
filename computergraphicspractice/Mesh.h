#pragma once
#include <vector>
#include "Triangle3D.h"

class Mesh
{
public:
	Mesh()
	{
		
	}
	void Projection()
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].Projection();
		}
	}
	void AddTriangle(Triangle3D tri)
	{
		Triangles.push_back(tri);
	}
	void Print(int r, int g, int b)
	{
		cout << "printing" << endl;
		extern Vec3d cameralookat;
		extern Vec3d cameralocation;
		Vec4d lookat(cameralookat.x, cameralookat.y, cameralookat.z, 1);
		Vec4d location(cameralocation.x, cameralocation.y, cameralocation.z, 1);
		/*before we print we have to clip all the triangles so pass in our vecotor of triangl3ds and we get another vector of triangl3ds which are our new clipped triangles*/
		vector<Triangle3D> clippedtriangles;
		for (int i = 0; i < Triangles.size(); i++)
		{
			vector<Triangle3D> tmp;
			tmp = Triangles[i].cliptrianglestart(Triangles[i]);

			for (int j = 0; j < tmp.size(); j++)
			{
				clippedtriangles.push_back(tmp[j]);
			}
		}

		for (int i = 0; i < clippedtriangles.size(); i++)
		{
			if (clippedtriangles[i].normal.DotProduct(clippedtriangles[i].one - location) >= 0)
			{
				clippedtriangles[i].one.w = 1; clippedtriangles[i].two.w = 1; clippedtriangles[i].three.w = 1;
				clippedtriangles[i].Print(clippedtriangles[i].r, clippedtriangles[i].g, clippedtriangles[i].b);
				//clippedtriangles[i].TriangleFill(clippedtriangles[i].r, clippedtriangles[i].g, clippedtriangles[i].b);
			}
		}
	}
	void Move(float x, float y, float z)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].Move(x, y,z);
		}
	}

	void ReverseTriangles()
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].ReverseTriangle();
		}
	}
	void SetNormals()
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].normal = Triangles[i].calculatenormal(1);
		}
	}
	void SetColor(int r, int g, int b)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].one.r = r; Triangles[i].one.g = g; Triangles[i].one.b = b;
			Triangles[i].two.r = r; Triangles[i].two.g = g; Triangles[i].two.b = b;
			Triangles[i].three.r = r; Triangles[i].three.g = g; Triangles[i].three.b = b;
		}
	}
	void ReverseNormals()
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].normal = Triangles[i].reversenormal();
		}
	}
	void RodriguesRotation(Vec4d axis, float angle)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].Rodriguesrotate(axis, Triangles[i].one,angle);
			Triangles[i].Rodriguesrotate(axis, Triangles[i].two, angle);
			Triangles[i].Rodriguesrotate(axis, Triangles[i].three, angle);
			Triangles[i].Rodriguesrotate(axis, Triangles[i].normal, angle);
			Triangles[i].normal = Triangles[i].normal.normalize();
		}
	}
	void Rotate(float xangle, float yangle, float zangle, Vec4d center)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].RotateX(xangle,center);
			Triangles[i].normal = Triangles[i].normal.normalize();
			Triangles[i].Rotatey(yangle,center);
			Triangles[i].normal = Triangles[i].normal.normalize();
			Triangles[i].Rotatez(zangle,center);
			Triangles[i].normal = Triangles[i].normal.normalize();
			//Triangles[i].normal = Triangles[i].calculatenormal();
		}
	}
	void Draw(int r, int g, int b)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].DrawTriangle(r, g, b);
		}
	}
	void add(float x, float y, float z)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].one.x += x;
			Triangles[i].two.x += x;
			Triangles[i].three.x += x;

			Triangles[i].one.y += y;
			Triangles[i].two.y += y;
			Triangles[i].three.y += y;

			Triangles[i].one.z += z;
			Triangles[i].two.z += z;
			Triangles[i].three.z += z;
		}
	}
	void Scale(double scalex, double scaley, double scalez)
	{
		for (int i = 0; i < Triangles.size(); i++)
		{
			Triangles[i].Scale(scalex, scaley, scalez);
		}
	}
	vector<Triangle3D> Triangles;
private:

};