#include "HLSLBuffer.h"

#define HLSL_EXPAND \
   HLSL_EVALUATE(Int)\
   HLSL_EVALUATE(Int2)\
   HLSL_EVALUATE(Int3)\
   HLSL_EVALUATE(Int4)\
   HLSL_EVALUATE(Float)\
   HLSL_EVALUATE(Float2)\
   HLSL_EVALUATE(Float3)\
   HLSL_EVALUATE(Float4)\
   HLSL_EVALUATE(Bool)\
   HLSL_EVALUATE(Bool2)\
   HLSL_EVALUATE(Bool3)\
   HLSL_EVALUATE(Bool4)\
   HLSL_EVALUATE(Matrix)

namespace Duat::Utility::HLSL {

#define ARRAY_END ((char)(Type::Invalid) + 1)
#define STRUCT_END ((char)(Type::Invalid) + 2)

	Struct::Struct(const std::vector<Assign>& rhs) {
		elements.resize(rhs.size());
		for (int i = 0; i < rhs.size(); ++i)
			elements[i] = rhs[i];
	}

	Struct::Struct(const Struct& rhs)
	{
		elements = rhs.elements;
	}

	Struct::Struct(Struct&& rhs) noexcept
	{
		elements = std::move(rhs.elements);
	}

	Struct& Struct::operator=(const Struct& rhs) 
	{
		elements = rhs.elements; return *this; 
	}

	Struct& Struct::operator=(Struct&& rhs) noexcept 
	{ 
		elements = std::move(rhs.elements); return *this;
	}



	Array::Array(const std::vector<Assign>& rhs)
	{
		elements.resize(rhs.size());
		if (rhs.size() == 0) return;

		if (rhs[0].m_label != "") elements[0].m_label = rhs[0].m_label;
		elements[0].m_value = rhs[0].m_value;
		elements[0].m_type = rhs[0].m_type;
		for (int i = 1; i < rhs.size(); ++i)
		{
			if (CompatibilityCheck(elements[0].m_value, rhs[i].m_value, rhs[i].m_loc, i))
			{
				if (rhs[i].m_label != "") elements[i].m_label = rhs[i].m_label;
				elements[i].m_value = rhs[i].m_value;
				elements[i].m_type = rhs[i].m_type;
			}
			else
			{
				elements[i] = Element();
			}
		}
	}

	Array::Array(const Array& rhs)
	{ 
		elements = rhs.elements; 
	}

	Array::Array(Array&& rhs) noexcept 
	{ 
		elements = std::move(rhs.elements); 
	}

	Array& Array::operator=(const Array& rhs)
	{
		elements = rhs.elements; return *this; 
	}

	Array& Array::operator=(Array&& rhs) noexcept 
	{
		elements = std::move(rhs.elements); return *this; 
	}

	Type Array::GetArrayType() const
	{ 
		return elements.size() > 0 ? elements[0].m_type : Type::Invalid; 
	}

	std::string Array::GetArrayTypeString() const
	{
		if (elements.size() > 0)
		{
			auto sign = GetSignatureRec(elements[0].m_value);
			if (sign.size() == 1) return TypeToString(elements[0].m_type);
			else return SignatureToString(sign);
		}
		else return "";
	}
		
	HLSLDataType InitializeHLSLDataType(Type type)
	{
#define HLSL_EVALUATE(x) else if(type == Type::x) { static Meta<Type::x>::TrueType var; return var; }
		if (type == Type::Struct) return Struct();
		else if (type == Type::Array) return Array();
		HLSL_EXPAND
		return Empty();
#undef HLSL_EVALUATE
	}

	Type GetTypeFromValue(const HLSLDataType& value) {
#define HLSL_EVALUATE(x) else if (std::holds_alternative<Meta<Type::x>::TrueType>(value)) { return Type::x; }
		if (std::holds_alternative<Struct>(value)) return Type::Struct;
		else if (std::holds_alternative<Array>(value)) return Type::Array;
		HLSL_EXPAND
			return Type::Invalid;
#undef HLSL_EVALUATE
	}

	std::vector<char> GetSignatureRec(const HLSLDataType& value) 
	{
#define HLSL_EVALUATE(x) else if (std::holds_alternative<Meta<Type::x>::TrueType>(value)) { out.push_back((char)Type::x); }
		std::vector<char> out;
		if (std::holds_alternative<Struct>(value)) {
			Struct str = std::get<Struct>(value);
			out.push_back((char)Type::Struct);
			for (const auto& e : str.elements)
			{
				std::vector<char> temp = GetSignatureRec(e.GetValue());
				out.insert(out.end(), temp.begin(), temp.end());
			}
			out.push_back(STRUCT_END);
		}
		else if (std::holds_alternative<Array>(value)) {
			const Array& arr = std::get<Array>(value);
			out.push_back((char)Type::Array);
			for (const auto& e : arr.elements)
			{
				std::vector<char> temp = GetSignatureRec(e.GetValue());
				out.insert(out.end(), temp.begin(), temp.end());
			}
			out.push_back(ARRAY_END);
		}
		HLSL_EXPAND
#undef HLSL_EVALUATE
		return out;
	}

	bool CompatibilityCheck(const HLSLDataType& a, const HLSLDataType& b, std::source_location loc, int index) 
	{
		auto a_sign = GetSignatureRec(a);
		auto b_sign = GetSignatureRec(b);
		size_t cmp_size = a_sign.size() >= b_sign.size() ? a_sign.size() : b_sign.size();
		bool compatible = !((bool)(std::memcmp(a_sign.data(), b_sign.data(), cmp_size)));

		if (!compatible)
		{
			Result result;
			std::string note = "\nNote: once the buffer is created you cannot change variable types, you can only edit their values.";
			if (GetTypeFromValue(a) == Type::Struct && GetTypeFromValue(b) == Type::Struct)
			{
				if (index != -1)
				{
					result << Error("Signature missmatch for element [" + std::to_string(index) +
						"].\nArray Type: Struct" + SignatureToString(a_sign) + "\nInvalid Type: Struct" +
						SignatureToString(b_sign) + note, loc
					);
				}
				else
				{
					result << Error("Signature missmatch.\nStruct A : " + SignatureToString(a_sign) +
						"\n\nStruct B:" + SignatureToString(b_sign) + note, loc);
				}
			}
			else if (GetTypeFromValue(a) == Type::Array && GetTypeFromValue(b) == Type::Array)
			{
				const Array& a_arr = std::get<Array>(a);
				const Array& b_arr = std::get<Array>(b);
				if (index != -1)
				{
					result << Error("Signature missmatch for element [" + std::to_string(index) +
						"].\nArray Type: Array" + a_arr.GetArrayTypeString() + "\nInvalid Type: Array" +
						b_arr.GetArrayTypeString() + note, loc
					);
				}
				else
				{
					result << Error("Signature missmatch.\nArray A: " + a_arr.GetArrayTypeString() +
						"\nArray B: " + b_arr.GetArrayTypeString() + note, loc);
				}
			}
			else
			{
				if (index != -1)
				{
					result << Error("Signature missmatch for element [" + std::to_string(index) +
						"].\nArray Type: " + TypeToString(GetTypeFromValue(a)) + "\nInvalid Type: " +
						TypeToString(GetTypeFromValue(b)) + note, loc
					);
				}
				else
				{
					result << Error("Signature missmatch.\nVariable A: " + TypeToString(GetTypeFromValue(a)) +
						"\nVariable B: " + TypeToString(GetTypeFromValue(b)) + note, loc);
				}
			}
		}
		return compatible;
	}

	void AssignRec(Element& lhs, Assign rhs) 
	{
		if (rhs.GetType() == Type::Struct)
		{
			Struct& str = std::get<Struct>(rhs.GetValue());
			for (int i = 0; i < str.elements.size(); ++i)
				AssignRec(lhs[Index(i, rhs.GetLocation())], Assign(str.elements[i].GetValue(), rhs.GetLocation()));
		}
		else if (rhs.GetType() == Type::Array)
		{
			Array& arr = std::get<Array>(rhs.GetValue());
			for (int i = 0; i < arr.elements.size(); ++i)
				AssignRec(lhs[Index(i, rhs.GetLocation())], Assign(arr.elements[i].GetValue(), rhs.GetLocation()));
		}
		else
		{
			lhs.m_value = rhs.GetValue();
		}
	}

#define HLSL_EVALUATE(x) Assign::Assign(const Meta<Type::x>::TrueType& value, std::source_location loc) \
	{ \
		m_type = Type::x; \
		m_value = value; \
		m_loc = loc; \
	}
	HLSL_EXPAND
#undef HLSL_EVALUATE

	Assign::Assign(const HLSLDataType& value, std::source_location loc)
	{
		m_type = GetTypeFromValue(value);
		m_value = value;
		m_loc = loc;
	}

	Assign::Assign(const Struct& value, std::source_location loc)
	{
		m_type = Type::Struct;
		m_value = value;
		m_loc = loc;
	}

	Assign::Assign(const Array& value, std::source_location loc)
	{
		m_type = Type::Array;
		m_value = value;
		m_loc = loc;
	}

	std::string Assign::GetLabel() const
	{
		return m_label;
	}

	Type Assign::GetType() const
	{
		return m_type;
	}

	std::source_location Assign::GetLocation() const
	{
		return m_loc;
	}

	HLSLDataType& Assign::GetValue()
	{
		return m_value;
	}

	const HLSLDataType& Assign::GetValue() const
	{
		return m_value;
	}

	Label::Label(const std::string& label, std::source_location loc) : value(label), loc(std::move(loc)) 
	{
	}

	Label::Label(const char* label, std::source_location loc) : value(label), loc(std::move(loc)) 
	{
	}

	Index::Index(size_t index, std::source_location loc) : value(index), loc(std::move(loc)) 
	{
	}

	Element::Element(const std::string& label, Type type)
	{
		m_label = label;
		m_type = type;
		m_value = InitializeHLSLDataType(type);
	}

#define HLSL_EVALUATE(x) \
		Element::Element(const std::string& label, const Meta<Type::x>::TrueType& var) { \
				m_type = Type::x; \
				m_value = var; \
				m_label = label; \
			}
	HLSL_EXPAND
#undef HLSL_EVALUATE

	Element::Element(const std::string& label, const Struct& var) 
	{
		m_type = Type::Struct;
		m_value = var;
		m_label = label;
	}

	Element::Element(const std::string& label, const Array& var) 
	{
		m_type = Type::Array;
		m_value = var;
		m_label = label;
	}

	Element::Element(const std::string& label, const Error& err) 
	{
		m_type = Type::Error;
		m_label = label;
		m_value = err;
	}

	Element& Element::Rename(const std::string& label) 
	{
		m_label = label;
		return *this;
	}

	Element& Element::operator=(const Assign& rhs) {
		if (m_buf)
		{
			if (CompatibilityCheck(m_value, rhs.m_value, rhs.m_loc))
			{
				AssignRec(*this, rhs);
				EmplaceRec(*this);
			}
		}
		else
		{
			if (rhs.m_label != "") m_label = rhs.m_label;
			m_type = rhs.m_type;
			m_value = rhs.m_value;
		}
		return *this;
	}

	Element& Element::operator[](Label label) 
	{
		if (m_type == Type::Struct)
		{
			Struct& str = std::get<Struct>(m_value);
			for (auto& e : str.elements)
				if (e.GetLabel() == label.value)
					return e;

			if (!m_buf)
			{
				str.elements.push_back(Element(label.value, Type::Empty));
				return str.elements[str.elements.size() - 1];
			}
		}
		else if (m_type == Type::Array)
		{
			Array& arr = std::get<Array>(m_value);
			for (auto& e : arr.elements)
				if (e.GetLabel() == label.value)
					return e;

			if (!m_buf)
			{
				arr.elements.push_back(Element(label.value, arr.elements.size() == 0 ?
					Type::Empty : arr.elements[0].GetType()));
				return arr.elements[arr.elements.size() - 1];
			}
		}
		else
		{
			Error err("Element \"" + m_label + "\" is neither Struct nor Array, so it doesn't have field\"" +
				label.value + "\" or any other fields.", label.loc);
			m_result << err;
		}

		Error err("The " + TypeToString(m_type) + " \"" + m_label + "\" doesn't have field named \"" + label.value +
			"\".\nNote: once Buffer is constructed you cannot expand Structures and Arrays anymore, you can only edit their values.",
			label.loc);
		m_result << err;
		return *this;
	}

	Element& Element::operator[](Index index) 
	{
		if (m_type == Type::Struct)
		{
			Struct& str = std::get<Struct>(m_value);
			if (index.value < str.elements.size())
			{
				return str.elements[index.value];
			}
			else if (!m_buf)
			{
				str.elements.resize(index.value + 1);
				return str.elements[index.value];
			}
		}
		else if (m_type == Type::Array)
		{
			Array& arr = std::get<Array>(m_value);
			if (index.value < arr.elements.size())
			{
				return arr.elements[index.value];
			}
			else if (!m_buf)
			{
				arr.elements.resize(index.value + 1, arr.elements.size() == 0 ?
					Element("", Type::Empty) : Element("", arr.elements[0].GetType()));
				return arr.elements[index.value];
			}
		}
		else
		{
			Error err("Element \"" + m_label +
				"\" is neither Struct nor Array, so it is impossible to access members using index operator", index.loc);
			m_result << err;
		}

		Error err("Index [" + std::to_string(index.value) + "] exceeds "
			+ TypeToString(m_type) + " \"" + m_label + "\" length. " +
			"\nNote: once Buffer is constructed you cannot expand Structures and Arrays anymore, you can only edit their values.",
			index.loc);
		m_result << err;
		return *this;
	}

	Type Element::GetType() const
	{
		return m_type; 
	}

	std::string Element::GetLabel() const
	{ 
		return m_label; 
	}

	HLSLDataType Element::GetValue()
	{ 
		return m_value;
	}

	const HLSLDataType& Element::GetValue() const
	{
		return m_value; 
	}

	char* Element::GetBuf()
	{ 
		return m_buf; 
	}

	size_t Element::GetOffset() const 
	{ 
		return m_offset; 
	}

}
#undef HLSL_EXPAND