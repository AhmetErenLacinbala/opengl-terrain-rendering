#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string.h>

#include "terrain.h"

//#define DEBUG_PRINT



void BaseTerrain::InitTerrain(float WorldScale)
{
    if (!m_terrainTech.Init()) {
        printf("Error initializing tech\n");
        exit(0);
    }

    m_worldScale = WorldScale;
}


void BaseTerrain::LoadFromFile(const char* pFilename)
{
    printf("loadfine start \n");
    LoadHeightMapFile(pFilename);

    m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);
    printf("loadfile end \n");
}


void BaseTerrain::LoadHeightMapFile(const char* pFilename)
{
    int FileSize = 0;
    unsigned char* p = (unsigned char*)ReadBinaryFile(pFilename, FileSize);

    if (FileSize % sizeof(float) != 0) {
        printf("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, pFilename, FileSize);
        exit(0);
    }

    m_terrainSize = (int)sqrtf((float)FileSize / (float)sizeof(float));

    printf("Terrain size %d\n", m_terrainSize);

    if ((m_terrainSize * m_terrainSize) != (FileSize / sizeof(float))) {
        printf("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, pFilename, FileSize);
        exit(0);
    }

    m_heightMap.InitArray2D(m_terrainSize, m_terrainSize, (float*)p);
}

void BaseTerrain::Render(const BasicCamera& globalCamera) {
    printf("base Terrain render start\n");
    Render(globalCamera);
    printf("base terreain render end\n");
}

float BaseTerrain::GetHeight(int x, int z) const {
    return m_heightMap.Get(x, z);
}

float BaseTerrain::GetWorldScale() const {
    return m_worldScale;
}
