#pragma once
#include "Triangle3D.h"
#include <SDL.h>
#include <vector>

class BSP {
public:

	BSP()
	{

	}
	struct Node;
	void CreateTree(vector<Triangle3D>& tris)
	{
		cout << "Creating BSP Tree..." << endl;
		root = new Node();
		root->left = 0; root->right = 0; root->tri = &tris[0];
		for (int i = 1; i < tris.size(); i++)
		{
			AddTriangle(root, tris[i]);
		}
	}
	void AddTriangle(Node*& cr, Triangle3D& tri)
	{
		float tmpswap;
		Vec4d vecswap, A, B;
		float fa, fb, fc,ee;
		Vec4d a, b, c;
		a = tri.one; b = tri.two; c = tri.three;
		
		ee = .5f;
		fa = cr->tri->planeequationself(a);
		fb = cr->tri->planeequationself(b);
		fc = cr->tri->planeequationself(c);
		
		if (abs(fa) < ee)
			fa = 0;
		if (abs(fb) < ee)
			fb = 0;
		if (abs(fc) < ee)
			fc = 0;

		if (fa >= 0 && fb >= 0 && fc >= 0)
		{
			if (cr->left == 0)
			{
				Node* tmp = new Node();
				tmp->left = 0; tmp->right = 0; tmp->tri = &tri;
				cr->left = tmp;
			}
			else
			{
				AddTriangle(cr->left, tri);
			}
		}
		else if (fa <= 0 && fb <= 0 && fc <= 0)
		{
			if (cr->right == 0)
			{
				Node* tmp = new Node();
				tmp->left = 0; tmp->right = 0; tmp->tri = &tri;
				cr->right = tmp;
			}
			else
			{
				AddTriangle(cr->right, tri);
			}
		}
		else
		{
			//clip triangle
			if (fa*fc >= 0)
			{
				swap(fc, fb);
				swap(c, b);

				swap(fa, fb);
				swap(a, b);
			}
			else if (fb*fc >= 0)
			{
				swap(fa, fc);
				swap(a, c);

				swap(fa, fb);
				swap(a, b);
			}
			Vec4d n = cr->tri->calculatenormal();
			A = cr->tri->planeintersectpoint(cr->tri->one, n, a, c);
			B = cr->tri->planeintersectpoint(cr->tri->one, n, b, c);
			Triangle3D* t1 = new Triangle3D(a, b, A);
			Triangle3D* t2 = new Triangle3D(b, B, A);
			Triangle3D* t3 = new Triangle3D(A, B, c);
			/*now decide if c is in the plane or outside if its in the plane we pass in t3 else pass in t1 and t2*/

			if (fc >= 0)
			{
				if (cr->left == 0)
				{
					Node* tmp = new Node;
					tmp->left = 0; tmp->right = 0; tmp->tri = t1;
					cr->left = tmp;
				}
				else
					AddTriangle(cr->left, *t1);
				
				AddTriangle(cr->left, *t2);
				
				if (cr->right == 0)
				{
					Node* tmp = new Node;
					tmp->left = 0; tmp->right = 0; tmp->tri = t3;
					cr->right = tmp;
				}
				else
					AddTriangle(cr->right, *t3);
			}
			else
			{
				if (cr->right == 0)
				{
					Node* tmp = new Node;
					tmp->left = 0; tmp->right = 0; tmp->tri = t1;
					cr->right = tmp;
				}
				else
					AddTriangle(cr->right, *t1);

				AddTriangle(cr->right, *t2);

				if (cr->left == 0)
				{
					Node* tmp = new Node;
					tmp->left = 0; tmp->right = 0; tmp->tri = t3;
					cr->left = tmp;
				}
				else
					AddTriangle(cr->left, *t3);
			}
		}

	}

	int Sizestart()
	{
		int counter = 0;
		Size(counter, root);
		return counter;
	}
	void Size(int & counter, Node* cr)
	{
		if (cr == 0)
		{
			return;
		}
		else
		{
			Size(counter, cr->left);
			counter++;
			Size(counter, cr->right);
		}
	}
	void printinfostart()
	{
		printinfo(root);
	}
	void printinfo(Node* cr)
	{
		if (cr == 0)
		{
			return;
		}
		else
		{
			printinfo(cr->left);
			cr->tri->PrintInfo();
			printinfo(cr->right);
		}
	}

	void DrawStart(SDL_Renderer* grender, Vec4d e, bool delay = 0)
	{
		Draw(grender, root, e, delay);
	}
	void Draw(SDL_Renderer* grender, Node* cr, Vec4d e, bool delay = 0)
	{
		if (cr == 0)
		{
			return;
		}
		if (cr->tri->planeequationself(e) < 0)
		{
			Draw(grender, cr->left, e);
			cr->tri->DrawTriangle(55, 55, 55);
			Draw(grender, cr->right, e);
		}
		else
		{
			Draw(grender, cr->right, e);
			cr->tri->DrawTriangle(55, 55, 55);
			Draw(grender, cr->left, e);
		}
	}


	struct Node {
		Triangle3D * tri;
		Node* left;
		Node* right;
	};
	Node* root;

private:

};