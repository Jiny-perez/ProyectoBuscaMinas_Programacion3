include("C:/C++/Proyecto_Buscaminas/build/Release/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Proyecto_Buscaminas-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "C:/C++/Proyecto_Buscaminas/build/Release/Proyecto_Buscaminas.exe"
    GENERATE_QT_CONF
)
