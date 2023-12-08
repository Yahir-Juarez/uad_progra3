#pragma once

#ifndef CAppParcial3_H
#define CAppParcial3_H

#include <map>

#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "../Include/Parcial-1.h"
#include "Mundo.h"
#include "Frustum.h"
#include "CCamera.h"
#include "objDataParcal3.h"
#include "QuadtreeNode.h"
#include "Cells.h"
// --------------------------------------------------------------------------------------------------------------------------------------
// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
// --------------------------------------------------------------------------------------------------------------------------------------

class CAppParcial3 : public CApp
{
private:

	// ---------------------------------------------------
	// Private member variables specific to CAppParcial2 only
	// ---------------------------------------------------
	//
	// ---------------------------------------------------
	Mundo jsonObjects;

protected:

	// Method to initialize the menu 
	// (not needed in CAppParcial2, so return false)
	bool initializeMenu() { return false; }

public:
	// Constructors and destructor
	CAppParcial3();
	CAppParcial3(int window_width, int window_height);
	~CAppParcial3();

	// --------------------------------------------------------------------------------------------------------------------------
	// Inherited methods from CApp
	// Initialize(), update(), run(), and render() are PURE VIRTUAL methods, so they need to be implemented in this DERIVED class
	// --------------------------------------------------------------------------------------------------------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// ------------------------------------------------------------------------------------------------------------------------
	// Other inherited methods from CApp. These are optional to override.
	// Only provide an implementation in this DERIVED class if you need them to do something different than the base class CApp
	// -----------------------------------------------------------------------------------------------------------------------

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Called when mouse moves within the window
	void onMouseMove(float deltaX, float deltaY);

	// -----------------------------------------
	// Public methods specific to CAppEmpty only
	// -----------------------------------------
	//
	// -----------------------------------------
	void onF2(int mods) override;                       // F2
	IDsRender memoryGraphic();
	IDsRender getMemoryGraphic(const string& filename);

	void onArrowUp(int mods) override;
	void onArrowDown(int mods) override;
	void onArrowLeft(int mods) override;
	void onArrowRight(int mods) override;

private:

	// ------------------------------------------
	// Private methods specific to CAppEmpty only
	// ------------------------------------------
	//
	// ------------------------------------------
	obj3D objeto3D;
	vector<unsigned int> textureID;
	unsigned int currentShaderID;
	unsigned int geometryID;

	vector<IDsRender> RenderOBJ;

	//11/10/2023

	double rotationSpeed = 90.0f;
	double rotationActual = 0.0f;
	CVector3 currentPosition = { 0.0, -15.0 , -10.0 };

	//////////////////////////////////////////Mundo//////////////////////////////

	int numCols;
	int numRows;
	float cellSize;
	string orientation;


	CVector3 pointyHexCorner(CVector3 centro, float size, int i = 1);
	void openFile();
	vector<float> vertices;
	vector<float> normales;
	vector<float> uvCoords;
	vector<unsigned short> Vericextotal;
	vector<unsigned short> Normaltotal;
	vector<unsigned short> UVCoordstotal;
	map<string, IDsRender> vMapasObjNamesId;

	
	vector<objData> dataObjs;
	void renderObj();
	void runproyecto();

	void instalinzeWorld(int width, int hight);
	Camera* m_camera;



	/////////////////////////////////////////// Tercer Parcial /////////////////////////////////////////////////////////

	struct dataSector
	{
		CVector3 SectorPoint;
		vector<cell> objectsRender;
		int numRows;
		int numColumns;
		int totalFaces;
	};
	vector<cell*> ptrCells;

	QuadtreeNode* nodosQuadtrees;
	vector <dataSector> sectors;
	vector<cell*> m_nodes_cells;
	void getCells();
	void createFrustum(dataSector* actualSector);
	int getTotalNumFaces(dataSector& actualSector);
};

#endif // !CAPPEMPTY_H