#include "Hierarchy.h"


namespace Duat::Utility {
		
	template<typename T>
	Hierarchy<T>::Hierarchy()
	{
		HierarchyNode<T> n;
		n.name = "root";
		n.index = 0;
		m_at = 0;
		m_nodes.push_back(n);
	}

	template<typename T>
	std::string Hierarchy<T>::GetName()
	{
		return m_nodes[m_at].name;
	}

	template<typename T>
	std::string Hierarchy<T>::GetName(int index)
	{
		return m_nodes[index].name;
	}

	template<typename T>
	int Hierarchy<T>::Go(std::string nodeName)
	{
		for (int i = 0; i < m_nodes.size(); ++i)
			if (m_nodes[i].name == nodeName)
				return m_at = i;
		return m_at;
	}

	template<typename T>
	int Hierarchy<T>::Go(int position)
	{
		return m_at = position;
	}

	template<typename T>
	int Hierarchy<T>::GoRoot()
	{
		return m_at = 0;
	}

	template<typename T>
	int Hierarchy<T>::Step(int step)
	{
		if (step < 0)
			return m_at = m_nodes[m_at].parents[step];

		return m_at = m_nodes[m_at].children[step];
	}

	template<typename T>
	int Hierarchy<T>::Create(std::string name)
	{
		m_nodes[m_at].children.push_back(m_nodes.size());

		HierarchyNode<T> n;
		n.name = name;
		n.index = m_nodes.size();
		n.parents = m_nodes[m_at].parents;
		n.parents.push_back(m_at);
		m_nodes.push_back(n);
		return m_nodes.size() - 1;
	}

	template<typename T>
	int Hierarchy<T>::Delete()
	{
		if (m_at == 0) return 0;

		auto children = get_all_children(m_at);
		std::sort(children.begin(), children.end(),
			[](int a, int b) { return a < b; });

		for (int i = children.size() - 1; i >= 0; --i)
		{
			for (int j = m_nodes.size() - 1; j >= 0; --j)
			{
				if (j < children[i]) break;
				if (j > children[i])
				{
					--m_nodes[j].index;
					continue;
				}
				if (j == children[i])
					m_nodes.erase(m_nodes.begin() + j);
			}
		}

		return m_at;
	}

	template<typename T>
	int Hierarchy<T>::GetIndex()
	{
		return m_nodes[m_at].index;
	}

	template<typename T>
	ring<int>& Hierarchy<T>::GetParents()
	{
		return m_nodes[m_at].parents;
	}

	template<typename T>
	ring<int>& Hierarchy<T>::GetParents(int index)
	{
		return m_nodes[index].parents;
	}

	template<typename T>
	ring<int>& Hierarchy<T>::GetChildren()
	{
		return m_nodes[m_at].children;
	}

	template<typename T>
	ring<int>& Hierarchy<T>::GetChildren(int index)
	{
		return m_nodes[index].children;
	}

	template<typename T>
	int Hierarchy<T>::SetName(std::string name)
	{
		m_nodes[m_at].name = name;
		return m_at;
	}

	template<typename T>
	int Hierarchy<T>::SetName(std::string name, int index)
	{
		m_nodes[index].name = name;
		return index;
	}
		
	template<typename T>
	HierarchyNode<T>& Hierarchy<T>::Get(int position)
	{
		if (position < 0) return m_nodes[m_at];
		return m_nodes[position];
	}

	template<typename T>
	int Hierarchy<T>::GetNodeCount()
	{
		return m_nodes.size();
	}

	template<typename T>
	HierarchyNode<T>& Hierarchy<T>::GetStep(int step)
	{
		int at;
		if (step <= 0)
			at = m_nodes[m_at].parents[step];
		else
			at = m_nodes[m_at].children[step - 1];

		return m_nodes[at];
	}

	template<typename T>
	HierarchyNode<T>& Hierarchy<T>::GetStep(int index, int step)
	{
		int at;
		if (step <= 0)
			at = m_nodes[index].parents[step];
		else
			at = m_nodes[index].children[step - 1];

		return m_nodes[at];
	}

	template<typename T>
	std::vector<int> Hierarchy<T>::get_all_children(int from)
	{
		std::vector<int> result;
		for (auto child : m_nodes[from].children)
		{
			result.push_back(child);
			auto result_rec = get_all_children(child);
			result.insert(result.end(), result_rec.begin(), result_rec.end());
		}
		return result;
	}

}