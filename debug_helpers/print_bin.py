import gdb

class BinPrint(gdb.Command):
    def __init__(self):
        super(BinPrint, self).__init__("bin_print", gdb.COMMAND_USER)

    def invoke(self, arg, form_tty):
        value = int(gdb.parse_and_eval(arg))
        size = 8
        if (value > 2**8 - 1):
            size = 16
        if (value > 2**16 - 1):
            size = 34
        size += 2
        print(f"{value:#0{size}b}")

BinPrint()


