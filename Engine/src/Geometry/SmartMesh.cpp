#include "SmartMesh.h"


using namespace DirectX;
using namespace Duat::Utility;

namespace Duat::Geometry {

	SmartMesh::SmartMesh()
	{
		auto& sekai = Get();
		sekai.position = sekai.rotation = { 0,0,0 };
		sekai.scale = { 1.0f, 1.0f, 1.0f };
		sekai.posRef = sekai.rotRef = sekai.scaRef = 0;
	}

	int SmartMesh::Create(std::string name,
		DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale,
		DirectX::INT3 posRef, DirectX::INT3 rotRef, DirectX::INT3 scaRef)
	{
		auto& sekai = Get(Hierarchy<SmartVertex>::Create(name));
		sekai.position = position;
		sekai.rotation = rotation;
		sekai.scale = scale;
		sekai.posRef = posRef;
		sekai.rotRef = rotRef;
		sekai.scaRef = scaRef;
		sekai.origin = { 0,0,0 };

		return sekai.index;
	}

	int SmartMesh::CreateAndGo(std::string name, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale, DirectX::INT3 posRef, DirectX::INT3 rotRef, DirectX::INT3 scaRef)
	{
		Create(name, position, rotation, scale, posRef, rotRef, scaRef);
		return Go(name);
	}

	void SmartMesh::CreateCurve(std::function<DirectX::XMFLOAT3(float)> builder_function, Fibre x_axis, Fibre y_axis, Fibre z_axis, AxisMask x_mask, AxisMask y_mask, AxisMask z_mask)
	{
		int longest_axis = x_axis.nodes > y_axis.nodes
			?
			x_axis.nodes > z_axis.nodes ? x_axis.nodes.size() : z_axis.nodes.size()
			:
			y_axis.nodes > z_axis.nodes ? y_axis.nodes.size() : z_axis.nodes.size();

		ring<XMFLOAT3> curve;
		XMFLOAT3 normalizer = { -99999, -99999, -99999 };
		if (longest_axis == 0) longest_axis = 100;
		for (int i = 0; i <= longest_axis; ++i)
		{
			XMFLOAT3 point = builder_function((float)i / (float)longest_axis);
			if (std::abs(point.x) > normalizer.x) normalizer.x = std::abs(point.x);
			if (std::abs(point.y) > normalizer.y) normalizer.y = std::abs(point.y);
			if (std::abs(point.z) > normalizer.z) normalizer.z = std::abs(point.z);
			curve.push_back(point);
		}



		// preventing zero division and fraction division
		if (normalizer.x < 1.0f) normalizer.x = 1.0f;
		if (normalizer.y < 1.0f) normalizer.y = 1.0f;
		if (normalizer.z < 1.0f) normalizer.z = 1.0f;

		if (normalizer.x != 1.0f)
		{
			for (auto& point : curve)
				point.x /= normalizer.x;
		}
		if (normalizer.y != 1.0f)
		{
			for (auto& point : curve)
				point.y /= normalizer.y;
		}
		if (normalizer.z != 1.0f)
		{
			for (auto& point : curve)
				point.z /= normalizer.z;
		}

		ring<XMFLOAT3> deformed_curve;
		normalizer = { -99999, -99999, -99999 };
		for (auto point : curve)
		{
			// IGNORE AXIS DEFORMATION
			//deformed_curve.push_back(point);
			//continue;

			XMFLOAT3 deformed_point = { 0,0,0 };
			// SCALING BY ROOT SIZE AND AXIS MASKING MUST BE ADDED
			if (x_axis.nodes.size() != 0)
			{
				if (point.x >= 0)
					deformed_point += GetPosition(x_axis.nodes[point.x]);
				else
					deformed_point -= GetPosition(x_axis.nodes[std::abs(point.x)]);
			}
			else
				deformed_point += { point.x, 0, 0};
			if (y_axis.nodes.size() != 0)
			{
				if (point.y >= 0)
					deformed_point += GetPosition(y_axis.nodes[point.y]);
				else
					deformed_point -= GetPosition(y_axis.nodes[std::abs(point.y)]);
			}
			else
				deformed_point += { 0, point.y, 0};
			if (z_axis.nodes.size() != 0)
			{
				if (point.z >= 0)
					deformed_point += GetPosition(z_axis.nodes[point.z]);
				else
					deformed_point -= GetPosition(z_axis.nodes[std::abs(point.z)]);
			}
			else
				deformed_point += { 0, 0, point.z};

			if (std::abs(deformed_point.x) > normalizer.x) normalizer.x = std::abs(deformed_point.x);
			if (std::abs(deformed_point.y) > normalizer.y) normalizer.y = std::abs(deformed_point.y);
			if (std::abs(deformed_point.z) > normalizer.z) normalizer.z = std::abs(deformed_point.z);
			deformed_curve.push_back(deformed_point);
		}

		// preventing zero division
		if (normalizer.x == 0) normalizer.x = 1;
		if (normalizer.y == 0) normalizer.y = 1;
		if (normalizer.z == 0) normalizer.z = 1;

		for (auto& point : deformed_curve)
			Create("point", point);

		/*for (int i = 0; i < deformed_curve.size(); ++i)
			Create("Point" + To::String(i), deformed_curve[i] / normalizer,
				{ 0,0,0 }, { 1,1,1 }, { 0,0,0 }, -1, -1, -1);*/
	}

	void SmartMesh::AddPatch(Patch p)
	{
		m_surface.push_back(p);
	}

	Mesh SmartMesh::GetMesh(Topology topology)
	{
		ring<InterpolatedIndex> all_nodes;
		for (auto& patch : m_surface)
		{
			if (patch.GetTopology() != topology) continue;
			auto strips = patch.Get_UV();
			all_nodes.insert(all_nodes.end(), strips.begin(), strips.end());
		}

		std::map<unsigned int, unsigned int> node_to_index;
		ring<Geometry::Vertex> vertices;
		ring<unsigned int> indices;
		int index_counter = 0;
		for (auto& node : all_nodes)
		{
			if (node_to_index.find(node.value) == node_to_index.end())
			{
				node_to_index[node.value] = index_counter;
				++index_counter;
				Vertex vtx(GetPosition(node.value, Setup(0)), node.uv, { 1,1,1,1 });
				vertices.push_back(vtx);
			}
			indices.push_back(node_to_index[node.value]);
		}

		if (topology == Topology::TriangleList)
			Math::CalculateNormals(vertices, indices);

		Mesh out;
		out.SetVertices(vertices);
		out.SetIndices(indices);
		return out;
	}

	void SmartMesh::clamp_360(DirectX::INT3 index)
	{
		float& x = Get(index.x).rotation.x;
		float& y = Get(index.y).rotation.y;
		float& z = Get(index.z).rotation.z;

		for (; std::abs(x) >= 360.0f; x < 0 ? x += 360.0f : x -= 360.0f);
		for (; std::abs(y) >= 360.0f; y < 0 ? y += 360.0f : y -= 360.0f);
		for (; std::abs(z) >= 360.0f; z < 0 ? z += 360.0f : z -= 360.0f);
	}

	DirectX::INT3 SmartMesh::GetPosRef(DirectX::INT3 index)
	{
		resolve_index(index);

		INT3 result = {
			Get(index.x).posRef.x,
			Get(index.y).posRef.y,
			Get(index.z).posRef.z
		};

		if (result.x < 0) result.x = GetParents(index.x)[-1];
		if (result.y < 0) result.y = GetParents(index.y)[-1];
		if (result.z < 0) result.z = GetParents(index.z)[-1];

		return result;
	}

	DirectX::INT3 SmartMesh::GetRotRef(DirectX::INT3 index)
	{
		resolve_index(index);

		INT3 result = {
			Get(index.x).rotRef.x,
			Get(index.y).rotRef.y,
			Get(index.z).rotRef.z
		};

		if (result.x < 0) result.x = GetParents(index.x)[-1];
		if (result.y < 0) result.y = GetParents(index.y)[-1];
		if (result.z < 0) result.z = GetParents(index.z)[-1];

		return result;
	}

	DirectX::INT3 SmartMesh::GetScaRef(DirectX::INT3 index)
	{
		resolve_index(index);

		INT3 result = {
			Get(index.x).scaRef.x,
			Get(index.y).scaRef.y,
			Get(index.z).scaRef.z
		};

		if (result.x < 0) result.x = GetParents(index.x)[-1];
		if (result.y < 0) result.y = GetParents(index.y)[-1];
		if (result.z < 0) result.z = GetParents(index.z)[-1];

		return result;
	}

	DirectX::XMFLOAT3 SmartMesh::GetPosition(DirectX::INT3 index, Setup setup)
	{
		/*
			in both cases we place vector in ref world
			however in GET the vector already exists and is the subtraction of origins

		set:
			We must operate on global metrics to be reliable
			We construct vector according to globalized setup references
			Such global vector we insert into index' parent world space (parent=ref)
			We do so because "index" is actually what we move, instead of where it happens [parent]
			Insertion is done via dividing vector subtraction by index' parent global scale
			and reverse rotation to "cancel" rotation applied by parent world
		*/

		resolve_all(index, setup);

		if (index == setup.posRef || GetPosRef(index) == setup.posRef)
		{
			XMFLOAT3 result = {
				Get(index.x).position.x,
				Get(index.y).position.y,
				Get(index.z).position.z
			};
			return result;
		}

		// global metrics
		XMFLOAT3 idx_pos = get_global_position(index);
		XMFLOAT3 ref_pos = get_global_position(setup.posRef);
		XMFLOAT3 ref_rot = get_global_rotation(setup.rotRef);
		XMFLOAT3 ref_sca = get_global_scale(setup.scaRef);

		// construct vec
		XMFLOAT3 vec = idx_pos - ref_pos;
		if (!setup.is_signed.x) vec.x = (vec.x - ref_sca.x) / 2 * ref_sca.x;
		else vec.x *= ref_sca.x;
		if (!setup.is_signed.y) vec.y = (vec.y - ref_sca.y) / 2 * ref_sca.y;
		else vec.y *= ref_sca.y;
		if (!setup.is_signed.z) vec.z = (vec.z - ref_sca.z) / 2 * ref_sca.z;
		else vec.z *= ref_sca.z;


		// insert vec into ref space
		return XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			setup.is_clockwise ? ref_rot * -1 : ref_rot
		)
		);
	}

	DirectX::XMFLOAT3 SmartMesh::GetPosition(DirectX::XMFLOAT3 point, Setup setup)
	{
		resolve_reference(0, setup);
		// global metrics
		XMFLOAT3 idx_pos = point;
		XMFLOAT3 ref_pos = get_global_position(setup.posRef);
		XMFLOAT3 ref_rot = get_global_rotation(setup.rotRef);
		XMFLOAT3 ref_sca = get_global_scale(setup.scaRef);

		// construct vec
		XMFLOAT3 vec = idx_pos - ref_pos;
		if (!setup.is_signed.x) vec.x = (vec.x - ref_sca.x) / 2 * ref_sca.x;
		else vec.x /= ref_sca.x;
		if (!setup.is_signed.y) vec.y = (vec.y - ref_sca.y) / 2 * ref_sca.y;
		else vec.y /= ref_sca.y;
		if (!setup.is_signed.z) vec.z = (vec.z - ref_sca.z) / 2 * ref_sca.z;
		else vec.z /= ref_sca.z;


		// insert vec into ref space
		return XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			setup.is_clockwise ? ref_rot * -1 : ref_rot
		)
		);
	}

	DirectX::XMFLOAT2 SmartMesh::GetPosition(DirectX::XMFLOAT2 point, Setup setup)
	{
		resolve_reference(0, setup);
		// global metrics
		XMFLOAT3 idx_pos = { point.x, point.y,0.0f };
		XMFLOAT3 ref_pos = get_global_position(setup.posRef);
		XMFLOAT3 ref_rot = get_global_rotation(setup.rotRef);
		XMFLOAT3 ref_sca = get_global_scale(setup.scaRef);

		// construct vec
		XMFLOAT3 vec = idx_pos - ref_pos;
		if (!setup.is_signed.x) vec.x = (vec.x - ref_sca.x) / 2 * ref_sca.x;
		else vec.x /= ref_sca.x;
		if (!setup.is_signed.y) vec.y = (vec.y - ref_sca.y) / 2 * ref_sca.y;
		else vec.y /= ref_sca.y;


		// insert vec into ref space
		vec = XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			setup.is_clockwise ? ref_rot * -1 : ref_rot
		)
		);
		return { vec.x,vec.y };
	}

	DirectX::XMFLOAT3 SmartMesh::GetRotation(DirectX::INT3 index, Setup setup)
	{
		resolve_all(index, setup);

		if ((index == setup.rotRef) == true)
		{
			return {
				Get(index.x).rotation.x,
				Get(index.y).rotation.y,
				Get(index.z).rotation.z
			};
		}

		// relative rotation
		XMFLOAT3 result = get_global_rotation(index) - get_global_rotation(setup.rotRef);

		if (!setup.is_clockwise.x) result.x = 360.0f - result.x;
		if (!setup.is_clockwise.y) result.y = 360.0f - result.y;
		if (!setup.is_clockwise.z) result.z = 360.0f - result.z;

		// "clamp" to 360 deg max
		for (; std::abs(result.x) >= 360.0f; result.x < 0 ? result.x += 360.0f : result.x -= 360.0f);
		for (; std::abs(result.y) >= 360.0f; result.y < 0 ? result.y += 360.0f : result.y -= 360.0f);
		for (; std::abs(result.z) >= 360.0f; result.z < 0 ? result.z += 360.0f : result.z -= 360.0f);

		return result;
	}

	DirectX::XMFLOAT3 SmartMesh::GetScale(DirectX::INT3 index, Setup setup)
	{
		resolve_all(index, setup);

		if ((index == setup.scaRef) == true)
		{
			return {
				Get(index.x).rotation.x,
				Get(index.y).rotation.y,
				Get(index.z).rotation.z
			};
		}

		// relative scale
		return get_global_scale(index) / get_global_scale(setup.scaRef);
	}

	Cube<float> SmartMesh::GetExceed(DirectX::INT3 index, Setup setup)
	{
		resolve_all(index, setup);

		XMFLOAT3 boundary = get_global_boundary(index, index);
		XMFLOAT3 ref_boundary = get_global_boundary(setup.rotRef, setup.scaRef);

		//XMFLOAT3 shifted_positive = GetOriginPosition(index, Setup(0)) + boundary;
		//XMFLOAT3 shifted_negative = GetOriginPosition(index, Setup(0)) - boundary;
		//XMFLOAT3 ref_shifted_positive = GetOriginPosition(setup.posRef, Setup(0)) + ref_boundary;
		//XMFLOAT3 ref_shifted_negative = GetOriginPosition(setup.posRef, Setup(0)) - ref_boundary;

		XMFLOAT3 shifted_positive = get_global_position(index) + boundary;
		XMFLOAT3 shifted_negative = get_global_position(index) - boundary;
		XMFLOAT3 ref_shifted_positive = get_global_position(setup.posRef) + ref_boundary;
		XMFLOAT3 ref_shifted_negative = get_global_position(setup.posRef) - ref_boundary;

		Cube<float> result;
		result.top = shifted_positive.y - ref_shifted_positive.y;
		result.right = shifted_positive.x - ref_shifted_positive.x;
		result.back = shifted_positive.z - ref_shifted_positive.z;
		result.bottom = ref_shifted_negative.y - shifted_negative.y;
		result.left = ref_shifted_negative.x - shifted_negative.x;
		result.front = ref_shifted_negative.z - shifted_negative.z;

		if (!setup.is_signed.x)
		{
			result.left += ref_boundary.x;
			result.right += ref_boundary.x;
		}
		if (!setup.is_signed.y)
		{
			result.top += ref_boundary.y;
			result.bottom += ref_boundary.y;
		}
		if (!setup.is_signed.z)
		{
			result.front += ref_boundary.z;
			result.back += ref_boundary.z;
		}

		if (!setup.is_lefthanded.x)
		{
			result.left *= -1;
			result.right *= -1;
		}
		if (!setup.is_lefthanded.y)
		{
			result.top *= -1;
			result.bottom *= -1;
		}
		if (!setup.is_lefthanded.z)
		{
			result.front *= -1;
			result.back *= -1;
		}

		return result;
	}

	Cube<float> SmartMesh::GetExceed(DirectX::XMFLOAT3 point, Setup setup)
	{
		// to prevent negative setup values
		resolve_reference(0, setup);
		XMFLOAT3 ref_boundary = get_global_boundary(setup.rotRef, setup.scaRef);

		XMFLOAT3 shifted_positive = point;
		XMFLOAT3 shifted_negative = point;
		XMFLOAT3 ref_shifted_positive = get_global_position(setup.posRef) + ref_boundary;
		XMFLOAT3 ref_shifted_negative = get_global_position(setup.posRef) - ref_boundary;

		Cube<float> result;
		result.top = shifted_positive.y - ref_shifted_positive.y;
		result.right = shifted_positive.x - ref_shifted_positive.x;
		result.back = shifted_positive.z - ref_shifted_positive.z;
		result.bottom = ref_shifted_negative.y - shifted_negative.y;
		result.left = ref_shifted_negative.x - shifted_negative.x;
		result.front = ref_shifted_negative.z - shifted_negative.z;

		if (!setup.is_signed.x)
		{
			result.left += ref_boundary.x;
			result.right += ref_boundary.x;
		}
		if (!setup.is_signed.y)
		{
			result.top += ref_boundary.y;
			result.bottom += ref_boundary.y;
		}
		if (!setup.is_signed.z)
		{
			result.front += ref_boundary.z;
			result.back += ref_boundary.z;
		}

		if (!setup.is_lefthanded.x)
		{
			result.left *= -1;
			result.right *= -1;
		}
		if (!setup.is_lefthanded.y)
		{
			result.top *= -1;
			result.bottom *= -1;
		}
		if (!setup.is_lefthanded.z)
		{
			result.front *= -1;
			result.back *= -1;
		}

		return result;
	}

	Cube<float> SmartMesh::GetExceed(DirectX::XMFLOAT2 point, Setup setup)
	{
		// to prevent negative setup values
		resolve_reference(0, setup);
		XMFLOAT3 ref_boundary = get_global_boundary(setup.rotRef, setup.scaRef);

		XMFLOAT3 shifted_positive = { point.x, point.y, 0.0f };
		XMFLOAT3 shifted_negative = { point.x, point.y, 0.0f };
		XMFLOAT3 ref_shifted_positive = get_global_position(setup.posRef) + ref_boundary;
		XMFLOAT3 ref_shifted_negative = get_global_position(setup.posRef) - ref_boundary;

		Cube<float> result;
		result.top = shifted_positive.y - ref_shifted_positive.y;
		result.right = shifted_positive.x - ref_shifted_positive.x;
		result.back = 0.0f;
		result.bottom = ref_shifted_negative.y - shifted_negative.y;
		result.left = ref_shifted_negative.x - shifted_negative.x;
		result.front = 0.0f;

		if (!setup.is_signed.x)
		{
			result.left += ref_boundary.x;
			result.right += ref_boundary.x;
		}
		if (!setup.is_signed.y)
		{
			result.top += ref_boundary.y;
			result.bottom += ref_boundary.y;
		}

		if (!setup.is_lefthanded.x)
		{
			result.left *= -1;
			result.right *= -1;
		}
		if (!setup.is_lefthanded.y)
		{
			result.top *= -1;
			result.bottom *= -1;
		}

		return result;
	}

	bool SmartMesh::Contains(DirectX::INT3 index, Setup setup)
	{
		Cube<float> exc = GetExceed(index, setup);

		if (
			exc.left <= 0 && exc.right <= 0 &&
			exc.top <= 0 && exc.bottom <= 0 &&
			exc.front <= 0 && exc.back <= 0
			)
			return true;

		return false;
	}

	bool SmartMesh::Contains(DirectX::XMFLOAT3 point, Setup setup)
	{
		Cube<float> exc = GetExceed(point, setup);

		if (
			exc.left <= 0 && exc.right <= 0 &&
			exc.top <= 0 && exc.bottom <= 0 &&
			exc.front <= 0 && exc.back <= 0
			)
			return true;

		return false;
	}

	bool SmartMesh::Contains(DirectX::XMFLOAT2 point, Setup setup)
	{
		Cube<float> exc = GetExceed(point, setup);

		if (
			exc.left <= 0 && exc.right <= 0 &&
			exc.top <= 0 && exc.bottom <= 0 &&
			exc.front <= 0 && exc.back <= 0
			)
			return true;

		return false;
	}

	DirectX::XMFLOAT3 SmartMesh::GetOrigin(DirectX::INT3 index)
	{
		resolve_index(index);
		return {
			Get(index.x).origin.x,
			Get(index.y).origin.y,
			Get(index.z).origin.z
		};
	}

	DirectX::XMFLOAT3 SmartMesh::GetOriginPosition(DirectX::INT3 index, Setup setup)
	{
		resolve_all(index, setup);
		XMFLOAT3 result = GetPosition(index, setup);
		result -= GetOrigin(index) * get_global_scale(index) / get_global_scale(setup.scaRef);
		return result;
	}

	DirectX::XMMATRIX SmartMesh::GetMatrix()
	{
		return GetMatrix(GetIndex());
	}

	DirectX::XMMATRIX SmartMesh::GetMatrix(DirectX::INT3 index)
	{
		resolve_index(index);
		XMMATRIX result = XMMatrixIdentity();
		result *= XMMatrixScaling(get_global_scale(index));
		result *= XMMatrixRotationRollPitchYawDegrees(get_global_rotation(index));
		result *= XMMatrixTranslation(get_global_position(index));
		//result *= XMMatrixTranslation(GetOriginPosition(index, Setup(0)));
		return result;
	}

	DirectX::INT3 SmartMesh::SetAllRef(DirectX::INT3 ref, DirectX::INT3 index)
	{
		SetPosRef(ref, index);
		SetRotRef(ref, index);
		SetScaRef(ref, index);
		return index;
	}

	DirectX::INT3 SmartMesh::SetPosRef(DirectX::INT3 ref, DirectX::INT3 index)
	{
		resolve_index(index);

		Get(index.x).posRef.x = ref.x;
		Get(index.y).posRef.y = ref.y;
		Get(index.z).posRef.z = ref.z;

		return index;

	}

	DirectX::INT3 SmartMesh::SetRotRef(DirectX::INT3 ref, DirectX::INT3 index)
	{
		resolve_index(index);

		Get(index.x).rotRef.x = ref.x;
		Get(index.y).rotRef.y = ref.y;
		Get(index.z).rotRef.z = ref.z;

		return index;
	}

	DirectX::INT3 SmartMesh::SetScaRef(DirectX::INT3 ref, DirectX::INT3 index)
	{
		resolve_index(index);

		Get(index.x).scaRef.x = ref.x;
		Get(index.y).scaRef.y = ref.y;
		Get(index.z).scaRef.z = ref.z;

		return index;
	}

	DirectX::INT3 SmartMesh::SetPosition(DirectX::XMFLOAT3 pos, Setup setup, DirectX::INT3 index)
	{
		/*
			in both cases we place vector in ref world
			however in GET the vector already exists and is the subtraction of origins

		set:
			We must operate on global metrics to be reliable
			We construct vector according to globalized setup references
			Such global vector we insert into index' parent world space (parent=ref)
			We do so because "index" is actually what we move, instead of where it happens [parent]
			Insertion is done via dividing vector subtraction by index' parent global scale
			and reverse rotation to "cancel" rotation applied by parent world
		*/

		resolve_all(index, setup);

		// global metrics
		XMFLOAT3 idx_parent_pos = get_global_position(GetPosRef(index));
		XMFLOAT3 idx_parent_rot = get_global_rotation(GetRotRef(index));
		XMFLOAT3 idx_parent_sca = get_global_scale(GetScaRef(index));
		XMFLOAT3 ref_pos = get_global_position(setup.posRef);
		XMFLOAT3 ref_rot = get_global_rotation(setup.rotRef);
		XMFLOAT3 ref_sca = get_global_scale(setup.scaRef);

		// construct vec
		XMFLOAT3 vec;
		if (!setup.is_signed.x) vec.x = (pos.x + ref_sca.x) * 0.5f * ref_sca.x;
		else vec.x = pos.x * ref_sca.x;
		if (!setup.is_signed.y) vec.y = (pos.y + ref_sca.y) * 0.5f * ref_sca.y;
		else vec.y = pos.y * ref_sca.y;
		if (!setup.is_signed.z) vec.z = (pos.z + ref_sca.z) * 0.5f * ref_sca.z;
		else vec.z = pos.z * ref_sca.z;

		if (!setup.is_lefthanded.x) vec.x *= -1;
		if (!setup.is_lefthanded.y) vec.y *= -1;
		if (!setup.is_lefthanded.z) vec.z *= -1;

		// apply rotation
		vec = XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			setup.is_clockwise ? ref_rot * -1 : ref_rot
		)
		);

		// result is vec from idx_parent (origin) to final position
		vec = (vec + ref_pos) - idx_parent_pos;

		// insert into index' parent space
		// since vec size is currently in ref scale we need to multiply by idx/ref
		vec /= idx_parent_sca;
		// cancel rotation
		vec = XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			idx_parent_rot * -1
		)
		);

		Get(index.x).position.x = vec.x;
		Get(index.y).position.y = vec.y;
		Get(index.z).position.z = vec.z;
		return index;
	}

	DirectX::INT3 SmartMesh::SetRotation(DirectX::XMFLOAT3 rot, Setup setup, DirectX::INT3 index)
	{
		resolve_index(index);
		rot -= GetRotation(index, setup); // WHY ? ? ? difference?

		// if counter-clockwise
		if (!setup.is_clockwise.x) rot.x = 360.0f - rot.x;
		if (!setup.is_clockwise.y) rot.y = 360.0f - rot.y;
		if (!setup.is_clockwise.z) rot.z = 360.0f - rot.z;

		Get(index.x).rotation.x = rot.x;
		Get(index.y).rotation.y = rot.y;
		Get(index.z).rotation.z = rot.z;
		clamp_360(index);

		return index;
	}

	DirectX::INT3 SmartMesh::SetScale(DirectX::XMFLOAT3 scale, Setup setup, DirectX::INT3 index)
	{
		if (scale.x == 0.0f) scale.x = 1.0f;
		if (scale.y == 0.0f) scale.y = 1.0f;
		if (scale.z == 0.0f) scale.z = 1.0f;

		resolve_index(index);
		if (setup.is_signed.x)
			Get(index.x).scale.x = scale.x;
		else
			Get(index.x).scale.x = scale.x * 2;
		if (setup.is_signed.y)
			Get(index.y).scale.y = scale.y;
		else
			Get(index.y).scale.y = scale.y * 2;
		if (setup.is_signed.z)
			Get(index.z).scale.z = scale.z;
		else
			Get(index.z).scale.z = scale.z * 2;
		return index;
	}

	DirectX::INT3 SmartMesh::SetOrigin(DirectX::XMFLOAT3 origin, DirectX::INT3 index)
	{
		resolve_index(index);
		Get(index.x).origin.x = origin.x;
		Get(index.y).origin.y = origin.y;
		Get(index.z).origin.z = origin.z;
		return index;
	}


	DirectX::INT3 SmartMesh::Translate(DirectX::XMFLOAT3 pos, Setup setup, DirectX::INT3 index)
	{
		resolve_all(index, setup);

		// global metrics
		XMFLOAT3 idx_parent_pos = get_global_position(GetPosRef(index));
		XMFLOAT3 idx_parent_rot = get_global_rotation(GetRotRef(index));
		XMFLOAT3 idx_parent_sca = get_global_scale(GetScaRef(index));
		XMFLOAT3 ref_pos = get_global_position(setup.posRef);
		XMFLOAT3 ref_rot = get_global_rotation(setup.rotRef);
		XMFLOAT3 ref_sca = get_global_scale(setup.scaRef);

		// construct vec
		XMFLOAT3 vec;
		if (!setup.is_signed.x) vec.x = (pos.x + ref_sca.x) * 0.5f * ref_sca.x;
		else vec.x = pos.x * ref_sca.x;
		if (!setup.is_signed.y) vec.y = (pos.y + ref_sca.y) * 0.5f * ref_sca.y;
		else vec.y = pos.y * ref_sca.y;
		if (!setup.is_signed.z) vec.z = (pos.z + ref_sca.z) * 0.5f * ref_sca.z;
		else vec.z = pos.z * ref_sca.z;

		if (!setup.is_lefthanded.x) vec.x *= -1;
		if (!setup.is_lefthanded.y) vec.y *= -1;
		if (!setup.is_lefthanded.z) vec.z *= -1;

		// apply rotation
		vec = XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			setup.is_clockwise ? ref_rot * -1 : ref_rot
		)
		);

		// result is vec from idx_parent (origin) to final position
		vec = (vec + ref_pos) - idx_parent_pos;

		// insert into index' parent space
		vec *= idx_parent_sca;
		// cancel rotation
		vec = XMFloat3Transform(vec, XMMatrixRotationRollPitchYawDegrees
		(
			idx_parent_rot * -1
		)
		);

		Get(index.x).position.x += vec.x;
		Get(index.y).position.y += vec.y;
		Get(index.z).position.z += vec.z;
		return index;
	}

	DirectX::INT3 SmartMesh::Rotate(DirectX::XMFLOAT3 rot, Setup setup, DirectX::INT3 index)
	{
		resolve_index(index);
		rot -= GetRotation(index, setup); // WHY ? ? ? difference?

		// if counter-clockwise
		if (!setup.is_clockwise.x) rot.x = 360.0f - rot.x;
		if (!setup.is_clockwise.y) rot.y = 360.0f - rot.y;
		if (!setup.is_clockwise.z) rot.z = 360.0f - rot.z;

		Get(index.x).rotation.x += rot.x;
		Get(index.y).rotation.y += rot.y;
		Get(index.z).rotation.z += rot.z;
		clamp_360(index);

		return index;
	}

	DirectX::INT3 SmartMesh::Scale(DirectX::XMFLOAT3 sca, Setup setup, DirectX::INT3 index)
	{
		resolve_index(index);
		if (setup.is_signed.x)
			Get(index.x).scale.x += sca.x;
		else
			Get(index.x).scale.x += sca.x * 2;
		if (setup.is_signed.y)
			Get(index.y).scale.y += sca.y;
		else
			Get(index.y).scale.y += sca.y * 2;
		if (setup.is_signed.z)
			Get(index.z).scale.z += sca.z;
		else
			Get(index.z).scale.z += sca.z * 2;
		return index;
	}

	DirectX::INT3 SmartMesh::Fit(DirectX::INT3 index)
	{
		Cube<float> exc = GetExceed(index);

		auto& sekai_x = Get(index.x);
		sekai_x.scale.x -= (exc.left + exc.right) / 2;
		sekai_x.position.x += exc.left / 2;
		sekai_x.position.x -= exc.right / 2;

		auto& sekai_y = Get(index.y);
		sekai_y.scale.y -= (exc.top + exc.bottom) / 2;
		sekai_y.position.y += exc.bottom / 2;
		sekai_y.position.y -= exc.top / 2;

		auto& sekai_z = Get(index.z);
		sekai_z.scale.z -= (exc.front + exc.back) / 2;
		sekai_z.position.z += exc.front / 2;
		sekai_z.position.z -= exc.back / 2;

		return index;
	}

	Patch::Patch(Topology t)
	{
		topology = t;
	}

	Patch::Patch(Fibre begin, Fibre end, Topology t)
	{
		topology = t;
		AddStrip(begin, end);
	}

	ring<unsigned int> Patch::Get()
	{
		ring<unsigned int> result;
		for (auto& strip : strips)
			for (auto& index : strip)
				result.push_back(index.value);
		return result;
	}

	ring<InterpolatedIndex> Patch::Get_UV()
	{
		ring<InterpolatedIndex> result;
		for (auto& strip : strips)
			result.insert(result.end(), strip.begin(), strip.end());
		return result;
	}

	int Patch::AddStrip(Fibre begin, Fibre end)
	{
		int b_size = begin.nodes.size();
		int e_size = end.nodes.size();
		Fibre* from = b_size <= e_size ? &begin : &end;
		Fibre* to = &begin == from ? &end : &begin;
		int size_difference = to->nodes.size() - from->nodes.size();

		ring<unsigned int> values;
		ring<XMFLOAT2> uvs;
#define ugly_verytemp_neveragain_macro_FROM uvs.push_back({ 0.0f, (float)i / (float)(from->nodes.size() - 1) });
#define ugly_verytemp_neveragain_macro_TO uvs.push_back({ 1.0f, (float)i / (float)(to->nodes.size() - 1) });

		switch (topology)
		{
		case Topology::TriangleList:
			if (b_size == 0 || e_size == 0 || b_size + e_size < 3)
				m_result << "Invalid paramaters for TriangleList.";

			for (int i = 0; i < from->nodes.size() - 1; ++i)
			{
				values.push_back(from->nodes[i]);
				values.push_back(to->nodes[i]);
				values.push_back(to->nodes[i + 1]);

				values.push_back(from->nodes[i]);
				values.push_back(to->nodes[i + 1]);
				values.push_back(from->nodes[i + 1]);

				ugly_verytemp_neveragain_macro_FROM
					ugly_verytemp_neveragain_macro_TO
					ugly_verytemp_neveragain_macro_TO
					ugly_verytemp_neveragain_macro_FROM
					ugly_verytemp_neveragain_macro_TO
					ugly_verytemp_neveragain_macro_FROM
			}
			for (int i = 0; i < size_difference - 1; ++i)
			{
				values.push_back(from->nodes[-1]);
				values.push_back(to->nodes[i]);
				values.push_back(to->nodes[i + 1]);

				ugly_verytemp_neveragain_macro_FROM
					ugly_verytemp_neveragain_macro_TO
					ugly_verytemp_neveragain_macro_TO
			}
			break;
		case Topology::LineList:
			if (b_size < 2)
				m_result << "Invalid paramaters for LineList.";

			for (int i = 0; i < b_size - 1; ++i)
			{
				values.push_back(begin.nodes[i]);
				values.push_back(begin.nodes[i + 1]);
			}
			break;
		case Topology::PointList:
			if (b_size == 0)
				m_result << "Invalid paramaters for PointList.";

			for (int i = 0; i < b_size; ++i)
				values.push_back(begin.nodes[i]);
			for (int i = 0; i < e_size; ++i)
				values.push_back(end.nodes[i]);
			break;
		}

		ring<InterpolatedIndex> strip;
		if (topology == Topology::TriangleList)
		{
			for (int i = 0; i < values.size(); ++i)
			{
				InterpolatedIndex index;
				index.value = values[i];
				index.uv = uvs[i];
				strip.push_back(index);
			}
		}
		else
		{
			for (int i = 0; i < values.size(); ++i)
			{
				InterpolatedIndex index;
				index.value = values[i];
				strip.push_back(index);
			}
		}

		strips.push_back(strip);
		return strips.size() - 1;
	}

	void Patch::DeleteStrip(int at)
	{
		strips.erase(at);
	}

	ring<InterpolatedIndex> Patch::GetStrip(int at)
	{
		return strips[at];
	}

	ring<InterpolatedIndex> Patch::GetStripByHandle(int handle)
	{
		return strips.get(handle);
	}

	Topology Patch::GetTopology()
	{
		return topology;
	}

	Topology Patch::SetTopology(Topology t)
	{
		topology = t;
		return t;
	}

	void Fibre::Append(Hierarchy<SmartVertex>& cone, unsigned int node_index, float from, float to, Fibre::Type type)
	{
		switch (type)
		{
		case Fibre::Type::Children:
		{
			auto children = cone.GetChildren(node_index);
			for (int i = from * children.size(); i < to * children.size(); ++i)
				nodes.push_back(children[i]);

			break;
		}
		case Fibre::Type::Siblings:
		{
			auto siblings = cone.GetChildren(cone.Get(node_index).parents[-1]);
			int position = 0;
			for (int i = 0; i < siblings.size(); ++i)
				if (siblings[i] == node_index) break;
				else ++position;

			for (int i = position + from * siblings.size(); i < position + to * siblings.size(); ++i)
				nodes.push_back(siblings[i]);

			break;
		}
		case Fibre::Type::Parents:
		{
			auto parents = cone.GetParents(node_index);
			for (int i = from * parents.size(); i < to * parents.size(); ++i)
				nodes.push_back(parents[-i - 1]);

			break;
		}
		case Fibre::Type::Peer:
		{
			ring<int> peers;
			generate_peers_rec(cone, peers, cone.GetParents(node_index).size(), 0);

			int position = 0;
			for (int i = 0; i < peers.size(); ++i)
				if (peers[i] == node_index) break;
				else ++position;

			for (int i = position + from * peers.size(); i < position + to * peers.size(); ++i)
				nodes.push_back(peers[i]);

			break;
		}
		}
	}

	void Fibre::Init(Hierarchy<SmartVertex>& cone, unsigned int node_index, float from, float to, Fibre::Type type)
	{
		nodes.clear();
		Append(cone, node_index, from, to, type);
	}

	void Fibre::generate_peers_rec(Hierarchy<SmartVertex>& cone, ring<int>& peers, int parent_count, int index)
	{
		if (cone.GetParents(index).size() == parent_count)
			peers.push_back(index);
		if (cone.GetParents(index).size() < parent_count)
			for (auto& child : cone.GetChildren(index))
				generate_peers_rec(cone, peers, parent_count, child);
		return;
	}


	DirectX::XMFLOAT3 SmartMesh::get_global_position(DirectX::INT3 index)
	{
		resolve_index(index);
		XMFLOAT3 result = { 0,0,0 };
		INT3 ref = 0;

		// parent worlds' global scale & rotation

		if (index.x != 0)
		{
			auto& sekai_x = Get(index.x);

			XMFLOAT3 x_scale = get_global_scale(GetScaRef(index.x));
			XMFLOAT3 x_rotation = get_global_rotation(GetRotRef(index.x));

			result.x = XMFloat3Transform(
				x_scale * sekai_x.position,
				XMMatrixRotationRollPitchYawDegrees(x_rotation)
			).x - get_global_scale(index.x).x * sekai_x.origin.x;


			ref.x = GetPosRef(index.x).x;
		}

		if (index.y != 0)
		{
			auto& sekai_y = Get(index.y);

			XMFLOAT3 y_scale = get_global_scale(GetScaRef(index.y));
			XMFLOAT3 y_rotation = get_global_rotation(GetRotRef(index.y));

			result.y = XMFloat3Transform(
				y_scale * sekai_y.position,
				XMMatrixRotationRollPitchYawDegrees(y_rotation)
			).y - get_global_scale(index.y).y * sekai_y.origin.y;

			ref.y = GetPosRef(index.y).y;
		}

		if (index.z != 0)
		{
			auto& sekai_z = Get(index.z);

			XMFLOAT3 z_scale = get_global_scale(GetScaRef(index.z));
			XMFLOAT3 z_rotation = get_global_rotation(GetRotRef(index.z));

			result.z = XMFloat3Transform(
				z_scale * sekai_z.position,
				XMMatrixRotationRollPitchYawDegrees(z_rotation)
			).z - get_global_scale(index.z).z * sekai_z.origin.z;

			ref.z = GetPosRef(index.z).z;
		}

		if (ref == 0) return result;
		else return result + get_global_position(ref);
	}

	DirectX::XMFLOAT3 SmartMesh::get_global_rotation(DirectX::INT3 index)
	{
		resolve_index(index);
		XMFLOAT3 result;
		result.x = Get(index.x).rotation.x;
		result.y = Get(index.y).rotation.y;
		result.z = Get(index.z).rotation.z;
		INT3 ref;
		ref.x = GetRotRef(index.x).x;
		ref.y = GetRotRef(index.y).y;
		ref.z = GetRotRef(index.z).z;
		if (ref == 0) return result;
		else return result + get_global_rotation(ref);
	}

	DirectX::XMFLOAT3 SmartMesh::get_global_scale(DirectX::INT3 index)
	{
		resolve_index(index);
		XMFLOAT3 result;
		result.x = Get(index.x).scale.x;
		result.y = Get(index.y).scale.y;
		result.z = Get(index.z).scale.z;
		INT3 ref;
		ref.x = GetScaRef(index.x).x;
		ref.y = GetScaRef(index.y).y;
		ref.z = GetScaRef(index.z).z;
		if (ref == 0) return result;
		else return result * get_global_scale(ref);
	}

	DirectX::XMFLOAT3 SmartMesh::get_global_boundary(DirectX::INT3 rotRef, DirectX::INT3 scaRef)
	{
		XMFLOAT3 half_scale = get_global_scale(scaRef);
		XMFLOAT3 rotation = get_global_rotation(rotRef);
		XMFLOAT3 rotated_half_scale = XMFloat3Transform(
			half_scale,
			XMMatrixRotationRollPitchYawDegrees(rotation)
		);
		XMFLOAT3 delta_scale = rotated_half_scale - half_scale;
		return half_scale + XMFloat3Abs(delta_scale);
	}

	void SmartMesh::resolve_index(DirectX::INT3& index)
	{
		if (index.x < 0) index.x = GetIndex();
		if (index.y < 0) index.y = GetIndex();
		if (index.z < 0) index.z = GetIndex();
	}

	void SmartMesh::resolve_reference(DirectX::INT3 index, Setup& setup)
	{
		resolve_index(index);

		// resolve pos
		INT3 ref = GetPosRef(index);
		if (setup.posRef.x < 0) setup.posRef.x = ref.x;
		if (setup.posRef.y < 0) setup.posRef.y = ref.y;
		if (setup.posRef.z < 0) setup.posRef.z = ref.z;

		// resolve rot
		ref = GetRotRef(index);
		if (setup.rotRef.x < 0) setup.rotRef.x = ref.x;
		if (setup.rotRef.y < 0) setup.rotRef.y = ref.y;
		if (setup.rotRef.z < 0) setup.rotRef.z = ref.z;

		// resolve sca
		ref = GetScaRef(index);
		if (setup.scaRef.x < 0) setup.scaRef.x = ref.x;
		if (setup.scaRef.y < 0) setup.scaRef.y = ref.y;
		if (setup.scaRef.z < 0) setup.scaRef.z = ref.z;
	}

	void SmartMesh::resolve_pos_reference(DirectX::INT3 index, DirectX::INT3& posRef)
	{
		resolve_index(index);
		INT3 ref = GetPosRef(index);
		if (posRef.x < 0) posRef.x = ref.x;
		if (posRef.y < 0) posRef.y = ref.y;
		if (posRef.z < 0) posRef.z = ref.z;
	}

	void SmartMesh::resolve_rot_reference(DirectX::INT3 index, DirectX::INT3& rotRef)
	{
		resolve_index(index);
		INT3 ref = GetRotRef(index);
		if (rotRef.x < 0) rotRef.x = ref.x;
		if (rotRef.y < 0) rotRef.y = ref.y;
		if (rotRef.z < 0) rotRef.z = ref.z;
	}

	void SmartMesh::resolve_sca_reference(DirectX::INT3 index, DirectX::INT3& scaRef)
	{
		resolve_index(index);
		INT3 ref = GetScaRef(index);
		if (scaRef.x < 0) scaRef.x = ref.x;
		if (scaRef.y < 0) scaRef.y = ref.y;
		if (scaRef.z < 0) scaRef.z = ref.z;
	}

	void SmartMesh::resolve_all(DirectX::INT3& index, Setup& setup)
	{
		// resolve index
		if (index.x < 0) index.x = GetIndex();
		if (index.y < 0) index.y = GetIndex();
		if (index.z < 0) index.z = GetIndex();

		// resolve pos
		INT3 ref = GetPosRef(index);
		if (setup.posRef.x < 0) setup.posRef.x = ref.x;
		if (setup.posRef.y < 0) setup.posRef.y = ref.y;
		if (setup.posRef.z < 0) setup.posRef.z = ref.z;

		// resolve rot
		ref = GetRotRef(index);
		if (setup.rotRef.x < 0) setup.rotRef.x = ref.x;
		if (setup.rotRef.y < 0) setup.rotRef.y = ref.y;
		if (setup.rotRef.z < 0) setup.rotRef.z = ref.z;

		// resolve sca
		ref = GetScaRef(index);
		if (setup.scaRef.x < 0) setup.scaRef.x = ref.x;
		if (setup.scaRef.y < 0) setup.scaRef.y = ref.y;
		if (setup.scaRef.z < 0) setup.scaRef.z = ref.z;
	}

}