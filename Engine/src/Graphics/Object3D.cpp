#include "Object3D.h"
#include "System.h"


namespace Duat::Graphics {

    Object3D::Object3D(System& gfx) : Object3D(&gfx)
    {
    }

    Object3D::Object3D(System* pGFX) : m_pGFX(pGFX), m_DCIndex(-1), m_GizmoDCIndex(-1)
    {
    }

    Object3D::Object3D(System& gfx, const Geometry::Mesh& mesh, const GraphicsObject& gObj)
        : Object3D(&gfx, mesh, gObj)
    {
    }

    Object3D::Object3D(System* pGFX, const Geometry::Mesh& mesh, const GraphicsObject& gObj)
    {
        m_pGFX = pGFX;
        m_DCIndex = -1;
        m_GizmoDCIndex = -1;
        static_cast<Geometry::Mesh&>(*this) = mesh;
        static_cast<GraphicsObject&>(*this) = gObj;
    }
        
    Geometry::Mesh Object3D::GetMesh() const
    {
        return *this;
    }

    bool Object3D::IsDrawCallEnabled() const
    {
        return m_DCIndex != -1;
    }

    bool Object3D::IsGizmoEnabled() const
    {
        return m_GizmoDCIndex != -1;
    }


    void Object3D::DrawCallEnabled(bool flag)
    {
        if (flag == true && m_DCIndex == -1)
            m_DCIndex = m_pGFX->AddDrawCall(*this);
        else if (flag == false && m_DCIndex != -1)
        {
            m_pGFX->RemoveDrawCall(m_DCIndex);
            m_DCIndex = -1;
        }
    }

    void Object3D::GizmoEnabled(bool flag)
    {
        if (flag == true && m_GizmoDCIndex == -1)
        {
            GraphicsObject restore = *this;
            Geometry::Mesh restoreMesh = *this;
            SetVS("ProjectionGizmo");
            SetPS("ProjectionGizmo");
            SetBS_BlendEnabled(false);
            SetRS_CullMode(Cull::None);
            SetDSS_DepthComparison(Comparison::Always);
            SetTopology(Topology::LineList);

            std::vector<Geometry::Vertex> vertices =
            {
                Geometry::Vertex(0, 0, 0),
                Geometry::Vertex(1, 0, 0),
                Geometry::Vertex(1, 1, 0)
            };

            std::vector<unsigned int> indices = { 0,1,1,2,2,0 };
            SetVertices(vertices);
            SetIndices(indices);

            m_GizmoDCIndex = m_pGFX->AddDrawCall(*this);
            
            static_cast<Geometry::Mesh&>(*this) = restoreMesh;
            static_cast<GraphicsObject&>(*this) = restore;
        }
        else if (flag == false && m_GizmoDCIndex != -1)
        {
            m_pGFX->RemoveDrawCall(m_GizmoDCIndex);
            m_GizmoDCIndex = -1;
        }
    }
}