#include "Object3D.h"
#include "System.h"


namespace Duat::Graphics {
    void Object3D::SetProjectionGizmo(bool flag)
    {
        if (flag == true && m_projectionGizmo == -1)
        {
            GraphicsObject restore = *this;
            vs = "ProjectionGizmo";
            ps = "ProjectionGizmo";
            bs = "Disabled";
            rs = "Expensive";
            dss = "Always";
            tp = Topology::LineList;

            std::vector<Geometry::Vertex> vertices =
            {
                Geometry::Vertex(0, 0, 0),
                Geometry::Vertex(1, 0, 0),
                Geometry::Vertex(1, 1, 0)
            };

            std::vector<unsigned int> indices = { 0,1,1,2,2,0 };
            mesh.SetVertices(vertices);
            mesh.SetIndices(indices);

            m_projectionGizmo = m_pGFX->AddDrawCall(*this);
            this->vs = restore.vs;
            this->ps = restore.ps;
            this->bs = restore.bs;
            this->rs = restore.rs;
            this->dss = restore.dss;
            this->tp = restore.tp;
            this->mesh = restore.mesh;
        }
        else if (flag == false && m_projectionGizmo != -1)
        {
            m_pGFX->RemoveDrawCall(m_projectionGizmo);
            m_projectionGizmo = -1;
        }
    }
}