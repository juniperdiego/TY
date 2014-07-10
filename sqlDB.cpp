#include "sqlDB.h"

sqlite3 * sqlDB:: s_db = NULL;

int isExisted( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
        bool *isExisted_=(bool*)para; 
            *isExisted_= (**column_value) != '0'; 
                return 0; 
}

sqlDB::sqlDB()
{
    if(s_db == NULL)
    {
        const string dbName = "zig.db";

        // 1. open the database
        int rc;
        rc = sqlite3_open(dbName.c_str(), &s_db);
        if( rc )
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(s_db));
            sqlite3_close(s_db);
            exit(1);
        }
    }
}

sqlDB::~sqlDB()
{
    if(s_db != NULL)
    {
        sqlite3_close(s_db);
        s_db = NULL;
    }
}

int sqlDB::tableExist(string tableName)
{
    bool bExist;
    char *zErrMsg = 0;
    int rc;

    char str[1024];
    sprintf(str, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s';", tableName.c_str());
    sqlite3_exec( s_db , str , isExisted , & bExist, &zErrMsg );
    return bExist;
}

bool sqlDB::insertToTable(string tableName, int key, string val)
{
    char sql[1024] ="";
    char* errMsg = NULL;
    sprintf(sql, "insert into %s (key, val)  values( %d, \"%s\" );", tableName.c_str(), key, val.c_str());
    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;
}

int sqlDB::sqlInit()
{

}


bool sqlDB::exist_in_db(sqlite3 *db, const string table, const string id ){
    char sql_query[128]={0};
    sprintf(sql_query,"select count(*) from %s where id='%s'", table.c_str(), id.c_str());

    sqlite3_stmt *pstmt;
    sqlite3_prepare(db, sql_query, strlen(sql_query), &pstmt, NULL);
    sqlite3_step(pstmt);

    int count=sqlite3_column_int(pstmt,0);
    sqlite3_finalize(pstmt);
    if(count > 0)
        return true;
    else
        return false;
}


