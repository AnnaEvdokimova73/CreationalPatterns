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

	std::string BuildQuery() const
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
				queryText += key + "=" + val + " AND ";
			}

			for (int i = 0; i < 5; ++i)
			{
				queryText.pop_back();
			}
		}

		queryText += ";";

		return queryText;
	}

private:
	QueryData queryData;
};