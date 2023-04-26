namespace VL
{
	template<typename T>
	std::shared_ptr<T> Asset<T>::getAsset(const std::string& name, bool cache)
	{
		auto it = m_assets.find(name);
		if (it != m_assets.end())
		{
			return it->second;
		}
		else if(cache == true)
		{
			m_assets[name] = loadAsset(name);
			return m_assets[name];
		}
		else
		{
			return loadAsset(name);
		}
	}
}