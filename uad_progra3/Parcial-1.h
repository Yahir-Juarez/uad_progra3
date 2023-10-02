#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

class archivos_obj
{
public:
	archivos_obj();

	vector<string> newmtl;
	vector<string> map_Kd;

	vector<float> vertices;
	vector<float> normales;
	vector<float> uvCoords;

	struct Caras
	{
		string usemtl;
		vector<unsigned int> v_ind_vertices;
		vector<unsigned int> v_ind_uvs;
		vector<unsigned int> v_ind_normales;
	};

	vector<Caras> v_Caras;
private:
	istringstream LectorCaras(string linea);
	void LectorCarasQuads(string linea);
	void LectorGeneral(vector<float>& typeVector, ifstream& archivo);
	void LectorMtllib(string nombre_archivo);
};

archivos_obj::archivos_obj()
{
	ifstream archivo("TestObjects_Triangles.obj");
	if (!archivo.is_open())
	{
		cout << "No se pudo abrir\n";
	}
	else
	{
		cout << "Se abrio\n";
	}
	while (!archivo.eof())
	{
		string indice;
		archivo >> indice;
		if (indice == "v")
		{
			LectorGeneral(vertices, archivo);
		}
		else if (indice == "vn")
		{
			LectorGeneral(normales, archivo);
		}
		else if (indice == "vt")
		{
			LectorGeneral(uvCoords, archivo);
		}
		//Lector de caras
		else if (indice == "f")
		{
			string linea;
			string palabra;
			getline(archivo, linea);
			istringstream lins(linea);
			int contador = 0;
			while (lins >> palabra)
			{
				contador++;
			}
			//Triangulos
			if (contador == 3)
			{
				LectorCaras(linea);
			}
			//Quads
			else if (contador == 4)
			{
				LectorCarasQuads(linea);
			}
			else
			{
				cout << "Error al leer esta Cara, posible N-Gon detectado\n";
			}
		}
		else if (indice == "usemtl")
		{
			string nombre;
			Caras nuevo_elemento;
			archivo >> nombre;
			nuevo_elemento.usemtl = nombre;
			v_Caras.push_back(nuevo_elemento);
		}
		else if (indice == "mtllib")
		{
			string nombreArchivo;
			archivo >> nombreArchivo;
			LectorMtllib(nombreArchivo);
		}
	}
	archivo.close();
	for (int i = 0; i < newmtl.size(); i++)
	{
		cout << "newmtl -> " << newmtl[i] << endl;
	}
	for (int i = 0; i < map_Kd.size(); i++)
	{
		cout << "map_Kd -> " << map_Kd[i] << endl;
	}
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << "v " << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n";
		i += 2;
	}
	for (int i = 0; i < normales.size(); i++)
	{
		cout << "vn " << normales[i] << " " << normales[i + 1] << " " << normales[i + 2] << "\n";
		i += 2;
	}
	for (int i = 0; i < uvCoords.size(); i++)
	{
		cout << "vt " << uvCoords[i] << " " << uvCoords[i + 1] << " " << uvCoords[i + 2] << "\n";
		i += 2;
	}

	for (int i = 0; i < v_Caras.size(); i++)
	{
		cout << "usemtl -> " << v_Caras[i].usemtl << endl;
		for (int x = 0; x < v_Caras[i].v_ind_normales.size(); x++)
		{
			cout << "f " << v_Caras[i].v_ind_vertices[x] << " " << v_Caras[i].v_ind_uvs[x] << " " << v_Caras[i].v_ind_normales[x] << " "
				<< v_Caras[i].v_ind_vertices[x + 1] << " " << v_Caras[i].v_ind_uvs[x + 1] << " " << v_Caras[i].v_ind_normales[x + 1]
				<< " " << v_Caras[i].v_ind_vertices[x + 2] << " " << v_Caras[i].v_ind_uvs[x + 2] << " "
				<< v_Caras[i].v_ind_normales[x + 2] << "\n";
			x += 2;
		}

	}
}

void archivos_obj::LectorMtllib(string nombre_archivo)
{
	ifstream archivoMtllib(nombre_archivo);
	if (!archivoMtllib.is_open())
	{
		cout << "No se pudo abrir\n";
	}
	else
	{
		cout << "Se abrio\n";
	}
	while (!archivoMtllib.eof())
	{
		string indice;
		archivoMtllib >> indice;
		if (indice == "newmtl")
		{
			string material;
			archivoMtllib >> material;
			newmtl.push_back(material);
		}
		else if (indice == "map_Kd")
		{
			string mapa;
			archivoMtllib >> mapa;
			map_Kd.push_back(mapa);
		}
	}
	archivoMtllib.close();
}

void archivos_obj::LectorGeneral(vector<float>& typeVector, ifstream& archivo)
{
	float posicion;
	int vuelta = 0;
	while (vuelta != 3)
	{
		archivo >> posicion;
		typeVector.push_back(posicion);
		vuelta++;
	}
}

istringstream archivos_obj::LectorCaras(string linea)
{
	istringstream lins(linea);
	int posicion;
	char posicionChar = NULL;
	int vueltas = 0;
	int f_vuelta = 0;

	for (int i = v_Caras.size() - 1; i < v_Caras.size(); i++)
	{
		while (vueltas != 3)
		{
			lins >> posicion;
			v_Caras[i].v_ind_vertices.push_back(posicion);
			lins >> posicionChar;
			lins >> posicion;
			v_Caras[i].v_ind_uvs.push_back(posicion);
			lins >> posicionChar;
			lins >> posicion;
			v_Caras[i].v_ind_normales.push_back(posicion);
			vueltas++;
		}
	}

	return lins;
}

void archivos_obj::LectorCarasQuads(string linea)
{
	int numActual = 0;
	char caracter = NULL;
	istringstream lins = LectorCaras(linea);
	for (int i = v_Caras.size() - 1; i < v_Caras.size(); i++)
	{
		v_Caras[i].v_ind_vertices.push_back(v_Caras[i].v_ind_vertices[v_Caras[i].v_ind_vertices.size() - 1]);
		v_Caras[i].v_ind_uvs.push_back(v_Caras[i].v_ind_uvs[v_Caras[i].v_ind_uvs.size() - 1]);
		v_Caras[i].v_ind_normales.push_back(v_Caras[i].v_ind_normales[v_Caras[i].v_ind_normales.size() - 1]);
		lins >> numActual;
		lins >> caracter;
		v_Caras[i].v_ind_vertices.push_back(numActual);
		lins >> numActual;
		lins >> caracter;
		v_Caras[i].v_ind_uvs.push_back(numActual);
		lins >> numActual;
		v_Caras[i].v_ind_normales.push_back(numActual);
		v_Caras[i].v_ind_vertices.push_back(v_Caras[i].v_ind_vertices[v_Caras[i].v_ind_vertices.size() - 5]);
		v_Caras[i].v_ind_uvs.push_back(v_Caras[i].v_ind_uvs[v_Caras[i].v_ind_uvs.size() - 5]);
		v_Caras[i].v_ind_normales.push_back(v_Caras[i].v_ind_normales[v_Caras[i].v_ind_normales.size() - 5]);
	}
}
