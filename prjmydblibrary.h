#ifndef PRJMYDBLIBRARY_H
#define PRJMYDBLIBRARY_H

#include "prjmydblibrary_global.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <QListWidget>
#include <QtSql/QtSql>
#include <QSqlQuery>

enum class clsReturnDataType:int {INT,FLOAT,DOUBLE,STRING};

class PRJMYDBLIBRARYSHARED_EXPORT PrjMyDBLibrary
{

public:
    PrjMyDBLibrary(QString _strDatabaseName, QString _strDbStorePath);
    PrjMyDBLibrary();
    void fnDBDisconnect();
    static QSqlDatabase objDbCon;
    static QSqlQuery objRs;
    int fnGetSRSCRowIntValue(QString strQuery, QString strColName);
    QString fnGetSRSCStringValue(QString strQuery, QString strColName);
    float fnGetSRSCFloatValue(QString strQuery, QString strColName);
    double fnGetSRSCDoubleValue(QString strQuery, QString strColName);
    void fnDBReopen();
private:
    static bool blnIsConnectionOpen;
    void fnConnectDbForNonAndroid();
    void fnConnectDbForAndroid();
    QString strDatabaseName,strDbStorePath;
    void fnClasInti();
    int intSingleVal;
    float fltSingleVal;
    double dblSingleVal;
    QString strSingleVal;
    bool fnGetSingleRowSingleColFieldValue(QString strQuery, QString strColName, clsReturnDataType returnType);
};

#endif // PRJMYDBLIBRARY_H
