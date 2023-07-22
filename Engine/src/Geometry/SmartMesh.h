#pragma once
#include <Utility/Classes.h>
#include <functional>
#include <map>
#include "Mesh.h"
#include "Useful.h"
#include "SmartVertex.h"


namespace Duat::Geometry {
		
	struct Setup {
		Setup() : is_signed(true), is_lefthanded(true), is_clockwise(true),
			posRef(-1), rotRef(-1), scaRef(-1) {}
		Setup(DirectX::INT3 ref) : is_signed(true), is_lefthanded(true), is_clockwise(true),
			posRef(ref), rotRef(ref), scaRef(ref) {}
		Setup(DirectX::INT3 posRef, DirectX::INT3 rotRef, DirectX::INT3 scaRef) :
			is_signed(true), is_lefthanded(true), is_clockwise(true),
			posRef(posRef), rotRef(rotRef), scaRef(scaRef) {}

		DirectX::BOOL3 is_signed;
		DirectX::BOOL3 is_lefthanded;
		DirectX::BOOL3 is_clockwise;
		DirectX::INT3 posRef;
		DirectX::INT3 rotRef;
		DirectX::INT3 scaRef;
	};

	enum class AxisMask
	{
		None, XYZ, X, Y, Z, XY, XZ, YZ
	};

	struct Fibre
	{
		enum class Type {
			Children, Parents, Siblings, Peer
		};

		Fibre() = default;
		Fibre(Utility::Hierarchy<SmartVertex>& cone, unsigned int node_index, float from = 0.0f, float to = 1.0f,
			Fibre::Type type = Fibre::Type::Children)
		{
			Init(cone, node_index, from, to, type);
		}

		void Append(Utility::Hierarchy<SmartVertex>& cone, unsigned int node_index, float from, float to, Fibre::Type type);
		void Init(Utility::Hierarchy<SmartVertex>& cone, unsigned int node_index, float from, float to, Fibre::Type type);
		Utility::ring<unsigned int> nodes;
	private:
		void generate_peers_rec(Utility::Hierarchy<SmartVertex>& cone, Utility::ring<int>& peers, int parent_count, int index);
	};

	struct Patch
	{
		Patch() = default;
		Patch(Topology t);
		Patch(Fibre begin, Fibre end, Topology t = Topology::TriangleList);
		Utility::ring<unsigned int> Get();
		Utility::ring<InterpolatedIndex> Get_UV();

		// each strip is pretty much patch already
		// splitting patch into multiple strips just allows more flexibility
		int AddStrip(Fibre begin, Fibre end = {});
		void DeleteStrip(int at);
		Utility::ring<InterpolatedIndex> GetStrip(int at);
		Utility::ring<InterpolatedIndex> GetStripByHandle(int handle);
		Topology GetTopology();
		Topology SetTopology(Topology t);
	private:
		Utility::Result m_result;
		Topology topology = Topology::TriangleList;
		Utility::ring<Utility::ring<InterpolatedIndex>> strips;
	};

	struct SmartMesh : public Utility::Hierarchy<SmartVertex> {
		SmartMesh();

		int Create(std::string name,
			DirectX::XMFLOAT3 position = { 0,0,0 },
			DirectX::XMFLOAT3 rotation = { 0,0,0 },
			DirectX::XMFLOAT3 scale = { 1,1,1 },
			DirectX::INT3 posRef = {-1,-1,-1},
			DirectX::INT3 rotRef = {-1,-1,-1},
			DirectX::INT3 scaRef = {-1,-1,-1}
		);
		int CreateAndGo(std::string name,
			DirectX::XMFLOAT3 position = { 0,0,0 },
			DirectX::XMFLOAT3 rotation = { 0,0,0 },
			DirectX::XMFLOAT3 scale = { 1,1,1 },
			DirectX::INT3 posRef = { -1,-1,-1 },
			DirectX::INT3 rotRef = { -1,-1,-1 },
			DirectX::INT3 scaRef = { -1,-1,-1 }
		);

		void CreateCurve(
			std::function<DirectX::XMFLOAT3(float)> builder_function,
			Fibre x_axis = Fibre(), Fibre y_axis = Fibre(), Fibre z_axis = Fibre(),
			AxisMask x_mask = AxisMask::None, 
			AxisMask y_mask = AxisMask::None, 
			AxisMask z_mask = AxisMask::None
		);

		void AddPatch(Patch p);
		Mesh GetMesh(Topology topology = Topology::TriangleList);

		// create curve
		// create spiral

		// if Refs are negative default to nearest parent, otherwise index must be specified
		// if index is negative default to current position

		DirectX::INT3 GetPosRef(DirectX::INT3 index = -1);
		DirectX::INT3 GetRotRef(DirectX::INT3 index = -1);
		DirectX::INT3 GetScaRef(DirectX::INT3 index = -1);
		DirectX::XMFLOAT3 GetPosition(DirectX::INT3 index = -1, Setup setup = Setup());
		DirectX::XMFLOAT3 GetPosition(DirectX::XMFLOAT3 point, Setup setup);
		DirectX::XMFLOAT2 GetPosition(DirectX::XMFLOAT2 point, Setup setup);
		DirectX::XMFLOAT3 GetRotation(DirectX::INT3 index = -1, Setup setup = Setup());
		DirectX::XMFLOAT3 GetScale(DirectX::INT3 index = -1, Setup setup = Setup());
		DirectX::XMMATRIX GetMatrix();
		DirectX::XMMATRIX GetMatrix(DirectX::INT3 index);
		Cube<float> GetExceed(DirectX::INT3 index = -1, Setup setup = Setup());
		Cube<float> GetExceed(DirectX::XMFLOAT3 point, Setup setup = Setup());
		Cube<float> GetExceed(DirectX::XMFLOAT2 point, Setup setup = Setup());
		DirectX::XMFLOAT3 GetOrigin(DirectX::INT3 index = -1);
		DirectX::XMFLOAT3 GetOriginPosition(DirectX::INT3 index = -1, Setup setup = Setup());
		bool Contains(DirectX::INT3 index, Setup setup);
		bool Contains(DirectX::XMFLOAT3 point, Setup setup);
		bool Contains(DirectX::XMFLOAT2 point, Setup setup);

		DirectX::INT3 SetAllRef(DirectX::INT3 ref, DirectX::INT3 index = -1);
		DirectX::INT3 SetPosRef(DirectX::INT3 ref, DirectX::INT3 index = -1);
		DirectX::INT3 SetRotRef(DirectX::INT3 ref, DirectX::INT3 index = -1);
		DirectX::INT3 SetScaRef(DirectX::INT3 ref, DirectX::INT3 index = -1);
		DirectX::INT3 SetPosition(DirectX::XMFLOAT3 pos, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 SetRotation(DirectX::XMFLOAT3 rot, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 SetScale(DirectX::XMFLOAT3 scale, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 SetOrigin(DirectX::XMFLOAT3 origin, DirectX::INT3 index = -1);
		DirectX::INT3 Translate(DirectX::XMFLOAT3 pos, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 Rotate(DirectX::XMFLOAT3 rot, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 Scale(DirectX::XMFLOAT3 sca, Setup setup = Setup(), DirectX::INT3 index = -1);
		DirectX::INT3 Fit(DirectX::INT3 index = -1);

		// fibre is made of nodes
		// strip is made of threads
		// patch is made of strips
				

	private:
		Utility::Result m_result;

		DirectX::XMFLOAT3 get_global_position(DirectX::INT3 index);
		DirectX::XMFLOAT3 get_global_rotation(DirectX::INT3 index);
		DirectX::XMFLOAT3 get_global_scale(DirectX::INT3 index);
		DirectX::XMFLOAT3 get_global_boundary(DirectX::INT3 rotRef, DirectX::INT3 scaRef);
		void resolve_index(DirectX::INT3& index);
		void resolve_reference(DirectX::INT3 index, Setup& setup);
		void resolve_pos_reference(DirectX::INT3 index, DirectX::INT3& posRef);
		void resolve_rot_reference(DirectX::INT3 index, DirectX::INT3& rotRef);
		void resolve_sca_reference(DirectX::INT3 index, DirectX::INT3& scaRef);
		void resolve_all(DirectX::INT3& index, Setup& setup);
		void clamp_360(DirectX::INT3 index);

		Utility::ring<Patch> m_surface;
	};

}