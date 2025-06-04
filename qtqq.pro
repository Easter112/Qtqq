QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataBase/database.cpp \
    WidgetLogin/Body/centerwidget.cpp \
    WidgetLogin/Body/login/loginwidget.cpp \
    WidgetLogin/Body/modify/modifypassword.cpp \
    WidgetLogin/Body/regist/registwidget.cpp \
    WidgetLogin/Tittle/tittleBar.cpp \
    WidgetLogin/frame/baseframe.cpp \
    WidgetLogin/frame/formwork.cpp \
    WidgetLogin/utils/utils.cpp \
    WidgetMain/framework/chatform.cpp \
    WidgetMain/framework/contactform.cpp \
    WidgetMain/framework/mainform.cpp \
    WidgetMain/mainApp/Contact/contact.cpp \
    WidgetMain/mainApp/chatModule/communicate/message.cpp \
    WidgetMain/mainApp/chatModule/send/sendmsg.cpp \
    WidgetMain/mainApp/chatModule/topTittleBar/toptittle.cpp \
    WidgetMain/mainApp/chatwindow.cpp \
    WidgetMain/mainApp/leftToolsBar/toolsbar.cpp \
    WidgetMain/mainApp/search/form.cpp \
    WidgetMain/utils/CustomTreeDelegate.cpp \
    WidgetMain/utils/messageitemdelegate.cpp \
    WidgetMain/utils/windowbehaviour.cpp \
    main.cpp

HEADERS += \
    DataBase/database.h \
    WidgetLogin/Body/centerwidget.h \
    WidgetLogin/Body/login/loginwidget.h \
    WidgetLogin/Body/modify/modifypassword.h \
    WidgetLogin/Body/regist/registwidget.h \
    WidgetLogin/Tittle/tittlebar.h \
    WidgetLogin/frame/baseframe.h \
    WidgetLogin/frame/formwork.h \
    WidgetLogin/utils/utils.h \
    WidgetMain/framework/chatform.h \
    WidgetMain/framework/contactform.h \
    WidgetMain/framework/mainform.h \
    WidgetMain/mainApp/Contact/contact.h \
    WidgetMain/mainApp/chatModule/communicate/message.h \
    WidgetMain/mainApp/chatModule/send/sendmsg.h \
    WidgetMain/mainApp/chatModule/topTittleBar/toptittle.h \
    WidgetMain/mainApp/chatwindow.h \
    WidgetMain/mainApp/leftToolsBar/toolsbar.h \
    WidgetMain/mainApp/search/form.h \
    WidgetMain/utils/CustomTreeDelegate.h \
    WidgetMain/utils/messageitemdelegate.h \
    WidgetMain/utils/windowbehaviour.h

FORMS += \
    WidgetLogin/Body/centerwidget.ui \
    WidgetLogin/Body/login/loginwidget.ui \
    WidgetLogin/Body/modify/modifypassword.ui \
    WidgetLogin/Body/regist/registwidget.ui \
    WidgetLogin/Tittle/tittlebar.ui \
    WidgetLogin/frame/formwork.ui \
    WidgetMain/framework/chatform.ui \
    WidgetMain/framework/contactform.ui \
    WidgetMain/framework/mainform.ui \
    WidgetMain/mainApp/chatModule/communicate/message.ui \
    WidgetMain/mainApp/chatModule/send/sendmsg.ui \
    WidgetMain/mainApp/chatModule/topTittleBar/toptittle.ui \
    WidgetMain/mainApp/chatwindow.ui \
    WidgetMain/mainApp/contact/contact.ui \
    WidgetMain/mainApp/leftToolsBar/toolsbar.ui \
    WidgetMain/mainApp/search/form.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/res.qrc

DISTFILES += \
    resource/css/loginWidget.css \
    resource/css/registWidget.css \
    resource/image/123.png \
    resource/image/call.png \
    resource/image/chatLogo.png \
    resource/image/close.png \
    resource/image/contactLogo.png \
    resource/image/cut.png \
    resource/image/editHeadPicture.png \
    resource/image/emotion.png \
    resource/image/file.png \
    resource/image/headChange.png \
    resource/image/info.png \
    resource/image/logo.png \
    resource/image/max.png \
    resource/image/message.png \
    resource/image/min.png \
    resource/image/newuser.png \
    resource/image/qqlogoclassic.png \
    resource/image/restore.png \
    resource/image/skin.png \
    resource/image/video.png
