#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

class obj3D
{
public:
	obj3D();
	~obj3D();
	bool loadFile(const string& filename);
	vector<float>* getModelVertices();
	int getNumVertices();
	vector<float>* getModelNormals();
	int getNumNormals();
	vector<float>* getModelUvCoords();
	int getNumUvCoords();
	int getNumFaces();
	vector<unsigned short>* getModelVerticexIndices();
	vector<unsigned short>* getModelNormalsIndices();
	vector<unsigned short>* getModelUvCoordsIndices();
	vector<string>* getmaterialmtl() { return &newmtl; }
	bool getconfirmationtexture() const { return textures; }
	bool getconfirmationcoordstexture() const { return UVcoordsTextures; }


private:
	vector<string> newmtl;
	vector<string> map_Kd;
	bool textures = false;
	bool UVcoordsTextures = false;

	vector<float> vertices;
	vector<float> normales;
	vector<float> uvCoords;
	vector<unsigned short> Vericextotal;
	vector<unsigned short> Normaltotal;
	vector<unsigned short> UVCoordstotal;

	int faces = 0;

	struct Caras
	{
		string usemtl;
		vector<unsigned short> v_ind_vertices;
		vector<unsigned short> v_ind_uvs;
		vector<unsigned short> v_ind_normales;
	};

	vector<Caras> v_Caras;
	istringstream LectorCaras(string linea);
	void LectorCarasQuads(string linea);
	void LectorGeneral(vector<float>& typeVector, ifstream& archivo);
	void LectorMtllib(string nombre_archivo);
};
