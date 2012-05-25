#ifndef CLIENT_OBJECTTABLEMODEL_HPP
#define CLIENT_OBJECTTABLEMODEL_HPP

#include <iterator>
#include <vector>
#include <cassert>
#include <algorithm>
#include "abstractobjecttablemodel.hpp"
#include "game/container.hpp"

template<class T>
class ObjectTableModel : public AbstractObjectTableModel
{
	public:
		class Field;

		void addField(const Field* field)
		{
			fields.push_back(field);
		}

		int getFieldIndex(const Field* field)
		{
			auto it = std::find(fields.begin(), fields.end(), field);

			if(it != fields.end())
				return std::distance(fields.begin(), it);

			return -1;
		}

		class Field
		{
			public:
				virtual std::string getHeader() const = 0;
				virtual QVariant getData(T* t) const = 0;
				virtual QVariant getDecoration(T* t) const = 0;

				int getIndex() const
				{
					return parent->getFieldIndex(this);
				}

				Field(ObjectTableModel* parent):
					parent(parent)
				{
					parent->addField(this);
				};

			private:
				ObjectTableModel* parent;
				std::string header;
				std::function<QVariant(T*)> func;

		};

		virtual int getRowCount() const
		{
			return dataSource.getItemCount();
		}

		T* getObject(int row) const
		{
			assert(row >= 0);
			assert(row < dataSource.getItemCount());

			return dataSource.getByIndex(row);
		}

		ObjectTableModel(const Game::Container<T>& dataSource):
			dataSource(dataSource)
		{
			connect(&dataSource, SIGNAL(added(int)), this, SLOT(onAdd(int)));
			connect(&dataSource, SIGNAL(removed(int)), this, SLOT(onRemove(int)));
			connect(&dataSource, SIGNAL(changed(int)), this, SLOT(onChange(int)));
		}

	protected:
		virtual std::string getHeader(int col) const
		{
			return fields[col]->getHeader();
		}

		virtual int getColumnCount() const
		{
			return fields.size();
		}

                virtual QVariant getData(int row, int col) const
		{
			auto it = dataSource.begin();

			for(int i = 0; i < row; ++i)
				++it;

			return fields[col]->getData(*it);
		}

		virtual QVariant getDecoration(int row, int col) const
		{
			auto it = dataSource.begin();

			std::advance(it, row);

			return fields[col]->getDecoration(*it);
		}

		void onAdd(int index)
		{
			beginInsertRows(QModelIndex(), index, index);
			endInsertRows();
		}

		void onRemove(int index)
		{
			beginRemoveRows(QModelIndex(), index, index);
			endRemoveRows();
		}

		void onChange(int index)
		{
			(void)index;
		}

	private:
		const Game::Container<T>& dataSource;
		std::vector<const Field*> fields;

};

#endif
