#pragma once
#include <cmath>
#include <vector>
#include <Utility/ErrorHandling.h>


namespace Duat::Utility {

	template<typename T>
	struct ring : public std::vector<T>
	{
		const T& operator[](int at) const {
			if (this->size() == 0) m_result << "Ring size zero.";
			return std::vector<T>::operator[](evaluate_index(at));
		}

		const T& operator[](float at) const {
			int index = std::floor(at * (this->size() - 1));
			return (*this)[evaluate_index(index)];
		}

		const T& operator[](double at) const {
			return (*this)[(float)at];
		}


		T& operator[](int at)
		{
			if (this->size() == 0) m_result << "Ring size zero.";
			return std::vector<T>::operator[](evaluate_index(at));
		}

		T& operator[](float at)
		{
			int index = std::floor(at * (this->size() - 1));
			return (*this)[evaluate_index(index)];
		}

		T& operator[](double at)
		{
			return (*this)[(float)at];
		}

		bool operator>(ring<T>& rhs)
		{
			return this->size() > rhs.size();
		}
		
		bool operator<(ring<T>& rhs)
		{
			return this->size() < rhs.size();
		}

		auto erase(int at)
		{
			at = evaluate_index(at);
			sync_shift();
			perform_erase_shift(at);
			erase_shift.erase(erase_shift.begin() + at);
			return std::vector<T>::erase(this->begin() + at);
		}

		T& get(int index_handle)
		{
			sync_shift();
			int at = evaluate_index(index_handle);
			return std::vector<T>::operator[](at + erase_shift[at]);
		}

	private:
		void sync_shift()
		{
			for (int i = 0; i < this->size() - erase_shift.size(); ++i)
				erase_shift.push_back(0);
		}
		void perform_erase_shift(int at)
		{
			for(int i = at; i < erase_shift.size(); ++i)
				erase_shift[at]--;
		}
		int evaluate_index(int index) const
		{
			int mod_index = std::abs(index) % (int)this->size();
			if (index < 0 && mod_index != 0) return this->size() - mod_index;
			if (index < 0 && mod_index == 0) return 0;
			return mod_index;
		}

		Utility::Result m_result;
		std::vector<int> erase_shift;
	};

}