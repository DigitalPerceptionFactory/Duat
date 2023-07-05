#pragma once
#include <string>
#include <vector>
#include <variant>
#include <DirectXMath.h>
#include "DX_INT2.h"
#include "DX_INT3.h"
#include "DX_INT4.h"
#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"
#include <Utility/ErrorHandling/Error.h>
#include <Utility/ErrorHandling/Result.h>

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

#define HLSL_EXPAND_PTR \
   HLSL_EVALUATE(IntPtr)\
   HLSL_EVALUATE(Int2Ptr)\
   HLSL_EVALUATE(Int3Ptr)\
   HLSL_EVALUATE(Int4Ptr)\
   HLSL_EVALUATE(FloatPtr)\
   HLSL_EVALUATE(Float2Ptr)\
   HLSL_EVALUATE(Float3Ptr)\
   HLSL_EVALUATE(Float4Ptr)\
   HLSL_EVALUATE(BoolPtr)\
   HLSL_EVALUATE(Bool2Ptr)\
   HLSL_EVALUATE(Bool3Ptr)\
   HLSL_EVALUATE(Bool4Ptr)\
   HLSL_EVALUATE(MatrixPtr)

#define ARRAY_END ((char)(Type::Invalid) + 1)
#define STRUCT_END ((char)(Type::Invalid) + 2)

namespace Duat::Utility::HLSL {

	struct Element;
	struct Struct;
	struct Array;
	struct Assign;
	struct Index;
	struct Label;
	struct Buffer;
	struct Layout;
	struct Empty {};

	enum class Type {
#define HLSL_EVALUATE(x) x,
		HLSL_EXPAND
		HLSL_EXPAND_PTR
#undef HLSL_EVALUATE
		Struct, Array, Empty, Error, Invalid
	};

	template<Type T>
	struct Meta {
		static constexpr Type type = Type::Invalid;
	};
	template<> struct Meta<Type::Int> {
		using TrueType = int;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Int;
		static constexpr char signature[] = "i1";
	};
	template<> struct Meta<Type::Int2> {
		using TrueType = DirectX::INT2;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Int2;
		static constexpr char signature[] = "i2";
	};
	template<> struct Meta<Type::Int3> {
		using TrueType = DirectX::INT3;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Int3;
		static constexpr char signature[] = "i3";
	};
	template<> struct Meta<Type::Int4> {
		using TrueType = DirectX::INT4;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Int4;
		static constexpr char signature[] = "i4";
	};
	template<> struct Meta<Type::Bool> {
		using TrueType = bool;
		static constexpr size_t padding = 3;
		static constexpr Type type = Type::Bool;
		static constexpr char signature[] = "b1";
	};
	template<> struct Meta<Type::Bool2> {
		using TrueType = DirectX::BOOL2;
		static constexpr size_t padding = 2;
		static constexpr Type type = Type::Bool2;
		static constexpr char signature[] = "b2";
	};
	template<> struct Meta<Type::Bool3> {
		using TrueType = DirectX::BOOL3;
		static constexpr size_t padding = 1;
		static constexpr Type type = Type::Bool3;
		static constexpr char signature[] = "b3";
	};
	template<> struct Meta<Type::Bool4> {
		using TrueType = DirectX::BOOL4;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Bool4;
		static constexpr char signature[] = "b4";
	};
	template<> struct Meta<Type::Float> {
		using TrueType = float;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Float;
		static constexpr char signature[] = "f1";
	};
	template<> struct Meta<Type::Float2> {
		using TrueType = DirectX::XMFLOAT2;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Float2;
		static constexpr char signature[] = "f2";
	};
	template<> struct Meta<Type::Float3> {
		using TrueType = DirectX::XMFLOAT3;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Float3;
		static constexpr char signature[] = "f3";
	};
	template<> struct Meta<Type::Float4> {
		using TrueType = DirectX::XMFLOAT4;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Float4;
		static constexpr char signature[] = "f4";
	};
	template<> struct Meta<Type::Matrix> {
		using TrueType = DirectX::XMMATRIX;
		static constexpr size_t padding = 16 % sizeof(TrueType);
		static constexpr Type type = Type::Matrix;
		static constexpr char signature[] = "m";
	};
	template<> struct Meta<Type::Struct> {
		using TrueType = Struct;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Struct;
		static constexpr char signature[] = "s";
	};
	template<> struct Meta<Type::Array> {
		using TrueType = Array;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Array;
		static constexpr char signature[] = "a";
	};

	template<> struct Meta<Type::IntPtr> {
		using TrueType = int*;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::IntPtr;
		static constexpr char signature[] = "pi1";
	};
	template<> struct Meta<Type::Int2Ptr> {
		using TrueType = DirectX::INT2*;
		static constexpr size_t padding = 16 % sizeof(DirectX::INT2);
		static constexpr Type type = Type::Int2Ptr;
		static constexpr char signature[] = "pi2";
	};
	template<> struct Meta<Type::Int3Ptr> {
		using TrueType = DirectX::INT3*;
		static constexpr size_t padding = 16 % sizeof(DirectX::INT3);
		static constexpr Type type = Type::Int3Ptr;
		static constexpr char signature[] = "pi3";
	};
	template<> struct Meta<Type::Int4Ptr> {
		using TrueType = DirectX::INT4*;
		static constexpr size_t padding = 16 % sizeof(DirectX::INT4);
		static constexpr Type type = Type::Int4Ptr;
		static constexpr char signature[] = "pi4";
	};
	template<> struct Meta<Type::BoolPtr> {
		using TrueType = bool*;
		static constexpr size_t padding = 3;
		static constexpr Type type = Type::BoolPtr;
		static constexpr char signature[] = "pb1";
	};
	template<> struct Meta<Type::Bool2Ptr> {
		using TrueType = DirectX::BOOL2*;
		static constexpr size_t padding = 2;
		static constexpr Type type = Type::Bool2Ptr;
		static constexpr char signature[] = "pb2";
	};
	template<> struct Meta<Type::Bool3Ptr> {
		using TrueType = DirectX::BOOL3*;
		static constexpr size_t padding = 1;
		static constexpr Type type = Type::Bool3Ptr;
		static constexpr char signature[] = "pb3";
	};
	template<> struct Meta<Type::Bool4Ptr> {
		using TrueType = DirectX::BOOL4*;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::Bool4Ptr;
		static constexpr char signature[] = "pb4";
	};
	template<> struct Meta<Type::FloatPtr> {
		using TrueType = float*;
		static constexpr size_t padding = 0;
		static constexpr Type type = Type::FloatPtr;
		static constexpr char signature[] = "pf1";
	};
	template<> struct Meta<Type::Float2Ptr> {
		using TrueType = DirectX::XMFLOAT2*;
		static constexpr size_t padding = 16 % sizeof(DirectX::XMFLOAT2);
		static constexpr Type type = Type::Float2Ptr;
		static constexpr char signature[] = "pf2";
	};
	template<> struct Meta<Type::Float3Ptr> {
		using TrueType = DirectX::XMFLOAT3*;
		static constexpr size_t padding = 16 % sizeof(DirectX::XMFLOAT3);
		static constexpr Type type = Type::Float3Ptr;
		static constexpr char signature[] = "pf3";
	};
	template<> struct Meta<Type::Float4Ptr> {
		using TrueType = DirectX::XMFLOAT4*;
		static constexpr size_t padding = 16 % sizeof(DirectX::XMFLOAT4);
		static constexpr Type type = Type::Float4Ptr;
		static constexpr char signature[] = "pf4";
	};
	template<> struct Meta<Type::MatrixPtr> {
		using TrueType = DirectX::XMMATRIX*;
		static constexpr size_t padding = 16 % sizeof(DirectX::XMMATRIX);
		static constexpr Type type = Type::MatrixPtr;
		static constexpr char signature[] = "pm";
	};

#define HLSL_EVALUATE(x) Meta<Type::x>::TrueType,
	typedef std::variant<HLSL_EXPAND HLSL_EXPAND_PTR Struct, Array, Empty, Error> HLSLDataType;
#undef HLSL_EVALUATE
	
	static std::string TypeToString(Type t)
	{
#define HLSL_EVALUATE(x) case Type::x: return #x;
		switch (t)
		{
			HLSL_EXPAND
			HLSL_EXPAND_PTR
		case Type::Struct: return "Struct";
		case Type::Array: return "Array";
		case Type::Empty: return "Empty";
		case Type::Error: return "Error";
		case Type::Invalid: return "Invalid";
		}
		return "TypeToStringFAILED";
#undef HLSL_EVALUATE
	}
	static HLSLDataType InitializeHLSLDataType(Type type);
	static std::string GetTabs(int count) {
		std::string tab_string = "";
		for (int i = 0; i < count; ++i) tab_string += "   ";
		return tab_string;
	}
	static std::string SignatureToString(const std::vector<char>& signature)
	{
		std::string out = "";
		int tab_counter = 0;
		for (const char& type : signature)
		{
			if (type == (char)Type::Struct || type == (char)Type::Array)
			{
				out += "\n" + GetTabs(tab_counter) + "{";
				++tab_counter;
			}
			else if (type == STRUCT_END || type == ARRAY_END)
			{
				--tab_counter;
				out += "\n" + GetTabs(tab_counter) + "}";
			}
			else
				out += "\n" + GetTabs(tab_counter) + TypeToString(Type(type));
		}
		return out;
	}
	static Type GetTypeFromValue(const HLSLDataType& value);
	static std::vector<char> GetSignatureRec(const HLSLDataType& value);
	static bool CompatibilityCheck(const HLSLDataType& a, const HLSLDataType& b,
		std::source_location loc = std::source_location::current(), int index = -1);
	// Note: AssignRec gonna fail miserably if you call it without CompatibilityCheck
	static void AssignRec(Element& lhs, Assign rhs);

	struct Struct {
		Struct() = default;
		Struct(const std::vector<Assign>& rhs);
		Struct(const Struct& rhs);
		Struct(Struct&& rhs) noexcept;
		Struct& operator=(const Struct& rhs);
		Struct& operator=(Struct&& rhs) noexcept;
		std::vector<Element> elements;
	};

	struct Array {
		Array() = default;
		Array(const std::vector<Assign>& rhs);
		Array(const Array& rhs);
		Array(Array&& rhs) noexcept;
		Array& operator=(const Array& rhs);
		Array& operator=(Array&& rhs) noexcept;

		Type GetArrayType() const;
		std::string GetArrayTypeString() const;

		std::vector<Element> elements;
	};
		
	
	

	struct Assign {
		friend Array; friend Struct; friend Element;
		
		Assign() = default;
#define HLSL_EVALUATE(x) Assign(const Meta<Type::x>::TrueType& value, std::source_location loc = std::source_location::current());
		HLSL_EXPAND
#undef HLSL_EVALUATE
#define HLSL_EVALUATE(x) Assign(Meta<Type::x>::TrueType value, std::source_location loc = std::source_location::current());
		HLSL_EXPAND_PTR
#undef HLSL_EVALUATE
		Assign(const HLSLDataType& value, std::source_location loc = std::source_location::current());
		Assign(const Struct& value, std::source_location loc = std::source_location::current());
		Assign(const Array& value, std::source_location loc = std::source_location::current());

		std::string GetLabel() const;
		Type GetType() const;
		std::source_location GetLocation() const;
		HLSLDataType& GetValue();
		const HLSLDataType& GetValue() const;
	private:
		std::string m_label = "";
		Type m_type = Type::Empty;
		HLSLDataType m_value = Empty();
		std::source_location m_loc;
	};

	struct Label {
		Label(const std::string& label, std::source_location loc = std::source_location::current());
		Label(const char* label, std::source_location loc = std::source_location::current());
		std::string value;
		std::source_location loc;
	};

	struct Index {
		Index(size_t index, std::source_location loc = std::source_location::current());
		size_t value;
		std::source_location loc;
	};

	struct Element {
		friend Array; friend Struct; friend Buffer; friend Layout;
		friend void AssignRec(Element& lhs, Assign rhs);

		Element() = default;

		// Parametrized Constructors
		Element(const std::string& label, Type type);
#define HLSL_EVALUATE(x) Element(const std::string& label, const Meta<Type::x>::TrueType& var);
		HLSL_EXPAND
#undef HLSL_EVALUATE
#define HLSL_EVALUATE(x) Element(const std::string& label, Meta<Type::x>::TrueType var);
		HLSL_EXPAND_PTR
#undef HLSL_EVALUATE

		Element(const std::string& label, const Struct& var);
		Element(const std::string& label, const Array& var);
		Element(const std::string& label, const Error& err);

		// Assignment Operators
		Element& Rename(const std::string& label);

		Element& operator=(const Assign& rhs);

		Element& operator[](Label label);
		Element& operator[](Index index);

		Type GetType() const;
		std::string GetLabel() const;
		HLSLDataType GetValue();
		const HLSLDataType& GetValue() const;
		char* GetBuf();
		size_t GetOffset() const;
		
	private:
		Result m_result;
		Type m_type = Type::Empty;
		std::string m_label = "";
		HLSLDataType m_value = Empty();
		char* m_buf = nullptr;
		size_t m_offset = 0;
	};

	static void EmplaceRec(Element& e)
	{
		HLSLDataType value = e.GetValue();
		Type type = e.GetType();
		if (type == Type::Array)
		{
			Array& arr = std::get<Array>(value);
			for (auto& a : arr.elements)
				EmplaceRec(a);
			return;
		}
		else if (type == Type::Struct)
		{
			Struct& str = std::get<Struct>(value);
			for (auto& s : str.elements)
				EmplaceRec(s);
			return;
		}
#define HLSL_EVALUATE(x) \
			else if (type == Type::x) { \
				auto& var = std::get<Meta<Type::x>::TrueType>(value); \
				std::memcpy(&e.GetBuf()[e.GetOffset()], &var, sizeof(var)); \
				return; }
		HLSL_EXPAND
#undef HLSL_EVALUATE
#define HLSL_EVALUATE(x) \
			else if (type == Type::x) { \
				auto var = *std::get<Meta<Type::x>::TrueType>(value); \
				std::memcpy(&e.GetBuf()[e.GetOffset()], &var, sizeof(var)); \
				return; }
		HLSL_EXPAND_PTR
#undef HLSL_EVALUATE
	}

	struct Layout {
		friend Buffer;
		Layout() {
			root = Element("root", Struct());
		}
		Layout(const std::string& root_name) {
			root = Element(root_name, Struct());
		}
		Element& operator[](Label label) {
			return root[label];
		}
		Element& operator[](Index index) {
			return root[index];
		}
		Element& GetRoot() {
			return root;
		}
	private:
		Element root;
	};
		
	struct Buffer {
		friend Element;
		Buffer() = default;
		Buffer(const Layout& layout) {
			Init(layout);
		}
		void Init(const Layout& layout) {
			m_layout = layout;
			size_t buffer_size = CalcOffsetRec(0, m_layout.root);
			m_buffer.resize(buffer_size);
			SetPtrRec(m_layout.root);
			EmplaceRec(m_layout.root);
			SetDynamicRec(m_layout.root);
		}
		Element& operator[](Label label) {
			return m_layout[label];
		}
		void* GetBuffer() {
			return m_buffer.data();
		}
		size_t GetBufferSize() {
			return m_buffer.size();
		}
		Element& GetRoot() {
			return m_layout.GetRoot();
		}
		void Update() {
			for (auto& e : m_dynamic)
				EmplaceRec(e);
		}
	protected:
		size_t CalcOffsetRec(size_t m_offset, Element& e) {
			e.m_offset = m_offset;
			if (e.m_type == Type::Array) {
				Array& arr = std::get<Array>(e.m_value);
				size_t arr_offset = 0;
				for (auto& a : arr.elements)
					arr_offset += CalcOffsetRec(m_offset + arr_offset, a);

				return arr_offset + (16 - arr_offset % 16);
			}
			else if (e.m_type == Type::Struct) {
				Struct& str = std::get<Struct>(e.m_value);
				size_t str_offset = 0;
				for (auto& s : str.elements)
					str_offset += CalcOffsetRec(m_offset + str_offset, s);

				return str_offset + (16 - str_offset % 16);
			}
#define HLSL_EVALUATE(x) \
			else if (e.m_type == Type::x) { \
				auto& var = std::get<Meta<Type::x>::TrueType>(e.m_value); \
				return sizeof(var) + Meta<Type::x>::padding; \
			}
			HLSL_EXPAND
#undef HLSL_EVALUATE
#define HLSL_EVALUATE(x) \
			else if (e.m_type == Type::x) { \
				auto var = *std::get<Meta<Type::x>::TrueType>(e.m_value); \
				return sizeof(var) + Meta<Type::x>::padding; \
			}
			HLSL_EXPAND_PTR
#undef HLSL_EVALUATE
				
			return 0;
		}
		void SetPtrRec(Element& e) {
			e.m_buf = m_buffer.data();
			if (e.m_type == Type::Array)
			{
				Array& arr = std::get<Array>(e.m_value);
				for (auto& a : arr.elements)
					SetPtrRec(a);
			}
			else if (e.m_type == Type::Struct)
			{
				Struct& str = std::get<Struct>(e.m_value);
				for (auto& s : str.elements)
					SetPtrRec(s);
			}
		}
		void SetDynamicRec(Element& e)
		{
			if (e.m_type == Type::Array)
			{
				Array& arr = std::get<Array>(e.m_value);
				for (auto& a : arr.elements)
					SetDynamicRec(a);
			}
			else if (e.m_type == Type::Struct)
			{
				Struct& str = std::get<Struct>(e.m_value);
				for (auto& s : str.elements)
					SetDynamicRec(s);
			}
#define HLSL_EVALUATE(x) else if (e.m_type == Type::x) { m_dynamic.push_back(e); }
			HLSL_EXPAND_PTR
#undef HLSL_EVALUATE
		}

		Layout m_layout;
		std::vector<Element> m_dynamic;
		std::vector<char> m_buffer;
	};

	

}
#undef HLSL_EXPAND
#undef HLSL_EXPAND_PTR
#undef ARRAY_END
#undef STRUCT_END
