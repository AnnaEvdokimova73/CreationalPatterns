#include "sql_query_builder.h"
#include <iostream>

int main()
{
    AdvancedSqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone", "address" });
    query_builder.AddFrom("students");

    std::map<std::string, std::string> whereMap;
    whereMap["name"] = "Nick";
    whereMap["profession"] = "doctor";
    query_builder.AddWhere(whereMap);

    query_builder.AddWhereMore("id", "3"); // Добавляем условие id > 3
    query_builder.AddWhereLess("id", "50"); // Добавляем условие id < 50

    std::cout << query_builder.BuildQuery();
}