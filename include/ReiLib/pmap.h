#pragma once

#include <map>
#include <vector>
#include <algorithm>

#define PMAP_MAX_SIZE 256

namespace rei
{
	template<class Key, class Val>
	class pmap
	{
		struct DataPair
		{
			DataPair(Val val) : value(val), dead(false) {}
			bool dead;
			Val value;
		};

	public:
		pmap(unsigned int maxSize = PMAP_MAX_SIZE) : max(maxSize) { data.reserve(max); }
		~pmap() {}
		void push(Key key, Val&& val)
		{
			if (data.size() < PMAP_MAX_SIZE)
			{
				unsigned int pIndex = (int) data.size();
				unsigned int dIndex = 0;
				data.push_back(DataPair(val));
				for (DataPair& pair : data)
				{
					if (pair.dead)
					{
						std::swap(data[dIndex], data[pIndex]);
						pIndex = dIndex;
						data.pop_back();
						break;
					}
					++dIndex;
				}
				index[key] = pIndex;
			}
			else { std::cout << "POOL MAP MAX CAPACITY" << std::endl; }
		}

		void push(Key key, Val& val)
		{
			if (data.size() < PMAP_MAX_SIZE)
			{
				unsigned int pIndex = (unsigned int)data.size();
				unsigned int dIndex = 0;
				data.push_back(DataPair(val));
				for (DataPair& pair : data)
				{
					if (pair.dead)
					{
						std::swap(data[dIndex], data[pIndex]);
						pIndex = dIndex;
						data.pop_back();
						break;
					}
					++dIndex;
				}
				index[key] = pIndex;
			}
			else { std::cout << "POOL MAP MAX CAPACITY" << std::endl; }
		}

		void remove(Key key)
		{
			data[index[key]].dead = true;
			index.erase(key);
		}

		void clear()
		{
			index.clear();
			data.clear();
		}

		bool check(Key key)
		{
			return index.find(key) != index.end();
		}

		Val& get(Key key)
		{
			try {
				if (index.find(key) != index.end())
				{
					return data[index[key]].value;
				}
				else {
					throw(69);
				}
			}
			catch (int err)
			{
				std::cout << "ERR " << err << ": Accessing null object" << std::endl;
				return data[0].value;
			}

		}

		auto find(Key key)
		{
			return index.find(key);
		}

		std::map<Key, unsigned int>& getMap() { return index; }
		std::vector<DataPair>& getRaw()
		{
			return data;
		}

	private:
		size_t max;
		std::vector<DataPair> data;
		std::map<Key, unsigned int> index;
	};
}


