#pragma once
#include <algorithm>
#include <string>
#include "Ring.h"


namespace Duat::Utility {

	template<typename T>
	struct Hierarchy {
		struct Node : public T {
			std::string name;
			int index;
			ring<int> parents;
			ring<int> children;
		};

		Hierarchy()
		{
			Node n;
			n.name = "root";
			n.index = 0;
			m_at = 0;
			m_nodes.push_back(n);
		}

		std::string GetName()
		{
			return m_nodes[m_at].name;
		}

		std::string GetName(int index)
		{
			return m_nodes[index].name;
		}

		int Go(std::string nodeName)
		{
			for (int i = 0; i < m_nodes.size(); ++i)
				if (m_nodes[i].name == nodeName)
					return m_at = i;
			return m_at;
		}

		int Go(int position)
		{
			return m_at = position;
		}

		int GoRoot()
		{
			return m_at = 0;
		}

		int Step(int step)
		{
			if (step < 0)
				return m_at = m_nodes[m_at].parents[step];

			return m_at = m_nodes[m_at].children[step];
		}

		int Create(std::string name)
		{
			m_nodes[m_at].children.push_back(m_nodes.size());

			Node n;
			n.name = name;
			n.index = m_nodes.size();
			n.parents = m_nodes[m_at].parents;
			n.parents.push_back(m_at);
			m_nodes.push_back(n);
			return m_nodes.size() - 1;
		}

		int Delete()
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

		int GetIndex()
		{
			return m_nodes[m_at].index;
		}

		ring<int>& GetParents()
		{
			return m_nodes[m_at].parents;
		}

		ring<int>& GetParents(int index)
		{
			return m_nodes[index].parents;
		}

		ring<int>& GetChildren()
		{
			return m_nodes[m_at].children;
		}

		ring<int>& GetChildren(int index)
		{
			return m_nodes[index].children;
		}

		int SetName(std::string name)
		{
			m_nodes[m_at].name = name;
			return m_at;
		}

		int SetName(std::string name, int index)
		{
			m_nodes[index].name = name;
			return index;
		}

		Node& Get(int position = -1)
		{
			if (position < 0) return m_nodes[m_at];
			return m_nodes[position];
		}

		int GetNodeCount()
		{
			return m_nodes.size();
		}

		Node& GetStep(int step)
		{
			int at;
			if (step <= 0)
				at = m_nodes[m_at].parents[step];
			else
				at = m_nodes[m_at].children[step - 1];

			return m_nodes[at];
		}

		Node& GetStep(int index, int step)
		{
			int at;
			if (step <= 0)
				at = m_nodes[index].parents[step];
			else
				at = m_nodes[index].children[step - 1];

			return m_nodes[at];
		}

		protected:
			int m_at = 0;
			std::vector<Node> m_nodes;
		std::vector<int> get_all_children(int from)
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

	};

}