#include "cmakelists.h"
#include <QTextStream>

CMakeLists::CMakeLists()
{

}

void CMakeLists::SetProjectName(const QString &name)
{
    projectName = name;
}

void CMakeLists::AddCMakeFlags(const QString & key, const QString & value)
{
    cmakeFlags.insert(key,value);
}

void CMakeLists::AddDefine(const QString & value)
{
    defines.append(value);
}

void CMakeLists::AddIncludeDirectory(const QString & dir)
{
    includeDirectories.append(dir);
}


void CMakeLists::AddSousrce(const QString & key, const QString & value)
{
    sources.insert(key, value);
}

QString CMakeLists::GenerateCMakeLists()
{
    QString outputString;
    QTextStream ots(&outputString);

    for (const auto& e: cmakeFlags.keys())
    {
        ots << QString("set (%1 %2)").arg(e, cmakeFlags.value(e)) << endl;
    }

    // add definitions
    if (defines.size() > 0)
    {
        QString def = "";
        for (const auto& e: defines)
        {
            def += "-D" + e + " ";
        }
        ots << QString("add definitions(%1)").arg(def) << endl;
    }

    // include directories
    for (const auto& e: includeDirectories)
    {
        ots << QString("include_directoreis(%1)").arg(e) << endl;
    }

    for (const auto& e: sources.keys())
    {
        ots << QString("add_executable(%1 %2)").arg(e, sources.value(e)) << endl;
    }

    return outputString;
}
