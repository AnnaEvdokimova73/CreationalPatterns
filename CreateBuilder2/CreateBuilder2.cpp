#include "sql_query_builder.h"
#include <iostream>

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone", "address" });
    query_builder.AddFrom("students");

    std::map<std::string, std::string> whereMap;
    whereMap["id"] = "115";
    whereMap["name"] = "Nick";
    whereMap["profession"] = "doctor";
    query_builder.AddWhere(whereMap);

    std::cout << query_builder.BuildQuery();
}