#include "devDB.h"
#include "pkgDB.h"

using namespace std;




int main()
{
#if 0
    // 1  test devDB
    devDB  dev_db;

    string devVer;
    string pkgVer;
    string apkVer;
    string chanID;

    dev_db.get(DEV_VER, devVer);
    dev_db.get(PKG_VER, pkgVer);
    dev_db.get(APK_VER, apkVer);
    dev_db.get(CHAN_ID, chanID);

    cout <<"devVer\t" << devVer<<endl;
    cout <<"pkgVer\t" << pkgVer<<endl;
    cout <<"apkVer\t" << apkVer<<endl;
    cout <<"chanID\t" << chanID<<endl;

    dev_db.set(DEV_VER, "devvv");
    dev_db.set(PKG_VER, "pkgvv");
    dev_db.set(APK_VER, "apkvv");
    dev_db.set(CHAN_ID, "chanvv");

    dev_db.get(DEV_VER, devVer);
    dev_db.get(PKG_VER, pkgVer);
    dev_db.get(APK_VER, apkVer);
    dev_db.get(CHAN_ID, chanID);

    cout <<"devVer\t" << devVer<<endl;
    cout <<"pkgVer\t" << pkgVer<<endl;
    cout <<"apkVer\t" << apkVer<<endl;
    cout <<"chanID\t" << chanID<<endl;
    cout << endl;
#endif

    // 2  test pkgDB
#if 0
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
#endif
    devDB  dev_db2;
    pkgDB  pkg_db;
    pkgInfo pInfo;

    vector<string>  apkList;
    apkList.push_back("1.apk");
    apkList.push_back("2.apk");
    apkList.push_back("3.apk");
    apkList.push_back("4.apk");
    apkList.push_back("5.apk");
    apkList.push_back("6.apk");
    apkList.push_back("7.apk");

    pInfo.pkgID = 100;
    pInfo.pkgName = "name1";
    pInfo.batchCode = "batchcode1";
    pInfo.apkList  = apkList;
    pInfo.apkSum = apkList.size();
    pInfo.date = "20140707121212";

    bool suc = pkg_db.set(pInfo);
    if(suc == true)
        cout << "insert suc"<<endl;
    else
        cout << "insert fail"<<endl;



    int nrow = 0, ncolumn = 0;
    char **azResult; 
    char * zErrMsg;

    char sql[] = "SELECT * FROM packageTable";
    sqlite3_get_table( pkg_db.get_db() , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

    int i = 0 ;
    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );

    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
        printf( "azResult[%d] = %s\n", i , azResult[i] );






    pkg_db.get(pInfo);

    cout << "pInfo.pkgID\t" << pInfo.pkgID<<endl;
    cout << "pInfo.pkgName \t" << pInfo.pkgName<<endl;
    cout << "pInfo.batchCode\t" <<pInfo.batchCode <<endl;
    cout << "pInfo.apkSum  \t" << pInfo.apkSum <<endl;
    cout << "pInfo.date \t" << pInfo.date<<endl;

    for(size_t i = 0; i< pInfo.apkList.size(); i++)
    {
        cout << pInfo.apkList[i] << "\t";
    }
    cout << endl;

#if 1
    apkList.push_back("8.apk");
    pInfo.pkgID = 200;
    pInfo.pkgName = "name2";
    pInfo.batchCode = "batchcode2";
    pInfo.apkList  = apkList;
    pInfo.apkSum = apkList.size();
    pInfo.date = "20140707144488";

    pkg_db.set(pInfo);
    pkg_db.get(pInfo);
    cout << "pInfo.pkgID\t" << pInfo.pkgID<<endl;
    cout << "pInfo.pkgName \t" << pInfo.pkgName<<endl;
    cout << "pInfo.batchCode\t" <<pInfo.batchCode <<endl;
    cout << "pInfo.apkSum  \t" << pInfo.apkSum <<endl;
    cout << "pInfo.date \t" << pInfo.date<<endl;

    for(size_t i = 0; i< pInfo.apkList.size(); i++)
    {
        cout << pInfo.apkList[i] << "\t";
    }
    cout << endl;
#endif
    return 0;
}
