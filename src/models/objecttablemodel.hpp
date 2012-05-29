#ifndef CLIENT_OBJECTTABLEMODEL_HPP
#define CLIENT_OBJECTTABLEMODEL_HPP

#include <iterator>
#include <vector>
#include <cassert>
#include <algorithm>
#include "abstractobjecttablemodel.hpp"
#include "game/container.hpp"

template<class T>
class ObjectTableModel : public AbstractObjectTableModel, public Game::Container<T>::Listener
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

		void onAdd(Game::Container<T>* container, int index)
		{
			(void)container;

			beginInsertRows(QModelIndex(), index, index);
			endInsertRows();
		}

		void onRemove(Game::Container<T>* container, int index)
		{
			(void)container;

			beginRemoveRows(QModelIndex(), index, index);
			endRemoveRows();
		}

		void onChange(Game::Container<T>* container, int i)
		{
			dataChanged(index(i, 0), index(i, columnCount(QModelIndex()) - 1));

			std::cout << i << std::endl;

			(void)container;
		}

		ObjectTableModel(const Game::Container<T>& dataSource):
			dataSource(dataSource)
		{
			dataSource.addListener(this);
		}

		~ObjectTableModel()
		{
			dataSource.removeListener(this);
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

	private:
		const Game::Container<T>& dataSource;
		std::vector<const Field*> fields;

};

#endif
