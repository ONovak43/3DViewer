namespace VL
{
	namespace OpenGL
	{
        template<typename T>
        inline void OpenGLBuffer::setStaticData(const std::vector<T>& data)
        {
            auto d = data.data();
            setStaticData(data.data(), data.size() * sizeof(T));
        }

        template<typename T>
        inline void OpenGLBuffer::setDynamicData(const std::vector<T>& data)
        {
            setDynamicData(data.data(), data.size() * sizeof(T));
        }
	}
}