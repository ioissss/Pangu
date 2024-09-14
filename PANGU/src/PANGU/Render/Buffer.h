#pragma once

namespace PANGU {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case PANGU::ShaderDataType::None:
			break;
		case PANGU::ShaderDataType::Float:
			return 4;
		case PANGU::ShaderDataType::Float2:
			return 4 * 2;
		case PANGU::ShaderDataType::Float3:
			return 4 * 3;
		case PANGU::ShaderDataType::Float4:
			return 4 * 4;
		case PANGU::ShaderDataType::Mat3:
			return 3 * 3 * 4;
		case PANGU::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case PANGU::ShaderDataType::Int:
			return 4;
		case PANGU::ShaderDataType::Int2:
			return 4 * 2;
		case PANGU::ShaderDataType::Int3:
			return 4 * 3;
		case PANGU::ShaderDataType::Int4:
			return 4 * 4;
		case PANGU::ShaderDataType::Bool:
			return 1;
		}

		PG_CORE_ASSERT(false,"未知的ShaderDataType");

		return 0;
	}
	
	struct BufferElement
	{
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		ShaderDataType Type;
		bool Normalized;

		uint32_t GetComponentCount()const {
			switch (Type)
			{
			case PANGU::ShaderDataType::Float:
				return 1;
			case PANGU::ShaderDataType::Float2:
				return 2;
			case PANGU::ShaderDataType::Float3:
				return 3;
			case PANGU::ShaderDataType::Float4:
				return 4;
			case PANGU::ShaderDataType::Mat3:
				return 9;
			case PANGU::ShaderDataType::Mat4:
				return 16;
			case PANGU::ShaderDataType::Int:
				return 1;
			case PANGU::ShaderDataType::Int2:
				return 2;
			case PANGU::ShaderDataType::Int3:
				return 3;
			case PANGU::ShaderDataType::Int4:
				return 4;
			case PANGU::ShaderDataType::Bool:
				return 1;
			}

			PG_CORE_ASSERT(false, "调用函数GetComponentCount()时获取到未知的ShaderDataType");

			return 0;
		}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false):
			Name(name),Type(type),Size(ShaderDataTypeSize(type)),Offset(0),Normalized(normalized){}
	};

	class BufferLayout {
	public:
		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements):elements(elements){
			CalBufferElementOffsetAndStride();
		}
		std::vector<BufferElement>& GetLayout() { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }

		std::vector<BufferElement>::const_iterator begin()const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end()const { return elements.end(); }

		uint32_t GetStride()const { return Stride; }

	private:
		std::vector<BufferElement> elements;
		uint32_t Stride = 0;
		void CalBufferElementOffsetAndStride() {
			uint32_t stride = 0;
			for (BufferElement& element : elements) {
				element.Offset = stride;
				stride += element.Size;
				this->Stride += element.Size;
			}
		}
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual BufferLayout& GetLayout() = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer();
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual uint32_t GetCount()const = 0;
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}
