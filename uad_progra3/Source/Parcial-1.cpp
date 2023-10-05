#include "../Include/Parcial-1.h"

obj3D::obj3D()
{

}

obj3D::~obj3D()
{

}

bool obj3D::loadFile(const string& filename)
{
	ifstream archivo(filename);
	if (!archivo.is_open())
	{
		cout << "No se pudo abrir\n";
		return false;
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
			textures = true;
			LectorGeneral(normales, archivo);
		}
		else if (indice == "vt")
		{
			UVcoordsTextures = true;
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
				faces++;
			}
			//Quads
			else if (contador == 4)
			{
				LectorCarasQuads(linea);
				faces++;
				faces++;
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
	
	if (uvCoords.size() == 0)
	{
		uvCoords.push_back(.0f);
		uvCoords.push_back(.0f);
	}

	//Imprime todolo que se guardo
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

	return true;
}

void obj3D::LectorMtllib(string nombre_archivo)
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

void obj3D::LectorGeneral(vector<float>& typeVector, ifstream& archivo)
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

istringstream obj3D::LectorCaras(string linea)
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
			v_Caras[i].v_ind_vertices.push_back(posicion - 1);
			lins >> posicionChar;
			lins >> posicion;
			v_Caras[i].v_ind_uvs.push_back(posicion - 1);
			lins >> posicionChar;
			lins >> posicion;
			v_Caras[i].v_ind_normales.push_back(posicion - 1);
			vueltas++;
		}
	}

	return lins;
}

void obj3D::LectorCarasQuads(string linea)
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
		v_Caras[i].v_ind_vertices.push_back(numActual - 1);
		lins >> numActual;
		lins >> caracter;
		v_Caras[i].v_ind_uvs.push_back(numActual - 1);
		lins >> numActual;
		v_Caras[i].v_ind_normales.push_back(numActual - 1);
		v_Caras[i].v_ind_vertices.push_back(v_Caras[i].v_ind_vertices[v_Caras[i].v_ind_vertices.size() - 5]);
		v_Caras[i].v_ind_uvs.push_back(v_Caras[i].v_ind_uvs[v_Caras[i].v_ind_uvs.size() - 5]);
		v_Caras[i].v_ind_normales.push_back(v_Caras[i].v_ind_normales[v_Caras[i].v_ind_normales.size() - 5]);
	}
}


//////////////////////////////////////////////Funciones Publicas///////////////////////////////////////////


vector<float>* obj3D::getModelVertices()
{
	return &vertices;
}
int obj3D::getNumVertices()
{
	return vertices.size();
}
vector<float>* obj3D::getModelNormals()
{
	return&normales;
}
int obj3D::getNumNormals()
{
	return normales.size();
}
vector<float>* obj3D::getModelUvCoords()
{
	return &uvCoords;
}
int obj3D::getNumUvCoords()
{
	return uvCoords.size();
}
int obj3D::getNumFaces()
{
	return faces;
}
vector<unsigned short>* obj3D::getModelVerticexIndices()
{
	for (int i = 0; i < v_Caras.size(); i++)
	{
		for (int x = 0; x < v_Caras[i].v_ind_vertices.size(); x++)
		{
			Vericextotal.push_back(v_Caras[i].v_ind_vertices[x]);
		}
	}
	return &Vericextotal;
}
vector<unsigned short>* obj3D::getModelNormalsIndices()
{
	
	for (int i = 0; i < v_Caras.size(); i++)
	{
		for (int x = 0; x < v_Caras[i].v_ind_normales.size(); x++)
		{
			Normaltotal.push_back(v_Caras[i].v_ind_normales[x]);
		}
	}
	return &Normaltotal;
}
vector<unsigned short>* obj3D::getModelUvCoordsIndices()
{
	for (int i = 0; i < v_Caras.size(); i++)
	{
		for (int x = 0; x < v_Caras[i].v_ind_uvs.size(); x++)
		{
			UVCoordstotal.push_back(v_Caras[i].v_ind_uvs[x]);
		}
	}
	return &UVCoordstotal;
}

