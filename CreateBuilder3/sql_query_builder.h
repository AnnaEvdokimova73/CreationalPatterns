#pragma once

#pragma once
#include <string>
#include <vector>
#include <map>

struct QueryData {
	std::vector<std::string> vecCol;
	std::string tableName;
	std::map<std::string, std::string> mapCond;

};

class SqlSelectQueryBuilder {
public:

	SqlSelectQueryBuilder& AddColumn(const std::string& colName)
	{
		queryData.vecCol.push_back(colName);
		return *this;
	}

	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
	{
		for (std::string col : columns)
		{
			queryData.vecCol.push_back(col);
		}
		return *this;
	}

	SqlSelectQueryBuilder& AddFrom(const std::string& tableName)
	{
		queryData.tableName = tableName;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value)
	{
		queryData.mapCond[key] = value;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept
	{
		for (auto& [key, val] : kv)
		{
			queryData.mapCond[key] = val;
		}

		return *this;
	}

	std::string BuildQuery()
	{
		if (queryData.tableName.empty())
		{
			return "";
		}

		std::string queryText = "SELECT ";

		if (queryData.vecCol.empty())
		{
			queryText += "*";
		}
		else
		{
			for (auto& col : queryData.vecCol)
			{
				queryText += col + ", ";
			}
			queryText.pop_back();
			queryText.pop_back();
		}

		queryText += " FROM " + queryData.tableName;

		if (!queryData.mapCond.empty())
		{
			queryText += " WHERE ";

			for (auto& [key, val] : queryData.mapCond)
			{
				queryText += key + " = " + val + " AND ";
			}

			queryText += addSpecCond();

			for (int i = 0; i < 5; ++i)
			{
				queryText.pop_back();
			}
		}

		queryText += ";";

		return queryText;
	}

	virtual std::string addSpecCond()
	{
		return "";
	}

private:
	QueryData queryData;	
};

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder
{
public:

	SqlSelectQueryBuilder& AddWhereMore(const std::string& key, const std::string& value)
	{
		mapMore[key] = value;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhereLess(const std::string& key, const std::string& value)
	{
		mapLess[key] = value;
		return *this;
	}

	virtual std::string addSpecCond() override
	{
		std::string textTemp;

		for (auto& [key, val] : mapMore)
		{
			textTemp += key + " > " + val + " AND ";
		}

		for (auto& [key, val] : mapLess)
		{
			textTemp += key + " < " + val + " AND ";
		}

		return textTemp;
	}

private:
	std::map<std::string, std::string> mapMore;
	std::map<std::string, std::string> mapLess;
};