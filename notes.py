import tkinter as tk
from tkinter import filedialog, messagebox, font
import os
import chardet

class CodeEditor(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title('Notes')
        self.geometry('1200x800')

        # 设置字体
        self.custom_font = font.Font(family="Consolas", size=12)
        
        # 创建用于显示行号的Canvas组件
        self.lineno = tk.Canvas(self, width=40, bg='light grey')
        self.lineno.pack(side=tk.LEFT, fill=tk.Y)

        # 创建垂直滚动条
        self.vsb = tk.Scrollbar(self, orient="vertical")
        self.vsb.pack(side=tk.RIGHT, fill=tk.Y)

        self.text_editor = tk.Text(self, bg='black', fg='white', insertbackground='white', 
                                   font=self.custom_font, yscrollcommand=self.vsb.set)
        self.text_editor.pack(fill=tk.BOTH, expand=True)

        # 绑定 <<Modified>> 事件到 text_editor_change 方法
        self.text_editor.bind("<<Modified>>", self.text_editor_change)

        self.create_menu()

        # 初始化keywords字典
        self.keywords = {
            '赋值': '#00ffff',
            '加': '#00ffff',
            '减': '#00ffff',
            '调用': '#00ffff',
            '定义': '#00ffff',
            '；': '#aaaaaa',
            '“': '#00ff00',
            '”': '#00ff00',
            '主函数': '#ff0000',
            '返回': '#ff0000',
            '声明': '#aa00ff',
            '全局': '#aa00ff',
            '代码段': '#aa00ff',
            '0': '#ffff00',
            '1': '#ffff00',
            '2': '#ffff00',
            '3': '#ffff00',
            '4': '#ffff00',
            '5': '#ffff00',
            '6': '#ffff00',
            '7': '#ffff00',
            '8': '#ffff00',
            '9': '#ffff00',
            '0x': '#ffff00',
            '栈顶': '#848400',
            'rax': '#848400',
            'rbx': '#848400',
            'rcx': '#848400',
            'rdx': '#848400'
        }

        self.highlight_keywords()

        # 更新行号
        self.update_line_numbers()

        # 配置滚动条
        self.vsb['command'] = self.on_vsb_move

    def on_text_yview(self, *args):
        # 更新行号
        self.update_line_numbers()
        # 调用垂直滚动条的set方法
        self.vsb.set(*args)

    def create_menu(self):
        menu_bar = tk.Menu(self)
        self.config(menu=menu_bar)

        file_menu = tk.Menu(menu_bar, tearoff=0)
        menu_bar.add_cascade(label='文件', menu=file_menu)
        file_menu.add_command(label='打开', command=self.open_file)
        file_menu.add_command(label='保存', command=self.save_file)

        mode_menu = tk.Menu(menu_bar, tearoff=0)
        menu_bar.add_cascade(label='模式', menu=mode_menu)
        mode_menu.add_command(label='CASM', command=self.CASM)
        mode_menu.add_command(label='NASM', command=self.NASM)
        mode_menu.add_command(label='C/C++', command=self.C_language)
        mode_menu.add_command(label='Simple', command=self.simple)
        mode_menu.add_command(label='Python', command=self.Python)
        mode_menu.add_command(label='Rust', command=self.Rust)
        mode_menu.add_command(label='Java', command=self.Java)

        other_menu = tk.Menu(menu_bar, tearoff=0)
        menu_bar.add_cascade(label='其他', menu=other_menu)
        other_menu.add_command(label='编译C', command=self.compile_c)
        other_menu.add_command(label='编译C++', command=self.compile_cpp)
        other_menu.add_command(label='运行python', command=self.compile_python)
        other_menu.add_command(label='关于', command=self.about)
        other_menu.add_command(label='...', command=self.nothing)

    def open_file(self):
        filepath = filedialog.askopenfilename()
        if filepath:
            try:
                self.current_opened_file_path = filepath
                with open(filepath, 'rb') as raw_file:
                    raw_content = raw_file.read()
                    result = chardet.detect(raw_content)
                    encoding = result.get('encoding', 'utf-8')
                with open(filepath, 'r', encoding=encoding) as file:
                    content = file.read()
                    self.text_editor.delete(1.0, tk.END)
                    self.text_editor.insert(1.0, content)
                    # 调用 text_editor_change 以高亮显示新内容
                    self.text_editor_change(None)
            except Exception as e:
                print(f"打开文件时发生错误: {e}")


    def save_file(self):
        filepath = filedialog.asksaveasfilename(defaultextension='.txt')
        if filepath:
            content = self.text_editor.get(1.0, tk.END)
            with open(filepath, 'w') as file:
                file.write(content)

    def highlight_keywords(self):
        for keyword, color in self.keywords.items():
            self.text_editor.tag_config(keyword, foreground=color)
            start = '1.0'
            while True:
                pos = self.text_editor.search(keyword, start, stopindex=tk.END)
                if not pos: break
                end = f'{pos}+{len(keyword)}c'
                self.text_editor.tag_add(keyword, pos, end)
                start = end

    def text_editor_change(self, event):
        self.text_editor.edit_modified(False)  # 清除已修改标记
        self.highlight_keywords()  # 重新高亮显示关键词
        self.update_line_numbers()  # 更新行号

    def update_line_numbers(self):
        # Clear existing line numbers
        self.lineno.delete("all")

        # Get the total number of lines in the text editor
        line_count = int(self.text_editor.index('end-1c').split('.')[0])

        # Redraw the line numbers based on the actual position of each line in the text editor
        for i in range(1, line_count + 1):
            # Get the top-left and bottom-right coordinates of the line in the text editor
            bbox = self.text_editor.bbox(f"{i}.0")

            if bbox:
                # The third element of bbox represents the Y-coordinate of the top-left corner of the line
                y = bbox[1]

                # Draw the line number at the appropriate position in the canvas
                self.lineno.create_text(2, y, anchor="nw", text=str(i), fill="dark blue", font=self.custom_font)

    def on_vsb_move(self, first, last):
        try:
            first_float = float(first)
            self.text_editor.yview_moveto(first_float)
        except ValueError:
            pass

    def nothing(self):
        pass

    def about(self):
        messagebox.showinfo("关于", "作者：林泓翰")

    def NASM(self):
        self.keywords = {
            'mov': '#00ffff',
            'add': '#00ffff',
            'sub': '#00ffff',
            'call': '#00ffff',
            'db': '#00ffff',
            ';': '#aaaaaa',
            '"': '#00ff00',
            'main': '#ff0000',
            'ret': '#ff0000',
            'extern': '#aa00ff',
            'global': '#aa00ff',
            'SECTION .test': '#aa00ff',
            '0': '#ffff00',
            '1': '#ffff00',
            '2': '#ffff00',
            '3': '#ffff00',
            '4': '#ffff00',
            '5': '#ffff00',
            '6': '#ffff00',
            '7': '#ffff00',
            '8': '#ffff00',
            '9': '#ffff00',
            '0x': '#ffff00',
            'rsp': '#848400',
            'rax': '#848400',
            'rbx': '#848400',
            'rcx': '#848400',
            'rdx': '#848400'
        }
        self.highlight_keywords()

    def simple(self):
        self.keywords = {
            'mov': '#00ffff',
            'add': '#00ffff',
            'sub': '#00ffff',
            'call': '#00ffff',
            'db': '#00ffff',
            'rsp': '#848400',
            'rax': '#848400',
            'rbx': '#848400',
            'rcx': '#848400',
            'rdx': '#848400',
            'main': '#ff0000',
            'ret': '#ff0000',
            'extern': '#aa00ff',
            'global': '#aa00ff',
            'SECTION .test': '#aa00ff',
            'print': '#00ffff',
            'input': '#00ffff',
            'int': '#00ffff',
            'str': '#00ffff',
            'MessageBoxA': '#00ffff',
            'if': '#800080',
            'else': '#800080',
            'while': '#800080',
            'for': '#800080',
            '"': '#00ff00',
            'main': '#ff0000',
            'return': '#ff0000',
            '[': '#848400',
            ']': '#848400',
            '?': '#848400',
            ':': '#848400',
            '%': '#848400',
            '^': '#848400',
            '|': '#848400',
            '~': '#848400',
            '0': '#ffff00',
            '1': '#ffff00',
            '2': '#ffff00',
            '3': '#ffff00',
            '4': '#ffff00',
            '5': '#ffff00',
            '6': '#ffff00',
            '7': '#ffff00',
            '8': '#ffff00',
            '9': '#ffff00',
            '0x': '#ffff00',
            '//': '#aaaaaa',
            '/*': '#aaaaaa',
            '*/': '#aaaaaa',
            '#': '#aaaaaa',
            '{': '#848400',
            '}': '#848400',
            '(': '#848400',
            ')': '#848400',
            ';': '#848400',
            ',': '#848400',
            '.': '#848400',
            '&': '#848400',
            '*': '#848400',
            '+': '#848400',
            '-': '#848400',
            '/': '#848400',
            '=': '#848400',
            '<': '#848400',
            '>': '#848400',
            '"': '#00ff00',
            '!': '#848400',
            '0x': '#ffff00',
            '#NASM_END': '#848400',
            '#NASM': '#848400',
            '#include': '#848400',
        }
        self.highlight_keywords()

    def CASM(self):
        self.keywords = {
            '赋值': '#00ffff',
            '加': '#00ffff',
            '减': '#00ffff',
            '调用': '#00ffff',
            '定义': '#00ffff',
            '；': '#aaaaaa',
            '“': '#00ff00',
            '”': '#00ff00',
            '主函数': '#ff0000',
            '返回': '#ff0000',
            '声明': '#aa00ff',
            '全局': '#aa00ff',
            '代码段': '#aa00ff',
            '0': '#ffff00',
            '1': '#ffff00',
            '2': '#ffff00',
            '3': '#ffff00',
            '4': '#ffff00',
            '5': '#ffff00',
            '6': '#ffff00',
            '7': '#ffff00',
            '8': '#ffff00',
            '9': '#ffff00',
            '0x': '#ffff00',
            '栈顶': '#848400',
            'rax': '#848400',
            'rbx': '#848400',
            'rcx': '#848400',
            'rdx': '#848400'
        }
        self.highlight_keywords()

    def C_language(self):
        self.keywords = {
            'int': '#00ffff',
            'float': '#00ffff',
            'double': '#00ffff',
            'char': '#00ffff',
            'void': '#00ffff',
            'if': '#800080',
            'else': '#800080',
            'while': '#800080',
            'for': '#800080',
            'return': '#00ffff',
            'break': '#00ffff',
            'continue': '#00ffff',
            'switch': '#800080',
            'case': '#800080',
            'default': '#00ffff',
            'struct': '#00ffff',
            'typedef': '#00ffff',
            'enum': '#00ffff',
            'union': '#00ffff',
            'const': '#00ffff',
            'static': '#00ffff',
            'extern': '#00ffff',
            'sizeof': '#00ffff',
            'include': '#00ffff',
            'define': '#00ffff',
            'main': '#ff0000',
            'printf': '#00ff00',
            'scanf': '#00ff00',
            'cin': '#00ff00',
            'cout': '#00ff00',
            'std': '#00ff00',
            'using': '#00ff00',
            'namespace': '#00ff00',
            'bool': '#00ffff',
            'true': '#800080',
            'false': '#800080',
            'new': '#00ffff',
            'delete': '#00ffff',
            'try': '#800080',
            'catch': '#00ffff',
            'throw': '#00ffff',
            'template': '#00ffff',
            'typename': '#00ffff',
            'inline': '#00ffff',
            'volatile': '#00ffff',
            'friend': '#00ffff',
            'virtual': '#00ffff',
            'explicit': '#00ffff',
            'override': '#00ffff',
            'constexpr': '#00ffff',
            '[': '#848400',
            ']': '#848400',
            '?': '#848400',
            ':': '#848400',
            '%': '#848400',
            '^': '#848400',
            '|': '#848400',
            '~': '#848400',
            '__attribute__': '#00ffff',
            '0': '#ffff00',
            '1': '#ffff00',
            '2': '#ffff00',
            '3': '#ffff00',
            '4': '#ffff00',
            '5': '#ffff00',
            '6': '#ffff00',
            '7': '#ffff00',
            '8': '#ffff00',
            '9': '#ffff00',
            '0x': '#ffff00',
            '//': '#aaaaaa',
            '/*': '#aaaaaa',
            '*/': '#aaaaaa',
            '#': '#aaaaaa',
            '{': '#848400',
            '}': '#848400',
            '(': '#848400',
            ')': '#848400',
            ';': '#848400',
            ',': '#848400',
            '.': '#848400',
            '&': '#848400',
            '*': '#848400',
            '+': '#848400',
            '-': '#848400',
            '/': '#848400',
            '=': '#848400',
            '<': '#848400',
            '>': '#848400',
            '"': '#00ff00',
            '!': '#848400'
        }
        self.highlight_keywords()

    def Python(self):
        self.keywords = {
            'and': '#00ffff',
            'as': '#00ffff',
            'assert': '#00ffff',
            'async': '#00ffff',
            'await': '#00ffff',
            'break': '#00ffff',
            'class': '#00ffff',
            'continue': '#00ffff',
            'def': '#00ffff',
            'del': '#00ffff',
            'elif': '#00ffff',
            'else': '#00ffff',
            'except': '#00ffff',
            'False': '#800080',
            'finally': '#00ffff',
            'from': '#00ffff',
            'global': '#00ffff',
            'if': '#800080',
            'import': '#00ffff',
            'in': '#00ffff',
            'is': '#00ffff',
            'lambda': '#00ffff',
            'None': '#800080',
            'nonlocal': '#00ffff',
            'not': '#00ffff',
            'or': '#00ffff',
            'pass': '#00ffff',
            'raise': '#00ffff',
            'return': '#00ffff',
            'True': '#800080',
            'try': '#800080',
            'while': '#800080',
            'with': '#00ffff',
            'yield': '#00ffff',
            'input': '#00ff00',
            'int': '#00ffff',
            'float': '#00ffff',
            'str': '#00ffff',
            'list': '#00ffff',
            'tuple': '#00ffff',
            'set': '#00ffff',
            'dict': '#00ffff',
            'for': '#800080',
            'print': '#00ff00',
            '//': '#aaaaaa',
            '%': '#aaaaaa',
            '*': '#aaaaaa',
            '**': '#aaaaaa',
            '+': '#aaaaaa',
            '-': '#aaaaaa',
            '/': '#aaaaaa',
            '=': '#aaaaaa',
            '==': '#848400',
            '!=': '#848400',
            '<': '#848400',
            '>': '#848400',
            '<=': '#848400',
            '>=': '#848400',
            '&': '#848400',
            '|': '#848400',
            '^': '#848400',
            '~': '#848400',
            '<<': '#848400',
            '>>': '#848400',
            '#': '#aaaaaa',
            '{': '#848400',
            '}': '#848400',
            '[': '#848400',
            ']': '#848400',
            '(': '#848400',
            ')': '#848400',
            ';': '#848400',
            ',': '#848400',
            '.': '#848400',
            '@': '#848400',
            '"': '#00ff00',
            "'": '#00ff00',
            '\'': '#00ff00'
        }
        self.highlight_keywords()

    def Rust(self):
        self.keywords = {
            'async': '#00ffff',
            'await': '#00ffff',
            'break': '#00ffff',
            'const': '#00ffff',
            'continue': '#00ffff',
            'crate': '#00ffff',
            'else': '#00ffff',
            'enum': '#00ffff',
            'extern': '#00ffff',
            'false': '#800080',
            'fn': '#00ffff',
            'for': '#800080',
            'if': '#800080',
            'impl': '#00ffff',
            'in': '#00ffff',
            'let': '#00ffff',
            'loop': '#00ffff',
            'match': '#00ffff',
            'mod': '#00ffff',
            'move': '#00ffff',
            'mut': '#00ffff',
            'pub': '#00ffff',
            'ref': '#00ffff',
            'return': '#00ffff',
            'Self': '#00ffff',
           'self': '#00ffff',
            'static': '#00ffff',
            'struct': '#00ffff',
            'super': '#00ffff',
            'trait': '#00ffff',
            'true': '#800080',
            'type': '#00ffff',
            'unsafe': '#00ffff',
            'use': '#00ffff',
            'while': '#800080',
            'Box': '#00ffff',
            'String': '#00ffff',
            'Vec': '#00ffff',
            'i32': '#00ffff',
            'u32': '#00ffff',
            'f32': '#00ffff',
            '&': '#848400',
            '*': '#848400',
            '+': '#848400',
            '-': '#848400',
            '/': '#848400',
            '=': '#848400',
            '<': '#848400',
            '>': '#848400',
            '!': '#848400',
            '#': '#aaaaaa',
            '{': '#848400',
            '}': '#848400',
            '[': '#848400',
            ']': '#848400',
            '(': '#848400',
            ')': '#848400',
            ';': '#848400',
            ',': '#848400',
            '.': '#848400',
            '::': '#848400',
            '"': '#00ff00'
        }
        self.highlight_keywords()

    def Java(self):
        self.keywords = {
            'abstract': '#00ffff',
            'assert': '#00ffff',
            'boolean': '#00ffff',
            'break': '#00ffff',
            'byte': '#00ffff',
            'case': '#00ffff',
            'catch': '#00ffff',
            'char': '#00ffff',
            'class': '#00ffff',
            'const': '#00ffff',
            'continue': '#00ffff',
            'default': '#00ffff',
            'do': '#00ffff',
            'double': '#00ffff',
            'else': '#00ffff',
            'enum': '#00ffff',
            'extends': '#00ffff',
            'final': '#00ffff',
            'finally': '#00ffff',
            'float': '#00ffff',
            'for': '#800080',
            'if': '#800080',
            'implements': '#00ffff',
            'import': '#00ffff',
            'instanceof': '#00ffff',
            'int': '#00ffff',
            'interface': '#00ffff',
            'long': '#00ffff',
            'native': '#00ffff',
            'new': '#00ffff',
            'package': '#00ffff',
            'private': '#00ffff',
            'protected': '#00ffff',
            'public': '#00ffff',
            'return': '#00ffff',
            'short': '#00ffff',
            'static': '#00ffff',
            'strictfp': '#00ffff',
            'super': '#00ffff',
            'switch': '#00ffff',
            'synchronized': '#00ffff',
            'this': '#00ffff',
            'throw': '#00ffff',
            'throws': '#00ffff',
            'transient': '#00ffff',
            'try': '#800080',
            'void': '#00ffff',
            'volatile': '#00ffff',
            'while': '#800080',
            'System.out.println': '#00ff00',
            'Scanner': '#00ff00',
            '.nextInt': '#00ff00',
            '.nextLine': '#00ff00',
            '//': '#aaaaaa',
            '/*': '#aaaaaa',
            '*/': '#aaaaaa',
            '#': '#aaaaaa',
            '{': '#848400',
            '}': '#848400',
            '[': '#848400',
            ']': '#848400',
            '(': '#848400',
            ')': '#848400',
            ';': '#848400',
            ',': '#848400',
            '.': '#848400',
            '=': '#848400',
            '<': '#848400',
            '>': '#848400',
            '<=': '#848400',
            '>=': '#848400',
            '==': '#848400',
            '!=': '#848400',
            '&': '#848400',
            '&&': '#848400',
            '|': '#848400',
            '||': '#848400',
            '^': '#848400',
            '~': '#848400',
            '!': '#848400',
            '"': '#00ff00',
            '\'': '#00ff00'
        }
        self.highlight_keywords()


    def get_current_file_path(self):
        return self.current_opened_file_path

    def compile_c(self):
        messagebox.showinfo("编译C", "开始编译C代码")
        filepath = self.get_current_file_path()
        if not filepath:
            messagebox.showerror("编译C", "请先打开一个C文件")
            return
        output_file = os.path.splitext(filepath)[0] + ".exe"
        compile_command = f"gcc {filepath} -o {output_file}"
        result = os.system(compile_command)
        if result == 0:
            messagebox.showinfo("编译C", f"C代码编译成功:output_file")
        else:
            messagebox.showerror("编译C", f"编译C代码时发生错误: 错误码 {result}")

    def compile_cpp(self):
        messagebox.showinfo("编译C++", "开始编译C++代码")
        filepath = self.get_current_file_path()
        if not filepath:
            messagebox.showerror("编译C++", "请先打开一个C++文件")
            return
        output_file = os.path.splitext(filepath)[0] + ".exe"
        compile_command = f"g++ {filepath} -o {output_file} -std=c++11"
        result = os.system(compile_command)
        if result == 0:
            messagebox.showinfo("编译C++", f"C++代码编译成功:output_file")
        else:
            messagebox.showerror("编译C++", f"编译C++代码时发生错误: 错误码 {result}")

    def compile_python(self):
        messagebox.showinfo("运行python", "开始运行python代码")
        filepath = self.get_current_file_path()
        if not filepath:
            messagebox.showerror("运行python", "请先打开一个python文件")
            return
        compile_command = f"python {filepath}"
        result = os.system(compile_command)


if __name__ == '__main__':
    app = CodeEditor()
    app.mainloop()
