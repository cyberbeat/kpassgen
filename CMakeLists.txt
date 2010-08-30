project(kpassgen)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${QT_INCLUDE} ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

###### Building kdicegen executable ######
set(kpassgen_SRCS
	main.cpp
	mainwindow.cpp
	hexpage.cpp
	alphanumericalpage.cpp
	optionspage.cpp
	generatepassword.cpp
    passwordlist.cpp
)

kde4_add_kcfg_files(kpassgen_SRCS settings.kcfgc)

kde4_add_ui_files(kpassgen_SRCS alphanumericalpage.ui hexpage.ui optionspage.ui)

kde4_add_app_icon( kpassgen "${CMAKE_CURRENT_SOURCE_DIR}/hi*-app-kpassgen.png"})

kde4_add_executable(kpassgen ${kpassgen_SRCS})

target_link_libraries(kpassgen ${KDE4_KDEUI_LIBS})


########### install files ###############

install(TARGETS kpassgen DESTINATION ${BIN_INSTALL_DIR})

install( FILES kpassgen.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR} )

install( FILES settings.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )


