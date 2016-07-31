#include "prjmydblibrary.h"

QSqlDatabase PrjMyDBLibrary::objDbCon = {QSqlDatabase::addDatabase(NULL)};
QSqlQuery PrjMyDBLibrary::objRs= {QSqlQuery(NULL)};
bool PrjMyDBLibrary::blnIsConnectionOpen=false;

PrjMyDBLibrary::PrjMyDBLibrary(QString _strDatabaseName, QString _strDbStorePath):strDatabaseName(_strDatabaseName),
	strDbStorePath(_strDbStorePath)
{

}

PrjMyDBLibrary::PrjMyDBLibrary()
{

}

void PrjMyDBLibrary::fnDBReopen()
{
	//close if connection connection open
	fnDBDisconnect();
	fnClasInti();
}

void PrjMyDBLibrary::fnClasInti()
{
	if(QSysInfo::productType()=="android")
	{
		fnConnectDbForAndroid();
	}
	else
	{
		fnConnectDbForNonAndroid();
	}
}

void PrjMyDBLibrary::fnDBDisconnect()
{
	if(blnIsConnectionOpen)
	{
		if(PrjMyDBLibrary::objDbCon.isOpen())
		{
			PrjMyDBLibrary::objDbCon.close();
			PrjMyDBLibrary::objRs.finish();
		}

		QDir ddir(strDbStorePath);
		if(ddir.exists())
		{
			QFile sfile(strDbStorePath + (QSysInfo::productType()=="android" ? "/" : "") + strDatabaseName);
			QString strFile = strDbStorePath + (QSysInfo::productType()=="android" ? "/" : "") + strDatabaseName + "_" + QDateTime::currentDateTime().toString("ddMMMyyyy_hhmmssAP") + ".backup";
			sfile.copy(strFile);
			QFile::setPermissions(strFile,QFile::WriteOwner | QFile::ReadOwner);
		}
	}
}

void PrjMyDBLibrary::fnConnectDbForAndroid()
{
	PrjMyDBLibrary::objDbCon = QSqlDatabase::addDatabase("QSQLITE");
	QFile sfile("assets:\\" + strDatabaseName);

	QDir ddir(strDbStorePath);
	if(!ddir.exists())
	{
		ddir.mkdir(strDbStorePath);
	}
	QFile dfile(strDbStorePath + "/" + strDatabaseName);
	if (!dfile.exists())
	{
		sfile.copy(strDbStorePath + "/" + strDatabaseName);
		QFile::setPermissions(strDbStorePath + "/" + strDatabaseName,QFile::WriteOwner | QFile::ReadOwner);
	}
	PrjMyDBLibrary::objDbCon.setDatabaseName(strDbStorePath + "/" + strDatabaseName);
	if (!PrjMyDBLibrary::objDbCon.open())
	{
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
		                      qApp->tr("Unable to establish a database connection.\n"
		                               "This example needs SQLite support. Please read "
		                               "the Qt SQL driver documentation for information how "
		                               "to build it.\n\n"
		                               "Click Cancel to exit."), QMessageBox::Cancel);
		return;
	}
	else
	{
		blnIsConnectionOpen=true;
		PrjMyDBLibrary::objRs = {QSqlQuery(PrjMyDBLibrary::objDbCon)};
	}
}

void PrjMyDBLibrary::fnConnectDbForNonAndroid()
{
	PrjMyDBLibrary::objDbCon = QSqlDatabase::addDatabase("QSQLITE");
	PrjMyDBLibrary::objDbCon.setDatabaseName(strDbStorePath + strDatabaseName);
	if (!PrjMyDBLibrary::objDbCon.open())
	{
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
		                      qApp->tr("Unable to establish a database connection.\n"
		                               "This example needs SQLite support. Please read "
		                               "the Qt SQL driver documentation for information how "
		                               "to build it.\n\n"
		                               "Click Cancel to exit."), QMessageBox::Cancel);
		return;
	}
	else
	{
		blnIsConnectionOpen=true;
		PrjMyDBLibrary::objRs = {QSqlQuery(PrjMyDBLibrary::objDbCon)};
	}
}


//single row single column
double PrjMyDBLibrary::fnGetSRSCDoubleValue(QString strQuery,QString strColName)
{
	if(fnGetSingleRowSingleColFieldValue(strQuery,strColName,clsReturnDataType::DOUBLE))
	{
		return dblSingleVal;
	}
	else
	{
		return -1.0;
	}
}

//single row single column
float PrjMyDBLibrary::fnGetSRSCFloatValue(QString strQuery,QString strColName)
{
	if(fnGetSingleRowSingleColFieldValue(strQuery,strColName,clsReturnDataType::FLOAT))
	{
		return fltSingleVal;
	}
	else
	{
		return -1.0;
	}
}

//single row single column
QString PrjMyDBLibrary::fnGetSRSCStringValue(QString strQuery,QString strColName)
{
	if(fnGetSingleRowSingleColFieldValue(strQuery,strColName,clsReturnDataType::STRING))
	{
		return strSingleVal;
	}
	else
	{
		return "";
	}
}

//single row single column
int PrjMyDBLibrary::fnGetSRSCRowIntValue(QString strQuery,QString strColName)
{
	if(fnGetSingleRowSingleColFieldValue(strQuery,strColName,clsReturnDataType::INT))
	{
		return intSingleVal;
	}
	else
	{
		return -1;
	}
}

//single row single column
bool PrjMyDBLibrary::fnGetSingleRowSingleColFieldValue(QString strQuery,QString strColName, clsReturnDataType returnType)
{
	if(PrjMyDBLibrary::objRs.exec(strQuery))
	{
		if(PrjMyDBLibrary::objRs.next())
		{
			switch(returnType)
			{
			case clsReturnDataType::INT:
				intSingleVal = PrjMyDBLibrary::objRs.value(strColName).toInt();
				break;
			case clsReturnDataType::DOUBLE:
				dblSingleVal = PrjMyDBLibrary::objRs.value(strColName).toDouble();
				break;
			case clsReturnDataType::FLOAT:
				fltSingleVal = PrjMyDBLibrary::objRs.value(strColName).toFloat();
				break;
			case clsReturnDataType::STRING:
				strSingleVal = PrjMyDBLibrary::objRs.value(strColName).toString();
				break;
			}
		}
		else
		{
			QMessageBox::critical(0, qApp->tr("Query Error"), qApp->tr("No row found error"),QMessageBox::Cancel);
			PrjMyDBLibrary::objRs.clear();
			return false;
		}
	}
	else
	{
		QMessageBox::critical(0, qApp->tr("Query Error"), qApp->tr("Query execution error"),QMessageBox::Cancel);
		return false;
	}
	PrjMyDBLibrary::objRs.clear();
	return true;
}
