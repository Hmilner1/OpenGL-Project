#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include "Structures.h"

using namespace std;

namespace MeshLoader
{
    //created the relivant functions 
    void LoadVertices(ifstream& inFile, Mesh& mesh);
    void LoadNormals(ifstream& inFile, Mesh& mesh);
    void LoadIndices(ifstream& inFile, Mesh& mesh);
    void LoadTexCoords(ifstream& inFile, Mesh& mesh);

    //loads in the verticies from the file read to be used 
    void LoadVertices(ifstream& inFile, Mesh& mesh)
    {
        inFile >> mesh.VertexCount;
        //if there is any verticies it will add them to a array
        if (mesh.VertexCount > 0)
        {
            mesh.Vertices = new Vertex[mesh.VertexCount];

            for (int i = 0; i < mesh.VertexCount; i++)
            {
                inFile >> mesh.Vertices[i].x;
                inFile >> mesh.Vertices[i].y;
                inFile >> mesh.Vertices[i].z;
            }
        }
    }
    //loads in the normals from the file read to be used 
    void LoadNormals(ifstream& inFile, Mesh& mesh)
    {
        inFile >> mesh.NormalCount;
        //if there is any normals it will add them to a array
        mesh.Normals = new Vector3[mesh.NormalCount];
        for (int i = 0; i < mesh.NormalCount; i++)
        {
            inFile >> mesh.Normals[i].x;
            inFile >> mesh.Normals[i].y;
            inFile >> mesh.Normals[i].z;
        }
    }
    //loads in the texture cord from the file read to be used 
    void LoadTexCoords(ifstream& inFile, Mesh& mesh)
    {
        inFile >> mesh.TexCoordCount;
        //if there is any texture cord it will add them to a array
        mesh.TexCoords = new TexCoord[mesh.TexCoordCount];
        for (int i = 0; i < mesh.TexCoordCount; i++)
        {
            inFile >> mesh.TexCoords[i].u;
            inFile >> mesh.TexCoords[i].v;
        }
    }
    //loads in the indices from the file read to be used 
    void LoadIndices(ifstream& inFile, Mesh& mesh)
    {
        inFile >> mesh.IndexCount;
        //if there is any indices it will add them to a array
        mesh.Indices = new GLushort[mesh.IndexCount];
        for (int i = 0; i < mesh.IndexCount; i++)
        {
            inFile >> mesh.Indices[i];
        }
    }
    //load function allowing meshes to be loaded in using data  
    Mesh* MeshLoader::Load(char* path)
    {
        Mesh* mesh = new Mesh();

        ifstream inFile;

        inFile.open(path);

        if (!inFile.good())
        {
            cerr << "Can't open texture file " << path << endl;
            return nullptr;
        }
        //calls the functions and passes them to the mesh loader
        LoadVertices(inFile, *mesh);
        LoadTexCoords(inFile, *mesh);
        LoadNormals(inFile, *mesh);
        LoadIndices(inFile, *mesh);

        return mesh;
    }
}