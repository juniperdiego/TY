#include "devDB.h"

devDB::devDB()
{

    // 1. should open the db, but the db is opened
    
    // 2. name the divec talbe 
    m_tabName = "deviceTable";

    // 3. create the table 


    char sql[1024] ="";
    if(!tableExist(m_tabName))
    {
        char* errMsg;
        // creat the table
        sprintf(sql, "CREATE TABLE %s ( key integer PRIMARY KEY, val varchar(128) );", m_tabName.c_str());
        sqlite3_exec(s_db, sql, NULL, NULL, &errMsg);

        m_devVer  = "1.0.0";
        m_pkgVer  = "0";
        m_apkVer  = "0";
        m_chanId  = "0";

        // insert the row
        insertToTable(m_tabName, DEV_VER, m_devVer);
        insertToTable(m_tabName, PKG_VER, m_pkgVer);
        insertToTable(m_tabName, APK_VER, m_apkVer);
        insertToTable(m_tabName, CHAN_ID, m_chanId);
    }
}

devDB::~devDB()
{
}


bool devDB::set(devDBKey key, string value)
{
    char sql[1024] ="";
    char* errMsg;
    sprintf(sql, "insert or replace into %s (key, val)  values( %d, \"%s\" );", m_tabName.c_str(), key, value.c_str());
    if(SQLITE_OK == sqlite3_exec(s_db, sql, NULL, NULL, &errMsg))
        return true;
    return false;

}


bool devDB::get(devDBKey key, string& value)
{
    value = "";
    char sql[1024] ="";
    char* errMsg;
    sqlite3_stmt *stmt;
    int rc;

    sprintf(sql, "select val from %s where key = '%d';", m_tabName.c_str(), key);

    rc= sqlite3_prepare(s_db,sql, strlen(sql), &stmt,0);     
    if( rc ){   
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(s_db));   
        sqlite3_close(s_db);   
        return false;   
    }   

    while(sqlite3_step(stmt)==SQLITE_ROW ) {   
        value = string( (const char*)sqlite3_column_text(stmt,0));   
        //printf("%s\n",  (const char*)sqlite3_column_text(stmt,0));
    }   
    sqlite3_finalize(stmt);
    return true;
}
