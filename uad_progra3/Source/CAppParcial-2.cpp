#include "../stdafx.h"

#include <iostream>
#include <Windows.h>
using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppParcial-2.h"
#include "../Include/CTextureLoader.h"
#include "../Include/CVector3.h"
#include "../Include/CWideStringHelper.h"

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
	if (estadoProyecto == false)
	{
		runproyecto();
		estadoProyecto = true;
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
		posicion.X -= 5.0f;

		MathHelper::Matrix4 scaleMatrix = MathHelper::ScaleMatrix(2.0, 2.0, 2.0);

		MathHelper::Matrix4 rotationAndTranslation = MathHelper::SimpleModelMatrixRotationTranslation((float)currentRadians, posicion);

		MathHelper::Matrix4 modelMatrix2 = MathHelper::Multiply(rotationAndTranslation, scaleMatrix);

		MathHelper::Matrix4 translationmatrix = MathHelper::TranslationMatrix(currentPosition.X, currentPosition.Y, currentPosition.Z);
		MathHelper::Matrix4 rotationMatrix = MathHelper::RotAroundX(currentRadians);
		MathHelper::Matrix4 modelMatrix = MathHelper::Multiply(rotationMatrix, translationmatrix);
		unsigned int modelShader = currentShaderID;
		unsigned int modelVAO = geometryID;
		unsigned int modelTexture = 0;

		if (textureID.size() > 0)
		{
			modelTexture = textureID[0];
		}
		textureID;
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
		renderObj();
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


IDsRender CAppParcial2::memoryGraphic()
{
	unsigned int shaderId;
	unsigned int geometryId2;
	CVector3 center(0, 0, 0);
	for (int i = 0; i < 6; i++)
	{
		CVector3 temporalVector3 = pointyHexCorner(center, cellSize, i);
		vertices.push_back(temporalVector3.getX());
		vertices.push_back(temporalVector3.getY());
		vertices.push_back(temporalVector3.getZ());
	}

	shaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);

	bool loadedToGraphicsCard = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&shaderId,
		&geometryId2,
		vertices.data(),
		vertices.size(),
		normales.data(),
		normales.size(),
		uvCoords.data(),
		uvCoords.size(),
		Vericextotal.data(),
		Vericextotal.size()/3,
		Normaltotal.data(),
		Normaltotal.size()/3,
		UVCoordstotal.data(),
		4
	);
	if (loadedToGraphicsCard == false)
	{
		cout << "No funciono" << endl;
	}
	IDsRender IDs;
	IDs.ShaderId = shaderId;
	IDs.GeometryId = geometryId2;
	return IDs;
}

//void CAppParcial2::memoryGraphic()
//{
//	if (!objeto3D.loadFile(multibyteString.c_str()))
//	{
//		cout << "Unable to load 3D model" << endl;
//	}
//	else
//	{
//		setMenuActive(false);
//		string materialname;
//		vector<string>* materialsnamedata = objeto3D.getmaterialmtl();
//		for (int i = 0; i < materialsnamedata->size(); i++)
//		{
//			unsigned int ID;
//			materialname = materialsnamedata->at(i);
//			if (CTextureLoader::loadTexture(materialname.c_str(), &ID, getOpenGLRenderer()))
//			{
//				textureID.push_back(ID);
//			}
//		}
//		if (objeto3D.getconfirmationcoordstexture() && objeto3D.getconfirmationtexture())
//		{
//			// Switch shaders to textured object ones
//			currentShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);
//		}
//		else
//		{
//			// Load color shader
//			currentShaderID = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);
//		}
//		vector<unsigned short>* test = objeto3D.getModelVerticexIndices();
//		bool loadedToGraphicsCard = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
//			&currentShaderID,
//			&geometryID,
//			objeto3D.getModelVertices()->data(),
//			objeto3D.getNumVertices(),
//			objeto3D.getModelNormals()->data(),
//			objeto3D.getNumNormals(),
//			objeto3D.getModelUvCoords()->data(),
//			objeto3D.getNumUvCoords(),
//			objeto3D.getModelVerticexIndices()->data(),
//			objeto3D.getNumFaces(),
//			objeto3D.getModelNormalsIndices()->data(),
//			objeto3D.getNumFaces(),
//			objeto3D.getModelUvCoordsIndices()->data(),
//			objeto3D.getNumFaces()
//		);
//		if (loadedToGraphicsCard == false)
//		{
//			cout << "No funciono" << endl;
//		}
//	}
//}

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


void CAppParcial2::openFile()
{
	Vericextotal.push_back(0);
	Vericextotal.push_back(1);
	Vericextotal.push_back(5);
	Vericextotal.push_back(1);
	Vericextotal.push_back(2);
	Vericextotal.push_back(5);
	Vericextotal.push_back(5);
	Vericextotal.push_back(2);
	Vericextotal.push_back(4);
	Vericextotal.push_back(2);
	Vericextotal.push_back(3);
	Vericextotal.push_back(4);
	for (int i = 0; i < 12; i++)
	{
		Normaltotal.push_back(0);
	}
	for (int i = 0; i < 12; i++)
	{
		UVCoordstotal.push_back(0);
	}
	for (int i = 0; i < 3; i++)
	{
		normales.push_back(0);
		normales.push_back(1);
		normales.push_back(0);
	}
	for (int i = 0; i < 3; i++)
	{
		uvCoords.push_back(0.0f);
		uvCoords.push_back(0.0f);
	}
	std::ifstream archivo("Resources//MEDIA//HEXGRID//hexgrid_cfg.json");
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo JSON." << std::endl;
		return;
	}

	json jsondata;
	archivo >> jsondata;

	numCols = jsondata["HexGrid"]["numCols"];
	numRows = jsondata["HexGrid"]["numRows"];
	cellSize = jsondata["HexGrid"]["cellSize"];
	string temporalOrientation = jsondata["HexGrid"]["orientation"];
	orientation = temporalOrientation;

	for (const auto& objeto : jsondata["Models"])
	{
		std::string nombre = objeto["name"];
		std::string filename = objeto["filename"];
		wstring wFilepath;
		std::string filepath;
		CWideStringHelper::GetResourceFullPath(filename.c_str(), wFilepath, filepath);
		vMapasObjNamesId[nombre];
		vMapasObjNamesId[nombre] = getMemoryGraphic(filepath);
	}
	for (const auto& objeto : jsondata["ModelInstances"])
	{
		
		std::string nombre = objeto["model"];
		int	posRow = objeto["row"];
		int	posCol = objeto["column"];
		float escala = objeto["scale"];
		std::vector<float> rotationTempopral = objeto["rotation"];
		CVector3 vRotation;
		vRotation.X = rotationTempopral[0];
		vRotation.Y = rotationTempopral[1];
		vRotation.Z = rotationTempopral[2];
		MathHelper::Matrix4 matrixCalculo;
		matrixCalculo = MathHelper::RotAroundX(rotationTempopral[0]);
		matrixCalculo = MathHelper::RotAroundY(rotationTempopral[1]);
		matrixCalculo = MathHelper::RotAroundZ(rotationTempopral[2]);
		matrixCalculo = MathHelper::ScaleMatrix(escala, escala, escala);
		objData dataObj;
		dataObj.nameObj = nombre;
		dataObj.posCol = posCol;
		dataObj.posRow = posRow;
		dataObj.posicionMatriz = matrixCalculo;
		dataObjs.push_back(dataObj);
	}

	archivo.close();


}

CVector3 CAppParcial2::pointyHexCorner(CVector3 centro, float size, int i)
{
	float angle_deg = 60 * i - 30;
	float angle_rad = 3.1416 / 180 * angle_deg;
	return CVector3(centro.getX() + (size * cos(angle_rad)), 0, centro.getZ() + (size * sin(angle_rad)));
}

IDsRender CAppParcial2::getMemoryGraphic(const string& filename)
{
	obj3D newobject;
	IDsRender temporalObjectId;
	unsigned int currentShaderId;
	unsigned int currentgeometryId;
	if (!newobject.loadFile(filename))
	{
		cout << "Unable to load 3D model" << endl;
	}
	else
	{
		setMenuActive(false);
		string materialname;
		vector<string>* materialsnamedata = newobject.getmaterialmtl();
		for (int i = 0; i < materialsnamedata->size(); i++)
		{
			unsigned int ID;
			materialname = materialsnamedata->at(i);
			if (CTextureLoader::loadTexture(materialname.c_str(), &ID, getOpenGLRenderer()))
			{
				textureID.push_back(ID);
			}
		}
		if (newobject.getconfirmationcoordstexture() && newobject.getconfirmationtexture())
		{
			// Switch shaders to textured object ones
			currentShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);
		}
		else
		{
			// Load color shader
			currentShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);
		}
		vector<unsigned short>* test = newobject.getModelVerticexIndices();
		bool loadedToGraphicsCard = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
			&currentShaderId,
			&currentgeometryId,
			newobject.getModelVertices()->data(),
			newobject.getNumVertices(),
			newobject.getModelNormals()->data(),
			newobject.getNumNormals(),
			newobject.getModelUvCoords()->data(),
			newobject.getNumUvCoords(),
			newobject.getModelVerticexIndices()->data(),
			newobject.getNumFaces(),
			newobject.getModelNormalsIndices()->data(),
			newobject.getNumFaces(),
			newobject.getModelUvCoordsIndices()->data(),
			newobject.getNumFaces()
		);
		if (loadedToGraphicsCard == false)
		{
			cout << "No funciono" << endl;
		}
		temporalObjectId.GeometryId = currentgeometryId;
		temporalObjectId.ShaderId = currentShaderId;
		temporalObjectId.numFaces = newobject.getNumFaces();
	}
	return temporalObjectId;
}

void CAppParcial2::renderObj()
{
	double posicionX = -15;
	unsigned int modelTexture = 0;
	unsigned int modelShader2;
	unsigned int modelVAO2;
	for (int i = 0; i < RenderOBJ.size(); i++)
	{
		modelShader2 = RenderOBJ[0].ShaderId;
		modelVAO2 = RenderOBJ[0].GeometryId;
	}

	bool menos = true;
	MathHelper::Matrix4 Hexgrid;
	CVector3 posicionhex(posicionX, -5, -10);
	for (int j = 0; j < numRows; j++)
	{
		for (int i = 0; i < numCols; i++)
		{
			float colorHEX[3] = { .15f, .61f, .15f };
			Hexgrid = MathHelper::TranslationMatrix(posicionhex.getX(), posicionhex.getY(), posicionhex.getZ());
			getOpenGLRenderer()->renderObject(
				&modelShader2,
				&modelVAO2,
				&modelTexture,
				4,
				colorHEX,
				&Hexgrid,
				COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
				false
			);
			for (int k = 0; k < dataObjs.size(); k++)
			{
				if (dataObjs[k].posCol == i && dataObjs[k].posRow == j)
				{
					float colorOBJ[3] = { 0.0f, .3f, 0.0f };
					dataObjs[k].posicionMatriz = MathHelper::TranslationMatrix(posicionhex.getX(), posicionhex.getY(), posicionhex.getZ());
					unsigned int textureId;
					unsigned int geometryId;
					geometryId = vMapasObjNamesId[dataObjs[k].nameObj].GeometryId;
					textureId = vMapasObjNamesId[dataObjs[k].nameObj].ShaderId;
					getOpenGLRenderer()->renderObject(
						&textureId,
						&geometryId,
						&modelTexture,
						vMapasObjNamesId[dataObjs[k].nameObj].numFaces,
						colorOBJ,
						&dataObjs[k].posicionMatriz,
						COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
						false
					);
				}
			}
			posicionhex.X += sqrt(3) * cellSize;
		}
		posicionhex.Z += ((-2 * cellSize) * (.75));
		if (menos == true)
		{
			posicionhex.X = posicionX - ((sqrt(3) * cellSize) / 2);
			menos = false;
		}
		else
		{
			posicionhex.X = posicionX;
			menos = true;
		}
	}
}

void CAppParcial2::runproyecto()
{
	openFile();
	IDsRender temporealHEX = memoryGraphic();
	RenderOBJ.push_back(temporealHEX);
}