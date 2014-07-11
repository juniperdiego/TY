#ifndef _PKG_DB_H__
#define _PKG_DB_H__
#include"sqlDB.h"

#include<vector>

class pkgInfo
{
    public:
        int             pkgID;  
        string          pkgName;
        string          batchCode;
        vector<string>  apkList;
        int             apkSum;
        string          date;
};


class pkgDB :public sqlDB
{

    public:
        pkgDB();
        ~pkgDB();

        bool set(const pkgInfo& pkg);
        bool get(pkgInfo & pkg);

    private:
        string      m_tabName;
};


#endif
