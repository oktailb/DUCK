TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -I/usr/lib64/wx/include/gtk3-unicode-3.0 -I/usr/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread
QMAKE_LFLAGS += -pthread   -lwx_gtk3u_xrc-3.0 -lwx_gtk3u_webview-3.0 -lwx_gtk3u_html-3.0 -lwx_gtk3u_qa-3.0 -lwx_gtk3u_adv-3.0 -lwx_gtk3u_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0

INCLUDEPATH += inc

SOURCES +=  main.cpp \
            MainWindow.cpp \
            src/MMI/editFormMMI.cpp \
            src/MMI/flowMMI.cpp \
            src/MMI/sideMMI.cpp \
            src/MMI/tribunePanelMMI.cpp \
            src/MMI/filtersPanelMMI.cpp \
            src/MMI/pluginsPanelMMI.cpp \
            src/MMI/controlPanelMMI.cpp \
            src/MMI/palmipede.cpp


HEADERS += \
    inc/Appli.h \
    inc/MainWindow.h \
    inc/MMI/editFormMMI.h \
    inc/MMI/flowMMI.h \
    inc/MMI/sideMMI.h \
    inc/MMI/tribunePanelMMI.h \
    inc/MMI/filtersPanelMMI.h \
    inc/MMI/pluginsPanelMMI.h \
    inc/MMI/controlPanelMMI.h \
    inc/MMI/palmipede.h
