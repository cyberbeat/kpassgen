project(kpassgen)

find_package(ECM 5.61.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(ECMAddAppIcon)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)

find_package(Qt5 COMPONENTS Core Widgets DBus REQUIRED)
find_package(KF5Config)
find_package(KF5I18n)
find_package(KF5XmlGui)
find_package(KF5CoreAddons)
find_package(KF5Completion)
find_package(KF5Auth)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
cmake_minimum_required(VERSION 2.6)


###### Building kdicegen executable ######
set(kpassgen_SRCS
    main.cpp
    mainwindow.cpp
    generatepassword.cpp
    passwordview.cpp
    passwordwidget.cpp
    passwordmodel.cpp
)

ecm_qt_declare_logging_category(kpassgen_SRCS HEADER kpassgen.h IDENTIFIER kpassgen CATEGORY_NAME org.kde.kpassgen)


kconfig_add_kcfg_files(kpassgen_SRCS settings.kcfgc)

ki18n_wrap_ui(kpassgen_SRCS kpassgen.ui)

file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/*-kpassgen.png")

ecm_add_app_icon(kpassgen ICONS ${ICONS_SRCS})

add_executable(kpassgen ${kpassgen_SRCS})

target_link_libraries(kpassgen KF5::XmlGui KF5::I18n KF5::CoreAddons KF5::Completion KF5::Auth)

########### install files ###############

install(TARGETS kpassgen DESTINATION ${BIN_INSTALL_DIR})

install(FILES kpassgen.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

install(FILES kpassgen.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})

ecm_install_icons(ICONS ${ICONS_SRCS} DESTINATION ${ICON_INSTALL_DIR})

install(FILES settings.kcfg  DESTINATION  ${KCFG_INSTALL_DIR})

install(FILES kpassgenui.rc DESTINATION  ${KXMLGUI_INSTALL_DIR}/kpassgen)
