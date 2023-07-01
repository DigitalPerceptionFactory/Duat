#include "Mesh.h"

namespace Duat::Geometry {

    void Mesh::TestInit()
    {
        Vertex a;
        a.position = { -1,-1,1, 1 };
        a.texCoord.x = 0;
        a.texCoord.y = 0;
        a.color = { 1,0,0, 1 };

        Vertex b;
        b.position = { 0,1,1, 1 };
        b.texCoord.x = 0.5f;
        b.texCoord.y = 1;
        b.color = { 1,0,0, 1 };

        Vertex c;
        c.position = { 1,-1,1, 1 };
        c.texCoord.x = 1;
        c.texCoord.y = 0;
        c.color = { 1,0,0, 1 };

        m_vertices.push_back(a);
        m_vertices.push_back(b);
        m_vertices.push_back(c);

        m_indices = { 0,1,2 };
    }

    const std::vector<Vertex>& Mesh::GetVertices() const
    {
        return m_vertices;
    }

    const std::vector<unsigned int>& Mesh::GetIndices() const
    {
        return m_indices;
    }
        
}