import sys
import json
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWebEngineWidgets import QWebEngineView


# 数据存储文件名
DATA_FILE = 'data.dll'


# 创建主窗口
class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # 设置窗口标题
        self.setWindowTitle('microweb浏览器')
        # 设置窗口大小900*600
        self.resize(1500, 900)
        # 设置窗口图标
        self.setWindowIcon(QIcon('icons/icon.ico'))
        self.show()

        # 创建tabwidget（多标签页面）
        self.tabWidget = QTabWidget()
        self.tabWidget.setTabShape(QTabWidget.Triangular)
        self.tabWidget.setDocumentMode(True)
        self.tabWidget.setMovable(True)
        self.tabWidget.setTabsClosable(True)
        self.tabWidget.tabCloseRequested.connect(self.close_Tab)
        self.setCentralWidget(self.tabWidget)

        # 第一个tab页面
        self.webview = WebEngineView(self)  # self必须要有，是将主窗口作为参数，传给浏览器
        self.create_tab(self.webview)

        # 使用QToolBar创建导航栏，并使用QAction创建按钮
        # 添加导航栏
        navigation_bar = QToolBar('Navigation')
        # 设定图标的大小
        navigation_bar.setIconSize(QSize(16, 16))
        # 添加导航栏到窗口中
        self.addToolBar(navigation_bar)

        # QAction类提供了抽象的用户界面action，这些action可以被放置在窗口部件中
        # 添加前进、后退、停止加载和刷新的按钮
        back_button = QAction(QIcon('icons/houtui.png'), 'Back', self)
        next_button = QAction(QIcon('icons/qianjin.png'), 'Forward', self)
        stop_button = QAction(QIcon('icons/close.png'),'stop', self)
        reload_button = QAction(QIcon('icons/shuaxin.png'),'reload', self)

        # 绑定事件
        back_button.triggered.connect(self.webview.back)
        next_button.triggered.connect(self.webview.forward)
        stop_button.triggered.connect(self.webview.stop)
        reload_button.triggered.connect(self.webview.reload)

        # 将按钮添加到导航栏上
        navigation_bar.addAction(back_button)
        navigation_bar.addAction(next_button)
        navigation_bar.addAction(stop_button)
        navigation_bar.addAction(reload_button)

        # 添加URL地址栏
        self.urlbar = QLineEdit()
        # 让地址栏能响应回车按键信号
        self.urlbar.returnPressed.connect(self.navigate_to_url)

        navigation_bar.addSeparator()
        navigation_bar.addWidget(self.urlbar)

        # 让浏览器相应url地址的变化
        self.webview.urlChanged.connect(self.renew_urlbar)

        # 加载上次关闭时的网页
        self.load_previous_sessions()

        # 添加新建页面按钮
        new_tab_button = QAction(QIcon('icons/new.png'), 'New Tab', self)
        new_tab_button.triggered.connect(self.new_tab)
        navigation_bar.addAction(new_tab_button)

        # 连接下载请求信号
        profile = self.webview.page().profile()
        profile.downloadRequested.connect(self.handle_download_request)

    def load_previous_sessions(self):
        try:
            with open(DATA_FILE, 'r', encoding='utf-8') as f:
                data = json.load(f)
                for url in data.get('urls', []):
                    webview = WebEngineView(self)
                    webview.load(QUrl(url))
                    self.create_tab(webview)
        except FileNotFoundError:
            # 首次启动，创建默认页面
            self.webview.load(QUrl("https://www.bing.com/?mkt=zh-CN"))

    def save_sessions(self):
        data = {'urls': []}
        for index in range(self.tabWidget.count()):
            widget = self.tabWidget.widget(index)
            layout = widget.layout()
            if layout:
                webview = layout.itemAt(0).widget()
                if isinstance(webview, WebEngineView):
                    data['urls'].append(webview.url().toString())
        with open(DATA_FILE, 'w', encoding='utf-8') as f:
            json.dump(data, f, ensure_ascii=False, indent=4)

    # 显示地址
    def navigate_to_url(self):
        q = QUrl(self.urlbar.text())
        if q.scheme() == '':
            q.setScheme('http')
        self.webview.setUrl(q)

    # 响应输入的地址
    def renew_urlbar(self, q):
        # 将当前网页的链接更新到地址栏
        self.urlbar.setText(q.toString())
        self.urlbar.setCursorPosition(0)

    # 创建tab页面
    def create_tab(self, webview):
        self.tab = QWidget()
        index = self.tabWidget.addTab(self.tab, "加载中...")
        self.tabWidget.setCurrentWidget(self.tab)

        # 渲染到页面
        self.Layout = QHBoxLayout(self.tab)
        self.Layout.setContentsMargins(0, 0, 0, 0)
        self.Layout.addWidget(webview)

        # 连接标题变化信号
        webview.titleChanged.connect(lambda title: self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), title))

    # 关闭tab页面
    def close_Tab(self, index):
        if self.tabWidget.count() > 1:
            self.tabWidget.removeTab(index)
        else:
            self.close()  # 当只有1个tab时，关闭主窗口

    def new_tab(self):
        new_webview = WebEngineView(self)
        new_webview.load(QUrl("https://www.bing.com/?mkt=zh-CN"))
        self.create_tab(new_webview)

    def closeEvent(self, event):
        self.save_sessions()
        event.accept()

    def handle_download_request(self, download):
        # 选择保存文件的路径
        save_path, _ = QFileDialog.getSaveFileName(self, '保存文件', '', '')
        if save_path:
            download.setPath(save_path)
            download.accept()

    def contextMenuEvent(self, event):
        # 创建右键菜单
        context_menu = QMenu(self)
        about_action = QAction('关于', self)
        about_action.triggered.connect(self.show_about_dialog)
        context_menu.addAction(about_action)
        context_menu.exec_(self.mapToGlobal(event.pos()))

    def show_about_dialog(self):
        # 显示关于对话框
        QMessageBox.about(self, '关于 microweb 浏览器', '(c) 2025 Lin Honghan\n这是一个简单的PyQt5浏览器，\n用于学习目的。\n开源地址:https://github.com/linhhanpy/microweb/')


# 创建浏览器，重写createwindow方法实现页面连接的点击跳转
class WebEngineView(QWebEngineView):
    def __init__(self, mainwindow, parent=None):
        super(WebEngineView, self).__init__(parent)
        self.mainwindow = mainwindow

    # 重写createwindow()
    def createWindow(self, QWebEnginePage_WebWindowType):
        new_webview = WebEngineView(self.mainwindow)
        self.mainwindow.create_tab(new_webview)
        return new_webview


# 程序入口
if __name__ == "__main__":
    app = QApplication(sys.argv)
    # 创建主窗口
    browser = MainWindow()
    browser.show()
    # 运行应用，并监听事件
    sys.exit(app.exec_())

# pyinstaller -i icon.ico -w --clean main.py
