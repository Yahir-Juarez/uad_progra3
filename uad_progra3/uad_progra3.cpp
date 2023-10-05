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
#include "Include/Parcial-1.h"

int main()
{
	CApp *app = NULL;					// Pointer to BASE class CApp
	//app = new CAppEmpty(800, 600);		// Using pointer to base class, create a new object of DERIVED class
	app = new CAppParcial1(2000, 2000);
	app->run();							// Run the app
	delete app;							// Delete pointer
	app = NULL;							// Set pointer to NULL

	return 0;
}

