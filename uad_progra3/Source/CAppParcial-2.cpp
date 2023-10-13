#include "../stdafx.h"

#include <iostream>
#include <Windows.h>
using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppParcial-2.h"
#include "../Include/CTextureLoader.h"
#include "../Include/CVector3.h"

#include "../Include/MathHelper.h"

/* */
CAppParcial2::CAppParcial2() :
	CAppParcial2(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
}

/* */
CAppParcial2::CAppParcial2(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppEmpty(int window_width, int window_height)" << endl;

	// Initialize class member variables here
	// ======================================
	//
	// ======================================
}

/* */
CAppParcial2::~CAppParcial2()
{
	cout << "Destructor: ~CAppParcial2()" << endl;

	// Free memory allocated in this class instance here
	// =================================================
	//
	// =================================================
	for (unsigned int i : textureID)
	{
		getOpenGLRenderer()->deleteTexture(&i);
	}
	getOpenGLRenderer()->freeGraphicsMemoryForObject(&geometryID);
}

/* */
void CAppParcial2::initialize()
{

}

/* */
void CAppParcial2::run()
{
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		// Note: The following create() method creates the Window itself. Do NOT make any OpenGL calls before this line, your app WILL crash.
		if (getGameWindow()->create(CAPP_PROGRA3_EMPTYAPP_WINDOW_TITLE))
		{
			initialize();

			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

/* */
void CAppParcial2::update(double deltaTime)
{
	// Do not update if delta time is < 0
	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Update app-specific stuff here
	// ===============================
	//
	// ===============================

	//Si no funciona multiplicar por .001

	double degress = rotationSpeed * (deltaTime / 1000.0f);

	rotationActual += degress;
	if (rotationActual >= 360.0)
	{
		rotationActual -= 360.0;
	}
}

/* */
void CAppParcial2::render()
{
	CGameMenu* menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL
		&& menu->isInitialized()
		&& menu->isActive())
	{
		//...
	}
	else // Otherwise, render app-specific stuff here...
	{

		double currentRadians = rotationActual * PI_OVER_180;

		// White 
		// Colors are in the 0..1 range, if you want to use RGB, use (R/255, G/255, G/255)
		float color[3] = { 1.0f, 1.0f, 1.0f };

		// convert total degrees rotated to radians;
		//double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation

		CVector3 posicion = CVector3::ZeroVector();
		posicion = currentPosition;
		posicion.X -= 5;
		MathHelper::Matrix4 rotationTransalation = MathHelper::SimpleModelMatrixRotationTranslation((float)currentRadians, posicion);



		MathHelper::Matrix4 translationmatrix = MathHelper::TranslationMatrix(currentPosition.X, currentPosition.Y, currentPosition.Z);
		MathHelper::Matrix4 rotationMatrix = MathHelper::RotAroundX(currentRadians);
		MathHelper::Matrix4 modelMatrix2 = MathHelper::Multiply(rotationTransalation, translationmatrix);
		MathHelper::Matrix4 scaleMatrix = MathHelper::ScaleMatrix(2.0, 2.0, 2.0);
		MathHelper::Matrix4 modelMatrix = MathHelper::Multiply(translationmatrix, rotationMatrix);
		unsigned int modelShader = currentShaderID;
		unsigned int modelVAO = geometryID;
		unsigned int modelTexture = 0;

		if (textureID.size() > 0)
		{
			modelTexture = textureID[0];
		}

		getOpenGLRenderer()->renderObject(
			&modelShader,
			&modelVAO,
			&modelTexture,
			objeto3D.getNumFaces(),
			color,
			&modelMatrix,
			COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
			false
		);

		getOpenGLRenderer()->renderObject(
			&modelShader,
			&modelVAO,
			&modelTexture,
			objeto3D.getNumFaces(),
			color,
			&modelMatrix2,
			COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
			false
		);

	}
}

/* */
void CAppParcial2::onMouseMove(float deltaX, float deltaY)
{
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
void CAppParcial2::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}


void CAppParcial2::onF2(int mods)
{
	setMenuActive(true);

	std::wstring wideStringBuffer = L"";
	wideStringBuffer.resize(MAX_PATH);

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L" Obj Files\0*.obj\0 Stl Files\0*.stl\0 3DS Files\0*.3ds\0 All files\0*.*\0";
	ofn.lpstrFile = &wideStringBuffer[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a model file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), NULL, 0, NULL, NULL);
		std::string multibyteString(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), &multibyteString[0], size_needed, NULL, NULL);
		cout << "Filename to load: " << multibyteString.c_str() << endl;

		if (!objeto3D.loadFile(multibyteString.c_str()))
		{
			cout << "Unable to load 3D model" << endl;
		}
		else
		{
			setMenuActive(false);
			string materialname;
			vector<string>* materialsnamedata = objeto3D.getmaterialmtl();
			for (int i = 0; i < materialsnamedata->size(); i++)
			{
				unsigned int ID;
				materialname = materialsnamedata->at(i);
				if (CTextureLoader::loadTexture(materialname.c_str(), &ID, getOpenGLRenderer()))
				{
					textureID.push_back(ID);
				}
			}
			if (objeto3D.getconfirmationcoordstexture() && objeto3D.getconfirmationtexture())
			{
				// Switch shaders to textured object ones
				currentShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);
			}
			else
			{
				// Load color shader
				currentShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);
			}

			bool loadedToGraphicsCard = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
				&currentShaderID,
				&geometryID,
				objeto3D.getModelVertices()->data(),
				objeto3D.getNumVertices(),
				objeto3D.getModelNormals()->data(),
				objeto3D.getNumNormals(),
				objeto3D.getModelUvCoords()->data(),
				objeto3D.getNumUvCoords(),
				objeto3D.getModelVerticexIndices()->data(),
				objeto3D.getNumFaces(),
				objeto3D.getModelNormalsIndices()->data(),
				objeto3D.getNumFaces(),
				objeto3D.getModelUvCoordsIndices()->data(),
				objeto3D.getNumFaces()
			);
			if (loadedToGraphicsCard == false)
			{
				cout << "No funciono" << endl;
			}
		}
	}
}