def __fmt(color: int, placeholder: str, msg: str, *args):
    print(f"\x1b[1m[\x1b[{color}m{placeholder}\x1b[0;1m]: {msg}", *args, "\x1b[0m")


def ok(msg: str, *args):
    __fmt(32, "OK", msg, *args)


def warning(msg: str, *args):
    __fmt(33, "WARNING", msg, *args)


def error(msg: str, *args):
    __fmt(31, "ERROR", msg, *args)


def note(msg: str, *args):
    __fmt(34, "NOTE", msg, *args)
