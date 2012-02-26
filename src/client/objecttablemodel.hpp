#ifndef CLIENT_TABLEMODEL_HPP
#define CLIENT_TABLEMODEL_HPP

#include <iterator>
#include <vector>
#include <cassert>
#include <algorithm>
#include "abstractobjecttablemodel.hpp"
#include "objecttomodel.hpp"
#include "game/container.hpp"

template<class T> 
class ObjectTableModel : public AbstractObjectTableModel
{
	public:
		virtual int getRowCount() const
		{
			return rows.size();
		}
	
		T* getObject(int row) const
		{
			return rows[row];
		}
	
		ObjectTableModel(const Game::Container<T>& dataSource):
			dataSource(dataSource)
		{
			for(T* t : dataSource)
			{
				rows.push_back(t);
			}
		
			connect(&dataSource, SIGNAL(childAdded(int)), this, SLOT(onAdd(int)));
			connect(&dataSource, SIGNAL(childRemoved(int)), this, SLOT(onRemove(int)));
			connect(&dataSource, SIGNAL(childChanged(int)), this, SLOT(onChange(int)));
		}

	protected:
		virtual std::string getHeader(int col) const
		{
			return converter.getHeader(col);
		}

		virtual int getColumnCount() const 
		{
			return converter.getColumnCount();
		}

                virtual QVariant getData(int row, int col) const
		{
			auto it = rows.begin();

			for(int i = 0; i < row; ++i)
				++it;

			return converter.getData(*it, col);
		}	

		void onAdd(int index)
		{
			T* t = dataSource.getByIndex(index);
			
			beginInsertRows(QModelIndex(), rows.size(), rows.size());
				
			rows.push_back(t);
				
			endInsertRows();
		}
		
		void onRemove(int index)
		{
			auto it = rows.begin();
			
			advance(it, index);
				
			// item must exist because it cannot be removed unless it was added earlier
			assert(it != rows.end());
			
			beginRemoveRows(QModelIndex(), index, index);
			
			rows.erase(it);
			
			endRemoveRows();
		}
		
		void onChange(int index)
		{
			(void)index;
		}
	
	private:
		const Game::Container<T>& dataSource;
	
		ObjectModel<T> converter;
		std::vector<T*> rows;
		
};

#endif
