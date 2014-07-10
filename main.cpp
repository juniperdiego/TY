#include "devDB.h"

using namespace std;




int main()
{
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

    return 0;
}
