// uad_progra3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Include/CApp.h"
#include "Include/CAppCubeTest.h"
#include "Include/CAppObjLoader.h"
#include "Include/CAppGeometricFigures.h"
#include "Include/CAppEmpty.h"
#include "Include/CAppParcial-1.h"
#include "Include/CAppParcial-2.h"
#include "Include/CAppParcial-3.h"
#include "Include/Parcial-1.h"
#include "Include/Plane.h"
#include "Include/Frustum.h"

int main(int argc, char* argv[])
{
	CVector3 pt0{ 3.0f, 6.0f, 0.0f };
	CVector3 pt1{3.0f, 3.0f, 0.0f};
	CVector3 pt2{ 3.0f, 6.0f, -3.0f };

	CVector3 pt3{ 1.0f, 5.0f, -5.0f };
	Plane prueba(pt0, pt1, pt2);

	cout << "Normal X: " << prueba.A << endl;
	cout << "Normal Y: " << prueba.B << endl;
	cout << "Normal Z: " << prueba.C << endl;

	cout << "Distancia a origen " << prueba.D << endl;

	cout << "Distancia a vertice 0: " << prueba.distanceToPoint(pt0) << endl;
	cout << "Distancia a vertice 1: " << prueba.distanceToPoint(pt1) << endl;
	cout << "Distancia a vertice 2: " << prueba.distanceToPoint(pt2) << endl;

	cout << "Distancia a vertice 3: " << prueba.distanceToPoint(pt3) << endl;


	CVector3 eyePos{ 0.0f, 0.0f, 0.0f };
	CVector3 lookAtPos{ 0.0f, 0.0f, -5.0f };
	CVector3 upVector{ 0.0f, 1.0f, 0.0f };
	CVector3 rightVector{ 1.0f, 0.0f, 0.0f };
	ViewFrustum frustum;
	frustum.update(eyePos, lookAtPos, upVector, rightVector, 0.001f, 1000.0f, 75.0f, (1024.0f / 768.0f));
	
	cout << "Top Plane: X -> " << frustum.m_planes[0].A << " Y -> " << frustum.m_planes[0].B << " Z -> " << frustum.m_planes[0].C << " -> " << endl; //La normal del top plane
	cout << "Buttom Plane: X -> " << frustum.m_planes[1].A << " Y -> " << frustum.m_planes[1].B << " Z -> " << frustum.m_planes[1].C << " -> " << endl; //La normal del top plane
	cout << "Left Plane: X -> " << frustum.m_planes[2].A << " Y -> " << frustum.m_planes[2].B << " Z -> " << frustum.m_planes[2].C << " -> " << endl; //La normal del top plane
	cout << "Right Plane: X -> " << frustum.m_planes[3].A << " Y -> " << frustum.m_planes[3].B << " Z -> " << frustum.m_planes[3].C << " -> " << endl; //La normal del top plane
	cout << "Near Plane: X -> " << frustum.m_planes[4].A << " Y -> " << frustum.m_planes[4].B << " Z -> " << frustum.m_planes[4].C << " -> " << endl; //La normal del top plane
	cout << "Far Plane: X -> " << frustum.m_planes[5].A << " Y -> " << frustum.m_planes[5].B << " Z -> " << frustum.m_planes[5].C << " -> " << endl; //La normal del top plane
	
	CVector3 point(0.0f, 0.0f, -500.0f);

	cout << "Is visible: " << frustum.isPointVisible(point) << endl;
	CApp *app = NULL;					// Pointer to BASE class CApp
	//app = new CAppEmpty(800, 600);		// Using pointer to base class, create a new object of DERIVED class
	app = new CAppParcial3(2000, 1000);
	app->run();							// Run the app
	delete app;							// Delete pointer
	app = NULL;							// Set pointer to NULL

	return 0;
}

