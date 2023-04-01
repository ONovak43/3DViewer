namespace VL
{
	template<typename T>
	std::shared_ptr<T> Asset<T>::getAsset(const std::string& name)
	{
		auto it = m_assets.find(name);
		if (it != m_assets.end())
		{
			return it->second;
		}
		else
		{
			auto asset = loadAsset(name);
			m_assets[name] = std::move(asset);
			return m_assets[name];
		}
	}
}